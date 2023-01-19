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
 * @file    oop_referenced_object.h
 * @brief   Generated header.
 *
 * @addtogroup OOP_REFERENCED_OBJECT
 * @brief   Common ancestor class of all reference-counted objects.
 * @details Base class for objects that implement a reference counter and are
 *          disposed when the number of references reaches zero. This class
 *          extends @p base_object_c class.
 * @note    This is a generated file, do not edit directly.
 * @{
 */
 
 #ifndef OOP_REFERENCED_OBJECT_H
 #define OOP_REFERENCED_OBJECT_H

#include "oop_base_object.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a references counter.
 */
typedef unsigned int object_references_t;

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* Module class referenced_object_c                                          */
/*===========================================================================*/

/**
 * @brief   Type of a referenced object class.
 */
typedef struct referenced_object referenced_object_c;

/**
 * @brief   @p referenced_object_c methods as a structure.
 */
struct referenced_object_methods {
  void * (*addref)(void *ip);
  object_references_t (*release)(void *ip);
  /* end methods */
};

/**
 * @brief   @p referenced_object_c data as a structure.
 */
struct referenced_object_data {
  /**
   * @brief   Number of references to the object.
   */
  references                                object_references_t;
};

/**
 * @brief   @p referenced_object_c specific methods.
 */
#define __referenced_object_methods                                         \
  __base_object_methods                                                     \
  struct referenced_object_methods          ro;

/**
 * @brief   @p referenced_object_c specific data.
 */
#define __referenced_object_data                                            \
  __base_object_data                                                        \
  struct referenced_object_data             ro;

/**
 * @brief   @p referenced_object_c virtual methods table.
 */
struct referenced_object_vmt {
  __referenced_object_methods
};

/**
 * @brief   Structure representing a referenced object class.
 */
struct referenced_object {
  /**
   * @brief   Virtual Methods Table.
   */
  const struct referenced_object_vmt        *vmt;
  __referenced_object_data
};

/**
 * @name    Methods implementations (referenced_object_c)
 * @{
 */
/**
 * @brief   Implementation of object creation.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p referenced_object_c structure
 *                              to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
CC_FORCE_INLINE
static inline void *__referenced_object_objinit_impl(void *ip, const void *vmt) {
  referenced_object_c *self = (referenced_object_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __base_object_objinit_impl(self, vmt);

  /* Initialization code.*/
  self->references = (object_references_t)0;

  return self;
}

/**
 * @brief   Implementation of object finalization.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p referenced_object_c structure
 *                              to be disposed.
 */
CC_FORCE_INLINE
static inline void __referenced_object_dispose_impl(void *ip) {
  referenced_object_c *self = (referenced_object_c *)ip;

  __base_object_dispose_impl(self);

  /* No finalization code.*/
  (void)self;
}

/**
 * @brief   Implementation of method @p roAddRef().
 * @note    This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p referenced_object_c structure.
 * @return                      A new reference pointer.
 */
CC_FORCE_INLINE
static inline void * __referenced_object_addref_impl(void *ip) {
  referenced_object_c *self = (referenced_object_c *)ip;

  self->references++;

  osalDbgAssert(self->references != (oop_object_references_t)0, "overflow");

  return self;
}

/**
 * @brief   Implementation of method @p roRelease().
 * @note    This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p referenced_object_c structure.
 * @return                      The value of the reference counter.
 */
CC_FORCE_INLINE
static inline object_references_t __referenced_object_release_impl(void *ip) {
  referenced_object_c *self = (referenced_object_c *)ip;

  osalDbgAssert(self->references > 0U, "zero references");

  if (--self->references == 0U) {
    __referenced_object_dispose_impl(self);
  }

  return self->references;
}
/** @} */

/**
 * @name    Abstract/Virtual methods of (referenced_object_c)
 * @{
 */
/**
 * @brief   New object reference creation.
 * @details The references counter is increased and a new reference pointer is
 *          returned.
 *
 * @param[in,out] ip            Pointer to a @p referenced_object_c structure.
 * @return                      A new reference pointer.
 */
CC_FORCE_INLINE
static inline void * roAddRef(void *ip) {
  referenced_object_c *self = (referenced_object_c *)ip;

  return self->vmt->ro.addref(ip);
}

/**
 * @brief   Release of an object reference.
 * @details The reference counter is decreased, if the counter reaches zero
 *          then the object is disposed.
 *
 * @param[in,out] ip            Pointer to a @p referenced_object_c structure.
 * @return                      The value of the reference counter.
 */
CC_FORCE_INLINE
static inline object_references_t roRelease(void *ip) {
  referenced_object_c *self = (referenced_object_c *)ip;

  return self->vmt->ro.release(ip);
}
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* OOP_REFERENCED_OBJECT_H */

/** @} */
