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
 * @file        drvoverlay_impl.h
 * @brief       VFS Overlay Driver implementation header.
 *
 * @addtogroup  DRVOVERLAY
 * @{
 */
 
#ifndef DRVOVERLAY_IMPL_H
#define DRVOVERLAY_IMPL_H

#if (VFS_CFG_ENABLE_DRV_OVERLAY == TRUE) || defined (__DOXYGEN__)

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void *__ovldir_ro_addref_impl(void *ip);
  object_references_t __ovldir_ro_release_impl(void *ip);
  msg_t __ovldir_vfsnode_stat_impl(void *ip, vfs_stat_t *sp);
  msg_t __ovldir_vfsdir_first_impl(void *ip, vfs_direntry_info_t *dip);
  msg_t __ovldir_vfsdir_next_impl(void *ip, vfs_direntry_info_t *dip);
  msg_t __ovldrv_vfsdrv_setcwd_impl(void *ip, const char *path);
  msg_t __ovldrv_vfsdrv_getcwd_impl(void *ip, char *buf, size_t size);
  msg_t __ovldrv_vfsdrv_stat_impl(void *ip, const char *path,
                                  vfs_stat_t *sp);
  msg_t __ovldrv_vfsdrv_opendir_impl(void *ip, const char *path,
                                     vfs_directory_node_c **vdnpp);
  msg_t __ovldrv_vfsdrv_openfile_impl(void *ip, const char *path,
                                      int flags, vfs_file_node_c **vfnpp);
  msg_t __ovldrv_vfsdrv_unlink_impl(void *ip, const char *path);
  msg_t __ovldrv_vfsdrv_rename_impl(void *ip, const char *oldpath,
                                    const char *newpath);
  msg_t __ovldrv_vfsdrv_mkdir_impl(void *ip, const char *path,
                                   vfs_mode_t mode);
  msg_t __ovldrv_vfsdrv_rmdir_impl(void *ip, const char *path);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* VFS_CFG_ENABLE_DRV_OVERLAY == TRUE */

#endif /* DRVOVERLAY_IMPL_H */

/** @} */
