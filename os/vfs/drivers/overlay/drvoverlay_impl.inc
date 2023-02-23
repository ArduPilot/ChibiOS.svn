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

/* This is an included part of drvoverlay.c, must not be compiled alone.*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

static msg_t match_driver(vfs_overlay_driver_c *odp,
                          const char **pathp,
                          vfs_driver_c **vdpp) {
  unsigned i;

  i = 0U;
  while (i < odp->ovldrv.next_driver) {
    size_t n;

    n = path_match_element(*pathp, odp->ovldrv.names[i], VFS_CFG_NAMELEN_MAX + 1);
    if (n < VFS_CFG_NAMELEN_MAX + 1) {
      *pathp += n;
      *vdpp = odp->ovldrv.drivers[i];
      return CH_RET_SUCCESS;
    }

    i++;
  }

  return CH_RET_ENOENT;
}

static const char *get_current_directory(vfs_overlay_driver_c *drvp) {
  const char *cwd = drvp->ovldrv.path_cwd;

  /* In case it has not yet been defined using root.*/
  if (cwd == NULL) {
    return "/";
  }

  return cwd;
}

static msg_t build_absolute_path(vfs_overlay_driver_c *drvp,
                                 char *buf,
                                 const char *path) {
  msg_t ret;

  do {

    /* Initial buffer state, empty string.*/
    *buf = '\0';

    /* Relative paths handling.*/
    if (!path_is_separator(*path)) {
      if (path_append(buf,
                      get_current_directory(drvp),
                      VFS_CFG_PATHLEN_MAX + 1) == (size_t)0) {
        ret = CH_RET_ENAMETOOLONG;
        break;
      }
    }

    /* Adding the specified path.*/
    if (path_append(buf, path, VFS_CFG_PATHLEN_MAX + 1) == (size_t)0) {
      ret = CH_RET_ENAMETOOLONG;
      break;
    }

    /* Normalization of the absolute path.*/
    if (path_normalize(buf, buf, VFS_CFG_PATHLEN_MAX + 1) == (size_t)0) {
      ret = CH_RET_ENAMETOOLONG;
      break;
    }

    ret = CH_RET_SUCCESS;

  } while (false);

  return ret;
}

static msg_t open_absolute_dir(vfs_overlay_driver_c *drvp,
                               char *path,
                               vfs_directory_node_c **vdnpp) {
  msg_t ret;

  do {
    const char *scanpath;

    /* Making sure there is a final separator.*/
    if (path_add_separator(path, VFS_CFG_PATHLEN_MAX + 1) == (size_t)0) {
      ret = CH_RET_ENAMETOOLONG;
      break;
    }

    /* Initial separator is expected, skipping it.*/
    scanpath = path + 1;

    /* If it is the root.*/
    if (*scanpath == '\0') {
      vfs_overlay_dir_node_c *odnp;

      /* Creating a root directory node.*/
      odnp = chPoolAlloc(&vfs_overlay_driver_static.dir_nodes_pool);
      if (odnp != NULL) {

        /* Node object initialization.*/
        (void) ovldirObjectInit(odnp, drvp, VFS_MODE_S_IFDIR | VFS_MODE_S_IRUSR);
/*        __referenced_object_objinit_impl(odnp, &dir_node_vmt);
        odnp->vfsnode.driver       = (vfs_driver_c *)drvp;
        odnp->vfsnode.mode         = VFS_MODE_S_IFDIR | VFS_MODE_S_IRUSR;
        odnp->ovldir.index         = 0U;
        odnp->ovldir.overlaid_root = NULL;*/

        /* Trying to obtain a root node from the overlaid driver, it
           could fail, in that case the pointer stays at NULL.*/
        if (drvp->ovldrv.overlaid_drv != NULL) {
          (void) vfsDrvOpenDirectory((void *)drvp->ovldrv.overlaid_drv,
                                     drvp->ovldrv.path_prefix == NULL ? "/" : drvp->ovldrv.path_prefix,
                                     &odnp->ovldir.overlaid_root);
/*          (void) drvp->ovldrv.overlaid_drv->vmt->vfsdrv.opendir((void *)drvp->ovldrv.overlaid_drv,
                                                   drvp->ovldrv.path_prefix == NULL ? "/" : drvp->ovldrv.path_prefix,
                                                   &odnp->ovldir.overlaid_root);*/
        }
        *vdnpp = (vfs_directory_node_c *)odnp;

        ret = CH_RET_SUCCESS;
        break;
      }
      else {
        ret = CH_RET_ENOMEM;
        break;
      }
    }
    else { /* Not the root.*/
      vfs_driver_c *dp;

      /* Searching for a match among registered overlays.*/
      ret = match_driver(drvp, &scanpath, &dp);
      if (!CH_RET_IS_ERROR(ret)) {
        /* Delegating node creation to a registered driver.*/
        ret = vfsDrvOpenDirectory((void *)dp,
                                  *scanpath == '\0' ? "/" : scanpath,
                                  vdnpp);
/*        ret = dp->vmt->vfsdrv.opendir((void *)dp,
                                *scanpath == '\0' ? "/" : scanpath,
                                vdnpp);*/
      }
      else {
        size_t path_offset;

        /* Is there an overlaid driver? if so we need to pass request
           processing there.*/
        if (drvp->ovldrv.overlaid_drv != NULL) {

          /* Processing the prefix, if defined.*/
          if (drvp->ovldrv.path_prefix != NULL) {
            if ((path_offset = path_prepend(path,
                                            drvp->ovldrv.path_prefix,
                                            VFS_CFG_PATHLEN_MAX + 1)) == (size_t)0) {
              ret = CH_RET_ENAMETOOLONG;
              break;
            }
          }
          else {
            path_offset = 0U;
          }

          /* Passing the combined path to the overlaid driver.*/
          ret = vfsDrvOpenDirectory((void *)drvp->ovldrv.overlaid_drv,
                                    path,
                                    vdnpp);
/*          ret = drvp->ovldrv.overlaid_drv->vmt->vfsdrv.opendir((void *)drvp->ovldrv.overlaid_drv,
                                                  path,
                                                  vdnpp);*/
          CH_BREAK_ON_ERROR(ret);

          ret = (msg_t)path_offset;
        }
      }
    }
  }
  while (false);

  return ret;
}

static msg_t open_absolute_file(vfs_overlay_driver_c *drvp,
                                char *path,
                                int oflag,
                                vfs_file_node_c **vfnpp) {
  msg_t ret;

  do {
    const char *scanpath;

    /* Initial separator is expected, skipping it.*/
    scanpath = path + 1;

    /* If it is the root.*/
    if (*scanpath == '\0') {

      /* Always not found, root is not a file.*/
      ret = CH_RET_EISDIR;
    }
    else {
      vfs_driver_c *dp;

      /* Searching for a match among registered overlays.*/
      ret = match_driver(drvp, &scanpath, &dp);
      if (!CH_RET_IS_ERROR(ret)) {
        /* Delegating node creation to a registered driver, making sure it
           does not receive an empty path.*/
        ret = vfsDrvOpenFile((void *)dp, *scanpath == '\0' ? "/" : scanpath, oflag, vfnpp);
/*        ret = dp->vmt->vfsdrv.openfile((void *)dp,
                                 *scanpath == '\0' ? "/" : scanpath,
                                 oflag, vfnpp);*/
      }
      else {
        /* Is there an overlaid driver? if so we need to pass request
           processing there.*/
        if (drvp->ovldrv.overlaid_drv != NULL) {

          /* Processing the prefix, if defined.*/
          if (drvp->ovldrv.path_prefix != NULL) {
            if (path_prepend(path,
                             drvp->ovldrv.path_prefix,
                             VFS_CFG_PATHLEN_MAX + 1) == (size_t)0) {
              ret = CH_RET_ENAMETOOLONG;
              break;
            }
          }

          /* Passing the combined path to the overlaid driver.*/
          ret = vfsDrvOpenFile((void *)drvp->ovldrv.overlaid_drv, path, oflag, vfnpp);
/*          ret = drvp->ovldrv.overlaid_drv->vmt->vfsdrv.openfile((void *)drvp->ovldrv.overlaid_drv,
                                                   path,
                                                   oflag,
                                                   vfnpp);*/
        }
      }
    }
  }
  while (false);

  return ret;
}

static msg_t drv_overlaid_path_call(vfs_overlay_driver_c *drvp,
                                    char *buf,
                                    msg_t (*fn)(void *ip, const char *path)) {
  msg_t ret;

  do {
    /* Is there an overlaid driver? if so we need to pass request
       processing there.*/
    if (drvp->ovldrv.overlaid_drv != NULL) {

      /* Processing the prefix, if defined.*/
      if (drvp->ovldrv.path_prefix != NULL) {
        if (path_prepend(buf,
                         drvp->ovldrv.path_prefix,
                         VFS_CFG_PATHLEN_MAX + 1) == (size_t)0) {
          ret = CH_RET_ENAMETOOLONG;
          break;
        }
      }

      /* Passing the combined path to the overlaid driver.*/
      ret = fn((void *)drvp->ovldrv.overlaid_drv, buf);
    }
    else {
      ret = CH_RET_ENOENT;
    }
  } while (false);

  return ret;
}

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

void *__ovldir_ro_addref_impl(void *ip) {

  return __ro_addref_impl(ip);
}

object_references_t __ovldir_ro_release_impl(void *ip) {
  vfs_overlay_dir_node_c *odnp = (vfs_overlay_dir_node_c *)ip;
  object_references_t references;

  chSysLock();
  references = __ro_release_impl(ip);
  chSysUnlock();
  if (references == 0U) {

    if (odnp->ovldir.overlaid_root != NULL) {
      (void) __ro_release_impl((void *)odnp->ovldir.overlaid_root);
/*      odnp->overlaid_root->vmt->release((void *)odnp->overlaid_root);*/
    }

    chPoolFree(&vfs_overlay_driver_static.dir_nodes_pool, (void *)odnp);
  }

  return references;
}

msg_t __ovldir_vfsnode_stat_impl(void *ip, vfs_stat_t *sp) {

  return __vfsnode_stat_impl(ip, sp); /* TODO */
}

msg_t __ovldir_vfsdir_next_impl(void *ip, vfs_direntry_info_t *dip) {
  vfs_overlay_dir_node_c *odnp = (vfs_overlay_dir_node_c *)ip;
  vfs_overlay_driver_c *drvp = (vfs_overlay_driver_c *)odnp->vfsnode.driver;

  if (odnp->ovldir.index < drvp->ovldrv.next_driver) {
    dip->mode   = VFS_MODE_S_IFDIR | VFS_MODE_S_IRUSR;
    dip->size   = (vfs_offset_t)0;
    strcpy(dip->name, drvp->ovldrv.names[odnp->ovldir.index]);

    odnp->ovldir.index++;

    return (msg_t)1;
  }
  if (odnp->ovldir.overlaid_root != NULL) {
    if (odnp->ovldir.index == drvp->ovldrv.next_driver) {

      odnp->ovldir.index++;

      return vfsDirReadFirst((void *)odnp->ovldir.overlaid_root, dip);
/*      return odnp->ovldir.overlaid_root->vmt->vfsdir.first((void *)odnp->ovldir.overlaid_root,
                                                 dip);*/
    }
    if (odnp->ovldir.index > drvp->ovldrv.next_driver) {

      return vfsDirReadNext((void *)odnp->ovldir.overlaid_root, dip);
/*      return odnp->ovldir.overlaid_root->vmt->vfsdir.next((void *)odnp->ovldir.overlaid_root,
                                                dip);*/
    }
  }

  return (msg_t)0;
}

msg_t __ovldir_vfsdir_first_impl(void *ip, vfs_direntry_info_t *dip) {
  vfs_overlay_dir_node_c *odnp = (vfs_overlay_dir_node_c *)ip;

  odnp->ovldir.index = 0U;

  return __ovldir_vfsdir_next_impl(ip, dip);
}

msg_t __ovldrv_vfsdrv_setcwd_impl(void *ip, const char *path) {
  vfs_shared_buffer_t *shbuf;
  msg_t ret;

  /* Taking a path buffer from the pool.*/
  shbuf = vfs_buffer_take();

  do {
    vfs_overlay_driver_c *drvp = (vfs_overlay_driver_c *)ip;
    vfs_directory_node_c *vdnp;
    size_t path_offset;

    ret = build_absolute_path(drvp, shbuf->path.buf1, path);
    CH_BREAK_ON_ERROR(ret);

    /* Trying to access the directory in order to validate the
       combined path. Note, it can modify the path in the buffer.*/
    ret = open_absolute_dir(drvp, shbuf->path.buf1, &vdnp);
    CH_BREAK_ON_ERROR(ret);
    roRelease((void *)vdnp);
/*    vdnp->vmt->release((void *)vdnp);*/
    path_offset = (size_t)ret;

    /* One-time allocation of the CWD buffer, this memory is allocated, once,
       only if the application uses a CWD, it is never released.*/
    if (drvp->ovldrv.path_cwd == NULL) {
      drvp->ovldrv.path_cwd = chCoreAlloc(VFS_CFG_PATHLEN_MAX + 1);
      if (drvp->ovldrv.path_cwd == NULL) {
        ret = CH_RET_ENOMEM;
        break;
      }
    }

    /* Copying the validated path into the CWD buffer.*/
    strcpy(drvp->ovldrv.path_cwd, shbuf->path.buf1 + path_offset);

  } while (false);

  /* Buffer returned.*/
  vfs_buffer_release(shbuf);

  return ret;
}

msg_t __ovldrv_vfsdrv_getcwd_impl(void *ip, char *buf, size_t size) {
  vfs_overlay_driver_c *drvp = (vfs_overlay_driver_c *)ip;

  *buf = '\0';
  if (path_append(buf, get_current_directory(drvp), size) == (size_t)0) {
    return CH_RET_ERANGE;
  }

  return CH_RET_SUCCESS;
}

msg_t __ovldrv_vfsdrv_stat_impl(void *ip, const char *path,
                                vfs_stat_t *sp) {
  vfs_shared_buffer_t *shbuf;
  msg_t ret;

  /* Taking a path buffer from the pool.*/
  shbuf = vfs_buffer_take();

  do {
    vfs_overlay_driver_c *drvp = (vfs_overlay_driver_c *)ip;
    const char *scanpath;

    /* Building the absolute path based on current directory.*/
    ret = build_absolute_path(drvp, shbuf->path.buf1, path);
    CH_BREAK_ON_ERROR(ret);

    /* Skipping the root separator.*/
    scanpath = shbuf->path.buf1 + 1;

    /* If it is not root checking among mounted drivers.*/
    if (*scanpath != '\0') {
      vfs_driver_c *dp;

      /* Searching for a match among registered overlays.*/
      ret = match_driver(drvp, &scanpath, &dp);
      if (!CH_RET_IS_ERROR(ret)) {
        /* Delegating directory creation to a registered driver.*/
        ret = vfsDrvStat((void *)dp, scanpath, sp);
/*        ret = dp->vmt->stat((void *)dp, scanpath, sp);*/
        break;
      }
    }

    /* Is there an overlaid driver? if so we need to pass request
       processing there.*/
    if (drvp->ovldrv.overlaid_drv != NULL) {

      /* Processing the prefix, if defined.*/
      if (drvp->ovldrv.path_prefix != NULL) {
        if (path_prepend(shbuf->path.buf1,
                         drvp->ovldrv.path_prefix,
                         VFS_CFG_PATHLEN_MAX + 1) == (size_t)0) {
          ret = CH_RET_ENAMETOOLONG;
          break;
        }
      }

      /* Passing the combined path to the overlaid driver.*/
      ret = vfsDrvStat((void *)drvp->ovldrv.overlaid_drv, shbuf->path.buf1, sp);
/*      ret = drvp->overlaid_drv->vmt->stat((void *)drvp->overlaid_drv,
                                          shbuf->path.buf1, sp);*/
    }
    else {
      ret = CH_RET_ENOENT;
    }
  } while (false);

  /* Buffer returned.*/
  vfs_buffer_release(shbuf);

  return ret;
}

msg_t __ovldrv_vfsdrv_opendir_impl(void *ip, const char *path,
                                   vfs_directory_node_c **vdnpp) {
  vfs_shared_buffer_t *shbuf;
  msg_t ret;

  /* Taking a path buffer from the pool.*/
  shbuf = vfs_buffer_take();

  do {
    vfs_overlay_driver_c *drvp = (vfs_overlay_driver_c *)ip;

    /* Building the absolute path based on current directory.*/
    ret = build_absolute_path(drvp, shbuf->path.buf1, path);
    CH_BREAK_ON_ERROR(ret);

    ret = open_absolute_dir(drvp, shbuf->path.buf1, vdnpp);
    CH_BREAK_ON_ERROR(ret);

    /* Required because the offset returned by open_absolute_dir().*/
    ret = CH_RET_SUCCESS;
  } while (false);

  /* Buffer returned.*/
  vfs_buffer_release(shbuf);

  return ret;
}

msg_t __ovldrv_vfsdrv_openfile_impl(void *ip, const char *path,
                                    int flags, vfs_file_node_c **vfnpp) {
  vfs_shared_buffer_t *shbuf;
  msg_t ret;

  /* Taking a path buffer from the pool.*/
  shbuf = vfs_buffer_take();

  do {
    vfs_overlay_driver_c *drvp = (vfs_overlay_driver_c *)ip;

    /* Building the absolute path based on current directory.*/
    ret = build_absolute_path(drvp, shbuf->path.buf1, path);
    CH_BREAK_ON_ERROR(ret);

    ret = open_absolute_file(drvp, shbuf->path.buf1, flags, vfnpp);
  } while (false);

  /* Buffer returned.*/
  vfs_buffer_release(shbuf);

  return ret;
}

msg_t __ovldrv_vfsdrv_unlink_impl(void *ip, const char *path) {
  vfs_shared_buffer_t *shbuf;
  msg_t ret;

  /* Taking a path buffer from the pool.*/
  shbuf = vfs_buffer_take();

  do {
    vfs_overlay_driver_c *drvp = (vfs_overlay_driver_c *)ip;
    const char *scanpath;

    /* Building the absolute path based on current directory.*/
    ret = build_absolute_path(drvp, shbuf->path.buf1, path);
    CH_BREAK_ON_ERROR(ret);

    /* Skipping the root separator.*/
    scanpath = shbuf->path.buf1 + 1;

    /* If it is the root.*/
    if (*scanpath == '\0') {
      ret = CH_RET_EISDIR;
    }
    else { /* Not the root.*/
      vfs_driver_c *dp;

      /* Searching for a match among registered overlays.*/
      ret = match_driver(drvp, &scanpath, &dp);
      if (!CH_RET_IS_ERROR(ret)) {
        /* Delegating file deletion to a registered driver.*/
        ret = vfsDrvUnlink((void *)dp, scanpath);
/*        ret = dp->vmt->unlink((void *)dp, scanpath);*/
      }
      else {
        /* Passing the request to the overlaid driver, if any.*/
        /* TODO remove the dirty trick.*/
        ret = drv_overlaid_path_call(drvp, shbuf->path.buf1,
                                     drvp->ovldrv.overlaid_drv->vmt->vfsdrv.unlink);
      }
    }
  } while (false);

  /* Buffer returned.*/
  vfs_buffer_release(shbuf);

  return ret;
}

msg_t __ovldrv_vfsdrv_rename_impl(void *ip, const char *oldpath,
                                  const char *newpath) {
  msg_t ret;
  vfs_shared_buffer_t *shbuf;

  /* Taking a path buffer from the pool.*/
  shbuf = vfs_buffer_take();

  do {
    msg_t oldret, newret;
    vfs_overlay_driver_c *drvp = (vfs_overlay_driver_c *)ip;
    vfs_driver_c *olddp, *newdp;
    const char *op, *np;

    /* Building the absolute paths based on current directory.*/
    ret = build_absolute_path(drvp, shbuf->path.buf1, oldpath);
    CH_BREAK_ON_ERROR(ret);
    ret = build_absolute_path(drvp, shbuf->path.buf2, newpath);
    CH_BREAK_ON_ERROR(ret);

    /* Skipping root separators.*/
    op = shbuf->path.buf1 + 1;
    np = shbuf->path.buf2 + 1;

    /* Searching for a match among registered drivers.*/
    oldret = match_driver(drvp, &op, &olddp);
    newret = match_driver(drvp, &np, &newdp);

    /* There are various combinations to consider.*/
    if (!CH_RET_IS_ERROR(oldret) && !CH_RET_IS_ERROR(newret)) {
       /* If paths both refer to registered drivers then must refer to
          the same driver, we cannot do a rename across drivers.*/
      if (olddp == newdp) {
        /* Delegating node renaming to the registered driver.*/
        ret = vfsDrvRename((void *)olddp, op, np);
/*        ret = olddp->vmt->rename((void *)olddp, op, np);*/
      }
      else {
        /* Mixed, not allowing it.*/
        ret = CH_RET_EXDEV;
      }
    }
    else if (CH_RET_IS_ERROR(oldret) && CH_RET_IS_ERROR(newret)) {
      /* If both paths refer to the overlaid driver then passing down the
         request.*/
      if (drvp->ovldrv.overlaid_drv != NULL) {

        /* Processing the prefix, if defined.*/
        if (drvp->ovldrv.path_prefix != NULL) {
          if (path_prepend(shbuf->path.buf1,
                           drvp->ovldrv.path_prefix,
                           VFS_CFG_PATHLEN_MAX + 1) == (size_t)0) {
            ret = CH_RET_ENAMETOOLONG;
            break;
          }
          if (path_prepend(shbuf->path.buf2,
                           drvp->ovldrv.path_prefix,
                           VFS_CFG_PATHLEN_MAX + 1) == (size_t)0) {
            ret = CH_RET_ENAMETOOLONG;
            break;
          }
        }

        /* Passing the combined path to the overlaid driver.*/
        ret = vfsDrvRename((void *)drvp->ovldrv.overlaid_drv,
                           shbuf->path.buf1,
                           shbuf->path.buf2);
/*        ret = drvp->overlaid_drv->vmt->rename((void *)drvp->overlaid_drv,
                                              shbuf->path.buf1,
                                              shbuf->path.buf2);*/
      }
    }
    else {
      /* Mixed, not allowing it.*/
      ret = CH_RET_EXDEV;
    }
  } while (false);

  /* Buffers returned, note, in reverse order.*/
  vfs_buffer_release(shbuf);

  return ret;
}

msg_t __ovldrv_vfsdrv_mkdir_impl(void *ip, const char *path,
                                 vfs_mode_t mode) {
  vfs_shared_buffer_t *shbuf;
  msg_t ret;

  /* Taking a path buffer from the pool.*/
  shbuf = vfs_buffer_take();

  do {
    vfs_overlay_driver_c *drvp = (vfs_overlay_driver_c *)ip;
    const char *scanpath;

    /* Building the absolute path based on current directory.*/
    ret = build_absolute_path(drvp, shbuf->path.buf1, path);
    CH_BREAK_ON_ERROR(ret);

    /* Skipping the root separator.*/
    scanpath = shbuf->path.buf1 + 1;

    /* If it is the root.*/
    if (*scanpath == '\0') {
      ret = CH_RET_EEXIST;
    }
    else { /* Not the root.*/
      vfs_driver_c *dp;

      /* Searching for a match among registered overlays.*/
      ret = match_driver(drvp, &scanpath, &dp);
      if (!CH_RET_IS_ERROR(ret)) {
        /* Delegating directory creation to a registered driver.*/
        ret = vfsDrvMkdir((void *)dp, scanpath, mode);
/*        ret = dp->vmt->mkdir((void *)dp, scanpath, mode);*/
      }
      else {
        /* Is there an overlaid driver? if so we need to pass request
           processing there.*/
        if (drvp->ovldrv.overlaid_drv != NULL) {

          /* Processing the prefix, if defined.*/
          if (drvp->ovldrv.path_prefix != NULL) {
            if (path_prepend(shbuf->path.buf1,
                             drvp->ovldrv.path_prefix,
                             VFS_CFG_PATHLEN_MAX + 1) == (size_t)0) {
              ret = CH_RET_ENAMETOOLONG;
              break;
            }
          }

          /* Passing the combined path to the overlaid driver.*/
          ret = vfsDrvMkdir((void *)drvp->ovldrv.overlaid_drv, shbuf->path.buf1, mode);
/*          ret = drvp->overlaid_drv->vmt->mkdir((void *)drvp->overlaid_drv,
                                               shbuf->path.buf1, mode);*/
        }
        else {
          ret = CH_RET_ENOENT;
        }
      }
    }
  } while (false);

  /* Buffer returned.*/
  vfs_buffer_release(shbuf);

  return ret;
}

msg_t __ovldrv_vfsdrv_rmdir_impl(void *ip, const char *path) {
  vfs_shared_buffer_t *shbuf;
  msg_t ret;

  /* Taking a path buffer from the pool.*/
  shbuf = vfs_buffer_take();

  do {
    vfs_overlay_driver_c *drvp = (vfs_overlay_driver_c *)ip;
    const char *scanpath;

    /* Building the absolute path based on current directory.*/
    ret = build_absolute_path(drvp, shbuf->path.buf1, path);
    CH_BREAK_ON_ERROR(ret);

    /* Skipping the root separator.*/
    scanpath = shbuf->path.buf1 + 1;

    /* If it is the root.*/
    if (*scanpath == '\0') {
      ret = CH_RET_EACCES;
    }
    else { /* Not the root.*/
      vfs_driver_c *dp;

      /* Searching for a match among registered overlays.*/
      ret = match_driver(drvp, &scanpath, &dp);
      if (!CH_RET_IS_ERROR(ret)) {
        /* Delegating directory deletion to a registered driver.*/
        ret = vfsDrvRmdir((void *)dp, scanpath);
/*        ret = dp->vmt->rmdir((void *)dp, scanpath);*/
      }
      else {
        /* Passing the request to the overlaid driver, if any.*/
        ret = drv_overlaid_path_call(drvp, shbuf->path.buf1,
                                     drvp->ovldrv.overlaid_drv->vmt->vfsdrv.rmdir);
      }
    }
  } while (false);

  /* Buffer returned.*/
  vfs_buffer_release(shbuf);

  return ret;
}

/** @} */
