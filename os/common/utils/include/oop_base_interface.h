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
 * @file    oop_base_interface.h
 * @brief   Generated OOP_BASE_INTERFACE header.
 *
 * @addtogroup OOP_BASE_INTERFACE
 * @brief   Common interfaces ancestor.
 * @details There are no methods in this interface. This interface is just
 *          meant to be the common ancestor of all interfaces used in ChibiOS.
 * @note    This is a generated file, do not edit directly.
 * @{
 */
 
#ifndef OOP_BASE_INTERFACE_H
#define OOP_BASE_INTERFACE_H

#include <stddef.h>

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
 * @brief   Returns an object pointer starting from an interface pointer.
 * @details Because multiple inheritance, an object can implement multiple
 *          interfaces.
 *          This macro returns the pointer to the base object starting from a
 *          pointer to any of its composing classes or interfaces. This is done
 *          by using the @p offsetof() macro in @p stdlib.h.
 *
 * @param         c             Class type implementing the interface.
 * @param         ifname        Name of the interface field within the class
 *                              structure.
 * @param         ip            Pointer to the interface field within the class
 *                              structure.
 * @return                      A pointer to an object of type @p c
 *                              implementing the interface @p ifname.
 */
#define oopGetInstance(c, ifname, ip)                                       \
  (c)(((size_t)(ip)) - (size_t)offsetof(c, c.ifname))                       

/*===========================================================================*/
/* Module interface base_interface_i                                         */
/*===========================================================================*/

/**
 * @brief   Type of a base interface interface.
 */
typedef struct base_interface base_interface_i;

/**
 * @brief   @p base_interface_i methods.
 */
#define __base_interface_methods                                            \
  /* This field represents the offset between the current object
     and the container object.*/                                            \
  size_t                                    instance_offset;                \
  /* no methods */

/**
 * @brief   @p base_interface_i VMT initializer.
 */
#define __base_interface_vmt_init(offset, ns)                               \
  .instance_offset                          = (offset)

/**
 * @brief   @p base_interface_i virtual methods table.
 */
struct base_interface_vmt {
  __base_interface_methods
};

/**
 * @brief   Structure representing a base interface.
 */
struct base_interface {
  /**
   * @brief   Virtual Methods Table.
   */
  const struct base_interface_vmt           *vmt;
};

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

#endif /* OOP_BASE_INTERFACE_H */

/** @} */
