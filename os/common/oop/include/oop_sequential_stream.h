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
 * @brief   Generated OOP_SEQUENTIAL_STREAM header.
 *
 * @addtogroup OOP_SEQUENTIAL_STREAM
 * @brief   Sequential data streams interface.
 * @note    This class is compatible with legacy HAL @p BaseSequentialStream.
 * @note    This is a generated file, do not edit directly.
 * @{
 */
 
#ifndef OOP_SEQUENTIAL_STREAM_H
#define OOP_SEQUENTIAL_STREAM_H

#include "oop_base_interface.h"

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
/* Module macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Sequential Stream write (implicit form).
 * @details This function writes data from a buffer to a stream.
 *
 * @param[in,out] objp          Pointer to the object implementing the
 *                              interface.
 * @param[in]     bp            Pointer to the data buffer.
 * @param[in]     n             The maximum amount of data to be transferred.
 * @return                      The number of bytes transferred. The returned
 *                              value can be less than the specified number of
 *                              bytes if an end-of-file condition has been met.
 */
#define __stmWrite(objp, bp, n)                                             \
  stmWrite(&(objp)->stm, (bp), (n))

/**
 * @brief   Sequential Stream read (implicit form).
 * @details This function reads data from a stream into a buffer.
 *
 * @param[in,out] objp          Pointer to the object implementing the
 *                              interface.
 * @param[out]    bp            Pointer to the data buffer.
 * @param[in]     n             The maximum amount of data to be transferred.
 * @return                      The number of bytes transferred. The returned
 *                              value can be less than the specified number of
 *                              bytes if an end-of-file condition has been met.
 */
#define __stmRead(objp, bp, n)                                              \
  stmRead(&(objp)->stm, (bp), (n))

/**
 * @brief   Sequential Stream blocking byte write (implicit form).
 * @details This function writes a byte value to a stream. If the stream is not
 *          ready to accept data then the calling thread is suspended.
 *
 * @param[in,out] objp          Pointer to the object implementing the
 *                              interface.
 * @param[in]     b             The byte value to be written to the stream.
 * @return                      The operation status.
 */
#define __stmPut(objp, b)                                                   \
  stmPut(&(objp)->stm, (b))

/**
 * @brief   Sequential Stream blocking byte read (implicit form).
 * @details This function reads a byte value from a stream. If the data is not
 *          available then the calling thread is suspended.
 *
 * @param[in,out] objp          Pointer to the object implementing the
 *                              interface.
 * @return                      A byte value from the stream.
 */
#define __stmGet(objp)                                                      \
  stmGet(&(objp)->stm)

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module interface base_sequential_stream_i                                 */
/*===========================================================================*/

/**
 * @brief   Type of a base sequential stream interface interface.
 */
typedef struct base_sequential_stream base_sequential_stream_i;

/**
 * @brief   @p base_sequential_stream_i methods as a structure.
 */
struct stm_methods {
  size_t (*write)(void *ip, const uint8_t *bp, size_t n);
  size_t (*read)(void *ip, uint8_t *bp, size_t n);
  msg_t (*put)(void *ip, uint8_t b);
  msg_t (*get)(void *ip);
};

/**
 * @brief   @p base_sequential_stream_i methods.
 */
#define __stm_methods                                                       \
  __bi_methods                                                              \
  struct stm_methods                        stm;

/**
 * @brief   @p base_sequential_stream_i VMT initializer.
 */
#define __stm_vmt_init(ns)                                                  \
  __bi_vmt_init(ns)                                                         \
  .stm.write                                = __##ns##_write_impl,          \
  .stm.read                                 = __##ns##_read_impl,           \
  .stm.put                                  = __##ns##_put_impl,            \
  .stm.get                                  = __##ns##_get_impl,

/**
 * @brief   @p base_sequential_stream_i virtual methods table.
 */
struct base_sequential_stream_vmt {
  __stm_methods
};

/**
 * @brief   Structure representing a base sequential stream interface.
 */
struct base_sequential_stream {
  /**
   * @brief   Virtual Methods Table.
   */
  const struct base_sequential_stream_vmt   *vmt;
};

/**
 * @name    Interface methods of @p base_sequential_stream_i
 * @{
 */
/**
 * @brief   Sequential Stream write.
 * @details This function writes data from a buffer to a stream.
 *
 * @param[in,out] ip            Pointer to a @p base_sequential_stream_i, or
 *                              derived, interface.
 * @param[in]     bp            Pointer to the data buffer.
 * @param[in]     n             The maximum amount of data to be transferred.
 * @return                      The number of bytes transferred. The returned
 *                              value can be less than the specified number of
 *                              bytes if an end-of-file condition has been met.
 */
CC_FORCE_INLINE
static inline size_t stmWrite(void *ip, const uint8_t *bp, size_t n) {
  base_sequential_stream_i *self = (base_sequential_stream_i *)ip;
  return self->vmt->stm.write(ip, bp, n);
}

/**
 * @brief   Sequential Stream read.
 * @details This function reads data from a stream into a buffer.
 *
 * @param[in,out] ip            Pointer to a @p base_sequential_stream_i, or
 *                              derived, interface.
 * @param[out]    bp            Pointer to the data buffer.
 * @param[in]     n             The maximum amount of data to be transferred.
 * @return                      The number of bytes transferred. The returned
 *                              value can be less than the specified number of
 *                              bytes if an end-of-file condition has been met.
 */
CC_FORCE_INLINE
static inline size_t stmRead(void *ip, uint8_t *bp, size_t n) {
  base_sequential_stream_i *self = (base_sequential_stream_i *)ip;
  return self->vmt->stm.read(ip, bp, n);
}

/**
 * @brief   Sequential Stream blocking byte write.
 * @details This function writes a byte value to a stream. If the stream is not
 *          ready to accept data then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_sequential_stream_i, or
 *                              derived, interface.
 * @param[in]     b             The byte value to be written to the stream.
 * @return                      The operation status.
 */
CC_FORCE_INLINE
static inline msg_t stmPut(void *ip, uint8_t b) {
  base_sequential_stream_i *self = (base_sequential_stream_i *)ip;
  return self->vmt->stm.put(ip, b);
}

/**
 * @brief   Sequential Stream blocking byte read.
 * @details This function reads a byte value from a stream. If the data is not
 *          available then the calling thread is suspended.
 *
 * @param[in,out] ip            Pointer to a @p base_sequential_stream_i, or
 *                              derived, interface.
 * @return                      A byte value from the stream.
 */
CC_FORCE_INLINE
static inline msg_t stmGet(void *ip) {
  base_sequential_stream_i *self = (base_sequential_stream_i *)ip;
  return self->vmt->stm.get(ip);
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
