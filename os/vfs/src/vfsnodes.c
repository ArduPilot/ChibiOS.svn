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
 * @file        vfsnodes.c
 * @brief       Generated VFS Nodes source.
 * @note        This is a generated file, do not edit directly.
 *
 * @addtogroup  VFSNODES
 * @{
 */

#include "vfs.h"

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

/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module class "vfs_node_c" methods.                                        */
/*===========================================================================*/

/**
 * @name        Virtual methods implementations of vfs_node_c
 * @{
 */
/**
 * @memberof    vfs_node_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_node_c instance to be
 *                              initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
void *__vfsnode_objinit_impl(void *ip, const void *vmt) {
  vfs_node_c *self = (vfs_node_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __ro_objinit_impl(self, vmt);

  /* No initialization code.*/

  return self;
}

/**
 * @memberof    vfs_node_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_node_c instance to be
 *                              disposed.
 */
void __vfsnode_dispose_impl(void *ip) {
  vfs_node_c *self = (vfs_node_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __ro_dispose_impl(self);
}
/** @} */

/*===========================================================================*/
/* Module class "vfs_directory_node_c" methods.                              */
/*===========================================================================*/

/**
 * @name        Virtual methods implementations of vfs_directory_node_c
 * @{
 */
/**
 * @memberof    vfs_directory_node_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_directory_node_c instance
 *                              to be initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
void *__vfsdir_objinit_impl(void *ip, const void *vmt) {
  vfs_directory_node_c *self = (vfs_directory_node_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __vfsnode_objinit_impl(self, vmt);

  /* No initialization code.*/

  return self;
}

/**
 * @memberof    vfs_directory_node_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_directory_node_c instance
 *                              to be disposed.
 */
void __vfsdir_dispose_impl(void *ip) {
  vfs_directory_node_c *self = (vfs_directory_node_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsnode_dispose_impl(self);
}
/** @} */

/*===========================================================================*/
/* Module class "vfs_file_node_c" methods.                                   */
/*===========================================================================*/

/**
 * @name        Virtual methods implementations of vfs_file_node_c
 * @{
 */
/**
 * @memberof    vfs_file_node_c
 * @protected
 *
 * @brief       Implementation of object creation.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[out]    ip            Pointer to a @p vfs_file_node_c instance to be
 *                              initialized.
 * @param[in]     vmt           VMT pointer for the new object.
 * @return                      A new reference to the object.
 */
void *__vfsfile_objinit_impl(void *ip, const void *vmt) {
  vfs_file_node_c *self = (vfs_file_node_c *)ip;

  /* Initialization of the ancestors-defined parts.*/
  __vfsnode_objinit_impl(self, vmt);

  /* No initialization code.*/

  return self;
}

/**
 * @memberof    vfs_file_node_c
 * @protected
 *
 * @brief       Implementation of object finalization.
 * @note        This function is meant to be used by derived classes.
 *
 * @param[in,out] ip            Pointer to a @p vfs_file_node_c instance to be
 *                              disposed.
 */
void __vfsfile_dispose_impl(void *ip) {
  vfs_file_node_c *self = (vfs_file_node_c *)ip;

  /* No finalization code.*/
  (void)self;

  /* Finalization of the ancestors-defined parts.*/
  __vfsnode_dispose_impl(self);
}
/** @} */

/** @} */
