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
 * @file        drvoverlay.h
 * @brief       Generated VFS Template Driver header.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  DRVOVERLAY
 * @{
 */
 
#ifndef DRVOVERLAY_H
#define DRVOVERLAY_H

#if (VFS_CFG_ENABLE_DRV_OVERLAY == TRUE) || defined (__DOXYGEN__)

#include "oop_sequential_stream.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief       Maximum number of overlay directories.
 */
#if !defined(DRV_CFG_OVERLAY_DRV_MAX) || defined(__DOXYGEN__)
#define DRV_CFG_OVERLAY_DRV_MAX             1
#endif

/**
 * @brief       Number of directory nodes pre-allocated in the pool.
 */
#if !defined(DRV_CFG_OVERLAY_DIR_NODES_NUM) || defined(__DOXYGEN__)
#define DRV_CFG_OVERLAY_DIR_NODES_NUM       1
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Checks on DRV_CFG_OVERLAY_DRV_MAX configuration.*/
#if DRV_CFG_OVERLAY_DRV_MAX < 1
#error "invalid DRV_CFG_OVERLAY_DRV_MAX value"
#endif

/* Checks on DRV_CFG_OVERLAY_DIR_NODES_NUM configuration.*/
#if DRV_CFG_OVERLAY_DIR_NODES_NUM < 1
#error "invalid DRV_CFG_OVERLAY_DIR_NODES_NUM value"
#endif

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/**
 * @class       vfs_overlay_dir_node_c
 * @extends     vfs_directory_node_c
 *
 * @note        The class namespace is <tt>ovldir</tt>, access to class fields
 *              is done using: <tt><objp>->ovldir.<fieldname></tt><br>Note that
 *              fields of ancestor classes are in their own namespace in order
 *              to avoid field naming conflicts.
 *
 * @name        Class @p vfs_overlay_dir_node_c structures
 * @{
 */

/**
 * @brief       Type of a VFS overlay directory node class.
 */
typedef struct vfs_overlay_dir_node vfs_overlay_dir_node_c;

/**
 * @brief       Class @p vfs_overlay_dir_node_c data as a structure.
 */
struct ovldir_data {
  unsigned                  index;
  vfs_directory_node_c      *overlaid_root;
};

/**
 * @brief       Class @p vfs_overlay_dir_node_c methods.
 */
#define __ovldir_methods                                                    \
  __vfsdir_methods                                                          \
  /* No methods.*/

/**
 * @brief       Class @p vfs_overlay_dir_node_c data.
 */
#define __ovldir_data                                                       \
  __vfsdir_data                                                             \
  struct ovldir_data        ovldir;

/**
 * @brief       Class @p vfs_overlay_dir_node_c VMT initializer.
 */
#define __ovldir_vmt_init(ns)                                               \
  __vfsdir_vmt_init(ns)

/**
 * @brief       Class @p vfs_overlay_dir_node_c virtual methods table.
 */
struct vfs_overlay_dir_node_vmt {
  __ovldir_methods
};

/**
 * @brief       Structure representing a VFS overlay directory node class.
 */
struct vfs_overlay_dir_node {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_overlay_dir_node_vmt *vmt;
  __ovldir_data
};
/** @} */

/**
 * @class       vfs_overlay_driver_c
 * @extends     vfs_driver_c
 *
 * @note        The class namespace is <tt>ovldrv</tt>, access to class fields
 *              is done using: <tt><objp>->ovldrv.<fieldname></tt><br>Note that
 *              fields of ancestor classes are in their own namespace in order
 *              to avoid field naming conflicts.
 *
 * @name        Class @p vfs_overlay_driver_c structures
 * @{
 */

/**
 * @brief       Type of a VFS overlay driver class.
 */
typedef struct vfs_overlay_driver vfs_overlay_driver_c;

/**
 * @brief       Class @p vfs_overlay_driver_c data as a structure.
 */
struct ovldrv_data {
  vfs_driver_c              *overlaid_drv;
  const char                *path_prefix;
  char                      *path_cwd;
  unsigned                  next_driver;
  const char                *names[DRV_CFG_OVERLAY_DRV_MAX];
  vfs_driver_c              *drivers[DRV_CFG_OVERLAY_DRV_MAX];
};

/**
 * @brief       Class @p vfs_overlay_driver_c methods.
 */
#define __ovldrv_methods                                                    \
  __vfsdrv_methods                                                          \
  /* No methods.*/

/**
 * @brief       Class @p vfs_overlay_driver_c data.
 */
#define __ovldrv_data                                                       \
  __vfsdrv_data                                                             \
  struct ovldrv_data        ovldrv;

/**
 * @brief       Class @p vfs_overlay_driver_c VMT initializer.
 */
#define __ovldrv_vmt_init(ns)                                               \
  __vfsdrv_vmt_init(ns)

/**
 * @brief       Class @p vfs_overlay_driver_c virtual methods table.
 */
struct vfs_overlay_driver_vmt {
  __ovldrv_methods
};

/**
 * @brief       Structure representing a VFS overlay driver class.
 */
struct vfs_overlay_driver {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_overlay_driver_vmt *vmt;
  __ovldrv_data
};
/** @} */

/**
 * @brief       Structure representing the global state of @p
 *              vfs_overlay_driver_c.
 */
struct vfs_overlay_driver_static_struct {
  /**
   * @brief       Pool of directory nodes.
   */
  memory_pool_t             dir_nodes_pool;
  /**
   * @brief       Static storage of directory nodes.
   */
  vfs_overlay_dir_node_c    dir_nodes[DRV_CFG_OVERLAY_DIR_NODES_NUM];
};

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

extern struct vfs_overlay_driver_static_struct vfs_overlay_driver_static;

#ifdef __cplusplus
extern "C" {
#endif
  /* Methods of vfs_overlay_dir_node_c.*/
  void *__ovldir_objinit_impl(void *ip, const void *vmt,
                              vfs_overlay_driver_c *driver, vfs_mode_t mode);
  void __ovldir_dispose_impl(void *ip);
  /* Methods of vfs_overlay_driver_c.*/
  void *__ovldrv_objinit_impl(void *ip, const void *vmt,
                              vfs_driver_c *overlaid_drv,
                              const char *path_prefix);
  void __ovldrv_dispose_impl(void *ip);
  msg_t ovldrvRegisterDriver(void *ip, vfs_driver_c *vdp, const char *name);
  /* Regular functions.*/
  void __drv_overlay_init(void);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

/**
 * @name        Constructor and destructor of vfs_overlay_dir_node_c
 * @{
 */
/**
 * @memberof    vfs_overlay_dir_node_c
 *
 * @brief       Default initialization function of @p vfs_overlay_dir_node_c.
 *
 * @param[out]    self          Pointer to a @p vfs_overlay_dir_node_c instance
 *                              to be initialized.
 * @param[in]     driver        Pointer to the controlling driver.
 * @param[in]     mode          Node mode flags.
 * @return                      Pointer to the initialized object.
 *
 * @objinit
 */
CC_FORCE_INLINE
static inline vfs_overlay_dir_node_c *ovldirObjectInit(vfs_overlay_dir_node_c *self,
                                                       vfs_overlay_driver_c *driver,
                                                       vfs_mode_t mode) {
  extern const struct vfs_overlay_dir_node_vmt __ovldir_vmt;

  return __ovldir_objinit_impl(self, &__ovldir_vmt, driver, mode);
}

/**
 * @memberof    vfs_overlay_dir_node_c
 *
 * @brief       Default finalization function of @p vfs_overlay_dir_node_c.
 *
 * @param[in,out] self          Pointer to a @p vfs_overlay_dir_node_c instance
 *                              to be finalized.
 *
 * @dispose
 */
CC_FORCE_INLINE
static inline void ovldirDispose(vfs_overlay_dir_node_c *self) {

  __ovldir_dispose_impl(self);
}
/** @} */

/**
 * @name        Constructor and destructor of vfs_overlay_driver_c
 * @{
 */
/**
 * @memberof    vfs_overlay_driver_c
 *
 * @brief       Default initialization function of @p vfs_overlay_driver_c.
 *
 * @param[out]    self          Pointer to a @p vfs_overlay_driver_c instance
 *                              to be initialized.
 * @param[in]     overlaid_drv  Pointer to a driver to be overlaid or @p NULL.
 * @param[in]     path_prefix   Prefix to be added to the paths or @p NULL, it
 *                              must be a normalized absolute path.
 * @return                      Pointer to the initialized object.
 *
 * @objinit
 */
CC_FORCE_INLINE
static inline vfs_overlay_driver_c *ovldrvObjectInit(vfs_overlay_driver_c *self,
                                                     vfs_driver_c *overlaid_drv,
                                                     const char *path_prefix) {
  extern const struct vfs_overlay_driver_vmt __ovldrv_vmt;

  return __ovldrv_objinit_impl(self, &__ovldrv_vmt, overlaid_drv, path_prefix);
}

/**
 * @memberof    vfs_overlay_driver_c
 *
 * @brief       Default finalization function of @p vfs_overlay_driver_c.
 *
 * @param[in,out] self          Pointer to a @p vfs_overlay_driver_c instance
 *                              to be finalized.
 *
 * @dispose
 */
CC_FORCE_INLINE
static inline void ovldrvDispose(vfs_overlay_driver_c *self) {

  __ovldrv_dispose_impl(self);
}
/** @} */

#endif /* VFS_CFG_ENABLE_DRV_OVERLAY == TRUE */

#endif /* DRVOVERLAY_H */

/** @} */
