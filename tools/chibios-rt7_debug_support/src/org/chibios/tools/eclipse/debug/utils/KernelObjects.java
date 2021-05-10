/********************************************************************************
 * Copyright (c) 2019 Giovanni Di Sirio.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 ********************************************************************************/

package org.chibios.tools.eclipse.debug.utils;

import java.util.HashMap;
import java.util.LinkedHashMap;

public class KernelObjects extends DebugProxy {

  protected final static String[] threadStates = {
    "READY",
    "CURRENT",
    "STARTED",
    "SUSPENDED",
    "QUEUED",
    "WTSEM",
    "WTMTX",
    "WTCOND",
    "SLEEPING",
    "WTEXIT",
    "WTOREVT",
    "WTANDEVT",
    "SNDMSGQ",
    "SNDMSG",
    "WTMSG",
    "FINAL",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown",
    "unknown"
  };

  public KernelObjects() {
  	
  	super();
  }

  private boolean checkChibiOS() throws DebugProxyException {

    // Check on current thread in order to decide if the kernel has already
    // been initialized.
    String r_current;
    try {
      r_current = evaluateExpression("(uint32_t)ch0.rlist.current");
      if (r_current == null)
        return true;
    } catch (DebugProxyException e) {
      throw new DebugProxyException("ChibiOS/RT not found on target");
    } catch (Exception e) {
      return true;
    }
    if (r_current.compareTo("0") == 0)
      throw new DebugProxyException("ChibiOS/RT not yet initialized");

    return false;
  }

  /**
   * @brief   Return the list of threads.
   * @details The threads list is fetched from memory by scanning the
   *          registry.
   *
   * @return  A @p LinkedHashMap object whose keys are the threads addresses
   *          as decimal strings, the value is an @p HashMap of the thread
   *          fields:
   *          - stack
   *          - stklimit
   *          - name
   *          - state
   *          - state_s
   *          - flags
   *          - prio
   *          - refs
   *          - time
   *          - wtobjp
   *          - stats_n
   *          - stats_worst
   *          - stats_cumulative
   *          .
   *          Missing fields are set to "-".
   * @retval null                   If the debugger encountered an error or
   *                                the target is running.
   *
   * @throws DebugProxyException    If the debugger is active but the registry
   *                                is not found, not initialized or corrupted.
   */
  public LinkedHashMap<String, HashMap<String, String>> readThreads()
      throws DebugProxyException {

	if (checkChibiOS())
      return null;

    // rlist structure address.
    String reglist;
    try {
    	// First checking if it is placed in "ch_system", SMP scenario.
    	reglist = evaluateExpression("(uint32_t)&ch_system.reglist");
      if (reglist == null)
        return null;
    } catch (DebugProxyException e) {
    	// Then trying in ch0, non-SMP scenario.
      try {
      	reglist = evaluateExpression("(uint32_t)&ch0.reglist");
        if (reglist == null)
          return null;
      } catch (DebugProxyException e1) {
        throw new DebugProxyException("ready list not found on target");
      } catch (Exception e1) {
        return null;
      }
    } catch (Exception e) {
      return null;
    }

    // Scanning registry.
    LinkedHashMap<String, HashMap<String, String>> lhm =
        new LinkedHashMap<String, HashMap<String, String>>(10);
    String current_reg = reglist;
    String previous_reg = reglist;
    while (true) {
    	String current_thread;
    	
      // Fetching next thread in the registry (newer link). This fetch fails
      // if the register is not enabled in the kernel and the "newer" field
      // does not exist.
      try {
        current_reg = evaluateExpression("(uint32_t)((ch_queue_t *)" + current_reg + ")->next");
      } catch (DebugProxyException e1) {
        throw new DebugProxyException("ChibiOS/RT registry not enabled in kernel");
      }

      // This can happen if the kernel is not initialized yet or if the
      // registry is corrupted.
      if (current_reg.compareTo("0") == 0)
        throw new DebugProxyException("ChibiOS/RT registry integrity check failed, NULL pointer");

      // TODO: integrity check on the pointer value (alignment, range).

      // The previous thread in the list is fetched as an integrity check.
      String older = evaluateExpression("(uint32_t)((ch_queue_t *)" + current_reg + ")->prev");
      if (older.compareTo("0") == 0)
        throw new DebugProxyException("ChibiOS/RT registry integrity check failed, NULL pointer");
      if (previous_reg.compareTo(older) != 0)
        throw new DebugProxyException("ChibiOS/RT registry integrity check failed, double linked list violation");

      // End of the linked list condition.
      if (current_reg.compareTo(reglist) == 0)
        break;

      // Thread associated to this registry entry.
      try {
        long current_thread_address = evaluateExpressionNumber(current_reg + " - ((char *)(&((thread_t *)0)->rqueue) - (char *)0)");
        current_thread = Long.toString(current_thread_address);
      } catch (DebugProxyException e1) {
        throw new DebugProxyException("ChibiOS/RT registry offset calculation error");
      }
      
      // Hash of threads fields.
      HashMap<String, String> map = new HashMap<String, String>(16);

      // Fetch of the various fields in the thread_t structure. Some fields
      // are optional so are placed within try-catch.
      long stklimit;
      try {
        stklimit = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + current_thread + ")->wabase");
        map.put("stklimit", Long.toString(stklimit));
      } catch (DebugProxyException e) {
        map.put("stklimit", "-");
        stklimit = -1;
      }

      long stack;
      try {
        stack = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + current_thread + ")->ctx.r13");
        map.put("stack", Long.toString(stack));
      } catch (DebugProxyException e) {
        try {
          stack = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + current_thread + ")->ctx.sp");
          map.put("stack", Long.toString(stack));
        } catch (DebugProxyException ex) {
          map.put("stack", "-");
          stack = -1;
        }
      }

      if ((stklimit <= 0) || (stack <= 0))
          map.put("stkunused", "-");
      else {
        if ((stack < 0) || (stack < stklimit))
            map.put("stkunused", "overflow");
        else {
          long stkunused = scanStack(stklimit, stack, (byte)0x55);
          map.put("stkunused", Long.toString(stkunused));
        }
      }

      long n;
      try {
        n = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + current_thread + ")->name");
        if (n == 0)
          map.put("name", "<no name>");
        else
          map.put("name", readCString(n, 16));
      } catch (DebugProxyException e) {
        map.put("name", "-");
      }

      n = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + current_thread + ")->state");
      map.put("state", Long.toString(n));
      if ((n >= 0) && (n < threadStates.length)) {
        map.put("state_s", threadStates[(int)n]);
      }
      else
        map.put("state_s", "unknown");

      n = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + current_thread + ")->flags");
      map.put("flags", Long.toString(n));

      n = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + current_thread + ")->hdr.pqueue.prio");
      map.put("prio", Long.toString(n));

      try {
        n = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + current_thread + ")->refs");
        map.put("refs", Long.toString(n));
      } catch (DebugProxyException e) {
        map.put("refs", "-");
      }

      try {
        n = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + current_thread + ")->time");
        map.put("time", Long.toString(n));
      } catch (DebugProxyException e) {
        map.put("time", "-");
      }

      try {
        n = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + current_thread + ")->u.wtobjp");
        map.put("wtobjp", Long.toString(n));
      } catch (DebugProxyException e) {
        map.put("wtobjp", "-");
      }

      try {
        n = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + current_thread + ")->stats.n");
        map.put("stats_n", Long.toString(n));
      } catch (DebugProxyException e) {
        map.put("stats_n", "-");
      }

      try {
        n = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + current_thread + ")->stats.worst");
        map.put("stats_worst", Long.toString(n));
      } catch (DebugProxyException e) {
        map.put("stats_worst", "-");
      }

      try {
        n = evaluateExpressionNumber("(uint64_t)((struct ch_thread *)" + current_thread + ")->stats.cumulative");
        map.put("stats_cumulative", Long.toString(n));
      } catch (DebugProxyException e) {
        map.put("stats_cumulative", "-");
      }

      // Inserting the new thread map into the threads list.
      lhm.put(current_thread, map);

      previous_reg = current_reg;
    }
    return lhm;
  }

  /**
   * @brief   Return the list of timers.
   * @details The timers list is fetched from memory by scanning the
   *          @p vtlist structure.
   *
   * @return  A @p LinkedHashMap object whose keys are the timers addresses
   *          as decimal strings, the value is an @p HashMap of the timers
   *          fields:
   *          - delta
   *          - func
   *          - par
   *          .
   * @retval null                   If the debugger encountered an error or
   *                                the target is running.
   *
   * @throws DebugProxyException    If the debugger is active but the structure
   *                                @p vtlist is not found, not initialized or
   *                                corrupted.
   */
  public LinkedHashMap<String, HashMap<String, String>> readTimers()
      throws DebugProxyException {

    if (checkChibiOS())
      return null;

    // Delta list structure address.
    String vtlist;
    try {
      vtlist = evaluateExpression("(uint32_t)&ch0.vtlist");
      if (vtlist == null)
        return null;
    } catch (DebugProxyException e) {
      throw new DebugProxyException("virtual timers list not found on target");
    } catch (Exception e) {
      return null;
    }

    // Scanning delta list.
    LinkedHashMap<String, HashMap<String, String>> lhm =
        new LinkedHashMap<String, HashMap<String, String>>(10);
    String current = vtlist;
    String previous = vtlist;
    while (true) {
      
      // Fetching next timer in the delta list (next link).
      current = evaluateExpression("(uint32_t)((struct ch_virtual_timer *)" + current + ")->dlist.next");

      // This can happen if the kernel is not initialized yet or if the
      // delta list is corrupted.
      if (current.compareTo("0") == 0)
        throw new DebugProxyException("ChibiOS/RT delta list integrity check failed, NULL pointer");

      // TODO: integrity check on the pointer value (alignment, range).

      // The previous timer in the delta list is fetched as a integrity check.
      String prev = evaluateExpression("(uint32_t)((struct ch_virtual_timer *)" + current + ")->dlist.prev");
      if (prev.compareTo("0") == 0)
        throw new DebugProxyException("ChibiOS/RT delta list integrity check failed, NULL pointer");
      if (previous.compareTo(prev) != 0)
        throw new DebugProxyException("ChibiOS/RT delta list integrity check failed, double linked list violation");

      // End of the linked list condition.
      if (current.compareTo(vtlist) == 0)
        break;

      // Hash of timers fields.
      HashMap<String, String> map = new HashMap<String, String>(16);

      // Fetch of the various fields in the virtual_timer_t structure. Some fields
      // are optional so are placed within try-catch.
      long n = evaluateExpressionNumber("(uint32_t)((struct ch_virtual_timer *)" + current + ")->dlist.delta");
      map.put("delta", Long.toString(n));

      n = evaluateExpressionNumber("(uint32_t)((struct ch_virtual_timer *)" + current + ")->func");
      map.put("func", Long.toString(n));

      n = evaluateExpressionNumber("(uint32_t)((struct ch_virtual_timer *)" + current + ")->par");
      map.put("par", Long.toString(n));

      try {
        n = evaluateExpressionNumber("(uint32_t)((struct ch_virtual_timer *)" + current + ")->last");
        map.put("last", Long.toString(n));
      } catch (DebugProxyException e) {
        map.put("last", "-");
      }

      try {
        n = evaluateExpressionNumber("(uint32_t)((struct ch_virtual_timer *)" + current + ")->reload");
        map.put("reload", Long.toString(n));
      } catch (DebugProxyException e) {
        map.put("reload", "-");
      }

      // Inserting the new thread map into the threads list.
      lhm.put(current, map);

      previous = current;
    }
    return lhm;
  }

  /**
   * @brief   Return the list of trace buffer entries.
   * @details The trace buffer is fetched from memory by scanning the
   *          @p dbg_trace_buffer array.
   *
   * @return  A @p LinkedHashMap object whose keys are the timers addresses
   *          as decimal strings, the value is an @p HashMap of the timers
   *          fields:
   *          - time
   *          - ntp
   *          - wtobjp
   *          - state
   *          - state_s
   *          .
   * @retval null                   If the debugger encountered an error or
   *                                the target is running.
   *
   * @throws DebugProxyException    If the debugger is active but the structure
   *                                @p ch0.trace_buffer is not found, not
   *                                initialized or corrupted.
   */
  public LinkedHashMap<String, HashMap<String, String>> readTraceBuffer()
      throws DebugProxyException {

    if (checkChibiOS())
      return null;

    // Trace buffer size.
    String s;
    try {
      s = evaluateExpression("(uint32_t)ch0.trace_buffer.size");
      if (s == null)
        return null;
    } catch (DebugProxyException e) {
      throw new DebugProxyException("trace buffer not found on target");
    } catch (Exception e) {
      return null;
    }

    int tbsize = (int)HexUtils.parseNumber(s);
    int tbrecsize = (int)evaluateExpressionNumber("(uint32_t)sizeof (trace_event_t)");
    long tbstart = evaluateExpressionNumber("(uint32_t)ch0.trace_buffer.buffer");
    long tbend = evaluateExpressionNumber("(uint32_t)&ch0.trace_buffer.buffer[" + tbsize + "]");
    long tbptr = evaluateExpressionNumber("(uint32_t)ch0.trace_buffer.ptr");

    // Scanning the trace buffer from the oldest event to the newest.
    LinkedHashMap<String, HashMap<String, String>> lhm =
        new LinkedHashMap<String, HashMap<String, String>>(64);
    int n = tbsize;
    int i = -tbsize + 1;
    while (n > 0) {
      // Hash of timers fields.
      HashMap<String, String> map = new HashMap<String, String>(16);

      // This is the record type, fields change according to this.
      String type = evaluateExpression("(uint32_t)(((trace_event_t *)" + tbptr + ")->type)");
      map.put("type", type);

      // Fields common to all types.
      long state = evaluateExpressionNumber("(uint32_t)(((trace_event_t *)" + tbptr + ")->state)");
      map.put("state", Long.toString(state));
      if ((state >= 0) && (state < threadStates.length))
        map.put("state_s", threadStates[(int)state]);
      else
        map.put("state_s", "unknown");

      String rtstamp = evaluateExpression("(uint32_t)(((trace_event_t *)" + tbptr + ")->rtstamp)");
      map.put("rtstamp", rtstamp);

      String time = evaluateExpression("(uint32_t)(((trace_event_t *)" + tbptr + ")->time)");
      map.put("time", time);

      // Fields specific to a CH_TRACE_TYPE_READY event.
      if (type.compareTo("1") == 0) {
        String tp = evaluateExpression("(uint32_t)(((trace_event_t *)" + tbptr + ")->u.rdy.tp)");
        map.put("sw_tp", tp);

        String msg = evaluateExpression("(uint32_t)(((trace_event_t *)" + tbptr + ")->u.rdy.msg)");
        map.put("sw_msg", msg);
      }

      // Fields specific to a CH_TRACE_TYPE_SWITCH event.
      if (type.compareTo("2") == 0) {
        String ntp = evaluateExpression("(uint32_t)(((trace_event_t *)" + tbptr + ")->u.sw.ntp)");
        map.put("sw_ntp", ntp);

        String wtobjp = evaluateExpression("(uint32_t)(((trace_event_t *)" + tbptr + ")->u.sw.wtobjp)");
        map.put("sw_wtobjp", wtobjp);
      }

      // Fields specific to a CH_TRACE_TYPE_ISR_ENTER and CH_TRACE_TYPE_ISR_LEAVE events.
      if ((type.compareTo("3") == 0) || (type.compareTo("4") == 0)) {
        long name = evaluateExpressionNumber("(uint32_t)(((trace_event_t *)" + tbptr + ")->u.isr.name)");
        String name_s = readCString(name, 16);
        map.put("isr_name_s", name_s);
      }

      // Fields specific to a CH_TRACE_TYPE_HALT event.
      if (type.compareTo("5") == 0) {
        long reason = evaluateExpressionNumber("(uint32_t)(((trace_event_t *)" + tbptr + ")->u.halt.reason)");
        String reason_s = readCString(reason, 16);
        map.put("halt_reason_s", reason_s);
      }

      // Fields specific to a CH_TRACE_TYPE_USER event.
      if (type.compareTo("6") == 0) {
        String up1 = evaluateExpression("(uint32_t)(((trace_event_t *)" + tbptr + ")->u.user.up1)");
        map.put("user_up1", up1);

        String up2 = evaluateExpression("(uint32_t)(((trace_event_t *)" + tbptr + ")->u.user.up2)");
        map.put("user_up2", up2);
      }

      // Inserting the new event map into the events list if it is not CH_TRACE_TYPE_UNUSED.
      if (type.compareTo("0") != 0)
        lhm.put(Integer.toString(i), map);

      tbptr += tbrecsize;
      if (tbptr >= tbend)
        tbptr = tbstart;
      n--;
      i++;
    }
    return lhm;
  }
  
  /**
   * @brief   Return the list of the system global variables.
   *
   * @return  A @p LinkedHashMap object whose keys are the variable names and
   *          the values are the variable values.
   *
   * @retval null                   If the debugger encountered an error or
   *                                the target is running.
   *
   * @throws DebugProxyException    If the debugger is active but the structure
   *                                @p dbg_trace_buffer is not found, not
   *                                initialized or corrupted.
   */
  public LinkedHashMap<String, String> readGlobalVariables()
      throws DebugProxyException {

    if (checkChibiOS())
      return null;

    LinkedHashMap<String, String> map = new LinkedHashMap<String, String>(16);

    try {
        String vt_lasttime = evaluateExpression("(uint32_t)ch0.vtlist.dlist.delta");
        if (vt_lasttime == null)
          return null;
        map.put("vt_lasttime", vt_lasttime);
    } catch (DebugProxyException e1) {
      throw new DebugProxyException("virtual timers list not found on target");
    } catch (Exception e) {
      return null;
    }

    try {
      String vt_systime = evaluateExpression("(uint32_t)ch0.vtlist.systime");
      if (vt_systime == null)
        return null;
      map.put("vt_systime", vt_systime);
    } catch (DebugProxyException e) {}

    try {
        String vt_lasttime = evaluateExpression("(uint32_t)ch0.vtlist.lasttime");
        if (vt_lasttime == null)
          return null;
        map.put("vt_lasttime", vt_lasttime);
    } catch (DebugProxyException e) {}

    try {
      long r_current = evaluateExpressionNumber("(uint32_t)ch0.rlist.current");
      if (r_current != 0) {
        String name;
        try {
          long n = evaluateExpressionNumber("(uint32_t)((struct ch_thread *)" + r_current + ")->name");
          if (n == 0)
            name = "<no name>";
          else
            name = readCString(n, 16);
        } catch (DebugProxyException e) {
          name = "-";
        }
        map.put("r_current", HexUtils.dword2HexString((int)r_current) + " \"" + name + "\"");
      }
      else
        map.put("r_current", "0");
    } catch (DebugProxyException e) {}

    try {
      String r_preempt = evaluateExpression("(uint32_t)ch0.rlist.preempt");
      map.put("r_preempt", r_preempt);
    } catch (DebugProxyException e) {}

    try {
      Long addr = evaluateExpressionNumber("(uint32_t)ch0.dbg.panic_msg");
      if (addr == 0)
        map.put("dbg_panic_msg", "<NULL>");
      else
        map.put("dbg_panic_msg", readCString(addr, 32));
    } catch (DebugProxyException e) {
      map.put("dbg_panic_msg", "<not enabled>");
    }

    try {
      Long isr_cnt = evaluateExpressionNumber("(uint32_t)ch0.dbg.isr_cnt");
      if (isr_cnt == 0)
        map.put("dbg_isr_cnt", "not within ISR");
      else
        map.put("dbg_isr_cnt", "within ISR");
    } catch (DebugProxyException e) {
      map.put("dbg_isr_cnt", "<not enabled>");
    }

    try {
      Long lock_cnt = evaluateExpressionNumber("(uint32_t)ch0.dbg.lock_cnt");
      if (lock_cnt == 0)
        map.put("dbg_lock_cnt", "not within lock");
      else
        map.put("dbg_lock_cnt", "within lock");
    } catch (DebugProxyException e) {
      map.put("dbg_lock_cnt", "<not enabled>");
    }

    return map;
  }

  /**
   * @brief   Return the list of statistics variables.
   * @details The statistics info are fetched from memory by accessing the
   *          kernel_stats structure.
   *
   * @return  A @p LinkedHashMap object whose keys are the variable names,
   *          the value is an @p HashMap statistics counters:
   *          - best
   *          - worst
   *          - cumulative
   *          .
   * @retval null                   If the debugger encountered an error or
   *                                the target is running.
   *
   * @throws DebugProxyException    If the debugger is active but the structure
   *                                @p dbg_trace_buffer is not found, not
   *                                initialized or corrupted.
   */
  public LinkedHashMap<String, HashMap<String, String>> readStatistics()
      throws DebugProxyException {

    if (checkChibiOS())
      return null;

    // Statistics structure.
    String s;
    try {
      s = evaluateExpression("(uint32_t)&ch0.kernel_stats");
      if (s == null)
        return null;
    } catch (DebugProxyException e) {
      throw new DebugProxyException("statistics info structure not found on target");
    } catch (Exception e) {
      return null;
    }

    LinkedHashMap<String, HashMap<String, String>> lhm =
            new LinkedHashMap<String, HashMap<String, String>>(64);

    try {
        long n_irq = evaluateExpressionNumber("(uint32_t)ch0.kernel_stats.n_irq");
        HashMap<String, String> map = new HashMap<String, String>(4);
        map.put("best", "");
        map.put("worst", "");
        map.put("n", Long.toString(n_irq));
        map.put("cumulative", "");
        lhm.put("Number of IRQs", map);
    } catch (DebugProxyException e) {}

    try {
        long n_ctxswc = evaluateExpressionNumber("(uint32_t)ch0.kernel_stats.n_ctxswc");
        HashMap<String, String> map = new HashMap<String, String>(4);
        map.put("best", "");
        map.put("worst", "");
        map.put("n", Long.toString(n_ctxswc));
        map.put("cumulative", "");
        lhm.put("Number of Context Switches", map);
    } catch (DebugProxyException e) {}

    try {
        long m_crit_thd_best = evaluateExpressionNumber("(uint32_t)ch0.kernel_stats.m_crit_thd.best");
        long m_crit_thd_worst = evaluateExpressionNumber("(uint32_t)ch0.kernel_stats.m_crit_thd.worst");
        long m_crit_thd_n = evaluateExpressionNumber("(uint32_t)ch0.kernel_stats.m_crit_thd.n");
        String m_crit_thd_cumulative = evaluateExpression("(uint64_t)ch0.kernel_stats.m_crit_thd.cumulative");
        HashMap<String, String> map = new HashMap<String, String>(4);
        map.put("best", Long.toString(m_crit_thd_best));
        map.put("worst", Long.toString(m_crit_thd_worst));
        map.put("n", Long.toString(m_crit_thd_n));
        map.put("cumulative", m_crit_thd_cumulative);
        lhm.put("Threads Critical Zones", map);
    } catch (DebugProxyException e) {}

    try {
        long m_crit_isr_best = evaluateExpressionNumber("(uint32_t)ch0.kernel_stats.m_crit_isr.best");
        long m_crit_isr_worst = evaluateExpressionNumber("(uint32_t)ch0.kernel_stats.m_crit_isr.worst");
        long m_crit_isr_n = evaluateExpressionNumber("(uint32_t)ch0.kernel_stats.m_crit_isr.n");
        String m_crit_isr_cumulative = evaluateExpression("(uint64_t)ch0.kernel_stats.m_crit_isr.cumulative");
        HashMap<String, String> map = new HashMap<String, String>(4);
        map.put("best", Long.toString(m_crit_isr_best));
        map.put("worst", Long.toString(m_crit_isr_worst));
        map.put("n", Long.toString(m_crit_isr_n));
        map.put("cumulative", m_crit_isr_cumulative);
        lhm.put("ISRs Critical Zones", map);
    } catch (DebugProxyException e) {}

    return lhm;
  }
}
