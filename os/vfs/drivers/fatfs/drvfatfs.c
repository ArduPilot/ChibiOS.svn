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
 * @file        drvfatfs.c
 * @brief       Generated VFS FatFS Driver source.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  DRVFATFS
 * @{
 */

#include "vfs.h"

#if (VFS_CFG_ENABLE_DRV_FATFS == TRUE) || defined(__DOXYGEN__)

#include "ff.h"

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
 * @brief       Global state of @p vfs_fatfs_driver_c.
 */
struct vfs_fatfs_driver_static_struct vfs_fatfs_driver_static;

/**
 * @brief       Global state of @p vfs_fatfs_driver_c.
 */
struct vfs_fatfs_driver_static_nc_struct __nocache_vfs_fatfs_driver_static;

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

/**
 * @class       vfs_fatfs_dir_node_c
 * @extends     vfs_directory_node_c
 *
 * @note        The class namespace is <tt>ffdir</tt>, access to class fields
 *              is done using: <tt><objp>->ffdir.<fieldname></tt><br>Note that
 *              fields of ancestor classes are in their own namespace in order
 *              to avoid field naming conflicts.
 *
 * @name        Class @p vfs_fatfs_dir_node_c structures
 * @{
 */

/**
 * @brief       Type of a VFS fatfs directory node class.
 */
typedef struct vfs_fatfs_dir_node vfs_fatfs_dir_node_c;

/**
 * @brief       Class @p vfs_fatfs_dir_node_c data as a structure.
 */
struct ffdir_data {
  /**
   * @brief       FatFS inner @p DIR structure.
   */
  DIR                       dir;
};

/**
 * @brief       Class @p vfs_fatfs_dir_node_c methods.
 */
#define __ffdir_methods                                                     \
  __vfsdir_methods                                                          \
  /* No methods.*/

/**
 * @brief       Class @p vfs_fatfs_dir_node_c data.
 */
#define __ffdir_data                                                        \
  __vfsdir_data                                                             \
  struct ffdir_data         ffdir;

/**
 * @brief       Class @p vfs_fatfs_dir_node_c VMT initializer.
 */
#define __ffdir_vmt_init(ns)                                                \
  __vfsdir_vmt_init(ns)

/**
 * @brief       Class @p vfs_fatfs_dir_node_c virtual methods table.
 */
struct vfs_fatfs_dir_node_vmt {
  __ffdir_methods
};

/**
 * @brief       Structure representing a VFS fatfs directory node class.
 */
struct vfs_fatfs_dir_node {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_fatfs_dir_node_vmt *vmt;
  __ffdir_data
};
/** @} */

/**
 * @class       vfs_fatfs_file_node_c
 * @extends     vfs_file_node_c
 * @implements  sequential_stream_i
 *
 * @note        The class namespace is <tt>fffile</tt>, access to class fields
 *              is done using: <tt><objp>->fffile.<fieldname></tt><br>Note that
 *              fields of ancestor classes are in their own namespace in order
 *              to avoid field naming conflicts.
 *
 * @name        Class @p vfs_fatfs_file_node_c structures
 * @{
 */

/**
 * @brief       Type of a VFS fatfs file node class.
 */
typedef struct vfs_fatfs_file_node vfs_fatfs_file_node_c;

/**
 * @brief       Class @p vfs_fatfs_file_node_c data as a structure.
 */
struct fffile_data {
  /**
   * @brief       Implemented interface @p sequential_stream_i.
   */
  sequential_stream_i       stm;
  /**
   * @brief       FatFS inner @p FIL structure.
   */
  FIL                       file;
};

/**
 * @brief       Class @p vfs_fatfs_file_node_c methods.
 */
#define __fffile_methods                                                    \
  __vfsfile_methods                                                         \
  /* No methods.*/

/**
 * @brief       Class @p vfs_fatfs_file_node_c data.
 */
#define __fffile_data                                                       \
  __vfsfile_data                                                            \
  struct fffile_data        fffile;

/**
 * @brief       Class @p vfs_fatfs_file_node_c VMT initializer.
 */
#define __fffile_vmt_init(ns)                                               \
  __vfsfile_vmt_init(ns)

/**
 * @brief       Class @p vfs_fatfs_file_node_c virtual methods table.
 */
struct vfs_fatfs_file_node_vmt {
  __fffile_methods
};

/**
 * @brief       Structure representing a VFS fatfs file node class.
 */
struct vfs_fatfs_file_node {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_fatfs_file_node_vmt *vmt;
  __fffile_data
};

/**
 * @memberof    vfs_fatfs_file_node_c
 *
 * @brief       Access macro for vfs_fatfs_file_node_c interfaces.
 *
 * @param[in]     ip            Pointer to the class instance.
 * @param         ifns          Implemented interface namespace.
 * @return                      A void pointer to the interface within the
 *                              class instance.
 *
 * @api
 */
#define fffileGetIf(ip, ifns)                                               \
  boGetIf(ip, ifns, fffile)
/** @} */

/**
 * @brief       Global state of @p vfs_fatfs_driver_c.
 */
struct vfs_fatfs_driver_static_struct {
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
  vfs_fatfs_dir_node_c      dir_nodes[DRV_CFG_FATFS_DIR_NODES_NUM];
  /**
   * @brief       Static storage of file nodes.
   */
  vfs_fatfs_file_node_c     file_nodes[DRV_CFG_FATFS_FILE_NODES_NUM];
};

/**
 * @brief       Global state of @p vfs_fatfs_driver_c (non-cached part).
 */
struct vfs_fatfs_driver_static_nc_struct {
  /**
   * @brief       Pool of file system objects.
   */
  FATFS                     fs[DRV_CFG_FATFS_FS_NUM];
};

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/* Module code has been generated into an hand-editable file and included
   here.*/
#include "drvfatfs_impl.inc"

#endif /* VFS_CFG_ENABLE_DRV_FATFS == TRUE */

/** @} */
