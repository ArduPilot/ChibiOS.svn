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
 * @file        vfsnodes.h
 * @brief       Generated VFS Nodes header.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  VFSNODES
 * @brief       Common ancestor class of all reference-counted objects.
 * @{
 */
 
#ifndef VFSNODES_H
#define VFSNODES_H

/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

/**
 * @name    Node types
 * @{
 */
#define VFS_MODE_S_IFMT                     S_IFMT
#define VFS_MODE_S_IFREG                    S_IFREG
#define VFS_MODE_S_IFDIR                    S_IFDIR
#define VFS_MODE_S_IFCHR                    S_IFCHR
#define VFS_MODE_S_IFIFO                    S_IFIFO
/** @} */

/**
 * @name    Node access for User
 * @{
 */
#define VFS_MODE_S_IRWXU                    S_IRWXU
#define VFS_MODE_S_IRUSR                    S_IRUSR
#define VFS_MODE_S_IWUSR                    S_IWUSR
#define VFS_MODE_S_IXUSR                    S_IXUSR
/** @} */

/**
 * @name    Node helpers
 * @{
 */
#define VFS_MODE_S_ISREG(mode)              S_ISREG(mode)
#define VFS_MODE_S_ISDIR(mode)              S_ISDIR(mode)
#define VFS_MODE_S_ISCHR(mode)              S_ISCHR(mode)
#define VFS_MODE_S_ISFIFO(mode)             S_ISFIFO(mode)
/** @} */

/**
 * @name    Seek modes compatible with Posix
 * @{
 */
#define VFS_SEEK_SET                        SEEK_SET
#define VFS_SEEK_CUR                        SEEK_CUR
#define VFS_SEEK_END                        SEEK_END
/** @} */

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

typedef struct vfs_driver vfs_driver_c;

/**
 * @brief       Type of a file offset.
 */
typedef int32_t vfs_offset_t;

/**
 * @brief       Type of a node mode.
 */
typedef int32_t vfs_mode_t;

/**
 * @brief       Type of a seek mode.
 */
typedef int vfs_seekmode_t;

/**
 * @brief       Type of a directory entry structure.
 */
typedef struct vfs_direntry_info vfs_direntry_info_t;

/**
 * @brief       Type of a node information structure.
 * @note        Add time, permissions etc.
 */
typedef struct vfs_stat vfs_stat_t;

/**
 * @brief       Structure representing a directory entry.
 */
struct vfs_direntry_info {
  /**
   * @brief       Node mode.
   */
  vfs_mode_t                mode;
  /**
   * @brief       Size of the node.
   */
  vfs_offset_t              size;
  /**
   * @brief       Name of the node.
   */
  char                      name[VFS_CFG_NAMELEN_MAX + 1];
};

/**
 * @brief       Structure representing a node information.
 */
struct vfs_stat {
  /**
   * @brief       Node mode.
   */
  vfs_mode_t                mode;
  /**
   * @brief       Size of the node.
   */
  vfs_offset_t              size;
};

/**
 * @class       vfs_node_c
 * @extends     referenced_object_c
 *
 * @brief       Common ancestor class of all VFS nodes.
 * @note        The class namespace is <tt>vfsnode</tt>, access to class fields
 *              is done using: <tt><objp>->vfsnode.<fieldname></tt><br>Note
 *              that fields of ancestor classes are in their own namespace in
 *              order to avoid field naming conflicts.
 *
 * @name        Class @p vfs_node_c structures
 * @{
 */

/**
 * @brief       Type of a VFS node class.
 */
typedef struct vfs_node vfs_node_c;

/**
 * @brief       Class @p vfs_node_c methods as a structure.
 */
struct vfsnode_methods {
  msg_t (*stat)(void *ip, vfs_stat_t *sp);
};

/**
 * @brief       Class @p vfs_node_c data as a structure.
 */
struct vfsnode_data {
  /**
   * @brief       Driver handling this node.
   */
  vfs_driver_c              *driver;
  /**
   * @brief       Node mode information.
   */
  vfs_mode_t                mode;
};

/**
 * @brief       Class @p vfs_node_c methods.
 */
#define __vfsnode_methods                                                   \
  __ro_methods                                                              \
  struct vfsnode_methods    vfsnode;

/**
 * @brief       Class @p vfs_node_c data.
 */
#define __vfsnode_data                                                      \
  __ro_data                                                                 \
  struct vfsnode_data       vfsnode;

/**
 * @brief       Class @p vfs_node_c VMT initializer.
 */
#define __vfsnode_vmt_init(ns)                                              \
  __ro_vmt_init(ns)                                                         \
  .vfsnode.stat                             = __##ns##_vfsnode_stat_impl,

/**
 * @brief       Class @p vfs_node_c virtual methods table.
 */
struct vfs_node_vmt {
  __vfsnode_methods
};

/**
 * @brief       Structure representing a VFS node class.
 */
struct vfs_node {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_node_vmt *vmt;
  __vfsnode_data
};
/** @} */

/**
 * @class       vfs_directory_node_c
 * @extends     vfs_node_c
 *
 * @brief       Ancestor class of all VFS directory nodes classes.
 * @note        The class namespace is <tt>vfsdir</tt>, access to class fields
 *              is done using: <tt><objp>->vfsdir.<fieldname></tt><br>Note that
 *              fields of ancestor classes are in their own namespace in order
 *              to avoid field naming conflicts.
 *
 * @name        Class @p vfs_directory_node_c structures
 * @{
 */

/**
 * @brief       Type of a VFS directory node class.
 */
typedef struct vfs_directory_node vfs_directory_node_c;

/**
 * @brief       Class @p vfs_directory_node_c methods as a structure.
 */
struct vfsdir_methods {
  msg_t (*first)(void *ip, vfs_direntry_info_t *dip);
  msg_t (*next)(void *ip, vfs_direntry_info_t *dip);
};

/**
 * @brief       Class @p vfs_directory_node_c methods.
 */
#define __vfsdir_methods                                                    \
  __vfsnode_methods                                                         \
  struct vfsdir_methods     vfsdir;

/**
 * @brief       Class @p vfs_directory_node_c data.
 */
#define __vfsdir_data                                                       \
  __vfsnode_data                                                            \
  /* No data.*/

/**
 * @brief       Class @p vfs_directory_node_c VMT initializer.
 */
#define __vfsdir_vmt_init(ns)                                               \
  __vfsnode_vmt_init(ns)                                                    \
  .vfsdir.first                             = __##ns##_vfsdir_first_impl,   \
  .vfsdir.next                              = __##ns##_vfsdir_next_impl,

/**
 * @brief       Class @p vfs_directory_node_c virtual methods table.
 */
struct vfs_directory_node_vmt {
  __vfsdir_methods
};

/**
 * @brief       Structure representing a VFS directory node class.
 */
struct vfs_directory_node {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_directory_node_vmt *vmt;
  __vfsdir_data
};
/** @} */

/**
 * @class       vfs_file_node_c
 * @extends     vfs_node_c
 *
 * @brief       Ancestor class of all VFS file nodes classes.
 * @note        The class namespace is <tt>vfsfile</tt>, access to class fields
 *              is done using: <tt><objp>->vfsfile.<fieldname></tt><br>Note
 *              that fields of ancestor classes are in their own namespace in
 *              order to avoid field naming conflicts.
 *
 * @name        Class @p vfs_file_node_c structures
 * @{
 */

/**
 * @brief       Type of a VFS file node class.
 */
typedef struct vfs_file_node vfs_file_node_c;

/**
 * @brief       Class @p vfs_file_node_c methods as a structure.
 */
struct vfsfile_methods {
  ssize_t (*read)(void *ip, uint8_t *buf, size_t n);
  ssize_t (*write)(void *ip, const uint8_t *buf, size_t n);
  msg_t (*setpos)(void *ip, vfs_offset_t offset, vfs_seekmode_t whence);
  vfs_offset_t (*getpos)(void *ip);
  BaseSequentialStream * (*getstream)(void *ip);
};

/**
 * @brief       Class @p vfs_file_node_c methods.
 */
#define __vfsfile_methods                                                   \
  __vfsnode_methods                                                         \
  struct vfsfile_methods    vfsfile;

/**
 * @brief       Class @p vfs_file_node_c data.
 */
#define __vfsfile_data                                                      \
  __vfsnode_data                                                            \
  /* No data.*/

/**
 * @brief       Class @p vfs_file_node_c VMT initializer.
 */
#define __vfsfile_vmt_init(ns)                                              \
  __vfsnode_vmt_init(ns)                                                    \
  .vfsfile.read                             = __##ns##_vfsfile_read_impl,   \
  .vfsfile.write                            = __##ns##_vfsfile_write_impl,  \
  .vfsfile.setpos                           = __##ns##_vfsfile_setpos_impl, \
  .vfsfile.getpos                           = __##ns##_vfsfile_getpos_impl, \
  .vfsfile.getstream                        = __##ns##_vfsfile_getstream_impl,

/**
 * @brief       Class @p vfs_file_node_c virtual methods table.
 */
struct vfs_file_node_vmt {
  __vfsfile_methods
};

/**
 * @brief       Structure representing a VFS file node class.
 */
struct vfs_file_node {
  /**
   * @brief       Virtual Methods Table.
   */
  const struct vfs_file_node_vmt *vmt;
  __vfsfile_data
};
/** @} */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  /* Methods of vfs_node_c.*/
  void *__vfsnode_objinit_impl(void *ip, const void *vmt);
  void __vfsnode_dispose_impl(void *ip);
  msg_t __vfsnode_stat_impl(void *ip, vfs_stat_t *sp);
  /* Methods of vfs_directory_node_c.*/
  void *__vfsdir_objinit_impl(void *ip, const void *vmt);
  void __vfsdir_dispose_impl(void *ip);
  msg_t __vfsdir_first_impl(void *ip, vfs_direntry_info_t *dip);
  msg_t __vfsdir_next_impl(void *ip, vfs_direntry_info_t *dip);
  /* Methods of vfs_file_node_c.*/
  void *__vfsfile_objinit_impl(void *ip, const void *vmt);
  void __vfsfile_dispose_impl(void *ip);
  ssize_t __vfsfile_read_impl(void *ip, uint8_t *buf, size_t n);
  ssize_t __vfsfile_write_impl(void *ip, const uint8_t *buf, size_t n);
  msg_t __vfsfile_setpos_impl(void *ip, vfs_offset_t offset,
                              vfs_seekmode_t whence);
  vfs_offset_t __vfsfile_getpos_impl(void *ip);
  BaseSequentialStream *__vfsfile_getstream_impl(void *ip);
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

/**
 * @name        Virtual methods of vfs_node_c
 * @{
 */
/**
 * @memberof    vfs_node_c
 * @public
 *
 * @brief       Returns information about the node.
 *
 * @param[in,out] ip            Pointer to a @p vfs_node_c instance.
 * @param[out]    sp            Pointer to a @p vfs_stat_t structure.
 * @return                      The operation result.
 *
 * @api
 */
CC_FORCE_INLINE
static inline msg_t vfsNodeStat(void *ip, vfs_stat_t *sp) {
  vfs_node_c *self = (vfs_node_c *)ip;

  return self->vmt->vfsnode.stat(ip, sp);
}
/** @} */

/**
 * @name        Virtual methods of vfs_directory_node_c
 * @{
 */
/**
 * @memberof    vfs_directory_node_c
 * @public
 *
 * @brief       First directory entry.
 *
 * @param[in,out] ip            Pointer to a @p vfs_directory_node_c instance.
 * @param[out]    dip           Pointer to a @p vfs_direntry_info_t structure.
 * @return                      The operation result.
 *
 * @api
 */
CC_FORCE_INLINE
static inline msg_t vfsDirReadFirst(void *ip, vfs_direntry_info_t *dip) {
  vfs_directory_node_c *self = (vfs_directory_node_c *)ip;

  return self->vmt->vfsdir.first(ip, dip);
}

/**
 * @memberof    vfs_directory_node_c
 * @public
 *
 * @brief       Next directory entry.
 *
 * @param[in,out] ip            Pointer to a @p vfs_directory_node_c instance.
 * @param[out]    dip           Pointer to a @p vfs_direntry_info_t structure.
 * @return                      The operation result.
 *
 * @api
 */
CC_FORCE_INLINE
static inline msg_t vfsDirReadNext(void *ip, vfs_direntry_info_t *dip) {
  vfs_directory_node_c *self = (vfs_directory_node_c *)ip;

  return self->vmt->vfsdir.next(ip, dip);
}
/** @} */

/**
 * @name        Virtual methods of vfs_file_node_c
 * @{
 */
/**
 * @memberof    vfs_file_node_c
 * @public
 *
 * @brief       File node read.
 *
 * @param[in,out] ip            Pointer to a @p vfs_file_node_c instance.
 * @param[out]    buf           Pointer to the data buffer.
 * @param[in]     n             Maximum amount of data to be transferred.
 * @return                      The transferred number of bytes or an error.
 *
 * @api
 */
CC_FORCE_INLINE
static inline ssize_t vfsFileRead(void *ip, uint8_t *buf, size_t n) {
  vfs_file_node_c *self = (vfs_file_node_c *)ip;

  return self->vmt->vfsfile.read(ip, buf, n);
}

/**
 * @memberof    vfs_file_node_c
 * @public
 *
 * @brief       File node read.
 *
 * @param[in,out] ip            Pointer to a @p vfs_file_node_c instance.
 * @param[in]     buf           Pointer to the data buffer.
 * @param[in]     n             Maximum amount of data to be transferred.
 * @return                      The transferred number of bytes or an error.
 *
 * @api
 */
CC_FORCE_INLINE
static inline ssize_t vfsFileWrite(void *ip, const uint8_t *buf, size_t n) {
  vfs_file_node_c *self = (vfs_file_node_c *)ip;

  return self->vmt->vfsfile.write(ip, buf, n);
}

/**
 * @memberof    vfs_file_node_c
 * @public
 *
 * @brief       Changes the current file position.
 *
 * @param[in,out] ip            Pointer to a @p vfs_file_node_c instance.
 * @param[in]     offset        Offset to be applied.
 * @param[in]     whence        Seek mode to be used.
 * @return                      The operation result.
 *
 * @api
 */
CC_FORCE_INLINE
static inline msg_t vfsFileSetPosition(void *ip, vfs_offset_t offset,
                                       vfs_seekmode_t whence) {
  vfs_file_node_c *self = (vfs_file_node_c *)ip;

  return self->vmt->vfsfile.setpos(ip, offset, whence);
}

/**
 * @memberof    vfs_file_node_c
 * @public
 *
 * @brief       Returns the current file position.
 *
 * @param[in,out] ip            Pointer to a @p vfs_file_node_c instance.
 * @return                      The current file position.
 *
 * @api
 */
CC_FORCE_INLINE
static inline vfs_offset_t vfsFileGetPosition(void *ip) {
  vfs_file_node_c *self = (vfs_file_node_c *)ip;

  return self->vmt->vfsfile.getpos(ip);
}

/**
 * @memberof    vfs_file_node_c
 * @public
 *
 * @brief       Returns the inner HAL stream associated to the file.
 *
 * @param[in,out] ip            Pointer to a @p vfs_file_node_c instance.
 * @return                      Pointer to the HAL stream interface.
 *
 * @api
 */
CC_FORCE_INLINE
static inline BaseSequentialStream *vfsFileGetStream(void *ip) {
  vfs_file_node_c *self = (vfs_file_node_c *)ip;

  return self->vmt->vfsfile.getstream(ip);
}
/** @} */

#endif /* VFSNODES_H */

/** @} */
