/*
    ChibiOS - Copyright (C) 2006..2023 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file        oop_synchronized_object.c
 * @brief       Generated Synchronized Object source.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  OOP_SYNCHRONIZED_OBJECT
 * @{
 */

#include "oop_synchronized_object.h"

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module local macros.                                                      */
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

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module class "synchronized_object_c" methods.                             */
/*===========================================================================*/

/**
 * @name        Virtual methods implementations of synchronized_object_c
 * @{
 */
/**
 * @memberof    synchronized_object_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p synchronized_object_c instance
 *                              to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
void *__so_objinit_impl(void *ip, const void *vmt) {
  synchronized_object_c *self = (synchronized_object_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __ro_objinit_impl(self, vmt);

  /* Initialization code.*/
  osalMutexObjectInit(&self->mutex);

  return self;
}

/**
 * @memberof    synchronized_object_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p synchronized_object_c instance
 *                              to be disposed.
 */
void __so_dispose_impl(void *ip) {
  synchronized_object_c *self = (synchronized_object_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __ro_dispose_impl(self);
}
/** @} */

/**
 * @name        Regular methods of synchronized_object_c
 * @{
 */
/**
 * @memberof    synchronized_object_c
 * @public
 *
 * @brief       Object lock.
 *
 * @param[in,out] ip            Pointer to a @p synchronized_object_c instance.
 */
void soLock(void *ip) {
  synchronized_object_c *self = (synchronized_object_c *)ip;

  osalMutexLock(&self->mutex);
}

/**
 * @memberof    synchronized_object_c
 * @public
 *
 * @brief       Object unlock.
 *
 * @param[in,out] ip            Pointer to a @p synchronized_object_c instance.
 */
void soUnlock(void *ip) {
  synchronized_object_c *self = (synchronized_object_c *)ip;

  osalMutexUnlock(&self->mutex);
}
/** @} */

/** @} */
