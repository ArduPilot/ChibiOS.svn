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
  [#assign sourcename = basename + ".c" /]
  [#assign docgroup   = basename?upper_case /]
  [#-- Generating class header.--]
  [@pp.changeOutputFile name="../src/" + sourcename /]
/*
[@license.EmitLicenseAsText /]
*/

/**
 * @file    ${sourcename}
[@doxygen.EmitBrief "" "Generated source." /]
 *
 * @addtogroup ${docgroup}
 * @{
 */

#include "${headername}"

/*===========================================================================*/
/* Module local definitions.                                                 */
/*===========================================================================*/

[@ccode.GenerateDefinesFromNode node=module.private.definitions /]
/*===========================================================================*/
/* Module exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Module local types.                                                       */
/*===========================================================================*/

[@ccode.GenerateTypedefsFromNode node=module.private.types /]
/*===========================================================================*/
/* Module local variables.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Module local functions.                                                   */
/*===========================================================================*/

  [#-- Scanning all public methods to be generated in this file.--]
  [#list module.public.classes.class as class]
/*===========================================================================*/
/* Module class ${"\"" + (cclasses.GetClassCType(class) + "\"" + " methods.")?right_pad(61)}*/
/*===========================================================================*/

[@cclasses.GenerateClassRegularMethods class /]
  [/#list]
/*===========================================================================*/
/* Module exported functions.                                                */
/*===========================================================================*/

/** @} */
[/#list]
