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

/* This is an, automatically generated, implementation file that can be
   manually edited, it is not re-generated if already present.*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/
void __stmdir_bo_dispose_impl(void *ip) {

  /* Disposing self.*/
  __ro_dispose_impl(ip);

  /* Last because it corrupts the object.*/
  chPoolFree(&vfs_streams_driver_static.dir_nodes_pool, ip);
}

void *__stmdir_ro_addref_impl(void *ip) {

  chSysLock();
  ip = __ro_addref_impl(ip);
  chSysUnlock();

  return ip;
}

object_references_t __stmdir_ro_release_impl(void *ip) {
  object_references_t references;

  chSysLock();
  references = __ro_release_impl(ip);
  chSysUnlock();

  return references;
}

msg_t __stmdir_vfsnode_stat_impl(void *ip, vfs_stat_t *sp) {

  return __vfsnode_stat_impl(ip, sp);
}

msg_t __stmdir_vfsdir_next_impl(void *ip, vfs_direntry_info_t *dip) {
  vfs_streams_dir_node_c *sdnp = (vfs_streams_dir_node_c *)ip;
  vfs_streams_driver_c *vsdp = (vfs_streams_driver_c *)sdnp->vfsnode.driver;

  if (vsdp->stmdrv.streams[sdnp->stmdir.index].name != NULL) {

    dip->mode = VFS_MODE_S_IFIFO | VFS_MODE_S_IRUSR | VFS_MODE_S_IWUSR;
    dip->size = (vfs_offset_t)0;
    strcpy(dip->name, vsdp->stmdrv.streams[sdnp->stmdir.index].name);

    sdnp->stmdir.index++;

    return (msg_t)1;
  }

  return (msg_t)0;
}

msg_t __stmdir_vfsdir_first_impl(void *ip, vfs_direntry_info_t *dip) {
  vfs_streams_dir_node_c *sdnp = (vfs_streams_dir_node_c *)ip;

  sdnp->stmdir.index = 0U;

  return __stmdir_vfsdir_next_impl(ip, dip);
}

void __stmfile_bo_dispose_impl(void *ip) {

  /* Disposing self.*/
  __ro_dispose_impl(ip);

  /* Last because it corrupts the object.*/
  chPoolFree(&vfs_streams_driver_static.file_nodes_pool, ip);
}

void *__stmfile_ro_addref_impl(void *ip) {

  chSysLock();
  ip = __ro_addref_impl(ip);
  chSysUnlock();

  return ip;
}

object_references_t __stmfile_ro_release_impl(void *ip) {
  object_references_t references;

  chSysLock();
  references = __ro_release_impl(ip);
  chSysUnlock();

  return references;
}

msg_t __stmfile_vfsnode_stat_impl(void *ip, vfs_stat_t *sp) {

  return __vfsnode_stat_impl(ip, sp);
}

ssize_t __stmfile_vfsfile_read_impl(void *ip, uint8_t *buf, size_t size) {
  vfs_streams_file_node_c *sfnp = (vfs_streams_file_node_c *)ip;

  return stmRead(sfnp->stmfile.stm, buf, size);
}

ssize_t __stmfile_vfsfile_write_impl(void *ip, const uint8_t *buf,
                                    size_t size) {
  vfs_streams_file_node_c *sfnp = (vfs_streams_file_node_c *)ip;

  return stmWrite(sfnp->stmfile.stm, buf, size);
}

msg_t __stmfile_vfsfile_setpos_impl(void *ip, vfs_offset_t offset,
                                    vfs_seekmode_t whence) {

  return __vfsfile_setpos_impl(ip, offset, whence);
}

vfs_offset_t __stmfile_vfsfile_getpos_impl(void *ip) {

  return __vfsfile_getpos_impl(ip);
}

sequential_stream_i *__stmfile_vfsfile_getstream_impl(void *ip) {
  vfs_streams_file_node_c *sfnp = (vfs_streams_file_node_c *)ip;

  return sfnp->stmfile.stm;
}

void __stmdrv_bo_dispose_impl(void *ip) {

  /* Disposing self.*/
  __ro_dispose_impl(ip);
}

msg_t __stmdrv_vfsdrv_setcwd_impl(void *ip, const char *path) {

  return __vfsdrv_setcwd_impl(ip, path);
}

msg_t __stmdrv_vfsdrv_getcwd_impl(void *ip, char *buf, size_t size) {

  return __vfsdrv_getcwd_impl(ip, buf, size);
}

msg_t __stmdrv_vfsdrv_stat_impl(void *ip, const char *path,
                                vfs_stat_t *sp) {
  msg_t ret;

  (void)ip;

  do {
    ret = vfs_parse_match_separator(&path);
    CH_BREAK_ON_ERROR(ret);

    ret = vfs_parse_match_end(&path);
    CH_BREAK_ON_ERROR(ret);

    sp->mode = VFS_MODE_S_IFDIR;
    sp->size = (vfs_offset_t)0;

    ret = CH_RET_SUCCESS;
  }
  while (false);

  return ret;
}

msg_t __stmdrv_vfsdrv_opendir_impl(void *ip, const char *path,
                                    vfs_directory_node_c **vdnpp) {
  vfs_streams_driver_c *drvp = (vfs_streams_driver_c *)ip;
  msg_t ret;

  do {
    vfs_streams_dir_node_c *sdnp;

    ret = vfs_parse_match_separator(&path);
    CH_BREAK_ON_ERROR(ret);

    ret = vfs_parse_match_end(&path);
    CH_BREAK_ON_ERROR(ret);

    sdnp = chPoolAlloc(&vfs_streams_driver_static.dir_nodes_pool);
    if (sdnp != NULL) {

      /* Node object initialization.*/
      (void) stmdirObjectInit(sdnp,
                              (vfs_driver_c *)drvp,
                              VFS_MODE_S_IFDIR | VFS_MODE_S_IRUSR);
/*      __ro_objinit_impl(sdnp, &dir_node_vmt);
      sdnp->vfsnode.driver  = (vfs_driver_c *)drvp;
      sdnp->vfsnode.mode    = VFS_MODE_S_IFDIR | VFS_MODE_S_IRUSR;
      sdnp->stmdir.index           = 0U;*/

      *vdnpp = (vfs_directory_node_c *)sdnp;
      return CH_RET_SUCCESS;
    }

    ret = CH_RET_ENOMEM;
  }
  while (false);

  return ret;
}

msg_t __stmdrv_vfsdrv_openfile_impl(void *ip, const char *path,
                                    int flags, vfs_file_node_c **vfnpp) {
  vfs_streams_driver_c *drvp = (vfs_streams_driver_c *)ip;
  const drv_streams_element_t *dsep;
  msg_t ret;

  (void)flags; /* TODO  handle invalid modes.*/

  do {
    char fname[VFS_CFG_NAMELEN_MAX + 1]; /* TODO remove automatic buffer.*/

    ret = vfs_parse_match_separator(&path);
    CH_BREAK_ON_ERROR(ret);

    ret = (msg_t)vfs_path_get_element(&path, fname, VFS_CFG_NAMELEN_MAX + 1);
    CH_BREAK_ON_ERROR(ret);

    /* Null element.*/
    if (ret == (msg_t)0) {
      /* Trying to open the root as a file.*/
      ret = CH_RET_EISDIR;
      break;
    }

    ret = vfs_parse_match_end(&path);
    CH_BREAK_ON_ERROR(ret);

    dsep = &drvp->stmdrv.streams[0];
    while (dsep->name != NULL) {
      if (strncmp(fname, dsep->name, VFS_CFG_NAMELEN_MAX) == 0) {
        vfs_streams_file_node_c *sfnp;

        sfnp = chPoolAlloc(&vfs_streams_driver_static.file_nodes_pool);
        if (sfnp != NULL) {

          /* Node object initialization.*/
          (void) stmfileObjectInit(sfnp,
                                   (vfs_driver_c *)drvp,
                                   VFS_MODE_S_IFIFO | VFS_MODE_S_IRUSR | VFS_MODE_S_IWUSR,
                                   dsep->stm);
/*          __ro_objinit_impl(sfnp, &file_node_vmt);
          sfnp->vfsnode.driver  = (vfs_driver_c *)drvp;
          sfnp->vfsnode.mode    = VFS_MODE_S_IFIFO | VFS_MODE_S_IRUSR | VFS_MODE_S_IWUSR;
          sfnp->stream  = dsep->stream;*/

          *vfnpp = (vfs_file_node_c *)sfnp;
          return CH_RET_SUCCESS;
        }

        return CH_RET_ENOMEM;
      }

      dsep++;
    }

    ret = CH_RET_ENOENT;
  }
  while (false);

  return ret;
}

msg_t __stmdrv_vfsdrv_unlink_impl(void *ip, const char *path) {

  return __vfsdrv_unlink_impl(ip, path);
}

msg_t __stmdrv_vfsdrv_rename_impl(void *ip, const char *oldpath,
                                const char *newpath) {

  return __vfsdrv_rename_impl(ip, oldpath, newpath);
}

msg_t __stmdrv_vfsdrv_mkdir_impl(void *ip, const char *path,
                                vfs_mode_t mode) {

  return __vfsdrv_mkdir_impl(ip, path, mode);
}

msg_t __stmdrv_vfsdrv_rmdir_impl(void *ip, const char *path) {

  return __vfsdrv_rmdir_impl(ip, path);
}

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

