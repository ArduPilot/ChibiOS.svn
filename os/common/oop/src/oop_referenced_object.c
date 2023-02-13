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
 * @file        oop_referenced_object.c
 * @brief       Generated Referenced Object source.
 *
 * @addtogroup  OOP_REFERENCED_OBJECT
 * @{
 */

#include "oop_referenced_object.h"

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
/* Module class "referenced_object_c" methods.                               */
/*===========================================================================*/

/**
 * @name        Virtual methods implementations of referenced_object_c
 * @{
 */
/**
 * @memberof    referenced_object_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p referenced_object_c instance to
 *                              be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
void *__ro_objinit_impl(void *ip, const void *vmt) {
  referenced_object_c *self = (referenced_object_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __bo_objinit_impl(self, vmt);

  /* Initialization code.*/
  self->ro.references = (object_references_t)0;

  return self;
}

/**
 * @memberof    referenced_object_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p referenced_object_c instance to
 *                              be disposed.
 */
void __ro_dispose_impl(void *ip) {
  referenced_object_c *self = (referenced_object_c *)ip;

  __bo_dispose_impl(self);

  /* No finalization code.*/
  (void)self;
}

/**
 * @brief       Implementation of method @p roAddRef().
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p referenced_object_c instance.
 * @return                      A new reference pointer.
 */
void * __ro_addref_impl(void *ip) {
  referenced_object_c *self = (referenced_object_c *)ip;
  self->ro.references++;

  osalDbgAssert(self->ro.references != (object_references_t)0, "overflow");

  return self;
}

/**
 * @brief       Implementation of method @p roRelease().
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p referenced_object_c instance.
 * @return                      The value of the reference counter.
 */
object_references_t __ro_release_impl(void *ip) {
  referenced_object_c *self = (referenced_object_c *)ip;
  osalDbgAssert(self->ro.references > 0U, "zero references");

  if (--self->ro.references == 0U) {
    __ro_dispose_impl(self);
  }

  return self->ro.references;
}
/** @} */

/** @} */