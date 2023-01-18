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
 * @file    generator_test.h
 * @brief   Generated header.
 *
 * @addtogroup GENERATOR_TEST
 * @brief   Code generator test module.
 * @details This is not real code, just the output of a test for the modules
 *          generator tool.
 * @note    This is a generated file, do not edit directly.
 * @{
 */
 
 #ifndef GENERATOR_TEST_H
 #define GENERATOR_TEST_H

#include <stddef.h>
#include "hal.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @name    Grouped defines without comments
 * @{
 */
#define TEST_DEF1                           0U
#define TEST_DEF2                           1U
#define TEST_DEF3                           2U
#define TEST_DEF4                           3U
#define TEST_DEF5                           4U
/** @} */

/**
 * @name    Grouped defines with comments
 * @{
 */
/**
 * @brief   This is a comment.
 * @details This is a longer comment.
 */
#define TEST_DEF1_DOC                       0U
/**
 * @brief   This is a comment.
 * @note    This is a note.
 */
#define TEST_DEF2_DOC                       0U
/** @} */

/**
 * @brief   This is a comment.
 */
#define TEST_DEF1_NOGROUP                   0U
/**
 * @brief   This is a comment.
 */
#define TEST_DEF2_NOGROUP                   1U

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   This is a comment.
 * @details This is a longer comment.
 */
#if !defined(TEST_CFG_OPTION1) || defined(__DOXYGEN__)
#define TEST_CFG_OPTION1                    TRUE
#endif

/**
 * @brief   This is a comment.
 * @note    This is a note.
 */
#if !defined(TEST_CFG_OPTION2) || defined(__DOXYGEN__)
#define TEST_CFG_OPTION2                    FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of an unsigned int.
 */
typedef unsigned int test_state_t;

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Test macro.
 * @details This is a long comment.
 *
 * @param         a             Parameter 1.
 * @param         b             Parameter 2.
 * @return                      A value of unspecified type.
 */
#define test_macro1(a, b)                                                   \
  ((a) + (b))                                                               

/*===========================================================================*/
/* Module class test_interface_c                                             */
/*===========================================================================*/

/**
 * @brief   Type of a test interface class.
 */
typedef struct test_interface test_interface_c;

/**
 * @brief   @p test_interface_c specific methods.
 */
#define __test_interface_methods                                            \
  __base_object_methods                                                     \
  int (*start)(void *ip);                                                   \
  int (*stop)(void *ip);                                                    \
  /* end methods */

/**
 * @brief   @p test_interface_c specific data.
 */
#define __test_interface_data                                               \
  __base_object_data                                                        \
  /* end data */

/**
 * @brief   @p test_interface_c virtual methods table.
 */
struct test_interface_vmt {
  __test_interface_methods
};

/**
 * @brief   Structure representing a test interface class.
 */
struct test_interface {
  /**
   * @brief   Virtual Methods Table.
   */
  const struct test_interface_vmt           *vmt;
  __test_interface_data
};

/**
 * @name    Methods implementations (test_interface_c)
 * @{
 */
/**
 * @brief   Implementation of object creation.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p test_interface_c structure to
 *                              be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
CC_FORCE_INLINE
static inline void *__test_interface_objinit_impl(void *ip, const void *vmt) {
  test_interface_c *self = (test_interface_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __base_object_objinit_impl(self, vmt);

  /* No initialization code.*/

  return self;
}

/**
 * @brief   Implementation of object finalization.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p test_interface_c structure to
 *                              be disposed.
 */
CC_FORCE_INLINE
static inline void __test_interface_dispose_impl(void *ip) {
  test_interface_c *self = (test_interface_c *)ip;

  __base_object_dispose_impl(self);

  /* No finalization code.*/
  (void)self;
}
/** @} */

/**
 * @name    Abstract/Virtual methods of (test_interface_c)
 * @{
 */
/**
 * @brief   Low level driver start.
 *
 * @param[in,out] ip            Pointer to a @p test_interface_c structure.
 * @return                      The operation status.
 */
CC_FORCE_INLINE
static inline int testStart(void *ip) {
  test_interface_c *self = (test_interface_c *)ip;

  return self->vmt->start(ip);
}

/**
 * @brief   Low level driver start.
 *
 * @param[in,out] ip            Pointer to a @p test_interface_c structure.
 * @return                      The operation status.
 */
CC_FORCE_INLINE
static inline int testStop(void *ip) {
  test_interface_c *self = (test_interface_c *)ip;

  return self->vmt->stop(ip);
}
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  /* Methods of test_interface_c.*/
  int testOpen(const void *ip);
  void testClose(const void *ip);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* GENERATOR_TEST_H */

/** @} */
