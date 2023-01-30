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

[#assign class_suffix = "_c" /]
[#assign interface_suffix = "_i" /]

[#--
  -- Returns the interface name from an XML node.
  --]
[#function GetInterfaceName node=[]]
  [#local if = node /]
  [#local ifname = (if.@name[0]!"no-name")?trim /]
  [#return ifname /]
[/#function]

[#--
  -- Returns the interface C type from an XML node.
  --]
[#function GetInterfaceCType node=[]]
  [#local if = node /]
  [#local ifname  = GetInterfaceName(if)
          ifctype = ifname + interface_suffix /]
  [#return ifctype /]
[/#function]

[#--
  -- Returns the interface namespace from an XML node.
  --]
[#function GetInterfaceNamespace node=[]]
  [#local if = node /]
  [#local ifnamespace = (if.@namespace[0]!"no-namespace")?trim /]
  [#return ifnamespace /]
[/#function]

[#--
  -- Returns the interface description from an XML node.
  --]
[#function GetInterfaceDescription node=[]]
  [#local if = node /]
  [#local ifdescr = (if.@descr[0]!"no-descr")?trim /]
  [#return ifdescr /]
[/#function]

[#--
  -- Returns the interface ancestor name from an XML node.
  --]
[#function GetInterfaceAncestorName node=[]]
  [#local if = node /]
  [#local ancestorname = (if.@ancestor[0]!"")?trim /]
  [#return ancestorname /]
[/#function]

[#--
  -- Returns the interface ancestor C type from an XML node.
  --]
[#function GetInterfaceAncestorCType node=[]]
  [#local if = node /]
  [#local ancestorname  = GetInterfaceAncestorName(if)
          ancestorctype = ancestorname + interface_suffix /]
  [#return ancestorctype /]
[/#function]

[#--
  -- Returns the class name from an XML node.
  --]
[#function GetClassName node=[]]
  [#local class = node /]
  [#local classname = (class.@name[0]!"no-name")?trim /]
  [#return classname /]
[/#function]

[#--
  -- Returns the class type from an XML node.
  --]
[#function GetClassType node=[]]
  [#local class = node /]
  [#local classtype = (class.@type[0]!"no-type")?trim /]
  [#return classtype /]
[/#function]

[#--
  -- Returns the class namespace from an XML node.
  --]
[#function GetClassNamespace node=[]]
  [#local class = node /]
  [#local classnamespace = (class.@namespace[0]!"no-namespace")?trim /]
  [#return classnamespace /]
[/#function]

[#--
  -- Returns the class C type from an XML node.
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
  [#local classdescr = (class.@descr[0]!"no-descr")?trim /]
  [#return classdescr /]
[/#function]

[#--
  -- Returns the class ancestor name from an XML node.
  --]
[#function GetClassAncestorName node=[]]
  [#local class = node /]
  [#local ancestorname = (class.@ancestor[0]!"")?trim /]
  [#return ancestorname /]
[/#function]

[#--
  -- Returns the class ancestor C type from an XML node.
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
  [#local methodname = (method.@name[0]!"no-name")?trim /]
  [#return methodname /]
[/#function]

[#--
  -- Returns the method short name from an XML node.
  --]
[#function GetMethodShortName node=[]]
  [#local method = node /]
  [#local methodsname = (method.@shortname[0]!"")?trim /]
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
  [#local methodctype = (method.@ctype[0]!"void")?trim /]
  [#return methodctype /]
[/#function]

[#--
  -- This macro generates virtual methods pointers from an XML node.
  --]
[#macro GeneratMethodsPointers methods=[] ipctype="void *"]
  [#list methods.* as node]
    [#if node?node_name == "method"]
      [#local method = node /]
      [#local methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method) /]
      [#local funcptr = "  " + methodretctype + " (*" + methodsname + ")(" +
                        ccode.MakeProtoParamsSequence([ipctype + "ip"] method)?join(", ") +
                        ");" /]
${funcptr}
    [#elseif node?node_name == "condition"]
      [#local condition = node /]
      [#local condcheck = (condition.@check[0]!"1")?trim /]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GeneratMethodsPointers condition /]
#endif /* ${condcheck} */
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates a VMT initializer macro from an XML node.
  --]
[#macro GenerateClassVMTInitializers methods=[] namespace="no-namespace"]
  [#list methods.* as node]
    [#if node?node_name == "method"]
      [#local method = node /]
      [#local methodsname    = GetMethodShortName(method) /]
      [#local s = ("  ." + namespace + "." + methodsname)?right_pad(ccode.initializers_align) +
                  ("= __##ns##_" + namespace + "_" + methodsname) /]
      [#if node?has_next]
        [#local s = (s + ", ")?right_pad(ccode.backslash_align) + "\\" /]
      [/#if]
${s}
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates a VMT structure from an XML node.
  --]
[#macro GenerateClassVMTStructure node=[]]
  [#local class = node /]
  [#local classname        = GetClassName(class)
          classtype        = GetClassType(class)
          classnamespace   = GetClassNamespace(class)
          classctype       = GetClassCType(class)
          classdescr       = GetClassDescription(class)
          ancestorname     = GetClassAncestorName(class) /]
  [#if classtype == "regular"]
    [#assign generated = true /]
/**
[@doxygen.EmitBrief "" "VMT structure of " + classdescr + " class." /]
 */
static const struct ${classname}_vmt ${classnamespace}_vmt = {
  __${ancestorname}_vmt_init((size_t)offsetof(${classctype}, vmt), ${classnamespace})
};

  [/#if]
[/#macro]

[#--
  -- This macro generates a class wrapper from an XML node.
  --]
[#macro GenerateClassWrapper node=[]]
  [#local class = node /]
  [#local classname        = GetClassName(class)
          classnamespace   = GetClassNamespace(class)
          classctype       = GetClassCType(class)
          classdescr       = GetClassDescription(class)
          ancestorname     = GetClassAncestorName(class)
          ancestorfullname = GetClassAncestorCType(class) /]
/**
[@doxygen.EmitBrief "" "Type of a " + classdescr + " class." /]
 */
typedef struct ${classname} ${classctype};

  [#local methodsstruct = classname?lower_case + "_methods" /]
  [#if node.methods.virtual?size > 0]
/**
[@doxygen.EmitBrief "" "@p " + classctype + " methods as a structure." /]
 */
struct ${methodsstruct} {
[@GeneratMethodsPointers class.methods.virtual /]
};

  [/#if]
  [#local datastruct = classname?lower_case + "_data" /]
  [#if class.fields.*?size > 0]
/**
[@doxygen.EmitBrief "" "@p " + classctype + " data as a structure." /]
 */
struct ${datastruct} {
[@ccode.GenerateStructureFields "  " class.fields /]
};

  [/#if]
/**
[@doxygen.EmitBrief "" "@p " + classctype + " methods." /]
 */
  [#local methodsdefine = "__" + classname?lower_case + "_methods" /]
#define ${methodsdefine?right_pad(68) + "\\"}
  [#if ancestorname?length > 0]
${("  __" + ancestorname?lower_case?lower_case + "_methods")?right_pad(76)}\
  [#else]
    [#local instance_string = ccode.MakeVariableDeclaration("  "
                                                            "instance_offset"
                                                            "size_t")?right_pad(76) + "\\" /]
  /* This field represents the offset between the current object
     and the container object.*/                                            \
${instance_string}
  [/#if]
  [#if class.methods.virtual?size > 0]
[@ccode.GenerateVariableDeclaration indent="  "
                                    name=classnamespace
                                    ctype="struct " + methodsstruct /]


  [#else]
  /* no methods */

  [/#if]
/**
[@doxygen.EmitBrief "" "@p " + classctype + " data." /]
 */
  [#local datadefine = "__" + classname?lower_case + "_data" /]
#define ${datadefine?right_pad(68) + "\\"}
  [#if ancestorname?length > 0]
${("  __" + ancestorname?lower_case + "_data")?right_pad(76)}\
  [/#if]
  [#if class.fields.*?size > 0]
[@ccode.GenerateVariableDeclaration indent="  "
                                    name=classnamespace
                                    ctype="struct " + datastruct /]


  [#else]
  /* no data */

  [/#if]
/**
[@doxygen.EmitBrief "" "@p " + classctype + " VMT initializer." /]
 */
  [#local vmtinitsdefine = "__" + classname?lower_case + "_vmt_init(offset, ns)" /]
#define ${vmtinitsdefine?right_pad(68) + "\\"}
  [#if ancestorname?length > 0]
    [#local s = "  __" + ancestorname?lower_case + "_vmt_init(offset, ns)" /]
    [#if node.methods.virtual?size > 0]
      [#local s = (s + ", ")?right_pad(76) + "\\" /]
    [/#if]
${s}
[@GenerateClassVMTInitializers methods=node.methods.virtual namespace=classnamespace /]
  [#else]
  .instance_offset                          = (offset)
  [/#if]

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
${ccode.MakeVariableDeclaration("  " "vmt" vmtctype)}
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
  [#list class.methods.virtual.* as node]
    [#if node?node_name == "method"]
      [#local method=node /]
      [#local methodname     = GetMethodName(method)
              methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method)
              methodimpl     = (method.implementation[0]!"")?trim /]
      [#if methodimpl?length > 0]

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
    [/#if]
  [/#list]
/** @} */

[/#macro]

[#--
  -- This macro generates virtual methods from an XML node.
  --]
[#macro GeneratVirtualMethods methods=[] classctype="void" classnamespace=""]
  [#list methods.* as node]
    [#if node?node_name == "method"]
      [#local method = node /]
      [#local methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method) /]
[@doxygen.EmitFullCommentFromNode indent="" node=method
                                  extraname="ip" extradir="both"
                                  extratext="Pointer to a @p " + classctype + " structure." /]
CC_FORCE_INLINE
[@ccode.GeneratePrototype modifiers = ["static", "inline"]
                          params    = ["void *ip"]
                          node=method /] {
  ${classctype} *self = (${classctype} *)ip;

        [#local callname   = "self->vmt->" + classnamespace + "." + methodsname /]
        [#local callparams = ccode.MakeCallParamsSequence(["ip"] method) /]
        [#if methodretctype == "void"]
[@ccode.GenerateFunctionCall "  " "" callname callparams /]
        [#else]
[@ccode.GenerateFunctionCall "  " "return" callname callparams /]
        [/#if]
}
    [#elseif node?node_name == "condition"]
      [#local condition = node /]
      [#local condcheck = (condition.@check[0]!"1")?trim /]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GeneratVirtualMethods condition classctype classnamespace /]
#endif /* ${condcheck} */
    [/#if]
    [#if node?has_next]

    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates virtual methods as inline functions
  -- from an XML node.
  --]
[#macro GenerateClassVirtualMethods node=[]]
  [#local class = node /]
  [#if class.methods.virtual.*?size > 0]
    [#local classnamespace = GetClassNamespace(class)
            classctype     = GetClassCType(class) /]
/**
 * @name    Virtual methods of (${classctype})
 * @{
 */
[@GeneratVirtualMethods class.methods.virtual classctype classnamespace /]
/** @} */

  [/#if]
[/#macro]

[#--
  -- This macro generates regular method prototypes from an XML node.
  --]
[#macro GenerateRegularMethodsPrototypes methods=[]]
  [#list methods.* as node]
    [#if node?node_name == "method"]
      [#local method = node /]
      [#local methodname     = GetMethodName(method)
              methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method) /]
[@ccode.GeneratePrototype indent    = "  "
                          modifiers = []
                          params    = ["const void *ip"]
                          node=method /];
    [#elseif node?node_name == "condition"]
      [#local condition = node /]
      [#local condcheck = (condition.@check[0]!"1")?trim /]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GenerateRegularMethodsPrototypes condition /]
#endif /* ${condcheck} */
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates regular method prototypes from a class XML node.
  --]
[#macro GenerateClassRegularMethodsPrototypes class=[]]
  [#if class.methods.regular.*?size > 0]
  /* Methods of ${GetClassCType(class)}.*/
[@GenerateRegularMethodsPrototypes class.methods.regular /]
  [/#if]
[/#macro]

[#--
  -- This macro generates regular methods from an XML node.
  --]
[#macro GenerateRegularMethods methods=[] classctype="void"]
  [#list methods.* as node]
    [#if node?node_name == "method"]
      [#local method = node /]
      [#local methodname     = GetMethodName(method)
              methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method)
              methodimpl     = (method.implementation[0]!"")?trim /]
[@doxygen.EmitFullCommentFromNode indent="" node=method
                                  extraname="ip" extradir="both"
                                  extratext="Pointer to a @p " + classctype + " structure." /]
[@ccode.GeneratePrototype modifiers = []
                          params    = ["const void *ip"]
                          node=method /] {
  ${classctype} *self = (${classctype} *)ip;

[@ccode.EmitIndentedCCode indent="  " ccode=methodimpl /]
}
    [#elseif node?node_name == "condition"]
      [#local condition = node /]
      [#local condcheck = (condition.@check[0]!"1")?trim /]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GenerateRegularMethods condition classctype /]
#endif /* ${condcheck} */
    [/#if]
    [#if node?has_next]

    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates regular methods from a class XML node.
  --]
[#macro GenerateClassRegularMethods class=[]]
  [#if class.methods.regular.*?size > 0]
    [#local classctype = GetClassCType(class) /]
    [#assign generated = true /]
/**
 * @name    Regular methods of (${classctype})
 * @{
 */
[@GenerateRegularMethods class.methods.regular classctype /]
/** @} */

  [/#if]
[/#macro]

[#--
  -- This macro generates a class wrapper from an XML node.
  --]
[#macro GenerateInterfaceWrapper node=[]]
  [#local if = node /]
  [#local ifname           = GetInterfaceName(if)
          ifnamespace      = GetInterfaceNamespace(if)
          ifctype          = GetInterfaceCType(if)
          ifdescr          = GetInterfaceDescription(if)
          ancestorname     = GetInterfaceAncestorName(if)
          ancestorfullname = GetInterfaceAncestorCType(if) /]
/**
[@doxygen.EmitBrief "" "Type of a " + ifdescr + " interface." /]
 */
typedef struct ${ifname} ${ifctype};

  [#local methodsstruct = ifname?lower_case + "_methods" /]
  [#if node.methods.method?size > 0]
/**
[@doxygen.EmitBrief "" "@p " + ifctype + " methods as a structure." /]
 */
struct ${methodsstruct} {
[@GeneratMethodsPointers methods=if.methods /]
};

  [/#if]
/**
[@doxygen.EmitBrief "" "@p " + ifctype + " methods." /]
 */
  [#local methodsdefine = "__" + ifname?lower_case + "_methods" /]
#define ${methodsdefine?right_pad(68) + "\\"}
  [#if ancestorname?length > 0]
${("  __" + ancestorname?lower_case?lower_case + "_methods")?right_pad(76)}\
  [/#if]
  [#if if.methods.method?size > 0]
[@ccode.GenerateVariableDeclaration indent="  "
                                    name=ifnamespace
                                    ctype="struct " + methodsstruct /]


  [#else]
  /* No methods.*/

  [/#if]
/**
[@doxygen.EmitBrief "" "@p " + ifctype + " VMT initializer." /]
 */
  [#local vmtinitsdefine = "__" + ifname?lower_case + "_vmt_init(ns)" /]
#define ${vmtinitsdefine?right_pad(68) + "\\"}
  [#if ancestorname?length > 0]
    [#local s = "  __" + ancestorname?lower_case + "_vmt_init(ns)" /]
    [#if node.methods?size > 0]
      [#local s = (s + ", ")?right_pad(76) + "\\" /]
    [/#if]
${s}
[@GenerateClassVMTInitializers methods=node.methods namespace=ifnamespace /]
  [#else]
  /* No methods.*/
  [/#if]

  [#if (ancestorname?length > 0) || (node.methods.method?size > 0)]
/**
[@doxygen.EmitBrief "" "@p " + ifctype + " virtual methods table." /]
 */
struct ${ifname?lower_case}_vmt {
  ${methodsdefine}
};

/**
[@doxygen.EmitBrief "" "Structure representing a " + ifdescr + "." /]
 */
struct ${ifname?lower_case} {
  /**
[@doxygen.EmitBrief "  " "Virtual Methods Table." /]
   */
  [#local vmtctype  = "const struct " + ifname?lower_case + "_vmt$I*$N" /]
${ccode.MakeVariableDeclaration("  " "vmt" vmtctype)}
};

  [/#if]
  [#--
    -- Generation of methods-access functions.
    --]
  [#if if.methods.method.*?size > 0]
/**
 * @name    Interface methods of @p ${ifctype}
 * @{
 */
  [#list if.methods.method as method]
    [#local methodsname    = GetMethodShortName(method)
            methodretctype = GetMethodCType(method) /]
[@doxygen.EmitFullCommentFromNode indent="" node=method
                                  extraname="ip" extradir="both"
                                  extratext="Pointer to a @p " + ifctype +
                                            ", or derived, interface." /]
CC_FORCE_INLINE
[@ccode.GeneratePrototype modifiers = ["static", "inline"]
                          params    = ["void *ip"]
                          node=method /] {
  ${ifctype} *self = (${ifctype} *)ip;

    [#local callname   = "self->vmt->" + ifnamespace + "." + methodsname /]
    [#local callparams = ccode.MakeCallParamsSequence(["ip"] method) /]
    [#if methodretctype == "void"]
[@ccode.GenerateFunctionCall "  " "" callname callparams /]
    [#else]
[@ccode.GenerateFunctionCall "  " "return" callname callparams /]
    [/#if]
}
    [#if method?has_next]

    [/#if]
  [/#list]
/** @} */

  [/#if]
[/#macro]
