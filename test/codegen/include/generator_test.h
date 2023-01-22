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
#define TEST_DEF(n)                         ((n) << 5)
#define TEST_DEF1                           TEST_DEF(0U)
#define TEST_DEF2                           TEST_DEF(1U)
#define TEST_DEF3                           TEST_DEF(2U)
#define TEST_DEF4                           TEST_DEF(3U)
#if (defined(EXTRA_DEFINITIONS)) || defined (__DOXYGEN__)
#define TEST_DEF5                           TEST_DEF(4U)
#define TEST_DEF6                           TEST_DEF(5U)
#endif /* defined(EXTRA_DEFINITIONS) */
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

/* Checks on TEST_CFG_OPTION1 configuration.*/
#if (TEST_CFG_OPTION1 != FALSE) && (TEST_CFG_OPTION1 != TRUE)
#error "invalid TEST_CFG_OPTION1 value"
#endif

/* Checks on TEST_CFG_OPTION2 configuration.*/
#if (TEST_CFG_OPTION2 != FALSE) && (TEST_CFG_OPTION2 != TRUE)
#error "custom message for TEST_CFG_OPTION2"
#endif

#if (TEST_CFG_OPTION1 = TRUE) || defined (__DOXYGEN__)
/**
 * @brief   Option 1 is enabled.
 */
#define TEST_COND_DEF                       1U
#endif /* TEST_CFG_OPTION1 = TRUE */

#if (TEST_CFG_OPTION1 = FALSE) || defined (__DOXYGEN__)
/**
 * @brief   Option 1 is disabled.
 */
#define TEST_COND_DEF                       2U
#endif /* TEST_CFG_OPTION1 = FALSE */

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
/* Module class test_class_c                                                 */
/*===========================================================================*/

/**
 * @brief   Type of a test class class.
 */
typedef struct test_class test_class_c;

/**
 * @brief   @p test_class_c methods as a structure.
 */
struct test_class_methods {
  int (*start)(void *ip);
  int (*stop)(void *ip);
#if (TEST_CFG_OPTION2 == TRUE) || defined (__DOXYGEN__)
  void (*reinit)(void *ip);
#endif /* TEST_CFG_OPTION2 == TRUE */
};

/**
 * @brief   @p test_class_c data as a structure.
 */
struct test_class_data {
  /**
   * @brief   A counter variable.
   */
  int                                       counter;
#if (TEST_CFG_OPTION2 == TRUE) || defined (__DOXYGEN__)
  /**
   * @brief   An optional chickens variable.
   */
  unsigned int                              chickens;
#endif /* TEST_CFG_OPTION2 == TRUE */
};

/**
 * @brief   @p test_class_c specific methods.
 */
#define __test_class_methods                                                \
  __base_object_methods                                                     \
  struct test_class_methods                 test;

/**
 * @brief   @p test_class_c specific data.
 */
#define __test_class_data                                                   \
  __base_object_data                                                        \
  struct test_class_data                    test;

/**
 * @brief   @p test_class_c virtual methods table.
 */
struct test_class_vmt {
  __test_class_methods
};

/**
 * @brief   Structure representing a test class class.
 */
struct test_class {
  /**
   * @brief   Virtual Methods Table.
   */
  const struct test_class_vmt               *vmt;
  __test_class_data
};

/**
 * @name    Methods implementations (test_class_c)
 * @{
 */
/**
 * @brief   Implementation of object creation.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p test_class_c structure to be
 *                              initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
CC_FORCE_INLINE
static inline void *__test_class_objinit_impl(void *ip, const void *vmt) {
  test_class_c *self = (test_class_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __base_object_objinit_impl(self, vmt);

  /* No initialization code.*/

  return self;
}

/**
 * @brief   Implementation of object finalization.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p test_class_c structure to be
 *                              disposed.
 */
CC_FORCE_INLINE
static inline void __test_class_dispose_impl(void *ip) {
  test_class_c *self = (test_class_c *)ip;

  __base_object_dispose_impl(self);

  /* No finalization code.*/
  (void)self;
}
/** @} */

/**
 * @name    Virtual methods of (test_class_c)
 * @{
 */
/**
 * @brief   Low level driver start.
 *
 * @param[in,out] ip            Pointer to a @p test_class_c structure.
 * @return                      The operation status.
 */
CC_FORCE_INLINE
static inline int testStart(void *ip) {
  test_class_c *self = (test_class_c *)ip;

  return self->vmt->test.start(ip);
}

/**
 * @brief   Low level driver start.
 *
 * @param[in,out] ip            Pointer to a @p test_class_c structure.
 * @return                      The operation status.
 */
CC_FORCE_INLINE
static inline int testStop(void *ip) {
  test_class_c *self = (test_class_c *)ip;

  return self->vmt->test.stop(ip);
}

#if (TEST_CFG_OPTION2 == TRUE) || defined (__DOXYGEN__)
/**
 * @brief   Conditional method.
 *
 * @param[in,out] ip            Pointer to a @p test_class_c structure.
 */
CC_FORCE_INLINE
static inline void testReinit(void *ip) {
  test_class_c *self = (test_class_c *)ip;

   self->vmt->test.reinit(ip);
}
#endif /* TEST_CFG_OPTION2 == TRUE */
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  /* Methods of test_class_c.*/
  int testOpen(const void *ip);
  void testClose(const void *ip);
#if (TEST_CFG_OPTION1 == TRUE) || defined (__DOXYGEN__)
  void testConfigure(const void *ip);
#endif /* TEST_CFG_OPTION1 == TRUE */
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* GENERATOR_TEST_H */

/** @} */
