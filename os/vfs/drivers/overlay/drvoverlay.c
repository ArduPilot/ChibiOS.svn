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
 * @file        drvoverlay.c
 * @brief       Generated VFS Template Driver source.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  DRVOVERLAY
 * @{
 */

#include "vfs.h"
#include "drvoverlay_impl.h"

#if (VFS_CFG_ENABLE_DRV_OVERLAY == TRUE) || defined (__DOXYGEN__)

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module local macros.                                                      */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/**
 * @brief       Global state of @p vfs_overlay_driver_c.
 */
struct vfs_overlay_driver_static_struct vfs_overlay_driver_static;

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief       Module initialization.
 *
 * @init
 */
void __drv_overlay_init(void) {

  /* Initializing pools.*/
  chPoolObjectInit(&vfs_overlay_driver_static.dir_nodes_pool,
                   sizeof (vfs_overlay_dir_node_c),
                   chCoreAllocAlignedI);

  /* Preloading pools.*/
  chPoolLoadArray(&vfs_overlay_driver_static.dir_nodes_pool,
                  &vfs_overlay_driver_static.dir_nodes[0],
                  DRV_CFG_OVERLAY_DIR_NODES_NUM);
}

/*===========================================================================*/
/* Module class "vfs_overlay_dir_node_c" methods.                            */
/*===========================================================================*/

/**
 * @brief       VMT structure of VFS overlay directory node class.
 * @note        It is public because accessed by the inlined constructor.
 */
const struct vfs_overlay_dir_node_vmt __ovldir_vmt = {
  __ovldir_vmt_init(ovldir)
};

/**
 * @name        Virtual methods implementations of vfs_overlay_dir_node_c
 * @{
 */
/**
 * @memberof    vfs_overlay_dir_node_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_overlay_dir_node_c instance
 *                              to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @param[in]     driver        Pointer to the controlling driver.
 * @param[in]     mode          Node mode flags.
 * @return                      A new reference to the object.
 */
void *__ovldir_objinit_impl(void *ip, const void *vmt,
                            vfs_overlay_driver_c *driver, vfs_mode_t mode) {
  vfs_overlay_dir_node_c *self = (vfs_overlay_dir_node_c *)ip;

  /* Initialization code.*/
  self = __vfsdir_objinit_impl(ip, vmt, (vfs_driver_c *)driver, mode);

  self->ovldir.index         = 0U;
  self->ovldir.overlaid_root = NULL;

  return self;
}

/**
 * @memberof    vfs_overlay_dir_node_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_overlay_dir_node_c instance
 *                              to be disposed.
 */
void __ovldir_dispose_impl(void *ip) {
  vfs_overlay_dir_node_c *self = (vfs_overlay_dir_node_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsdir_dispose_impl(self);
}
/** @} */

/*===========================================================================*/
/* Module class "vfs_overlay_driver_c" methods.                              */
/*===========================================================================*/

/**
 * @brief       VMT structure of VFS overlay driver class.
 * @note        It is public because accessed by the inlined constructor.
 */
const struct vfs_overlay_driver_vmt __ovldrv_vmt = {
  __ovldrv_vmt_init(ovldrv)
};

/**
 * @name        Virtual methods implementations of vfs_overlay_driver_c
 * @{
 */
/**
 * @memberof    vfs_overlay_driver_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_overlay_driver_c instance
 *                              to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @param[in]     overlaid_drv  Pointer to a driver to be overlaid or @p NULL.
 * @param[in]     path_prefix   Prefix to be added to the paths or @p NULL, it
 *                              must be a normalized absolute path.
 * @return                      A new reference to the object.
 */
void *__ovldrv_objinit_impl(void *ip, const void *vmt,
                            vfs_driver_c *overlaid_drv,
                            const char *path_prefix) {
  vfs_overlay_driver_c *self = (vfs_overlay_driver_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __vfsdrv_objinit_impl(self, vmt);

  /* Initialization code.*/
  self->ovldrv.overlaid_drv = overlaid_drv;
  self->ovldrv.path_prefix  = path_prefix;
  self->ovldrv.path_cwd     = NULL;
  self->ovldrv.next_driver  = 0U;

  return self;
}

/**
 * @memberof    vfs_overlay_driver_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_overlay_driver_c instance
 *                              to be disposed.
 */
void __ovldrv_dispose_impl(void *ip) {
  vfs_overlay_driver_c *self = (vfs_overlay_driver_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsdrv_dispose_impl(self);
}
/** @} */

/**
 * @name        Regular methods of vfs_overlay_driver_c
 * @{
 */
/**
 * @memberof    vfs_overlay_driver_c
 * @public
 *
 * @brief       Registers a VFS driver as an overlay.
 *
 * @param[in,out] ip            Pointer to a @p vfs_overlay_driver_c instance.
 * @return                      The operation result.
 *
 * @api
 */
msg_t ovldrvRegisterDriver(void *ip, vfs_driver_c *vdp, const char *name) {
  vfs_overlay_driver_c *self = (vfs_overlay_driver_c *)ip;
  msg_t ret;

  if (self->ovldrv.next_driver >= DRV_CFG_OVERLAY_DRV_MAX) {
    ret = CH_RET_ENOMEM;
  }
  else {
    self->ovldrv.names[self->ovldrv.next_driver]   = name;
    self->ovldrv.drivers[self->ovldrv.next_driver] = vdp;
    self->ovldrv.next_driver++;
    ret = CH_RET_SUCCESS;
  }

  return ret;
}
/** @} */

#endif /* VFS_CFG_ENABLE_DRV_OVERLAY == TRUE */

/** @} */
