/*
    ChibiOS - Copyright (C) 2006,2007,2008,2009,2010,2011,2012,2013,2014,
              2015,2016,2017,2018,2019,2020,2021 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation version 3 of the License.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    vfs/drivers/drvsfs.c
 * @brief   HAL FatFS VFS driver code.
 *
 * @addtogroup VFS_DRV_SFS
 * @{
 */

#include "vfs.h"

#if (VFS_CFG_ENABLE_DRV_SFS == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

static msg_t drv_open_dir(void *instance,
                          const char *path,
                          vfs_directory_node_c **vdnpp);
static msg_t drv_open_file(void *instance,
                           const char *path,
                           int oflag,
                           vfs_file_node_c **vfnpp);

static const struct vfs_sfs_driver_vmt driver_vmt = {
  .open_dir     = drv_open_dir,
  .open_file    = drv_open_file
};

static void node_dir_release(void *instance);
static msg_t node_dir_first(void *instance, vfs_node_info_t *nip);
static msg_t node_dir_next(void *instance, vfs_node_info_t *nip);

static const struct vfs_sfs_dir_node_vmt dir_node_vmt = {
  .release      = node_dir_release,
  .dir_first    = node_dir_first,
  .dir_next     = node_dir_next
};

static void node_file_release(void *instance);
static BaseSequentialStream *node_file_get_stream(void *instance);
static ssize_t node_file_read(void *instance, uint8_t *buf, size_t n);
static ssize_t node_file_write(void *instance, const uint8_t *buf, size_t n);
static msg_t node_file_setpos(void *instance, vfs_offset_t offset);
static vfs_offset_t node_file_getpos(void *instance);
static vfs_offset_t node_file_getsize(void *instance);

static const struct vfs_sfs_file_node_vmt file_node_vmt = {
  .release          = node_file_release,
  .file_get_stream  = node_file_get_stream,
  .file_read        = node_file_read,
  .file_write       = node_file_write,
  .file_setpos      = node_file_setpos,
  .file_getpos      = node_file_getpos,
  .file_getsize     = node_file_getsize
};

static size_t file_stream_write(void *instance, const uint8_t *bp, size_t n);
static size_t file_stream_read(void *instance, uint8_t *bp, size_t n);
static msg_t file_stream_put(void *instance, uint8_t b);
static msg_t file_stream_get(void *instance);

static const struct BaseSequentialStreamVMT file_stream_vmt = {
  .instance_offset  = __CH_OFFSETOF(vfs_sfs_file_node_c, stream.vmt),
  .write            = file_stream_write,
  .read             = file_stream_read,
  .put              = file_stream_put,
  .get              = file_stream_get
};

/**
 * @brief   Static members of @p vfs_sfs_driver_c.
 */
static struct {
  /**
   * @brief   Pool of file system objects.
   */
  memory_pool_t                     fs_nodes_pool;
  /**
   * @brief   Pool of file info objects.
   */
  memory_pool_t                     info_nodes_pool;
  /**
   * @brief   Pool of directory nodes.
   */
  memory_pool_t                     dir_nodes_pool;
  /**
   * @brief   Pool of file nodes.
   */
  memory_pool_t                     file_nodes_pool;
  /**
   * @brief   Static storage of directory nodes.
   */
  vfs_sfs_dir_node_c                dir_nodes[DRV_CFG_SFS_DIR_NODES_NUM];
  /**
   * @brief   Static storage of file nodes.
   */
  vfs_sfs_file_node_c               file_nodes[DRV_CFG_SFS_FILE_NODES_NUM];
} vfs_sfs_driver_static;

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

static msg_t drv_open_dir(void *instance,
                          const char *path,
                          vfs_directory_node_c **vdnpp) {
  msg_t err = VFS_RET_SUCCESS;

  do {
    vfs_sfs_driver_c *drvp = (vfs_sfs_driver_c *)instance;

    (void)drvp;
    (void)path;
    (void)vdnpp;

  }
  while (false);

  return err;
}

static msg_t drv_open_file(void *instance,
                           const char *path,
                           int oflag,
                           vfs_file_node_c **vfnpp) {
  msg_t err = VFS_RET_SUCCESS;

  do {
    vfs_sfs_driver_c *drvp = (vfs_sfs_driver_c *)instance;

    (void)drvp;
    (void)path;
    (void)oflag;
    (void)vfnpp;

  }
  while (false);

  return err;
}

static void node_dir_release(void *instance) {
  vfs_sfs_dir_node_c *dnp = (vfs_sfs_dir_node_c *)instance;

  __referenced_object_release_impl(instance);
  if (__referenced_object_getref_impl(instance) == 0U) {

    chPoolFree(&vfs_sfs_driver_static.dir_nodes_pool, (void *)dnp);
  }
}

static msg_t node_dir_first(void *instance, vfs_node_info_t *nip) {
  vfs_sfs_dir_node_c *dnp = (vfs_sfs_dir_node_c *)instance;
  msg_t err = VFS_RET_SUCCESS;;

  (void)dnp;

  /* TODO rewind */
  err = node_dir_next(instance, nip);

  return err;
}

static msg_t node_dir_next(void *instance, vfs_node_info_t *nip) {
  msg_t err = VFS_RET_SUCCESS;

  do {
    vfs_sfs_dir_node_c *dnp = (vfs_sfs_dir_node_c *)instance;

    (void)dnp;
    (void)nip;
  }
  while (false);

  return err;
}

static void node_file_release(void *instance) {
  vfs_sfs_file_node_c *fnp = (vfs_sfs_file_node_c *)instance;

  __referenced_object_release_impl(instance);
  if (__referenced_object_getref_impl(instance) == 0U) {

    chPoolFree(&vfs_sfs_driver_static.file_nodes_pool, (void *)fnp);
  }
}

static BaseSequentialStream *node_file_get_stream(void *instance) {
  vfs_sfs_file_node_c *fnp = (vfs_sfs_file_node_c *)instance;

  return &fnp->stream;
}

static ssize_t node_file_read(void *instance, uint8_t *buf, size_t n) {
  vfs_sfs_file_node_c *fnp = (vfs_sfs_file_node_c *)instance;

  (void)fnp;
  (void)buf;
  (void)n;

  return (ssize_t)0;
}

static ssize_t node_file_write(void *instance, const uint8_t *buf, size_t n) {
  vfs_sfs_file_node_c *fnp = (vfs_sfs_file_node_c *)instance;

  (void)fnp;
  (void)buf;
  (void)n;

  return (ssize_t)0;
}

static msg_t node_file_setpos(void *instance, vfs_offset_t offset) {
  vfs_sfs_file_node_c *fnp = (vfs_sfs_file_node_c *)instance;

  (void)fnp;
  (void)offset;

  return VFS_RET_SUCCESS;
}

static vfs_offset_t node_file_getpos(void *instance) {
  vfs_sfs_file_node_c *fnp = (vfs_sfs_file_node_c *)instance;

  (void)fnp;

  return (vfs_offset_t)0;
}

static vfs_offset_t node_file_getsize(void *instance) {
  vfs_sfs_file_node_c *fnp = (vfs_sfs_file_node_c *)instance;

  (void)fnp;

  return (vfs_offset_t)0;
}

static size_t file_stream_write(void *instance, const uint8_t *bp, size_t n) {
  vfs_sfs_file_node_c *fnp = objGetInstance(vfs_sfs_file_node_c *,
                                            (BaseSequentialStream *)instance);
  msg_t msg;

  msg = fnp->vmt->file_write((void *)fnp, bp, n);
  if (msg < VFS_RET_SUCCESS) {

    return (size_t)0;
  }

  return (size_t)msg;
}

static size_t file_stream_read(void *instance, uint8_t *bp, size_t n) {
  vfs_sfs_file_node_c *fnp = objGetInstance(vfs_sfs_file_node_c *,
                                            (BaseSequentialStream *)instance);
  msg_t msg;

  msg = fnp->vmt->file_read((void *)fnp, bp, n);
  if (msg < VFS_RET_SUCCESS) {

    return (size_t)0;
  }

  return (size_t)msg;
}

static msg_t file_stream_put(void *instance, uint8_t b) {
  vfs_sfs_file_node_c *fnp = objGetInstance(vfs_sfs_file_node_c *,
                                            (BaseSequentialStream *)instance);
  msg_t msg;

  msg = fnp->vmt->file_write((void *)fnp, &b, (size_t)1);
  if (msg < VFS_RET_SUCCESS) {

    return STM_TIMEOUT;
  }

  return msg;
}

static msg_t file_stream_get(void *instance) {
  vfs_sfs_file_node_c *fnp = objGetInstance(vfs_sfs_file_node_c *,
                                            (BaseSequentialStream *)instance);
  msg_t msg;
  uint8_t b;

  msg = fnp->vmt->file_read((void *)fnp, &b, (size_t)1);
  if (msg < VFS_RET_SUCCESS) {

    return STM_TIMEOUT;
  }

  return (msg_t)b;
}

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Module initialization.
 *
 * @notapi
 */
void __drv_sfs_init(void) {

  /* Initializing pools.*/
  chPoolObjectInit(&vfs_sfs_driver_static.dir_nodes_pool,
                   sizeof (vfs_sfs_dir_node_c),
                   chCoreAllocAlignedI);
  chPoolObjectInit(&vfs_sfs_driver_static.file_nodes_pool,
                   sizeof (vfs_sfs_file_node_c),
                   chCoreAllocAlignedI);

  /* Preloading pools.*/
  chPoolLoadArray(&vfs_sfs_driver_static.dir_nodes_pool,
                  &vfs_sfs_driver_static.dir_nodes[0],
                  DRV_CFG_SFS_DIR_NODES_NUM);
  chPoolLoadArray(&vfs_sfs_driver_static.file_nodes_pool,
                  &vfs_sfs_driver_static.file_nodes[0],
                  DRV_CFG_SFS_FILE_NODES_NUM);
}

/**
 * @brief   VFS FatFS object initialization.
 *
 * @param[out] drvp     pointer to a @p vfs_sfs_driver_c structure
 * @param[in] rootname  name to be attributed to this object
 * @return              A pointer to this initialized object.
 *
 * @api
 */
vfs_driver_c *drvSFSObjectInit(vfs_sfs_driver_c *drvp,
                               const char *rootname) {

  __base_object_objinit_impl(drvp, &driver_vmt);
  drvp->rootname = rootname;

  return (vfs_driver_c *)drvp;
}

#endif /* VFS_CFG_ENABLE_DRV_SFS == TRUE */

/** @} */
