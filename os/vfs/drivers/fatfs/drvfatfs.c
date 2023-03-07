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

#if (VFS_CFG_ENABLE_DRV_FATFS == TRUE) || defined (__DOXYGEN__)

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

/* Methods implementations in an unmanaged module.*/
#include "drvfatfs_impl.inc"

/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

/**
 * @name        Virtual methods implementations of vfs_fatfs_dir_node_c
 * @{
 */
/**
 * @memberof    vfs_fatfs_dir_node_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_fatfs_dir_node_c instance
 *                              to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @param[in]     driver        Pointer to the controlling driver.
 * @param[in]     mode          Node mode flags.
 * @return                      A new reference to the object.
 */
void *__ffdir_objinit_impl(void *ip, const void *vmt, vfs_driver_c *driver,
                           vfs_mode_t mode) {
  vfs_fatfs_dir_node_c *self = (vfs_fatfs_dir_node_c *)ip;

  /* Initialization code.*/
  self = __vfsdir_objinit_impl(ip, vmt, (vfs_driver_c *)driver, mode);

  return self;
}

/**
 * @memberof    vfs_fatfs_dir_node_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_fatfs_dir_node_c instance
 *                              to be disposed.
 */
void __ffdir_dispose_impl(void *ip) {
  vfs_fatfs_dir_node_c *self = (vfs_fatfs_dir_node_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsdir_dispose_impl(self);
}
/** @} */

/**
 * @name        Constructor and destructor of vfs_fatfs_dir_node_c
 * @{
 */
/**
 * @memberof    vfs_fatfs_dir_node_c
 *
 * @brief       Default initialization function of @p vfs_fatfs_dir_node_c.
 *
 * @param[out]    self          Pointer to a @p vfs_fatfs_dir_node_c instance
 *                              to be initialized.
 * @param[in]     driver        Pointer to the controlling driver.
 * @param[in]     mode          Node mode flags.
 * @return                      Pointer to the initialized object.
 *
 * @objinit
 */
CC_FORCE_INLINE
static inline vfs_fatfs_dir_node_c *ffdir_object_init(vfs_fatfs_dir_node_c *self,
                                                      vfs_driver_c *driver,
                                                      vfs_mode_t mode) {
  static const struct vfs_fatfs_dir_node_vmt __ffdir_vmt = {
    __ffdir_vmt_init(ffdir)
  };

  return __ffdir_objinit_impl(self, &__ffdir_vmt, driver, mode);
}

/**
 * @memberof    vfs_fatfs_dir_node_c
 *
 * @brief       Default finalization function of @p vfs_fatfs_dir_node_c.
 *
 * @param[in,out] self          Pointer to a @p vfs_fatfs_dir_node_c instance
 *                              to be finalized.
 *
 * @dispose
 */
CC_FORCE_INLINE
static inline void ffdir_dispose(vfs_fatfs_dir_node_c *self) {

  __ffdir_dispose_impl(self);
}
/** @} */

/**
 * @name        Virtual methods implementations of vfs_fatfs_file_node_c
 * @{
 */
/**
 * @memberof    vfs_fatfs_file_node_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_fatfs_file_node_c instance
 *                              to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @param[in]     driver        Pointer to the controlling driver.
 * @param[in]     mode          Node mode flags.
 * @return                      A new reference to the object.
 */
void *__fffile_objinit_impl(void *ip, const void *vmt, vfs_driver_c *driver,
                            vfs_mode_t mode) {
  vfs_fatfs_file_node_c *self = (vfs_fatfs_file_node_c *)ip;

  /* Implementation of interface sequential_stream_i.*/
  {
    static const struct sequential_stream_vmt fffile_stm_vmt = {
      __stm_vmt_init(fffile, offsetof(vfs_fatfs_file_node_c, fffile.stm))
    };
    oopIfObjectInit(&self->fffile.stm, &fffile_stm_vmt);
  }

  /* Initialization code.*/
  self = __vfsfile_objinit_impl(ip, vmt, (vfs_driver_c *)driver, mode);

  return self;
}

/**
 * @memberof    vfs_fatfs_file_node_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_fatfs_file_node_c instance
 *                              to be disposed.
 */
void __fffile_dispose_impl(void *ip) {
  vfs_fatfs_file_node_c *self = (vfs_fatfs_file_node_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsfile_dispose_impl(self);
}
/** @} */

/**
 * @name        Constructor and destructor of vfs_fatfs_file_node_c
 * @{
 */
/**
 * @memberof    vfs_fatfs_file_node_c
 *
 * @brief       Default initialization function of @p vfs_fatfs_file_node_c.
 *
 * @param[out]    self          Pointer to a @p vfs_fatfs_file_node_c instance
 *                              to be initialized.
 * @param[in]     driver        Pointer to the controlling driver.
 * @param[in]     mode          Node mode flags.
 * @return                      Pointer to the initialized object.
 *
 * @objinit
 */
CC_FORCE_INLINE
static inline vfs_fatfs_file_node_c *fffile_object_init(vfs_fatfs_file_node_c *self,
                                                        vfs_driver_c *driver,
                                                        vfs_mode_t mode) {
  static const struct vfs_fatfs_file_node_vmt __fffile_vmt = {
    __fffile_vmt_init(fffile)
  };

  return __fffile_objinit_impl(self, &__fffile_vmt, driver, mode);
}

/**
 * @memberof    vfs_fatfs_file_node_c
 *
 * @brief       Default finalization function of @p vfs_fatfs_file_node_c.
 *
 * @param[in,out] self          Pointer to a @p vfs_fatfs_file_node_c instance
 *                              to be finalized.
 *
 * @dispose
 */
CC_FORCE_INLINE
static inline void fffile_dispose(vfs_fatfs_file_node_c *self) {

  __fffile_dispose_impl(self);
}
/** @} */

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/**
 * @brief       Module initialization.
 *
 * @init
 */
void __drv_fatfs_init(void) {

    /* Initializing pools.*/
    chPoolObjectInit(&vfs_fatfs_driver_static.dir_nodes_pool,
                     sizeof (vfs_fatfs_dir_node_c),
                     chCoreAllocAlignedI);
    chPoolObjectInit(&vfs_fatfs_driver_static.file_nodes_pool,
                     sizeof (vfs_fatfs_file_node_c),
                     chCoreAllocAlignedI);
    chPoolObjectInit(&vfs_fatfs_driver_static.info_nodes_pool,
                     sizeof (FILINFO),
                     chCoreAllocAlignedI);
    chPoolObjectInit(&vfs_fatfs_driver_static.fs_nodes_pool,
                     sizeof (FATFS),
                     NULL);

    /* Preloading pools.*/
    chPoolLoadArray(&vfs_fatfs_driver_static.dir_nodes_pool,
                    &vfs_fatfs_driver_static.dir_nodes[0],
                    DRV_CFG_FATFS_DIR_NODES_NUM);
    chPoolLoadArray(&vfs_fatfs_driver_static.file_nodes_pool,
                    &vfs_fatfs_driver_static.file_nodes[0],
                    DRV_CFG_FATFS_FILE_NODES_NUM);
    chPoolLoadArray(&vfs_fatfs_driver_static.fs_nodes_pool,
                    &__nocache_vfs_fatfs_driver_static.fs[0],
                    DRV_CFG_FATFS_FS_NUM);
}

/**
 * @brief       Mounts a FatFS volume.
 *
 * @param[in]     name          Name to be assigned to the volume, see FatFS @p
 *                              f_mount() documentation because there are
 *                              several options.
 * @param[in]     mountnow      Immediate mount option.
 * @return                      The operation result.
 *
 * @api
 */
msg_t ffdrvMount(const char *name, bool mountnow) {
  FATFS *fs;
  FRESULT res;

  fs = f_getfs(name);
  if (fs == NULL) {
    fs = chPoolAlloc(&vfs_fatfs_driver_static.fs_nodes_pool);
    if (fs == NULL) {
      return CH_RET_ENOMEM;
    }
  }

  res = f_mount(fs, name, (BYTE)(mountnow ? 1 : 0));
  if (res != FR_OK) {
    chPoolFree(&vfs_fatfs_driver_static.fs_nodes_pool, (void *)fs);
  }

  return translate_error(res);
}

/**
 * @brief       Unmounts a FatFS volume.
 *
 * @param[in]     name          Name of the volume to be unmounted.
 * @return                      The operation result.
 *
 * @api
 */
msg_t ffdrvUnmount(const char *name) {
  FATFS *fs;
  FRESULT res;

  fs = f_getfs(name);
  if (fs == NULL) {
    return CH_RET_EINVAL;
  }

  res = f_unmount(name);

  chPoolFree(&vfs_fatfs_driver_static.fs_nodes_pool, (void *)fs);

  return translate_error(res);
}

/*===========================================================================*/
/* Module class "vfs_fatfs_driver_c" methods.                                */
/*===========================================================================*/

/**
 * @brief       VMT structure of VFS fatfs driver class.
 * @note        It is public because accessed by the inlined constructor.
 */
const struct vfs_fatfs_driver_vmt __ffdrv_vmt = {
  __ffdrv_vmt_init(ffdrv)
};

/**
 * @name        Virtual methods implementations of vfs_fatfs_driver_c
 * @{
 */
/**
 * @memberof    vfs_fatfs_driver_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_fatfs_driver_c instance to
 *                              be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
void *__ffdrv_objinit_impl(void *ip, const void *vmt) {
  vfs_fatfs_driver_c *self = (vfs_fatfs_driver_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __vfsdrv_objinit_impl(self, vmt);

  /* No initialization code.*/

  return self;
}

/**
 * @memberof    vfs_fatfs_driver_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_fatfs_driver_c instance to
 *                              be disposed.
 */
void __ffdrv_dispose_impl(void *ip) {
  vfs_fatfs_driver_c *self = (vfs_fatfs_driver_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsdrv_dispose_impl(self);
}
/** @} */

#endif /* VFS_CFG_ENABLE_DRV_FATFS == TRUE */

/** @} */
