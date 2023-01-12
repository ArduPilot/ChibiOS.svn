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

<#--
  -- Coding style global settings.
  -->
[#assign indentation = "  " /]
[#assign tab = 2 /]
[#assign fields_align = 44 /]
[#assign define_value_align = 44 /]
[#assign boundary = 80 /]

[#--
  -- Emits a C function body code reformatting the indentation using the
  -- specified tab size and line prefix.
  --]
[#macro EmitIndentedCCode indent="  " ccode=""]
  [#local lines = ccode?string?split("^", "rm") /]
  [#list lines as line]
    [#if (line_index > 0) || (line?trim?length > 0)]
      [#if line?trim?length > 0]
        [#if line[0] == "#"]
${line?chop_linebreak}
        [#else]
${(indent + line)?chop_linebreak}
        [/#if]
      [#else]

      [/#if]
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This function generates a variable or field declaration in a string.
  -- @note Processes the $I and $N tokens in the ctype.
  --]
[#function MakeVariableDeclaration indent="" ctype="" name=""]
  [#if ctype?contains("$I")]
    [#local s1 = ctype?keep_before("$I")?trim
            s2 = ctype?keep_after("$I")?trim /]
    [#local fstring = (indent + s1 + " ")?right_pad(fields_align) + s2 /]
    [#if fstring?contains("$N")]
      [#local fstring = fstring?replace("$N", name) /]
    [#else]
      [#local fstring = fstring + name /]
    [/#if]
  [#else]
    [#local fstring = indent + ctype /]
    [#if fstring?contains("$N")]
      [#local fstring = fstring?replace("$N", name) /]
    [#else]
      [#local fstring = (fstring + " ")?right_pad(fields_align) + name /]
    [/#if]
  [/#if]
  [#return fstring + ";"/]
[/#function]

[#--
  -- This macro generates a variable or field.
  -- @note Does not generate the final EOL.
  -- @note Processes the $I and $N tokens in the ctype.
  --]
[#macro GenerateVariableDeclaration indent="" ctype="" name=""]
  [#local fstring = MakeVariableDeclaration(indent ctype name) /]
${fstring}[#rt]
[/#macro]

[#--
  -- Creates a sequence containing function parameters taken from an XML node.
  -- @note Processes the $I and $N tokens in the ccode.
  --]
[#function MakeParamsSequence params=[] node=[]]
  [#list node.param as param]
    [#local name  = param.@name[0]!"no-name"?trim
            ctype = param.@ctype[0]!"no-type $N"?trim /]
    [#if ctype?contains("$N")]
      [#local pstring = ctype?replace("$N", name) /]
    [#else]
      [#local pstring = ctype + " " + name /]
    [/#if]
    [#local params = params + [pstring] /]
  [/#list]
  [#if params?size == 0]
    [#local params = ["void"] /]
  [/#if] 
  [#return params /]
[/#function]

[#--
  -- This macro generates a function prototype from an XML node.
  -- @note Does not generate the final EOL.
  --]
[#macro GeneratePrototype indent="" name="" modifiers=[] params=[] node=[]]
  [#if name?length == 0]
    [#local name = node.@name[0]!"no-name"?trim /]
  [/#if]
  [#local retctype = node.@ctype[0]!"void"?trim /]
  [#local l1 = retctype + " " + name + "(" /]
  [#if modifiers?size > 0]
    [#local l1 = modifiers?join(" ") + " " + l1 /]
  [/#if]
  [#local l1 = indent + l1 /]
  [#local ln = ""?right_pad(l1?length) /]
  [#local params = MakeParamsSequence(params node) /]
  [#list params as param]
    [#if param_index == 0]
      [#local line = l1 + param /]
    [#else]
      [#if (line + ", " + param + "  ")?length > boundary]
${line + ","}
        [#local line = ln + param /]
      [#else]
        [#local line = line + ", " + param /]
      [/#if]
    [/#if]
  [/#list]
${line + ")"}[#rt]
[/#macro]

[#--
  -- Creates a sequence containing parameters names taken from an XML node.
  --]
[#function MakeCallParamsSequence params=[] node=[]]
  [#list node.param as param]
    [#local name  = param.@name[0]!"no-name"?trim /]
    [#local params = params + [name] /]
  [/#list]
  [#return params /]
[/#function]

[#--
  -- This macro generates a function call.
  --]
[#macro GenerateFunctionCall indent="" destination="" name="" params=[]]
  [#if name?length == 0]
    [#local name = "no-name" /]
  [/#if]
  [#local l1   = indent + destination?trim + " " + name + "(" /]
  [#local ln   = ""?right_pad(l1?length) /]
  [#local line = l1 /]
  [#list params as param]
    [#if param_index == 0]
      [#local line = l1 + param /]
    [#else]
      [#if (line + ", " + param + "  ")?length > boundary]
${line + ","}
        [#local line = ln + param /]
      [#else]
        [#local line = line + ", " + param /]
      [/#if]
    [/#if]
  [/#list]
${line + ");"}
[/#macro]
