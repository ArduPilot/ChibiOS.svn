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
 * @file    hal_base_driver.h
 * @brief   Generated HAL_BASE_DRIVER header.
 *
 * @addtogroup HAL_BASE_DRIVER
 * @brief   Common driver base abstract class.
 * @details This abstract class is the common ancestor of all HAL stateful HAL
 *          drivers.
 * @note    This is a generated file, do not edit directly.
 * @{
 */
 
#ifndef HAL_BASE_DRIVER_H
#define HAL_BASE_DRIVER_H

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @name    Common driver states
 * @{
 */
#define HAL_DRV_STATE_UNINIT                0U
#define HAL_DRV_STATE_STOP                  1U
#define HAL_DRV_STATE_READY                 2U
#define HAL_DRV_STATE_ACTIVE                3U
#define HAL_DRV_STATE_ERROR                 4U
/** @} */

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   Enables the mutual exclusion APIs on driver instances.
 * @note    Disabling this option saves both code and data space.
 */
#if !defined(HAL_USE_MUTUAL_EXCLUSION) || defined(__DOXYGEN__)
#define HAL_USE_MUTUAL_EXCLUSION            TRUE
#endif

/**
 * @brief   Enables the HAL registry for drivers.
 * @note    Disabling this option saves both code and data space.
 */
#if !defined(HAL_USE_REGISTRY) || defined(__DOXYGEN__)
#define HAL_USE_REGISTRY                    FALSE
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Checks on HAL_USE_MUTUAL_EXCLUSION configuration.*/
#if (HAL_USE_MUTUAL_EXCLUSION != FALSE) && (HAL_USE_MUTUAL_EXCLUSION != TRUE)
#error "invalid HAL_USE_MUTUAL_EXCLUSION value"
#endif

/* Checks on HAL_USE_REGISTRY configuration.*/
#if (HAL_USE_REGISTRY != FALSE) && (HAL_USE_REGISTRY != TRUE)
#error "invalid HAL_USE_REGISTRY value"
#endif

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a driver state variable.
 */
typedef unsigned int driver_state_t;

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* Module class hal_base_driver_c                                            */
/*===========================================================================*/

/**
 * @brief   Type of a HAL base driver class.
 */
typedef struct hal_base_driver hal_base_driver_c;

/**
 * @brief   @p hal_base_driver_c methods as a structure.
 */
struct hal_base_driver_methods {
  msg_t (*start)(void *ip);
  void (*stop)(void *ip);
  msg_t (*configure)(void *ip, const void *config);
  void * (*getif)(void *ip);
};

/**
 * @brief   @p hal_base_driver_c data as a structure.
 */
struct hal_base_driver_data {
  driver_state_t                            state;
  unsigned int                              opencnt;
  void                                      *owner;
#if (HAL_USE_MUTUAL_EXCLUSION == TRUE) || defined (__DOXYGEN__)
  mutex_t                                   mutex;
#endif /* HAL_USE_MUTUAL_EXCLUSION == TRUE */
};

/**
 * @brief   @p hal_base_driver_c methods.
 */
#define __hal_base_driver_methods                                           \
  __base_object_methods                                                     \
  struct hal_base_driver_methods            drv;

/**
 * @brief   @p hal_base_driver_c data.
 */
#define __hal_base_driver_data                                              \
  __base_object_data                                                        \
  struct hal_base_driver_data               drv;

/**
 * @brief   @p hal_base_driver_c VMT initializer.
 */
#define __hal_base_driver_vmt_init(offset, ns)                              \
  __base_object_vmt_init(offset, ns),                                       \
  .drv.start                                = __##ns##_start,               \
  .drv.stop                                 = __##ns##_stop,                \
  .drv.configure                            = __##ns##_configure,           \
  .drv.getif                                = __##ns##_getif

/**
 * @brief   @p hal_base_driver_c virtual methods table.
 */
struct hal_base_driver_vmt {
  __hal_base_driver_methods
};

/**
 * @brief   Structure representing a HAL base driver class.
 */
struct hal_base_driver {
  /**
   * @brief   Virtual Methods Table.
   */
  const struct hal_base_driver_vmt          *vmt;
  __hal_base_driver_data
};

/**
 * @name    Methods implementations (hal_base_driver_c)
 * @{
 */
/**
 * @brief   Implementation of object creation.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p hal_base_driver_c structure to
 *                              be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
CC_FORCE_INLINE
static inline void *__hal_base_driver_objinit_impl(void *ip, const void *vmt) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __base_object_objinit_impl(self, vmt);

  /* Initialization code.*/
  self->drv.state   = HAL_DRV_STATE_STOP;
  self->drv.opencnt = 0U;
  self->drv.owner   = NULL;
  osalMutexObjectInit(&self->drv.mutex);
#if HAL_USE_REGISTRY == TRUE
  self->drv.id      = 0U;
#endif

  return self;
}

/**
 * @brief   Implementation of object finalization.
 * @note    This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure to
 *                              be disposed.
 */
CC_FORCE_INLINE
static inline void __hal_base_driver_dispose_impl(void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  __base_object_dispose_impl(self);

  /* No finalization code.*/
  (void)self;
}
/** @} */

/**
 * @name    Virtual methods of (hal_base_driver_c)
 * @{
 */
/**
 * @brief   Low level driver start.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure.
 * @return                      The operation status.
 */
CC_FORCE_INLINE
static inline msg_t __drv_start_protected(void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  return self->vmt->drv.start(ip);
}

/**
 * @brief   Low level driver stop.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure.
 */
CC_FORCE_INLINE
static inline void __drv_stop_protected(void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

   self->vmt->drv.stop(ip);
}

/**
 * @brief   Driver configure.
 * @details Applies a new configuration to the driver. The configuration
 *          structure is architecture-dependent.
 * @note    Applying a configuration should be done while the peripheral is not
 *          actively operating, this function can fail depending on the driver
 *          implementation and current state.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure.
 * @param         config        New driver configuration.
 */
CC_FORCE_INLINE
static inline msg_t drvConfigureX(void *ip, const void *config) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  return self->vmt->drv.configure(ip, config);
}

/**
 * @brief   Driver interface get.
 *
 * @param[in,out] ip            Pointer to a @p hal_base_driver_c structure.
 * @return                      The driver interface or @p NULL if none.
 */
CC_FORCE_INLINE
static inline void * drvGetInterfaceX(void *ip) {
  hal_base_driver_c *self = (hal_base_driver_c *)ip;

  return self->vmt->drv.getif(ip);
}
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  /* Methods of hal_base_driver_c.*/
  msg_t drvOpen(const void *ip);
  void drvClose(const void *ip);
  driver_state_t drvGetStateX(const void *ip);
  void drvSetStateX(const void *ip, driver_state_t state);
  void * drvGetOwnerX(const void *ip);
  void drvSetOwnerX(const void *ip, void *owner);
#if (HAL_USE_MUTUAL_EXCLUSION == TRUE) || defined (__DOXYGEN__)
  void drvLock(const void *ip);
  void drvUnlock(const void *ip);
#endif /* HAL_USE_MUTUAL_EXCLUSION == TRUE */
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* HAL_BASE_DRIVER_H */

/** @} */
