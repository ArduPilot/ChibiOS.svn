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
  -- Global flag for generated code.
  -->
[#assign generated = false /]

<#--
  -- Coding style global settings.
  -->
[#assign indentation = "  " /]
[#assign tab = 2 /]
[#assign fields_align = 44 /]
[#assign define_value_align = 44 /]
[#assign initializers_align = 44 /]
[#assign backslash_align = 76 /]
[#assign boundary = 80 /]

[#--
  -- Returns the function/macro name from an XML node.
  --]
[#function GetName node=[]]
  [#local name = (node.@name[0]!"no-name")?trim /]
  [#return name /]
[/#function]

[#--
  -- Returns the function return C type from an XML node.
  --]
[#function GetCType node=[]]
  [#local ctype = (node.@ctype[0]!"void")?trim /]
  [#return ctype /]
[/#function]

[#--
  -- Returns the function/macro implementation from an XML node.
  --]
[#function GetImplementation node=[]]
  [#local impl = node.implementation[0]!"" /]
  [#return impl /]
[/#function]

[#--
  -- Emits a C function body code reformatting the indentation using the
  -- specified line prefix.
  --]
[#macro EmitIndentedCCode indent="  " ccode=""]
  [#local lines = ccode?string?split("^", "rm") /]
  [#list lines as line]
    [#local s = line?chop_linebreak /]
    [#if (line_index > 0) || (s?trim?length > 0)]
      [#if s?trim?length > 0]
        [#if s[0] == "#"]
${s}
        [#else]
${indent + s}
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
[#function MakeVariableDeclaration indent="" name="no-name" ctype="no-ctype"]
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
[#macro GenerateVariableDeclaration indent="" name="no-name" ctype="no-ctype"]
  [#local fstring = MakeVariableDeclaration(indent name ctype) /]
${fstring}[#rt]
[/#macro]

[#--
  -- Creates a sequence containing function parameters taken from an XML node.
  -- @note Processes the $I and $N tokens in the ccode.
  --]
[#function MakeProtoParamsSequence params=[] node=[]]
  [#list node.param as param]
    [#local name  = (param.@name[0]!"no-name")?trim
            ctype = (param.@ctype[0]!"no-type $N")?trim /]
    [#if ctype?contains("$N")]
      [#local pstring = ctype?replace("$N", name) /]
    [#else]
      [#if ctype?ends_with("*")]
        [#local pstring = ctype + "" + name /]
      [#else]
        [#local pstring = ctype + " " + name /]
      [/#if]
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
    [#local name = GetName(node) /]
  [/#if]
  [#local retctype = GetCType(node) /]
  [#local l1 = retctype + " " + name + "(" /]
  [#if modifiers?size > 0]
    [#local l1 = modifiers?join(" ") + " " + l1 /]
  [/#if]
  [#local l1 = indent + l1 /]
  [#local ln = ""?right_pad(l1?length) /]
  [#local params = MakeProtoParamsSequence(params node) /]
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
    [#local name  = (param.@name[0]!"no-name")?trim /]
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

[#--
  -- Generates inclusions from an XML node.
  --]
[#macro GenerateInclusionsFromNode node=[]]
  [#list node.include as include]
    [#assign style = (include.@style[0]!"regular")?trim /]
    [#if style == "angular"]
#include <${include[0]}>
    [#else]
#include "${include[0]}"
    [/#if]
    [#-- Empty line after last inclusion.--]
    [#if include?is_last]

    [/#if]
  [/#list]
[/#macro]

[#--
  -- Generates a single line definition macro from an XML node.
  --]
[#macro GenerateDefineFromNode node=[]]
  [#local define = node /]
  [#local name   = (define.@name[0]!"no-name")?trim
          value  = (define.@value[0]!"no-value")?trim /]
  [#if define.param[0]??]
    [#local params = MakeCallParamsSequence([], define) /]
    [#local s = ("#define " + name +  "(" + params?join(", ") + ")")?right_pad(define_value_align) + value /]
  [#else]
    [#local s = ("#define " + name +  " ")?right_pad(define_value_align) + value /]
  [/#if]
${s}
[/#macro]

[#--
  -- Generates all single line definitions from an XML node.
  --]
[#macro GenerateDefinesFromNode node=[]]
  [#list node.* as this]
    [#if this?node_name == "define"]
      [#if this.brief[0]??]
[@doxygen.EmitFullCommentFromNode "" this /]
[@ccode.GenerateDefineFromNode this /]
        [#if this?has_next || node?node_name?starts_with("definitions")]

        [/#if]
      [#else]
[@ccode.GenerateDefineFromNode this /]
        [#if node?node_name?starts_with("definitions")]

        [/#if]
      [/#if]
    [#elseif this?node_name == "group"]
      [#local groupdescription = (this.@description[0]!"no-description")?trim /]
/**
 * @name    ${groupdescription}
 * @{
 */
[@ccode.GenerateDefinesFromNode this /]
/** @} */
      [#if (node?node_name != "group") && (node?node_name != "condition")]

      [/#if]
    [#elseif this?node_name == "condition"]
      [#local condcheck = (this.@check[0]!"1")?trim /]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GenerateDefinesFromNode this /]
#endif /* ${condcheck} */
      [#if (node?node_name != "group") && (node?node_name != "condition")]

      [/#if]
    [/#if]
  [/#list]
[/#macro]

[#--
  -- Generates a conmfiguration definition from an XML node.
  --]
[#macro GenerateConfigFromNode node=[]]
  [#local config  = node /]
  [#local name    = (config.@name[0]!"no-name")?trim /]
  [#local default = (config.@default[0]!"no-default")?trim /]
  [#local s         = ("#define " + name +  " ")?right_pad(define_value_align) +
                      default /]
#if !defined(${name}) || defined(__DOXYGEN__)
${s}
#endif
[/#macro]

[#--
  -- Generates all configurations from an XML node.
  --]
[#macro GenerateConfigsFromNode node=[]]
  [#local configs = node /]
  [#if configs.config[0]??]
/**
 * @name    Configuration options
 * @{
 */
    [#list configs.* as this]
      [#if this?node_name == "config"]
[@doxygen.EmitFullCommentFromNode "" this /]
[@ccode.GenerateConfigFromNode this /]
      [/#if]
      [#if !this?is_last]

      [/#if]
    [/#list]
/** @} */

  [/#if]
[/#macro]

[#--
  -- Generates all configuration checks from an XML node.
  -- @note Processes the $N token in the check expression and message.
  --]
[#macro GenerateConfigAssertsFromNode node=[]]
  [#local configs = node /]
  [#list configs.config as config]
    [#local name    = (config.@name[0]!"no-name")?trim /]
    [#if config.assert[0]??]
/* Checks on ${name} configuration.*/
      [#list config.assert as assert]
        [#local invalid = (assert.@invalid[0]!"TRUE")?replace("$N", name)
                message = assert[0]?trim?replace("$N", name) /]
#if ${invalid}
        [#if message?length > 0]
#error "${message}"
        [#else]
#error "invalid ${name} value"
        [/#if]
#endif

      [/#list]
    [/#if]
  [/#list]
[/#macro]

[#--
  -- Generates a multi-line C macro from an XML node.
  --]
[#macro GenerateMacroFromNode indent="  " node=[]]
  [#local macro  = node /]
  [#local name   = (macro.@name[0]!"no-name")?trim /]
  [#local params = MakeCallParamsSequence([], macro) /]
  [#local macroimpl = GetImplementation(macro) /]
  [#if macroimpl?length == 0]
    [#local s      = "#define " + name + "(" + params?join(", ") + ")" /]
${s}
  [#else]
    [#local s      = ("#define " + name + "(" + params?join(", ") +
                     ") ")?right_pad(backslash_align) + "\\" /]
${s}
    [#local lines     = macroimpl?string?split("^", "rm") /]
    [#list lines?filter(line -> line?trim?length > 0) as line]
      [#local s = line?chop_linebreak /]
      [#if line?is_last]
${(indent + s + "")?right_pad(backslash_align)}
      [#else]
${(indent + s + "")?right_pad(backslash_align) + "\\"}
      [/#if]
    [/#list]
  [/#if]
[/#macro]

[#--
  -- Generates all macros from an XML node.
  --]
[#macro GenerateMacrosFromNode indent="  " node=[]]
  [#list node.* as this]
    [#if this?node_name == "macro"]
      [#if this.brief[0]?? && !this?is_first]

      [/#if]
[@doxygen.EmitFullCommentFromNode "" this /]
[@GenerateMacroFromNode node=this /]
    [#elseif this?node_name == "group"]
      [#local groupdescription = (this.@description[0]!"no-description")?trim /]
      [#if !this?is_first]

      [/#if]
/**
 * @name    ${groupdescription}
 * @{
 */
[@GenerateMacrosFromNode node=this /]
/** @} */
    [#elseif this?node_name == "condition"]
      [#local condcheck = (this.@check[0]!"1")?trim /]
      [#if !this?is_first]

      [/#if]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GenerateMacrosFromNode node=this /]
#endif /* ${condcheck} */
    [#elseif this?node_name == "elseif"]
      [#local condcheck = (this.@check[0]!"")?trim /]
      [#if !this?is_first]

      [/#if]
      [#if condcheck?length == 0]
#else
      [#else]
#elif ${condcheck}
      [/#if]
    [/#if]
    [#if this?is_last && (node?node_name?starts_with("macros"))]

    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates a simple type definition from an XML node.
  --]
[#macro GenerateTypedefFromNode indent="" node=[]]
  [#local typedef = node /]
  [#local typename = (typedef.@name!"no-name")?trim /]
  [#if typedef.basetype[0]??]
    [#local basetypename = (typedef.basetype[0].@ctype!"no-type")?trim /]
typedef ${basetypename} ${typename};
  [#elseif typedef.structtype[0]??]
  [#elseif typedef.enumtype[0]??]
  [#elseif typedef.functype[0]??]
  [#else]
  [/#if]
[/#macro]

[#--
  -- Generates all type definitions from an XML node.
  --]
[#macro GenerateTypedefsFromNode indent="" node=[]]
  [#list node.* as this]
    [#if this?node_name == "typedef"]
[@doxygen.EmitFullCommentFromNode indent this /]
[@ccode.GenerateTypedefFromNode node=this /]

    [#elseif this?node_name == "verbatim"]
      [#local ccode = (this[0]!"")?trim /]
[@EmitIndentedCCode indent ccode /]

    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates structure fields from an XML node.
  --]
[#macro GenerateStructureFields indent="" fields=[]]
  [#list fields.* as node]
    [#if node?node_name == "field"]
      [#local field = node /]
      [#local fieldname  = (field.@name[0]!"no-name")?trim
              fieldctype = (field.@ctype[0]!"no-ctype")?trim
              fieldstring = MakeVariableDeclaration("  " fieldname fieldctype) /]
[@doxygen.EmitFullCommentFromNode indent="  " node=field /]
${fieldstring}
    [#elseif node?node_name == "condition"]
      [#local condition = node /]
      [#local condcheck = (condition.@check[0]!"1")?trim /]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GenerateStructureFields indent condition /]
#endif /* ${condcheck} */
    [#elseif node?node_name == "verbatim"]
      [#local ccode = (node[0]!"")?trim /]
[@EmitIndentedCCode indent ccode /]
    [/#if]
  [/#list]
[/#macro]

[#--
  -- Generates a function from an XML node.
  --]
[#macro GenerateFunctionFromNode modifiers=[] node=[]]
  [#local funcimpl = GetImplementation(node) /]
[@GeneratePrototype modifiers=modifiers node=node /] {
[@EmitIndentedCCode indent="  " ccode=funcimpl /]
}
[/#macro]

[#--
  -- Generates all functions from an XML node.
  --]
[#macro GenerateFunctionsFromNode modifiers=[] node=[]]
  [#list node.* as this]
    [#if this?node_name == "function"]
      [#if this.brief[0]?? && !this?is_first]

      [/#if]
[@doxygen.EmitFullCommentFromNode "" this /]
[@GenerateFunctionFromNode modifiers=modifiers node=this /]
    [#elseif this?node_name == "group"]
      [#local groupdescription = (this.@description[0]!"no-description")?trim /]
      [#if !this?is_first]

      [/#if]
/**
 * @name    ${groupdescription}
 * @{
 */
[@GenerateFunctionsFromNode modifiers=modifiers node=this /]
/** @} */
    [#elseif this?node_name == "condition"]
      [#local condcheck = (this.@check[0]!"1")?trim /]
      [#if !this?is_first]

      [/#if]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GenerateFunctionsFromNode modifiers=modifiers node=this /]
#endif /* ${condcheck} */
    [#elseif this?node_name == "elseif"]
      [#local condcheck = (this.@check[0]!"")?trim /]
      [#if !this?is_first]

      [/#if]
      [#if condcheck?length == 0]
#else
      [#else]
#elif ${condcheck}
      [/#if]
    [/#if]
    [#if this?is_last && (node?node_name?starts_with("functions"))]

    [/#if]
  [/#list]
[/#macro]

[#--
  -- Generates all function prototypes from an XML node.
  -- Prototypes are generated without spacing and without comments.
  --]
[#macro GenerateFunctionPrototypesFromNode indent="  " modifiers=[] node=[]]
  [#list node.* as this]
    [#if this?node_name == "function"]
[@GeneratePrototype indent=indent modifiers=modifiers node=this /]
    [#elseif this?node_name == "group"]
[@GeneratePrototype indent=indent modifiers=modifiers node=this /]
    [#elseif this?node_name == "condition"]
      [#local condcheck = (this.@check[0]!"1")?trim /]
#if ${condcheck}
[@GeneratePrototype indent=indent modifiers=modifiers node=this /]
#endif
    [#elseif this?node_name == "elseif"]
      [#local condcheck = (this.@check[0]!"")?trim /]
      [#if condcheck?length == 0]
#else
      [#else]
#elif ${condcheck}
      [/#if]
    [/#if]
  [/#list]
[/#macro]
