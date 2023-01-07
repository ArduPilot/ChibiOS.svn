[#ftl]
[#--
    ChibiOS/RT - Copyright (C) 2006..2023 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
  --]
[#import "/@ftllibs/libutils.ftl" as utils /]
[#import "/@ftllibs/liblicense.ftl" as license /]
[@pp.changeOutputFile name="classgen/tmp.txt" /]
[@pp.dropOutputFile /]
[#assign instance = xml.instance /]
[#assign class_suffix = "_c" /]
[#-- Scanning all files to be generated.--]
[#list instance.files.file as file]
  [#-- Generating the header file.--]
  [#assign basename   = file.@name[0]?trim /]
  [#assign headername = basename + ".h" /]
  [#assign sourcename = basename + ".c" /]
  [#assign docgroup   = file.@docgroup[0]?trim /]
  [#-- Generating class header.--]
  [@pp.changeOutputFile name="../include/" + headername /]
/*
[@license.EmitLicenseAsText /]
*/

/**
 * @file    ${headername}
 * @brief   Generated OOP header.
 * @details TODO
 *
 * @addtogroup ${docgroup}
 * @{
 */
 
 #ifndef ${basename?upper_case}_H
 #define ${basename?upper_case}_H
  [#-- Generating inclusions.--]
/* TODO inclusions */
  [#-- Scanning all classes to be generated in this file.--]
  [#assign allabstract=true /]
  [#list file.classes.class as class]
    [#assign classname        = class.@name[0]?trim /]
    [#assign classfullname    = classname + class_suffix]
    [#assign classdescr       = class.@descr[0]?trim /]
    [#assign classtype        = class.@type[0]?trim /]
    [#assign ancestorname     = class.@ancestor[0]?trim /]
    [#assign ancestorfullname = classname + class_suffix]
    [#if classtype != "abstract"]
      [#assign allabstract=false /]
    [/#if]

/*===========================================================================*/
/* Class ${(classfullname + ".")?right_pad(68)}*/
/*===========================================================================*/

/**
 * @brief   Type of a ${classdescr} class.
 * @details TODO
 */
typedef struct ${classname} ${classfullname};

/**
 * @brief   @p ${classfullname} specific methods.
 */
    [#assign methodsdefine = "__" + classname?lower_case + "_methods" /]
#define ${methodsdefine?right_pad(68) + "\\"}
    [#if ancestorname?length == 0]
  /* Instance offset, used for multiple inheritance, normally zero. It
     represents the offset between the current object and the container
     object*/                                                               \
  size_t instance_offset;                                                   \
    [#else]
    [/#if]
  /* end methods */

/**
 * @brief   @p ${classfullname} specific data.
 * @details TODO
 */
    [#assign datadefine = "__" + classname?lower_case + "_data" /]
#define ${datadefine?right_pad(68) + "\\"}
    [#if ancestorname?length > 0]
  __${(ancestorname + "_data")?right_pad(66) + "\\"}
    [#else]
    [/#if]
  /* end data */

/**
 * @brief   @p ${classfullname} virtual methods table.
 */
struct ${classname?lower_case}_vmt {
  ${methodsdefine}
};

/**
 * @brief   Structure representing a ${classdescr} class.
 */
struct ${classname?lower_case} {
  /**
   * @brief   Virtual Methods Table.
   */
  const struct ${(classname?lower_case + "_vmt")?right_pad(28)} *vmt;
  ${datadefine}
};

/**
 * @name    Methods implementations
 * @{
 */
/**
 * @brief   Object creation implementation.
 *
 * @param[out] ip       Pointer to a @p ${classfullname} structure
 *                      to be initialized.
 * @param[in] vmt       VMT pointer for the new object.
 * @return              A new reference to the object.
 */
CC_FORCE_INLINE
static inline void *__${classname}_objinit_impl(void *ip, const void *vmt) {
  ${classname} *self = (${classname} *)ip;

    [#if ancestorname?length == 0]
  /* This is a root class, initializing the VMT pointer here.*/
  self->vmt = (struct base_object_vmt *)vmt;

    [#else]
  /* Initialization of the ancestors-defined parts.*/
  __${ancestorname}_objinit_impl(self);

    [/#if]
    [#if class.init.implementation[0]?? &&
         (class.dispose.implementation[0]?trim?length > 0)]
  /* Initialization code.*/
[@utils.EmitIndentedCCode start="  " tab=2 ccode=class.init.implementation[0]?string /]
    [#else]
  /* No initialization code.*/
    [/#if]

  return self;
}

/**
 * @brief   Object finalization implementation.
 *
 * @param[in] ip        Pointer to a @p ${classfullname} structure
 *                      to be disposed.
 */
CC_FORCE_INLINE
static inline void __${classname}_dispose_impl(void *ip) {
  ${classname} *self = (${classname} *)ip;

    [#if ancestorname?length > 0]
  __${ancestorname}_dispose_impl(self);

    [/#if]
    [#if class.dispose.implementation[0]?? &&
         (class.dispose.implementation[0]?trim?length > 0)]
  /* Finalization code.*/
[@utils.EmitIndentedCCode start="  " tab=2 ccode=class.dispose.implementation[0]?string /]
    [#else]
  /* No finalization code.*/
  (void)self;
    [/#if]
}
/** @} */
  [/#list]

#endif /* ${basename?upper_case}_H */

/** @} */
  [#if allabstract==allabstract]
    [#-- Generating class source, if not abstract.--]
    [@pp.changeOutputFile name="../src/" + sourcename /]
/*
[@license.EmitLicenseAsText /]
*/

/**
 * @file    ${sourcename}
 * @brief   Generated OOP source.
 * @details TODO
 *
 * @addtogroup ${docgroup}
 * @{
 */

#include "${headername}"

  [#-- Scanning all classes to be generated in this file.--]
    [#list file.classes.class as class]
      [#assign classname        = class.@name[0]?trim /]
      [#assign classfullname    = classname + class_suffix]
      [#assign classdescr       = class.@descr[0]?trim /]
      [#assign classtype        = class.@type[0]?trim /]
      [#assign ancestorname     = class.@ancestor[0]?trim /]
      [#assign ancestorfullname = classname + class_suffix]
/*===========================================================================*/
/* Class ${(classfullname + ".")?right_pad(68)}*/
/*===========================================================================*/
    [/#list]
  [/#if]
[/#list]
