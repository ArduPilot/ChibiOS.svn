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
  -- Resets global variables.
  --]
[#macro ResetState]
  [#assign generated = false /]
[/#macro]

[#--
  -- Returns the interface name from an XML node.
  --]
[#function GetInterfaceName node=[] default="no-name"]
  [#local if = node /]
  [#local ifname = (if.@name[0]!default)?trim /]
  [#return ifname /]
[/#function]

[#--
  -- Returns the interface namespace from an XML node.
  --]
[#function GetInterfaceNamespace node=[] default="no-namespace"]
  [#local if = node /]
  [#local ifnamespace = (if.@namespace[0]!default)?trim /]
  [#return ifnamespace /]
[/#function]

[#--
  -- Returns the interface C type from an XML node.
  --]
[#function GetInterfaceCType node=[] default=""]
  [#local if = node /]
  [#local ifname  = GetInterfaceName(if default) /]
  [#if ifname?length > 0]
    [#local ifctype = ifname + interface_suffix /]
  [#else ]
    [#local ifctype = default /]
  [/#if]
  [#return ifctype /]
[/#function]

[#--
  -- Returns the interface description from an XML node.
  --]
[#function GetInterfaceDescription node=[] default="no-descr"]
  [#local if = node /]
  [#local ifdescr = (if.@descr[0]!default)?trim /]
  [#return ifdescr /]
[/#function]

[#--
  -- Returns the interface ancestor name from an XML node.
  --]
[#function GetInterfaceAncestorName node=[] default=""]
  [#local if = node /]
  [#local ancestornamespace = (if.@ancestorname[0]!default)?trim /]
  [#return ancestornamespace /]
[/#function]

[#--
  -- Returns the interface ancestor name from an XML node.
  --]
[#function GetInterfaceAncestorNamespace node=[] default=""]
  [#local if = node /]
  [#local ancestornamespace = (if.@ancestornamespace[0]!default)?trim /]
  [#return ancestornamespace /]
[/#function]

[#--
  -- Returns the interface ancestor C type from an XML node.
  --]
[#function GetInterfaceAncestorCType node=[] default=""]
  [#local if = node /]
  [#local ancestorname  = GetInterfaceAncestorName(if default) /]
  [#if ancestorname?length > 0]
    [#local ancestorctype = ancestorname + interface_suffix /]
  [#else ]
    [#local ancestorctype = default /]
  [/#if]
  [#return ancestorctype /]
[/#function]

[#--
  -- Returns the class name from an XML node.
  --]
[#function GetClassName node=[] default="no-name"]
  [#local class = node /]
  [#local classname = (class.@name[0]!default)?trim /]
  [#return classname /]
[/#function]

[#--
  -- Returns the class namespace from an XML node.
  --]
[#function GetClassNamespace node=[] default="no-namespace"]
  [#local class = node /]
  [#local classnamespace = (class.@namespace[0]!default)?trim /]
  [#return classnamespace /]
[/#function]

[#--
  -- Returns the class C type from an XML node.
  --]
[#function GetClassCType node=[] default=""]
  [#local class = node /]
  [#local classname  = GetClassName(class default) /]
  [#if classname?length > 0]
    [#local classctype = classname + class_suffix /]
  [#else ]
    [#local classctype = default /]
  [/#if]
  [#return classctype /]
[/#function]

[#--
  -- Returns the class type from an XML node.
  --]
[#function GetClassType node=[] default="no-type"]
  [#local class = node /]
  [#local classtype = (class.@type[0]!default)?trim /]
  [#return classtype /]
[/#function]

[#--
  -- Returns the class description from an XML node.
  --]
[#function GetClassDescription node=[] default="no-descr"]
  [#local class = node /]
  [#local classdescr = (class.@descr[0]!default)?trim /]
  [#return classdescr /]
[/#function]

[#--
  -- Returns the class ancestor name from an XML node.
  --]
[#function GetClassAncestorName node=[] default=""]
  [#local class = node /]
  [#local ancestornamespace = (class.@ancestorname[0]!default)?trim /]
  [#return ancestornamespace /]
[/#function]

[#--
  -- Returns the class ancestor namespace from an XML node.
  --]
[#function GetClassAncestorNamespace node=[] default=""]
  [#local class = node /]
  [#local ancestornamespace = (class.@ancestornamespace[0]!default)?trim /]
  [#return ancestornamespace /]
[/#function]

[#--
  -- Returns the class ancestor C type from an XML node.
  --]
[#function GetClassAncestorCType node=[] default=""]
  [#local class = node /]
  [#local ancestorname  = GetClassAncestorName(class default) /]
  [#if ancestorname?length > 0]
    [#local ancestorctype = ancestorname + class_suffix /]
  [#else ]
    [#local ancestorctype = default /]
  [/#if]
  [#return ancestorctype /]
[/#function]

[#--
  -- Returns the method name from an XML node.
  --]
[#function GetMethodName node=[] default="no-name"]
  [#local method = node /]
  [#local methodname = (method.@name[0]!default)?trim /]
  [#return methodname /]
[/#function]

[#--
  -- Returns the method short name from an XML node.
  --]
[#function GetMethodShortName node=[] default=""]
  [#local method = node /]
  [#local methodsname = (method.@shortname[0]!default)?trim /]
    [#if methodsname?length == 0]
      [#local methodsname = GetMethodName(method default)?lower_case /]
    [/#if]
  [#return methodsname /]
[/#function]

[#--
  -- Returns the method return C type from an XML node.
  --]
[#function GetMethodCType node=[] default="void"]
  [#local method = node /]
  [#local methodctype = (method.@ctype[0]!default)?trim /]
  [#return methodctype /]
[/#function]

[#--
  -- This macro generates virtual methods pointers from an XML node.
  --]
[#macro GenerateVMTPointers methods=[] ipctype="void *"]
  [#list methods.method as method]
    [#local methodsname    = GetMethodShortName(method)
            methodretctype = GetMethodCType(method) /]
    [#local funcptr = "  " + methodretctype + " (*" + methodsname + ")(" +
                      ccode.MakeProtoParamsSequence([ipctype + "ip"] method)?join(", ") +
                      ");" /]
${funcptr}
  [/#list]
[/#macro]

[#--
  -- This macro generates a VMT initializer macro from an XML node.
  --]
[#macro GenerateVMTInitializers methods=[] namespace="no-namespace"]
  [#list methods.* as node]
    [#if node?node_name == "method"]
      [#local method = node /]
      [#local methodsname    = GetMethodShortName(method) /]
      [#local s = ("  ." + namespace + "." + methodsname)?right_pad(ccode.initializers_align) +
                  ("= __##ns##_" + methodsname + "_impl,") /]
      [#if node?has_next]
        [#local s = (s + " ")?right_pad(ccode.backslash_align) + "\\" /]
      [/#if]
${s}
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates a class wrapper from an XML node.
  --]
[#macro GenerateClassWrapper node=[]]
  [#local class = node /]
  [#local classname         = GetClassName(class)
          classnamespace    = GetClassNamespace(class)
          classctype        = GetClassCType(class)
          classdescr        = GetClassDescription(class)
          ancestorname      = GetClassAncestorName(class)
          ancestorctype     = GetClassAncestorCType(class)
          ancestornamespace = GetClassAncestorNamespace(class) /]
/**
 * @class       ${classctype}
  [#if ancestorctype?length > 0]
 * @extends     ${ancestorctype}
  [/#if]
  [#if class.brief[0]??]
 *
[@doxygen.EmitBriefFromNode node=class /]
[@doxygen.EmitDetailsFromNode node=class /]
[@doxygen.EmitPreFromNode node=class /]
[@doxygen.EmitPostFromNode node=class /]
[@doxygen.EmitNoteFromNode node=class /]
  [/#if]
 */

/**
[@doxygen.EmitBrief "" "Type of a " + classdescr + " class." /]
 */
typedef struct ${classname} ${classctype};

  [#local methodsstruct = classnamespace + "_methods" /]
  [#if node.methods.virtual?size > 0]
/**
[@doxygen.EmitBrief "" "@p " + classctype + " methods as a structure." /]
 */
struct ${methodsstruct} {
[@GenerateVMTPointers class.methods.virtual /]
};

  [/#if]
  [#local datastruct = classnamespace + "_data" /]
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
  [#local methodsdefine = "__" + classnamespace + "_methods" /]
#define ${methodsdefine?right_pad(68) + "\\"}
  [#if ancestornamespace?length > 0]
${("  __" + ancestornamespace + "_methods")?right_pad(76)}\
  [/#if]
  [#if class.methods.virtual?size > 0]
[@ccode.GenerateVariableDeclaration indent="  "
                                    name=classnamespace
                                    ctype="struct " + methodsstruct /]


  [#else]
  /* No methods.*/

  [/#if]
/**
[@doxygen.EmitBrief "" "@p " + classctype + " data." /]
 */
  [#local datadefine = "__" + classnamespace + "_data" /]
#define ${datadefine?right_pad(68) + "\\"}
  [#if ancestornamespace?length > 0]
${("  __" + ancestornamespace + "_data")?right_pad(76)}\
  [/#if]
  [#if class.fields.*?size > 0]
[@ccode.GenerateVariableDeclaration indent="  "
                                    name=classnamespace
                                    ctype="struct " + datastruct /]


  [#else]
  /* No data.*/

  [/#if]
/**
[@doxygen.EmitBrief "" "@p " + classctype + " VMT initializer." /]
 */
  [#local vmtinitsdefine = "__" + classnamespace + "_vmt_init(ns)" /]
#define ${vmtinitsdefine?right_pad(68) + "\\"}
  [#if ancestornamespace?length > 0]
    [#local s = "  __" + ancestornamespace + "_vmt_init(ns)" /]
    [#if node.methods.virtual?size > 0]
      [#local s = (s + " ")?right_pad(76) + "\\" /]
    [/#if]
${s}
[@GenerateVMTInitializers methods=node.methods.virtual namespace=classnamespace /]
  [#else]
  /* No methods.*/
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
  -- This macro generates virtual methods as inline functions
  -- from an XML node.
  --]
[#macro GenerateClassVirtualMethods node=[]]
  [#local class = node /]
  [#if class.methods.virtual.method?size > 0]
    [#local classnamespace = GetClassNamespace(class)
            classctype     = GetClassCType(class) /]
/**
 * @name    Virtual methods of ${classctype}
 * @{
 */
    [#list class.methods.virtual.method as method]
      [#local methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method) /]
[@doxygen.EmitFullCommentFromNode indent="" node=method
                                  extraname="ip" extradir="both"
                                  extratext="Pointer to a @p " + classctype + " instance." /]
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
      [#if method?has_next]

      [/#if]
    [/#list]
/** @} */

  [/#if]
[/#macro]

[#--
  -- This macro generates constructor and destructor prototypes from an XML node.
  --]
[#macro GenerateClassConstructorDestructorPrototypes node=[]]
  [#local class = node /]
  [#local classtype         = GetClassType(class)
          classnamespace    = GetClassNamespace(class)
          classctype        = GetClassCType(class) /]
  [#if classtype == "regular"]
  ${classctype} *${classnamespace}ObjectInit(${classctype} *self);
  void ${classnamespace}Dispose(${classctype} *self);
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
                          params    = ["void *ip"]
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
  -- This macro generates regular method prototypes from an XML node.
  --]
[#macro GenerateVirtualMethodsPrototypes class=[]]
  [#local classname        = GetClassName(class)
          classnamespace   = GetClassNamespace(class) /]
  void *__${classnamespace}_objinit_impl(void *ip, const void *vmt);
  void __${classnamespace}_dispose_impl(void *ip);
  [#list class.methods.virtual.* as node]
    [#if node?node_name == "method"]
      [#local method=node /]
      [#local methodname     = GetMethodName(method)
              methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method)
              methodimpl     = (method.implementation[0]!"")?trim /]
[@ccode.GeneratePrototype indent    = "  "
                          name      = "__" + classnamespace + "_" + methodsname + "_impl"
                          modifiers = []
                          params    = ["void *ip"]
                          node      = method /];
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates regular method prototypes from a class XML node.
  --]
[#macro GenerateClassMethodsPrototypes class=[]]
    [#local classctype = GetClassCType(class) /]
  /* Methods of ${classctype}.*/
[@GenerateClassConstructorDestructorPrototypes class /]
[@GenerateRegularMethodsPrototypes class.methods.regular /]
[@GenerateVirtualMethodsPrototypes class /]
[/#macro]

[#--
  -- This macro generates a class wrapper from an XML node.
  --]
[#macro GenerateInterfaceWrapper node=[]]
  [#local if = node /]
  [#local ifname            = GetInterfaceName(if)
          ifnamespace       = GetInterfaceNamespace(if)
          ifctype           = GetInterfaceCType(if)
          ifdescr           = GetInterfaceDescription(if)
          ancestorname      = GetInterfaceAncestorName(if)
          ancestorctype     = GetInterfaceAncestorCType(if)
          ancestornamespace = GetInterfaceAncestorNamespace(if) /]
/**
 * @interface   ${ifctype}
  [#if ancestorctype?length > 0]
 * @extends     ${ancestorctype}
  [/#if]
  [#if if.brief[0]??]
 *
[@doxygen.EmitBriefFromNode node=if /]
[@doxygen.EmitDetailsFromNode node=if /]
[@doxygen.EmitPreFromNode node=if /]
[@doxygen.EmitPostFromNode node=if /]
[@doxygen.EmitNoteFromNode node=if /]
  [/#if]
 */

/**
[@doxygen.EmitBrief "" "Type of a " + ifdescr + " interface." /]
 */
typedef struct ${ifname} ${ifctype};

  [#local methodsstruct = ifnamespace + "_methods" /]
  [#if node.methods.method?size > 0]
/**
[@doxygen.EmitBrief "" "@p " + ifctype + " methods as a structure." /]
 */
struct ${methodsstruct} {
[@GenerateVMTPointers methods=if.methods /]
};

  [/#if]
/**
[@doxygen.EmitBrief "" "@p " + ifctype + " methods." /]
 */
  [#local methodsdefine = "__" + ifnamespace + "_methods" /]
#define ${methodsdefine?right_pad(68) + "\\"}
  [#if ancestornamespace?length > 0]
${("  __" + ancestornamespace + "_methods")?right_pad(76)}\
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
  [#local vmtinitsdefine = "__" + ifnamespace + "_vmt_init(ns)" /]
#define ${vmtinitsdefine?right_pad(68) + "\\"}
  [#if ancestornamespace?length > 0]
    [#local s = "  __" + ancestornamespace + "_vmt_init(ns)" /]
    [#if node.methods?size > 0]
      [#local s = (s + " ")?right_pad(76) + "\\" /]
    [/#if]
${s}
[@GenerateVMTInitializers methods=node.methods namespace=ifnamespace /]
  [#else]
  /* No methods.*/
  [/#if]

  [#if (ancestornamespace?length > 0) || (node.methods.method?size > 0)]
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

[#--
  -- This macro generates class method implementations from an XML node.
  --]
[#macro GenerateClassMethodsImplementations node=[]]
  [#local class = node /]
  [#local classname         = GetClassName(class)
          classctype        = GetClassCType(class)
          classnamespace    = GetClassNamespace(class)
          classdescr        = GetClassDescription(class)
          ancestornamespace = GetClassAncestorNamespace(class) /]
  [#assign generated = true /]
/**
 * @name    Virtual methods implementations of ${classctype}
 * @{
 */
/**
[@doxygen.EmitBrief "" "Implementation of object creation." /]
[@doxygen.EmitNote  "" "This function is meant to be used by derived classes." /]
 *
[@doxygen.EmitParam name="ip" dir="out"
                    text="Pointer to a @p " + classctype + " instance to be initialized." /]
[@doxygen.EmitParam name="vmt" dir="in"
                    text="VMT pointer for the new object." /]
[@doxygen.EmitReturn text="A new reference to the object." /]
 */
void *__${classnamespace}_objinit_impl(void *ip, const void *vmt) {
  ${classctype} *self = (${classctype} *)ip;

  [#if ancestornamespace?length == 0]
  /* This is a root class, initializing the VMT pointer here.*/
  self->vmt = (struct base_object_vmt *)vmt;

  [#else]
  /* Initialization of the ancestors-defined parts.*/
  __${ancestornamespace}_objinit_impl(self, vmt);

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
                    text="Pointer to a @p " + classctype + " instance to be disposed." /]
 */
void __${classnamespace}_dispose_impl(void *ip) {
  ${classctype} *self = (${classctype} *)ip;

  [#if ancestornamespace?length > 0]
  __${ancestornamespace}_dispose_impl(self);

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
                    text="Pointer to a @p " + classctype + " instance." /]
[@doxygen.EmitParamFromNode node=method /]
[@doxygen.EmitReturnFromNode node=method /]
 */
[@ccode.GeneratePrototype indent    = ""
                          name      = "__" + classnamespace + "_" + methodsname + "_impl"
                          modifiers = []
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
  -- This macro generates constructor and destructor from an XML node.
  --]
[#macro GenerateClassConstructorDestructor node=[]]
  [#local class = node /]
  [#local classname         = GetClassName(class)
          classtype         = GetClassType(class)
          classnamespace    = GetClassNamespace(class)
          classctype        = GetClassCType(class)
          classdescr        = GetClassDescription(class) /]
  [#if classtype == "regular"]
    [#assign generated = true /]
/**
 * @name    Constructor and destructor of ${classctype}
 * @{
 */
/**
[@doxygen.EmitBrief "" "VMT structure of " + classdescr + " class." /]
 */
static const struct ${classname}_vmt ${classnamespace}_vmt = {
  __${classnamespace}_vmt_init(${classnamespace})
};

/**
[@doxygen.EmitBrief "" "Default initialize function of @p " + classctype + "." /]
 *
[@doxygen.EmitParam name=paramname dir="out"
                    text="Pointer to a @p " + classctype + " instance to be initialized." /]
[@doxygen.EmitReturn text="Pointer to the initialized object." /]
 */
${classctype} *${classnamespace}ObjectInit(${classctype} *self) {

  return __${classnamespace}_objinit_impl(self, &${classnamespace}_vmt);
}

/**
[@doxygen.EmitBrief "" "Default finalize function of @p " + classctype + "." /]
 *
[@doxygen.EmitParam name=paramname dir="both"
                    text="Pointer to a @p " + classctype + " instance to be finalized." /]
 */
void ${classnamespace}Dispose(${classctype} *self) {

  __${classnamespace}_dispose_impl(self);
}
/** @} */

  [/#if]
[/#macro]

[#--
  -- This macro generates regular methods from an XML node.
  --]
[#macro GenerateClassRegularMethods methods=[] classctype="no-ctype"]
  [#list methods.* as node]
    [#if node?node_name == "method"]
      [#local method = node /]
      [#local methodname     = GetMethodName(method)
              methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method)
              methodimpl     = method.implementation[0]!"" /]
      [#assign generated = true /]
[@doxygen.EmitFullCommentFromNode indent="" node=method
                                  extraname="ip" extradir="both"
                                  extratext="Pointer to a @p " + classctype + " instance." /]
[@ccode.GeneratePrototype modifiers = []
                          params    = ["void *ip"]
                          node=method /] {
  ${classctype} *self = (${classctype} *)ip;
[@ccode.EmitIndentedCCode indent="  " ccode=methodimpl /]
}
    [#elseif node?node_name == "condition"]
      [#local condition = node /]
      [#local condcheck = (condition.@check[0]!"1")?trim /]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GenerateClassRegularMethods condition classctype /]
#endif /* ${condcheck} */
    [/#if]
    [#if node?has_next]

    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates a class wrapper (.c part) from an XML node.
  --]
[#macro GenerateClassWrapperCode class=[]]
[@GenerateClassMethodsImplementations class /]
[@GenerateClassConstructorDestructor class /]
  [#if class.methods.regular.*?size > 0]
    [#local classctype = GetClassCType(class) /]
    [#assign generated = true /]
/**
 * @name    Regular methods of ${classctype}
 * @{
 */
[@GenerateClassRegularMethods class.methods.regular classctype /]
/** @} */

  [/#if]
[/#macro]
