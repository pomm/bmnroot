/********************************************************************
* /home/merz/BMN/GIT/trunk_220814/build/geobase/G__GeoBaseDict.h
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************************/
#ifdef __CINT__
#error /home/merz/BMN/GIT/trunk_220814/build/geobase/G__GeoBaseDict.h/C is only for compilation. Abort cint.
#endif
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define G__ANSIHEADER
#define G__DICTIONARY
#define G__PRIVATE_GVALUE
#include "G__ci.h"
#include "FastAllocString.h"
extern "C" {
extern void G__cpp_setup_tagtableG__GeoBaseDict();
extern void G__cpp_setup_inheritanceG__GeoBaseDict();
extern void G__cpp_setup_typetableG__GeoBaseDict();
extern void G__cpp_setup_memvarG__GeoBaseDict();
extern void G__cpp_setup_globalG__GeoBaseDict();
extern void G__cpp_setup_memfuncG__GeoBaseDict();
extern void G__cpp_setup_funcG__GeoBaseDict();
extern void G__set_cpp_environmentG__GeoBaseDict();
}


#include "TObject.h"
#include "TMemberInspector.h"
#include "FairGeoAssembly.h"
#include "FairGeoCone.h"
#include "FairGeoCons.h"
#include "FairGeoEltu.h"
#include "FairGeoBuilder.h"
#include "FairGeoInterface.h"
#include "FairGeoIo.h"
#include "FairGeoLoader.h"
#include "FairGeoMatrix.h"
#include "FairGeoMedia.h"
#include "FairGeoMedium.h"
#include "FairGeoNode.h"
#include "FairGeoOldAsciiIo.h"
#include "FairGeoPcon.h"
#include "FairGeoPgon.h"
#include "FairGeoRootBuilder.h"
#include "FairGeoRotation.h"
#include "FairGeoSet.h"
#include "FairGeoShapes.h"
#include "FairGeoSphe.h"
#include "FairGeoTransform.h"
#include "FairGeoTrap.h"
#include "FairGeoTrd1.h"
#include "FairGeoTube.h"
#include "FairGeoTubs.h"
#include "FairGeoTorus.h"
#include "FairGeoVector.h"
#include "FairGeoVolume.h"
#include "FairGeoCompositeVolume.h"
#include "FairGeoAsciiIo.h"
#include "FairGeoBrik.h"
#include "FairGeoBasicShape.h"
#include <algorithm>
namespace std { }
using namespace std;

#ifndef G__MEMFUNCBODY
#endif

extern G__linked_taginfo G__G__GeoBaseDictLN_TClass;
extern G__linked_taginfo G__G__GeoBaseDictLN_TBuffer;
extern G__linked_taginfo G__G__GeoBaseDictLN_TMemberInspector;
extern G__linked_taginfo G__G__GeoBaseDictLN_TObject;
extern G__linked_taginfo G__G__GeoBaseDictLN_TNamed;
extern G__linked_taginfo G__G__GeoBaseDictLN_TString;
extern G__linked_taginfo G__G__GeoBaseDictLN_basic_fstreamlEcharcOchar_traitslEchargRsPgR;
extern G__linked_taginfo G__G__GeoBaseDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR;
extern G__linked_taginfo G__G__GeoBaseDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__G__GeoBaseDictLN_TList;
extern G__linked_taginfo G__G__GeoBaseDictLN_TObjArray;
extern G__linked_taginfo G__G__GeoBaseDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR;
extern G__linked_taginfo G__G__GeoBaseDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoTransform;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoVolume;
extern G__linked_taginfo G__G__GeoBaseDictLN_TArrayD;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoBasicShape;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoAssembly;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoCone;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoCons;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoEltu;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoNode;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoMedium;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoBuilder;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoIo;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoSet;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoMedia;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoShapes;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoInterface;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoLoader;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoVector;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoMatrix;
extern G__linked_taginfo G__G__GeoBaseDictLN_TRotMatrix;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoRotation;
extern G__linked_taginfo G__G__GeoBaseDictLN_iteratorlEbidirectional_iterator_tagcOTObjectmUcOlongcOconstsPTObjectmUmUcOconstsPTObjectmUaNgR;
extern G__linked_taginfo G__G__GeoBaseDictLN_maplEintcOTGeoElementRNmUcOlesslEintgRcOallocatorlEpairlEconstsPintcOTGeoElementRNmUgRsPgRsPgR;
extern G__linked_taginfo G__G__GeoBaseDictLN_TGeoVolume;
extern G__linked_taginfo G__G__GeoBaseDictLN_TGeoManager;
extern G__linked_taginfo G__G__GeoBaseDictLN_vectorlETGeoVolumeAssemblycLcLThreadData_tmUcOallocatorlETGeoVolumeAssemblycLcLThreadData_tmUgRsPgR;
extern G__linked_taginfo G__G__GeoBaseDictLN_reverse_iteratorlEvectorlETGeoVolumeAssemblycLcLThreadData_tmUcOallocatorlETGeoVolumeAssemblycLcLThreadData_tmUgRsPgRcLcLiteratorgR;
extern G__linked_taginfo G__G__GeoBaseDictLN_EFairGeoNodeType;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoOldAsciiIo;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoPcon;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoPgon;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoRootBuilder;
extern G__linked_taginfo G__G__GeoBaseDictLN_TArrayI;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoSphe;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoTrap;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoTrd1;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoTube;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoTubs;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoTorus;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoCompositeVolume;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoAsciiIo;
extern G__linked_taginfo G__G__GeoBaseDictLN_FairGeoBrik;

/* STUB derived class for protected member access */