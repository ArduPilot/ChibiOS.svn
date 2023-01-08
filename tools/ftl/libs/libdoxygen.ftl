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
  -- This macro generates a brief description from an XML node.
  --]
[#macro EmitBriefFromNode object=[]]
  [#if object.brief[0]??]
[@doxygen.EmitBrief "" object.brief[0] /]
  [/#if]
[/#macro]

[#--
  -- This macro generates a detailed description from an XML node.
  --]
[#macro EmitDetailsFromNode object=[]]
  [#if object.details[0]??]
[@doxygen.EmitDetails "" object.details[0] /]
  [/#if]
[/#macro]

[#--
  -- This macro generates a pre tags list from an XML nodet.
  --]
[#macro EmitPreFromNode object=[]]
  [#list object.* as pre]
    [#if pre?node_name == "pre"]
[@doxygen.EmitPre "" pre[0] /]
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates a post tags list from an XML node.
  --]
[#macro EmitPostFromNode object=[]]
  [#list object.* as post]
    [#if post?node_name == "post"]
[@doxygen.EmitPost "" post[0] /]
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates a notes list from an XML node.
  --]
[#macro EmitNoteFromNode object=[]]
  [#list object.* as note]
    [#if note?node_name == "note"]
[@doxygen.EmitNote "" note[0] /]
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates a complete Doxygen documentation comment.
  --]
[#macro EmitFullCommentNode object=[]]
/**
  [@doxygen.EmitBriefFromNode object /]
  [@doxygen.EmitDetailsFromNode object /]
  [@doxygen.EmitPreFromNode object /]
  [@doxygen.EmitPostFromNode object /]
  [@doxygen.EmitNoteFromNode object /]
 */
[/#macro]
