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
[#assign xmlcache = {} /]
[#assign classescache={} /]
[#assign ifscache={} /]

[#--
  -- Resets global variables.
  --]
[#macro ResetState]
  [#assign generated = false /]
[/#macro]

[#--
  -- Getting references of all module public classes/interfaces.
  --]
[#macro ImportModulePublicClasses node=[]]
  [#list node.public.types.interface as interface]
    [#assign ifscache = ifscache + {GetNodeNamespace(interface):interface} /]
  [/#list]
  [#list node.public.types.class as class]
    [#assign classescache = classescache + {GetNodeNamespace(class):class} /]
  [/#list]
  [#list node.imports.import as import]
    [#local xmlname = import?trim /]
    [#if xmlcache[xmlname]??]
        [#-- Already in cache, no need to reimport.--]
    [#else]
      [#attempt]
        [#local xmldoc = pp.loadData("xml", xmlname) /]
      [#recover]
        [@pp.dropOutputFile /]
        [#stop ">>>> Importing '" + xmlname + "' failed!"]
      [/#attempt]
      [@ImportModulePublicClasses node=xmldoc.module /]
      [#assign xmlcache = xmlcache + {xmlname:xmldoc} /]
    [/#if]
  [/#list]
[/#macro]

[#--
  -- Getting references of all module private classes/interfaces.
  --]
[#macro ImportModulePrivateClasses node=[]]
  [#list node.public.types.interface as interface]
    [#assign ifscache = ifscache + {GetNodeNamespace(interface):interface} /]
  [/#list]
  [#list node.public.types.class as class]
    [#assign classescache = classescache + {GetNodeNamespace(class):class} /]
  [/#list]
[/#macro]

[#macro InitModule node=[]]
  [@ccode.ResetState /]
  [@ResetState /]
  [@ImportModulePrivateClasses node=node /]
  [@ImportModulePublicClasses node=node /]
[#-- ${xmlcache?keys?join(", ")} - ${classescache?keys?join(", ")} - ${ifscache?keys?join(", ")} --]
[/#macro]

[#--
  -- Returns the name attribute from an XML node.
  --]
[#function GetNodeName node=[] default="no-name"]
  [#return (node.@name[0]!default)?trim /]
[/#function]

[#--
  -- Returns the namespace attribute from an XML node.
  --]
[#function GetNodeNamespace node=[] default="no-namespace"]
  [#return (node.@namespace[0]!default)?trim /]
[/#function]

[#--
  -- Returns the ancestorname attribute from an XML node.
  --]
[#function GetNodeAncestorName node=[] default=""]
  [#return (node.@ancestorname[0]!default)?trim /]
[/#function]

[#--
  -- Returns the ancestornamespace attribute from an XML node.
  --]
[#function GetNodeAncestorNamespace node=[] default=""]
  [#return (node.@ancestornamespace[0]!default)?trim /]
[/#function]

[#--
  -- Returns the descr attribute from an XML node.
  --]
[#function GetNodeDescription node=[] default="no-descr"]
  [#return (node.@descr[0]!default)?trim /]
[/#function]

[#--
  -- Returns the interface C type from an XML node.
  --]
[#function GetInterfaceCType node=[] default=""]
  [#local if = node /]
  [#local ifname  = GetNodeName(if default) /]
  [#if ifname?length > 0]
    [#local ifctype = ifname + interface_suffix /]
  [#else ]
    [#local ifctype = default /]
  [/#if]
  [#return ifctype /]
[/#function]

[#--
  -- Returns the interface ancestor C type from an XML node.
  --]
[#function GetInterfaceAncestorCType node=[] default=""]
  [#local if = node /]
  [#local ancestorname  = GetNodeAncestorName(if default) /]
  [#if ancestorname?length > 0]
    [#local ancestorctype = ancestorname + interface_suffix /]
  [#else ]
    [#local ancestorctype = default /]
  [/#if]
  [#return ancestorctype /]
[/#function]

[#--
  -- Returns the class C type from an XML node.
  --]
[#function GetClassCType node=[] default=""]
  [#local class = node /]
  [#local classname  = GetNodeName(class default) /]
  [#if classname?length > 0]
    [#local classctype = classname + class_suffix /]
  [#else ]
    [#local classctype = default /]
  [/#if]
  [#return classctype /]
[/#function]

[#--
  -- Returns the class ancestor C type from an XML node.
  --]
[#function GetClassAncestorCType node=[] default=""]
  [#local class = node /]
  [#local ancestorname  = GetNodeAncestorName(class default) /]
  [#if ancestorname?length > 0]
    [#local ancestorctype = ancestorname + class_suffix /]
  [#else ]
    [#local ancestorctype = default /]
  [/#if]
  [#return ancestorctype /]
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
  -- Returns the method short name from an XML node.
  --]
[#function GetMethodShortName node=[] default=""]
  [#local method = node /]
  [#local methodsname = (method.@shortname[0]!default)?trim /]
    [#if methodsname?length == 0]
      [#local methodsname = GetNodeName(method default)?lower_case /]
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
  -- Returns the method short name from an XML node.
  --]
[#function GetObjinitCallsuper node=[] default="true"]
  [#return (node.@callsuper[0]!default)?trim /]
[/#function]

[#--
  -- This macro generates virtual methods pointers from an XML node.
  --]
[#macro GenerateVMTPointers methods=[] ipctype="void *"]
  [#list methods.method as method]
    [#local methodsname    = GetMethodShortName(method)
            methodretctype = GetMethodCType(method) /]
    [#local funcptr = ccode.indentation + methodretctype + " (*" + methodsname + ")(" +
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
                  ("= __##ns##_" + namespace + "_" + methodsname + "_impl,") /]
      [#if node?has_next]
        [#local s = (s + " ")?right_pad(ccode.backslash_align) + "\\" /]
      [/#if]
${s}
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates virtual methods as inline functions
  -- from an XML node.
  --]
[#macro GenerateVirtualMethods methods=[] ctype="no-ctype" namespace="no-namespace"]
  [#if methods.method?size > 0]
/**
[@doxygen.EmitTagVerbatim "" "name" "Virtual methods of " + ctype /]
 * @{
 */
    [#list methods.method as method]
      [#local methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method) /]
[@doxygen.EmitFullCommentFromNode indent="" node=method
                                  extraname="ip" extradir="both"
                                  extratext="Pointer to a @p " + ctype + " instance."
                                  memberof=ctype /]
CC_FORCE_INLINE
[@ccode.GeneratePrototypeFromNode modifiers = ["static", "inline"]
                                  params    = ["void *ip"]
                                  node=method /] {
[@ccode.Indent 1 /]${ctype} *self = (${ctype} *)ip;

      [#local callname   = "self->vmt->" + namespace + "." + methodsname /]
      [#local callparams = ccode.MakeCallParamsSequence(["ip"] method) /]
      [#if methodretctype == "void"]
[@ccode.GenerateFunctionCall ccode.indentation "" callname callparams /]
      [#else]
[@ccode.GenerateFunctionCall ccode.indentation "return " callname callparams /]
      [/#if]
}
      [#if method?has_next]

      [/#if]
    [/#list]
/** @} */

  [/#if]
[/#macro]

[#--
  -- This macro generates a Doxygen list of implemented interfaces from an XML node.
  --]
[#macro GenerateClassImplementsTags node=[]]
  [#list node.* as this]
    [#if this?node_name == "ifref"]
    [#local refname      = GetNodeName(this)
            refnamespace = GetNodeNamespace(this)
            refctype     = GetInterfaceCType(this) /]
[@doxygen.EmitTagVerbatim indent="" tag="implements" text=refctype /]
    [#elseif this?node_name == "condition"]
[@GenerateClassImplementsTags this /]
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates interface access macros from an XML node.
  --]
[#macro GenerateClassInterfaceMacros node=[]]
  [#if node.implements.*?size > 0]
    [#local classnamespace = GetNodeNamespace(node)
            classctype     = GetClassCType(node) /]

/**
[@doxygen.EmitTagVerbatim indent "memberof" classctype /]
 *
[@doxygen.EmitBrief "" "Access macro for " + classctype + " interfaces." /]
 *
[@doxygen.EmitParam "" "ip" "in" "Pointer to the class instance." /]
[@doxygen.EmitParam "" "ifns" "" "Implemented interface namespace." /]
[@doxygen.EmitReturn "" "A void pointer to the interface within the class instance." /]
 *
 * @api
 */
${("#define " + classnamespace + "GetIf(ip, ifns)")?right_pad(ccode.backslash_align) + "\\"}
[@ccode.Indent 1 /]boGetIf(ip, ifns, ${classnamespace})
  [/#if]
[/#macro]

[#--
  -- This macro generates regular methods from an XML node.
  --]
[#macro GenerateClassMethods methods=[] classctype="no-ctype" inline=false]
  [#list methods.* as node]
    [#if node?node_name == "method"]
      [#local method = node /]
      [#local methodname     = GetNodeName(method)
              methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method)
              methodimpl     = method.implementation[0]!"" /]
      [#assign generated = true /]
[@doxygen.EmitFullCommentFromNode indent="" node=method
                                  extraname="ip" extradir="both"
                                  extratext="Pointer to a @p " + classctype + " instance."
                                  memberof=classctype /]
      [#if inline]
CC_FORCE_INLINE
        [#local modifiers = ["static", "inline"] /]
      [#else]
        [#local modifiers = [] /]
      [/#if]
[@ccode.GeneratePrototypeFromNode modifiers = modifiers
                                  params    = ["void *ip"]
                                  node=method /] {
  ${classctype} *self = (${classctype} *)ip;
[@ccode.GenerateIndentedCCode indent=ccode.indentation
                              ccode=methodimpl /]
}
    [#elseif node?node_name == "condition"]
      [#local condition = node /]
      [#local condcheck = (condition.@check[0]!"1")?trim /]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GenerateClassMethods condition classctype inline /]
#endif /* ${condcheck} */
    [/#if]
    [#if node?has_next]

    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates private constructor and destructor from an XML node.
  --]
[#macro GenerateClassPrivateConstructorDestructor node=[]]
  [#local classname         = GetNodeName(node)
          classnamespace    = GetNodeNamespace(node)
          classtype         = GetClassType(node)
          classctype        = GetClassCType(node)
          classdescr        = GetNodeDescription(node) /]
  [#if classtype == "regular"]
    [#assign generated = true /]
/**
[@doxygen.EmitTagVerbatim "" "name" "Default constructor of " + classctype /]
 * @{
 */
/**
[@doxygen.EmitTagVerbatim "" "memberof" classctype /]
 *
[@doxygen.EmitBrief "" "Default initialization function of @p " + classctype + "." /]
 *
[@doxygen.EmitParam name = "self"
                    dir  = "out"
                    text = "Pointer to a @p " + classctype + " instance to be initialized." /]
[@doxygen.EmitParamFromNode node = node.methods.objinit[0] /]
[@doxygen.EmitReturn text = "Pointer to the initialized object." /]
 *
 * @objinit
 */
CC_FORCE_INLINE
[@ccode.GeneratePrototypeFromNode indent    = ""
                                  name      = classnamespace + "_object_init"
                                  ctype     = classctype + " *"
                                  modifiers = ["static", "inline"]
                                  params    = [classctype + " *self"]
                                  node      = node.methods.objinit[0] /] {
    [#local vmtname = "__" + classnamespace + "_vmt" /]
[@ccode.Indent 1 /]static const struct ${classname}_vmt ${vmtname} = {
[@ccode.Indent 2 /]__${classname}_vmt_init(${classnamespace})
[@ccode.Indent 1 /]};

    [#local params = ccode.MakeCallParamsSequence(["self", "&" + vmtname], node.methods.objinit[0]) /]
[@ccode.GenerateFunctionCall indent      = ccode.indentation
                             destination = "return"
                             name        = "__" + classnamespace + "_objinit_impl"
                             params      = params /]
}
/** @} */

  [/#if]
[/#macro]

[#--
  -- This macro generates public constructor and destructor from an XML node.
  --]
[#macro GenerateClassPublicConstructorDestructor node=[]]
  [#local classname         = GetNodeName(node)
          classnamespace    = GetNodeNamespace(node)
          classtype         = GetClassType(node)
          classctype        = GetClassCType(node)
          classdescr        = GetNodeDescription(node) /]
  [#if classtype == "regular"]
    [#assign generated = true /]
/**
[@doxygen.EmitTagVerbatim "" "name" "Default constructor of " + classctype /]
 * @{
 */
/**
[@doxygen.EmitTagVerbatim "" "memberof" classctype /]
 *
[@doxygen.EmitBrief "" "Default initialization function of @p " + classctype + "." /]
 *
[@doxygen.EmitParam name = "self"
                    dir  = "out"
                    text = "Pointer to a @p " + classctype + " instance to be initialized." /]
[@doxygen.EmitParamFromNode node = node.methods.objinit[0] /]
[@doxygen.EmitReturn text = "Pointer to the initialized object." /]
 *
 * @objinit
 */
CC_FORCE_INLINE
[@ccode.GeneratePrototypeFromNode indent    = ""
                                  name      = classnamespace + "ObjectInit"
                                  ctype     = classctype + " *"
                                  modifiers = ["static", "inline"]
                                  params    = [classctype + " *self"]
                                  node      = node.methods.objinit[0] /] {
[@ccode.Indent 1 /]extern const struct ${classname}_vmt __${classnamespace}_vmt;

    [#local params = ccode.MakeCallParamsSequence(["self", "&__" + classnamespace + "_vmt"], node.methods.objinit[0]) /]
[@ccode.GenerateFunctionCall indent      = ccode.indentation
                             destination = "return"
                             name        = "__" + classnamespace + "_objinit_impl"
                             params      = params /]
}
/** @} */

  [/#if]
[/#macro]

[#--
  -- This macro generates class virtual methods as inline functions
  -- from an XML node.
  --]
[#macro GenerateClassVirtualMethods class=[]]
  [#local classnamespace = GetNodeNamespace(class)
          classctype     = GetClassCType(class) /]
[@GenerateVirtualMethods methods=class.methods.virtual
                         ctype=classctype
                         namespace=classnamespace /]
[/#macro]

[#--
  -- This macro generates inline methods from an XML node.
  --]
[#macro GenerateClassInlineMethods class=[]]
  [#if class.methods.inline.*?size > 0]
    [#local classctype = GetClassCType(class) /]
/**
[@doxygen.EmitTagVerbatim "" "name" "Inline methods of " + classctype /]
 * @{
 */
[@GenerateClassMethods class.methods.inline classctype true /]
/** @} */

  [/#if]
[/#macro]

[#--
  -- This macro generates regular method prototypes from an XML node.
  --]
[#macro GenerateClassRegularMethodsPrototypes node=[]]
  [#list node.* as this]
    [#if this?node_name == "method"]
      [#local method = this /]
      [#local methodname     = GetNodeName(method)
              methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method) /]
[@ccode.GeneratePrototypeFromNode indent    = ccode.indentation
                                  modifiers = []
                                  params    = ["void *ip"]
                                  node=method /];
    [#elseif this?node_name == "condition"]
      [#local condition = this /]
      [#local condcheck = (condition.@check[0]!"1")?trim /]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GenerateClassRegularMethodsPrototypes condition /]
#endif /* ${condcheck} */
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates regular method prototypes from an XML node.
  --]
[#macro GenerateClassVirtualMethodsPrototypes class=[]]
  [#local classname        = GetNodeName(class)
          classnamespace   = GetNodeNamespace(class) /]
[@ccode.GeneratePrototypeFromNode indent    = ccode.indentation
                                  name      = "__" + classnamespace + "_objinit_impl"
                                  ctype     = "void *"
                                  modifiers = []
                                  params    = ["void *ip", "const void *vmt"]
                                  node      = class.methods.objinit[0] /];
[@ccode.GeneratePrototype indent    = ccode.indentation
                          name      = "__" + classnamespace + "_dispose_impl"
                          ctype     = "void"
                          modifiers = []
                          params    = ["void *ip"] /];
  [#list class.methods.virtual.* as node]
    [#if node?node_name == "method"]
      [#local method=node /]
      [#local methodname     = GetNodeName(method)
              methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method)
              methodimpl     = method.implementation[0]!"" /]
      [#if methodimpl?length > 0]
[@ccode.GeneratePrototypeFromNode indent    = ccode.indentation
                                  name      = "__" + classnamespace + "_" + methodsname + "_impl"
                                  modifiers = []
                                  params    = ["void *ip"]
                                  node      = method /];
      [/#if]
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates regular method prototypes from a class XML node.
  --]
[#macro GenerateClassMethodsPrototypes class=[]]
    [#local classctype = GetClassCType(class) /]
[@ccode.Indent 1 /]/* Methods of ${classctype}.*/
[@GenerateClassVirtualMethodsPrototypes class /]
[@GenerateClassRegularMethodsPrototypes class.methods.regular /]
[/#macro]

[#--
  -- This macro generates class interface fields from an XML node.
  --]
[#macro GenerateClassInterfaceFields node=[]]
  [#list node.* as this]
    [#if this?node_name == "ifref"]
      [#local ifname      = GetNodeName(this)
              ifnamespace = GetNodeNamespace(this)
              ifctype     = GetInterfaceCType(this) /]
[@ccode.Indent 1 /]/**
[@doxygen.EmitBrief ccode.indentation "Implemented interface @p " + ifctype + "." /]
[@ccode.Indent 1 /] */
[@ccode.GenerateVariableDeclaration indent=ccode.indentation
                                    name=ifnamespace
                                    ctype=ifctype /]

    [#elseif this?node_name == "condition"]
      [#local condcheck = (this.@check[0]!"1")?trim /]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GenerateClassInterfaceFields this /]
#endif /* ${condcheck} */
    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates a class wrapper from an XML node.
  --]
[#macro GenerateClassWrapper node=[]]
  [#local class = node /]
  [#local classname         = GetNodeName(class)
          classnamespace    = GetNodeNamespace(class)
          classctype        = GetClassCType(class)
          classdescr        = GetNodeDescription(class)
          ancestorname      = GetNodeAncestorName(class, "")
          ancestorctype     = GetClassAncestorCType(class) /]
/**
[@doxygen.EmitTagVerbatim indent="" tag="class" text=classctype /]
  [#if ancestorctype?length > 0]
[@doxygen.EmitTagVerbatim indent="" tag="extends" text=ancestorctype /]
  [/#if]
[@GenerateClassImplementsTags class.implements /]
 *
[@doxygen.EmitBriefFromNode node=class /]
[@doxygen.EmitDetailsFromNode node=class /]
[@doxygen.EmitPreFromNode node=class /]
[@doxygen.EmitPostFromNode node=class /]
[@doxygen.EmitNoteFromNode node=class /]
[@doxygen.EmitNote text="The class namespace is <tt>" + classnamespace + "</tt>, access to " +
                        "class fields is done using: <tt><objp>->" + classnamespace + ".<fieldname></tt><br>" +
                        "Note that fields of ancestor classes are in their own namespace in order to " +
                        "avoid field naming conflicts." /]
 *
[@doxygen.EmitTagVerbatim indent="" tag="name" text="Class @p " + classctype + " structures"/]
 * @{
 */

/**
[@doxygen.EmitBrief "" "Type of a " + classdescr + " class." /]
 */
typedef struct ${classname} ${classctype};

  [#local methodsstruct = classname + "_methods" /]
  [#if node.methods.virtual?size > 0]
/**
[@doxygen.EmitBrief "" "Class @p " + classctype + " methods as a structure." /]
 */
struct ${methodsstruct} {
[@GenerateVMTPointers class.methods.virtual /]
};

  [/#if]
  [#local datastruct = classname + "_data" /]
  [#if class.fields.*?size > 0]
/**
[@doxygen.EmitBrief "" "Class @p " + classctype + " data as a structure." /]
 */
struct ${datastruct} {
[@GenerateClassInterfaceFields node=class.implements /]
[@ccode.GenerateStructureFieldsFromNode ccode.indentation class.fields /]
};

  [/#if]
/**
[@doxygen.EmitBrief "" "Class @p " + classctype + " methods." /]
 */
  [#local methodsdefine = "__" + classname + "_methods" /]
#define ${methodsdefine?right_pad(68) + "\\"}
  [#if ancestorname?length > 0]
${("  __" + ancestorname + "_methods")?right_pad(76)}\
  [/#if]
  [#if class.methods.virtual?size > 0]
[@ccode.GenerateVariableDeclaration indent=ccode.indentation
                                    name=classnamespace
                                    ctype="struct " + methodsstruct /]


  [#else]
[@ccode.Indent 1 /]/* No methods.*/

  [/#if]
/**
[@doxygen.EmitBrief "" "Class @p " + classctype + " data." /]
 */
  [#local datadefine = "__" + classname + "_data" /]
#define ${datadefine?right_pad(68) + "\\"}
  [#if ancestorname?length > 0]
${("  __" + ancestorname + "_data")?right_pad(76)}\
  [/#if]
  [#if class.fields.*?size > 0]
[@ccode.GenerateVariableDeclaration indent=ccode.indentation
                                    name=classnamespace
                                    ctype="struct " + datastruct /]


  [#else]
[@ccode.Indent 1 /]/* No data.*/

  [/#if]
/**
[@doxygen.EmitBrief "" "Class @p " + classctype + " VMT initializer." /]
 */
  [#local vmtinitsdefine = "__" + classname + "_vmt_init(ns)" /]
#define ${vmtinitsdefine?right_pad(68) + "\\"}
  [#if ancestorname?length > 0]
    [#-- Case where there is an ancestor.--]
    [#local s = "  __" + ancestorname + "_vmt_init(ns)" /]
    [#if node.methods.virtual?size > 0]
      [#local s = (s + " ")?right_pad(76) + "\\" /]
    [/#if]
${s}
[@GenerateVMTInitializers methods=node.methods.virtual namespace=classnamespace /]
  [#else]
    [#-- Case where there is no ancestor.--]
    [#if node.methods.virtual?size > 0]
[@GenerateVMTInitializers methods=node.methods.virtual namespace=classnamespace /]
    [#else]
[@ccode.Indent 1 /]/* No methods.*/
    [/#if]
  [/#if]

/**
[@doxygen.EmitBrief "" "Class @p " + classctype + " virtual methods table." /]
 */
struct ${classname?lower_case}_vmt {
  ${methodsdefine}
};

/**
[@doxygen.EmitBrief "" "Structure representing a " + classdescr + " class." /]
 */
struct ${classname?lower_case} {
[@ccode.Indent 1 /]/**
[@doxygen.EmitBrief ccode.indentation "Virtual Methods Table." /]
[@ccode.Indent 1 /] */
  [#local vmtctype  = "const struct " + classname?lower_case + "_vmt$I*$N" /]
${ccode.MakeVariableDeclaration(ccode.indentation "vmt" vmtctype)}
  ${datadefine}
};
[@GenerateClassInterfaceMacros class /]
/** @} */
[/#macro]

[#--
  -- This macro generates interface virtual methods as inline functions
  -- from an XML node.
  --]
[#macro GenerateInterfaceVirtualMethods if=[]]
  [#local ifnamespace = GetNodeNamespace(if)
          ifctype     = GetInterfaceCType(if) /]
[@GenerateVirtualMethods methods=if.methods
                         ctype=ifctype
                         namespace=ifnamespace /]
[/#macro]

[#--
  -- This macro generates a class wrapper from an XML node.
  --]
[#macro GenerateInterfaceWrapper node=[]]
  [#local if = node /]
  [#local ifname            = GetNodeName(if)
          ifnamespace       = GetNodeNamespace(if)
          ifctype           = GetInterfaceCType(if)
          ifdescr           = GetNodeDescription(if)
          ancestorname      = GetNodeAncestorName(if, "")
          ancestorctype     = GetInterfaceAncestorCType(if) /]
/**
 * @interface   ${ifctype}
  [#if ancestorctype?length > 0]
 * @extends     ${ancestorctype}
  [/#if]
 *
[@doxygen.EmitBriefFromNode node=if /]
[@doxygen.EmitDetailsFromNode node=if /]
[@doxygen.EmitPreFromNode node=if /]
[@doxygen.EmitPostFromNode node=if /]
[@doxygen.EmitNoteFromNode node=if /]
[@doxygen.EmitNote text="The interface namespace is <tt>" + ifnamespace + "</tt>, access to " +
                        "an implemented interface is done using: " +
                        "<tt>&<objp>-><classnamespace>." + ifnamespace + "</tt>"/]
 *
[@doxygen.EmitTagVerbatim indent="" tag="name" text="Interface @p " + ifctype + " structures"/]
 * @{
 */

/**
[@doxygen.EmitBrief "" "Type of a " + ifdescr + " interface." /]
 */
typedef struct ${ifname} ${ifctype};

  [#local methodsstruct = ifname + "_methods" /]
  [#if node.methods.method?size > 0]
/**
[@doxygen.EmitBrief "" "Interface @p " + ifctype + " methods as a structure." /]
 */
struct ${methodsstruct} {
[@GenerateVMTPointers methods=if.methods /]
};

  [/#if]
/**
[@doxygen.EmitBrief "" "Interface @p " + ifctype + " methods." /]
 */
  [#local methodsdefine = "__" + ifname + "_methods" /]
${("#define " + methodsdefine)?right_pad(ccode.backslash_align) + "\\"}
  [#if ancestorname?length > 0]
${(ccode.indentation + "__" + ancestorname +
                       "_methods")?right_pad(ccode.backslash_align) + "\\"}
  [/#if]
  [#if if.methods.method?size > 0]
[@ccode.GenerateVariableDeclaration indent=ccode.indentation
                                    name=ifnamespace
                                    ctype="struct " + methodsstruct /]


  [#else]
${(ccode.indentation + "/* Memory offset between this interface structure and begin of")}
${(ccode.indentation + "   the implementing class structure.*/")?right_pad(ccode.backslash_align) + "\\"}
${(ccode.indentation + "size_t instance_offset;")}

  [/#if]
/**
[@doxygen.EmitBrief "" "Interface @p " + ifctype + " VMT initializer." /]
 *
[@doxygen.EmitParam "" "ns" "" "Namespace of the implementing class." /]
[@doxygen.EmitParam "" "off" "in" "VMT offset to be stored." /]
 */
  [#local vmtinitsdefine = "__" + ifname + "_vmt_init(ns, off)" /]
#define ${vmtinitsdefine?right_pad(68) + "\\"}
  [#if ancestorname?length > 0]
    [#local s = "  __" + ancestorname + "_vmt_init(ns, off)" /]
    [#if node.methods?size > 0]
      [#local s = (s + " ")?right_pad(76) + "\\" /]
    [/#if]
${s}
[@GenerateVMTInitializers methods=node.methods namespace=ifnamespace /]
  [#else]
${(ccode.indentation + ".instance_offset")?right_pad(ccode.initializers_align) + "= off,"}
  [/#if]

/**
[@doxygen.EmitBrief "" "Interface @p " + ifctype + " virtual methods table." /]
 */
struct ${ifname?lower_case}_vmt {
  ${methodsdefine}
};

/**
[@doxygen.EmitBrief "" "Structure representing a " + ifdescr + "." /]
 */
struct ${ifname?lower_case} {
[@ccode.Indent 1 /]/**
[@doxygen.EmitBrief ccode.indentation "Virtual Methods Table." /]
[@ccode.Indent 1 /] */
  [#local vmtctype  = "const struct " + ifname?lower_case + "_vmt$I*$N" /]
${ccode.MakeVariableDeclaration(ccode.indentation "vmt" vmtctype)}
};
/** @} */
[/#macro]

[#--
  -- This macro generates class method implementations from an XML node.
  --]
[#macro GenerateClassInterfacesInitialization node=[] classctype="no-ctype" classnamespace="no-namespace"]
  [#list node.* as this]
    [#if this?node_name == "ifref"]
      [#local ifname      = GetNodeName(this)
              ifnamespace = GetNodeNamespace(this)
              ifctype     = GetInterfaceCType(this) /]
[@ccode.Indent 1 /]/* Implementation of interface ${ifctype}.*/
[@ccode.Indent 1 /]{
[@ccode.Indent 2 /]static const struct ${ifname}_vmt ${classnamespace}_${ifnamespace}_vmt = {
[@ccode.Indent 3 /]__${ifname}_vmt_init(${classnamespace}, offsetof(${classctype}, ${classnamespace}.${ifnamespace}))
[@ccode.Indent 2 /]};
[@ccode.Indent 2 /]oopIfObjectInit(&self->${classnamespace}.${ifnamespace}, &${classnamespace}_${ifnamespace}_vmt);
[@ccode.Indent 1 /]}
      [#if node?node_name != "condition"]

      [/#if]
    [#elseif this?node_name == "condition"]
      [#local condcheck = (this.@check[0]!"1")?trim /]
#if (${condcheck}) || defined (__DOXYGEN__)
[@GenerateClassInterfacesInitialization this classctype classnamespace /]
#endif /* ${condcheck} */

    [/#if]
  [/#list]
[/#macro]

[#--
  -- This macro generates class method implementations from an XML node.
  --]
[#macro GenerateClassMethodsImplementations modifiers=[] node=[]]
  [#local class = node /]
  [#local classname         = GetNodeName(class)
          classnamespace    = GetNodeNamespace(class)
          classctype        = GetClassCType(class)
          classdescr        = GetNodeDescription(class)
          ancestorname      = GetNodeAncestorName(class, "")
          ancestornamespace = GetNodeAncestorNamespace(class) /]
  [#assign generated = true /]
/**
[@doxygen.EmitTagVerbatim "" "name" "Methods implementations of " + classctype /]
 * @{
 */
/**
[@doxygen.EmitTagVerbatim "" "memberof" classctype /]
 * @protected
 *
[@doxygen.EmitBrief "" "Implementation of object creation." /]
[@doxygen.EmitNote  "" "This function is meant to be used by derived classes." /]
 *
[@doxygen.EmitParam name="ip" dir="out"
                    text="Pointer to a @p " + classctype + " instance to be initialized." /]
[@doxygen.EmitParam name="vmt" dir="in"
                    text="VMT pointer for the new object." /]
[@doxygen.EmitParamFromNode node = class.methods.objinit[0] /]
[@doxygen.EmitReturn text="A new reference to the object." /]
 */
[@ccode.GeneratePrototypeFromNode indent    = ""
                                  name      = "__" + classnamespace + "_objinit_impl"
                                  ctype     = "void *"
                                  modifiers = modifiers
                                  params    = ["void *ip", "const void *vmt"]
                                  node      = class.methods.objinit[0] /] {
[@ccode.Indent 1 /]${classctype} *self = (${classctype} *)ip;

  [#if ancestorname?length == 0]
[@ccode.Indent 1 /]/* This is a root class, initializing the VMT pointer here.*/
[@ccode.Indent 1 /]self->vmt = (struct base_object_vmt *)vmt;

  [#else]
    [#if GetObjinitCallsuper(class.methods.objinit[0]) == "true"]
[@ccode.Indent 1 /]/* Initialization of the ancestors-defined parts.*/
[@ccode.GenerateFunctionCall indent      = ccode.indentation
                             destination = ""
                             name        = "__" + ancestornamespace + "_objinit_impl"
                             params      = ["self", "vmt"] /]

    [/#if]
  [/#if]
  [#if class.implements.*?size > 0]
[@GenerateClassInterfacesInitialization class.implements classctype classnamespace /]
  [/#if]
  [#if (class.methods.objinit[0].implementation[0])?? &&
       (class.methods.objinit[0].implementation[0]?trim?length > 0)]
[@ccode.Indent 1 /]/* Initialization code.*/
[@ccode.GenerateIndentedCCode indent=ccode.indentation
                              ccode=class.methods.objinit[0].implementation[0]?string /]
  [#else]
[@ccode.Indent 1 /]/* No initialization code.*/
  [/#if]

[@ccode.Indent 1 /]return self;
}

/**
[@doxygen.EmitTagVerbatim "" "memberof" classctype /]
 * @protected
 *
[@doxygen.EmitBrief "" "Implementation of object finalization." /]
[@doxygen.EmitNote  "" "This function is meant to be used by derived classes." /]
 *
[@doxygen.EmitParam name="ip" dir="both"
                    text="Pointer to a @p " + classctype + " instance to be disposed." /]
 */
[@ccode.GeneratePrototype indent    = ""
                          name      = "__" + classnamespace + "_dispose_impl"
                          ctype     = "void"
                          modifiers = modifiers
                          params    = ["void *ip"] /] {
[@ccode.Indent 1 /]${classctype} *self = (${classctype} *)ip;

  [#if (class.methods.dispose[0].implementation[0])?? &&
       (class.methods.dispose[0].implementation[0]?trim?length > 0)]
[@ccode.Indent 1 /]/* Finalization code.*/
[@ccode.GenerateIndentedCCode indent=ccode.indentation
                              ccode=class.methods.dispose[0].implementation[0]?string /]
  [#else]
[@ccode.Indent 1 /]/* No finalization code.*/
[@ccode.Indent 1 /](void)self;
  [/#if]
  [#if ancestorname?length > 0]

[@ccode.Indent 1 /]/* Finalization of the ancestors-defined parts.*/
[@ccode.Indent 1 /]__${ancestornamespace}_dispose_impl(self);
  [/#if]
}
  [#list class.methods.virtual.* as node]
    [#if node?node_name == "method"]
      [#local method=node /]
      [#local methodname     = GetNodeName(method)
              methodsname    = GetMethodShortName(method)
              methodretctype = GetMethodCType(method)
              methodimpl     = method.implementation[0]!"" /]
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
[@ccode.GeneratePrototypeFromNode indent    = ""
                                  name      = "__" + classnamespace + "_" + methodsname + "_impl"
                                  modifiers = modifiers
                                  params    = ["void *ip"]
                                  node      = method /] {
[@ccode.Indent 1 /]${classctype} *self = (${classctype} *)ip;
[@ccode.GenerateIndentedCCode indent=ccode.indentation
                              ccode=methodimpl /]
}
      [/#if]
    [/#if]
  [/#list]
/** @} */

[/#macro]


[#--
  -- This macro generates constructor and destructor from an XML node.
  --]
[#macro GenerateClassVMT node=[]]
  [#local classname      = GetNodeName(node)
          classnamespace = GetNodeNamespace(node)
          classtype      = GetClassType(node)
          classctype     = GetClassCType(node)
          classdescr     = GetNodeDescription(node) /]
  [#if classtype == "regular"]
    [#assign generated = true /]
/**
[@doxygen.EmitBrief "" "VMT structure of " + classdescr + " class." /]
[@doxygen.EmitNote "" "It is public because accessed by the inlined constructor." /]
 */
const struct ${classname}_vmt __${classnamespace}_vmt = {
  __${classname}_vmt_init(${classnamespace})
};

  [/#if]
[/#macro]

[#--
  -- This macro generates regular methods from an XML node.
  --]
[#macro GenerateClassRegularMethods node=[]]
  [#local class = node /]
  [#if class.methods.regular.*?size > 0]
    [#local classctype = GetClassCType(class) /]
/**
[@doxygen.EmitTagVerbatim "" "name" "Regular methods of " + classctype /]
 * @{
 */
[@GenerateClassMethods class.methods.regular classctype false /]
/** @} */

  [/#if]
[/#macro]

[#--
  -- This macro generates a class wrapper (.c part) from an XML node.
  --]
[#macro GenerateClassWrapperCode class=[]]
[@GenerateClassVMT node=class /]
[@GenerateClassMethodsImplementations node=class /]
[@GenerateClassRegularMethods node=class /]
[/#macro]
