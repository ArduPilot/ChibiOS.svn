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
 * @file        oop_base_object.h
 * @brief       Generated Base Object header.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  OOP_BASE_OBJECT
 * @brief       Common ancestor abstract class.
 * @{
 */

#ifndef OOP_BASE_OBJECT_H
#define OOP_BASE_OBJECT_H

#if (defined(OOP_USE_CHIBIOS)) || defined (__DOXYGEN__)
#include "ch.h"
#elif defined(OOP_USE_NOTHING)
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#else
#include "osal.h"
#endif

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

/**
 * @brief       Returns an object pointer starting from a pointer to a class
 *              member.
 *
 * @param         c             Class type name.
 * @param         m             Class member field name.
 * @param[in]     p             Class member field pointer.
 * @return                      A pointer to an object of type @p c containing
 *                              the field @p m.
 *
 * @api
 */
#define oopGetOwner(c, m, p)                                                \
  (c *)(((size_t)(p)) - (size_t)offsetof(c, m))

/**
 * @brief       Returns a pointer to one of the implemented interfaces.
 * @note        The interface pointer is returned as a <tt>void *</tt> in order
 *              to be directly usable as any of the interface's ancestors
 *              pointers.
 *
 * @param[in]     ip            Pointer to the class instance.
 * @param         ifns          Implemented interface namespace.
 * @param         cns           Implementing class namespace.
 * @return                      A void pointer to the interface within the
 *                              class instance.
 *
 * @api
 */
#define boGetIf(ip, ifns, cns)                                              \
  (void *)(&(ip)->cns.ifns)

#if (defined(OOP_USE_CHIBIOS)) || defined (__DOXYGEN__)
/**
 * @brief       Condition assertion.
 *
 * @param         c             Condition to be proven true.
 * @param         r             Remark associated to the assertion.
 */
#define oopAssert(c, r)                                                     \
  chDbgAssert(c, r)

#elif defined(OOP_USE_NOTHING)
#define oopAssert(c, r)                                                     \
  do {                                                                      \
    (void)c;                                                                \
    (void)r;                                                                \
  } while (false)

#else
#define oopAssert(c, r)                                                     \
  osalDbgAssert(c, r)
#endif /* defined(OOP_USE_CHIBIOS) */

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/**
 * @class       base_object_c
 *
 * @brief       Common ancestor abstract class.
 * @details     This abstract class is the common ancestor of all classes used
 *              in ChibiOS. This class just defines the position of the VMT
 *              pointer inside the structure.
 * @note        The class namespace is <tt>bo</tt>, access to class fields is
 *              done using: <tt><objp>->bo.<fieldname></tt><br>Note that fields
 *              of ancestor classes are in their own namespace in order to
 *              avoid field naming conflicts.
 *
 * @name        Class @p base_object_c structures
 * @{
 */

/**
 * @brief       Type of a base object class.
 */
typedef struct base_object base_object_c;

/**
 * @brief       Class @p base_object_c methods as a structure.
 */
struct bo_methods {
  void (*dispose)(void *ip);
};

/**
 * @brief       Class @p base_object_c methods.
 */
#define __bo_methods                                                        \
  struct bo_methods         bo;

/**
 * @brief       Class @p base_object_c data.
 */
#define __bo_data                                                           \
  /* No data.*/

/**
 * @brief       Class @p base_object_c VMT initializer.
 */
#define __bo_vmt_init(ns)                                                   \
  .bo.dispose                               = __##ns##_bo_dispose_impl,

/**
 * @brief       Class @p base_object_c virtual methods table.
 */
struct base_object_vmt {
  __bo_methods
};

/**
 * @brief       Structure representing a base object class.
 */
struct base_object {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct base_object_vmt *vmt;
  __bo_data
};
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  /* Methods of base_object_c.*/
  void *__bo_objinit_impl(void *ip, const void *vmt);
  void __bo_dispose_impl(void *ip);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

/**
 * @name        Virtual methods of base_object_c
 * @{
 */
/**
 * @memberof    base_object_c
 * @public
 *
 * @brief       Object finalization.
 *
 * @param[in,out] ip            Pointer to a @p base_object_c instance.
 *
 * @dispose
 */
CC_FORCE_INLINE
static inline void boDispose(void *ip) {
  base_object_c *self = (base_object_c *)ip;

  self->vmt->bo.dispose(ip);
}
/** @} */

/**
 * @name        Inline methods of base_object_c
 * @{
 */
/**
 * @memberof    base_object_c
 * @public
 *
 * @brief       Conditional object finalization.
 * @details     The object is disposed if the passed reference is different
 *              from @p NULL.
 *
 * @param[in,out] ip            Pointer to a @p base_object_c instance.
 */
CC_FORCE_INLINE
static inline void boFree(void *ip) {
  base_object_c *self = (base_object_c *)ip;

  if (self != NULL) {
    boDispose(self);
  }
}
/** @} */

#endif /* OOP_BASE_OBJECT_H */

/** @} */
