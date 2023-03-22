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
 * @file        oop_referenced_object.h
 * @brief       Generated Referenced Object header.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  OOP_REFERENCED_OBJECT
 * @brief       Common ancestor class of all reference-counted objects.
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
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief       Type of a references counter.
 */
typedef unsigned int object_references_t;

/**
 * @class       referenced_object_c
 * @extends     base_object_c
 *
 * @brief       Common ancestor class of all reference-counted objects.
 * @details     Base class for objects that implement a reference counter and
 *              are disposed when the number of references reaches zero. This
 *              class extends @p base_object_c class.
 * @note        The class namespace is <tt>ro</tt>, access to class fields is
 *              done using: <tt><objp>->ro.<fieldname></tt><br>Note that fields
 *              of ancestor classes are in their own namespace in order to
 *              avoid field naming conflicts.
 *
 * @name        Class @p referenced_object_c structures
 * @{
 */

/**
 * @brief       Type of a referenced object class.
 */
typedef struct referenced_object referenced_object_c;

/**
 * @brief       Class @p referenced_object_c methods as a structure.
 */
struct referenced_object_methods {
  void * (*addref)(void *ip);
  object_references_t (*release)(void *ip);
};

/**
 * @brief       Class @p referenced_object_c data as a structure.
 */
struct referenced_object_data {
  /**
   * @brief       Number of references to the object.
   */
  object_references_t       references;
};

/**
 * @brief       Class @p referenced_object_c methods.
 */
#define __referenced_object_methods                                         \
  __base_object_methods                                                     \
  struct referenced_object_methods ro;

/**
 * @brief       Class @p referenced_object_c data.
 */
#define __referenced_object_data                                            \
  __base_object_data                                                        \
  struct referenced_object_data ro;

/**
 * @brief       Class @p referenced_object_c VMT initializer.
 */
#define __referenced_object_vmt_init(ns)                                    \
  __base_object_vmt_init(ns)                                                \
  .ro.addref                                = __##ns##_ro_addref_impl,      \
  .ro.release                               = __##ns##_ro_release_impl,

/**
 * @brief       Class @p referenced_object_c virtual methods table.
 */
struct referenced_object_vmt {
  __referenced_object_methods
};

/**
 * @brief       Structure representing a referenced object class.
 */
struct referenced_object {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct referenced_object_vmt *vmt;
  __referenced_object_data
};
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  /* Methods of referenced_object_c.*/
  void *__ro_objinit_impl(void *ip, const void *vmt);
  void __ro_dispose_impl(void *ip);
  void *__ro_addref_impl(void *ip);
  object_references_t __ro_release_impl(void *ip);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

/**
 * @name        Virtual methods of referenced_object_c
 * @{
 */
/**
 * @memberof    referenced_object_c
 * @public
 *
 * @brief       New object reference creation.
 * @details     The references counter is increased and a new reference pointer
 *              is returned.
 *
 * @param[in,out] ip            Pointer to a @p referenced_object_c instance.
 * @return                      A new reference pointer.
 */
CC_FORCE_INLINE
static inline void *roAddRef(void *ip) {
  referenced_object_c *self = (referenced_object_c *)ip;

  return self->vmt->ro.addref(ip);
}

/**
 * @memberof    referenced_object_c
 * @public
 *
 * @brief       Release of an object reference.
 * @details     The reference counter is decreased, if the counter reaches zero
 *              then the object is disposed.
 *
 * @param[in,out] ip            Pointer to a @p referenced_object_c instance.
 * @return                      The value of the reference counter.
 */
CC_FORCE_INLINE
static inline object_references_t roRelease(void *ip) {
  referenced_object_c *self = (referenced_object_c *)ip;

  return self->vmt->ro.release(ip);
}
/** @} */

#endif /* OOP_REFERENCED_OBJECT_H */

/** @} */
