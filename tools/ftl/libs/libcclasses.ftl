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

[#assign class_suffix = "_c" /]

[#--
  -- Returns the class name from an XML node.
  --]
[#function GetClassName node=[]]
  [#local class = node /]
  [#local classname = class.@name[0]!"no-name"?trim /]
  [#return classname /]
[/#function]

[#--
  -- Returns the C type of the class from an XML node.
  --]
[#function GetClassCType node=[]]
  [#local class = node /]
  [#local classname  = GetClassName(class)
          classctype = classname + class_suffix /]
  [#return classctype /]
[/#function]

[#--
  -- Returns the class description from an XML node.
  --]
[#function GetClassDescription node=[]]
  [#local class = node /]
  [#local classdescr = class.@descr[0]!"no-descr"?trim /]
  [#return classdescr /]
[/#function]

[#--
  -- Returns the class ancestor name from an XML node.
  --]
[#function GetClassAncestorName node=[]]
  [#local class = node /]
  [#local ancestorname = class.@ancestor[0]!"no-ancestor"?trim /]
  [#return ancestorname /]
[/#function]

[#--
  -- Returns the C type of the class from an XML node.
  --]
[#function GetClassAncestorCType node=[]]
  [#local class = node /]
  [#local ancestorname  = GetClassAncestorName(class)
          ancestorctype = ancestorname + class_suffix /]
  [#return ancestorctype /]
[/#function]

[#--
  -- Returns the method name from an XML node.
  --]
[#function GetMethodName node=[]]
  [#local method = node /]
  [#local methodname = method.@name[0]!"no-name"?trim /]
  [#return methodname /]
[/#function]

[#--
  -- Returns the method short name from an XML node.
  --]
[#function GetMethodShortName node=[]]
  [#local method = node /]
  [#local methodsname = method.@shortname[0]!""?trim /]
    [#if methodsname?length == 0]
      [#local methodsname = GetMethodName(method)?lower_case /]
    [/#if]
  [#return methodsname /]
[/#function]

[#--
  -- Returns the method return C type from an XML node.
  --]
[#function GetMethodCType node=[]]
  [#local method = node /]
  [#local methodctype = method.@ctype[0]!"void"?trim /]
  [#return methodctype /]
[/#function]

[#--
  -- This macro generates a class wrapper from an XML node.
  --]
[#macro GenerateClassWrapper node=[]]
  [#local class = node /]
  [#local classname        = GetClassName(class)
          classctype       = GetClassCType(class)
          classdescr       = GetClassDescription(class)
          ancestorname     = GetClassAncestorName(class)
          ancestorfullname = GetClassAncestorCType(class) /]
/**
[@doxygen.EmitBrief "" "Type of a " + classdescr + " class." /]
 */
typedef struct ${classname} ${classctype};

/**
[@doxygen.EmitBrief "" "@p " + classctype + " specific methods." /]
 */
  [#local methodsdefine = "__" + classname?lower_case + "_methods" /]
#define ${methodsdefine?right_pad(68) + "\\"}
  [#if ancestorname?length == 0]
      [#-- Special case where the class has no ancestor.--]
  /* Instance offset, used for multiple inheritance, normally zero. It
     represents the offset between the current object and the container
     object*/                                                               \
  size_t instance_offset;                                                   \
  [#else]
${("  __" + ancestorname?lower_case?lower_case + "_methods")?right_pad(76)}\
  [/#if]
  [#-- Generating list of virtual methods in the VMT.--]
  [#list class.methods.* as method]
    [#local methodname     = GetMethodName(method)
            methodsname    = GetMethodShortName(method)
            methodretctype = GetMethodCType(method) /]
    [#if (method?node_name == "abstract") || (method?node_name == "virtual")]
      [#local funcptr = "  " + methodretctype + " (*" + methodsname + ")(" +
                        ccode.MakeProtoParamsSequence(["void *ip"] method)?join(", ") +
                        ");" /]
${funcptr?right_pad(76)}\
    [/#if]
  [/#list]
  /* end methods */

/**
[@doxygen.EmitBrief "" "@p " + classctype + " specific data." /]
 */
  [#local datadefine = "__" + classname?lower_case + "_data" /]
#define ${datadefine?right_pad(68) + "\\"}
  [#if ancestorname?length > 0]
  __${(ancestorname + "_data")?right_pad(72) + "\\"}
  [/#if]
  [#list class.fields.field as field]
    [#local fieldname  = field.@name[0]?trim
            fieldctype = field.@ctype[0]?trim
            fieldstring = ccode.MakeVariableDeclaration("  " fieldctype fieldname)?right_pad(76) /]
${fieldstring}\
  [/#list]
  /* end data */

/**
[@doxygen.EmitBrief "" "@p " + classctype + " virtual methods table." /]
 */
struct ${classname?lower_case}_vmt {
  ${methodsdefine}
};

/**
[@doxygen.EmitBrief "" "Structure representing a " + classdescr + " class." /]
 */
struct ${classname?lower_case} {
  /**
[@doxygen.EmitBrief "  " "Virtual Methods Table." /]
   */
  [#local vmtctype  = "const struct " + classname?lower_case + "_vmt$I*$N" /]
${ccode.MakeVariableDeclaration("  " vmtctype "vmt")}
  ${datadefine}
};

[/#macro]

[#--
  -- This macro generates class method implementations from an XML node.
  --]
[#macro GenerateClassMethodsImplementations node=[]]
  [#local class = node /]
  [#local classname        = GetClassName(class)
          classctype       = GetClassCType(class)
          classdescr       = GetClassDescription(class)
          ancestorname     = GetClassAncestorName(class)
          ancestorfullname = GetClassAncestorCType(class) /]
/**
 * @name    Methods implementations (${classctype})
 * @{
 */
/**
[@doxygen.EmitBrief "" "Implementation of object creation." /]
[@doxygen.EmitNote  "" "This function is meant to be used by derived classes." /]
 *
[@doxygen.EmitParam name="ip" dir="out"
                    text="Pointer to a @p " + classctype + " structure to be initialized." /]
[@doxygen.EmitParam name="vmt" dir="in"
                    text="VMT pointer for the new object." /]
[@doxygen.EmitReturn text="A new reference to the object." /]
 */
CC_FORCE_INLINE
static inline void *__${classname}_objinit_impl(void *ip, const void *vmt) {
  ${classctype} *self = (${classctype} *)ip;

  [#if ancestorname?length == 0]
  /* This is a root class, initializing the VMT pointer here.*/
  self->vmt = (struct base_object_vmt *)vmt;

  [#else]
  /* Initialization of the ancestors-defined parts.*/
  __${ancestorname}_objinit_impl(self, vmt);

  [/#if]
  [#if (class.methods.objinit[0].implementation[0])?? &&
       (class.methods.objinit[0].implementation[0]?trim?length > 0)]
  /* Initialization code.*/
[@ccode.EmitIndentedCCode indent="  " ccode=class.methods.objinit[0].implementation[0]?string /]
  [#else]
  /* No initialization code.*/
  [/#if]

  return self;
}

/**
[@doxygen.EmitBrief "" "Implementation of object finalization." /]
[@doxygen.EmitNote  "" "This function is meant to be used by derived classes." /]
 *
[@doxygen.EmitParam name="ip" dir="both"
                    text="Pointer to a @p " + classctype + " structure to be disposed." /]
 */
CC_FORCE_INLINE
static inline void __${classname}_dispose_impl(void *ip) {
  ${classctype} *self = (${classctype} *)ip;

  [#if ancestorname?length > 0]
  __${ancestorname}_dispose_impl(self);

  [/#if]
  [#if (class.methods.dispose[0].implementation[0])?? &&
       (class.methods.dispose[0].implementation[0]?trim?length > 0)]
  /* Finalization code.*/
[@ccode.EmitIndentedCCode indent="  " ccode=class.methods.dispose[0].implementation[0]?string /]
  [#else]
  /* No finalization code.*/
  (void)self;
  [/#if]
}
  [#list class.methods.* as method]
    [#local methodname     = GetMethodName(method)
            methodsname    = GetMethodShortName(method)
            methodretctype = GetMethodCType(method)
            methodimpl     = method.implementation[0]!""?trim /]
    [#if method?node_name == "virtual"]

/**
[@doxygen.EmitBrief "" "Implementation of method @p " + methodname + "()." /]
[@doxygen.EmitNote  "" "This function is meant to be used by derived classes." /]
 *
[@doxygen.EmitParam name="ip" dir="both"
                    text="Pointer to a @p " + classctype + " structure." /]
[@doxygen.EmitParamFromNode node=method /]
[@doxygen.EmitReturnFromNode node=method /]
 */
CC_FORCE_INLINE
[@ccode.GeneratePrototype indent    = ""
                          name      = "__" + classname + "_" + methodsname + "_impl"
                          modifiers = ["static" "inline"]
                          params    = ["void *ip"]
                          node      = method /] {
  ${classctype} *self = (${classctype} *)ip;

[@ccode.EmitIndentedCCode indent="  " ccode=methodimpl /]
}
    [/#if]
  [/#list]
/** @} */

[/#macro]

[#--
  -- This macro generates abstract/virtual methods as inline functions
  -- from an XML node.
  --]
[#macro GenerateClassIndirectMethods node=[]]
  [#local class = node /]
  [#if (class.methods.virtual?size > 0) || (class.methods.abstract?size > 0)]
    [#local classname        = GetClassName(class)
            classctype       = GetClassCType(class)
            classdescr       = GetClassDescription(class)
            ancestorname     = GetClassAncestorName(class)
            ancestorfullname = GetClassAncestorCType(class) /]
/**
 * @name    Abstract/Virtual methods of (${classctype})
 * @{
 */
    [#local first = true /]
    [#list class.methods.* as method]
      [#local methodname     = GetMethodName(method)
              methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method)
              methodimpl     = method.implementation[0]!""?trim /]
      [#if (method?node_name == "abstract") ||
           (method?node_name == "virtual")]
        [#if !first]

        [/#if]
        [#local first = false /]
/**
[@doxygen.EmitBriefFromNode node=method /]
[@doxygen.EmitDetailsFromNode node=method /]
[@doxygen.EmitPreFromNode node=method /]
[@doxygen.EmitPostFromNode node=method /]
[@doxygen.EmitNoteFromNode node=method /]
 *
[@doxygen.EmitParam name="ip" dir="both"
                    text="Pointer to a @p " + classctype + " structure." /]
[@doxygen.EmitParamFromNode node=method /]
[@doxygen.EmitReturnFromNode node=method /]
 */
CC_FORCE_INLINE
[@ccode.GeneratePrototype modifiers = ["static", "inline"]
                          params    = ["void *ip"]
                          node=method /] {
  ${classctype} *self = (${classctype} *)ip;

        [#local callname   = "self->vmt->" + methodsname /]
        [#local callparams = ccode.MakeCallParamsSequence(["ip"] method) /]
        [#if methodretctype == "void"]
[@ccode.GenerateFunctionCall "  " "" callname callparams /]
        [#else]
[@ccode.GenerateFunctionCall "  " "return" callname callparams /]
        [/#if]
}
      [/#if]
    [/#list]
/** @} */

  [/#if]
[/#macro]

[#--
  -- This macro generates regular methods as inline functions from an XML node.
  --]
[#macro GenerateClassRegularMethodsPrototypes node=[]]
  [#local class = node /]
  [#local classname        = GetClassName(class)
          classctype       = GetClassCType(class)
          classdescr       = GetClassDescription(class)
          ancestorname     = GetClassAncestorName(class)
          ancestorfullname = GetClassAncestorCType(class) /]
  [#if class.methods.method?size > 0]
  /* Methods of ${classctype}.*/
    [#list class.methods.method as method]
      [#local methodname     = GetMethodName(method)
              methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method)
              methodimpl     = method.implementation[0]!""?trim /]
[@ccode.GeneratePrototype indent    = "  "
                          modifiers = []
                          params    = ["const void *ip"]
                          node=method /];
    [/#list]
  [/#if]
[/#macro]

[#--
  -- This macro generates regular methods as inline functions from an XML node.
  --]
[#macro GenerateClassRegularMethods node=[]]
  [#local class = node /]
  [#local classname        = GetClassName(class)
          classctype       = GetClassCType(class)
          classdescr       = GetClassDescription(class)
          ancestorname     = GetClassAncestorName(class)
          ancestorfullname = GetClassAncestorCType(class) /]
  [#if class.methods.method?size > 0]
/**
 * @name    Regular methods of (${classctype})
 * @{
 */
    [#list class.methods.method as method]
      [#local methodname     = GetMethodName(method)
              methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method)
              methodimpl     = method.implementation[0]!""?trim /]
/**
[@doxygen.EmitBriefFromNode node=method /]
[@doxygen.EmitDetailsFromNode node=method /]
[@doxygen.EmitPreFromNode node=method /]
[@doxygen.EmitPostFromNode node=method /]
[@doxygen.EmitNoteFromNode node=method /]
 *
[@doxygen.EmitParam name="ip" dir="both"
                    text="Pointer to a @p " + classctype + " structure." /]
[@doxygen.EmitParamFromNode node=method /]
[@doxygen.EmitReturnFromNode node=method /]
 */
[@ccode.GeneratePrototype modifiers = []
                          params    = ["const void *ip"]
                          node=method /] {
  ${classctype} *self = (${classctype} *)ip;

[@ccode.EmitIndentedCCode indent="  " ccode=methodimpl /]
}
      [#if method?has_next]

      [/#if]
    [/#list]
/** @} */

  [/#if]
[/#macro]
