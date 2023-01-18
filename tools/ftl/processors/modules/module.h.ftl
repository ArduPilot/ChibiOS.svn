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
[#import "/@ftllibs/libcclasses.ftl" as cclasses /]
[@pp.dropOutputFile /]
[@pp.changeOutputFile name="classgen/tmp.txt" /]
[@pp.dropOutputFile /]
[#assign instance = xml.instance /]
[#-- Scanning all files to be generated.--]
[#list instance.modules.module as module]
  [#-- Generating the header file.--]
  [#assign basename   = module.@name[0]?trim /]
  [#assign headername = basename + ".h" /]
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
[@doxygen.EmitBriefFromNode node=module /]
[@doxygen.EmitDetailsFromNode node=module /]
[@doxygen.EmitNoteFromNode node=module /]
 * @{
 */
 
 #ifndef ${basename?upper_case}_H
 #define ${basename?upper_case}_H

  [#-- Generating inclusions.--]
  [#list module.public.inclusions.include as include]
    [#assign style = include.@style[0]!"regular" /]
    [#if style == "angular"]
#include <${include[0]}>
    [#else]
#include "${include[0]}"
    [/#if]
    [#-- Empty line after last inclusion.--]
    [#if include?is_last]

    [/#if]
  [/#list]
/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

[@ccode.GenerateDefinesFromNode node=module.public.definitions /]
/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

[@ccode.GenerateConfigsFromNode node=module.public.configs /]
/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

[@ccode.GenerateTypedefsFromNode node=module.public.types /]
/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

[@ccode.GenerateMacrosFromNode node=module.public.macros /]
  [#-- Scanning all classes to be generated in this module.--]
  [#list module.public.classes.class as class]
/*===========================================================================*/
/* Module class ${cclasses.GetClassCType(class)?right_pad(61)}*/
/*===========================================================================*/

[@cclasses.GenerateClassWrapper class /]
[@cclasses.GenerateClassMethodsImplementations class /]
[@cclasses.GenerateClassIndirectMethods class /]
  [/#list]
/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  [#list module.public.classes.class as class]
[@cclasses.GenerateClassRegularMethodsPrototypes class /]
  [/#list]
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

#endif /* ${basename?upper_case}_H */

/** @} */
[/#list]
