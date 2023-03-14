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
 * @file        drvstreams.c
 * @brief       Generated VFS Streams Driver source.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  DRVSTREAMS
 * @{
 */

#include "vfs.h"

#if (VFS_CFG_ENABLE_DRV_STREAMS == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module local macros.                                                      */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/**
 * @brief       Structure representing the global state of @p
 *              vfs_streams_driver_c.
 */
struct vfs_streams_driver_static_struct {
  /**
   * @brief       Pool of directory nodes.
   */
  memory_pool_t             dir_nodes_pool;
  /**
   * @brief       Pool of file nodes.
   */
  memory_pool_t             file_nodes_pool;
  /**
   * @brief       Static storage of directory nodes.
   */
  vfs_streams_dir_node_c    dir_nodes[DRV_CFG_STREAMS_DIR_NODES_NUM];
  /**
   * @brief       Static storage of file nodes.
   */
  vfs_streams_file_node_c   file_nodes[DRV_CFG_STREAMS_FILE_NODES_NUM];
};

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/**
 * @brief       Global state of @p vfs_streams_driver_c.
 */
static struct vfs_streams_driver_static_struct vfs_streams_driver_static;

/* Methods implementations in an unmanaged module.*/
#include "drvstreams_impl.inc"

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
void __drv_streams_init(void) {

    /* Initializing pools.*/
    chPoolObjectInit(&vfs_streams_driver_static.dir_nodes_pool,
                     sizeof (vfs_streams_dir_node_c),
                     chCoreAllocAlignedI);
    chPoolObjectInit(&vfs_streams_driver_static.file_nodes_pool,
                     sizeof (vfs_streams_file_node_c),
                     chCoreAllocAlignedI);

    /* Preloading pools.*/
    chPoolLoadArray(&vfs_streams_driver_static.dir_nodes_pool,
                    &vfs_streams_driver_static.dir_nodes[0],
                    DRV_CFG_STREAMS_DIR_NODES_NUM);
    chPoolLoadArray(&vfs_streams_driver_static.file_nodes_pool,
                    &vfs_streams_driver_static.file_nodes[0],
                    DRV_CFG_STREAMS_FILE_NODES_NUM);
}

/*===========================================================================*/
/* Module class "vfs_streams_dir_node_c" methods.                            */
/*===========================================================================*/

/**
 * @brief       VMT structure of VFS streams directory node class.
 * @note        It is public because accessed by the inlined constructor.
 */
const struct vfs_streams_dir_node_vmt __stmdir_vmt = {
  __stmdir_vmt_init(stmdir)
};

/**
 * @name        Methods implementations of vfs_streams_dir_node_c
 * @{
 */
/**
 * @memberof    vfs_streams_dir_node_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_streams_dir_node_c instance
 *                              to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @param[in]     driver        Pointer to the controlling driver.
 * @param[in]     mode          Node mode flags.
 * @return                      A new reference to the object.
 */
void *__stmdir_objinit_impl(void *ip, const void *vmt, vfs_driver_c *driver,
                            vfs_mode_t mode) {
  vfs_streams_dir_node_c *self = (vfs_streams_dir_node_c *)ip;

  /* Initialization code.*/
  self = __vfsdir_objinit_impl(ip, vmt, (vfs_driver_c *)driver, mode);
  self->stmdir.index = 0U;

  return self;
}

/**
 * @memberof    vfs_streams_dir_node_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_streams_dir_node_c instance
 *                              to be disposed.
 */
void __stmdir_dispose_impl(void *ip) {
  vfs_streams_dir_node_c *self = (vfs_streams_dir_node_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsdir_dispose_impl(self);
}
/** @} */

/*===========================================================================*/
/* Module class "vfs_streams_file_node_c" methods.                           */
/*===========================================================================*/

/**
 * @brief       VMT structure of VFS streams file node class.
 * @note        It is public because accessed by the inlined constructor.
 */
const struct vfs_streams_file_node_vmt __stmfile_vmt = {
  __stmfile_vmt_init(stmfile)
};

/**
 * @name        Methods implementations of vfs_streams_file_node_c
 * @{
 */
/**
 * @memberof    vfs_streams_file_node_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_streams_file_node_c
 *                              instance to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @param[in]     driver        Pointer to the controlling driver.
 * @param[in]     mode          Node mode flags.
 * @param[in]     stream        Stream to be associated.
 * @return                      A new reference to the object.
 */
void *__stmfile_objinit_impl(void *ip, const void *vmt, vfs_driver_c *driver,
                             vfs_mode_t mode, sequential_stream_i *stream) {
  vfs_streams_file_node_c *self = (vfs_streams_file_node_c *)ip;

  /* Initialization code.*/
  self = __vfsfile_objinit_impl(ip, vmt, (vfs_driver_c *)driver, mode);
  self->stmfile.stm = stream;

  return self;
}

/**
 * @memberof    vfs_streams_file_node_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_streams_file_node_c
 *                              instance to be disposed.
 */
void __stmfile_dispose_impl(void *ip) {
  vfs_streams_file_node_c *self = (vfs_streams_file_node_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsfile_dispose_impl(self);
}
/** @} */

/*===========================================================================*/
/* Module class "vfs_streams_driver_c" methods.                              */
/*===========================================================================*/

/**
 * @brief       VMT structure of VFS streams driver class.
 * @note        It is public because accessed by the inlined constructor.
 */
const struct vfs_streams_driver_vmt __stmdrv_vmt = {
  __stmdrv_vmt_init(stmdrv)
};

/**
 * @name        Methods implementations of vfs_streams_driver_c
 * @{
 */
/**
 * @memberof    vfs_streams_driver_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_streams_driver_c instance
 *                              to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @param[in]     streams       Pointer to a @p vfs_streams_driver_c structure.
 * @return                      A new reference to the object.
 */
void *__stmdrv_objinit_impl(void *ip, const void *vmt,
                            const drv_streams_element_t *streams) {
  vfs_streams_driver_c *self = (vfs_streams_driver_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __vfsdrv_objinit_impl(self, vmt);

  /* Initialization code.*/
  self->stmdrv.streams  = streams;

  return self;
}

/**
 * @memberof    vfs_streams_driver_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_streams_driver_c instance
 *                              to be disposed.
 */
void __stmdrv_dispose_impl(void *ip) {
  vfs_streams_driver_c *self = (vfs_streams_driver_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsdrv_dispose_impl(self);
}
/** @} */

#endif /* VFS_CFG_ENABLE_DRV_STREAMS == TRUE */

/** @} */
