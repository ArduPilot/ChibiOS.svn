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
[#assign doxygen_boundary = 80 /]
[#assign text_align = 32 /]

[#--
  -- Ouputs a formatted text starting from a "rich text" node containing
  -- text and formatting elements.
  --]
[#macro EmitRichTextFromNode p1="" pn="" textnode=[]]
  [#list textnode?children as node]
    [#if node?is_first]
      [#local l1 = p1
              ln = pn /]
    [#else]
      [#local l1 = pn
              ln = pn /]
    [/#if]
    [#if node?node_type == "text"]
      [#local text = node?trim?cap_first /]
      [#if text?matches("^.*[a-zA-Z0-9]$")]
[@utils.FormatStringAsText l1 ln utils.WithDot(text) doxygen_boundary /]
      [#else]
[@utils.FormatStringAsText l1 ln text doxygen_boundary /]
      [/#if]
    [#elseif node?node_type == "element"]
      [#if node?node_name == "verbatim"]
        [#local lines = node?string?split("^", "rm") /]
        [#list lines as line]
          [#local s = line?chop_linebreak /]
          [#if (line_index > 0) || (s?trim?length > 0)]
            [#if line?is_first]
${l1 + s}
            [#else]
${ln + s}
            [/#if]
          [/#if]
        [/#list]
      [#elseif node?node_name == "br"]
      [/#if]
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates a brief tag description.
  --]
[#macro EmitBrief indent="" text=""]
[@utils.FormatStringAsText indent + " * @brief   "
                           indent + " *          "
                           utils.WithDot(text?cap_first)
                           doxygen_boundary /]
[/#macro]

[#--
  -- This macro generates a details tag description.
  --]
[#macro EmitDetails indent="" text=""]
[@utils.FormatStringAsText indent + " * @details "
                           indent + " *          "
                           utils.WithDot(text?cap_first)
                           doxygen_boundary /]
[/#macro]

[#--
  -- This macro generates a pre tag description.
  --]
[#macro EmitPre indent="" text=""]
[@utils.FormatStringAsText indent + " * @pre     "
                           indent + " *          "
                           utils.WithDot(text?cap_first)
                           doxygen_boundary /]
[/#macro]

[#--
  -- This macro generates a post tag description.
  --]
[#macro EmitPost indent="" text=""]
[@utils.FormatStringAsText indent + " * @post    "
                           indent + " *          "
                           utils.WithDot(text?cap_first)
                           doxygen_boundary /]
[/#macro]

[#--
  -- This macro generates a note tag description.
  --]
[#macro EmitNote indent="" text=""]
[@utils.FormatStringAsText indent + " * @note    "
                           indent + " *          "
                           utils.WithDot(text?cap_first)
                           doxygen_boundary /]
[/#macro]

[#--
  -- This macro generates a param tag description.
  --]
[#macro EmitParam indent="" name="no-name" dir="boh" text="no-text"]
  [#if text?trim?length == 0]
    [#local text="missing description" /]
  [/#if]
  [#if dir == "in"]
[@utils.FormatStringAsText indent + (" * @param[in]     " + name + " ")?right_pad(text_align)
                           indent + " *"?right_pad(text_align)
                           utils.WithDot(text?cap_first)
                           doxygen_boundary /]
  [#elseif dir == "out"]
[@utils.FormatStringAsText indent + (" * @param[out]    " + name + " ")?right_pad(text_align)
                           indent + " *"?right_pad(text_align)
                           utils.WithDot(text?cap_first)
                           doxygen_boundary /]
  [#elseif dir == "both"]
[@utils.FormatStringAsText indent + (" * @param[in,out] " + name + " ")?right_pad(text_align)
                           indent + " *"?right_pad(text_align)
                           utils.WithDot(text?cap_first)
                           doxygen_boundary /]
  [#else]
[@utils.FormatStringAsText indent + (" * @param         " + name + " ")?right_pad(text_align)
                           indent + " *"?right_pad(text_align)
                           utils.WithDot(text?cap_first)
                           doxygen_boundary /]
  [/#if]
[/#macro]

[#--
  -- This macro generates a return tag description.
  --]
[#macro EmitReturn indent="" text=""]
[@utils.FormatStringAsText indent + (" * @return")?right_pad(text_align)
                           indent + " *"?right_pad(text_align)
                           utils.WithDot(text?cap_first)
                           doxygen_boundary /]
[/#macro]

[#--
  -- This macro generates a brief description from an XML node.
  --]
[#macro EmitBriefFromNode indent="" node=[]]
  [#if node.brief[0]??]
[@doxygen.EmitBrief indent node.brief[0]!"no description" /]
  [/#if]
[/#macro]

[#--
  -- This macro generates a detailed description from an XML node.
  --]
[#macro EmitDetailsFromNode indent="" node=[]]
  [#if node.details[0]??]
[@doxygen.EmitDetails indent node.details[0]!"no description" /]
  [/#if]
[/#macro]

[#--
  -- This macro generates a pre tags list from an XML nodet.
  --]
[#macro EmitPreFromNode indent="" node=[]]
  [#list node.pre as pre]
[@doxygen.EmitPre indent pre[0]!"no description" /]
  [/#list]
[/#macro]

[#--
  -- This macro generates a post tags list from an XML node.
  --]
[#macro EmitPostFromNode indent="" node=[]]
  [#list node.post as post]
[@doxygen.EmitPost indent post[0]!"no description" /]
  [/#list]
[/#macro]

[#--
  -- This macro generates a notes list from an XML node.
  --]
[#macro EmitNoteFromNode indent="" node=[]]
  [#list node.note as note]
[@doxygen.EmitNote indent note[0]!"no description" /]
  [/#list]
[/#macro]

[#--
  -- This macro generates a params list from an XML node.
  --]
[#macro EmitParamFromNode indent="" node=[]]
  [#list node.param as param]
    [#local name = param.@name[0]!"no-name"
            dir  = param.@dir[0]!"no-dir" /]
    [#if dir == "in"]
      [#local p1 = indent + (" * @param[in]     " + name + " ")?right_pad(text_align) /]
    [#elseif dir == "out"]
      [#local p1 = indent + (" * @param[out]    " + name + " ")?right_pad(text_align) /]
    [#elseif dir == "both"]
      [#local p1 = indent + (" * @param[in,out] " + name + " ")?right_pad(text_align) /]
    [#else]
      [#local p1 = indent + (" * @param         " + name + " ")?right_pad(text_align) /]
    [/#if]
    [#local pn = indent + " *"?right_pad(text_align) /]
[@EmitRichTextFromNode p1 pn param /]
  [/#list]
[/#macro]

[#--
  -- This macro generates a return tag from an XML node.
  --]
[#macro EmitReturnFromNode indent="" node=[]]
  [#list node.return as return]
[@doxygen.EmitReturn indent return[0]!"no description" /]
  [/#list]
[/#macro]

[#--
  -- This macro generates a complete Doxygen documentation comment.
  --]
[#macro EmitFullCommentFromNode indent="" node=[]
                                extraname="" extradir="" extratext=""]
  [#if node.brief[0]??]
${indent}/**
[@doxygen.EmitBriefFromNode indent node /]
[@doxygen.EmitDetailsFromNode indent node /]
[@doxygen.EmitPreFromNode indent node /]
[@doxygen.EmitPostFromNode indent node /]
[@doxygen.EmitNoteFromNode indent node /]
    [#if node.param[0]?? || node.return[0]?? || (extraname?length > 0)]
${indent} *
  [#if extraname?length > 0]
[@doxygen.EmitParam indent extraname extradir extratext /]
  [/#if]
[@doxygen.EmitParamFromNode indent node /]
[@doxygen.EmitReturnFromNode indent node /]
    [/#if]
${indent} */
  [/#if]
[/#macro]
