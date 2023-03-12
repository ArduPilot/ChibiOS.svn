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

/* This is an included part of drvstreams.c, must not be compiled alone.*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

void *__stmdir_ro_addref_impl(void *ip) {

  return __ro_addref_impl(ip);
}

object_references_t __stmdir_ro_release_impl(void *ip) {
  vfs_streams_dir_node_c *sdnp = (vfs_streams_dir_node_c *)ip;
  object_references_t references;

  chSysLock();
  references = __ro_release_impl(ip);
  chSysUnlock();
  if (references == 0U) {
    chPoolFree(&vfs_streams_driver_static.dir_nodes_pool, (void *)sdnp);
  }

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

void *__stmfile_ro_addref_impl(void *ip) {

  return __ro_addref_impl(ip);
}

object_references_t __stmfile_ro_release_impl(void *ip) {
  vfs_streams_file_node_c *sfnp = (vfs_streams_file_node_c *)ip;
  object_references_t references;

  chSysLock();
  references = __ro_release_impl(ip);
  chSysUnlock();
  if (references == 0U) {
    chPoolFree(&vfs_streams_driver_static.file_nodes_pool, (void *)sfnp);
  }

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
