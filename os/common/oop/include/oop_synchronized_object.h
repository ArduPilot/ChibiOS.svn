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
 * @file        oop_synchronized_object.h
 * @brief       Generated Synchronized Object header.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  OOP_SYNCHRONIZED_OBJECT
 * @brief       Common ancestor class of all reference-counted, synchronized
 *              objects.
 * @{
 */

#ifndef OOP_SYNCHRONIZED_OBJECT_H
#define OOP_SYNCHRONIZED_OBJECT_H

#include "oop_referenced_object.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/


#if defined(OOP_USE_NOTHING)
#error "OOP_USE_NOTHING specified, not compatible"
#endif
/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/**
 * @class       synchronized_object_c
 * @extends     referenced_object_c
 *
 * @brief       Common ancestor class of all reference-counted, synchronized
 *              objects.
 * @details     Base class for objects that require a synchronization
 *              mechanism. This class extends @p referenced_object_c class.
 * @note        The class namespace is <tt>so</tt>, access to class fields is
 *              done using: <tt><objp>->so.<fieldname></tt><br>Note that fields
 *              of ancestor classes are in their own namespace in order to
 *              avoid field naming conflicts.
 *
 * @name        Class @p synchronized_object_c structures
 * @{
 */

/**
 * @brief       Type of a synchronized object class.
 */
typedef struct synchronized_object synchronized_object_c;

/**
 * @brief       Class @p synchronized_object_c data as a structure.
 */
struct synchronized_object_data {
  /**
   * @brief       Embedded synchronization mutex.
   */
  mutex_t                   mutex;
};

/**
 * @brief       Class @p synchronized_object_c methods.
 */
#define __synchronized_object_methods                                       \
  __referenced_object_methods                                               \
  /* No methods.*/

/**
 * @brief       Class @p synchronized_object_c data.
 */
#define __synchronized_object_data                                          \
  __referenced_object_data                                                  \
  struct synchronized_object_data so;

/**
 * @brief       Class @p synchronized_object_c VMT initializer.
 */
#define __synchronized_object_vmt_init(ns)                                  \
  __referenced_object_vmt_init(ns)

/**
 * @brief       Class @p synchronized_object_c virtual methods table.
 */
struct synchronized_object_vmt {
  __synchronized_object_methods
};

/**
 * @brief       Structure representing a synchronized object class.
 */
struct synchronized_object {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct synchronized_object_vmt *vmt;
  __synchronized_object_data
};
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  /* Methods of synchronized_object_c.*/
  void *__so_objinit_impl(void *ip, const void *vmt);
  void __so_dispose_impl(void *ip);
  void soLock(void *ip);
  void soUnlock(void *ip);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* OOP_SYNCHRONIZED_OBJECT_H */

/** @} */
