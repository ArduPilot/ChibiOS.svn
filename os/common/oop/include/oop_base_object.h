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
 * @file    oop_base_object.h
 * @brief   Generated OOP_BASE_OBJECT header.
 *
 * @addtogroup OOP_BASE_OBJECT
 * @brief   Common ancestor abstract class.
 * @details This abstract class is the common ancestor of all classes used in
 *          ChibiOS. This class just defines the position of the VMT pointer
 *          inside the structure.
 * @note    This is a generated file, do not edit directly.
 * @{
 */
 
#ifndef OOP_BASE_OBJECT_H
#define OOP_BASE_OBJECT_H

#include "osal.h"

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
/* Module class base_object_c                                                */
/*===========================================================================*/

/**
 * @brief   Type of a base object class.
 */
typedef struct base_object base_object_c;

/**
 * @brief   @p base_object_c methods.
 */
#define __base_object_methods                                               \
  /* No methods.*/

/**
 * @brief   @p base_object_c data.
 */
#define __base_object_data                                                  \
  /* No data.*/

/**
 * @brief   @p base_object_c VMT initializer.
 */
#define __base_object_vmt_init(ns)                                          \
  /* No methods.*/

/**
 * @brief   @p base_object_c virtual methods table.
 */
struct base_object_vmt {
  __base_object_methods
};

/**
 * @brief   Structure representing a base object class.
 */
struct base_object {
  /**
   * @brief   Virtual Methods Table.
   */
  const struct base_object_vmt              *vmt;
  __base_object_data
};

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  /* Methods of base_object_c.*/
  void *__base_object_objinit_impl(void *ip, const void *vmt);
  void __base_object_dispose_impl(void *ip);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* OOP_BASE_OBJECT_H */

/** @} */
