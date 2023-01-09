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
[#macro EmitParam indent="" name="no-name" dir="boh" text="missing description"]
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
[#macro EmitBriefFromNode node=[]]
  [#if node.brief[0]??]
[@doxygen.EmitBrief "" node.brief[0] /]
  [/#if]
[/#macro]

[#--
  -- This macro generates a detailed description from an XML node.
  --]
[#macro EmitDetailsFromNode node=[]]
  [#if node.details[0]??]
[@doxygen.EmitDetails "" node.details[0] /]
  [/#if]
[/#macro]

[#--
  -- This macro generates a pre tags list from an XML nodet.
  --]
[#macro EmitPreFromNode node=[]]
  [#list node.pre as pre]
[@doxygen.EmitPre "" pre[0] /]
  [/#list]
[/#macro]

[#--
  -- This macro generates a post tags list from an XML node.
  --]
[#macro EmitPostFromNode node=[]]
  [#list node.post as post]
[@doxygen.EmitPost "" post[0] /]
  [/#list]
[/#macro]

[#--
  -- This macro generates a notes list from an XML node.
  --]
[#macro EmitNoteFromNode node=[]]
  [#list node.note as note]
[@doxygen.EmitNote "" note[0] /]
  [/#list]
[/#macro]

[#--
  -- This macro generates a params list from an XML node.
  --]
[#macro EmitParamFromNode node=[]]
  [#list node.param as param]
[@doxygen.EmitParam indent="" name=param.@name[0]!"no-name" dir=param.@dir[0]!"no-dir" text=param[0]?trim /]
  [/#list]
[/#macro]
name="no-name" dir="boh" indent="" text="missing description"
[#--
  -- This macro generates a complete Doxygen documentation comment.
  --]
[#macro EmitFullCommentNode node=[]]
/**
  [@doxygen.EmitBriefFromNode node /]
  [@doxygen.EmitDetailsFromNode node /]
  [@doxygen.EmitPreFromNode node /]
  [@doxygen.EmitPostFromNode node /]
  [@doxygen.EmitNoteFromNode node /]
 */
[/#macro]
