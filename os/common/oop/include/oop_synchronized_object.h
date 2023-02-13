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
 *
 * @addtogroup  OOP_SYNCHRONIZED_OBJECT
 * @brief       Common ancestor class of all reference-counted, synchronized
 *              objects.
 * @note        This is a generated file, do not edit directly.
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

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

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

/*===========================================================================*/
/* Module class synchronized_object_c                                        */
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
 */

/**
 * @brief       Type of a synchronized object class.
 */
typedef struct synchronized_object synchronized_object_c;

/**
 * @brief       @p synchronized_object_c data as a structure.
 */
struct so_data {
  /**
   * @brief       Embedded synchronization mutex.
   */
  mutex_t                                   mutex;
};

/**
 * @brief       @p synchronized_object_c methods.
 */
#define __so_methods                                                        \
  __ro_methods                                                              \
  /* No methods.*/

/**
 * @brief       @p synchronized_object_c data.
 */
#define __so_data                                                           \
  __ro_data                                                                 \
  struct so_data                            so;

/**
 * @brief       @p synchronized_object_c VMT initializer.
 */
#define __so_vmt_init(ns)                                                   \
  __ro_vmt_init(ns)

/**
 * @brief       @p synchronized_object_c virtual methods table.
 */
struct synchronized_object_vmt {
  __so_methods
};

/**
 * @brief       Structure representing a synchronized object class.
 */
struct synchronized_object {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct synchronized_object_vmt      *vmt;
  __so_data
};

#endif /* OOP_SYNCHRONIZED_OBJECT_H */

/** @} */
