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
 * @file        hal_buffered_serial.h
 * @brief       Generated Buffered Serial Driver header.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  HAL_BUFFERED_SERIAL
 * @brief       Common ancestor of drivers based on circular I/O buffers.
 * @details     This class implements a channel interface and links it to two
 *              circular I/O queues.
 * @{
 */
 
#ifndef HAL_BUFFERED_SERIAL_H
#define HAL_BUFFERED_SERIAL_H

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
 * @class       hal_buffered_serial_c
 * @extends     base_driver_c
 * @implements  asynchronous_channel_i
 *
 * @brief       Ancestor class of serial buffered drivers.
 * @note        The class namespace is <tt>bs</tt>, access to class fields is
 *              done using: <tt><objp>->bs.<fieldname></tt><br>Note that fields
 *              of ancestor classes are in their own namespace in order to
 *              avoid field naming conflicts.
 *
 * @name        Class @p hal_buffered_serial_c structures
 * @{
 */

/**
 * @brief       Type of a HAL buffered serial driver class.
 */
typedef struct hal_buffered_serial hal_buffered_serial_c;

/**
 * @brief       Class @p hal_buffered_serial_c data as a structure.
 */
struct bs_data {
  /**
   * @brief       Channel interface.
   */
  asynchronous_channel_i    chn;
  /**
   * @brief       Input queue.
   */
  input_queue_t             iqueue;
  /**
   * @brief       Output queue.
   */
  output_queue_t            oqueue;
  /**
   * @brief       I/O condition event source.
   */
  event_source_t            event;
};

/**
 * @brief       Class @p hal_buffered_serial_c methods.
 */
#define __bs_methods                                                        \
  __drv_methods                                                             \
  /* No methods.*/

/**
 * @brief       Class @p hal_buffered_serial_c data.
 */
#define __bs_data                                                           \
  __drv_data                                                                \
  struct bs_data            bs;

/**
 * @brief       Class @p hal_buffered_serial_c VMT initializer.
 */
#define __bs_vmt_init(ns)                                                   \
  __drv_vmt_init(ns)

/**
 * @brief       Class @p hal_buffered_serial_c virtual methods table.
 */
struct hal_buffered_serial_vmt {
  __bs_methods
};

/**
 * @brief       Structure representing a HAL buffered serial driver class.
 */
struct hal_buffered_serial {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct hal_buffered_serial_vmt *vmt;
  __bs_data
};

/**
 * @memberof    hal_buffered_serial_c
 *
 * @brief       Access macro for hal_buffered_serial_c interfaces.
 *
 * @param[in]     ip            Pointer to the class instance.
 * @param         ifns          Implemented interface namespace.
 * @return                      A void pointer to the interface within the
 *                              class instance.
 *
 * @api
 */
#define bsGetIf(ip, ifns)                                                   \
  boGetIf(ip, ifns, bs)
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  /* Methods of hal_buffered_serial_c.*/
  void *__bs_objinit_impl(void *ip, const void *vmt, uint8_t *ib,
                          size_t ibsize, qnotify_t inotify, void *iarg,
                          uint8_t *ob, size_t obsize, qnotify_t onotify,
                          void *oarg);
  void __bs_dispose_impl(void *ip);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* HAL_BUFFERED_SERIAL_H */

/** @} */
