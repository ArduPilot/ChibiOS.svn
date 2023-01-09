[#ftl]
[#--
    ChibiOS - Copyright (C) 2006,2007,2008,2009,2010,
              2011,2012,2013,2014,2015,2016,2017,2018,
              2019,2020 Giovanni Di Sirio.

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
[#assign fields_align = 44 /]
[#assign define_value_align = 44 /]
[#assign code_boundary = 80 /]

[#--
  -- Emits a C function body code reformatting the indentation using the
  -- specified tab size and line prefix.
  --]
[#macro EmitIndentedCCode indent="  " tab=2 ccode=""]
  [#assign lines = ccode?string?split("^", "rm") /]
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
  -- Creates a sequence containing function parameters taken from an XML node. 
  --]
[#function MakeParamsSequence params=[] node=[]]
  [#list node.param as param]
    [#local name  = param.@name[0]!"no-name"?trim
            ctype = param.@ctype[0]!"no-type $"?trim /]
    [#if ctype?contains("$")]
      [#local pstring = ctype?replace("$", name) /]
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
[#macro GeneratePrototype modifiers=[] params=[] node=[]]
  [#local name = node.@name[0]!"no-name"?trim /]
  [#if node.return?? && node.return[0]??]
    [#local retctype = (node.return[0].@ctype[0]!"void")?trim /]
  [#else]
    [#local retctype = "void" /]
  [/#if]
  [#local l1 = retctype + " " + name + "(" /]
  [#if modifiers?size > 0]
    [#local l1 = modifiers?join(" ") + " " + l1 /]
  [/#if]
  [#local ln = ""?right_pad(l1?length) /]
  [#local params = MakeParamsSequence(params node) /]
  [#list params as param]
    [#if param_index == 0]
      [#local line = l1 + param /]
    [#else]
      [#if (line + ", " + param + "  ")?length > code_boundary]
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
  -- This macro generates a function prototype from an XML "function"
  -- node passed as parameter.
  -- @note Does not generate the final EOL.
  --]
[#macro GeneratePrototypeOld function={}]
  [#if function.return?? && function.return[0]??]
    [#local rettype = (function.return[0].@type[0]!"void")?trim /]
  [#else]
    [#local rettype = "void" /]
  [/#if]
  [#local name = (function.@name[0]!"no-name")?trim /]
  [#local visibility = (function.@visibility[0]!"private")?trim /]
  [#if function.param?? && function.param[0]??]
    [#-- If the function has parameters then generates the parameters list --] 
    [#local l1 = rettype + " " + name + "(" /]
    [#if visibility == "private"]
      [#local l1 = "static " + l1 /]
    [/#if]
    [#local ln = ""?right_pad(l1?length) /]
    [#list function.param as param]
      [#local type = (param.@type[0]!"no-type")?trim /]
      [#if type?contains("$")]
        [#local pstring = type?replace("$", (param.@name[0]!"no-name")?trim) /]
      [#else]
        [#local pstring = type + " " + (param.@name[0]!"no-name")?trim /]
      [/#if]
      [#local dir = (param.@dir[0]!"boh")?trim?lower_case /]
      [#if dir == "in"]
        [#local pstring = "const " + pstring /]
      [/#if]
      [#if param_index == 0]
        [#local line = l1 + pstring /]
      [#else]
        [#if (line + ", " + pstring + "  ")?length > boundary]
${line + ","}
          [#local line = ln + pstring /]
        [#else]
          [#local line = line + ", " + pstring /]
        [/#if]
      [/#if]
    [/#list]
${line + ")"}[#rt]
  [#else]
${rettype + " " + name}(void)[#rt]
  [/#if]
[/#macro]
