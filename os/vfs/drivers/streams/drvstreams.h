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
 * @file        drvstreams.h
 * @brief       Generated VFS Streams Driver header.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  DRVSTREAMS
 * @{
 */

#ifndef DRVSTREAMS_H
#define DRVSTREAMS_H

#if (VFS_CFG_ENABLE_DRV_STREAMS == TRUE) || defined(__DOXYGEN__)

#include "oop_sequential_stream.h"

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief       Number of directory nodes pre-allocated in the pool.
 */
#if !defined(DRV_CFG_STREAMS_DIR_NODES_NUM) || defined(__DOXYGEN__)
#define DRV_CFG_STREAMS_DIR_NODES_NUM       1
#endif

/**
 * @brief       Number of file nodes pre-allocated in the pool.
 */
#if !defined(DRV_CFG_STREAMS_FILE_NODES_NUM) || defined(__DOXYGEN__)
#define DRV_CFG_STREAMS_FILE_NODES_NUM      1
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Checks on DRV_CFG_STREAMS_DIR_NODES_NUM configuration.*/
#if DRV_CFG_STREAMS_DIR_NODES_NUM < 1
#error "invalid DRV_CFG_STREAMS_DIR_NODES_NUM value"
#endif

/* Checks on DRV_CFG_STREAMS_FILE_NODES_NUM configuration.*/
#if DRV_CFG_STREAMS_FILE_NODES_NUM < 1
#error "invalid DRV_CFG_STREAMS_FILE_NODES_NUM value"
#endif

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief       Type of a stream association structure.
 */
typedef struct drv_streams_element drv_streams_element_t;

/**
 * @brief       Structure representing a stream association.
 */
struct drv_streams_element {
  /**
   * @brief       Filename for the stream.
   */
  const char                *name;
  /**
   * @brief       Pointer to the stream.
   */
  sequential_stream_i       *stm;
};

/**
 * @class       vfs_streams_dir_node_c
 * @extends     vfs_directory_node_c
 *
 * @note        The class namespace is <tt>stmdir</tt>, access to class fields
 *              is done using: <tt><objp>->stmdir.<fieldname></tt><br>Note that
 *              fields of ancestor classes are in their own namespace in order
 *              to avoid field naming conflicts.
 *
 * @name        Class @p vfs_streams_dir_node_c structures
 * @{
 */

/**
 * @brief       Type of a VFS streams directory node class.
 */
typedef struct vfs_streams_dir_node vfs_streams_dir_node_c;

/**
 * @brief       Class @p vfs_streams_dir_node_c data as a structure.
 */
struct stmdir_data {
  /**
   * @brief       Current directory entry during scanning.
   */
  unsigned                  index;
};

/**
 * @brief       Class @p vfs_streams_dir_node_c methods.
 */
#define __stmdir_methods                                                    \
  __vfsdir_methods                                                          \
  /* No methods.*/

/**
 * @brief       Class @p vfs_streams_dir_node_c data.
 */
#define __stmdir_data                                                       \
  __vfsdir_data                                                             \
  struct stmdir_data        stmdir;

/**
 * @brief       Class @p vfs_streams_dir_node_c VMT initializer.
 */
#define __stmdir_vmt_init(ns)                                               \
  __vfsdir_vmt_init(ns)

/**
 * @brief       Class @p vfs_streams_dir_node_c virtual methods table.
 */
struct vfs_streams_dir_node_vmt {
  __stmdir_methods
};

/**
 * @brief       Structure representing a VFS streams directory node class.
 */
struct vfs_streams_dir_node {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_streams_dir_node_vmt *vmt;
  __stmdir_data
};
/** @} */

/**
 * @class       vfs_streams_file_node_c
 * @extends     vfs_file_node_c
 *
 * @note        The class namespace is <tt>stmfile</tt>, access to class fields
 *              is done using: <tt><objp>->stmfile.<fieldname></tt><br>Note
 *              that fields of ancestor classes are in their own namespace in
 *              order to avoid field naming conflicts.
 *
 * @name        Class @p vfs_streams_file_node_c structures
 * @{
 */

/**
 * @brief       Type of a VFS streams file node class.
 */
typedef struct vfs_streams_file_node vfs_streams_file_node_c;

/**
 * @brief       Class @p vfs_streams_file_node_c data as a structure.
 */
struct stmfile_data {
  /**
   * @brief       Stream interface for this file.
   */
  sequential_stream_i       *stm;
};

/**
 * @brief       Class @p vfs_streams_file_node_c methods.
 */
#define __stmfile_methods                                                   \
  __vfsfile_methods                                                         \
  /* No methods.*/

/**
 * @brief       Class @p vfs_streams_file_node_c data.
 */
#define __stmfile_data                                                      \
  __vfsfile_data                                                            \
  struct stmfile_data       stmfile;

/**
 * @brief       Class @p vfs_streams_file_node_c VMT initializer.
 */
#define __stmfile_vmt_init(ns)                                              \
  __vfsfile_vmt_init(ns)

/**
 * @brief       Class @p vfs_streams_file_node_c virtual methods table.
 */
struct vfs_streams_file_node_vmt {
  __stmfile_methods
};

/**
 * @brief       Structure representing a VFS streams file node class.
 */
struct vfs_streams_file_node {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_streams_file_node_vmt *vmt;
  __stmfile_data
};
/** @} */

/**
 * @class       vfs_streams_driver_c
 * @extends     vfs_driver_c
 *
 * @note        The class namespace is <tt>stmdrv</tt>, access to class fields
 *              is done using: <tt><objp>->stmdrv.<fieldname></tt><br>Note that
 *              fields of ancestor classes are in their own namespace in order
 *              to avoid field naming conflicts.
 *
 * @name        Class @p vfs_streams_driver_c structures
 * @{
 */

/**
 * @brief       Type of a VFS streams driver class.
 */
typedef struct vfs_streams_driver vfs_streams_driver_c;

/**
 * @brief       Class @p vfs_streams_driver_c data as a structure.
 */
struct stmdrv_data {
  /**
   * @brief       Pointer to the stream elements to be exposed.
   */
  const drv_streams_element_t *streams;
};

/**
 * @brief       Class @p vfs_streams_driver_c methods.
 */
#define __stmdrv_methods                                                    \
  __vfsdrv_methods                                                          \
  /* No methods.*/

/**
 * @brief       Class @p vfs_streams_driver_c data.
 */
#define __stmdrv_data                                                       \
  __vfsdrv_data                                                             \
  struct stmdrv_data        stmdrv;

/**
 * @brief       Class @p vfs_streams_driver_c VMT initializer.
 */
#define __stmdrv_vmt_init(ns)                                               \
  __vfsdrv_vmt_init(ns)

/**
 * @brief       Class @p vfs_streams_driver_c virtual methods table.
 */
struct vfs_streams_driver_vmt {
  __stmdrv_methods
};

/**
 * @brief       Structure representing a VFS streams driver class.
 */
struct vfs_streams_driver {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_streams_driver_vmt *vmt;
  __stmdrv_data
};
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  /* Methods of vfs_streams_dir_node_c.*/
  void *__stmdir_objinit_impl(void *ip, const void *vmt, vfs_driver_c *driver,
                              vfs_mode_t mode);
  void __stmdir_dispose_impl(void *ip);
  /* Methods of vfs_streams_file_node_c.*/
  void *__stmfile_objinit_impl(void *ip, const void *vmt, vfs_driver_c *driver,
                               vfs_mode_t mode, sequential_stream_i *stream);
  void __stmfile_dispose_impl(void *ip);
  /* Methods of vfs_streams_driver_c.*/
  void *__stmdrv_objinit_impl(void *ip, const void *vmt,
                              const drv_streams_element_t *streams);
  void __stmdrv_dispose_impl(void *ip);
  /* Regular functions.*/
  void __drv_streams_init(void);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

/**
 * @name        Default constructor of vfs_streams_dir_node_c
 * @{
 */
/**
 * @memberof    vfs_streams_dir_node_c
 *
 * @brief       Default initialization function of @p vfs_streams_dir_node_c.
 *
 * @param[out]    self          Pointer to a @p vfs_streams_dir_node_c instance
 *                              to be initialized.
 * @param[in]     driver        Pointer to the controlling driver.
 * @param[in]     mode          Node mode flags.
 * @return                      Pointer to the initialized object.
 *
 * @objinit
 */
CC_FORCE_INLINE
static inline vfs_streams_dir_node_c *stmdirObjectInit(vfs_streams_dir_node_c *self,
                                                       vfs_driver_c *driver,
                                                       vfs_mode_t mode) {
  extern const struct vfs_streams_dir_node_vmt __stmdir_vmt;

  return __stmdir_objinit_impl(self, &__stmdir_vmt, driver, mode);
}
/** @} */

/**
 * @name        Default constructor of vfs_streams_file_node_c
 * @{
 */
/**
 * @memberof    vfs_streams_file_node_c
 *
 * @brief       Default initialization function of @p vfs_streams_file_node_c.
 *
 * @param[out]    self          Pointer to a @p vfs_streams_file_node_c
 *                              instance to be initialized.
 * @param[in]     driver        Pointer to the controlling driver.
 * @param[in]     mode          Node mode flags.
 * @param[in]     stream        Stream to be associated.
 * @return                      Pointer to the initialized object.
 *
 * @objinit
 */
CC_FORCE_INLINE
static inline vfs_streams_file_node_c *stmfileObjectInit(vfs_streams_file_node_c *self,
                                                         vfs_driver_c *driver,
                                                         vfs_mode_t mode,
                                                         sequential_stream_i *stream) {
  extern const struct vfs_streams_file_node_vmt __stmfile_vmt;

  return __stmfile_objinit_impl(self, &__stmfile_vmt, driver, mode, stream);
}
/** @} */

/**
 * @name        Default constructor of vfs_streams_driver_c
 * @{
 */
/**
 * @memberof    vfs_streams_driver_c
 *
 * @brief       Default initialization function of @p vfs_streams_driver_c.
 *
 * @param[out]    self          Pointer to a @p vfs_streams_driver_c instance
 *                              to be initialized.
 * @param[in]     streams       Pointer to a @p vfs_streams_driver_c structure.
 * @return                      Pointer to the initialized object.
 *
 * @objinit
 */
CC_FORCE_INLINE
static inline vfs_streams_driver_c *stmdrvObjectInit(vfs_streams_driver_c *self,
                                                     const drv_streams_element_t *streams) {
  extern const struct vfs_streams_driver_vmt __stmdrv_vmt;

  return __stmdrv_objinit_impl(self, &__stmdrv_vmt, streams);
}
/** @} */

#endif /* VFS_CFG_ENABLE_DRV_STREAMS == TRUE */

#endif /* DRVSTREAMS_H */

/** @} */
