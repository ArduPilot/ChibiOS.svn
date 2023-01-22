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
 * @file    oop_sequential_stream.h
 * @brief   Generated header.
 *
 * @addtogroup OOP_SEQUENTIAL_STREAM
 * @brief   Sequential data streams interface.
 * @note    This class is compatible with legacy HAL @p BaseSequentialStream.
 * @note    This is a generated file, do not edit directly.
 * @{
 */
 
#ifndef OOP_SEQUENTIAL_STREAM_H
#define OOP_SEQUENTIAL_STREAM_H

#include "oop_base_object.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @name    Streams return codes
 * @{
 */
#define STM_OK                              MSG_OK
#define STM_TIMEOUT                         MSG_TIMEOUT
#define STM_RESET                           MSG_RESET
/** @} */

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

/*===========================================================================*/
/* Module class base_sequential_stream_c                                     */
/*===========================================================================*/

/**
 * @brief   Type of a base sequential stream interface class.
 */
typedef struct base_sequential_stream base_sequential_stream_c;

/**
 * @brief   @p base_sequential_stream_c methods as a structure.
 */
struct base_sequential_stream_methods {
  size_t (*write)(void *ip, const uint8_t *bp, size_t n);
  size_t (*read)(void *ip, uint8_t *bp, size_t n);
  msg_t (*put)(void *ip, uint8_t b);
  msg_t (*get)(void *ip);
};

/**
 * @brief   @p base_sequential_stream_c specific methods.
 */
#define __base_sequential_stream_methods                                    \
  __base_object_methods                                                     \
  struct base_sequential_stream_methods     bss;

/**
 * @brief   @p base_sequential_stream_c specific data.
 */
#define __base_sequential_stream_data                                       \
  __base_object_data                                                        \
  /* no data */

/**
 * @brief   @p base_sequential_stream_c virtual methods table.
 */
struct base_sequential_stream_vmt {
  __base_sequential_stream_methods
};

/**
 * @brief   Structure representing a base sequential stream interface class.
 */
struct base_sequential_stream {
  /**
   * @brief   Virtual Methods Table.
   */
  const struct base_sequential_stream_vmt   *vmt;
  __base_sequential_stream_data
};

/**
 * @name    Methods implementations (base_sequential_stream_c)
 * @{
 */
/**
 * @brief   Implementation of object creation.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p base_sequential_stream_c
 *                              structure to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
CC_FORCE_INLINE
static inline void *__base_sequential_stream_objinit_impl(void *ip, const void *vmt) {
  base_sequential_stream_c *self = (base_sequential_stream_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __base_object_objinit_impl(self, vmt);

  /* No initialization code.*/

  return self;
}

/**
 * @brief   Implementation of object finalization.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p base_sequential_stream_c
 *                              structure to be disposed.
 */
CC_FORCE_INLINE
static inline void __base_sequential_stream_dispose_impl(void *ip) {
  base_sequential_stream_c *self = (base_sequential_stream_c *)ip;

  __base_object_dispose_impl(self);

  /* No finalization code.*/
  (void)self;
}
/** @} */

/**
 * @name    Virtual methods of (base_sequential_stream_c)
 * @{
 */
/**
 * @brief   Sequential Stream write.
 * @details This function writes data from a buffer to a stream.
 *
 * @param[in,out] ip            Pointer to a @p base_sequential_stream_c
 *                              structure.
 * @param         bp            Pointer to the data buffer.
 * @param         n             The maximum amount of data to be transferred.
 * @return                      The number of bytes transferred. The returned
 *                              value can be less than the specified number of
 *                              bytes if an end-of-file condition has been met.
 */
CC_FORCE_INLINE
static inline size_t streamWrite(void *ip, const uint8_t *bp, size_t n) {
  base_sequential_stream_c *self = (base_sequential_stream_c *)ip;

  return self->vmt->bss.write(ip, bp, n);
}

/**
 * @brief   Sequential Stream read.
 * @details This function reads data from a stream into a buffer.
 *
 * @param[in,out] ip            Pointer to a @p base_sequential_stream_c
 *                              structure.
 * @param         bp            Pointer to the data buffer.
 * @param         n             The maximum amount of data to be transferred.
 * @return                      The number of bytes transferred. The returned
 *                              value can be less than the specified number of
 *                              bytes if an end-of-file condition has been met.
 */
CC_FORCE_INLINE
static inline size_t streamRead(void *ip, uint8_t *bp, size_t n) {
  base_sequential_stream_c *self = (base_sequential_stream_c *)ip;

  return self->vmt->bss.read(ip, bp, n);
}

/**
 * @brief   Sequential Stream blocking byte write.
 * @details This function writes a byte value to a channel. If the channel is
 *          not ready to accept data then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_sequential_stream_c
 *                              structure.
 * @param         b             The byte value to be written to the channel.
 * @return                      The operation status.
 */
CC_FORCE_INLINE
static inline msg_t streamPut(void *ip, uint8_t b) {
  base_sequential_stream_c *self = (base_sequential_stream_c *)ip;

  return self->vmt->bss.put(ip, b);
}

/**
 * @brief   Sequential Stream blocking byte read.
 * @details This function reads a byte value from a channel. If the data is not
 *          available then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_sequential_stream_c
 *                              structure.
 * @return                      A byte value from the queue.
 */
CC_FORCE_INLINE
static inline msg_t streamGet(void *ip) {
  base_sequential_stream_c *self = (base_sequential_stream_c *)ip;

  return self->vmt->bss.get(ip);
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

#endif /* OOP_SEQUENTIAL_STREAM_H */

/** @} */
