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
 * @file        drvtemplate.h
 * @brief       Generated VFS Template Driver header.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  DRVTEMPLATE
 * @{
 */
 
#ifndef DRVTEMPLATE_H
#define DRVTEMPLATE_H

#if (VFS_CFG_ENABLE_DRV_TEMPLATE == TRUE) || defined (__DOXYGEN__)

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
#if !defined(DRV_CFG_TEMPLATE_DIR_NODES_NUM) || defined(__DOXYGEN__)
#define DRV_CFG_TEMPLATE_DIR_NODES_NUM      1
#endif

/**
 * @brief       Number of file nodes pre-allocated in the pool.
 */
#if !defined(DRV_CFG_TEMPLATE_FILE_NODES_NUM) || defined(__DOXYGEN__)
#define DRV_CFG_TEMPLATE_FILE_NODES_NUM     1
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Checks on DRV_CFG_TEMPLATE_DIR_NODES_NUM configuration.*/
#if DRV_CFG_TEMPLATE_DIR_NODES_NUM < 1
#error "invalid DRV_CFG_TEMPLATE_DIR_NODES_NUM value"
#endif

/* Checks on DRV_CFG_TEMPLATE_FILE_NODES_NUM configuration.*/
#if DRV_CFG_TEMPLATE_FILE_NODES_NUM < 1
#error "invalid DRV_CFG_TEMPLATE_FILE_NODES_NUM value"
#endif

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
  /* Methods of vfs_template_dir_node_c.*/
  void *__tmpldir_objinit_impl(void *ip, const void *vmt);
  void __tmpldir_dispose_impl(void *ip);
  /* Methods of vfs_template_file_node_c.*/
  void *__tmplfile_objinit_impl(void *ip, const void *vmt);
  void __tmplfile_dispose_impl(void *ip);
  /* Methods of vfs_template_driver_c.*/
  void *__tmpldrv_objinit_impl(void *ip, const void *vmt);
  void __tmpldrv_dispose_impl(void *ip);
  /* Regular functions.*/
  void __drv_template_init(void);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

/*===========================================================================*/
/* Module class vfs_template_dir_node_c                                      */
/*===========================================================================*/

/**
 * @class       vfs_template_dir_node_c
 * @extends     vfs_directory_node_c
 *
 * @note        The class namespace is <tt>tmpldir</tt>, access to class fields
 *              is done using: <tt><objp>->tmpldir.<fieldname></tt><br>Note
 *              that fields of ancestor classes are in their own namespace in
 *              order to avoid field naming conflicts.
 */

/**
 * @brief       Type of a VFS template directory node class.
 */
typedef struct vfs_template_dir_node vfs_template_dir_node_c;

/**
 * @brief       @p vfs_template_dir_node_c methods.
 */
#define __tmpldir_methods                                                   \
  __vfsdir_methods                                                          \
  /* No methods.*/

/**
 * @brief       @p vfs_template_dir_node_c data.
 */
#define __tmpldir_data                                                      \
  __vfsdir_data                                                             \
  /* No data.*/

/**
 * @brief       @p vfs_template_dir_node_c VMT initializer.
 */
#define __tmpldir_vmt_init(ns)                                              \
  __vfsdir_vmt_init(ns)

/**
 * @brief       @p vfs_template_dir_node_c virtual methods table.
 */
struct vfs_template_dir_node_vmt {
  __tmpldir_methods
};

/**
 * @brief       Structure representing a VFS template directory node class.
 */
struct vfs_template_dir_node {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_template_dir_node_vmt *vmt;
  __tmpldir_data
};

/**
 * @name        Constructor and destructor of vfs_template_dir_node_c
 * @{
 */
/**
 * @memberof    vfs_template_dir_node_c
 *
 * @brief       Default initialize function of @p vfs_template_dir_node_c.
 *
 * @param[out]    no-name       Pointer to a @p vfs_template_dir_node_c
 *                              instance to be initialized.
 * @return                      Pointer to the initialized object.
 */
CC_FORCE_INLINE
static inline vfs_template_dir_node_c *tmpldirObjectInit(vfs_template_dir_node_c *self) {
  extern const struct vfs_template_dir_node_vmt __tmpldir_vmt;

  return __tmpldir_objinit_impl(self, &__tmpldir_vmt);
}

/**
 * @memberof    vfs_template_dir_node_c
 *
 * @brief       Default finalize function of @p vfs_template_dir_node_c.
 *
 * @param[in,out] no-name       Pointer to a @p vfs_template_dir_node_c
 *                              instance to be finalized.
 */
CC_FORCE_INLINE
static inline void tmpldirDispose(vfs_template_dir_node_c *self) {

  __tmpldir_dispose_impl(self);
}
/** @} */

/*===========================================================================*/
/* Module class vfs_template_file_node_c                                     */
/*===========================================================================*/

/**
 * @class       vfs_template_file_node_c
 * @extends     vfs_file_node_c
 *
 * @note        The class namespace is <tt>tmplfile</tt>, access to class
 *              fields is done using:
 *              <tt><objp>->tmplfile.<fieldname></tt><br>Note that fields of
 *              ancestor classes are in their own namespace in order to avoid
 *              field naming conflicts.
 */

/**
 * @brief       Type of a VFS template file node class.
 */
typedef struct vfs_template_file_node vfs_template_file_node_c;

/**
 * @brief       @p vfs_template_file_node_c methods.
 */
#define __tmplfile_methods                                                  \
  __vfsfile_methods                                                         \
  /* No methods.*/

/**
 * @brief       @p vfs_template_file_node_c data.
 */
#define __tmplfile_data                                                     \
  __vfsfile_data                                                            \
  /* No data.*/

/**
 * @brief       @p vfs_template_file_node_c VMT initializer.
 */
#define __tmplfile_vmt_init(ns)                                             \
  __vfsfile_vmt_init(ns)

/**
 * @brief       @p vfs_template_file_node_c virtual methods table.
 */
struct vfs_template_file_node_vmt {
  __tmplfile_methods
};

/**
 * @brief       Structure representing a VFS template file node class.
 */
struct vfs_template_file_node {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_template_file_node_vmt *vmt;
  __tmplfile_data
};

/**
 * @name        Constructor and destructor of vfs_template_file_node_c
 * @{
 */
/**
 * @memberof    vfs_template_file_node_c
 *
 * @brief       Default initialize function of @p vfs_template_file_node_c.
 *
 * @param[out]    no-name       Pointer to a @p vfs_template_file_node_c
 *                              instance to be initialized.
 * @return                      Pointer to the initialized object.
 */
CC_FORCE_INLINE
static inline vfs_template_file_node_c *tmplfileObjectInit(vfs_template_file_node_c *self) {
  extern const struct vfs_template_file_node_vmt __tmplfile_vmt;

  return __tmplfile_objinit_impl(self, &__tmplfile_vmt);
}

/**
 * @memberof    vfs_template_file_node_c
 *
 * @brief       Default finalize function of @p vfs_template_file_node_c.
 *
 * @param[in,out] no-name       Pointer to a @p vfs_template_file_node_c
 *                              instance to be finalized.
 */
CC_FORCE_INLINE
static inline void tmplfileDispose(vfs_template_file_node_c *self) {

  __tmplfile_dispose_impl(self);
}
/** @} */

/*===========================================================================*/
/* Module class vfs_template_driver_c                                        */
/*===========================================================================*/

/**
 * @class       vfs_template_driver_c
 * @extends     vfs_driver_c
 *
 * @note        The class namespace is <tt>tmpldrv</tt>, access to class fields
 *              is done using: <tt><objp>->tmpldrv.<fieldname></tt><br>Note
 *              that fields of ancestor classes are in their own namespace in
 *              order to avoid field naming conflicts.
 */

/**
 * @brief       Type of a VFS template driver class.
 */
typedef struct vfs_template_driver vfs_template_driver_c;

/**
 * @brief       @p vfs_template_driver_c methods.
 */
#define __tmpldrv_methods                                                   \
  __vfsdrv_methods                                                          \
  /* No methods.*/

/**
 * @brief       @p vfs_template_driver_c data.
 */
#define __tmpldrv_data                                                      \
  __vfsdrv_data                                                             \
  /* No data.*/

/**
 * @brief       @p vfs_template_driver_c VMT initializer.
 */
#define __tmpldrv_vmt_init(ns)                                              \
  __vfsdrv_vmt_init(ns)

/**
 * @brief       @p vfs_template_driver_c virtual methods table.
 */
struct vfs_template_driver_vmt {
  __tmpldrv_methods
};

/**
 * @brief       Structure representing a VFS template driver class.
 */
struct vfs_template_driver {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_template_driver_vmt *vmt;
  __tmpldrv_data
};

/**
 * @name        Constructor and destructor of vfs_template_driver_c
 * @{
 */
/**
 * @memberof    vfs_template_driver_c
 *
 * @brief       Default initialize function of @p vfs_template_driver_c.
 *
 * @param[out]    no-name       Pointer to a @p vfs_template_driver_c instance
 *                              to be initialized.
 * @return                      Pointer to the initialized object.
 */
CC_FORCE_INLINE
static inline vfs_template_driver_c *tmpldrvObjectInit(vfs_template_driver_c *self) {
  extern const struct vfs_template_driver_vmt __tmpldrv_vmt;

  return __tmpldrv_objinit_impl(self, &__tmpldrv_vmt);
}

/**
 * @memberof    vfs_template_driver_c
 *
 * @brief       Default finalize function of @p vfs_template_driver_c.
 *
 * @param[in,out] no-name       Pointer to a @p vfs_template_driver_c instance
 *                              to be finalized.
 */
CC_FORCE_INLINE
static inline void tmpldrvDispose(vfs_template_driver_c *self) {

  __tmpldrv_dispose_impl(self);
}
/** @} */

#endif /* VFS_CFG_ENABLE_DRV_TEMPLATE == TRUE */

#endif /* DRVTEMPLATE_H */

/** @} */
