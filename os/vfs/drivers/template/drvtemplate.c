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
 * @file        drvtemplate.c
 * @brief       Generated VFS Template Driver source.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  DRVTEMPLATE
 * @{
 */

#include "vfs.h"

#if (VFS_CFG_ENABLE_DRV_TEMPLATE == TRUE) || defined (__DOXYGEN__)

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
 *              vfs_template_driver_c.
 */
struct vfs_template_driver_static_struct {
  /**
   * @brief       Pool of file system objects.
   */
  memory_pool_t             fs_nodes_pool;
  /**
   * @brief       Pool of file info objects.
   */
  memory_pool_t             info_nodes_pool;
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
  vfs_template_dir_node_c   dir_nodes[DRV_CFG_TEMPLATE_DIR_NODES_NUM];
  /**
   * @brief       Static storage of file nodes.
   */
  vfs_template_file_node_c  file_nodes[DRV_CFG_TEMPLATE_FILE_NODES_NUM];
};

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/**
 * @brief       Global state of @p vfs_template_driver_c.
 */
static struct vfs_template_driver_static_struct vfs_template_driver_static;

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

static void *__tmpldir_ro_addref_impl(void *ip) {

  return __ro_addref_impl(ip);
}

static object_references_t __tmpldir_ro_release_impl(void *ip) {

  return __ro_release_impl(ip);
}

static msg_t __tmpldir_vfsnode_stat_impl(void *ip, vfs_stat_t *sp) {

  return __vfsnode_stat_impl(ip, sp);
}

static msg_t __tmpldir_vfsdir_first_impl(void *ip, vfs_direntry_info_t *dip) {

  return __vfsdir_first_impl(ip, dip);
}

static msg_t __tmpldir_vfsdir_next_impl(void *ip, vfs_direntry_info_t *dip) {

  return __vfsdir_next_impl(ip, dip);
}

static void *__tmplfile_ro_addref_impl(void *ip) {

  return __ro_addref_impl(ip);
}

static object_references_t __tmplfile_ro_release_impl(void *ip) {

  return __ro_release_impl(ip);
}

static msg_t __tmplfile_vfsnode_stat_impl(void *ip, vfs_stat_t *sp) {

  return __vfsnode_stat_impl(ip, sp);
}

static ssize_t __tmplfile_vfsfile_read_impl(void *ip, uint8_t *buf,
                                            size_t size) {

  return __vfsfile_read_impl(ip, buf, size);
}

static ssize_t __tmplfile_vfsfile_write_impl(void *ip, const uint8_t *buf,
                                             size_t size) {

  return __vfsfile_write_impl(ip, buf, size);
}

static msg_t __tmplfile_vfsfile_setpos_impl(void *ip, vfs_offset_t offset,
                                            vfs_seekmode_t whence) {

  return __vfsfile_setpos_impl(ip, offset, whence);
}

static vfs_offset_t __tmplfile_vfsfile_getpos_impl(void *ip) {

  return __vfsfile_getpos_impl(ip);
}

static BaseSequentialStream *__tmplfile_vfsfile_getstream_impl(void *ip) {

  return __vfsfile_getstream_impl(ip);
}

static msg_t __tmpldrv_vfsdrv_setcwd_impl(void *ip, const char *path) {

  return __vfsdrv_setcwd_impl(ip, path);
}

static msg_t __tmpldrv_vfsdrv_getcwd_impl(void *ip, char *buf, size_t size) {

  return __vfsdrv_getcwd_impl(ip, buf, size);
}

static msg_t __tmpldrv_vfsdrv_stat_impl(void *ip, const char *path,
                                        vfs_stat_t *sp) {

  return __vfsdrv_stat_impl(ip, path, sp);
}

static msg_t __tmpldrv_vfsdrv_opendir_impl(void *ip, const char *path,
                                           vfs_directory_node_c **vdnpp) {

  return __vfsdrv_opendir_impl(ip, path, vdnpp);
}

static msg_t __tmpldrv_vfsdrv_openfile_impl(void *ip, const char *path,
                                            int flags, vfs_file_node_c **vfnpp) {

  return __vfsdrv_openfile_impl(ip, path, flags, vfnpp);
}

static msg_t __tmpldrv_vfsdrv_unlink_impl(void *ip, const char *path) {

  return __vfsdrv_unlink_impl(ip, path);
}

static msg_t __tmpldrv_vfsdrv_rename_impl(void *ip, const char *oldpath,
                                          const char *newpath) {

  return __vfsdrv_rename_impl(ip, oldpath, newpath);
}

static msg_t __tmpldrv_vfsdrv_mkdir_impl(void *ip, const char *path,
                                         vfs_mode_t mode) {

  return __vfsdrv_mkdir_impl(ip, path, mode);
}

static msg_t __tmpldrv_vfsdrv_rmdir_impl(void *ip, const char *path) {

  return __vfsdrv_rmdir_impl(ip, path);
}

static size_t __tmplfile_stm_write_impl(void *ip, const uint8_t *buf,
                                        size_t size) {
  vfs_template_file_node_c *self = oopIfGetOwner(vfs_template_file_node_c, ip);

  (void)self;
  (void)buf;
  (void)size;

  return (size_t)0;
}

static size_t __tmplfile_stm_read_impl(void *ip, uint8_t *buf, size_t size) {
  vfs_template_file_node_c *self = oopIfGetOwner(vfs_template_file_node_c, ip);

  (void)self;
  (void)buf;
  (void)size;

  return (size_t)0;
}

static msg_t __tmplfile_stm_put_impl(void *ip, uint8_t b) {
  vfs_template_file_node_c *self = oopIfGetOwner(vfs_template_file_node_c, ip);

  (void)self;
  (void)b;

  return MSG_OK;
}

static msg_t __tmplfile_stm_get_impl(void *ip) {
  vfs_template_file_node_c *self = oopIfGetOwner(vfs_template_file_node_c, ip);

  (void)self;

  return (msg_t)0;
}

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief       Module initialization.
 *
 * @init
 */
void __drv_template_init(void) {

  /* Initializing pools.*/
  chPoolObjectInit(&vfs_template_driver_static.dir_nodes_pool,
                   sizeof (vfs_template_dir_node_c),
                   chCoreAllocAlignedI);
  chPoolObjectInit(&vfs_template_driver_static.file_nodes_pool,
                   sizeof (vfs_template_file_node_c),
                   chCoreAllocAlignedI);

  /* Preloading pools.*/
  chPoolLoadArray(&vfs_template_driver_static.dir_nodes_pool,
                  &vfs_template_driver_static.dir_nodes[0],
                  DRV_CFG_TEMPLATE_DIR_NODES_NUM);
  chPoolLoadArray(&vfs_template_driver_static.file_nodes_pool,
                  &vfs_template_driver_static.file_nodes[0],
                  DRV_CFG_TEMPLATE_FILE_NODES_NUM);
}

/*===========================================================================*/
/* Module class "vfs_template_dir_node_c" methods.                           */
/*===========================================================================*/

/**
 * @brief       VMT structure of VFS template directory node class.
 * @note        It is public because accessed by the inlined constructor.
 */
const struct vfs_template_dir_node_vmt __tmpldir_vmt = {
  __tmpldir_vmt_init(tmpldir)
};

/**
 * @name        Virtual methods implementations of vfs_template_dir_node_c
 * @{
 */
/**
 * @memberof    vfs_template_dir_node_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_template_dir_node_c
 *                              instance to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
void *__tmpldir_objinit_impl(void *ip, const void *vmt) {
  vfs_template_dir_node_c *self = (vfs_template_dir_node_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __vfsdir_objinit_impl(self, vmt);

  /* No initialization code.*/

  return self;
}

/**
 * @memberof    vfs_template_dir_node_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_template_dir_node_c
 *                              instance to be disposed.
 */
void __tmpldir_dispose_impl(void *ip) {
  vfs_template_dir_node_c *self = (vfs_template_dir_node_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsdir_dispose_impl(self);
}
/** @} */

/*===========================================================================*/
/* Module class "vfs_template_file_node_c" methods.                          */
/*===========================================================================*/

/**
 * @brief       VMT structure of VFS template file node class.
 * @note        It is public because accessed by the inlined constructor.
 */
const struct vfs_template_file_node_vmt __tmplfile_vmt = {
  __tmplfile_vmt_init(tmplfile)
};

/**
 * @name        Virtual methods implementations of vfs_template_file_node_c
 * @{
 */
/**
 * @memberof    vfs_template_file_node_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_template_file_node_c
 *                              instance to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
void *__tmplfile_objinit_impl(void *ip, const void *vmt) {
  vfs_template_file_node_c *self = (vfs_template_file_node_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __vfsfile_objinit_impl(self, vmt);

  /* Implementation of interface sequential_stream_i.*/
  {
    static const struct sequential_stream_vmt tmplfile_stm_vmt = {
      __stm_vmt_init(tmplfile, offsetof(vfs_template_file_node_c, tmplfile.stm))
    };
    oopIfObjectInit(&self->tmplfile.stm, &tmplfile_stm_vmt);
  }

  /* No initialization code.*/

  return self;
}

/**
 * @memberof    vfs_template_file_node_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_template_file_node_c
 *                              instance to be disposed.
 */
void __tmplfile_dispose_impl(void *ip) {
  vfs_template_file_node_c *self = (vfs_template_file_node_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsfile_dispose_impl(self);
}
/** @} */

/*===========================================================================*/
/* Module class "vfs_template_driver_c" methods.                             */
/*===========================================================================*/

/**
 * @brief       VMT structure of VFS template driver class.
 * @note        It is public because accessed by the inlined constructor.
 */
const struct vfs_template_driver_vmt __tmpldrv_vmt = {
  __tmpldrv_vmt_init(tmpldrv)
};

/**
 * @name        Virtual methods implementations of vfs_template_driver_c
 * @{
 */
/**
 * @memberof    vfs_template_driver_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_template_driver_c instance
 *                              to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
void *__tmpldrv_objinit_impl(void *ip, const void *vmt) {
  vfs_template_driver_c *self = (vfs_template_driver_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __vfsdrv_objinit_impl(self, vmt);

  /* No initialization code.*/

  return self;
}

/**
 * @memberof    vfs_template_driver_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_template_driver_c instance
 *                              to be disposed.
 */
void __tmpldrv_dispose_impl(void *ip) {
  vfs_template_driver_c *self = (vfs_template_driver_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsdrv_dispose_impl(self);
}
/** @} */

#endif /* VFS_CFG_ENABLE_DRV_TEMPLATE == TRUE */

/** @} */
