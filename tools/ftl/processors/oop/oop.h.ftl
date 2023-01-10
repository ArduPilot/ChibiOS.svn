[#ftl]
[#--
    ChibiOS - Copyright (C) 2006..2023 Giovanni Di Sirio.

    This file is part of ChibiOS.

    ChibiOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
  --]

[#import "/@ftllibs/libutils.ftl" as utils /]
[#import "/@ftllibs/liblicense.ftl" as license /]
[#import "/@ftllibs/libdoxygen.ftl" as doxygen /]
[#import "/@ftllibs/libccode.ftl" as ccode /]
[@pp.dropOutputFile /]
[@pp.changeOutputFile name="classgen/tmp.txt" /]
[@pp.dropOutputFile /]
[#assign instance = xml.instance /]
[#assign class_suffix = "_c" /]
[#-- Scanning all files to be generated.--]
[#list instance.modules.module as module]
  [#-- Generating the header file.--]
  [#assign basename   = module.@name[0]?trim /]
  [#assign headername = basename + ".h" /]
  [#assign sourcename = basename + ".c" /]
  [#assign docgroup   = basename?upper_case /]
  [#-- Generating class header.--]
  [@pp.changeOutputFile name="../include/" + headername /]
/*
[@license.EmitLicenseAsText /]
*/

/**
 * @file    ${headername}
[@doxygen.EmitBrief "" "Generated header." /]
 *
 * @addtogroup ${docgroup}
[@doxygen.EmitBriefFromNode node=module.doc /]
[@doxygen.EmitDetailsFromNode node=module.doc /]
[@doxygen.EmitNoteFromNode node=module.doc /]
 * @{
 */
 
 #ifndef ${basename?upper_case}_H
 #define ${basename?upper_case}_H

  [#-- Generating inclusions.--]
  [#list module.inclusions.include as include]
    [#assign style = include.@style[0]!"regular" /]
    [#if style == "angular"]
#include <${include[0]}>
    [#else]
#include "${include[0]}"
    [/#if]
    [#if !include?has_next]

    [/#if]
  [/#list]
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
/* Module data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/
  [#-- Scanning all classes to be generated in this file.--]
  [#assign allabstract=true /]
  [#list module.classes.class as class]
    [#assign classname        = class.@name[0]?trim /]
    [#assign classctype       = classname + class_suffix]
    [#assign classdescr       = class.@descr[0]?trim /]
    [#assign classtype        = class.@type[0]?trim /]
    [#assign ancestorname     = class.@ancestor[0]?trim /]
    [#assign ancestorfullname = ancestorname + class_suffix]
    [#if classtype != "abstract"]
      [#assign allabstract=false /]
    [/#if]

/*===========================================================================*/
/* Class ${(classctype + ".")?right_pad(68)}*/
/*===========================================================================*/

/**
[@doxygen.EmitBrief "" "Type of a " + classdescr + " class." /]
 */
typedef struct ${classname} ${classctype};

/**
[@doxygen.EmitBrief "" "@p " + classctype + " specific methods." /]
 */
    [#assign methodsdefine = "__" + classname?lower_case + "_methods" /]
#define ${methodsdefine?right_pad(68) + "\\"}
    [#if ancestorname?length == 0]
  /* Instance offset, used for multiple inheritance, normally zero. It
     represents the offset between the current object and the container
     object*/                                                               \
  size_t instance_offset;                                                   \
    [#else]
${("  __" + ancestorname?lower_case?lower_case + "_methods")?right_pad(76)}\
      [#list class.methods.method as method]
        [#assign methodname     = method.@name[0]!"no-name"?trim /]
        [#assign methodsname    = method.@shortname[0]!""?trim /]
        [#assign methodtype     = method.@type[0]?trim /]
        [#assign methodretctype = method.return.@ctype[0]!""?trim /]
        [#if methodsname?length == 0]
          [#assign methodsname = methodname?lower_case /]
        [/#if]
        [#if methodretctype?length == 0]
          [#assign methodretctype = "void" /]
        [/#if]
        [#if methodtype=="virtual"]
          [#assign fptr = "  " + methodretctype + " (*" + methodsname + ")(" +
                          ccode.MakeParamsSequence(["void *ip"] method)?join(", ") +
                          ");" /]
${fptr?right_pad(76)}\
        [/#if]
      [/#list]
    [/#if]
  /* end methods */

/**
[@doxygen.EmitBrief "" "@p " + classctype + " specific data." /]
 */
    [#assign datadefine = "__" + classname?lower_case + "_data" /]
#define ${datadefine?right_pad(68) + "\\"}
    [#if ancestorname?length > 0]
  __${(ancestorname + "_data")?right_pad(72) + "\\"}
    [#else]
    [/#if]
    [#list class.fields.field as field]
      [#assign fieldname  = field.@name[0]?trim /]
      [#assign fieldctype = field.@ctype[0]?trim /]
      [#assign fstring = ccode.MakeVariable("  " fieldctype fieldname)?right_pad(76) /]
${fstring}\
    [/#list]
  /* end data */

/**
[@doxygen.EmitBrief "" "@p " + classctype + " virtual methods table." /]
 */
struct ${classname?lower_case}_vmt {
  ${methodsdefine}
};

/**
[@doxygen.EmitBrief "" "Structure representing a " + classdescr + " class." /]
 */
struct ${classname?lower_case} {
  /**
[@doxygen.EmitBrief "  " "Virtual Methods Table." /]
   */
  [#assign vmtctype  = "const struct " + classname?lower_case + "_vmt$I*$N" /]
${ccode.MakeVariable("  " vmtctype "vmt")}
  ${datadefine}
};

/**
 * @name    Methods implementations (${classctype})
 * @{
 */
/**
[@doxygen.EmitBrief "" "Implementation of object creation." /]
[@doxygen.EmitNote  "" "This function is meant to be used by derived classes." /]
 *
[@doxygen.EmitParam name="ip" dir="out"
                    text="Pointer to a @p " + classctype + " structure to be initialized." /]
[@doxygen.EmitParam name="vmt" dir="in"
                    text="VMT pointer for the new object." /]
[@doxygen.EmitReturn text="A new reference to the object." /]
 */
CC_FORCE_INLINE
static inline void *__${classname}_objinit_impl(void *ip, const void *vmt) {
  ${classctype} *self = (${classctype} *)ip;

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
[@doxygen.EmitBrief "" "Implementation of object finalization." /]
[@doxygen.EmitNote  "" "This function is meant to be used by derived classes." /]
 *
[@doxygen.EmitParam name="ip" dir="both"
                    text="Pointer to a @p " + classctype + " structure to be disposed." /]
 */
CC_FORCE_INLINE
static inline void __${classname}_dispose_impl(void *ip) {
  ${classctype} *self = (${classctype} *)ip;

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
    [#list class.methods.method as method]
      [#assign methodname     = method.@name[0]?trim /]
      [#assign methodsname    = method.@shortname[0]!""?trim /]
      [#assign methodtype     = method.@type[0]?trim /]
      [#assign methodretctype = method.return.@ctype[0]?trim /]
      [#assign methodimpl     = method.implementation[0]!""?trim /]
      [#if methodsname?length == 0]
        [#assign methodsname = methodname?lower_case /]
      [/#if]
      [#if methodretctype?length == 0]
        [#assign methodretctype = "void" /]
      [/#if]
      [#if (methodtype=="virtual") && (methodimpl?length > 0)]

/**
[@doxygen.EmitBrief "" "Implementation of method @p " + methodname + "()." /]
[@doxygen.EmitNote  "" "This function is meant to be used by derived classes." /]
 *
[@doxygen.EmitParam name="ip" dir="both"
                    text="Pointer to a @p " + classctype + " structure." /]
[@doxygen.EmitParamFromNode node=method /]
 */
CC_FORCE_INLINE
[@ccode.GeneratePrototype name      = "__" + classname + "_" + methodsname + "_impl"
                          modifiers = ["static" "inline"]
                          params    = ["void *ip"]
                          node      = method /] {
  ${classctype} *self = (${classctype} *)ip;

[@utils.EmitIndentedCCode start="  " tab=2 ccode=methodimpl /]
}
      [/#if]
    [/#list]
/** @} */
  [/#list]

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

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
    [#list module.classes.class as class]
      [#assign classname        = class.@name[0]?trim /]
      [#assign classctype       = classname + class_suffix]
      [#assign classdescr       = class.@descr[0]?trim /]
      [#assign classtype        = class.@type[0]?trim /]
      [#assign ancestorname     = class.@ancestor[0]?trim /]
      [#assign ancestorfullname = classname + class_suffix]
/*===========================================================================*/
/* Module class ${(classctype + ".")?right_pad(61)}*/
/*===========================================================================*/

    [/#list]
  [/#if]
[/#list]
