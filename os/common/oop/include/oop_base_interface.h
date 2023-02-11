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
 * @file        oop_base_interface.h
 * @brief       Generated Base Interface header.
 *
 * @addtogroup  OOP_BASE_INTERFACE
 * @brief       Common interfaces ancestor.
 * @note        This is a generated file, do not edit directly.
 * @{
 */
 
#ifndef OOP_BASE_INTERFACE_H
#define OOP_BASE_INTERFACE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "ccportab.h"

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
 * @brief       Returns an object pointer starting from an interface pointer.
 * @details     Because multiple inheritance, an object can implement multiple
 *              interfaces.
 *              This macro returns the pointer to the base object starting from
 *              a pointer to any of its composing classes or interfaces. This
 *              is done by using the @p offsetof() macro in @p stdlib.h.
 *
 * @param         c             Class type implementing the interface.
 * @param         ifname        Name of the interface field within the class
 *                              structure.
 * @param[in]     ip            Pointer to the interface field within the class
 *                              structure.
 * @return                      A pointer to an object of type @p c
 *                              implementing the interface @p ifname.
 *
 * @api
 */
#define oopGetInstance(c, ifname, ip)                                       \
  (c *)(((size_t)(ip)) - (size_t)offsetof(c, ifname))

/**
 * @brief       Initialization of an interface structure.
 * @details     An interface structure contains only a VMT pointer and no data,
 *              the purpose of this macro is VMT initialization.
 *
 * @param[out]    ip            Pointer to the interface structure to be
 *                              initialized.
 * @param[in]     vmtp          VMT pointer to be assigned to the interface
 *                              structure.
 *
 * @api
 */
#define oopInterfaceObjectInit(ip, vmtp)                                    \
  do {                                                                      \
    (ip)->vmt = (vmtp);                                                     \
  } while (false)

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module interface base_interface_i                                         */
/*===========================================================================*/

/**
 * @interface   base_interface_i
 *
 * @brief       Common interfaces ancestor.
 * @details     There are no methods in this interface. This interface is just
 *              meant to be the common ancestor of all interfaces used in
 *              ChibiOS.
 * @note        The interface name space is <tt>bi</tt>, access to an
 *              implemented interface is done using:
 *              <tt>&<objp>-><classnamespace>.bi</tt>.
 */

/**
 * @brief       Type of a base interface interface.
 */
typedef struct base_interface base_interface_i;

/**
 * @brief       @p base_interface_i methods.
 */
#define __bi_methods                                                        \
  /* No methods.*/

/**
 * @brief       @p base_interface_i VMT initializer.
 */
#define __bi_vmt_init(ns)                                                   \
  /* No methods.*/

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
