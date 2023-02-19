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
[#assign instance = xml.instance /]
[#-- Scanning all files to be generated.--]
[#list instance.modules.module as module]
  [#-- Generating the header file.--]
  [#assign modulename        = cclasses.GetNodeName(module) /]
  [#assign moduledescription = cclasses.GetNodeDescription(module) /]
  [#assign modulesheaderpath = (module.@headerpath[0]!"include")?trim?ensure_ends_with("/") /]
  [#assign moduleheadername  = modulename + ".h" /]
  [#assign moduledocgroup    = modulename?upper_case /]
  [#-- Generating class header.--]
  [@pp.changeOutputFile name=pp.home?trim?ensure_ends_with("/") + modulesheaderpath + moduleheadername /]
  [@ccode.ResetState /]
  [@cclasses.ResetState /]
/*
[@license.EmitLicenseAsText /]
*/

/**
[@doxygen.EmitTagVerbatim indent="" tag="file" text=moduleheadername /]
[@doxygen.EmitBrief "" "Generated " + moduledescription + " header." /]
[@doxygen.EmitNote text="This is a generated file, do not edit directly." /]
 *
[@doxygen.EmitTagVerbatim indent="" tag="addtogroup" text=moduledocgroup /]
[@doxygen.EmitBriefFromNode node=module /]
[@doxygen.EmitDetailsFromNode node=module /]
[@doxygen.EmitNoteFromNode node=module /]
 * @{
 */
 
#ifndef ${moduledocgroup}_H
#define ${moduledocgroup}_H

  [#-- Generating inclusions.--]
  [#if (module.public.inclusions[0])??]
[@ccode.GenerateInclusionsFromNode module.public.inclusions /]
  [/#if]
  [#-- Handling of conditional modules.--]
  [#assign module_condition =  module.@check[0]!""?trim/]
  [#if module_condition?length > 0]
#if (${module_condition}) || defined (__DOXYGEN__)

  [/#if]
/*===========================================================================*/
/* Module constants.                                                         */
/*===========================================================================*/

[#-- Generating early definitions.--]
[@ccode.GenerateDefinesFromNode node=module.public.definitions_early /]
/*===========================================================================*/
/* Module pre-compile time settings.                                         */
/*===========================================================================*/

[#-- Generating configuration options.--]
[@ccode.GenerateConfigsFromNode node=module.public.configs /]
/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

[#-- Generating checks on configuration options.--]
[@ccode.GenerateConfigAssertsFromNode node=module.public.configs /]
[#-- Generating late definitions.--]
[@ccode.GenerateDefinesFromNode node=module.public.definitions_late /]
/*===========================================================================*/
/* Module macros.                                                            */
/*===========================================================================*/

[#-- Generating multi-line macros.--]
[@ccode.GenerateMacrosFromNode node=module.public.macros /]
/*===========================================================================*/
/* Module data structures and types.                                         */
/*===========================================================================*/

[#-- Generating types declarations.--]
[@ccode.GenerateTypesFromNode node=module.public.types /]
/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

[@ccode.GenerateVariablesExternFromNode "" module.public.variables /]
#ifdef __cplusplus
extern "C" {
#endif
  [#list module.public.types.class as class]
[@cclasses.GenerateClassMethodsPrototypes class /]
  [/#list]
  [#if module.public.functions[0]??]
  /* Regular functions.*/
[@ccode.GenerateFunctionPrototypesFromNode node=module.public.functions /]
  [/#if]
#ifdef __cplusplus
}
#endif

/*===========================================================================*/
/* Module inline functions.                                                  */
/*===========================================================================*/

  [#-- Scanning all interfaces.--]
  [#list module.public.types.interface as if]
[@cclasses.GenerateInterfaceVirtualMethods if /]
  [/#list]
  [#-- Scanning all classes.--]
  [#list module.public.types.class as class]
[@cclasses.GenerateClassConstructorDestructor class /]
[@cclasses.GenerateClassVirtualMethods class /]
[@cclasses.GenerateClassInlineMethods class /]
  [/#list]
  [#if module_condition?length > 0]
#endif /* ${module_condition} */

  [/#if]
#endif /* ${moduledocgroup}_H */

/** @} */
[/#list]
