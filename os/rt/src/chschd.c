/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    chschd.c
 * @brief   Scheduler code.
 *
 * @addtogroup scheduler
 * @details This module provides the default portable scheduler code.
 * @{
 */

#include "ch.h"

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

#if (CH_CFG_NO_IDLE_THREAD == FALSE) || defined(__DOXYGEN__)
/**
 * @brief   This function implements the idle thread infinite loop.
 * @details The function puts the processor in the lowest power mode capable
 *          to serve interrupts.<br>
 *          The priority is internally set to the minimum system value so
 *          that this thread is executed only if there are no other ready
 *          threads in the system.
 *
 * @param[in] p         the thread parameter, unused in this scenario
 */
static void _idle_thread(void *p) {

  (void)p;

  while (true) {
    /*lint -save -e522 [2.2] Apparently no side effects because it contains
      an asm instruction.*/
    port_wait_for_interrupt();
    /*lint -restore*/
    CH_CFG_IDLE_LOOP_HOOK();
  }
}
#endif /* CH_CFG_NO_IDLE_THREAD == FALSE */

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

#if (CH_CFG_OPTIMIZE_SPEED == FALSE) || defined(__DOXYGEN__)
/**
 * @brief   Inserts a thread into a priority ordered queue.
 * @note    The insertion is done by scanning the list from the highest
 *          priority toward the lowest.
 *
 * @param[in] tp        the pointer to the thread to be inserted in the list
 * @param[in] tqp       the pointer to the threads list header
 *
 * @notapi
 */
void queue_prio_insert(thread_t *tp, threads_queue_t *tqp) {

  thread_t *cp = (thread_t *)tqp;
  do {
    cp = cp->queue.next;
  } while ((cp != (thread_t *)tqp) && (cp->prio >= tp->prio));
  tp->queue.next             = cp;
  tp->queue.prev             = cp->queue.prev;
  tp->queue.prev->queue.next = tp;
  cp->queue.prev             = tp;
}

/**
 * @brief   Inserts a thread into a queue.
 *
 * @param[in] tp        the pointer to the thread to be inserted in the list
 * @param[in] tqp       the pointer to the threads list header
 *
 * @notapi
 */
void queue_insert(thread_t *tp, threads_queue_t *tqp) {

  tp->queue.next             = (thread_t *)tqp;
  tp->queue.prev             = tqp->prev;
  tp->queue.prev->queue.next = tp;
  tqp->prev                  = tp;
}

/**
 * @brief   Removes the first-out thread from a queue and returns it.
 * @note    If the queue is priority ordered then this function returns the
 *          thread with the highest priority.
 *
 * @param[in] tqp       the pointer to the threads list header
 * @return              The removed thread pointer.
 *
 * @notapi
 */
thread_t *queue_fifo_remove(threads_queue_t *tqp) {
  thread_t *tp = tqp->next;

  tqp->next             = tp->queue.next;
  tqp->next->queue.prev = (thread_t *)tqp;

  return tp;
}

/**
 * @brief   Removes the last-out thread from a queue and returns it.
 * @note    If the queue is priority ordered then this function returns the
 *          thread with the lowest priority.
 *
 * @param[in] tqp   the pointer to the threads list header
 * @return          The removed thread pointer.
 *
 * @notapi
 */
thread_t *queue_lifo_remove(threads_queue_t *tqp) {
  thread_t *tp = tqp->prev;

  tqp->prev             = tp->queue.prev;
  tqp->prev->queue.next = (thread_t *)tqp;

  return tp;
}

/**
 * @brief   Removes a thread from a queue and returns it.
 * @details The thread is removed from the queue regardless of its relative
 *          position and regardless the used insertion method.
 *
 * @param[in] tp        the pointer to the thread to be removed from the queue
 * @return              The removed thread pointer.
 *
 * @notapi
 */
thread_t *queue_dequeue(thread_t *tp) {

  tp->queue.prev->queue.next = tp->queue.next;
  tp->queue.next->queue.prev = tp->queue.prev;

  return tp;
}

/**
 * @brief   Pushes a thread_t on top of a stack list.
 *
 * @param[in] tp    the pointer to the thread to be inserted in the list
 * @param[in] tlp   the pointer to the threads list header
 *
 * @notapi
 */
void list_insert(thread_t *tp, threads_list_t *tlp) {

  tp->queue.next = tlp->next;
  tlp->next      = tp;
}

/**
 * @brief   Pops a thread from the top of a stack list and returns it.
 * @pre     The list must be non-empty before calling this function.
 *
 * @param[in] tlp       the pointer to the threads list header
 * @return              The removed thread pointer.
 *
 * @notapi
 */
thread_t *list_remove(threads_list_t *tlp) {

  thread_t *tp = tlp->next;
  tlp->next = tp->queue.next;

  return tp;
}
#endif /* CH_CFG_OPTIMIZE_SPEED */

/**
 * @brief   Initializes a system instance.
 *
 * @param[out] cip      pointer to the @p ch_instance_t structure
 * @param[in] cicp      pointer to the @p ch_instance_config_t structure
 */
void chSchObjectInit(ch_instance_t *cip,
                     const ch_instance_config_t *cicp) {

  /* Port initialization for the current instance.*/
  port_init(cip);

  /* Ready list initialization.*/
  queue_init(&cip->rlist.queue);
  cip->rlist.prio = NOPRIO;

  /* Registry initialization.*/
#if CH_CFG_USE_REGISTRY == TRUE
  cip->rlist.newer = (thread_t *)&cip->rlist;
  cip->rlist.older = (thread_t *)&cip->rlist;
#endif

  /* Virtual timers list initialization.*/
  __vt_object_init(&cip->vtlist);

  /* Debug support initialization.*/
  __dbg_object_init(&cip->dbg);

#if CH_DBG_TRACE_MASK != CH_DBG_TRACE_MASK_DISABLED
  /* Trace buffer initialization.*/
  __trace_object_init(&cip->trace_buffer);
#endif

  /* Time Measurement initialization.*/
#if CH_CFG_USE_TM == TRUE
  __tm_object_init(&cip->tmc);
#endif

  /* Statistics intialization.*/
#if CH_DBG_STATISTICS == TRUE
  __stats_object_init(&cip->kernel_stats);
#endif

#if CH_CFG_NO_IDLE_THREAD == FALSE
  /* Now this instructions flow becomes the main thread.*/
#if CH_CFG_USE_REGISTRY == TRUE
  cip->rlist.current = _thread_init(&cip->mainthread,
                                    (const char *)&ch_debug,
                                    NORMALPRIO);
#else
  cip->rlist.current = _thread_init(&cip->mainthread, "main", NORMALPRIO);
#endif
#else
  /* Now this instructions flow becomes the idle thread.*/
  cip->rlist.current = _thread_init(&cip->mainthread, "idle", IDLEPRIO);
#endif

#if (CH_DBG_ENABLE_STACK_CHECK == TRUE) || (CH_CFG_USE_DYNAMIC == TRUE)
  cip->rlist.current->wabase = cicp->mainthread_base;
#endif

  /* Setting up the caller as current thread.*/
  cip->rlist.current->state = CH_STATE_CURRENT;

  /* User instance initialization hook.*/
  CH_CFG_INSTANCE_INIT_HOOK(cip);

#if CH_CFG_NO_IDLE_THREAD == FALSE
  {
    thread_descriptor_t idle_descriptor = {
      .name  = "idle",
      .wbase = cicp->idlethread_base,
      .wend  = cicp->idlethread_end,
      .prio  = IDLEPRIO,
      .funcp = _idle_thread,
      .arg   = NULL
    };

    /* This thread has the lowest priority in the system, its role is just to
       serve interrupts in its context while keeping the lowest energy saving
       mode compatible with the system status.*/
    (void) chThdCreateI(&idle_descriptor);
  }
#endif
}

/**
 * @brief   Inserts a thread in the Ready List placing it behind its peers.
 * @details The thread is positioned behind all threads with higher or equal
 *          priority.
 * @pre     The thread must not be already inserted in any list through its
 *          @p next and @p prev or list corruption would occur.
 * @post    This function does not reschedule so a call to a rescheduling
 *          function must be performed before unlocking the kernel. Note that
 *          interrupt handlers always reschedule on exit so an explicit
 *          reschedule must not be performed in ISRs.
 *
 * @param[in] tp        the thread to be made ready
 * @return              The thread pointer.
 *
 * @iclass
 */
thread_t *chSchReadyI(thread_t *tp) {
  thread_t *cp;

  chDbgCheckClassI();
  chDbgCheck(tp != NULL);
  chDbgAssert((tp->state != CH_STATE_READY) &&
              (tp->state != CH_STATE_FINAL),
              "invalid state");

  tp->state = CH_STATE_READY;
  cp = (thread_t *)&currcore->rlist.queue;
  do {
    cp = cp->queue.next;
  } while (cp->prio >= tp->prio);
  /* Insertion on prev.*/
  tp->queue.next             = cp;
  tp->queue.prev             = cp->queue.prev;
  tp->queue.prev->queue.next = tp;
  cp->queue.prev             = tp;

  return tp;
}

/**
 * @brief   Inserts a thread in the Ready List placing it ahead its peers.
 * @details The thread is positioned ahead all threads with higher or equal
 *          priority.
 * @pre     The thread must not be already inserted in any list through its
 *          @p next and @p prev or list corruption would occur.
 * @post    This function does not reschedule so a call to a rescheduling
 *          function must be performed before unlocking the kernel. Note that
 *          interrupt handlers always reschedule on exit so an explicit
 *          reschedule must not be performed in ISRs.
 *
 * @param[in] tp        the thread to be made ready
 * @return              The thread pointer.
 *
 * @iclass
 */
thread_t *chSchReadyAheadI(thread_t *tp) {
  thread_t *cp;

  chDbgCheckClassI();
  chDbgCheck(tp != NULL);
  chDbgAssert((tp->state != CH_STATE_READY) &&
              (tp->state != CH_STATE_FINAL),
              "invalid state");

  tp->state = CH_STATE_READY;
  cp = (thread_t *)&currcore->rlist.queue;
  do {
    cp = cp->queue.next;
  } while (cp->prio > tp->prio);
  /* Insertion on prev.*/
  tp->queue.next             = cp;
  tp->queue.prev             = cp->queue.prev;
  tp->queue.prev->queue.next = tp;
  cp->queue.prev             = tp;

  return tp;
}

/**
 * @brief   Puts the current thread to sleep into the specified state.
 * @details The thread goes into a sleeping state. The possible
 *          @ref thread_states are defined into @p threads.h.
 *
 * @param[in] newstate  the new thread state
 *
 * @sclass
 */
void chSchGoSleepS(tstate_t newstate) {
  thread_t *otp = currthread;

  chDbgCheckClassS();

  /* New state.*/
  otp->state = newstate;

#if CH_CFG_TIME_QUANTUM > 0
  /* The thread is renouncing its remaining time slices so it will have a new
     time quantum when it will wakeup.*/
  otp->ticks = (tslices_t)CH_CFG_TIME_QUANTUM;
#endif

  /* Next thread in ready list becomes current.*/
  currthread = queue_fifo_remove(&currcore->rlist.queue);
  currthread->state = CH_STATE_CURRENT;

  /* Handling idle-enter hook.*/
  if (currthread->prio == IDLEPRIO) {
    CH_CFG_IDLE_ENTER_HOOK();
  }

  /* Swap operation as tail call.*/
  chSysSwitch(currthread, otp);
}

/*
 * Timeout wakeup callback.
 */
static void wakeup(void *p) {
  thread_t *tp = (thread_t *)p;

  chSysLockFromISR();
  switch (tp->state) {
  case CH_STATE_READY:
    /* Handling the special case where the thread has been made ready by
       another thread with higher priority.*/
    chSysUnlockFromISR();
    return;
  case CH_STATE_SUSPENDED:
    *tp->u.wttrp = NULL;
    break;
#if CH_CFG_USE_SEMAPHORES == TRUE
  case CH_STATE_WTSEM:
    chSemFastSignalI(tp->u.wtsemp);
#endif
    /* Falls through.*/
  case CH_STATE_QUEUED:
    /* Falls through.*/
#if (CH_CFG_USE_CONDVARS == TRUE) && (CH_CFG_USE_CONDVARS_TIMEOUT == TRUE)
  case CH_STATE_WTCOND:
#endif
    /* States requiring dequeuing.*/
    (void) queue_dequeue(tp);
    break;
  default:
    /* Any other state, nothing to do.*/
    break;
  }
  tp->u.rdymsg = MSG_TIMEOUT;
  (void) chSchReadyI(tp);
  chSysUnlockFromISR();
}

/**
 * @brief   Puts the current thread to sleep into the specified state with
 *          timeout specification.
 * @details The thread goes into a sleeping state, if it is not awakened
 *          explicitly within the specified timeout then it is forcibly
 *          awakened with a @p MSG_TIMEOUT low level message. The possible
 *          @ref thread_states are defined into @p threads.h.
 *
 * @param[in] newstate  the new thread state
 * @param[in] timeout   the number of ticks before the operation timeouts, the
 *                      special values are handled as follow:
 *                      - @a TIME_INFINITE the thread enters an infinite sleep
 *                        state, this is equivalent to invoking
 *                        @p chSchGoSleepS() but, of course, less efficient.
 *                      - @a TIME_IMMEDIATE this value is not allowed.
 *                      .
 * @return              The wakeup message.
 * @retval MSG_TIMEOUT  if a timeout occurs.
 *
 * @sclass
 */
msg_t chSchGoSleepTimeoutS(tstate_t newstate, sysinterval_t timeout) {

  chDbgCheckClassS();

  if (TIME_INFINITE != timeout) {
    virtual_timer_t vt;

    chVTDoSetI(&vt, timeout, wakeup, currthread);
    chSchGoSleepS(newstate);
    if (chVTIsArmedI(&vt)) {
      chVTDoResetI(&vt);
    }
  }
  else {
    chSchGoSleepS(newstate);
  }

  return currthread->u.rdymsg;
}

/**
 * @brief   Wakes up a thread.
 * @details The thread is inserted into the ready list or immediately made
 *          running depending on its relative priority compared to the current
 *          thread.
 * @pre     The thread must not be already inserted in any list through its
 *          @p next and @p prev or list corruption would occur.
 * @note    It is equivalent to a @p chSchReadyI() followed by a
 *          @p chSchRescheduleS() but much more efficient.
 * @note    The function assumes that the current thread has the highest
 *          priority.
 *
 * @param[in] ntp       the thread to be made ready
 * @param[in] msg       the wakeup message
 *
 * @sclass
 */
void chSchWakeupS(thread_t *ntp, msg_t msg) {
  thread_t *otp = currthread;

  chDbgCheckClassS();

  chDbgAssert((currcore->rlist.queue.next == (thread_t *)&currcore->rlist.queue) ||
              (currcore->rlist.current->prio >= currcore->rlist.queue.next->prio),
              "priority order violation");

  /* Storing the message to be retrieved by the target thread when it will
     restart execution.*/
  ntp->u.rdymsg = msg;

  /* If the waken thread has a not-greater priority than the current
     one then it is just inserted in the ready list else it made
     running immediately and the invoking thread goes in the ready
     list instead.*/
  if (ntp->prio <= otp->prio) {
    (void) chSchReadyI(ntp);
  }
  else {
    otp = chSchReadyI(otp);

    /* Handling idle-leave hook.*/
    if (otp->prio == IDLEPRIO) {
      CH_CFG_IDLE_LEAVE_HOOK();
    }

    /* The extracted thread is marked as current.*/
    currthread = ntp;
    ntp->state = CH_STATE_CURRENT;

    /* Swap operation as tail call.*/
    chSysSwitch(ntp, otp);
  }
}

/**
 * @brief   Performs a reschedule if a higher priority thread is runnable.
 * @details If a thread with a higher priority than the current thread is in
 *          the ready list then make the higher priority thread running.
 *
 * @sclass
 */
void chSchRescheduleS(void) {

  chDbgCheckClassS();

  if (chSchIsRescRequiredI()) {
    chSchDoRescheduleAhead();
  }
}

#if !defined(CH_SCH_IS_PREEMPTION_REQUIRED_HOOKED)
/**
 * @brief   Evaluates if preemption is required.
 * @details The decision is taken by comparing the relative priorities and
 *          depending on the state of the round robin timeout counter.
 * @note    Not a user function, it is meant to be invoked by the scheduler
 *          itself or from within the port layer.
 *
 * @retval true         if there is a thread that must go in running state
 *                      immediately.
 * @retval false        if preemption is not required.
 *
 * @special
 */
bool chSchIsPreemptionRequired(void) {
  tprio_t p1 = firstprio(&currcore->rlist.queue);
  tprio_t p2 = currthread->prio;

#if CH_CFG_TIME_QUANTUM > 0
  /* If the running thread has not reached its time quantum, reschedule only
     if the first thread on the ready queue has a higher priority.
     Otherwise, if the running thread has used up its time quantum, reschedule
     if the first thread on the ready queue has equal or higher priority.*/
  return (currthread->ticks > (tslices_t)0) ? (p1 > p2) : (p1 >= p2);
#else
  /* If the round robin preemption feature is not enabled then performs a
     simpler comparison.*/
  return p1 > p2;
#endif
}
#endif /* !defined(CH_SCH_IS_PREEMPTION_REQUIRED_HOOKED) */

/**
 * @brief   Switches to the first thread on the runnable queue.
 * @details The current thread is positioned in the ready list behind all
 *          threads having the same priority. The thread regains its time
 *          quantum.
 * @note    Not a user function, it is meant to be invoked by the scheduler
 *          itself.
 *
 * @special
 */
void chSchDoRescheduleBehind(void) {
  thread_t *otp = currthread;

  /* Picks the first thread from the ready queue and makes it current.*/
  currthread = queue_fifo_remove(&currcore->rlist.queue);
  currthread->state = CH_STATE_CURRENT;

  /* Handling idle-leave hook.*/
  if (otp->prio == IDLEPRIO) {
    CH_CFG_IDLE_LEAVE_HOOK();
  }

#if CH_CFG_TIME_QUANTUM > 0
  /* It went behind peers so it gets a new time quantum.*/
  otp->ticks = (tslices_t)CH_CFG_TIME_QUANTUM;
#endif

  /* Placing in ready list behind peers.*/
  otp = chSchReadyI(otp);

  /* Swap operation as tail call.*/
  chSysSwitch(currthread, otp);
}

/**
 * @brief   Switches to the first thread on the runnable queue.
 * @details The current thread is positioned in the ready list ahead of all
 *          threads having the same priority.
 * @note    Not a user function, it is meant to be invoked by the scheduler
 *          itself.
 *
 * @special
 */
void chSchDoRescheduleAhead(void) {
  thread_t *otp = currthread;

  /* Picks the first thread from the ready queue and makes it current.*/
  currthread = queue_fifo_remove(&currcore->rlist.queue);
  currthread->state = CH_STATE_CURRENT;

  /* Handling idle-leave hook.*/
  if (otp->prio == IDLEPRIO) {
    CH_CFG_IDLE_LEAVE_HOOK();
  }

  /* Placing in ready list ahead of peers.*/
  otp = chSchReadyAheadI(otp);

  /* Swap operation as tail call.*/
  chSysSwitch(currthread, otp);
}

#if !defined(CH_SCH_DO_RESCHEDULE_HOOKED)
/**
 * @brief   Switches to the first thread on the runnable queue.
 * @details The current thread is positioned in the ready list behind or
 *          ahead of all threads having the same priority depending on
 *          if it used its whole time slice.
 * @note    Not a user function, it is meant to be invoked by the scheduler
 *          itself or from within the port layer.
 *
 * @special
 */
void chSchDoReschedule(void) {
  thread_t *otp = currthread;

  /* Picks the first thread from the ready queue and makes it current.*/
  currthread = queue_fifo_remove(&currcore->rlist.queue);
  currthread->state = CH_STATE_CURRENT;

  /* Handling idle-leave hook.*/
  if (otp->prio == IDLEPRIO) {
    CH_CFG_IDLE_LEAVE_HOOK();
  }

#if CH_CFG_TIME_QUANTUM > 0
  /* If CH_CFG_TIME_QUANTUM is enabled then there are two different scenarios
     to handle on preemption: time quantum elapsed or not.*/
  if (currthread->ticks == (tslices_t)0) {

    /* The thread consumed its time quantum so it is enqueued behind threads
       with same priority level, however, it acquires a new time quantum.*/
    otp = chSchReadyI(otp);

    /* The thread being swapped out receives a new time quantum.*/
    otp->ticks = (tslices_t)CH_CFG_TIME_QUANTUM;
  }
  else {
    /* The thread didn't consume all its time quantum so it is put ahead of
       threads with equal priority and does not acquire a new time quantum.*/
    otp = chSchReadyAheadI(otp);
  }
#else /* !(CH_CFG_TIME_QUANTUM > 0) */
  /* If the round-robin mechanism is disabled then the thread goes always
     ahead of its peers.*/
  otp = chSchReadyAheadI(otp);
#endif /* !(CH_CFG_TIME_QUANTUM > 0) */

  /* Swap operation as tail call.*/
  chSysSwitch(currthread, otp);
}
#endif /* !defined(CH_SCH_DO_RESCHEDULE_HOOKED) */

/** @} */
