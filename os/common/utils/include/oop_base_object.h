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
 * @brief   Generated header.
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
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Returns the object instance pointer starting from an interface
 *          pointer.
 * @details Because multiple inheritance, an object can be composed by multiple
 *          interfaces and/or classes (its ancestors).<br> This function
 *          returns the pointer to the base object starting from a pointer to
 *          any of its composing classes or interfaces. This is done by
 *          leveraging the offset field into each VMT table.
 *
 * @param         c             The class type of the object.
 * @param         p             A pointer to one of the object composing
 *                              classes or interfaces.
 * @return                      A pointer to an object of type @p c
 *                              implementing the interface/class @p p.
 */
#define oopGetInstance(c, p)                                                \
  (c)(((size_t)(ip)) - (**(size_t **)(p)))                                  

/*===========================================================================*/
/* Module class base_object_c                                                */
/*===========================================================================*/

/**
 * @brief   Type of a base object class.
 */
typedef struct base_object base_object_c;

/**
 * @brief   @p base_object_c specific methods.
 */
#define __base_object_methods                                               \
  /* This field represents the offset between the current object
     and the container object.*/                                            \
  size_t                                    instance_offset;                \
  /* no methods */

/**
 * @brief   @p base_object_c specific data.
 */
#define __base_object_data                                                  \
  /* no data */

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

/**
 * @name    Methods implementations (base_object_c)
 * @{
 */
/**
 * @brief   Implementation of object creation.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p base_object_c structure to be
 *                              initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
CC_FORCE_INLINE
static inline void *__base_object_objinit_impl(void *ip, const void *vmt) {
  base_object_c *self = (base_object_c *)ip;

  /* This is a root class, initializing the VMT pointer here.*/
  self->vmt = (struct base_object_vmt *)vmt;

  /* No initialization code.*/

  return self;
}

/**
 * @brief   Implementation of object finalization.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p base_object_c structure to be
 *                              disposed.
 */
CC_FORCE_INLINE
static inline void __base_object_dispose_impl(void *ip) {
  base_object_c *self = (base_object_c *)ip;

  /* No finalization code.*/
  (void)self;
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

#endif /* OOP_BASE_OBJECT_H */

/** @} */
