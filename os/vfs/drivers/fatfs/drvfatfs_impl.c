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
 * @file        drvfatfs_impl.c
 * @brief       VFS FatFS Driver implementation source.
 *
 * @addtogroup  DRVFATFS
 * @{
 */

#include "vfs.h"
#include "ff.h"
#include "drvfatfs_impl.h"

#if (VFS_CFG_ENABLE_DRV_FATFS == TRUE) || defined (__DOXYGEN__)

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

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

static BYTE translate_oflag(int oflag) {

  switch (oflag & VO_SUPPORTED_FLAGS_MASK) {
  case VO_RDONLY:                                   /* r */
    return FA_READ;
  case VO_RDWR:                                     /* r+ */
    return FA_READ | FA_WRITE;
  case VO_CREAT | VO_APPEND | VO_WRONLY:            /* a */
    return FA_OPEN_APPEND | FA_WRITE;
  case VO_CREAT | VO_APPEND | VO_RDWR:              /* a+ */
    return FA_OPEN_APPEND | FA_WRITE | FA_READ;
  case VO_CREAT | VO_WRONLY:                        /* w */
    return FA_CREATE_ALWAYS | FA_WRITE;
  case VO_CREAT | VO_RDWR:                          /* w+ */
    return FA_CREATE_ALWAYS | FA_WRITE | FA_READ;
  case VO_CREAT | VO_EXCL | VO_WRONLY:              /* wx */
    return  FA_CREATE_NEW | FA_WRITE;
  case VO_CREAT | VO_EXCL | VO_RDWR:                /* w+x */
    return  FA_CREATE_NEW | FA_WRITE | FA_READ;
  default:
    break;
  }

  return (BYTE)0;
}

static vfs_mode_t translate_mode(BYTE fattrib) {
  vfs_mode_t mode = VFS_MODE_S_IRUSR;

  if ((fattrib & AM_RDO) == 0) {
    mode |= VFS_MODE_S_IWUSR;
  }

  if ((fattrib & AM_DIR) == 0) {
    mode |= VFS_MODE_S_IFREG;
  }
  else {
    mode |= VFS_MODE_S_IFDIR;
  }

  return mode;
}

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

msg_t __ffdrv_translate_error(FRESULT res) {
  msg_t msg;

  switch (res) {
  case FR_OK:
    msg = CH_RET_SUCCESS;
    break;
  case FR_TIMEOUT:
    msg = CH_RET_TIMEOUT;
    break;
  case FR_NOT_ENOUGH_CORE:
    msg = CH_RET_ENOMEM;
    break;
  case FR_TOO_MANY_OPEN_FILES:
    msg = CH_RET_ENFILE;
    break;
  case FR_DISK_ERR:
  case FR_NOT_READY:
  case FR_INVALID_DRIVE:
  case FR_NO_FILESYSTEM:
    msg = CH_RET_EIO;
    break;
  case FR_NO_FILE:
  case FR_NO_PATH:
    msg = CH_RET_ENOENT;
    break;
  case FR_INVALID_NAME:
    msg = CH_RET_ENAMETOOLONG;
    break;
  case FR_DENIED:
  case FR_WRITE_PROTECTED:
    msg = CH_RET_EACCES;
    break;
  case FR_EXIST:
    msg = CH_RET_EEXIST;
    break;
  case FR_IS_DIRECTORY:
    msg = CH_RET_EISDIR;
    break;
  case FR_NOT_DIRECTORY:
    msg = CH_RET_ENOTDIR;
    break;
  default:
    msg = CH_RET_INNER_ERROR;
    break;
  }

  return msg;
}

void *__ffdir_ro_addref_impl(void *ip) {

  return __ro_addref_impl(ip);
}

object_references_t __ffdir_ro_release_impl(void *ip) {

  return __ro_release_impl(ip);
}

msg_t __ffdir_vfsnode_stat_impl(void *ip, vfs_stat_t *sp) {

  return __vfsnode_stat_impl(ip, sp);
}

msg_t __ffdir_vfsdir_first_impl(void *ip, vfs_direntry_info_t *dip) {

  return __vfsdir_first_impl(ip, dip);
}

msg_t __ffdir_vfsdir_next_impl(void *ip, vfs_direntry_info_t *dip) {

  return __vfsdir_next_impl(ip, dip);
}

void *__fffile_ro_addref_impl(void *ip) {

  return __ro_addref_impl(ip);
}

object_references_t __fffile_ro_release_impl(void *ip) {

  return __ro_release_impl(ip);
}

msg_t __fffile_vfsnode_stat_impl(void *ip, vfs_stat_t *sp) {

  return __vfsnode_stat_impl(ip, sp);
}

ssize_t __fffile_vfsfile_read_impl(void *ip, uint8_t *buf, size_t size) {

  return __vfsfile_read_impl(ip, buf, size);
}

ssize_t __fffile_vfsfile_write_impl(void *ip, const uint8_t *buf,
                                           size_t size) {

  return __vfsfile_write_impl(ip, buf, size);
}

msg_t __fffile_vfsfile_setpos_impl(void *ip, vfs_offset_t offset,
                                          vfs_seekmode_t whence) {

  return __vfsfile_setpos_impl(ip, offset, whence);
}

vfs_offset_t __fffile_vfsfile_getpos_impl(void *ip) {

  return __vfsfile_getpos_impl(ip);
}

BaseSequentialStream *__fffile_vfsfile_getstream_impl(void *ip) {

  return __vfsfile_getstream_impl(ip);
}

msg_t __ffdrv_vfsdrv_setcwd_impl(void *ip, const char *path) {
#if FF_FS_RPATH >= 1

  (void)ip;

  return translate_error(f_chdir((const TCHAR *)path));
#else

  (void)ip;

  if (strcmp(path, "/") != 0) {
    return CH_RET_ENOENT;
  }

  return CH_RET_SUCCESS;
#endif
}

msg_t __ffdrv_vfsdrv_getcwd_impl(void *ip, char *buf, size_t size) {

  return __vfsdrv_getcwd_impl(ip, buf, size);
}

msg_t __ffdrv_vfsdrv_stat_impl(void *ip, const char *path,
                                      vfs_stat_t *sp) {

  return __vfsdrv_stat_impl(ip, path, sp);
}

msg_t __ffdrv_vfsdrv_opendir_impl(void *ip, const char *path,
                                         vfs_directory_node_c **vdnpp) {

  return __vfsdrv_opendir_impl(ip, path, vdnpp);
}

msg_t __ffdrv_vfsdrv_openfile_impl(void *ip, const char *path,
                                          int flags, vfs_file_node_c **vfnpp) {

  return __vfsdrv_openfile_impl(ip, path, flags, vfnpp);
}

msg_t __ffdrv_vfsdrv_unlink_impl(void *ip, const char *path) {

  return __vfsdrv_unlink_impl(ip, path);
}

msg_t __ffdrv_vfsdrv_rename_impl(void *ip, const char *oldpath,
                                        const char *newpath) {

  return __vfsdrv_rename_impl(ip, oldpath, newpath);
}

msg_t __ffdrv_vfsdrv_mkdir_impl(void *ip, const char *path,
                                       vfs_mode_t mode) {

  return __vfsdrv_mkdir_impl(ip, path, mode);
}

msg_t __ffdrv_vfsdrv_rmdir_impl(void *ip, const char *path) {

  return __vfsdrv_rmdir_impl(ip, path);
}

size_t __fffile_stm_write_impl(void *ip, const uint8_t *buf,
                                      size_t size) {
  vfs_fatfs_file_node_c *self = oopIfGetOwner(vfs_fatfs_file_node_c, ip);

  (void)self;
  (void)buf;
  (void)size;

  return (size_t)0;
}

size_t __fffile_stm_read_impl(void *ip, uint8_t *buf, size_t size) {
  vfs_fatfs_file_node_c *self = oopIfGetOwner(vfs_fatfs_file_node_c, ip);

  (void)self;
  (void)buf;
  (void)size;

  return (size_t)0;
}

msg_t __fffile_stm_put_impl(void *ip, uint8_t b) {
  vfs_fatfs_file_node_c *self = oopIfGetOwner(vfs_fatfs_file_node_c, ip);

  (void)self;
  (void)b;

  return MSG_OK;
}

msg_t __fffile_stm_get_impl(void *ip) {
  vfs_fatfs_file_node_c *self = oopIfGetOwner(vfs_fatfs_file_node_c, ip);

  (void)self;

  return (msg_t)0;
}

#endif /* VFS_CFG_ENABLE_DRV_FATFS == TRUE */

/** @} */
