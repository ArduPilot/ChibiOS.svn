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
  [#-- Generating the source file.--]
  [#assign modulename        = cclasses.GetNodeName(module) /]
  [#assign moduledescription = cclasses.GetNodeDescription(module) /]
  [#assign headername        = modulename + ".h" /]
  [#assign sourcename        = modulename + ".c" /]
  [#assign docgroup          = modulename?upper_case /]
  [#-- Generating class header.--]
  [@pp.changeOutputFile name="../src/" + sourcename /]
  [@ccode.ResetState /]
  [@cclasses.ResetState /]
/*
[@license.EmitLicenseAsText /]
*/

/**
[@doxygen.EmitTagVerbatim indent="" tag="file" text=sourcename /]
[@doxygen.EmitBrief "" "Generated " + moduledescription + " source." /]
 *
[@doxygen.EmitTagVerbatim indent="" tag="addtogroup" text=docgroup /]
 * @{
 */

  [#-- Generating inclusions.--]
  [#if (module.private.inclusions[0])??]
[@ccode.GenerateInclusionsFromNode module.private.inclusions /]
  [#else]
#include "${headername}"

  [/#if]
  [#-- Handling of conditional modules.--]
  [#assign module_condition =  module.@check[0]!""?trim/]
  [#if module_condition?length > 0]
#if (${module_condition}) || defined (__DOXYGEN__)

  [/#if]
/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

[#-- Generating local definitions.--]
[@ccode.GenerateDefinesFromNode node=module.private.definitions /]
/*===========================================================================*/
/* Module local macros.                                                      */
/*===========================================================================*/

[#-- Generating multi-line macros.--]
[@ccode.GenerateMacrosFromNode node=module.private.macros /]
/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

[@ccode.GenerateVariablesFromNode "" module.public.variables false /]
/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

[#-- Generating local types.--]
[@ccode.GenerateTypesFromNode node=module.private.types /]
/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

[@ccode.GenerateVariablesFromNode "" module.private.variables true /]
/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

[@ccode.GenerateFunctionsFromNode modifiers=["static"] node=module.private.functions /]
/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

[@ccode.GenerateFunctionsFromNode node=module.public.functions /]
  [#-- Scanning all classes code to be generated in this module.--]
  [#list module.public.classes.class as class]
/*===========================================================================*/
/* Module class ${"\"" + (cclasses.GetClassCType(class) + "\"" + " methods.")?right_pad(60)}*/
/*===========================================================================*/

[@cclasses.GenerateClassWrapperCode class /]
  [/#list]
  [#if module_condition?length > 0]
#endif /* ${module_condition} */

  [/#if]
/** @} */
  [#-- Dropping the file if nothing has been generated inside.--]
  [#if (ccode.generated == false) && (cclasses.generated == false)]
    [@pp.dropOutputFile /]
  [/#if]
[/#list]
