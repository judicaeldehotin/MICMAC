#include "StdAfx.h"
//#include "general/all.h"
//#include "private/all.h"
// #include "XML_GEN/ParamChantierPhotogram.h"
namespace NS_ParamChantierPhotogram{
eTypeMalt  Str2eTypeMalt(const std::string & aName)
{
   if (aName=="eOrtho")
      return eOrtho;
   else if (aName=="eUrbanMNE")
      return eUrbanMNE;
   else if (aName=="eGeomImage")
      return eGeomImage;
   else if (aName=="eNbTypesMNE")
      return eNbTypesMNE;
  else
  {
      cout << aName << " is not a correct value for enum eTypeMalt\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eTypeMalt) 0;
}
void xml_init(eTypeMalt & aVal,cElXMLTree * aTree)
{
   aVal= Str2eTypeMalt(aTree->Contenu());
}
std::string  eToString(const eTypeMalt & anObj)
{
   if (anObj==eOrtho)
      return  "eOrtho";
   if (anObj==eUrbanMNE)
      return  "eUrbanMNE";
   if (anObj==eGeomImage)
      return  "eGeomImage";
   if (anObj==eNbTypesMNE)
      return  "eNbTypesMNE";
 std::cout << "Enum = eTypeMalt\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypeMalt & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eTypeFichierApp  Str2eTypeFichierApp(const std::string & aName)
{
   if (aName=="eAppEgels")
      return eAppEgels;
   else if (aName=="eAppGeoCub")
      return eAppGeoCub;
   else if (aName=="eAppInFile")
      return eAppInFile;
   else if (aName=="eAppXML")
      return eAppXML;
   else if (aName=="eNbTypeApp")
      return eNbTypeApp;
  else
  {
      cout << aName << " is not a correct value for enum eTypeFichierApp\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eTypeFichierApp) 0;
}
void xml_init(eTypeFichierApp & aVal,cElXMLTree * aTree)
{
   aVal= Str2eTypeFichierApp(aTree->Contenu());
}
std::string  eToString(const eTypeFichierApp & anObj)
{
   if (anObj==eAppEgels)
      return  "eAppEgels";
   if (anObj==eAppGeoCub)
      return  "eAppGeoCub";
   if (anObj==eAppInFile)
      return  "eAppInFile";
   if (anObj==eAppXML)
      return  "eAppXML";
   if (anObj==eNbTypeApp)
      return  "eNbTypeApp";
 std::cout << "Enum = eTypeFichierApp\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypeFichierApp & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eTypeFichierOriTxt  Str2eTypeFichierOriTxt(const std::string & aName)
{
   if (aName=="eOriTxtAgiSoft")
      return eOriTxtAgiSoft;
   else if (aName=="eOriTxtInFile")
      return eOriTxtInFile;
   else if (aName=="eNbTypeOriTxt")
      return eNbTypeOriTxt;
  else
  {
      cout << aName << " is not a correct value for enum eTypeFichierOriTxt\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eTypeFichierOriTxt) 0;
}
void xml_init(eTypeFichierOriTxt & aVal,cElXMLTree * aTree)
{
   aVal= Str2eTypeFichierOriTxt(aTree->Contenu());
}
std::string  eToString(const eTypeFichierOriTxt & anObj)
{
   if (anObj==eOriTxtAgiSoft)
      return  "eOriTxtAgiSoft";
   if (anObj==eOriTxtInFile)
      return  "eOriTxtInFile";
   if (anObj==eNbTypeOriTxt)
      return  "eNbTypeOriTxt";
 std::cout << "Enum = eTypeFichierOriTxt\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypeFichierOriTxt & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eTypeNumerique  Str2eTypeNumerique(const std::string & aName)
{
   if (aName=="eTN_u_int1")
      return eTN_u_int1;
   else if (aName=="eTN_int1")
      return eTN_int1;
   else if (aName=="eTN_u_int2")
      return eTN_u_int2;
   else if (aName=="eTN_int2")
      return eTN_int2;
   else if (aName=="eTN_int4")
      return eTN_int4;
   else if (aName=="eTN_float")
      return eTN_float;
   else if (aName=="eTN_double")
      return eTN_double;
   else if (aName=="eTN_Bits1MSBF")
      return eTN_Bits1MSBF;
  else
  {
      cout << aName << " is not a correct value for enum eTypeNumerique\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eTypeNumerique) 0;
}
void xml_init(eTypeNumerique & aVal,cElXMLTree * aTree)
{
   aVal= Str2eTypeNumerique(aTree->Contenu());
}
std::string  eToString(const eTypeNumerique & anObj)
{
   if (anObj==eTN_u_int1)
      return  "eTN_u_int1";
   if (anObj==eTN_int1)
      return  "eTN_int1";
   if (anObj==eTN_u_int2)
      return  "eTN_u_int2";
   if (anObj==eTN_int2)
      return  "eTN_int2";
   if (anObj==eTN_int4)
      return  "eTN_int4";
   if (anObj==eTN_float)
      return  "eTN_float";
   if (anObj==eTN_double)
      return  "eTN_double";
   if (anObj==eTN_Bits1MSBF)
      return  "eTN_Bits1MSBF";
 std::cout << "Enum = eTypeNumerique\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypeNumerique & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eComprTiff  Str2eComprTiff(const std::string & aName)
{
   if (aName=="eComprTiff_None")
      return eComprTiff_None;
   else if (aName=="eComprTiff_LZW")
      return eComprTiff_LZW;
   else if (aName=="eComprTiff_FAX4")
      return eComprTiff_FAX4;
   else if (aName=="eComprTiff_PackBits")
      return eComprTiff_PackBits;
  else
  {
      cout << aName << " is not a correct value for enum eComprTiff\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eComprTiff) 0;
}
void xml_init(eComprTiff & aVal,cElXMLTree * aTree)
{
   aVal= Str2eComprTiff(aTree->Contenu());
}
std::string  eToString(const eComprTiff & anObj)
{
   if (anObj==eComprTiff_None)
      return  "eComprTiff_None";
   if (anObj==eComprTiff_LZW)
      return  "eComprTiff_LZW";
   if (anObj==eComprTiff_FAX4)
      return  "eComprTiff_FAX4";
   if (anObj==eComprTiff_PackBits)
      return  "eComprTiff_PackBits";
 std::cout << "Enum = eComprTiff\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eComprTiff & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eTypePreCondRad  Str2eTypePreCondRad(const std::string & aName)
{
   if (aName=="ePCR_Atgt")
      return ePCR_Atgt;
   else if (aName=="ePCR_2SinAtgtS2")
      return ePCR_2SinAtgtS2;
  else
  {
      cout << aName << " is not a correct value for enum eTypePreCondRad\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eTypePreCondRad) 0;
}
void xml_init(eTypePreCondRad & aVal,cElXMLTree * aTree)
{
   aVal= Str2eTypePreCondRad(aTree->Contenu());
}
std::string  eToString(const eTypePreCondRad & anObj)
{
   if (anObj==ePCR_Atgt)
      return  "ePCR_Atgt";
   if (anObj==ePCR_2SinAtgtS2)
      return  "ePCR_2SinAtgtS2";
 std::cout << "Enum = eTypePreCondRad\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypePreCondRad & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eModeGeomMNT  Str2eModeGeomMNT(const std::string & aName)
{
   if (aName=="eGeomMNTCarto")
      return eGeomMNTCarto;
   else if (aName=="eGeomMNTEuclid")
      return eGeomMNTEuclid;
   else if (aName=="eGeomMNTFaisceauIm1PrCh_Px1D")
      return eGeomMNTFaisceauIm1PrCh_Px1D;
   else if (aName=="eGeomMNTFaisceauIm1PrCh_Px2D")
      return eGeomMNTFaisceauIm1PrCh_Px2D;
   else if (aName=="eGeomMNTFaisceauIm1ZTerrain_Px1D")
      return eGeomMNTFaisceauIm1ZTerrain_Px1D;
   else if (aName=="eGeomMNTFaisceauIm1ZTerrain_Px2D")
      return eGeomMNTFaisceauIm1ZTerrain_Px2D;
   else if (aName=="eGeomPxBiDim")
      return eGeomPxBiDim;
   else if (aName=="eNoGeomMNT")
      return eNoGeomMNT;
   else if (aName=="eGeomMNTFaisceauPrChSpherik")
      return eGeomMNTFaisceauPrChSpherik;
  else
  {
      cout << aName << " is not a correct value for enum eModeGeomMNT\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eModeGeomMNT) 0;
}
void xml_init(eModeGeomMNT & aVal,cElXMLTree * aTree)
{
   aVal= Str2eModeGeomMNT(aTree->Contenu());
}
std::string  eToString(const eModeGeomMNT & anObj)
{
   if (anObj==eGeomMNTCarto)
      return  "eGeomMNTCarto";
   if (anObj==eGeomMNTEuclid)
      return  "eGeomMNTEuclid";
   if (anObj==eGeomMNTFaisceauIm1PrCh_Px1D)
      return  "eGeomMNTFaisceauIm1PrCh_Px1D";
   if (anObj==eGeomMNTFaisceauIm1PrCh_Px2D)
      return  "eGeomMNTFaisceauIm1PrCh_Px2D";
   if (anObj==eGeomMNTFaisceauIm1ZTerrain_Px1D)
      return  "eGeomMNTFaisceauIm1ZTerrain_Px1D";
   if (anObj==eGeomMNTFaisceauIm1ZTerrain_Px2D)
      return  "eGeomMNTFaisceauIm1ZTerrain_Px2D";
   if (anObj==eGeomPxBiDim)
      return  "eGeomPxBiDim";
   if (anObj==eNoGeomMNT)
      return  "eNoGeomMNT";
   if (anObj==eGeomMNTFaisceauPrChSpherik)
      return  "eGeomMNTFaisceauPrChSpherik";
 std::cout << "Enum = eModeGeomMNT\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eModeGeomMNT & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eModeBinSift  Str2eModeBinSift(const std::string & aName)
{
   if (aName=="eModeLeBrisPP")
      return eModeLeBrisPP;
   else if (aName=="eModeAutopano")
      return eModeAutopano;
  else
  {
      cout << aName << " is not a correct value for enum eModeBinSift\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eModeBinSift) 0;
}
void xml_init(eModeBinSift & aVal,cElXMLTree * aTree)
{
   aVal= Str2eModeBinSift(aTree->Contenu());
}
std::string  eToString(const eModeBinSift & anObj)
{
   if (anObj==eModeLeBrisPP)
      return  "eModeLeBrisPP";
   if (anObj==eModeAutopano)
      return  "eModeAutopano";
 std::cout << "Enum = eModeBinSift\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eModeBinSift & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eModeSolveurEq  Str2eModeSolveurEq(const std::string & aName)
{
   if (aName=="eSysPlein")
      return eSysPlein;
   else if (aName=="eSysCreuxMap")
      return eSysCreuxMap;
   else if (aName=="eSysCreuxFixe")
      return eSysCreuxFixe;
   else if (aName=="eSysL1Barrodale")
      return eSysL1Barrodale;
   else if (aName=="eSysL2BlocSym")
      return eSysL2BlocSym;
  else
  {
      cout << aName << " is not a correct value for enum eModeSolveurEq\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eModeSolveurEq) 0;
}
void xml_init(eModeSolveurEq & aVal,cElXMLTree * aTree)
{
   aVal= Str2eModeSolveurEq(aTree->Contenu());
}
std::string  eToString(const eModeSolveurEq & anObj)
{
   if (anObj==eSysPlein)
      return  "eSysPlein";
   if (anObj==eSysCreuxMap)
      return  "eSysCreuxMap";
   if (anObj==eSysCreuxFixe)
      return  "eSysCreuxFixe";
   if (anObj==eSysL1Barrodale)
      return  "eSysL1Barrodale";
   if (anObj==eSysL2BlocSym)
      return  "eSysL2BlocSym";
 std::cout << "Enum = eModeSolveurEq\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eModeSolveurEq & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eUniteAngulaire  Str2eUniteAngulaire(const std::string & aName)
{
   if (aName=="eUniteAngleDegre")
      return eUniteAngleDegre;
   else if (aName=="eUniteAngleGrade")
      return eUniteAngleGrade;
   else if (aName=="eUniteAngleRadian")
      return eUniteAngleRadian;
  else
  {
      cout << aName << " is not a correct value for enum eUniteAngulaire\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eUniteAngulaire) 0;
}
void xml_init(eUniteAngulaire & aVal,cElXMLTree * aTree)
{
   aVal= Str2eUniteAngulaire(aTree->Contenu());
}
std::string  eToString(const eUniteAngulaire & anObj)
{
   if (anObj==eUniteAngleDegre)
      return  "eUniteAngleDegre";
   if (anObj==eUniteAngleGrade)
      return  "eUniteAngleGrade";
   if (anObj==eUniteAngleRadian)
      return  "eUniteAngleRadian";
 std::cout << "Enum = eUniteAngulaire\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eUniteAngulaire & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eDegreLiberteCPP  Str2eDegreLiberteCPP(const std::string & aName)
{
   if (aName=="eCPPFiges")
      return eCPPFiges;
   else if (aName=="eCPPLies")
      return eCPPLies;
   else if (aName=="eCPPLibres")
      return eCPPLibres;
  else
  {
      cout << aName << " is not a correct value for enum eDegreLiberteCPP\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eDegreLiberteCPP) 0;
}
void xml_init(eDegreLiberteCPP & aVal,cElXMLTree * aTree)
{
   aVal= Str2eDegreLiberteCPP(aTree->Contenu());
}
std::string  eToString(const eDegreLiberteCPP & anObj)
{
   if (anObj==eCPPFiges)
      return  "eCPPFiges";
   if (anObj==eCPPLies)
      return  "eCPPLies";
   if (anObj==eCPPLibres)
      return  "eCPPLibres";
 std::cout << "Enum = eDegreLiberteCPP\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eDegreLiberteCPP & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eModelesCalibUnif  Str2eModelesCalibUnif(const std::string & aName)
{
   if (aName=="eModeleEbner")
      return eModeleEbner;
   else if (aName=="eModeleDCBrown")
      return eModeleDCBrown;
   else if (aName=="eModelePolyDeg2")
      return eModelePolyDeg2;
   else if (aName=="eModelePolyDeg3")
      return eModelePolyDeg3;
   else if (aName=="eModelePolyDeg4")
      return eModelePolyDeg4;
   else if (aName=="eModelePolyDeg5")
      return eModelePolyDeg5;
   else if (aName=="eModelePolyDeg6")
      return eModelePolyDeg6;
   else if (aName=="eModelePolyDeg7")
      return eModelePolyDeg7;
   else if (aName=="eModele_FishEye_10_5_5")
      return eModele_FishEye_10_5_5;
   else if (aName=="eModele_EquiSolid_FishEye_10_5_5")
      return eModele_EquiSolid_FishEye_10_5_5;
   else if (aName=="eModele_DRad_PPaEqPPs")
      return eModele_DRad_PPaEqPPs;
   else if (aName=="eModele_Fraser_PPaEqPPs")
      return eModele_Fraser_PPaEqPPs;
  else
  {
      cout << aName << " is not a correct value for enum eModelesCalibUnif\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eModelesCalibUnif) 0;
}
void xml_init(eModelesCalibUnif & aVal,cElXMLTree * aTree)
{
   aVal= Str2eModelesCalibUnif(aTree->Contenu());
}
std::string  eToString(const eModelesCalibUnif & anObj)
{
   if (anObj==eModeleEbner)
      return  "eModeleEbner";
   if (anObj==eModeleDCBrown)
      return  "eModeleDCBrown";
   if (anObj==eModelePolyDeg2)
      return  "eModelePolyDeg2";
   if (anObj==eModelePolyDeg3)
      return  "eModelePolyDeg3";
   if (anObj==eModelePolyDeg4)
      return  "eModelePolyDeg4";
   if (anObj==eModelePolyDeg5)
      return  "eModelePolyDeg5";
   if (anObj==eModelePolyDeg6)
      return  "eModelePolyDeg6";
   if (anObj==eModelePolyDeg7)
      return  "eModelePolyDeg7";
   if (anObj==eModele_FishEye_10_5_5)
      return  "eModele_FishEye_10_5_5";
   if (anObj==eModele_EquiSolid_FishEye_10_5_5)
      return  "eModele_EquiSolid_FishEye_10_5_5";
   if (anObj==eModele_DRad_PPaEqPPs)
      return  "eModele_DRad_PPaEqPPs";
   if (anObj==eModele_Fraser_PPaEqPPs)
      return  "eModele_Fraser_PPaEqPPs";
 std::cout << "Enum = eModelesCalibUnif\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eModelesCalibUnif & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eTypeProjectionCam  Str2eTypeProjectionCam(const std::string & aName)
{
   if (aName=="eProjStenope")
      return eProjStenope;
   else if (aName=="eProjOrthographique")
      return eProjOrthographique;
  else
  {
      cout << aName << " is not a correct value for enum eTypeProjectionCam\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eTypeProjectionCam) 0;
}
void xml_init(eTypeProjectionCam & aVal,cElXMLTree * aTree)
{
   aVal= Str2eTypeProjectionCam(aTree->Contenu());
}
std::string  eToString(const eTypeProjectionCam & anObj)
{
   if (anObj==eProjStenope)
      return  "eProjStenope";
   if (anObj==eProjOrthographique)
      return  "eProjOrthographique";
 std::cout << "Enum = eTypeProjectionCam\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypeProjectionCam & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}

eTypeCoord  Str2eTypeCoord(const std::string & aName)
{
   if (aName=="eTC_WGS84")
      return eTC_WGS84;
   else if (aName=="eTC_GeoCentr")
      return eTC_GeoCentr;
   else if (aName=="eTC_RTL")
      return eTC_RTL;
   else if (aName=="eTC_Polyn")
      return eTC_Polyn;
   else if (aName=="eTC_Unknown")
      return eTC_Unknown;
   else if (aName=="eTC_Lambert93")
      return eTC_Lambert93;
   else if (aName=="eTC_LambertCC")
      return eTC_LambertCC;
   else if (aName=="eTC_Proj4")
      return eTC_Proj4;
  else
  {
      cout << aName << " is not a correct value for enum eTypeCoord\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eTypeCoord) 0;
}
void xml_init(eTypeCoord & aVal,cElXMLTree * aTree)
{
   aVal= Str2eTypeCoord(aTree->Contenu());
}
std::string  eToString(const eTypeCoord & anObj)
{
   if (anObj==eTC_WGS84)
      return  "eTC_WGS84";
   if (anObj==eTC_GeoCentr)
      return  "eTC_GeoCentr";
   if (anObj==eTC_RTL)
      return  "eTC_RTL";
   if (anObj==eTC_Polyn)
      return  "eTC_Polyn";
   if (anObj==eTC_Unknown)
      return  "eTC_Unknown";
   if (anObj==eTC_Lambert93)
      return  "eTC_Lambert93";
   if (anObj==eTC_LambertCC)
      return  "eTC_LambertCC";
   if (anObj==eTC_Proj4)
      return  "eTC_Proj4";
 std::cout << "Enum = eTypeCoord\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypeCoord & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}


std::string & cMicMacConfiguration::DirInstall()
{
   return mDirInstall;
}

const std::string & cMicMacConfiguration::DirInstall()const 
{
   return mDirInstall;
}


int & cMicMacConfiguration::NbProcess()
{
   return mNbProcess;
}

const int & cMicMacConfiguration::NbProcess()const 
{
   return mNbProcess;
}

cElXMLTree * ToXMLTree(const cMicMacConfiguration & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"MicMacConfiguration",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("DirInstall"),anObj.DirInstall())->ReTagThis("DirInstall"));
   aRes->AddFils(::ToXMLTree(std::string("NbProcess"),anObj.NbProcess())->ReTagThis("NbProcess"));
  return aRes;
}

void xml_init(cMicMacConfiguration & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.DirInstall(),aTree->Get("DirInstall",1)); //tototo 

   xml_init(anObj.NbProcess(),aTree->Get("NbProcess",1)); //tototo 
}


eTypeCoord & cBasicSystemeCoord::TypeCoord()
{
   return mTypeCoord;
}

const eTypeCoord & cBasicSystemeCoord::TypeCoord()const 
{
   return mTypeCoord;
}


std::vector< double > & cBasicSystemeCoord::AuxR()
{
   return mAuxR;
}

const std::vector< double > & cBasicSystemeCoord::AuxR()const 
{
   return mAuxR;
}


std::vector< int > & cBasicSystemeCoord::AuxI()
{
   return mAuxI;
}

const std::vector< int > & cBasicSystemeCoord::AuxI()const 
{
   return mAuxI;
}


std::vector< std::string > & cBasicSystemeCoord::AuxStr()
{
   return mAuxStr;
}

const std::vector< std::string > & cBasicSystemeCoord::AuxStr()const 
{
   return mAuxStr;
}


cTplValGesInit< bool > & cBasicSystemeCoord::ByFile()
{
   return mByFile;
}

const cTplValGesInit< bool > & cBasicSystemeCoord::ByFile()const 
{
   return mByFile;
}


std::vector< eUniteAngulaire > & cBasicSystemeCoord::AuxRUnite()
{
   return mAuxRUnite;
}

const std::vector< eUniteAngulaire > & cBasicSystemeCoord::AuxRUnite()const 
{
   return mAuxRUnite;
}

cElXMLTree * ToXMLTree(const cBasicSystemeCoord & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"BasicSystemeCoord",eXMLBranche);
   aRes->AddFils(ToXMLTree(std::string("TypeCoord"),anObj.TypeCoord())->ReTagThis("TypeCoord"));
  for
  (       std::vector< double >::const_iterator it=anObj.AuxR().begin();
      it !=anObj.AuxR().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("AuxR"),(*it))->ReTagThis("AuxR"));
  for
  (       std::vector< int >::const_iterator it=anObj.AuxI().begin();
      it !=anObj.AuxI().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("AuxI"),(*it))->ReTagThis("AuxI"));
  for
  (       std::vector< std::string >::const_iterator it=anObj.AuxStr().begin();
      it !=anObj.AuxStr().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("AuxStr"),(*it))->ReTagThis("AuxStr"));
   if (anObj.ByFile().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("ByFile"),anObj.ByFile().Val())->ReTagThis("ByFile"));
  for
  (       std::vector< eUniteAngulaire >::const_iterator it=anObj.AuxRUnite().begin();
      it !=anObj.AuxRUnite().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree(std::string("AuxRUnite"),(*it))->ReTagThis("AuxRUnite"));
  return aRes;
}

void xml_init(cBasicSystemeCoord & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.TypeCoord(),aTree->Get("TypeCoord",1)); //tototo 

   xml_init(anObj.AuxR(),aTree->GetAll("AuxR",false,1));

   xml_init(anObj.AuxI(),aTree->GetAll("AuxI",false,1));

   xml_init(anObj.AuxStr(),aTree->GetAll("AuxStr",false,1));

   xml_init(anObj.ByFile(),aTree->Get("ByFile",1),bool(false)); //tototo 

   xml_init(anObj.AuxRUnite(),aTree->GetAll("AuxRUnite",false,1));
}


cTplValGesInit< std::string > & cSystemeCoord::Comment()
{
   return mComment;
}

const cTplValGesInit< std::string > & cSystemeCoord::Comment()const 
{
   return mComment;
}


std::vector< cBasicSystemeCoord > & cSystemeCoord::BSC()
{
   return mBSC;
}

const std::vector< cBasicSystemeCoord > & cSystemeCoord::BSC()const 
{
   return mBSC;
}

cElXMLTree * ToXMLTree(const cSystemeCoord & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"SystemeCoord",eXMLBranche);
   if (anObj.Comment().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Comment"),anObj.Comment().Val())->ReTagThis("Comment"));
  for
  (       std::vector< cBasicSystemeCoord >::const_iterator it=anObj.BSC().begin();
      it !=anObj.BSC().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("BSC"));
  return aRes;
}

void xml_init(cSystemeCoord & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Comment(),aTree->Get("Comment",1)); //tototo 

   xml_init(anObj.BSC(),aTree->GetAll("BSC",false,1));
}


cSystemeCoord & cChangementCoordonnees::SystemeSource()
{
   return mSystemeSource;
}

const cSystemeCoord & cChangementCoordonnees::SystemeSource()const 
{
   return mSystemeSource;
}


cSystemeCoord & cChangementCoordonnees::SystemeCible()
{
   return mSystemeCible;
}

const cSystemeCoord & cChangementCoordonnees::SystemeCible()const 
{
   return mSystemeCible;
}

cElXMLTree * ToXMLTree(const cChangementCoordonnees & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ChangementCoordonnees",eXMLBranche);
   aRes->AddFils(ToXMLTree(anObj.SystemeSource())->ReTagThis("SystemeSource"));
   aRes->AddFils(ToXMLTree(anObj.SystemeCible())->ReTagThis("SystemeCible"));
  return aRes;
}

void xml_init(cChangementCoordonnees & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.SystemeSource(),aTree->Get("SystemeSource",1)); //tototo 

   xml_init(anObj.SystemeCible(),aTree->Get("SystemeCible",1)); //tototo 
}


std::string & cFileOriMnt::NameFileMnt()
{
   return mNameFileMnt;
}

const std::string & cFileOriMnt::NameFileMnt()const 
{
   return mNameFileMnt;
}


cTplValGesInit< std::string > & cFileOriMnt::NameFileMasque()
{
   return mNameFileMasque;
}

const cTplValGesInit< std::string > & cFileOriMnt::NameFileMasque()const 
{
   return mNameFileMasque;
}


Pt2di & cFileOriMnt::NombrePixels()
{
   return mNombrePixels;
}

const Pt2di & cFileOriMnt::NombrePixels()const 
{
   return mNombrePixels;
}


Pt2dr & cFileOriMnt::OriginePlani()
{
   return mOriginePlani;
}

const Pt2dr & cFileOriMnt::OriginePlani()const 
{
   return mOriginePlani;
}


Pt2dr & cFileOriMnt::ResolutionPlani()
{
   return mResolutionPlani;
}

const Pt2dr & cFileOriMnt::ResolutionPlani()const 
{
   return mResolutionPlani;
}


double & cFileOriMnt::OrigineAlti()
{
   return mOrigineAlti;
}

const double & cFileOriMnt::OrigineAlti()const 
{
   return mOrigineAlti;
}


double & cFileOriMnt::ResolutionAlti()
{
   return mResolutionAlti;
}

const double & cFileOriMnt::ResolutionAlti()const 
{
   return mResolutionAlti;
}


cTplValGesInit< int > & cFileOriMnt::NumZoneLambert()
{
   return mNumZoneLambert;
}

const cTplValGesInit< int > & cFileOriMnt::NumZoneLambert()const 
{
   return mNumZoneLambert;
}


eModeGeomMNT & cFileOriMnt::Geometrie()
{
   return mGeometrie;
}

const eModeGeomMNT & cFileOriMnt::Geometrie()const 
{
   return mGeometrie;
}


cTplValGesInit< Pt2dr > & cFileOriMnt::OrigineTgtLoc()
{
   return mOrigineTgtLoc;
}

const cTplValGesInit< Pt2dr > & cFileOriMnt::OrigineTgtLoc()const 
{
   return mOrigineTgtLoc;
}

cElXMLTree * ToXMLTree(const cFileOriMnt & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"FileOriMnt",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("NameFileMnt"),anObj.NameFileMnt())->ReTagThis("NameFileMnt"));
   if (anObj.NameFileMasque().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NameFileMasque"),anObj.NameFileMasque().Val())->ReTagThis("NameFileMasque"));
   aRes->AddFils(::ToXMLTree(std::string("NombrePixels"),anObj.NombrePixels())->ReTagThis("NombrePixels"));
   aRes->AddFils(::ToXMLTree(std::string("OriginePlani"),anObj.OriginePlani())->ReTagThis("OriginePlani"));
   aRes->AddFils(::ToXMLTree(std::string("ResolutionPlani"),anObj.ResolutionPlani())->ReTagThis("ResolutionPlani"));
   aRes->AddFils(::ToXMLTree(std::string("OrigineAlti"),anObj.OrigineAlti())->ReTagThis("OrigineAlti"));
   aRes->AddFils(::ToXMLTree(std::string("ResolutionAlti"),anObj.ResolutionAlti())->ReTagThis("ResolutionAlti"));
   if (anObj.NumZoneLambert().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NumZoneLambert"),anObj.NumZoneLambert().Val())->ReTagThis("NumZoneLambert"));
   aRes->AddFils(ToXMLTree(std::string("Geometrie"),anObj.Geometrie())->ReTagThis("Geometrie"));
   if (anObj.OrigineTgtLoc().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("OrigineTgtLoc"),anObj.OrigineTgtLoc().Val())->ReTagThis("OrigineTgtLoc"));
  return aRes;
}

void xml_init(cFileOriMnt & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NameFileMnt(),aTree->Get("NameFileMnt",1)); //tototo 

   xml_init(anObj.NameFileMasque(),aTree->Get("NameFileMasque",1)); //tototo 

   xml_init(anObj.NombrePixels(),aTree->Get("NombrePixels",1)); //tototo 

   xml_init(anObj.OriginePlani(),aTree->Get("OriginePlani",1)); //tototo 

   xml_init(anObj.ResolutionPlani(),aTree->Get("ResolutionPlani",1)); //tototo 

   xml_init(anObj.OrigineAlti(),aTree->Get("OrigineAlti",1)); //tototo 

   xml_init(anObj.ResolutionAlti(),aTree->Get("ResolutionAlti",1)); //tototo 

   xml_init(anObj.NumZoneLambert(),aTree->Get("NumZoneLambert",1)); //tototo 

   xml_init(anObj.Geometrie(),aTree->Get("Geometrie",1)); //tototo 

   xml_init(anObj.OrigineTgtLoc(),aTree->Get("OrigineTgtLoc",1)); //tototo 
}


Pt2dr & cRefPlani::Origine()
{
   return mOrigine;
}

const Pt2dr & cRefPlani::Origine()const 
{
   return mOrigine;
}


Pt2dr & cRefPlani::Resolution()
{
   return mResolution;
}

const Pt2dr & cRefPlani::Resolution()const 
{
   return mResolution;
}

cElXMLTree * ToXMLTree(const cRefPlani & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"RefPlani",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Origine"),anObj.Origine())->ReTagThis("Origine"));
   aRes->AddFils(::ToXMLTree(std::string("Resolution"),anObj.Resolution())->ReTagThis("Resolution"));
  return aRes;
}

void xml_init(cRefPlani & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Origine(),aTree->Get("Origine",1)); //tototo 

   xml_init(anObj.Resolution(),aTree->Get("Resolution",1)); //tototo 
}


double & cRefAlti::Origine()
{
   return mOrigine;
}

const double & cRefAlti::Origine()const 
{
   return mOrigine;
}


double & cRefAlti::Resolution()
{
   return mResolution;
}

const double & cRefAlti::Resolution()const 
{
   return mResolution;
}

cElXMLTree * ToXMLTree(const cRefAlti & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"RefAlti",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Origine"),anObj.Origine())->ReTagThis("Origine"));
   aRes->AddFils(::ToXMLTree(std::string("Resolution"),anObj.Resolution())->ReTagThis("Resolution"));
  return aRes;
}

void xml_init(cRefAlti & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Origine(),aTree->Get("Origine",1)); //tototo 

   xml_init(anObj.Resolution(),aTree->Get("Resolution",1)); //tototo 
}


cTplValGesInit< cRefAlti > & cGestionAltimetrie::RefAlti()
{
   return mRefAlti;
}

const cTplValGesInit< cRefAlti > & cGestionAltimetrie::RefAlti()const 
{
   return mRefAlti;
}


cTplValGesInit< double > & cGestionAltimetrie::ZMoyen()
{
   return mZMoyen;
}

const cTplValGesInit< double > & cGestionAltimetrie::ZMoyen()const 
{
   return mZMoyen;
}

cElXMLTree * ToXMLTree(const cGestionAltimetrie & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"GestionAltimetrie",eXMLBranche);
   if (anObj.RefAlti().IsInit())
      aRes->AddFils(ToXMLTree(anObj.RefAlti().Val())->ReTagThis("RefAlti"));
   if (anObj.ZMoyen().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("ZMoyen"),anObj.ZMoyen().Val())->ReTagThis("ZMoyen"));
  return aRes;
}

void xml_init(cGestionAltimetrie & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.RefAlti(),aTree->Get("RefAlti",1)); //tototo 

   xml_init(anObj.ZMoyen(),aTree->Get("ZMoyen",1)); //tototo 
}


cTplValGesInit< cSystemeCoord > & cXmlGeoRefFile::SysCo()
{
   return mSysCo;
}

const cTplValGesInit< cSystemeCoord > & cXmlGeoRefFile::SysCo()const 
{
   return mSysCo;
}


cRefPlani & cXmlGeoRefFile::RefPlani()
{
   return mRefPlani;
}

const cRefPlani & cXmlGeoRefFile::RefPlani()const 
{
   return mRefPlani;
}


cTplValGesInit< cRefAlti > & cXmlGeoRefFile::RefAlti()
{
   return GestionAltimetrie().RefAlti();
}

const cTplValGesInit< cRefAlti > & cXmlGeoRefFile::RefAlti()const 
{
   return GestionAltimetrie().RefAlti();
}


cTplValGesInit< double > & cXmlGeoRefFile::ZMoyen()
{
   return GestionAltimetrie().ZMoyen();
}

const cTplValGesInit< double > & cXmlGeoRefFile::ZMoyen()const 
{
   return GestionAltimetrie().ZMoyen();
}


cGestionAltimetrie & cXmlGeoRefFile::GestionAltimetrie()
{
   return mGestionAltimetrie;
}

const cGestionAltimetrie & cXmlGeoRefFile::GestionAltimetrie()const 
{
   return mGestionAltimetrie;
}

cElXMLTree * ToXMLTree(const cXmlGeoRefFile & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"XmlGeoRefFile",eXMLBranche);
   if (anObj.SysCo().IsInit())
      aRes->AddFils(ToXMLTree(anObj.SysCo().Val())->ReTagThis("SysCo"));
   aRes->AddFils(ToXMLTree(anObj.RefPlani())->ReTagThis("RefPlani"));
   aRes->AddFils(ToXMLTree(anObj.GestionAltimetrie())->ReTagThis("GestionAltimetrie"));
  return aRes;
}

void xml_init(cXmlGeoRefFile & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.SysCo(),aTree->Get("SysCo",1)); //tototo 

   xml_init(anObj.RefPlani(),aTree->Get("RefPlani",1)); //tototo 

   xml_init(anObj.GestionAltimetrie(),aTree->Get("GestionAltimetrie",1)); //tototo 
}


std::string & cSpecExtractFromFile::NameFile()
{
   return mNameFile;
}

const std::string & cSpecExtractFromFile::NameFile()const 
{
   return mNameFile;
}


std::string & cSpecExtractFromFile::NameTag()
{
   return mNameTag;
}

const std::string & cSpecExtractFromFile::NameTag()const 
{
   return mNameTag;
}


cTplValGesInit< bool > & cSpecExtractFromFile::AutorizeNonExisting()
{
   return mAutorizeNonExisting;
}

const cTplValGesInit< bool > & cSpecExtractFromFile::AutorizeNonExisting()const 
{
   return mAutorizeNonExisting;
}

cElXMLTree * ToXMLTree(const cSpecExtractFromFile & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"SpecExtractFromFile",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("NameFile"),anObj.NameFile())->ReTagThis("NameFile"));
   aRes->AddFils(::ToXMLTree(std::string("NameTag"),anObj.NameTag())->ReTagThis("NameTag"));
   if (anObj.AutorizeNonExisting().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("AutorizeNonExisting"),anObj.AutorizeNonExisting().Val())->ReTagThis("AutorizeNonExisting"));
  return aRes;
}

void xml_init(cSpecExtractFromFile & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NameFile(),aTree->Get("NameFile",1)); //tototo 

   xml_init(anObj.NameTag(),aTree->Get("NameTag",1)); //tototo 

   xml_init(anObj.AutorizeNonExisting(),aTree->Get("AutorizeNonExisting",1),bool(false)); //tototo 
}


std::string & cSpecifFormatRaw::NameFile()
{
   return mNameFile;
}

const std::string & cSpecifFormatRaw::NameFile()const 
{
   return mNameFile;
}


Pt2di & cSpecifFormatRaw::Sz()
{
   return mSz;
}

const Pt2di & cSpecifFormatRaw::Sz()const 
{
   return mSz;
}


bool & cSpecifFormatRaw::MSBF()
{
   return mMSBF;
}

const bool & cSpecifFormatRaw::MSBF()const 
{
   return mMSBF;
}


int & cSpecifFormatRaw::NbBitsParPixel()
{
   return mNbBitsParPixel;
}

const int & cSpecifFormatRaw::NbBitsParPixel()const 
{
   return mNbBitsParPixel;
}


bool & cSpecifFormatRaw::IntegerType()
{
   return mIntegerType;
}

const bool & cSpecifFormatRaw::IntegerType()const 
{
   return mIntegerType;
}


bool & cSpecifFormatRaw::SignedType()
{
   return mSignedType;
}

const bool & cSpecifFormatRaw::SignedType()const 
{
   return mSignedType;
}

cElXMLTree * ToXMLTree(const cSpecifFormatRaw & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"SpecifFormatRaw",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("NameFile"),anObj.NameFile())->ReTagThis("NameFile"));
   aRes->AddFils(::ToXMLTree(std::string("Sz"),anObj.Sz())->ReTagThis("Sz"));
   aRes->AddFils(::ToXMLTree(std::string("MSBF"),anObj.MSBF())->ReTagThis("MSBF"));
   aRes->AddFils(::ToXMLTree(std::string("NbBitsParPixel"),anObj.NbBitsParPixel())->ReTagThis("NbBitsParPixel"));
   aRes->AddFils(::ToXMLTree(std::string("IntegerType"),anObj.IntegerType())->ReTagThis("IntegerType"));
   aRes->AddFils(::ToXMLTree(std::string("SignedType"),anObj.SignedType())->ReTagThis("SignedType"));
  return aRes;
}

void xml_init(cSpecifFormatRaw & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NameFile(),aTree->Get("NameFile",1)); //tototo 

   xml_init(anObj.Sz(),aTree->Get("Sz",1)); //tototo 

   xml_init(anObj.MSBF(),aTree->Get("MSBF",1)); //tototo 

   xml_init(anObj.NbBitsParPixel(),aTree->Get("NbBitsParPixel",1)); //tototo 

   xml_init(anObj.IntegerType(),aTree->Get("IntegerType",1)); //tototo 

   xml_init(anObj.SignedType(),aTree->Get("SignedType",1)); //tototo 
}

eTotoModeGeomMEC  Str2eTotoModeGeomMEC(const std::string & aName)
{
   if (aName=="eTotoGeomMECIm1")
      return eTotoGeomMECIm1;
  else
  {
      cout << aName << " is not a correct value for enum eTotoModeGeomMEC\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eTotoModeGeomMEC) 0;
}
void xml_init(eTotoModeGeomMEC & aVal,cElXMLTree * aTree)
{
   aVal= Str2eTotoModeGeomMEC(aTree->Contenu());
}
std::string  eToString(const eTotoModeGeomMEC & anObj)
{
   if (anObj==eTotoGeomMECIm1)
      return  "eTotoGeomMECIm1";
 std::cout << "Enum = eTotoModeGeomMEC\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTotoModeGeomMEC & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}


std::string & cCM_Set::KeySet()
{
   return mKeySet;
}

const std::string & cCM_Set::KeySet()const 
{
   return mKeySet;
}


cTplValGesInit< std::string > & cCM_Set::KeyAssoc()
{
   return mKeyAssoc;
}

const cTplValGesInit< std::string > & cCM_Set::KeyAssoc()const 
{
   return mKeyAssoc;
}


std::string & cCM_Set::NameVarMap()
{
   return mNameVarMap;
}

const std::string & cCM_Set::NameVarMap()const 
{
   return mNameVarMap;
}

cElXMLTree * ToXMLTree(const cCM_Set & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CM_Set",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("KeySet"),anObj.KeySet())->ReTagThis("KeySet"));
   if (anObj.KeyAssoc().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("KeyAssoc"),anObj.KeyAssoc().Val())->ReTagThis("KeyAssoc"));
   aRes->AddFils(::ToXMLTree(std::string("NameVarMap"),anObj.NameVarMap())->ReTagThis("NameVarMap"));
  return aRes;
}

void xml_init(cCM_Set & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeySet(),aTree->Get("KeySet",1)); //tototo 

   xml_init(anObj.KeyAssoc(),aTree->Get("KeyAssoc",1)); //tototo 

   xml_init(anObj.NameVarMap(),aTree->Get("NameVarMap",1)); //tototo 
}


cTplValGesInit< std::string > & cModeCmdMapeur::CM_One()
{
   return mCM_One;
}

const cTplValGesInit< std::string > & cModeCmdMapeur::CM_One()const 
{
   return mCM_One;
}


std::string & cModeCmdMapeur::KeySet()
{
   return CM_Set().Val().KeySet();
}

const std::string & cModeCmdMapeur::KeySet()const 
{
   return CM_Set().Val().KeySet();
}


cTplValGesInit< std::string > & cModeCmdMapeur::KeyAssoc()
{
   return CM_Set().Val().KeyAssoc();
}

const cTplValGesInit< std::string > & cModeCmdMapeur::KeyAssoc()const 
{
   return CM_Set().Val().KeyAssoc();
}


std::string & cModeCmdMapeur::NameVarMap()
{
   return CM_Set().Val().NameVarMap();
}

const std::string & cModeCmdMapeur::NameVarMap()const 
{
   return CM_Set().Val().NameVarMap();
}


cTplValGesInit< cCM_Set > & cModeCmdMapeur::CM_Set()
{
   return mCM_Set;
}

const cTplValGesInit< cCM_Set > & cModeCmdMapeur::CM_Set()const 
{
   return mCM_Set;
}

cElXMLTree * ToXMLTree(const cModeCmdMapeur & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ModeCmdMapeur",eXMLBranche);
   if (anObj.CM_One().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("CM_One"),anObj.CM_One().Val())->ReTagThis("CM_One"));
   if (anObj.CM_Set().IsInit())
      aRes->AddFils(ToXMLTree(anObj.CM_Set().Val())->ReTagThis("CM_Set"));
  return aRes;
}

void xml_init(cModeCmdMapeur & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.CM_One(),aTree->Get("CM_One",1)); //tototo 

   xml_init(anObj.CM_Set(),aTree->Get("CM_Set",1)); //tototo 
}


std::string & cCmdMapRel::KeyRel()
{
   return mKeyRel;
}

const std::string & cCmdMapRel::KeyRel()const 
{
   return mKeyRel;
}


std::string & cCmdMapRel::NameArc()
{
   return mNameArc;
}

const std::string & cCmdMapRel::NameArc()const 
{
   return mNameArc;
}

cElXMLTree * ToXMLTree(const cCmdMapRel & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CmdMapRel",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("KeyRel"),anObj.KeyRel())->ReTagThis("KeyRel"));
   aRes->AddFils(::ToXMLTree(std::string("NameArc"),anObj.NameArc())->ReTagThis("NameArc"));
  return aRes;
}

void xml_init(cCmdMapRel & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeyRel(),aTree->Get("KeyRel",1)); //tototo 

   xml_init(anObj.NameArc(),aTree->Get("NameArc",1)); //tototo 
}


std::list< cCpleString > & cCMVA::NV()
{
   return mNV;
}

const std::list< cCpleString > & cCMVA::NV()const 
{
   return mNV;
}

cElXMLTree * ToXMLTree(const cCMVA & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CMVA",eXMLBranche);
  for
  (       std::list< cCpleString >::const_iterator it=anObj.NV().begin();
      it !=anObj.NV().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("NV"),(*it))->ReTagThis("NV"));
  return aRes;
}

void xml_init(cCMVA & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NV(),aTree->GetAll("NV",false,1));
}


bool & cCmdMappeur::ActivateCmdMap()
{
   return mActivateCmdMap;
}

const bool & cCmdMappeur::ActivateCmdMap()const 
{
   return mActivateCmdMap;
}


cTplValGesInit< std::string > & cCmdMappeur::CM_One()
{
   return ModeCmdMapeur().CM_One();
}

const cTplValGesInit< std::string > & cCmdMappeur::CM_One()const 
{
   return ModeCmdMapeur().CM_One();
}


std::string & cCmdMappeur::KeySet()
{
   return ModeCmdMapeur().CM_Set().Val().KeySet();
}

const std::string & cCmdMappeur::KeySet()const 
{
   return ModeCmdMapeur().CM_Set().Val().KeySet();
}


cTplValGesInit< std::string > & cCmdMappeur::KeyAssoc()
{
   return ModeCmdMapeur().CM_Set().Val().KeyAssoc();
}

const cTplValGesInit< std::string > & cCmdMappeur::KeyAssoc()const 
{
   return ModeCmdMapeur().CM_Set().Val().KeyAssoc();
}


std::string & cCmdMappeur::NameVarMap()
{
   return ModeCmdMapeur().CM_Set().Val().NameVarMap();
}

const std::string & cCmdMappeur::NameVarMap()const 
{
   return ModeCmdMapeur().CM_Set().Val().NameVarMap();
}


cTplValGesInit< cCM_Set > & cCmdMappeur::CM_Set()
{
   return ModeCmdMapeur().CM_Set();
}

const cTplValGesInit< cCM_Set > & cCmdMappeur::CM_Set()const 
{
   return ModeCmdMapeur().CM_Set();
}


cModeCmdMapeur & cCmdMappeur::ModeCmdMapeur()
{
   return mModeCmdMapeur;
}

const cModeCmdMapeur & cCmdMappeur::ModeCmdMapeur()const 
{
   return mModeCmdMapeur;
}


std::string & cCmdMappeur::KeyRel()
{
   return CmdMapRel().Val().KeyRel();
}

const std::string & cCmdMappeur::KeyRel()const 
{
   return CmdMapRel().Val().KeyRel();
}


std::string & cCmdMappeur::NameArc()
{
   return CmdMapRel().Val().NameArc();
}

const std::string & cCmdMappeur::NameArc()const 
{
   return CmdMapRel().Val().NameArc();
}


cTplValGesInit< cCmdMapRel > & cCmdMappeur::CmdMapRel()
{
   return mCmdMapRel;
}

const cTplValGesInit< cCmdMapRel > & cCmdMappeur::CmdMapRel()const 
{
   return mCmdMapRel;
}


std::list< cCMVA > & cCmdMappeur::CMVA()
{
   return mCMVA;
}

const std::list< cCMVA > & cCmdMappeur::CMVA()const 
{
   return mCMVA;
}


cTplValGesInit< std::string > & cCmdMappeur::ByMkF()
{
   return mByMkF;
}

const cTplValGesInit< std::string > & cCmdMappeur::ByMkF()const 
{
   return mByMkF;
}


cTplValGesInit< std::string > & cCmdMappeur::KeyTargetMkF()
{
   return mKeyTargetMkF;
}

const cTplValGesInit< std::string > & cCmdMappeur::KeyTargetMkF()const 
{
   return mKeyTargetMkF;
}

cElXMLTree * ToXMLTree(const cCmdMappeur & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CmdMappeur",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("ActivateCmdMap"),anObj.ActivateCmdMap())->ReTagThis("ActivateCmdMap"));
   aRes->AddFils(ToXMLTree(anObj.ModeCmdMapeur())->ReTagThis("ModeCmdMapeur"));
   if (anObj.CmdMapRel().IsInit())
      aRes->AddFils(ToXMLTree(anObj.CmdMapRel().Val())->ReTagThis("CmdMapRel"));
  for
  (       std::list< cCMVA >::const_iterator it=anObj.CMVA().begin();
      it !=anObj.CMVA().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("CMVA"));
   if (anObj.ByMkF().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("ByMkF"),anObj.ByMkF().Val())->ReTagThis("ByMkF"));
   if (anObj.KeyTargetMkF().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("KeyTargetMkF"),anObj.KeyTargetMkF().Val())->ReTagThis("KeyTargetMkF"));
  return aRes;
}

void xml_init(cCmdMappeur & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.ActivateCmdMap(),aTree->Get("ActivateCmdMap",1)); //tototo 

   xml_init(anObj.ModeCmdMapeur(),aTree->Get("ModeCmdMapeur",1)); //tototo 

   xml_init(anObj.CmdMapRel(),aTree->Get("CmdMapRel",1)); //tototo 

   xml_init(anObj.CMVA(),aTree->GetAll("CMVA",false,1));

   xml_init(anObj.ByMkF(),aTree->Get("ByMkF",1)); //tototo 

   xml_init(anObj.KeyTargetMkF(),aTree->Get("KeyTargetMkF",1)); //tototo 
}


std::list< std::string > & cOneCmdPar::OneCmdSer()
{
   return mOneCmdSer;
}

const std::list< std::string > & cOneCmdPar::OneCmdSer()const 
{
   return mOneCmdSer;
}

cElXMLTree * ToXMLTree(const cOneCmdPar & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"OneCmdPar",eXMLBranche);
  for
  (       std::list< std::string >::const_iterator it=anObj.OneCmdSer().begin();
      it !=anObj.OneCmdSer().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("OneCmdSer"),(*it))->ReTagThis("OneCmdSer"));
  return aRes;
}

void xml_init(cOneCmdPar & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.OneCmdSer(),aTree->GetAll("OneCmdSer",false,1));
}


cTplValGesInit< std::string > & cCmdExePar::NameMkF()
{
   return mNameMkF;
}

const cTplValGesInit< std::string > & cCmdExePar::NameMkF()const 
{
   return mNameMkF;
}


std::list< cOneCmdPar > & cCmdExePar::OneCmdPar()
{
   return mOneCmdPar;
}

const std::list< cOneCmdPar > & cCmdExePar::OneCmdPar()const 
{
   return mOneCmdPar;
}

cElXMLTree * ToXMLTree(const cCmdExePar & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CmdExePar",eXMLBranche);
   if (anObj.NameMkF().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NameMkF"),anObj.NameMkF().Val())->ReTagThis("NameMkF"));
  for
  (       std::list< cOneCmdPar >::const_iterator it=anObj.OneCmdPar().begin();
      it !=anObj.OneCmdPar().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("OneCmdPar"));
  return aRes;
}

void xml_init(cCmdExePar & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NameMkF(),aTree->Get("NameMkF",1),std::string("Make_CmdExePar")); //tototo 

   xml_init(anObj.OneCmdPar(),aTree->GetAll("OneCmdPar",false,1));
}


std::string & cPt3drEntries::Key()
{
   return mKey;
}

const std::string & cPt3drEntries::Key()const 
{
   return mKey;
}


Pt3dr & cPt3drEntries::Val()
{
   return mVal;
}

const Pt3dr & cPt3drEntries::Val()const 
{
   return mVal;
}

cElXMLTree * ToXMLTree(const cPt3drEntries & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"Pt3drEntries",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Key"),anObj.Key())->ReTagThis("Key"));
   aRes->AddFils(ToXMLTree(std::string("Val"),anObj.Val())->ReTagThis("Val"));
  return aRes;
}

void xml_init(cPt3drEntries & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Key(),aTree->Get("Key",1)); //tototo 

   xml_init(anObj.Val(),aTree->Get("Val",1)); //tototo 
}


std::string & cBasesPt3dr::NameBase()
{
   return mNameBase;
}

const std::string & cBasesPt3dr::NameBase()const 
{
   return mNameBase;
}


std::list< cPt3drEntries > & cBasesPt3dr::Pt3drEntries()
{
   return mPt3drEntries;
}

const std::list< cPt3drEntries > & cBasesPt3dr::Pt3drEntries()const 
{
   return mPt3drEntries;
}

cElXMLTree * ToXMLTree(const cBasesPt3dr & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"BasesPt3dr",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("NameBase"),anObj.NameBase())->ReTagThis("NameBase"));
  for
  (       std::list< cPt3drEntries >::const_iterator it=anObj.Pt3drEntries().begin();
      it !=anObj.Pt3drEntries().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("Pt3drEntries"));
  return aRes;
}

void xml_init(cBasesPt3dr & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NameBase(),aTree->Get("NameBase",1)); //tototo 

   xml_init(anObj.Pt3drEntries(),aTree->GetAll("Pt3drEntries",false,1));
}


std::string & cScalEntries::Key()
{
   return mKey;
}

const std::string & cScalEntries::Key()const 
{
   return mKey;
}


double & cScalEntries::Val()
{
   return mVal;
}

const double & cScalEntries::Val()const 
{
   return mVal;
}

cElXMLTree * ToXMLTree(const cScalEntries & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ScalEntries",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Key"),anObj.Key())->ReTagThis("Key"));
   aRes->AddFils(::ToXMLTree(std::string("Val"),anObj.Val())->ReTagThis("Val"));
  return aRes;
}

void xml_init(cScalEntries & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Key(),aTree->Get("Key",1)); //tototo 

   xml_init(anObj.Val(),aTree->Get("Val",1)); //tototo 
}


std::string & cBasesScal::NameBase()
{
   return mNameBase;
}

const std::string & cBasesScal::NameBase()const 
{
   return mNameBase;
}


std::list< cScalEntries > & cBasesScal::ScalEntries()
{
   return mScalEntries;
}

const std::list< cScalEntries > & cBasesScal::ScalEntries()const 
{
   return mScalEntries;
}

cElXMLTree * ToXMLTree(const cBasesScal & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"BasesScal",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("NameBase"),anObj.NameBase())->ReTagThis("NameBase"));
  for
  (       std::list< cScalEntries >::const_iterator it=anObj.ScalEntries().begin();
      it !=anObj.ScalEntries().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("ScalEntries"));
  return aRes;
}

void xml_init(cBasesScal & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NameBase(),aTree->Get("NameBase",1)); //tototo 

   xml_init(anObj.ScalEntries(),aTree->GetAll("ScalEntries",false,1));
}


std::list< cBasesPt3dr > & cBaseDataCD::BasesPt3dr()
{
   return mBasesPt3dr;
}

const std::list< cBasesPt3dr > & cBaseDataCD::BasesPt3dr()const 
{
   return mBasesPt3dr;
}


std::list< cBasesScal > & cBaseDataCD::BasesScal()
{
   return mBasesScal;
}

const std::list< cBasesScal > & cBaseDataCD::BasesScal()const 
{
   return mBasesScal;
}

cElXMLTree * ToXMLTree(const cBaseDataCD & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"BaseDataCD",eXMLBranche);
  for
  (       std::list< cBasesPt3dr >::const_iterator it=anObj.BasesPt3dr().begin();
      it !=anObj.BasesPt3dr().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("BasesPt3dr"));
  for
  (       std::list< cBasesScal >::const_iterator it=anObj.BasesScal().begin();
      it !=anObj.BasesScal().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("BasesScal"));
  return aRes;
}

void xml_init(cBaseDataCD & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.BasesPt3dr(),aTree->GetAll("BasesPt3dr",false,1));

   xml_init(anObj.BasesScal(),aTree->GetAll("BasesScal",false,1));
}


std::string & cParamVolChantierPhotogram::Directory()
{
   return mDirectory;
}

const std::string & cParamVolChantierPhotogram::Directory()const 
{
   return mDirectory;
}


cTplValGesInit< std::string > & cParamVolChantierPhotogram::DirOrientations()
{
   return mDirOrientations;
}

const cTplValGesInit< std::string > & cParamVolChantierPhotogram::DirOrientations()const 
{
   return mDirOrientations;
}


cElRegex_Ptr & cParamVolChantierPhotogram::NameSelector()
{
   return mNameSelector;
}

const cElRegex_Ptr & cParamVolChantierPhotogram::NameSelector()const 
{
   return mNameSelector;
}


cElRegex_Ptr & cParamVolChantierPhotogram::BandeIdSelector()
{
   return mBandeIdSelector;
}

const cElRegex_Ptr & cParamVolChantierPhotogram::BandeIdSelector()const 
{
   return mBandeIdSelector;
}


std::string & cParamVolChantierPhotogram::NomBandeId()
{
   return mNomBandeId;
}

const std::string & cParamVolChantierPhotogram::NomBandeId()const 
{
   return mNomBandeId;
}


std::string & cParamVolChantierPhotogram::NomIdInBande()
{
   return mNomIdInBande;
}

const std::string & cParamVolChantierPhotogram::NomIdInBande()const 
{
   return mNomIdInBande;
}


std::string & cParamVolChantierPhotogram::NomImage()
{
   return mNomImage;
}

const std::string & cParamVolChantierPhotogram::NomImage()const 
{
   return mNomImage;
}


cTplValGesInit< std::string > & cParamVolChantierPhotogram::DirImages()
{
   return mDirImages;
}

const cTplValGesInit< std::string > & cParamVolChantierPhotogram::DirImages()const 
{
   return mDirImages;
}

cElXMLTree * ToXMLTree(const cParamVolChantierPhotogram & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ParamVolChantierPhotogram",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Directory"),anObj.Directory())->ReTagThis("Directory"));
   if (anObj.DirOrientations().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("DirOrientations"),anObj.DirOrientations().Val())->ReTagThis("DirOrientations"));
   aRes->AddFils(::ToXMLTree(std::string("NameSelector"),anObj.NameSelector())->ReTagThis("NameSelector"));
   aRes->AddFils(::ToXMLTree(std::string("BandeIdSelector"),anObj.BandeIdSelector())->ReTagThis("BandeIdSelector"));
   aRes->AddFils(::ToXMLTree(std::string("NomBandeId"),anObj.NomBandeId())->ReTagThis("NomBandeId"));
   aRes->AddFils(::ToXMLTree(std::string("NomIdInBande"),anObj.NomIdInBande())->ReTagThis("NomIdInBande"));
   aRes->AddFils(::ToXMLTree(std::string("NomImage"),anObj.NomImage())->ReTagThis("NomImage"));
   if (anObj.DirImages().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("DirImages"),anObj.DirImages().Val())->ReTagThis("DirImages"));
  return aRes;
}

void xml_init(cParamVolChantierPhotogram & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Directory(),aTree->Get("Directory",1)); //tototo 

   xml_init(anObj.DirOrientations(),aTree->Get("DirOrientations",1),std::string("")); //tototo 

   xml_init(anObj.NameSelector(),aTree->Get("NameSelector",1)); //tototo 

   xml_init(anObj.BandeIdSelector(),aTree->Get("BandeIdSelector",1)); //tototo 

   xml_init(anObj.NomBandeId(),aTree->Get("NomBandeId",1)); //tototo 

   xml_init(anObj.NomIdInBande(),aTree->Get("NomIdInBande",1)); //tototo 

   xml_init(anObj.NomImage(),aTree->Get("NomImage",1)); //tototo 

   xml_init(anObj.DirImages(),aTree->Get("DirImages",1),std::string("")); //tototo 
}


std::list< cParamVolChantierPhotogram > & cParamChantierPhotogram::ParamVolChantierPhotogram()
{
   return mParamVolChantierPhotogram;
}

const std::list< cParamVolChantierPhotogram > & cParamChantierPhotogram::ParamVolChantierPhotogram()const 
{
   return mParamVolChantierPhotogram;
}

cElXMLTree * ToXMLTree(const cParamChantierPhotogram & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ParamChantierPhotogram",eXMLBranche);
  for
  (       std::list< cParamVolChantierPhotogram >::const_iterator it=anObj.ParamVolChantierPhotogram().begin();
      it !=anObj.ParamVolChantierPhotogram().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("ParamVolChantierPhotogram"));
  return aRes;
}

void xml_init(cParamChantierPhotogram & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.ParamVolChantierPhotogram(),aTree->GetAll("ParamVolChantierPhotogram",false,1));
}


std::string & cPDV::Im()
{
   return mIm;
}

const std::string & cPDV::Im()const 
{
   return mIm;
}


std::string & cPDV::Orient()
{
   return mOrient;
}

const std::string & cPDV::Orient()const 
{
   return mOrient;
}


std::string & cPDV::IdInBande()
{
   return mIdInBande;
}

const std::string & cPDV::IdInBande()const 
{
   return mIdInBande;
}


std::string & cPDV::Bande()
{
   return mBande;
}

const std::string & cPDV::Bande()const 
{
   return mBande;
}

cElXMLTree * ToXMLTree(const cPDV & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"PDV",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Im"),anObj.Im())->ReTagThis("Im"));
   aRes->AddFils(::ToXMLTree(std::string("Orient"),anObj.Orient())->ReTagThis("Orient"));
   aRes->AddFils(::ToXMLTree(std::string("IdInBande"),anObj.IdInBande())->ReTagThis("IdInBande"));
   aRes->AddFils(::ToXMLTree(std::string("Bande"),anObj.Bande())->ReTagThis("Bande"));
  return aRes;
}

void xml_init(cPDV & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Im(),aTree->Get("Im",1)); //tototo 

   xml_init(anObj.Orient(),aTree->Get("Orient",1)); //tototo 

   xml_init(anObj.IdInBande(),aTree->Get("IdInBande",1)); //tototo 

   xml_init(anObj.Bande(),aTree->Get("Bande",1)); //tototo 
}


std::string & cBandesChantierPhotogram::IdBande()
{
   return mIdBande;
}

const std::string & cBandesChantierPhotogram::IdBande()const 
{
   return mIdBande;
}


std::list< cPDV > & cBandesChantierPhotogram::PDVs()
{
   return mPDVs;
}

const std::list< cPDV > & cBandesChantierPhotogram::PDVs()const 
{
   return mPDVs;
}

cElXMLTree * ToXMLTree(const cBandesChantierPhotogram & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"BandesChantierPhotogram",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("IdBande"),anObj.IdBande())->ReTagThis("IdBande"));
  for
  (       std::list< cPDV >::const_iterator it=anObj.PDVs().begin();
      it !=anObj.PDVs().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("PDVs"));
  return aRes;
}

void xml_init(cBandesChantierPhotogram & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.IdBande(),aTree->Get("IdBande",1)); //tototo 

   xml_init(anObj.PDVs(),aTree->GetAll("PDVs",false,1));
}


std::list< cBandesChantierPhotogram > & cVolChantierPhotogram::BandesChantierPhotogram()
{
   return mBandesChantierPhotogram;
}

const std::list< cBandesChantierPhotogram > & cVolChantierPhotogram::BandesChantierPhotogram()const 
{
   return mBandesChantierPhotogram;
}

cElXMLTree * ToXMLTree(const cVolChantierPhotogram & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"VolChantierPhotogram",eXMLBranche);
  for
  (       std::list< cBandesChantierPhotogram >::const_iterator it=anObj.BandesChantierPhotogram().begin();
      it !=anObj.BandesChantierPhotogram().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("BandesChantierPhotogram"));
  return aRes;
}

void xml_init(cVolChantierPhotogram & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.BandesChantierPhotogram(),aTree->GetAll("BandesChantierPhotogram",false,1));
}


std::list< cVolChantierPhotogram > & cChantierPhotogram::VolChantierPhotogram()
{
   return mVolChantierPhotogram;
}

const std::list< cVolChantierPhotogram > & cChantierPhotogram::VolChantierPhotogram()const 
{
   return mVolChantierPhotogram;
}

cElXMLTree * ToXMLTree(const cChantierPhotogram & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ChantierPhotogram",eXMLBranche);
  for
  (       std::list< cVolChantierPhotogram >::const_iterator it=anObj.VolChantierPhotogram().begin();
      it !=anObj.VolChantierPhotogram().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("VolChantierPhotogram"));
  return aRes;
}

void xml_init(cChantierPhotogram & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.VolChantierPhotogram(),aTree->GetAll("VolChantierPhotogram",false,1));
}


int & cCplePDV::Id1()
{
   return mId1;
}

const int & cCplePDV::Id1()const 
{
   return mId1;
}


int & cCplePDV::Id2()
{
   return mId2;
}

const int & cCplePDV::Id2()const 
{
   return mId2;
}

cElXMLTree * ToXMLTree(const cCplePDV & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CplePDV",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Id1"),anObj.Id1())->ReTagThis("Id1"));
   aRes->AddFils(::ToXMLTree(std::string("Id2"),anObj.Id2())->ReTagThis("Id2"));
  return aRes;
}

void xml_init(cCplePDV & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Id1(),aTree->Get("Id1",1)); //tototo 

   xml_init(anObj.Id2(),aTree->Get("Id2",1)); //tototo 
}


Box2dr & cGraphePdv::BoxCh()
{
   return mBoxCh;
}

const Box2dr & cGraphePdv::BoxCh()const 
{
   return mBoxCh;
}


std::vector< cPDV > & cGraphePdv::PDVs()
{
   return mPDVs;
}

const std::vector< cPDV > & cGraphePdv::PDVs()const 
{
   return mPDVs;
}


std::list< cCplePDV > & cGraphePdv::CplePDV()
{
   return mCplePDV;
}

const std::list< cCplePDV > & cGraphePdv::CplePDV()const 
{
   return mCplePDV;
}

cElXMLTree * ToXMLTree(const cGraphePdv & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"GraphePdv",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("BoxCh"),anObj.BoxCh())->ReTagThis("BoxCh"));
  for
  (       std::vector< cPDV >::const_iterator it=anObj.PDVs().begin();
      it !=anObj.PDVs().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("PDVs"));
  for
  (       std::list< cCplePDV >::const_iterator it=anObj.CplePDV().begin();
      it !=anObj.CplePDV().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("CplePDV"));
  return aRes;
}

void xml_init(cGraphePdv & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.BoxCh(),aTree->Get("BoxCh",1)); //tototo 

   xml_init(anObj.PDVs(),aTree->GetAll("PDVs",false,1));

   xml_init(anObj.CplePDV(),aTree->GetAll("CplePDV",false,1));
}


double & cCercleRelief::Rayon()
{
   return mRayon;
}

const double & cCercleRelief::Rayon()const 
{
   return mRayon;
}


double & cCercleRelief::Profondeur()
{
   return mProfondeur;
}

const double & cCercleRelief::Profondeur()const 
{
   return mProfondeur;
}

cElXMLTree * ToXMLTree(const cCercleRelief & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CercleRelief",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Rayon"),anObj.Rayon())->ReTagThis("Rayon"));
   aRes->AddFils(::ToXMLTree(std::string("Profondeur"),anObj.Profondeur())->ReTagThis("Profondeur"));
  return aRes;
}

void xml_init(cCercleRelief & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Rayon(),aTree->Get("Rayon",1)); //tototo 

   xml_init(anObj.Profondeur(),aTree->Get("Profondeur",1)); //tototo 
}


int & cCibleCalib::Id()
{
   return mId;
}

const int & cCibleCalib::Id()const 
{
   return mId;
}


cTplValGesInit< bool > & cCibleCalib::Negatif()
{
   return mNegatif;
}

const cTplValGesInit< bool > & cCibleCalib::Negatif()const 
{
   return mNegatif;
}


Pt3dr & cCibleCalib::Position()
{
   return mPosition;
}

const Pt3dr & cCibleCalib::Position()const 
{
   return mPosition;
}


Pt3dr & cCibleCalib::Normale()
{
   return mNormale;
}

const Pt3dr & cCibleCalib::Normale()const 
{
   return mNormale;
}


std::vector< double > & cCibleCalib::Rayons()
{
   return mRayons;
}

const std::vector< double > & cCibleCalib::Rayons()const 
{
   return mRayons;
}


bool & cCibleCalib::Ponctuel()
{
   return mPonctuel;
}

const bool & cCibleCalib::Ponctuel()const 
{
   return mPonctuel;
}


bool & cCibleCalib::ReliefIsSortant()
{
   return mReliefIsSortant;
}

const bool & cCibleCalib::ReliefIsSortant()const 
{
   return mReliefIsSortant;
}


std::vector< cCercleRelief > & cCibleCalib::CercleRelief()
{
   return mCercleRelief;
}

const std::vector< cCercleRelief > & cCibleCalib::CercleRelief()const 
{
   return mCercleRelief;
}


std::string & cCibleCalib::NomType()
{
   return mNomType;
}

const std::string & cCibleCalib::NomType()const 
{
   return mNomType;
}


int & cCibleCalib::Qualite()
{
   return mQualite;
}

const int & cCibleCalib::Qualite()const 
{
   return mQualite;
}


cTplValGesInit< double > & cCibleCalib::FacteurElargRechCorrel()
{
   return mFacteurElargRechCorrel;
}

const cTplValGesInit< double > & cCibleCalib::FacteurElargRechCorrel()const 
{
   return mFacteurElargRechCorrel;
}


cTplValGesInit< double > & cCibleCalib::FacteurElargRechRaffine()
{
   return mFacteurElargRechRaffine;
}

const cTplValGesInit< double > & cCibleCalib::FacteurElargRechRaffine()const 
{
   return mFacteurElargRechRaffine;
}

cElXMLTree * ToXMLTree(const cCibleCalib & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CibleCalib",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Id"),anObj.Id())->ReTagThis("Id"));
   if (anObj.Negatif().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Negatif"),anObj.Negatif().Val())->ReTagThis("Negatif"));
   aRes->AddFils(ToXMLTree(std::string("Position"),anObj.Position())->ReTagThis("Position"));
   aRes->AddFils(ToXMLTree(std::string("Normale"),anObj.Normale())->ReTagThis("Normale"));
  for
  (       std::vector< double >::const_iterator it=anObj.Rayons().begin();
      it !=anObj.Rayons().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Rayons"),(*it))->ReTagThis("Rayons"));
   aRes->AddFils(::ToXMLTree(std::string("Ponctuel"),anObj.Ponctuel())->ReTagThis("Ponctuel"));
   aRes->AddFils(::ToXMLTree(std::string("ReliefIsSortant"),anObj.ReliefIsSortant())->ReTagThis("ReliefIsSortant"));
  for
  (       std::vector< cCercleRelief >::const_iterator it=anObj.CercleRelief().begin();
      it !=anObj.CercleRelief().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("CercleRelief"));
   aRes->AddFils(::ToXMLTree(std::string("NomType"),anObj.NomType())->ReTagThis("NomType"));
   aRes->AddFils(::ToXMLTree(std::string("Qualite"),anObj.Qualite())->ReTagThis("Qualite"));
   if (anObj.FacteurElargRechCorrel().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("FacteurElargRechCorrel"),anObj.FacteurElargRechCorrel().Val())->ReTagThis("FacteurElargRechCorrel"));
   if (anObj.FacteurElargRechRaffine().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("FacteurElargRechRaffine"),anObj.FacteurElargRechRaffine().Val())->ReTagThis("FacteurElargRechRaffine"));
  return aRes;
}

void xml_init(cCibleCalib & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Id(),aTree->Get("Id",1)); //tototo 

   xml_init(anObj.Negatif(),aTree->Get("Negatif",1),bool(false)); //tototo 

   xml_init(anObj.Position(),aTree->Get("Position",1)); //tototo 

   xml_init(anObj.Normale(),aTree->Get("Normale",1)); //tototo 

   xml_init(anObj.Rayons(),aTree->GetAll("Rayons",false,1));

   xml_init(anObj.Ponctuel(),aTree->Get("Ponctuel",1)); //tototo 

   xml_init(anObj.ReliefIsSortant(),aTree->Get("ReliefIsSortant",1)); //tototo 

   xml_init(anObj.CercleRelief(),aTree->GetAll("CercleRelief",false,1));

   xml_init(anObj.NomType(),aTree->Get("NomType",1)); //tototo 

   xml_init(anObj.Qualite(),aTree->Get("Qualite",1)); //tototo 

   xml_init(anObj.FacteurElargRechCorrel(),aTree->Get("FacteurElargRechCorrel",1)); //tototo 

   xml_init(anObj.FacteurElargRechRaffine(),aTree->Get("FacteurElargRechRaffine",1)); //tototo 
}


std::string & cPolygoneCalib::Name()
{
   return mName;
}

const std::string & cPolygoneCalib::Name()const 
{
   return mName;
}


std::vector< cCibleCalib > & cPolygoneCalib::Cibles()
{
   return mCibles;
}

const std::vector< cCibleCalib > & cPolygoneCalib::Cibles()const 
{
   return mCibles;
}

cElXMLTree * ToXMLTree(const cPolygoneCalib & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"PolygoneCalib",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Name"),anObj.Name())->ReTagThis("Name"));
  for
  (       std::vector< cCibleCalib >::const_iterator it=anObj.Cibles().begin();
      it !=anObj.Cibles().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("Cibles"));
  return aRes;
}

void xml_init(cPolygoneCalib & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Name(),aTree->Get("Name",1)); //tototo 

   xml_init(anObj.Cibles(),aTree->GetAll("Cibles",false,1));
}


std::string & cPointesCibleAC::NameIm()
{
   return mNameIm;
}

const std::string & cPointesCibleAC::NameIm()const 
{
   return mNameIm;
}


Pt2dr & cPointesCibleAC::PtIm()
{
   return mPtIm;
}

const Pt2dr & cPointesCibleAC::PtIm()const 
{
   return mPtIm;
}

cElXMLTree * ToXMLTree(const cPointesCibleAC & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"PointesCibleAC",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("NameIm"),anObj.NameIm())->ReTagThis("NameIm"));
   aRes->AddFils(::ToXMLTree(std::string("PtIm"),anObj.PtIm())->ReTagThis("PtIm"));
  return aRes;
}

void xml_init(cPointesCibleAC & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NameIm(),aTree->Get("NameIm",1)); //tototo 

   xml_init(anObj.PtIm(),aTree->Get("PtIm",1)); //tototo 
}


std::string & cCibleACalcByLiaisons::Name()
{
   return mName;
}

const std::string & cCibleACalcByLiaisons::Name()const 
{
   return mName;
}


std::list< cPointesCibleAC > & cCibleACalcByLiaisons::PointesCibleAC()
{
   return mPointesCibleAC;
}

const std::list< cPointesCibleAC > & cCibleACalcByLiaisons::PointesCibleAC()const 
{
   return mPointesCibleAC;
}

cElXMLTree * ToXMLTree(const cCibleACalcByLiaisons & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CibleACalcByLiaisons",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Name"),anObj.Name())->ReTagThis("Name"));
  for
  (       std::list< cPointesCibleAC >::const_iterator it=anObj.PointesCibleAC().begin();
      it !=anObj.PointesCibleAC().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("PointesCibleAC"));
  return aRes;
}

void xml_init(cCibleACalcByLiaisons & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Name(),aTree->Get("Name",1)); //tototo 

   xml_init(anObj.PointesCibleAC(),aTree->GetAll("PointesCibleAC",false,1));
}


cTplValGesInit< bool > & cCible2Rech::UseIt()
{
   return mUseIt;
}

const cTplValGesInit< bool > & cCible2Rech::UseIt()const 
{
   return mUseIt;
}


std::vector< int > & cCible2Rech::Id()
{
   return mId;
}

const std::vector< int > & cCible2Rech::Id()const 
{
   return mId;
}

cElXMLTree * ToXMLTree(const cCible2Rech & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"Cible2Rech",eXMLBranche);
   if (anObj.UseIt().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("UseIt"),anObj.UseIt().Val())->ReTagThis("UseIt"));
  for
  (       std::vector< int >::const_iterator it=anObj.Id().begin();
      it !=anObj.Id().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Id"),(*it))->ReTagThis("Id"));
  return aRes;
}

void xml_init(cCible2Rech & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.UseIt(),aTree->Get("UseIt",1),bool(false)); //tototo 

   xml_init(anObj.Id(),aTree->GetAll("Id",false,1));
}


cTplValGesInit< bool > & cIm2Select::UseIt()
{
   return mUseIt;
}

const cTplValGesInit< bool > & cIm2Select::UseIt()const 
{
   return mUseIt;
}


std::vector< std::string > & cIm2Select::Id()
{
   return mId;
}

const std::vector< std::string > & cIm2Select::Id()const 
{
   return mId;
}

cElXMLTree * ToXMLTree(const cIm2Select & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"Im2Select",eXMLBranche);
   if (anObj.UseIt().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("UseIt"),anObj.UseIt().Val())->ReTagThis("UseIt"));
  for
  (       std::vector< std::string >::const_iterator it=anObj.Id().begin();
      it !=anObj.Id().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Id"),(*it))->ReTagThis("Id"));
  return aRes;
}

void xml_init(cIm2Select & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.UseIt(),aTree->Get("UseIt",1),bool(false)); //tototo 

   xml_init(anObj.Id(),aTree->GetAll("Id",false,1));
}


std::list< cElRegex_Ptr > & cImageUseDirectPointeManuel::Id()
{
   return mId;
}

const std::list< cElRegex_Ptr > & cImageUseDirectPointeManuel::Id()const 
{
   return mId;
}

cElXMLTree * ToXMLTree(const cImageUseDirectPointeManuel & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ImageUseDirectPointeManuel",eXMLBranche);
  for
  (       std::list< cElRegex_Ptr >::const_iterator it=anObj.Id().begin();
      it !=anObj.Id().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Id"),(*it))->ReTagThis("Id"));
  return aRes;
}

void xml_init(cImageUseDirectPointeManuel & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Id(),aTree->GetAll("Id",false,1));
}


std::string & cExportAppuisAsDico::NameDico()
{
   return mNameDico;
}

const std::string & cExportAppuisAsDico::NameDico()const 
{
   return mNameDico;
}


Pt3dr & cExportAppuisAsDico::Incertitude()
{
   return mIncertitude;
}

const Pt3dr & cExportAppuisAsDico::Incertitude()const 
{
   return mIncertitude;
}

cElXMLTree * ToXMLTree(const cExportAppuisAsDico & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ExportAppuisAsDico",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("NameDico"),anObj.NameDico())->ReTagThis("NameDico"));
   aRes->AddFils(ToXMLTree(std::string("Incertitude"),anObj.Incertitude())->ReTagThis("Incertitude"));
  return aRes;
}

void xml_init(cExportAppuisAsDico & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NameDico(),aTree->Get("NameDico",1)); //tototo 

   xml_init(anObj.Incertitude(),aTree->Get("Incertitude",1)); //tototo 
}


std::list< cCibleACalcByLiaisons > & cComplParamEtalPoly::CibleACalcByLiaisons()
{
   return mCibleACalcByLiaisons;
}

const std::list< cCibleACalcByLiaisons > & cComplParamEtalPoly::CibleACalcByLiaisons()const 
{
   return mCibleACalcByLiaisons;
}


cTplValGesInit< cCible2Rech > & cComplParamEtalPoly::Cible2Rech()
{
   return mCible2Rech;
}

const cTplValGesInit< cCible2Rech > & cComplParamEtalPoly::Cible2Rech()const 
{
   return mCible2Rech;
}


cTplValGesInit< cIm2Select > & cComplParamEtalPoly::Im2Select()
{
   return mIm2Select;
}

const cTplValGesInit< cIm2Select > & cComplParamEtalPoly::Im2Select()const 
{
   return mIm2Select;
}


cTplValGesInit< cImageUseDirectPointeManuel > & cComplParamEtalPoly::ImageUseDirectPointeManuel()
{
   return mImageUseDirectPointeManuel;
}

const cTplValGesInit< cImageUseDirectPointeManuel > & cComplParamEtalPoly::ImageUseDirectPointeManuel()const 
{
   return mImageUseDirectPointeManuel;
}


std::string & cComplParamEtalPoly::NameDico()
{
   return ExportAppuisAsDico().Val().NameDico();
}

const std::string & cComplParamEtalPoly::NameDico()const 
{
   return ExportAppuisAsDico().Val().NameDico();
}


Pt3dr & cComplParamEtalPoly::Incertitude()
{
   return ExportAppuisAsDico().Val().Incertitude();
}

const Pt3dr & cComplParamEtalPoly::Incertitude()const 
{
   return ExportAppuisAsDico().Val().Incertitude();
}


cTplValGesInit< cExportAppuisAsDico > & cComplParamEtalPoly::ExportAppuisAsDico()
{
   return mExportAppuisAsDico;
}

const cTplValGesInit< cExportAppuisAsDico > & cComplParamEtalPoly::ExportAppuisAsDico()const 
{
   return mExportAppuisAsDico;
}

cElXMLTree * ToXMLTree(const cComplParamEtalPoly & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ComplParamEtalPoly",eXMLBranche);
  for
  (       std::list< cCibleACalcByLiaisons >::const_iterator it=anObj.CibleACalcByLiaisons().begin();
      it !=anObj.CibleACalcByLiaisons().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("CibleACalcByLiaisons"));
   if (anObj.Cible2Rech().IsInit())
      aRes->AddFils(ToXMLTree(anObj.Cible2Rech().Val())->ReTagThis("Cible2Rech"));
   if (anObj.Im2Select().IsInit())
      aRes->AddFils(ToXMLTree(anObj.Im2Select().Val())->ReTagThis("Im2Select"));
   if (anObj.ImageUseDirectPointeManuel().IsInit())
      aRes->AddFils(ToXMLTree(anObj.ImageUseDirectPointeManuel().Val())->ReTagThis("ImageUseDirectPointeManuel"));
   if (anObj.ExportAppuisAsDico().IsInit())
      aRes->AddFils(ToXMLTree(anObj.ExportAppuisAsDico().Val())->ReTagThis("ExportAppuisAsDico"));
  return aRes;
}

void xml_init(cComplParamEtalPoly & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.CibleACalcByLiaisons(),aTree->GetAll("CibleACalcByLiaisons",false,1));

   xml_init(anObj.Cible2Rech(),aTree->Get("Cible2Rech",1)); //tototo 

   xml_init(anObj.Im2Select(),aTree->Get("Im2Select",1)); //tototo 

   xml_init(anObj.ImageUseDirectPointeManuel(),aTree->Get("ImageUseDirectPointeManuel",1)); //tototo 

   xml_init(anObj.ExportAppuisAsDico(),aTree->Get("ExportAppuisAsDico",1)); //tototo 
}


Pt3dr & cOneAppuisDAF::Pt()
{
   return mPt;
}

const Pt3dr & cOneAppuisDAF::Pt()const 
{
   return mPt;
}


std::string & cOneAppuisDAF::NamePt()
{
   return mNamePt;
}

const std::string & cOneAppuisDAF::NamePt()const 
{
   return mNamePt;
}


Pt3dr & cOneAppuisDAF::Incertitude()
{
   return mIncertitude;
}

const Pt3dr & cOneAppuisDAF::Incertitude()const 
{
   return mIncertitude;
}

cElXMLTree * ToXMLTree(const cOneAppuisDAF & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"OneAppuisDAF",eXMLBranche);
   aRes->AddFils(ToXMLTree(std::string("Pt"),anObj.Pt())->ReTagThis("Pt"));
   aRes->AddFils(::ToXMLTree(std::string("NamePt"),anObj.NamePt())->ReTagThis("NamePt"));
   aRes->AddFils(ToXMLTree(std::string("Incertitude"),anObj.Incertitude())->ReTagThis("Incertitude"));
  return aRes;
}

void xml_init(cOneAppuisDAF & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Pt(),aTree->Get("Pt",1)); //tototo 

   xml_init(anObj.NamePt(),aTree->Get("NamePt",1)); //tototo 

   xml_init(anObj.Incertitude(),aTree->Get("Incertitude",1)); //tototo 
}


std::list< cOneAppuisDAF > & cDicoAppuisFlottant::OneAppuisDAF()
{
   return mOneAppuisDAF;
}

const std::list< cOneAppuisDAF > & cDicoAppuisFlottant::OneAppuisDAF()const 
{
   return mOneAppuisDAF;
}

cElXMLTree * ToXMLTree(const cDicoAppuisFlottant & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"DicoAppuisFlottant",eXMLBranche);
  for
  (       std::list< cOneAppuisDAF >::const_iterator it=anObj.OneAppuisDAF().begin();
      it !=anObj.OneAppuisDAF().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("OneAppuisDAF"));
  return aRes;
}

void xml_init(cDicoAppuisFlottant & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.OneAppuisDAF(),aTree->GetAll("OneAppuisDAF",false,1));
}


std::string & cOneModifIPF::KeyName()
{
   return mKeyName;
}

const std::string & cOneModifIPF::KeyName()const 
{
   return mKeyName;
}


Pt3dr & cOneModifIPF::Incertitude()
{
   return mIncertitude;
}

const Pt3dr & cOneModifIPF::Incertitude()const 
{
   return mIncertitude;
}


cTplValGesInit< bool > & cOneModifIPF::IsMult()
{
   return mIsMult;
}

const cTplValGesInit< bool > & cOneModifIPF::IsMult()const 
{
   return mIsMult;
}

cElXMLTree * ToXMLTree(const cOneModifIPF & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"OneModifIPF",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("KeyName"),anObj.KeyName())->ReTagThis("KeyName"));
   aRes->AddFils(ToXMLTree(std::string("Incertitude"),anObj.Incertitude())->ReTagThis("Incertitude"));
   if (anObj.IsMult().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("IsMult"),anObj.IsMult().Val())->ReTagThis("IsMult"));
  return aRes;
}

void xml_init(cOneModifIPF & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeyName(),aTree->Get("KeyName",1)); //tototo 

   xml_init(anObj.Incertitude(),aTree->Get("Incertitude",1)); //tototo 

   xml_init(anObj.IsMult(),aTree->Get("IsMult",1),bool(false)); //tototo 
}


std::list< cOneModifIPF > & cModifIncPtsFlottant::OneModifIPF()
{
   return mOneModifIPF;
}

const std::list< cOneModifIPF > & cModifIncPtsFlottant::OneModifIPF()const 
{
   return mOneModifIPF;
}

cElXMLTree * ToXMLTree(const cModifIncPtsFlottant & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ModifIncPtsFlottant",eXMLBranche);
  for
  (       std::list< cOneModifIPF >::const_iterator it=anObj.OneModifIPF().begin();
      it !=anObj.OneModifIPF().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("OneModifIPF"));
  return aRes;
}

void xml_init(cModifIncPtsFlottant & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.OneModifIPF(),aTree->GetAll("OneModifIPF",false,1));
}


std::string & cOneMesureAF1I::NamePt()
{
   return mNamePt;
}

const std::string & cOneMesureAF1I::NamePt()const 
{
   return mNamePt;
}


Pt2dr & cOneMesureAF1I::PtIm()
{
   return mPtIm;
}

const Pt2dr & cOneMesureAF1I::PtIm()const 
{
   return mPtIm;
}

cElXMLTree * ToXMLTree(const cOneMesureAF1I & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"OneMesureAF1I",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("NamePt"),anObj.NamePt())->ReTagThis("NamePt"));
   aRes->AddFils(::ToXMLTree(std::string("PtIm"),anObj.PtIm())->ReTagThis("PtIm"));
  return aRes;
}

void xml_init(cOneMesureAF1I & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NamePt(),aTree->Get("NamePt",1)); //tototo 

   xml_init(anObj.PtIm(),aTree->Get("PtIm",1)); //tototo 
}


std::string & cMesureAppuiFlottant1Im::NameIm()
{
   return mNameIm;
}

const std::string & cMesureAppuiFlottant1Im::NameIm()const 
{
   return mNameIm;
}


std::list< cOneMesureAF1I > & cMesureAppuiFlottant1Im::OneMesureAF1I()
{
   return mOneMesureAF1I;
}

const std::list< cOneMesureAF1I > & cMesureAppuiFlottant1Im::OneMesureAF1I()const 
{
   return mOneMesureAF1I;
}

cElXMLTree * ToXMLTree(const cMesureAppuiFlottant1Im & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"MesureAppuiFlottant1Im",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("NameIm"),anObj.NameIm())->ReTagThis("NameIm"));
  for
  (       std::list< cOneMesureAF1I >::const_iterator it=anObj.OneMesureAF1I().begin();
      it !=anObj.OneMesureAF1I().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("OneMesureAF1I"));
  return aRes;
}

void xml_init(cMesureAppuiFlottant1Im & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NameIm(),aTree->Get("NameIm",1)); //tototo 

   xml_init(anObj.OneMesureAF1I(),aTree->GetAll("OneMesureAF1I",false,1));
}


std::list< cMesureAppuiFlottant1Im > & cSetOfMesureAppuisFlottants::MesureAppuiFlottant1Im()
{
   return mMesureAppuiFlottant1Im;
}

const std::list< cMesureAppuiFlottant1Im > & cSetOfMesureAppuisFlottants::MesureAppuiFlottant1Im()const 
{
   return mMesureAppuiFlottant1Im;
}

cElXMLTree * ToXMLTree(const cSetOfMesureAppuisFlottants & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"SetOfMesureAppuisFlottants",eXMLBranche);
  for
  (       std::list< cMesureAppuiFlottant1Im >::const_iterator it=anObj.MesureAppuiFlottant1Im().begin();
      it !=anObj.MesureAppuiFlottant1Im().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("MesureAppuiFlottant1Im"));
  return aRes;
}

void xml_init(cSetOfMesureAppuisFlottants & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.MesureAppuiFlottant1Im(),aTree->GetAll("MesureAppuiFlottant1Im",false,1));
}


cTplValGesInit< int > & cMesureAppuis::Num()
{
   return mNum;
}

const cTplValGesInit< int > & cMesureAppuis::Num()const 
{
   return mNum;
}


Pt2dr & cMesureAppuis::Im()
{
   return mIm;
}

const Pt2dr & cMesureAppuis::Im()const 
{
   return mIm;
}


Pt3dr & cMesureAppuis::Ter()
{
   return mTer;
}

const Pt3dr & cMesureAppuis::Ter()const 
{
   return mTer;
}

cElXMLTree * ToXMLTree(const cMesureAppuis & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"MesureAppuis",eXMLBranche);
   if (anObj.Num().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Num"),anObj.Num().Val())->ReTagThis("Num"));
   aRes->AddFils(::ToXMLTree(std::string("Im"),anObj.Im())->ReTagThis("Im"));
   aRes->AddFils(ToXMLTree(std::string("Ter"),anObj.Ter())->ReTagThis("Ter"));
  return aRes;
}

void xml_init(cMesureAppuis & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Num(),aTree->Get("Num",1)); //tototo 

   xml_init(anObj.Im(),aTree->Get("Im",1)); //tototo 

   xml_init(anObj.Ter(),aTree->Get("Ter",1)); //tototo 
}


cTplValGesInit< std::string > & cListeAppuis1Im::NameImage()
{
   return mNameImage;
}

const cTplValGesInit< std::string > & cListeAppuis1Im::NameImage()const 
{
   return mNameImage;
}


std::list< cMesureAppuis > & cListeAppuis1Im::Mesures()
{
   return mMesures;
}

const std::list< cMesureAppuis > & cListeAppuis1Im::Mesures()const 
{
   return mMesures;
}

cElXMLTree * ToXMLTree(const cListeAppuis1Im & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ListeAppuis1Im",eXMLBranche);
   if (anObj.NameImage().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NameImage"),anObj.NameImage().Val())->ReTagThis("NameImage"));
  for
  (       std::list< cMesureAppuis >::const_iterator it=anObj.Mesures().begin();
      it !=anObj.Mesures().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("Mesures"));
  return aRes;
}

void xml_init(cListeAppuis1Im & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NameImage(),aTree->Get("NameImage",1),std::string("NoName")); //tototo 

   xml_init(anObj.Mesures(),aTree->GetAll("Mesures",false,1));
}


double & cVerifOrient::Tol()
{
   return mTol;
}

const double & cVerifOrient::Tol()const 
{
   return mTol;
}


cTplValGesInit< bool > & cVerifOrient::ShowMes()
{
   return mShowMes;
}

const cTplValGesInit< bool > & cVerifOrient::ShowMes()const 
{
   return mShowMes;
}


std::list< cMesureAppuis > & cVerifOrient::Appuis()
{
   return mAppuis;
}

const std::list< cMesureAppuis > & cVerifOrient::Appuis()const 
{
   return mAppuis;
}


cTplValGesInit< bool > & cVerifOrient::IsTest()
{
   return mIsTest;
}

const cTplValGesInit< bool > & cVerifOrient::IsTest()const 
{
   return mIsTest;
}


cTplValGesInit< cListeAppuis1Im > & cVerifOrient::AppuisConv()
{
   return mAppuisConv;
}

const cTplValGesInit< cListeAppuis1Im > & cVerifOrient::AppuisConv()const 
{
   return mAppuisConv;
}

cElXMLTree * ToXMLTree(const cVerifOrient & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"VerifOrient",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Tol"),anObj.Tol())->ReTagThis("Tol"));
   if (anObj.ShowMes().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("ShowMes"),anObj.ShowMes().Val())->ReTagThis("ShowMes"));
  for
  (       std::list< cMesureAppuis >::const_iterator it=anObj.Appuis().begin();
      it !=anObj.Appuis().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("Appuis"));
   if (anObj.IsTest().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("IsTest"),anObj.IsTest().Val())->ReTagThis("IsTest"));
   if (anObj.AppuisConv().IsInit())
      aRes->AddFils(ToXMLTree(anObj.AppuisConv().Val())->ReTagThis("AppuisConv"));
  return aRes;
}

void xml_init(cVerifOrient & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Tol(),aTree->Get("Tol",1)); //tototo 

   xml_init(anObj.ShowMes(),aTree->Get("ShowMes",1),bool(false)); //tototo 

   xml_init(anObj.Appuis(),aTree->GetAll("Appuis",false,1));

   xml_init(anObj.IsTest(),aTree->Get("IsTest",1),bool(false)); //tototo 

   xml_init(anObj.AppuisConv(),aTree->Get("AppuisConv",1)); //tototo 
}

eConventionsOrientation  Str2eConventionsOrientation(const std::string & aName)
{
   if (aName=="eConvInconnue")
      return eConvInconnue;
   else if (aName=="eConvApero_DistC2M")
      return eConvApero_DistC2M;
   else if (aName=="eConvApero_DistM2C")
      return eConvApero_DistM2C;
   else if (aName=="eConvOriLib")
      return eConvOriLib;
   else if (aName=="eConvMatrPoivillier_E")
      return eConvMatrPoivillier_E;
   else if (aName=="eConvAngErdas")
      return eConvAngErdas;
   else if (aName=="eConvAngErdas_Grade")
      return eConvAngErdas_Grade;
   else if (aName=="eConvAngAvionJaune")
      return eConvAngAvionJaune;
   else if (aName=="eConvAngSurvey")
      return eConvAngSurvey;
   else if (aName=="eConvAngPhotoMDegre")
      return eConvAngPhotoMDegre;
   else if (aName=="eConvAngPhotoMGrade")
      return eConvAngPhotoMGrade;
   else if (aName=="eConvAngLPSDegre")
      return eConvAngLPSDegre;
  else
  {
      cout << aName << " is not a correct value for enum eConventionsOrientation\n" ;
      ELISE_ASSERT(false,"XML enum value error");
  }
  return (eConventionsOrientation) 0;
}
void xml_init(eConventionsOrientation & aVal,cElXMLTree * aTree)
{
   aVal= Str2eConventionsOrientation(aTree->Contenu());
}
std::string  eToString(const eConventionsOrientation & anObj)
{
   if (anObj==eConvInconnue)
      return  "eConvInconnue";
   if (anObj==eConvApero_DistC2M)
      return  "eConvApero_DistC2M";
   if (anObj==eConvApero_DistM2C)
      return  "eConvApero_DistM2C";
   if (anObj==eConvOriLib)
      return  "eConvOriLib";
   if (anObj==eConvMatrPoivillier_E)
      return  "eConvMatrPoivillier_E";
   if (anObj==eConvAngErdas)
      return  "eConvAngErdas";
   if (anObj==eConvAngErdas_Grade)
      return  "eConvAngErdas_Grade";
   if (anObj==eConvAngAvionJaune)
      return  "eConvAngAvionJaune";
   if (anObj==eConvAngSurvey)
      return  "eConvAngSurvey";
   if (anObj==eConvAngPhotoMDegre)
      return  "eConvAngPhotoMDegre";
   if (anObj==eConvAngPhotoMGrade)
      return  "eConvAngPhotoMGrade";
   if (anObj==eConvAngLPSDegre)
      return  "eConvAngLPSDegre";
 std::cout << "Enum = eConventionsOrientation\n";
   ELISE_ASSERT(false,"Bad Value in eToString for enum value ");
   return "";
}

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eConventionsOrientation & anObj)
{
      return  cElXMLTree::ValueNode(aNameTag,eToString(anObj));
}


Pt2dr & cCalibrationInterneRadiale::CDist()
{
   return mCDist;
}

const Pt2dr & cCalibrationInterneRadiale::CDist()const 
{
   return mCDist;
}


std::vector< double > & cCalibrationInterneRadiale::CoeffDist()
{
   return mCoeffDist;
}

const std::vector< double > & cCalibrationInterneRadiale::CoeffDist()const 
{
   return mCoeffDist;
}


cTplValGesInit< double > & cCalibrationInterneRadiale::RatioDistInv()
{
   return mRatioDistInv;
}

const cTplValGesInit< double > & cCalibrationInterneRadiale::RatioDistInv()const 
{
   return mRatioDistInv;
}


cTplValGesInit< bool > & cCalibrationInterneRadiale::PPaEqPPs()
{
   return mPPaEqPPs;
}

const cTplValGesInit< bool > & cCalibrationInterneRadiale::PPaEqPPs()const 
{
   return mPPaEqPPs;
}

cElXMLTree * ToXMLTree(const cCalibrationInterneRadiale & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CalibrationInterneRadiale",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("CDist"),anObj.CDist())->ReTagThis("CDist"));
  for
  (       std::vector< double >::const_iterator it=anObj.CoeffDist().begin();
      it !=anObj.CoeffDist().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("CoeffDist"),(*it))->ReTagThis("CoeffDist"));
   if (anObj.RatioDistInv().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("RatioDistInv"),anObj.RatioDistInv().Val())->ReTagThis("RatioDistInv"));
   if (anObj.PPaEqPPs().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("PPaEqPPs"),anObj.PPaEqPPs().Val())->ReTagThis("PPaEqPPs"));
  return aRes;
}

void xml_init(cCalibrationInterneRadiale & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.CDist(),aTree->Get("CDist",1)); //tototo 

   xml_init(anObj.CoeffDist(),aTree->GetAll("CoeffDist",false,1));

   xml_init(anObj.RatioDistInv(),aTree->Get("RatioDistInv",1),double(1.3)); //tototo 

   xml_init(anObj.PPaEqPPs(),aTree->Get("PPaEqPPs",1),bool(false)); //tototo 
}


cCalibrationInterneRadiale & cCalibrationInternePghrStd::RadialePart()
{
   return mRadialePart;
}

const cCalibrationInterneRadiale & cCalibrationInternePghrStd::RadialePart()const 
{
   return mRadialePart;
}


cTplValGesInit< double > & cCalibrationInternePghrStd::P1()
{
   return mP1;
}

const cTplValGesInit< double > & cCalibrationInternePghrStd::P1()const 
{
   return mP1;
}


cTplValGesInit< double > & cCalibrationInternePghrStd::P2()
{
   return mP2;
}

const cTplValGesInit< double > & cCalibrationInternePghrStd::P2()const 
{
   return mP2;
}


cTplValGesInit< double > & cCalibrationInternePghrStd::b1()
{
   return mb1;
}

const cTplValGesInit< double > & cCalibrationInternePghrStd::b1()const 
{
   return mb1;
}


cTplValGesInit< double > & cCalibrationInternePghrStd::b2()
{
   return mb2;
}

const cTplValGesInit< double > & cCalibrationInternePghrStd::b2()const 
{
   return mb2;
}

cElXMLTree * ToXMLTree(const cCalibrationInternePghrStd & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CalibrationInternePghrStd",eXMLBranche);
   aRes->AddFils(ToXMLTree(anObj.RadialePart())->ReTagThis("RadialePart"));
   if (anObj.P1().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("P1"),anObj.P1().Val())->ReTagThis("P1"));
   if (anObj.P2().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("P2"),anObj.P2().Val())->ReTagThis("P2"));
   if (anObj.b1().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("b1"),anObj.b1().Val())->ReTagThis("b1"));
   if (anObj.b2().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("b2"),anObj.b2().Val())->ReTagThis("b2"));
  return aRes;
}

void xml_init(cCalibrationInternePghrStd & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.RadialePart(),aTree->Get("RadialePart",1)); //tototo 

   xml_init(anObj.P1(),aTree->Get("P1",1),double(0.0)); //tototo 

   xml_init(anObj.P2(),aTree->Get("P2",1),double(0.0)); //tototo 

   xml_init(anObj.b1(),aTree->Get("b1",1),double(0.0)); //tototo 

   xml_init(anObj.b2(),aTree->Get("b2",1),double(0.0)); //tototo 
}


eModelesCalibUnif & cCalibrationInterneUnif::TypeModele()
{
   return mTypeModele;
}

const eModelesCalibUnif & cCalibrationInterneUnif::TypeModele()const 
{
   return mTypeModele;
}


std::vector< double > & cCalibrationInterneUnif::Params()
{
   return mParams;
}

const std::vector< double > & cCalibrationInterneUnif::Params()const 
{
   return mParams;
}


std::vector< double > & cCalibrationInterneUnif::Etats()
{
   return mEtats;
}

const std::vector< double > & cCalibrationInterneUnif::Etats()const 
{
   return mEtats;
}

cElXMLTree * ToXMLTree(const cCalibrationInterneUnif & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CalibrationInterneUnif",eXMLBranche);
   aRes->AddFils(ToXMLTree(std::string("TypeModele"),anObj.TypeModele())->ReTagThis("TypeModele"));
  for
  (       std::vector< double >::const_iterator it=anObj.Params().begin();
      it !=anObj.Params().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Params"),(*it))->ReTagThis("Params"));
  for
  (       std::vector< double >::const_iterator it=anObj.Etats().begin();
      it !=anObj.Etats().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Etats"),(*it))->ReTagThis("Etats"));
  return aRes;
}

void xml_init(cCalibrationInterneUnif & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.TypeModele(),aTree->Get("TypeModele",1)); //tototo 

   xml_init(anObj.Params(),aTree->GetAll("Params",false,1));

   xml_init(anObj.Etats(),aTree->GetAll("Etats",false,1));
}


Pt2dr & cGridDeform2D::Origine()
{
   return mOrigine;
}

const Pt2dr & cGridDeform2D::Origine()const 
{
   return mOrigine;
}


Pt2dr & cGridDeform2D::Step()
{
   return mStep;
}

const Pt2dr & cGridDeform2D::Step()const 
{
   return mStep;
}


Im2D_REAL8 & cGridDeform2D::ImX()
{
   return mImX;
}

const Im2D_REAL8 & cGridDeform2D::ImX()const 
{
   return mImX;
}


Im2D_REAL8 & cGridDeform2D::ImY()
{
   return mImY;
}

const Im2D_REAL8 & cGridDeform2D::ImY()const 
{
   return mImY;
}

cElXMLTree * ToXMLTree(const cGridDeform2D & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"GridDeform2D",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Origine"),anObj.Origine())->ReTagThis("Origine"));
   aRes->AddFils(::ToXMLTree(std::string("Step"),anObj.Step())->ReTagThis("Step"));
   aRes->AddFils(::ToXMLTree(std::string("ImX"),anObj.ImX())->ReTagThis("ImX"));
   aRes->AddFils(::ToXMLTree(std::string("ImY"),anObj.ImY())->ReTagThis("ImY"));
  return aRes;
}

void xml_init(cGridDeform2D & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Origine(),aTree->Get("Origine",1)); //tototo 

   xml_init(anObj.Step(),aTree->Get("Step",1)); //tototo 

   xml_init(anObj.ImX(),aTree->Get("ImX",1)); //tototo 

   xml_init(anObj.ImY(),aTree->Get("ImY",1)); //tototo 
}


cGridDeform2D & cGridDirecteEtInverse::Directe()
{
   return mDirecte;
}

const cGridDeform2D & cGridDirecteEtInverse::Directe()const 
{
   return mDirecte;
}


cGridDeform2D & cGridDirecteEtInverse::Inverse()
{
   return mInverse;
}

const cGridDeform2D & cGridDirecteEtInverse::Inverse()const 
{
   return mInverse;
}


bool & cGridDirecteEtInverse::AdaptStep()
{
   return mAdaptStep;
}

const bool & cGridDirecteEtInverse::AdaptStep()const 
{
   return mAdaptStep;
}

cElXMLTree * ToXMLTree(const cGridDirecteEtInverse & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"GridDirecteEtInverse",eXMLBranche);
   aRes->AddFils(ToXMLTree(anObj.Directe())->ReTagThis("Directe"));
   aRes->AddFils(ToXMLTree(anObj.Inverse())->ReTagThis("Inverse"));
   aRes->AddFils(::ToXMLTree(std::string("AdaptStep"),anObj.AdaptStep())->ReTagThis("AdaptStep"));
  return aRes;
}

void xml_init(cGridDirecteEtInverse & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Directe(),aTree->Get("Directe",1)); //tototo 

   xml_init(anObj.Inverse(),aTree->Get("Inverse",1)); //tototo 

   xml_init(anObj.AdaptStep(),aTree->Get("AdaptStep",1)); //tototo 
}


Pt2dr & cPreCondRadial::C()
{
   return mC;
}

const Pt2dr & cPreCondRadial::C()const 
{
   return mC;
}


double & cPreCondRadial::F()
{
   return mF;
}

const double & cPreCondRadial::F()const 
{
   return mF;
}


eTypePreCondRad & cPreCondRadial::Mode()
{
   return mMode;
}

const eTypePreCondRad & cPreCondRadial::Mode()const 
{
   return mMode;
}

cElXMLTree * ToXMLTree(const cPreCondRadial & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"PreCondRadial",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("C"),anObj.C())->ReTagThis("C"));
   aRes->AddFils(::ToXMLTree(std::string("F"),anObj.F())->ReTagThis("F"));
   aRes->AddFils(ToXMLTree(std::string("Mode"),anObj.Mode())->ReTagThis("Mode"));
  return aRes;
}

void xml_init(cPreCondRadial & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.C(),aTree->Get("C",1)); //tototo 

   xml_init(anObj.F(),aTree->Get("F",1)); //tototo 

   xml_init(anObj.Mode(),aTree->Get("Mode",1)); //tototo 
}


Pt2dr & cPreCondGrid::C()
{
   return PreCondRadial().Val().C();
}

const Pt2dr & cPreCondGrid::C()const 
{
   return PreCondRadial().Val().C();
}


double & cPreCondGrid::F()
{
   return PreCondRadial().Val().F();
}

const double & cPreCondGrid::F()const 
{
   return PreCondRadial().Val().F();
}


eTypePreCondRad & cPreCondGrid::Mode()
{
   return PreCondRadial().Val().Mode();
}

const eTypePreCondRad & cPreCondGrid::Mode()const 
{
   return PreCondRadial().Val().Mode();
}


cTplValGesInit< cPreCondRadial > & cPreCondGrid::PreCondRadial()
{
   return mPreCondRadial;
}

const cTplValGesInit< cPreCondRadial > & cPreCondGrid::PreCondRadial()const 
{
   return mPreCondRadial;
}

cElXMLTree * ToXMLTree(const cPreCondGrid & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"PreCondGrid",eXMLBranche);
   if (anObj.PreCondRadial().IsInit())
      aRes->AddFils(ToXMLTree(anObj.PreCondRadial().Val())->ReTagThis("PreCondRadial"));
  return aRes;
}

void xml_init(cPreCondGrid & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.PreCondRadial(),aTree->Get("PreCondRadial",1)); //tototo 
}


Pt2dr & cCalibrationInterneGrid::C()
{
   return PreCondGrid().Val().PreCondRadial().Val().C();
}

const Pt2dr & cCalibrationInterneGrid::C()const 
{
   return PreCondGrid().Val().PreCondRadial().Val().C();
}


double & cCalibrationInterneGrid::F()
{
   return PreCondGrid().Val().PreCondRadial().Val().F();
}

const double & cCalibrationInterneGrid::F()const 
{
   return PreCondGrid().Val().PreCondRadial().Val().F();
}


eTypePreCondRad & cCalibrationInterneGrid::Mode()
{
   return PreCondGrid().Val().PreCondRadial().Val().Mode();
}

const eTypePreCondRad & cCalibrationInterneGrid::Mode()const 
{
   return PreCondGrid().Val().PreCondRadial().Val().Mode();
}


cTplValGesInit< cPreCondRadial > & cCalibrationInterneGrid::PreCondRadial()
{
   return PreCondGrid().Val().PreCondRadial();
}

const cTplValGesInit< cPreCondRadial > & cCalibrationInterneGrid::PreCondRadial()const 
{
   return PreCondGrid().Val().PreCondRadial();
}


cTplValGesInit< cPreCondGrid > & cCalibrationInterneGrid::PreCondGrid()
{
   return mPreCondGrid;
}

const cTplValGesInit< cPreCondGrid > & cCalibrationInterneGrid::PreCondGrid()const 
{
   return mPreCondGrid;
}


cGridDirecteEtInverse & cCalibrationInterneGrid::Grid()
{
   return mGrid;
}

const cGridDirecteEtInverse & cCalibrationInterneGrid::Grid()const 
{
   return mGrid;
}

cElXMLTree * ToXMLTree(const cCalibrationInterneGrid & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CalibrationInterneGrid",eXMLBranche);
   if (anObj.PreCondGrid().IsInit())
      aRes->AddFils(ToXMLTree(anObj.PreCondGrid().Val())->ReTagThis("PreCondGrid"));
   aRes->AddFils(ToXMLTree(anObj.Grid())->ReTagThis("Grid"));
  return aRes;
}

void xml_init(cCalibrationInterneGrid & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.PreCondGrid(),aTree->Get("PreCondGrid",1)); //tototo 

   xml_init(anObj.Grid(),aTree->Get("Grid",1)); //tototo 
}


Pt2dr & cSimilitudePlane::Scale()
{
   return mScale;
}

const Pt2dr & cSimilitudePlane::Scale()const 
{
   return mScale;
}


Pt2dr & cSimilitudePlane::Trans()
{
   return mTrans;
}

const Pt2dr & cSimilitudePlane::Trans()const 
{
   return mTrans;
}

cElXMLTree * ToXMLTree(const cSimilitudePlane & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"SimilitudePlane",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Scale"),anObj.Scale())->ReTagThis("Scale"));
   aRes->AddFils(::ToXMLTree(std::string("Trans"),anObj.Trans())->ReTagThis("Trans"));
  return aRes;
}

void xml_init(cSimilitudePlane & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Scale(),aTree->Get("Scale",1)); //tototo 

   xml_init(anObj.Trans(),aTree->Get("Trans",1)); //tototo 
}


Pt2dr & cAffinitePlane::I00()
{
   return mI00;
}

const Pt2dr & cAffinitePlane::I00()const 
{
   return mI00;
}


Pt2dr & cAffinitePlane::V10()
{
   return mV10;
}

const Pt2dr & cAffinitePlane::V10()const 
{
   return mV10;
}


Pt2dr & cAffinitePlane::V01()
{
   return mV01;
}

const Pt2dr & cAffinitePlane::V01()const 
{
   return mV01;
}

cElXMLTree * ToXMLTree(const cAffinitePlane & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"AffinitePlane",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("I00"),anObj.I00())->ReTagThis("I00"));
   aRes->AddFils(::ToXMLTree(std::string("V10"),anObj.V10())->ReTagThis("V10"));
   aRes->AddFils(::ToXMLTree(std::string("V01"),anObj.V01())->ReTagThis("V01"));
  return aRes;
}

void xml_init(cAffinitePlane & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.I00(),aTree->Get("I00",1)); //tototo 

   xml_init(anObj.V10(),aTree->Get("V10",1)); //tototo 

   xml_init(anObj.V01(),aTree->Get("V01",1)); //tototo 
}


cAffinitePlane & cOrIntGlob::Affinite()
{
   return mAffinite;
}

const cAffinitePlane & cOrIntGlob::Affinite()const 
{
   return mAffinite;
}


bool & cOrIntGlob::C2M()
{
   return mC2M;
}

const bool & cOrIntGlob::C2M()const 
{
   return mC2M;
}

cElXMLTree * ToXMLTree(const cOrIntGlob & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"OrIntGlob",eXMLBranche);
   aRes->AddFils(ToXMLTree(anObj.Affinite())->ReTagThis("Affinite"));
   aRes->AddFils(::ToXMLTree(std::string("C2M"),anObj.C2M())->ReTagThis("C2M"));
  return aRes;
}

void xml_init(cOrIntGlob & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Affinite(),aTree->Get("Affinite",1)); //tototo 

   xml_init(anObj.C2M(),aTree->Get("C2M",1)); //tototo 
}


Pt2dr & cParamForGrid::StepGrid()
{
   return mStepGrid;
}

const Pt2dr & cParamForGrid::StepGrid()const 
{
   return mStepGrid;
}


double & cParamForGrid::RayonInv()
{
   return mRayonInv;
}

const double & cParamForGrid::RayonInv()const 
{
   return mRayonInv;
}

cElXMLTree * ToXMLTree(const cParamForGrid & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ParamForGrid",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("StepGrid"),anObj.StepGrid())->ReTagThis("StepGrid"));
   aRes->AddFils(::ToXMLTree(std::string("RayonInv"),anObj.RayonInv())->ReTagThis("RayonInv"));
  return aRes;
}

void xml_init(cParamForGrid & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.StepGrid(),aTree->Get("StepGrid",1)); //tototo 

   xml_init(anObj.RayonInv(),aTree->Get("RayonInv",1)); //tototo 
}


cTplValGesInit< std::string > & cModNoDist::Inutile()
{
   return mInutile;
}

const cTplValGesInit< std::string > & cModNoDist::Inutile()const 
{
   return mInutile;
}

cElXMLTree * ToXMLTree(const cModNoDist & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ModNoDist",eXMLBranche);
   if (anObj.Inutile().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Inutile"),anObj.Inutile().Val())->ReTagThis("Inutile"));
  return aRes;
}

void xml_init(cModNoDist & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Inutile(),aTree->Get("Inutile",1)); //tototo 
}


cTplValGesInit< std::string > & cCalibDistortion::Inutile()
{
   return ModNoDist().Val().Inutile();
}

const cTplValGesInit< std::string > & cCalibDistortion::Inutile()const 
{
   return ModNoDist().Val().Inutile();
}


cTplValGesInit< cModNoDist > & cCalibDistortion::ModNoDist()
{
   return mModNoDist;
}

const cTplValGesInit< cModNoDist > & cCalibDistortion::ModNoDist()const 
{
   return mModNoDist;
}


cTplValGesInit< cCalibrationInterneRadiale > & cCalibDistortion::ModRad()
{
   return mModRad;
}

const cTplValGesInit< cCalibrationInterneRadiale > & cCalibDistortion::ModRad()const 
{
   return mModRad;
}


cTplValGesInit< cCalibrationInternePghrStd > & cCalibDistortion::ModPhgrStd()
{
   return mModPhgrStd;
}

const cTplValGesInit< cCalibrationInternePghrStd > & cCalibDistortion::ModPhgrStd()const 
{
   return mModPhgrStd;
}


cTplValGesInit< cCalibrationInterneUnif > & cCalibDistortion::ModUnif()
{
   return mModUnif;
}

const cTplValGesInit< cCalibrationInterneUnif > & cCalibDistortion::ModUnif()const 
{
   return mModUnif;
}


cTplValGesInit< cCalibrationInterneGrid > & cCalibDistortion::ModGrid()
{
   return mModGrid;
}

const cTplValGesInit< cCalibrationInterneGrid > & cCalibDistortion::ModGrid()const 
{
   return mModGrid;
}

cElXMLTree * ToXMLTree(const cCalibDistortion & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CalibDistortion",eXMLBranche);
   if (anObj.ModNoDist().IsInit())
      aRes->AddFils(ToXMLTree(anObj.ModNoDist().Val())->ReTagThis("ModNoDist"));
   if (anObj.ModRad().IsInit())
      aRes->AddFils(ToXMLTree(anObj.ModRad().Val())->ReTagThis("ModRad"));
   if (anObj.ModPhgrStd().IsInit())
      aRes->AddFils(ToXMLTree(anObj.ModPhgrStd().Val())->ReTagThis("ModPhgrStd"));
   if (anObj.ModUnif().IsInit())
      aRes->AddFils(ToXMLTree(anObj.ModUnif().Val())->ReTagThis("ModUnif"));
   if (anObj.ModGrid().IsInit())
      aRes->AddFils(ToXMLTree(anObj.ModGrid().Val())->ReTagThis("ModGrid"));
  return aRes;
}

void xml_init(cCalibDistortion & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.ModNoDist(),aTree->Get("ModNoDist",1)); //tototo 

   xml_init(anObj.ModRad(),aTree->Get("ModRad",1)); //tototo 

   xml_init(anObj.ModPhgrStd(),aTree->Get("ModPhgrStd",1)); //tototo 

   xml_init(anObj.ModUnif(),aTree->Get("ModUnif",1)); //tototo 

   xml_init(anObj.ModGrid(),aTree->Get("ModGrid",1)); //tototo 
}


std::string & cCorrectionRefractionAPosteriori::FileEstimCam()
{
   return mFileEstimCam;
}

const std::string & cCorrectionRefractionAPosteriori::FileEstimCam()const 
{
   return mFileEstimCam;
}


cTplValGesInit< std::string > & cCorrectionRefractionAPosteriori::NameTag()
{
   return mNameTag;
}

const cTplValGesInit< std::string > & cCorrectionRefractionAPosteriori::NameTag()const 
{
   return mNameTag;
}


double & cCorrectionRefractionAPosteriori::CoeffRefrac()
{
   return mCoeffRefrac;
}

const double & cCorrectionRefractionAPosteriori::CoeffRefrac()const 
{
   return mCoeffRefrac;
}


cTplValGesInit< bool > & cCorrectionRefractionAPosteriori::IntegreDist()
{
   return mIntegreDist;
}

const cTplValGesInit< bool > & cCorrectionRefractionAPosteriori::IntegreDist()const 
{
   return mIntegreDist;
}

cElXMLTree * ToXMLTree(const cCorrectionRefractionAPosteriori & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CorrectionRefractionAPosteriori",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("FileEstimCam"),anObj.FileEstimCam())->ReTagThis("FileEstimCam"));
   if (anObj.NameTag().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NameTag"),anObj.NameTag().Val())->ReTagThis("NameTag"));
   aRes->AddFils(::ToXMLTree(std::string("CoeffRefrac"),anObj.CoeffRefrac())->ReTagThis("CoeffRefrac"));
   if (anObj.IntegreDist().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("IntegreDist"),anObj.IntegreDist().Val())->ReTagThis("IntegreDist"));
  return aRes;
}

void xml_init(cCorrectionRefractionAPosteriori & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.FileEstimCam(),aTree->Get("FileEstimCam",1)); //tototo 

   xml_init(anObj.NameTag(),aTree->Get("NameTag",1),std::string("CalibrationInternConique")); //tototo 

   xml_init(anObj.CoeffRefrac(),aTree->Get("CoeffRefrac",1)); //tototo 

   xml_init(anObj.IntegreDist(),aTree->Get("IntegreDist",1),bool(false)); //tototo 
}


cTplValGesInit< eConventionsOrientation > & cCalibrationInternConique::KnownConv()
{
   return mKnownConv;
}

const cTplValGesInit< eConventionsOrientation > & cCalibrationInternConique::KnownConv()const 
{
   return mKnownConv;
}


std::vector< double > & cCalibrationInternConique::ParamAF()
{
   return mParamAF;
}

const std::vector< double > & cCalibrationInternConique::ParamAF()const 
{
   return mParamAF;
}


Pt2dr & cCalibrationInternConique::PP()
{
   return mPP;
}

const Pt2dr & cCalibrationInternConique::PP()const 
{
   return mPP;
}


double & cCalibrationInternConique::F()
{
   return mF;
}

const double & cCalibrationInternConique::F()const 
{
   return mF;
}


Pt2di & cCalibrationInternConique::SzIm()
{
   return mSzIm;
}

const Pt2di & cCalibrationInternConique::SzIm()const 
{
   return mSzIm;
}


cTplValGesInit< double > & cCalibrationInternConique::RayonUtile()
{
   return mRayonUtile;
}

const cTplValGesInit< double > & cCalibrationInternConique::RayonUtile()const 
{
   return mRayonUtile;
}


std::vector< bool > & cCalibrationInternConique::ComplIsC2M()
{
   return mComplIsC2M;
}

const std::vector< bool > & cCalibrationInternConique::ComplIsC2M()const 
{
   return mComplIsC2M;
}


cTplValGesInit< bool > & cCalibrationInternConique::ScannedAnalogik()
{
   return mScannedAnalogik;
}

const cTplValGesInit< bool > & cCalibrationInternConique::ScannedAnalogik()const 
{
   return mScannedAnalogik;
}


cAffinitePlane & cCalibrationInternConique::Affinite()
{
   return OrIntGlob().Val().Affinite();
}

const cAffinitePlane & cCalibrationInternConique::Affinite()const 
{
   return OrIntGlob().Val().Affinite();
}


bool & cCalibrationInternConique::C2M()
{
   return OrIntGlob().Val().C2M();
}

const bool & cCalibrationInternConique::C2M()const 
{
   return OrIntGlob().Val().C2M();
}


cTplValGesInit< cOrIntGlob > & cCalibrationInternConique::OrIntGlob()
{
   return mOrIntGlob;
}

const cTplValGesInit< cOrIntGlob > & cCalibrationInternConique::OrIntGlob()const 
{
   return mOrIntGlob;
}


Pt2dr & cCalibrationInternConique::StepGrid()
{
   return ParamForGrid().Val().StepGrid();
}

const Pt2dr & cCalibrationInternConique::StepGrid()const 
{
   return ParamForGrid().Val().StepGrid();
}


double & cCalibrationInternConique::RayonInv()
{
   return ParamForGrid().Val().RayonInv();
}

const double & cCalibrationInternConique::RayonInv()const 
{
   return ParamForGrid().Val().RayonInv();
}


cTplValGesInit< cParamForGrid > & cCalibrationInternConique::ParamForGrid()
{
   return mParamForGrid;
}

const cTplValGesInit< cParamForGrid > & cCalibrationInternConique::ParamForGrid()const 
{
   return mParamForGrid;
}


std::vector< cCalibDistortion > & cCalibrationInternConique::CalibDistortion()
{
   return mCalibDistortion;
}

const std::vector< cCalibDistortion > & cCalibrationInternConique::CalibDistortion()const 
{
   return mCalibDistortion;
}


std::string & cCalibrationInternConique::FileEstimCam()
{
   return CorrectionRefractionAPosteriori().Val().FileEstimCam();
}

const std::string & cCalibrationInternConique::FileEstimCam()const 
{
   return CorrectionRefractionAPosteriori().Val().FileEstimCam();
}


cTplValGesInit< std::string > & cCalibrationInternConique::NameTag()
{
   return CorrectionRefractionAPosteriori().Val().NameTag();
}

const cTplValGesInit< std::string > & cCalibrationInternConique::NameTag()const 
{
   return CorrectionRefractionAPosteriori().Val().NameTag();
}


double & cCalibrationInternConique::CoeffRefrac()
{
   return CorrectionRefractionAPosteriori().Val().CoeffRefrac();
}

const double & cCalibrationInternConique::CoeffRefrac()const 
{
   return CorrectionRefractionAPosteriori().Val().CoeffRefrac();
}


cTplValGesInit< bool > & cCalibrationInternConique::IntegreDist()
{
   return CorrectionRefractionAPosteriori().Val().IntegreDist();
}

const cTplValGesInit< bool > & cCalibrationInternConique::IntegreDist()const 
{
   return CorrectionRefractionAPosteriori().Val().IntegreDist();
}


cTplValGesInit< cCorrectionRefractionAPosteriori > & cCalibrationInternConique::CorrectionRefractionAPosteriori()
{
   return mCorrectionRefractionAPosteriori;
}

const cTplValGesInit< cCorrectionRefractionAPosteriori > & cCalibrationInternConique::CorrectionRefractionAPosteriori()const 
{
   return mCorrectionRefractionAPosteriori;
}

cElXMLTree * ToXMLTree(const cCalibrationInternConique & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CalibrationInternConique",eXMLBranche);
   if (anObj.KnownConv().IsInit())
      aRes->AddFils(ToXMLTree(std::string("KnownConv"),anObj.KnownConv().Val())->ReTagThis("KnownConv"));
  for
  (       std::vector< double >::const_iterator it=anObj.ParamAF().begin();
      it !=anObj.ParamAF().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("ParamAF"),(*it))->ReTagThis("ParamAF"));
   aRes->AddFils(::ToXMLTree(std::string("PP"),anObj.PP())->ReTagThis("PP"));
   aRes->AddFils(::ToXMLTree(std::string("F"),anObj.F())->ReTagThis("F"));
   aRes->AddFils(::ToXMLTree(std::string("SzIm"),anObj.SzIm())->ReTagThis("SzIm"));
   if (anObj.RayonUtile().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("RayonUtile"),anObj.RayonUtile().Val())->ReTagThis("RayonUtile"));
  for
  (       std::vector< bool >::const_iterator it=anObj.ComplIsC2M().begin();
      it !=anObj.ComplIsC2M().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("ComplIsC2M"),(*it))->ReTagThis("ComplIsC2M"));
   if (anObj.ScannedAnalogik().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("ScannedAnalogik"),anObj.ScannedAnalogik().Val())->ReTagThis("ScannedAnalogik"));
   if (anObj.OrIntGlob().IsInit())
      aRes->AddFils(ToXMLTree(anObj.OrIntGlob().Val())->ReTagThis("OrIntGlob"));
   if (anObj.ParamForGrid().IsInit())
      aRes->AddFils(ToXMLTree(anObj.ParamForGrid().Val())->ReTagThis("ParamForGrid"));
  for
  (       std::vector< cCalibDistortion >::const_iterator it=anObj.CalibDistortion().begin();
      it !=anObj.CalibDistortion().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("CalibDistortion"));
   if (anObj.CorrectionRefractionAPosteriori().IsInit())
      aRes->AddFils(ToXMLTree(anObj.CorrectionRefractionAPosteriori().Val())->ReTagThis("CorrectionRefractionAPosteriori"));
  return aRes;
}

void xml_init(cCalibrationInternConique & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KnownConv(),aTree->Get("KnownConv",1)); //tototo 

   xml_init(anObj.ParamAF(),aTree->GetAll("ParamAF",false,1));

   xml_init(anObj.PP(),aTree->Get("PP",1)); //tototo 

   xml_init(anObj.F(),aTree->Get("F",1)); //tototo 

   xml_init(anObj.SzIm(),aTree->Get("SzIm",1)); //tototo 

   xml_init(anObj.RayonUtile(),aTree->Get("RayonUtile",1)); //tototo 

   xml_init(anObj.ComplIsC2M(),aTree->GetAll("ComplIsC2M",false,1));

   xml_init(anObj.ScannedAnalogik(),aTree->Get("ScannedAnalogik",1),bool(false)); //tototo 

   xml_init(anObj.OrIntGlob(),aTree->Get("OrIntGlob",1)); //tototo 

   xml_init(anObj.ParamForGrid(),aTree->Get("ParamForGrid",1)); //tototo 

   xml_init(anObj.CalibDistortion(),aTree->GetAll("CalibDistortion",false,1));

   xml_init(anObj.CorrectionRefractionAPosteriori(),aTree->Get("CorrectionRefractionAPosteriori",1)); //tototo 
}


Pt3dr & cRepereCartesien::Ori()
{
   return mOri;
}

const Pt3dr & cRepereCartesien::Ori()const 
{
   return mOri;
}


Pt3dr & cRepereCartesien::Ox()
{
   return mOx;
}

const Pt3dr & cRepereCartesien::Ox()const 
{
   return mOx;
}


Pt3dr & cRepereCartesien::Oy()
{
   return mOy;
}

const Pt3dr & cRepereCartesien::Oy()const 
{
   return mOy;
}


Pt3dr & cRepereCartesien::Oz()
{
   return mOz;
}

const Pt3dr & cRepereCartesien::Oz()const 
{
   return mOz;
}

cElXMLTree * ToXMLTree(const cRepereCartesien & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"RepereCartesien",eXMLBranche);
   aRes->AddFils(ToXMLTree(std::string("Ori"),anObj.Ori())->ReTagThis("Ori"));
   aRes->AddFils(ToXMLTree(std::string("Ox"),anObj.Ox())->ReTagThis("Ox"));
   aRes->AddFils(ToXMLTree(std::string("Oy"),anObj.Oy())->ReTagThis("Oy"));
   aRes->AddFils(ToXMLTree(std::string("Oz"),anObj.Oz())->ReTagThis("Oz"));
  return aRes;
}

void xml_init(cRepereCartesien & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Ori(),aTree->Get("Ori",1)); //tototo 

   xml_init(anObj.Ox(),aTree->Get("Ox",1)); //tototo 

   xml_init(anObj.Oy(),aTree->Get("Oy",1)); //tototo 

   xml_init(anObj.Oz(),aTree->Get("Oz",1)); //tototo 
}


Pt3dr & cCodageMatr::L1()
{
   return mL1;
}

const Pt3dr & cCodageMatr::L1()const 
{
   return mL1;
}


Pt3dr & cCodageMatr::L2()
{
   return mL2;
}

const Pt3dr & cCodageMatr::L2()const 
{
   return mL2;
}


Pt3dr & cCodageMatr::L3()
{
   return mL3;
}

const Pt3dr & cCodageMatr::L3()const 
{
   return mL3;
}


cTplValGesInit< bool > & cCodageMatr::TrueRot()
{
   return mTrueRot;
}

const cTplValGesInit< bool > & cCodageMatr::TrueRot()const 
{
   return mTrueRot;
}

cElXMLTree * ToXMLTree(const cCodageMatr & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CodageMatr",eXMLBranche);
   aRes->AddFils(ToXMLTree(std::string("L1"),anObj.L1())->ReTagThis("L1"));
   aRes->AddFils(ToXMLTree(std::string("L2"),anObj.L2())->ReTagThis("L2"));
   aRes->AddFils(ToXMLTree(std::string("L3"),anObj.L3())->ReTagThis("L3"));
   if (anObj.TrueRot().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("TrueRot"),anObj.TrueRot().Val())->ReTagThis("TrueRot"));
  return aRes;
}

void xml_init(cCodageMatr & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.L1(),aTree->Get("L1",1)); //tototo 

   xml_init(anObj.L2(),aTree->Get("L2",1)); //tototo 

   xml_init(anObj.L3(),aTree->Get("L3",1)); //tototo 

   xml_init(anObj.TrueRot(),aTree->Get("TrueRot",1),bool(true)); //tototo 
}


Pt3dr & cRotationVect::L1()
{
   return CodageMatr().Val().L1();
}

const Pt3dr & cRotationVect::L1()const 
{
   return CodageMatr().Val().L1();
}


Pt3dr & cRotationVect::L2()
{
   return CodageMatr().Val().L2();
}

const Pt3dr & cRotationVect::L2()const 
{
   return CodageMatr().Val().L2();
}


Pt3dr & cRotationVect::L3()
{
   return CodageMatr().Val().L3();
}

const Pt3dr & cRotationVect::L3()const 
{
   return CodageMatr().Val().L3();
}


cTplValGesInit< bool > & cRotationVect::TrueRot()
{
   return CodageMatr().Val().TrueRot();
}

const cTplValGesInit< bool > & cRotationVect::TrueRot()const 
{
   return CodageMatr().Val().TrueRot();
}


cTplValGesInit< cCodageMatr > & cRotationVect::CodageMatr()
{
   return mCodageMatr;
}

const cTplValGesInit< cCodageMatr > & cRotationVect::CodageMatr()const 
{
   return mCodageMatr;
}


cTplValGesInit< Pt3dr > & cRotationVect::CodageAngulaire()
{
   return mCodageAngulaire;
}

const cTplValGesInit< Pt3dr > & cRotationVect::CodageAngulaire()const 
{
   return mCodageAngulaire;
}


cTplValGesInit< std::string > & cRotationVect::CodageSymbolique()
{
   return mCodageSymbolique;
}

const cTplValGesInit< std::string > & cRotationVect::CodageSymbolique()const 
{
   return mCodageSymbolique;
}

cElXMLTree * ToXMLTree(const cRotationVect & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"RotationVect",eXMLBranche);
   if (anObj.CodageMatr().IsInit())
      aRes->AddFils(ToXMLTree(anObj.CodageMatr().Val())->ReTagThis("CodageMatr"));
   if (anObj.CodageAngulaire().IsInit())
      aRes->AddFils(ToXMLTree(std::string("CodageAngulaire"),anObj.CodageAngulaire().Val())->ReTagThis("CodageAngulaire"));
   if (anObj.CodageSymbolique().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("CodageSymbolique"),anObj.CodageSymbolique().Val())->ReTagThis("CodageSymbolique"));
  return aRes;
}

void xml_init(cRotationVect & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.CodageMatr(),aTree->Get("CodageMatr",1)); //tototo 

   xml_init(anObj.CodageAngulaire(),aTree->Get("CodageAngulaire",1)); //tototo 

   xml_init(anObj.CodageSymbolique(),aTree->Get("CodageSymbolique",1)); //tototo 
}


cTplValGesInit< double > & cOrientationExterneRigide::AltiSol()
{
   return mAltiSol;
}

const cTplValGesInit< double > & cOrientationExterneRigide::AltiSol()const 
{
   return mAltiSol;
}


cTplValGesInit< double > & cOrientationExterneRigide::Profondeur()
{
   return mProfondeur;
}

const cTplValGesInit< double > & cOrientationExterneRigide::Profondeur()const 
{
   return mProfondeur;
}


cTplValGesInit< double > & cOrientationExterneRigide::Time()
{
   return mTime;
}

const cTplValGesInit< double > & cOrientationExterneRigide::Time()const 
{
   return mTime;
}


cTplValGesInit< eConventionsOrientation > & cOrientationExterneRigide::KnownConv()
{
   return mKnownConv;
}

const cTplValGesInit< eConventionsOrientation > & cOrientationExterneRigide::KnownConv()const 
{
   return mKnownConv;
}


Pt3dr & cOrientationExterneRigide::Centre()
{
   return mCentre;
}

const Pt3dr & cOrientationExterneRigide::Centre()const 
{
   return mCentre;
}


cTplValGesInit< Pt3dr > & cOrientationExterneRigide::Vitesse()
{
   return mVitesse;
}

const cTplValGesInit< Pt3dr > & cOrientationExterneRigide::Vitesse()const 
{
   return mVitesse;
}


cTplValGesInit< bool > & cOrientationExterneRigide::VitesseFiable()
{
   return mVitesseFiable;
}

const cTplValGesInit< bool > & cOrientationExterneRigide::VitesseFiable()const 
{
   return mVitesseFiable;
}


cTplValGesInit< Pt3dr > & cOrientationExterneRigide::IncCentre()
{
   return mIncCentre;
}

const cTplValGesInit< Pt3dr > & cOrientationExterneRigide::IncCentre()const 
{
   return mIncCentre;
}


cRotationVect & cOrientationExterneRigide::ParamRotation()
{
   return mParamRotation;
}

const cRotationVect & cOrientationExterneRigide::ParamRotation()const 
{
   return mParamRotation;
}

cElXMLTree * ToXMLTree(const cOrientationExterneRigide & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"OrientationExterneRigide",eXMLBranche);
   if (anObj.AltiSol().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("AltiSol"),anObj.AltiSol().Val())->ReTagThis("AltiSol"));
   if (anObj.Profondeur().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Profondeur"),anObj.Profondeur().Val())->ReTagThis("Profondeur"));
   if (anObj.Time().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Time"),anObj.Time().Val())->ReTagThis("Time"));
   if (anObj.KnownConv().IsInit())
      aRes->AddFils(ToXMLTree(std::string("KnownConv"),anObj.KnownConv().Val())->ReTagThis("KnownConv"));
   aRes->AddFils(ToXMLTree(std::string("Centre"),anObj.Centre())->ReTagThis("Centre"));
   if (anObj.Vitesse().IsInit())
      aRes->AddFils(ToXMLTree(std::string("Vitesse"),anObj.Vitesse().Val())->ReTagThis("Vitesse"));
   if (anObj.VitesseFiable().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("VitesseFiable"),anObj.VitesseFiable().Val())->ReTagThis("VitesseFiable"));
   if (anObj.IncCentre().IsInit())
      aRes->AddFils(ToXMLTree(std::string("IncCentre"),anObj.IncCentre().Val())->ReTagThis("IncCentre"));
   aRes->AddFils(ToXMLTree(anObj.ParamRotation())->ReTagThis("ParamRotation"));
  return aRes;
}

void xml_init(cOrientationExterneRigide & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.AltiSol(),aTree->Get("AltiSol",1)); //tototo 

   xml_init(anObj.Profondeur(),aTree->Get("Profondeur",1)); //tototo 

   xml_init(anObj.Time(),aTree->Get("Time",1),double(0.0)); //tototo 

   xml_init(anObj.KnownConv(),aTree->Get("KnownConv",1)); //tototo 

   xml_init(anObj.Centre(),aTree->Get("Centre",1)); //tototo 

   xml_init(anObj.Vitesse(),aTree->Get("Vitesse",1)); //tototo 

   xml_init(anObj.VitesseFiable(),aTree->Get("VitesseFiable",1),bool(true)); //tototo 

   xml_init(anObj.IncCentre(),aTree->Get("IncCentre",1)); //tototo 

   xml_init(anObj.ParamRotation(),aTree->Get("ParamRotation",1)); //tototo 
}


bool & cConvExplicite::SensYVideo()
{
   return mSensYVideo;
}

const bool & cConvExplicite::SensYVideo()const 
{
   return mSensYVideo;
}


bool & cConvExplicite::DistSenC2M()
{
   return mDistSenC2M;
}

const bool & cConvExplicite::DistSenC2M()const 
{
   return mDistSenC2M;
}


bool & cConvExplicite::MatrSenC2M()
{
   return mMatrSenC2M;
}

const bool & cConvExplicite::MatrSenC2M()const 
{
   return mMatrSenC2M;
}


Pt3dr & cConvExplicite::ColMul()
{
   return mColMul;
}

const Pt3dr & cConvExplicite::ColMul()const 
{
   return mColMul;
}


Pt3dr & cConvExplicite::LigMul()
{
   return mLigMul;
}

const Pt3dr & cConvExplicite::LigMul()const 
{
   return mLigMul;
}


eUniteAngulaire & cConvExplicite::UniteAngles()
{
   return mUniteAngles;
}

const eUniteAngulaire & cConvExplicite::UniteAngles()const 
{
   return mUniteAngles;
}


Pt3di & cConvExplicite::NumAxe()
{
   return mNumAxe;
}

const Pt3di & cConvExplicite::NumAxe()const 
{
   return mNumAxe;
}


bool & cConvExplicite::SensCardan()
{
   return mSensCardan;
}

const bool & cConvExplicite::SensCardan()const 
{
   return mSensCardan;
}


cTplValGesInit< eConventionsOrientation > & cConvExplicite::Convention()
{
   return mConvention;
}

const cTplValGesInit< eConventionsOrientation > & cConvExplicite::Convention()const 
{
   return mConvention;
}

cElXMLTree * ToXMLTree(const cConvExplicite & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ConvExplicite",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("SensYVideo"),anObj.SensYVideo())->ReTagThis("SensYVideo"));
   aRes->AddFils(::ToXMLTree(std::string("DistSenC2M"),anObj.DistSenC2M())->ReTagThis("DistSenC2M"));
   aRes->AddFils(::ToXMLTree(std::string("MatrSenC2M"),anObj.MatrSenC2M())->ReTagThis("MatrSenC2M"));
   aRes->AddFils(ToXMLTree(std::string("ColMul"),anObj.ColMul())->ReTagThis("ColMul"));
   aRes->AddFils(ToXMLTree(std::string("LigMul"),anObj.LigMul())->ReTagThis("LigMul"));
   aRes->AddFils(ToXMLTree(std::string("UniteAngles"),anObj.UniteAngles())->ReTagThis("UniteAngles"));
   aRes->AddFils(::ToXMLTree(std::string("NumAxe"),anObj.NumAxe())->ReTagThis("NumAxe"));
   aRes->AddFils(::ToXMLTree(std::string("SensCardan"),anObj.SensCardan())->ReTagThis("SensCardan"));
   if (anObj.Convention().IsInit())
      aRes->AddFils(ToXMLTree(std::string("Convention"),anObj.Convention().Val())->ReTagThis("Convention"));
  return aRes;
}

void xml_init(cConvExplicite & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.SensYVideo(),aTree->Get("SensYVideo",1)); //tototo 

   xml_init(anObj.DistSenC2M(),aTree->Get("DistSenC2M",1)); //tototo 

   xml_init(anObj.MatrSenC2M(),aTree->Get("MatrSenC2M",1)); //tototo 

   xml_init(anObj.ColMul(),aTree->Get("ColMul",1)); //tototo 

   xml_init(anObj.LigMul(),aTree->Get("LigMul",1)); //tototo 

   xml_init(anObj.UniteAngles(),aTree->Get("UniteAngles",1)); //tototo 

   xml_init(anObj.NumAxe(),aTree->Get("NumAxe",1)); //tototo 

   xml_init(anObj.SensCardan(),aTree->Get("SensCardan",1)); //tototo 

   xml_init(anObj.Convention(),aTree->Get("Convention",1),eConventionsOrientation(eConvInconnue)); //tototo 
}


cTplValGesInit< eConventionsOrientation > & cConvOri::KnownConv()
{
   return mKnownConv;
}

const cTplValGesInit< eConventionsOrientation > & cConvOri::KnownConv()const 
{
   return mKnownConv;
}


bool & cConvOri::SensYVideo()
{
   return ConvExplicite().Val().SensYVideo();
}

const bool & cConvOri::SensYVideo()const 
{
   return ConvExplicite().Val().SensYVideo();
}


bool & cConvOri::DistSenC2M()
{
   return ConvExplicite().Val().DistSenC2M();
}

const bool & cConvOri::DistSenC2M()const 
{
   return ConvExplicite().Val().DistSenC2M();
}


bool & cConvOri::MatrSenC2M()
{
   return ConvExplicite().Val().MatrSenC2M();
}

const bool & cConvOri::MatrSenC2M()const 
{
   return ConvExplicite().Val().MatrSenC2M();
}


Pt3dr & cConvOri::ColMul()
{
   return ConvExplicite().Val().ColMul();
}

const Pt3dr & cConvOri::ColMul()const 
{
   return ConvExplicite().Val().ColMul();
}


Pt3dr & cConvOri::LigMul()
{
   return ConvExplicite().Val().LigMul();
}

const Pt3dr & cConvOri::LigMul()const 
{
   return ConvExplicite().Val().LigMul();
}


eUniteAngulaire & cConvOri::UniteAngles()
{
   return ConvExplicite().Val().UniteAngles();
}

const eUniteAngulaire & cConvOri::UniteAngles()const 
{
   return ConvExplicite().Val().UniteAngles();
}


Pt3di & cConvOri::NumAxe()
{
   return ConvExplicite().Val().NumAxe();
}

const Pt3di & cConvOri::NumAxe()const 
{
   return ConvExplicite().Val().NumAxe();
}


bool & cConvOri::SensCardan()
{
   return ConvExplicite().Val().SensCardan();
}

const bool & cConvOri::SensCardan()const 
{
   return ConvExplicite().Val().SensCardan();
}


cTplValGesInit< eConventionsOrientation > & cConvOri::Convention()
{
   return ConvExplicite().Val().Convention();
}

const cTplValGesInit< eConventionsOrientation > & cConvOri::Convention()const 
{
   return ConvExplicite().Val().Convention();
}


cTplValGesInit< cConvExplicite > & cConvOri::ConvExplicite()
{
   return mConvExplicite;
}

const cTplValGesInit< cConvExplicite > & cConvOri::ConvExplicite()const 
{
   return mConvExplicite;
}

cElXMLTree * ToXMLTree(const cConvOri & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ConvOri",eXMLBranche);
   if (anObj.KnownConv().IsInit())
      aRes->AddFils(ToXMLTree(std::string("KnownConv"),anObj.KnownConv().Val())->ReTagThis("KnownConv"));
   if (anObj.ConvExplicite().IsInit())
      aRes->AddFils(ToXMLTree(anObj.ConvExplicite().Val())->ReTagThis("ConvExplicite"));
  return aRes;
}

void xml_init(cConvOri & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KnownConv(),aTree->Get("KnownConv",1)); //tototo 

   xml_init(anObj.ConvExplicite(),aTree->Get("ConvExplicite",1)); //tototo 
}


cTplValGesInit< cAffinitePlane > & cOrientationConique::OrIntImaM2C()
{
   return mOrIntImaM2C;
}

const cTplValGesInit< cAffinitePlane > & cOrientationConique::OrIntImaM2C()const 
{
   return mOrIntImaM2C;
}


cTplValGesInit< eTypeProjectionCam > & cOrientationConique::TypeProj()
{
   return mTypeProj;
}

const cTplValGesInit< eTypeProjectionCam > & cOrientationConique::TypeProj()const 
{
   return mTypeProj;
}


cTplValGesInit< cCalibrationInternConique > & cOrientationConique::Interne()
{
   return mInterne;
}

const cTplValGesInit< cCalibrationInternConique > & cOrientationConique::Interne()const 
{
   return mInterne;
}


cTplValGesInit< std::string > & cOrientationConique::FileInterne()
{
   return mFileInterne;
}

const cTplValGesInit< std::string > & cOrientationConique::FileInterne()const 
{
   return mFileInterne;
}


cTplValGesInit< bool > & cOrientationConique::RelativeNameFI()
{
   return mRelativeNameFI;
}

const cTplValGesInit< bool > & cOrientationConique::RelativeNameFI()const 
{
   return mRelativeNameFI;
}


cOrientationExterneRigide & cOrientationConique::Externe()
{
   return mExterne;
}

const cOrientationExterneRigide & cOrientationConique::Externe()const 
{
   return mExterne;
}


cTplValGesInit< cVerifOrient > & cOrientationConique::Verif()
{
   return mVerif;
}

const cTplValGesInit< cVerifOrient > & cOrientationConique::Verif()const 
{
   return mVerif;
}


cTplValGesInit< eConventionsOrientation > & cOrientationConique::KnownConv()
{
   return ConvOri().KnownConv();
}

const cTplValGesInit< eConventionsOrientation > & cOrientationConique::KnownConv()const 
{
   return ConvOri().KnownConv();
}


bool & cOrientationConique::SensYVideo()
{
   return ConvOri().ConvExplicite().Val().SensYVideo();
}

const bool & cOrientationConique::SensYVideo()const 
{
   return ConvOri().ConvExplicite().Val().SensYVideo();
}


bool & cOrientationConique::DistSenC2M()
{
   return ConvOri().ConvExplicite().Val().DistSenC2M();
}

const bool & cOrientationConique::DistSenC2M()const 
{
   return ConvOri().ConvExplicite().Val().DistSenC2M();
}


bool & cOrientationConique::MatrSenC2M()
{
   return ConvOri().ConvExplicite().Val().MatrSenC2M();
}

const bool & cOrientationConique::MatrSenC2M()const 
{
   return ConvOri().ConvExplicite().Val().MatrSenC2M();
}


Pt3dr & cOrientationConique::ColMul()
{
   return ConvOri().ConvExplicite().Val().ColMul();
}

const Pt3dr & cOrientationConique::ColMul()const 
{
   return ConvOri().ConvExplicite().Val().ColMul();
}


Pt3dr & cOrientationConique::LigMul()
{
   return ConvOri().ConvExplicite().Val().LigMul();
}

const Pt3dr & cOrientationConique::LigMul()const 
{
   return ConvOri().ConvExplicite().Val().LigMul();
}


eUniteAngulaire & cOrientationConique::UniteAngles()
{
   return ConvOri().ConvExplicite().Val().UniteAngles();
}

const eUniteAngulaire & cOrientationConique::UniteAngles()const 
{
   return ConvOri().ConvExplicite().Val().UniteAngles();
}


Pt3di & cOrientationConique::NumAxe()
{
   return ConvOri().ConvExplicite().Val().NumAxe();
}

const Pt3di & cOrientationConique::NumAxe()const 
{
   return ConvOri().ConvExplicite().Val().NumAxe();
}


bool & cOrientationConique::SensCardan()
{
   return ConvOri().ConvExplicite().Val().SensCardan();
}

const bool & cOrientationConique::SensCardan()const 
{
   return ConvOri().ConvExplicite().Val().SensCardan();
}


cTplValGesInit< eConventionsOrientation > & cOrientationConique::Convention()
{
   return ConvOri().ConvExplicite().Val().Convention();
}

const cTplValGesInit< eConventionsOrientation > & cOrientationConique::Convention()const 
{
   return ConvOri().ConvExplicite().Val().Convention();
}


cTplValGesInit< cConvExplicite > & cOrientationConique::ConvExplicite()
{
   return ConvOri().ConvExplicite();
}

const cTplValGesInit< cConvExplicite > & cOrientationConique::ConvExplicite()const 
{
   return ConvOri().ConvExplicite();
}


cConvOri & cOrientationConique::ConvOri()
{
   return mConvOri;
}

const cConvOri & cOrientationConique::ConvOri()const 
{
   return mConvOri;
}

cElXMLTree * ToXMLTree(const cOrientationConique & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"OrientationConique",eXMLBranche);
   if (anObj.OrIntImaM2C().IsInit())
      aRes->AddFils(ToXMLTree(anObj.OrIntImaM2C().Val())->ReTagThis("OrIntImaM2C"));
   if (anObj.TypeProj().IsInit())
      aRes->AddFils(ToXMLTree(std::string("TypeProj"),anObj.TypeProj().Val())->ReTagThis("TypeProj"));
   if (anObj.Interne().IsInit())
      aRes->AddFils(ToXMLTree(anObj.Interne().Val())->ReTagThis("Interne"));
   if (anObj.FileInterne().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("FileInterne"),anObj.FileInterne().Val())->ReTagThis("FileInterne"));
   if (anObj.RelativeNameFI().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("RelativeNameFI"),anObj.RelativeNameFI().Val())->ReTagThis("RelativeNameFI"));
   aRes->AddFils(ToXMLTree(anObj.Externe())->ReTagThis("Externe"));
   if (anObj.Verif().IsInit())
      aRes->AddFils(ToXMLTree(anObj.Verif().Val())->ReTagThis("Verif"));
   aRes->AddFils(ToXMLTree(anObj.ConvOri())->ReTagThis("ConvOri"));
  return aRes;
}

void xml_init(cOrientationConique & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.OrIntImaM2C(),aTree->Get("OrIntImaM2C",1)); //tototo 

   xml_init(anObj.TypeProj(),aTree->Get("TypeProj",1),eTypeProjectionCam(eProjStenope)); //tototo 

   xml_init(anObj.Interne(),aTree->Get("Interne",1)); //tototo 

   xml_init(anObj.FileInterne(),aTree->Get("FileInterne",1)); //tototo 

   xml_init(anObj.RelativeNameFI(),aTree->Get("RelativeNameFI",1),bool(false)); //tototo 

   xml_init(anObj.Externe(),aTree->Get("Externe",1)); //tototo 

   xml_init(anObj.Verif(),aTree->Get("Verif",1)); //tototo 

   xml_init(anObj.ConvOri(),aTree->Get("ConvOri",1)); //tototo 
}


std::string & cMNT2Cmp::NameIm()
{
   return mNameIm;
}

const std::string & cMNT2Cmp::NameIm()const 
{
   return mNameIm;
}


cTplValGesInit< std::string > & cMNT2Cmp::NameXml()
{
   return mNameXml;
}

const cTplValGesInit< std::string > & cMNT2Cmp::NameXml()const 
{
   return mNameXml;
}


cTplValGesInit< int > & cMNT2Cmp::IdIsRef()
{
   return mIdIsRef;
}

const cTplValGesInit< int > & cMNT2Cmp::IdIsRef()const 
{
   return mIdIsRef;
}


cTplValGesInit< std::string > & cMNT2Cmp::ShorName()
{
   return mShorName;
}

const cTplValGesInit< std::string > & cMNT2Cmp::ShorName()const 
{
   return mShorName;
}

cElXMLTree * ToXMLTree(const cMNT2Cmp & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"MNT2Cmp",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("NameIm"),anObj.NameIm())->ReTagThis("NameIm"));
   if (anObj.NameXml().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NameXml"),anObj.NameXml().Val())->ReTagThis("NameXml"));
   if (anObj.IdIsRef().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("IdIsRef"),anObj.IdIsRef().Val())->ReTagThis("IdIsRef"));
   if (anObj.ShorName().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("ShorName"),anObj.ShorName().Val())->ReTagThis("ShorName"));
  return aRes;
}

void xml_init(cMNT2Cmp & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NameIm(),aTree->Get("NameIm",1)); //tototo 

   xml_init(anObj.NameXml(),aTree->Get("NameXml",1)); //tototo 

   xml_init(anObj.IdIsRef(),aTree->Get("IdIsRef",1),int(0)); //tototo 

   xml_init(anObj.ShorName(),aTree->Get("ShorName",1)); //tototo 
}


std::list< Pt2di > & cContourPolyCM::Pts()
{
   return mPts;
}

const std::list< Pt2di > & cContourPolyCM::Pts()const 
{
   return mPts;
}

cElXMLTree * ToXMLTree(const cContourPolyCM & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ContourPolyCM",eXMLBranche);
  for
  (       std::list< Pt2di >::const_iterator it=anObj.Pts().begin();
      it !=anObj.Pts().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Pts"),(*it))->ReTagThis("Pts"));
  return aRes;
}

void xml_init(cContourPolyCM & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Pts(),aTree->GetAll("Pts",false,1));
}


std::list< Pt2di > & cEnvellopeZoneCM::Pts()
{
   return ContourPolyCM().Val().Pts();
}

const std::list< Pt2di > & cEnvellopeZoneCM::Pts()const 
{
   return ContourPolyCM().Val().Pts();
}


cTplValGesInit< cContourPolyCM > & cEnvellopeZoneCM::ContourPolyCM()
{
   return mContourPolyCM;
}

const cTplValGesInit< cContourPolyCM > & cEnvellopeZoneCM::ContourPolyCM()const 
{
   return mContourPolyCM;
}


cTplValGesInit< Box2dr > & cEnvellopeZoneCM::BoxContourCM()
{
   return mBoxContourCM;
}

const cTplValGesInit< Box2dr > & cEnvellopeZoneCM::BoxContourCM()const 
{
   return mBoxContourCM;
}

cElXMLTree * ToXMLTree(const cEnvellopeZoneCM & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"EnvellopeZoneCM",eXMLBranche);
   if (anObj.ContourPolyCM().IsInit())
      aRes->AddFils(ToXMLTree(anObj.ContourPolyCM().Val())->ReTagThis("ContourPolyCM"));
   if (anObj.BoxContourCM().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("BoxContourCM"),anObj.BoxContourCM().Val())->ReTagThis("BoxContourCM"));
  return aRes;
}

void xml_init(cEnvellopeZoneCM & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.ContourPolyCM(),aTree->Get("ContourPolyCM",1)); //tototo 

   xml_init(anObj.BoxContourCM(),aTree->Get("BoxContourCM",1)); //tototo 
}


cTplValGesInit< std::string > & cZoneCmpMnt::NomZone()
{
   return mNomZone;
}

const cTplValGesInit< std::string > & cZoneCmpMnt::NomZone()const 
{
   return mNomZone;
}


std::list< Pt2di > & cZoneCmpMnt::Pts()
{
   return EnvellopeZoneCM().ContourPolyCM().Val().Pts();
}

const std::list< Pt2di > & cZoneCmpMnt::Pts()const 
{
   return EnvellopeZoneCM().ContourPolyCM().Val().Pts();
}


cTplValGesInit< cContourPolyCM > & cZoneCmpMnt::ContourPolyCM()
{
   return EnvellopeZoneCM().ContourPolyCM();
}

const cTplValGesInit< cContourPolyCM > & cZoneCmpMnt::ContourPolyCM()const 
{
   return EnvellopeZoneCM().ContourPolyCM();
}


cTplValGesInit< Box2dr > & cZoneCmpMnt::BoxContourCM()
{
   return EnvellopeZoneCM().BoxContourCM();
}

const cTplValGesInit< Box2dr > & cZoneCmpMnt::BoxContourCM()const 
{
   return EnvellopeZoneCM().BoxContourCM();
}


cEnvellopeZoneCM & cZoneCmpMnt::EnvellopeZoneCM()
{
   return mEnvellopeZoneCM;
}

const cEnvellopeZoneCM & cZoneCmpMnt::EnvellopeZoneCM()const 
{
   return mEnvellopeZoneCM;
}

cElXMLTree * ToXMLTree(const cZoneCmpMnt & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ZoneCmpMnt",eXMLBranche);
   if (anObj.NomZone().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NomZone"),anObj.NomZone().Val())->ReTagThis("NomZone"));
   aRes->AddFils(ToXMLTree(anObj.EnvellopeZoneCM())->ReTagThis("EnvellopeZoneCM"));
  return aRes;
}

void xml_init(cZoneCmpMnt & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NomZone(),aTree->Get("NomZone",1)); //tototo 

   xml_init(anObj.EnvellopeZoneCM(),aTree->Get("EnvellopeZoneCM",1)); //tototo 
}


double & cEcartZ::DynVisu()
{
   return mDynVisu;
}

const double & cEcartZ::DynVisu()const 
{
   return mDynVisu;
}

cElXMLTree * ToXMLTree(const cEcartZ & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"EcartZ",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("DynVisu"),anObj.DynVisu())->ReTagThis("DynVisu"));
  return aRes;
}

void xml_init(cEcartZ & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.DynVisu(),aTree->Get("DynVisu",1)); //tototo 
}


double & cCorrelPente::SzWCP()
{
   return mSzWCP;
}

const double & cCorrelPente::SzWCP()const 
{
   return mSzWCP;
}


double & cCorrelPente::GrMinCP()
{
   return mGrMinCP;
}

const double & cCorrelPente::GrMinCP()const 
{
   return mGrMinCP;
}

cElXMLTree * ToXMLTree(const cCorrelPente & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CorrelPente",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("SzWCP"),anObj.SzWCP())->ReTagThis("SzWCP"));
   aRes->AddFils(::ToXMLTree(std::string("GrMinCP"),anObj.GrMinCP())->ReTagThis("GrMinCP"));
  return aRes;
}

void xml_init(cCorrelPente & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.SzWCP(),aTree->Get("SzWCP",1)); //tototo 

   xml_init(anObj.GrMinCP(),aTree->Get("GrMinCP",1)); //tototo 
}


double & cMesureCmptMnt::DynVisu()
{
   return EcartZ().Val().DynVisu();
}

const double & cMesureCmptMnt::DynVisu()const 
{
   return EcartZ().Val().DynVisu();
}


cTplValGesInit< cEcartZ > & cMesureCmptMnt::EcartZ()
{
   return mEcartZ;
}

const cTplValGesInit< cEcartZ > & cMesureCmptMnt::EcartZ()const 
{
   return mEcartZ;
}


double & cMesureCmptMnt::SzWCP()
{
   return CorrelPente().Val().SzWCP();
}

const double & cMesureCmptMnt::SzWCP()const 
{
   return CorrelPente().Val().SzWCP();
}


double & cMesureCmptMnt::GrMinCP()
{
   return CorrelPente().Val().GrMinCP();
}

const double & cMesureCmptMnt::GrMinCP()const 
{
   return CorrelPente().Val().GrMinCP();
}


cTplValGesInit< cCorrelPente > & cMesureCmptMnt::CorrelPente()
{
   return mCorrelPente;
}

const cTplValGesInit< cCorrelPente > & cMesureCmptMnt::CorrelPente()const 
{
   return mCorrelPente;
}


cTplValGesInit< bool > & cMesureCmptMnt::EcartPente()
{
   return mEcartPente;
}

const cTplValGesInit< bool > & cMesureCmptMnt::EcartPente()const 
{
   return mEcartPente;
}

cElXMLTree * ToXMLTree(const cMesureCmptMnt & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"MesureCmptMnt",eXMLBranche);
   if (anObj.EcartZ().IsInit())
      aRes->AddFils(ToXMLTree(anObj.EcartZ().Val())->ReTagThis("EcartZ"));
   if (anObj.CorrelPente().IsInit())
      aRes->AddFils(ToXMLTree(anObj.CorrelPente().Val())->ReTagThis("CorrelPente"));
   if (anObj.EcartPente().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("EcartPente"),anObj.EcartPente().Val())->ReTagThis("EcartPente"));
  return aRes;
}

void xml_init(cMesureCmptMnt & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.EcartZ(),aTree->Get("EcartZ",1)); //tototo 

   xml_init(anObj.CorrelPente(),aTree->Get("CorrelPente",1)); //tototo 

   xml_init(anObj.EcartPente(),aTree->Get("EcartPente",1),bool(false)); //tototo 
}


Pt2dr & cCompareMNT::ResolutionPlaniTerrain()
{
   return mResolutionPlaniTerrain;
}

const Pt2dr & cCompareMNT::ResolutionPlaniTerrain()const 
{
   return mResolutionPlaniTerrain;
}


cTplValGesInit< int > & cCompareMNT::RabLoad()
{
   return mRabLoad;
}

const cTplValGesInit< int > & cCompareMNT::RabLoad()const 
{
   return mRabLoad;
}


std::string & cCompareMNT::NameFileRes()
{
   return mNameFileRes;
}

const std::string & cCompareMNT::NameFileRes()const 
{
   return mNameFileRes;
}


cTplValGesInit< bool > & cCompareMNT::VisuInter()
{
   return mVisuInter;
}

const cTplValGesInit< bool > & cCompareMNT::VisuInter()const 
{
   return mVisuInter;
}


std::list< cMNT2Cmp > & cCompareMNT::MNT2Cmp()
{
   return mMNT2Cmp;
}

const std::list< cMNT2Cmp > & cCompareMNT::MNT2Cmp()const 
{
   return mMNT2Cmp;
}


cTplValGesInit< std::string > & cCompareMNT::MasqGlobalCM()
{
   return mMasqGlobalCM;
}

const cTplValGesInit< std::string > & cCompareMNT::MasqGlobalCM()const 
{
   return mMasqGlobalCM;
}


std::list< cZoneCmpMnt > & cCompareMNT::ZoneCmpMnt()
{
   return mZoneCmpMnt;
}

const std::list< cZoneCmpMnt > & cCompareMNT::ZoneCmpMnt()const 
{
   return mZoneCmpMnt;
}


double & cCompareMNT::DynVisu()
{
   return MesureCmptMnt().EcartZ().Val().DynVisu();
}

const double & cCompareMNT::DynVisu()const 
{
   return MesureCmptMnt().EcartZ().Val().DynVisu();
}


cTplValGesInit< cEcartZ > & cCompareMNT::EcartZ()
{
   return MesureCmptMnt().EcartZ();
}

const cTplValGesInit< cEcartZ > & cCompareMNT::EcartZ()const 
{
   return MesureCmptMnt().EcartZ();
}


double & cCompareMNT::SzWCP()
{
   return MesureCmptMnt().CorrelPente().Val().SzWCP();
}

const double & cCompareMNT::SzWCP()const 
{
   return MesureCmptMnt().CorrelPente().Val().SzWCP();
}


double & cCompareMNT::GrMinCP()
{
   return MesureCmptMnt().CorrelPente().Val().GrMinCP();
}

const double & cCompareMNT::GrMinCP()const 
{
   return MesureCmptMnt().CorrelPente().Val().GrMinCP();
}


cTplValGesInit< cCorrelPente > & cCompareMNT::CorrelPente()
{
   return MesureCmptMnt().CorrelPente();
}

const cTplValGesInit< cCorrelPente > & cCompareMNT::CorrelPente()const 
{
   return MesureCmptMnt().CorrelPente();
}


cTplValGesInit< bool > & cCompareMNT::EcartPente()
{
   return MesureCmptMnt().EcartPente();
}

const cTplValGesInit< bool > & cCompareMNT::EcartPente()const 
{
   return MesureCmptMnt().EcartPente();
}


cMesureCmptMnt & cCompareMNT::MesureCmptMnt()
{
   return mMesureCmptMnt;
}

const cMesureCmptMnt & cCompareMNT::MesureCmptMnt()const 
{
   return mMesureCmptMnt;
}

cElXMLTree * ToXMLTree(const cCompareMNT & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CompareMNT",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("ResolutionPlaniTerrain"),anObj.ResolutionPlaniTerrain())->ReTagThis("ResolutionPlaniTerrain"));
   if (anObj.RabLoad().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("RabLoad"),anObj.RabLoad().Val())->ReTagThis("RabLoad"));
   aRes->AddFils(::ToXMLTree(std::string("NameFileRes"),anObj.NameFileRes())->ReTagThis("NameFileRes"));
   if (anObj.VisuInter().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("VisuInter"),anObj.VisuInter().Val())->ReTagThis("VisuInter"));
  for
  (       std::list< cMNT2Cmp >::const_iterator it=anObj.MNT2Cmp().begin();
      it !=anObj.MNT2Cmp().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("MNT2Cmp"));
   if (anObj.MasqGlobalCM().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("MasqGlobalCM"),anObj.MasqGlobalCM().Val())->ReTagThis("MasqGlobalCM"));
  for
  (       std::list< cZoneCmpMnt >::const_iterator it=anObj.ZoneCmpMnt().begin();
      it !=anObj.ZoneCmpMnt().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("ZoneCmpMnt"));
   aRes->AddFils(ToXMLTree(anObj.MesureCmptMnt())->ReTagThis("MesureCmptMnt"));
  return aRes;
}

void xml_init(cCompareMNT & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.ResolutionPlaniTerrain(),aTree->Get("ResolutionPlaniTerrain",1)); //tototo 

   xml_init(anObj.RabLoad(),aTree->Get("RabLoad",1),int(20)); //tototo 

   xml_init(anObj.NameFileRes(),aTree->Get("NameFileRes",1)); //tototo 

   xml_init(anObj.VisuInter(),aTree->Get("VisuInter",1),bool(false)); //tototo 

   xml_init(anObj.MNT2Cmp(),aTree->GetAll("MNT2Cmp",false,1));

   xml_init(anObj.MasqGlobalCM(),aTree->Get("MasqGlobalCM",1)); //tototo 

   xml_init(anObj.ZoneCmpMnt(),aTree->GetAll("ZoneCmpMnt",false,1));

   xml_init(anObj.MesureCmptMnt(),aTree->Get("MesureCmptMnt",1)); //tototo 
}


cTplValGesInit< double > & cDataBaseNameTransfo::AddFocMul()
{
   return mAddFocMul;
}

const cTplValGesInit< double > & cDataBaseNameTransfo::AddFocMul()const 
{
   return mAddFocMul;
}


cTplValGesInit< std::string > & cDataBaseNameTransfo::Separateur()
{
   return mSeparateur;
}

const cTplValGesInit< std::string > & cDataBaseNameTransfo::Separateur()const 
{
   return mSeparateur;
}

cElXMLTree * ToXMLTree(const cDataBaseNameTransfo & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"DataBaseNameTransfo",eXMLBranche);
   if (anObj.AddFocMul().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("AddFocMul"),anObj.AddFocMul().Val())->ReTagThis("AddFocMul"));
   if (anObj.Separateur().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Separateur"),anObj.Separateur().Val())->ReTagThis("Separateur"));
  return aRes;
}

void xml_init(cDataBaseNameTransfo & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.AddFocMul(),aTree->Get("AddFocMul",1)); //tototo 

   xml_init(anObj.Separateur(),aTree->Get("Separateur",1),std::string("%")); //tototo 
}


cTplValGesInit< std::string > & cInterpoleGrille::Directory()
{
   return mDirectory;
}

const cTplValGesInit< std::string > & cInterpoleGrille::Directory()const 
{
   return mDirectory;
}


std::string & cInterpoleGrille::Grille1()
{
   return mGrille1;
}

const std::string & cInterpoleGrille::Grille1()const 
{
   return mGrille1;
}


std::string & cInterpoleGrille::Grille2()
{
   return mGrille2;
}

const std::string & cInterpoleGrille::Grille2()const 
{
   return mGrille2;
}


std::string & cInterpoleGrille::Grille0()
{
   return mGrille0;
}

const std::string & cInterpoleGrille::Grille0()const 
{
   return mGrille0;
}


cTplValGesInit< Pt2dr > & cInterpoleGrille::StepGrid()
{
   return mStepGrid;
}

const cTplValGesInit< Pt2dr > & cInterpoleGrille::StepGrid()const 
{
   return mStepGrid;
}


double & cInterpoleGrille::Focale1()
{
   return mFocale1;
}

const double & cInterpoleGrille::Focale1()const 
{
   return mFocale1;
}


double & cInterpoleGrille::Focale2()
{
   return mFocale2;
}

const double & cInterpoleGrille::Focale2()const 
{
   return mFocale2;
}


double & cInterpoleGrille::Focale0()
{
   return mFocale0;
}

const double & cInterpoleGrille::Focale0()const 
{
   return mFocale0;
}


cTplValGesInit< int > & cInterpoleGrille::NbPtsByIter()
{
   return mNbPtsByIter;
}

const cTplValGesInit< int > & cInterpoleGrille::NbPtsByIter()const 
{
   return mNbPtsByIter;
}


cTplValGesInit< int > & cInterpoleGrille::DegPoly()
{
   return mDegPoly;
}

const cTplValGesInit< int > & cInterpoleGrille::DegPoly()const 
{
   return mDegPoly;
}


cTplValGesInit< eDegreLiberteCPP > & cInterpoleGrille::LiberteCPP()
{
   return mLiberteCPP;
}

const cTplValGesInit< eDegreLiberteCPP > & cInterpoleGrille::LiberteCPP()const 
{
   return mLiberteCPP;
}

cElXMLTree * ToXMLTree(const cInterpoleGrille & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"InterpoleGrille",eXMLBranche);
   if (anObj.Directory().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Directory"),anObj.Directory().Val())->ReTagThis("Directory"));
   aRes->AddFils(::ToXMLTree(std::string("Grille1"),anObj.Grille1())->ReTagThis("Grille1"));
   aRes->AddFils(::ToXMLTree(std::string("Grille2"),anObj.Grille2())->ReTagThis("Grille2"));
   aRes->AddFils(::ToXMLTree(std::string("Grille0"),anObj.Grille0())->ReTagThis("Grille0"));
   if (anObj.StepGrid().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("StepGrid"),anObj.StepGrid().Val())->ReTagThis("StepGrid"));
   aRes->AddFils(::ToXMLTree(std::string("Focale1"),anObj.Focale1())->ReTagThis("Focale1"));
   aRes->AddFils(::ToXMLTree(std::string("Focale2"),anObj.Focale2())->ReTagThis("Focale2"));
   aRes->AddFils(::ToXMLTree(std::string("Focale0"),anObj.Focale0())->ReTagThis("Focale0"));
   if (anObj.NbPtsByIter().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NbPtsByIter"),anObj.NbPtsByIter().Val())->ReTagThis("NbPtsByIter"));
   if (anObj.DegPoly().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("DegPoly"),anObj.DegPoly().Val())->ReTagThis("DegPoly"));
   if (anObj.LiberteCPP().IsInit())
      aRes->AddFils(ToXMLTree(std::string("LiberteCPP"),anObj.LiberteCPP().Val())->ReTagThis("LiberteCPP"));
  return aRes;
}

void xml_init(cInterpoleGrille & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Directory(),aTree->Get("Directory",1),std::string("")); //tototo 

   xml_init(anObj.Grille1(),aTree->Get("Grille1",1)); //tototo 

   xml_init(anObj.Grille2(),aTree->Get("Grille2",1)); //tototo 

   xml_init(anObj.Grille0(),aTree->Get("Grille0",1)); //tototo 

   xml_init(anObj.StepGrid(),aTree->Get("StepGrid",1)); //tototo 

   xml_init(anObj.Focale1(),aTree->Get("Focale1",1)); //tototo 

   xml_init(anObj.Focale2(),aTree->Get("Focale2",1)); //tototo 

   xml_init(anObj.Focale0(),aTree->Get("Focale0",1)); //tototo 

   xml_init(anObj.NbPtsByIter(),aTree->Get("NbPtsByIter",1),int(30)); //tototo 

   xml_init(anObj.DegPoly(),aTree->Get("DegPoly",1),int(3)); //tototo 

   xml_init(anObj.LiberteCPP(),aTree->Get("LiberteCPP",1),eDegreLiberteCPP(eCPPLibres)); //tototo 
}


std::string & cOneCalib2Visu::Name()
{
   return mName;
}

const std::string & cOneCalib2Visu::Name()const 
{
   return mName;
}


Pt3dr & cOneCalib2Visu::Coul()
{
   return mCoul;
}

const Pt3dr & cOneCalib2Visu::Coul()const 
{
   return mCoul;
}

cElXMLTree * ToXMLTree(const cOneCalib2Visu & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"OneCalib2Visu",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Name"),anObj.Name())->ReTagThis("Name"));
   aRes->AddFils(ToXMLTree(std::string("Coul"),anObj.Coul())->ReTagThis("Coul"));
  return aRes;
}

void xml_init(cOneCalib2Visu & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Name(),aTree->Get("Name",1)); //tototo 

   xml_init(anObj.Coul(),aTree->Get("Coul",1)); //tototo 
}


cTplValGesInit< std::string > & cVisuCalibZoom::Directory()
{
   return mDirectory;
}

const cTplValGesInit< std::string > & cVisuCalibZoom::Directory()const 
{
   return mDirectory;
}


Pt2dr & cVisuCalibZoom::SzIm()
{
   return mSzIm;
}

const Pt2dr & cVisuCalibZoom::SzIm()const 
{
   return mSzIm;
}


std::list< cOneCalib2Visu > & cVisuCalibZoom::OneCalib2Visu()
{
   return mOneCalib2Visu;
}

const std::list< cOneCalib2Visu > & cVisuCalibZoom::OneCalib2Visu()const 
{
   return mOneCalib2Visu;
}

cElXMLTree * ToXMLTree(const cVisuCalibZoom & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"VisuCalibZoom",eXMLBranche);
   if (anObj.Directory().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Directory"),anObj.Directory().Val())->ReTagThis("Directory"));
   aRes->AddFils(::ToXMLTree(std::string("SzIm"),anObj.SzIm())->ReTagThis("SzIm"));
  for
  (       std::list< cOneCalib2Visu >::const_iterator it=anObj.OneCalib2Visu().begin();
      it !=anObj.OneCalib2Visu().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("OneCalib2Visu"));
  return aRes;
}

void xml_init(cVisuCalibZoom & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Directory(),aTree->Get("Directory",1),std::string("")); //tototo 

   xml_init(anObj.SzIm(),aTree->Get("SzIm",1)); //tototo 

   xml_init(anObj.OneCalib2Visu(),aTree->GetAll("OneCalib2Visu",false,1));
}


std::string & cFilterLocalisation::KeyAssocOrient()
{
   return mKeyAssocOrient;
}

const std::string & cFilterLocalisation::KeyAssocOrient()const 
{
   return mKeyAssocOrient;
}


std::string & cFilterLocalisation::NameMasq()
{
   return mNameMasq;
}

const std::string & cFilterLocalisation::NameMasq()const 
{
   return mNameMasq;
}


std::string & cFilterLocalisation::NameMTDMasq()
{
   return mNameMTDMasq;
}

const std::string & cFilterLocalisation::NameMTDMasq()const 
{
   return mNameMTDMasq;
}

cElXMLTree * ToXMLTree(const cFilterLocalisation & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"FilterLocalisation",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("KeyAssocOrient"),anObj.KeyAssocOrient())->ReTagThis("KeyAssocOrient"));
   aRes->AddFils(::ToXMLTree(std::string("NameMasq"),anObj.NameMasq())->ReTagThis("NameMasq"));
   aRes->AddFils(::ToXMLTree(std::string("NameMTDMasq"),anObj.NameMTDMasq())->ReTagThis("NameMTDMasq"));
  return aRes;
}

void xml_init(cFilterLocalisation & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeyAssocOrient(),aTree->Get("KeyAssocOrient",1)); //tototo 

   xml_init(anObj.NameMasq(),aTree->Get("NameMasq",1)); //tototo 

   xml_init(anObj.NameMTDMasq(),aTree->Get("NameMTDMasq",1)); //tototo 
}


std::list< std::string > & cKeyExistingFile::KeyAssoc()
{
   return mKeyAssoc;
}

const std::list< std::string > & cKeyExistingFile::KeyAssoc()const 
{
   return mKeyAssoc;
}


bool & cKeyExistingFile::RequireExist()
{
   return mRequireExist;
}

const bool & cKeyExistingFile::RequireExist()const 
{
   return mRequireExist;
}


bool & cKeyExistingFile::RequireForAll()
{
   return mRequireForAll;
}

const bool & cKeyExistingFile::RequireForAll()const 
{
   return mRequireForAll;
}

cElXMLTree * ToXMLTree(const cKeyExistingFile & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"KeyExistingFile",eXMLBranche);
  for
  (       std::list< std::string >::const_iterator it=anObj.KeyAssoc().begin();
      it !=anObj.KeyAssoc().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("KeyAssoc"),(*it))->ReTagThis("KeyAssoc"));
   aRes->AddFils(::ToXMLTree(std::string("RequireExist"),anObj.RequireExist())->ReTagThis("RequireExist"));
   aRes->AddFils(::ToXMLTree(std::string("RequireForAll"),anObj.RequireForAll())->ReTagThis("RequireForAll"));
  return aRes;
}

void xml_init(cKeyExistingFile & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeyAssoc(),aTree->GetAll("KeyAssoc",false,1));

   xml_init(anObj.RequireExist(),aTree->Get("RequireExist",1)); //tototo 

   xml_init(anObj.RequireForAll(),aTree->Get("RequireForAll",1)); //tototo 
}


std::list< Pt2drSubst > & cNameFilter::FocMm()
{
   return mFocMm;
}

const std::list< Pt2drSubst > & cNameFilter::FocMm()const 
{
   return mFocMm;
}


cTplValGesInit< std::string > & cNameFilter::Min()
{
   return mMin;
}

const cTplValGesInit< std::string > & cNameFilter::Min()const 
{
   return mMin;
}


cTplValGesInit< std::string > & cNameFilter::Max()
{
   return mMax;
}

const cTplValGesInit< std::string > & cNameFilter::Max()const 
{
   return mMax;
}


cTplValGesInit< int > & cNameFilter::SizeMinFile()
{
   return mSizeMinFile;
}

const cTplValGesInit< int > & cNameFilter::SizeMinFile()const 
{
   return mSizeMinFile;
}


std::list< cKeyExistingFile > & cNameFilter::KeyExistingFile()
{
   return mKeyExistingFile;
}

const std::list< cKeyExistingFile > & cNameFilter::KeyExistingFile()const 
{
   return mKeyExistingFile;
}


cTplValGesInit< cFilterLocalisation > & cNameFilter::KeyLocalisation()
{
   return mKeyLocalisation;
}

const cTplValGesInit< cFilterLocalisation > & cNameFilter::KeyLocalisation()const 
{
   return mKeyLocalisation;
}

cElXMLTree * ToXMLTree(const cNameFilter & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"NameFilter",eXMLBranche);
  for
  (       std::list< Pt2drSubst >::const_iterator it=anObj.FocMm().begin();
      it !=anObj.FocMm().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("FocMm"),(*it))->ReTagThis("FocMm"));
   if (anObj.Min().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Min"),anObj.Min().Val())->ReTagThis("Min"));
   if (anObj.Max().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Max"),anObj.Max().Val())->ReTagThis("Max"));
   if (anObj.SizeMinFile().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("SizeMinFile"),anObj.SizeMinFile().Val())->ReTagThis("SizeMinFile"));
  for
  (       std::list< cKeyExistingFile >::const_iterator it=anObj.KeyExistingFile().begin();
      it !=anObj.KeyExistingFile().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("KeyExistingFile"));
   if (anObj.KeyLocalisation().IsInit())
      aRes->AddFils(ToXMLTree(anObj.KeyLocalisation().Val())->ReTagThis("KeyLocalisation"));
  return aRes;
}

void xml_init(cNameFilter & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.FocMm(),aTree->GetAll("FocMm",false,1));

   xml_init(anObj.Min(),aTree->Get("Min",1)); //tototo 

   xml_init(anObj.Max(),aTree->Get("Max",1)); //tototo 

   xml_init(anObj.SizeMinFile(),aTree->Get("SizeMinFile",1),int(-1)); //tototo 

   xml_init(anObj.KeyExistingFile(),aTree->GetAll("KeyExistingFile",false,1));

   xml_init(anObj.KeyLocalisation(),aTree->Get("KeyLocalisation",1)); //tototo 
}


std::string & cBasicAssocNameToName::PatternTransform()
{
   return mPatternTransform;
}

const std::string & cBasicAssocNameToName::PatternTransform()const 
{
   return mPatternTransform;
}


cTplValGesInit< cDataBaseNameTransfo > & cBasicAssocNameToName::NameTransfo()
{
   return mNameTransfo;
}

const cTplValGesInit< cDataBaseNameTransfo > & cBasicAssocNameToName::NameTransfo()const 
{
   return mNameTransfo;
}


cTplValGesInit< std::string > & cBasicAssocNameToName::PatternSelector()
{
   return mPatternSelector;
}

const cTplValGesInit< std::string > & cBasicAssocNameToName::PatternSelector()const 
{
   return mPatternSelector;
}


std::vector< std::string > & cBasicAssocNameToName::CalcName()
{
   return mCalcName;
}

const std::vector< std::string > & cBasicAssocNameToName::CalcName()const 
{
   return mCalcName;
}


cTplValGesInit< std::string > & cBasicAssocNameToName::Separateur()
{
   return mSeparateur;
}

const cTplValGesInit< std::string > & cBasicAssocNameToName::Separateur()const 
{
   return mSeparateur;
}


cTplValGesInit< cNameFilter > & cBasicAssocNameToName::Filter()
{
   return mFilter;
}

const cTplValGesInit< cNameFilter > & cBasicAssocNameToName::Filter()const 
{
   return mFilter;
}

cElXMLTree * ToXMLTree(const cBasicAssocNameToName & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"BasicAssocNameToName",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("PatternTransform"),anObj.PatternTransform())->ReTagThis("PatternTransform"));
   if (anObj.NameTransfo().IsInit())
      aRes->AddFils(ToXMLTree(anObj.NameTransfo().Val())->ReTagThis("NameTransfo"));
   if (anObj.PatternSelector().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("PatternSelector"),anObj.PatternSelector().Val())->ReTagThis("PatternSelector"));
  for
  (       std::vector< std::string >::const_iterator it=anObj.CalcName().begin();
      it !=anObj.CalcName().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("CalcName"),(*it))->ReTagThis("CalcName"));
   if (anObj.Separateur().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Separateur"),anObj.Separateur().Val())->ReTagThis("Separateur"));
   if (anObj.Filter().IsInit())
      aRes->AddFils(ToXMLTree(anObj.Filter().Val())->ReTagThis("Filter"));
  return aRes;
}

void xml_init(cBasicAssocNameToName & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.PatternTransform(),aTree->Get("PatternTransform",1)); //tototo 

   xml_init(anObj.NameTransfo(),aTree->Get("NameTransfo",1)); //tototo 

   xml_init(anObj.PatternSelector(),aTree->Get("PatternSelector",1)); //tototo 

   xml_init(anObj.CalcName(),aTree->GetAll("CalcName",false,1));

   xml_init(anObj.Separateur(),aTree->Get("Separateur",1),std::string("@")); //tototo 

   xml_init(anObj.Filter(),aTree->Get("Filter",1)); //tototo 
}


cTplValGesInit< Pt2di > & cAssocNameToName::Arrite()
{
   return mArrite;
}

const cTplValGesInit< Pt2di > & cAssocNameToName::Arrite()const 
{
   return mArrite;
}


cBasicAssocNameToName & cAssocNameToName::Direct()
{
   return mDirect;
}

const cBasicAssocNameToName & cAssocNameToName::Direct()const 
{
   return mDirect;
}


cTplValGesInit< cBasicAssocNameToName > & cAssocNameToName::Inverse()
{
   return mInverse;
}

const cTplValGesInit< cBasicAssocNameToName > & cAssocNameToName::Inverse()const 
{
   return mInverse;
}


cTplValGesInit< bool > & cAssocNameToName::AutoInverseBySym()
{
   return mAutoInverseBySym;
}

const cTplValGesInit< bool > & cAssocNameToName::AutoInverseBySym()const 
{
   return mAutoInverseBySym;
}

cElXMLTree * ToXMLTree(const cAssocNameToName & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"AssocNameToName",eXMLBranche);
   if (anObj.Arrite().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Arrite"),anObj.Arrite().Val())->ReTagThis("Arrite"));
   aRes->AddFils(ToXMLTree(anObj.Direct())->ReTagThis("Direct"));
   if (anObj.Inverse().IsInit())
      aRes->AddFils(ToXMLTree(anObj.Inverse().Val())->ReTagThis("Inverse"));
   if (anObj.AutoInverseBySym().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("AutoInverseBySym"),anObj.AutoInverseBySym().Val())->ReTagThis("AutoInverseBySym"));
  return aRes;
}

void xml_init(cAssocNameToName & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Arrite(),aTree->Get("Arrite",1)); //tototo 

   xml_init(anObj.Direct(),aTree->Get("Direct",1)); //tototo 

   xml_init(anObj.Inverse(),aTree->Get("Inverse",1)); //tototo 

   xml_init(anObj.AutoInverseBySym(),aTree->Get("AutoInverseBySym",1),bool(false)); //tototo 
}


cTplValGesInit< bool > & cSetNameDescriptor::AddDirCur()
{
   return mAddDirCur;
}

const cTplValGesInit< bool > & cSetNameDescriptor::AddDirCur()const 
{
   return mAddDirCur;
}


std::list< std::string > & cSetNameDescriptor::PatternAccepteur()
{
   return mPatternAccepteur;
}

const std::list< std::string > & cSetNameDescriptor::PatternAccepteur()const 
{
   return mPatternAccepteur;
}


std::list< std::string > & cSetNameDescriptor::PatternRefuteur()
{
   return mPatternRefuteur;
}

const std::list< std::string > & cSetNameDescriptor::PatternRefuteur()const 
{
   return mPatternRefuteur;
}


cTplValGesInit< int > & cSetNameDescriptor::NivSubDir()
{
   return mNivSubDir;
}

const cTplValGesInit< int > & cSetNameDescriptor::NivSubDir()const 
{
   return mNivSubDir;
}


cTplValGesInit< bool > & cSetNameDescriptor::NameCompl()
{
   return mNameCompl;
}

const cTplValGesInit< bool > & cSetNameDescriptor::NameCompl()const 
{
   return mNameCompl;
}


cTplValGesInit< std::string > & cSetNameDescriptor::SubDir()
{
   return mSubDir;
}

const cTplValGesInit< std::string > & cSetNameDescriptor::SubDir()const 
{
   return mSubDir;
}


std::list< std::string > & cSetNameDescriptor::Name()
{
   return mName;
}

const std::list< std::string > & cSetNameDescriptor::Name()const 
{
   return mName;
}


cTplValGesInit< std::string > & cSetNameDescriptor::Min()
{
   return mMin;
}

const cTplValGesInit< std::string > & cSetNameDescriptor::Min()const 
{
   return mMin;
}


cTplValGesInit< std::string > & cSetNameDescriptor::Max()
{
   return mMax;
}

const cTplValGesInit< std::string > & cSetNameDescriptor::Max()const 
{
   return mMax;
}


cTplValGesInit< cNameFilter > & cSetNameDescriptor::Filter()
{
   return mFilter;
}

const cTplValGesInit< cNameFilter > & cSetNameDescriptor::Filter()const 
{
   return mFilter;
}

cElXMLTree * ToXMLTree(const cSetNameDescriptor & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"SetNameDescriptor",eXMLBranche);
   if (anObj.AddDirCur().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("AddDirCur"),anObj.AddDirCur().Val())->ReTagThis("AddDirCur"));
  for
  (       std::list< std::string >::const_iterator it=anObj.PatternAccepteur().begin();
      it !=anObj.PatternAccepteur().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("PatternAccepteur"),(*it))->ReTagThis("PatternAccepteur"));
  for
  (       std::list< std::string >::const_iterator it=anObj.PatternRefuteur().begin();
      it !=anObj.PatternRefuteur().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("PatternRefuteur"),(*it))->ReTagThis("PatternRefuteur"));
   if (anObj.NivSubDir().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NivSubDir"),anObj.NivSubDir().Val())->ReTagThis("NivSubDir"));
   if (anObj.NameCompl().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NameCompl"),anObj.NameCompl().Val())->ReTagThis("NameCompl"));
   if (anObj.SubDir().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("SubDir"),anObj.SubDir().Val())->ReTagThis("SubDir"));
  for
  (       std::list< std::string >::const_iterator it=anObj.Name().begin();
      it !=anObj.Name().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Name"),(*it))->ReTagThis("Name"));
   if (anObj.Min().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Min"),anObj.Min().Val())->ReTagThis("Min"));
   if (anObj.Max().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Max"),anObj.Max().Val())->ReTagThis("Max"));
   if (anObj.Filter().IsInit())
      aRes->AddFils(ToXMLTree(anObj.Filter().Val())->ReTagThis("Filter"));
  return aRes;
}

void xml_init(cSetNameDescriptor & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.AddDirCur(),aTree->Get("AddDirCur",1),bool(true)); //tototo 

   xml_init(anObj.PatternAccepteur(),aTree->GetAll("PatternAccepteur",false,1));

   xml_init(anObj.PatternRefuteur(),aTree->GetAll("PatternRefuteur",false,1));

   xml_init(anObj.NivSubDir(),aTree->Get("NivSubDir",1),int(1)); //tototo 

   xml_init(anObj.NameCompl(),aTree->Get("NameCompl",1),bool(false)); //tototo 

   xml_init(anObj.SubDir(),aTree->Get("SubDir",1),std::string("")); //tototo 

   xml_init(anObj.Name(),aTree->GetAll("Name",false,1));

   xml_init(anObj.Min(),aTree->Get("Min",1)); //tototo 

   xml_init(anObj.Max(),aTree->Get("Max",1)); //tototo 

   xml_init(anObj.Filter(),aTree->Get("Filter",1)); //tototo 
}


std::string & cImMatrixStructuration::KeySet()
{
   return mKeySet;
}

const std::string & cImMatrixStructuration::KeySet()const 
{
   return mKeySet;
}


Pt2di & cImMatrixStructuration::Period()
{
   return mPeriod;
}

const Pt2di & cImMatrixStructuration::Period()const 
{
   return mPeriod;
}


bool & cImMatrixStructuration::XCroissants()
{
   return mXCroissants;
}

const bool & cImMatrixStructuration::XCroissants()const 
{
   return mXCroissants;
}


bool & cImMatrixStructuration::YCroissants()
{
   return mYCroissants;
}

const bool & cImMatrixStructuration::YCroissants()const 
{
   return mYCroissants;
}


bool & cImMatrixStructuration::XVarieFirst()
{
   return mXVarieFirst;
}

const bool & cImMatrixStructuration::XVarieFirst()const 
{
   return mXVarieFirst;
}

cElXMLTree * ToXMLTree(const cImMatrixStructuration & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ImMatrixStructuration",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("KeySet"),anObj.KeySet())->ReTagThis("KeySet"));
   aRes->AddFils(::ToXMLTree(std::string("Period"),anObj.Period())->ReTagThis("Period"));
   aRes->AddFils(::ToXMLTree(std::string("XCroissants"),anObj.XCroissants())->ReTagThis("XCroissants"));
   aRes->AddFils(::ToXMLTree(std::string("YCroissants"),anObj.YCroissants())->ReTagThis("YCroissants"));
   aRes->AddFils(::ToXMLTree(std::string("XVarieFirst"),anObj.XVarieFirst())->ReTagThis("XVarieFirst"));
  return aRes;
}

void xml_init(cImMatrixStructuration & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeySet(),aTree->Get("KeySet",1)); //tototo 

   xml_init(anObj.Period(),aTree->Get("Period",1)); //tototo 

   xml_init(anObj.XCroissants(),aTree->Get("XCroissants",1)); //tototo 

   xml_init(anObj.YCroissants(),aTree->Get("YCroissants",1)); //tototo 

   xml_init(anObj.XVarieFirst(),aTree->Get("XVarieFirst",1)); //tototo 
}


std::string & cFiltreEmprise::KeyOri()
{
   return mKeyOri;
}

const std::string & cFiltreEmprise::KeyOri()const 
{
   return mKeyOri;
}


double & cFiltreEmprise::RatioMin()
{
   return mRatioMin;
}

const double & cFiltreEmprise::RatioMin()const 
{
   return mRatioMin;
}


cTplValGesInit< bool > & cFiltreEmprise::MemoFile()
{
   return mMemoFile;
}

const cTplValGesInit< bool > & cFiltreEmprise::MemoFile()const 
{
   return mMemoFile;
}


cTplValGesInit< std::string > & cFiltreEmprise::Tag()
{
   return mTag;
}

const cTplValGesInit< std::string > & cFiltreEmprise::Tag()const 
{
   return mTag;
}

cElXMLTree * ToXMLTree(const cFiltreEmprise & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"FiltreEmprise",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("KeyOri"),anObj.KeyOri())->ReTagThis("KeyOri"));
   aRes->AddFils(::ToXMLTree(std::string("RatioMin"),anObj.RatioMin())->ReTagThis("RatioMin"));
   if (anObj.MemoFile().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("MemoFile"),anObj.MemoFile().Val())->ReTagThis("MemoFile"));
   if (anObj.Tag().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Tag"),anObj.Tag().Val())->ReTagThis("Tag"));
  return aRes;
}

void xml_init(cFiltreEmprise & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeyOri(),aTree->Get("KeyOri",1)); //tototo 

   xml_init(anObj.RatioMin(),aTree->Get("RatioMin",1)); //tototo 

   xml_init(anObj.MemoFile(),aTree->Get("MemoFile",1),bool(true)); //tototo 

   xml_init(anObj.Tag(),aTree->Get("Tag",1),std::string("OrientationConique")); //tototo 
}


std::string & cFiltreByRelSsEch::KeySet()
{
   return mKeySet;
}

const std::string & cFiltreByRelSsEch::KeySet()const 
{
   return mKeySet;
}


std::string & cFiltreByRelSsEch::KeyAssocCple()
{
   return mKeyAssocCple;
}

const std::string & cFiltreByRelSsEch::KeyAssocCple()const 
{
   return mKeyAssocCple;
}


IntSubst & cFiltreByRelSsEch::SeuilBasNbPts()
{
   return mSeuilBasNbPts;
}

const IntSubst & cFiltreByRelSsEch::SeuilBasNbPts()const 
{
   return mSeuilBasNbPts;
}


IntSubst & cFiltreByRelSsEch::SeuilHautNbPts()
{
   return mSeuilHautNbPts;
}

const IntSubst & cFiltreByRelSsEch::SeuilHautNbPts()const 
{
   return mSeuilHautNbPts;
}


IntSubst & cFiltreByRelSsEch::NbMinCple()
{
   return mNbMinCple;
}

const IntSubst & cFiltreByRelSsEch::NbMinCple()const 
{
   return mNbMinCple;
}

cElXMLTree * ToXMLTree(const cFiltreByRelSsEch & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"FiltreByRelSsEch",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("KeySet"),anObj.KeySet())->ReTagThis("KeySet"));
   aRes->AddFils(::ToXMLTree(std::string("KeyAssocCple"),anObj.KeyAssocCple())->ReTagThis("KeyAssocCple"));
   aRes->AddFils(::ToXMLTree(std::string("SeuilBasNbPts"),anObj.SeuilBasNbPts())->ReTagThis("SeuilBasNbPts"));
   aRes->AddFils(::ToXMLTree(std::string("SeuilHautNbPts"),anObj.SeuilHautNbPts())->ReTagThis("SeuilHautNbPts"));
   aRes->AddFils(::ToXMLTree(std::string("NbMinCple"),anObj.NbMinCple())->ReTagThis("NbMinCple"));
  return aRes;
}

void xml_init(cFiltreByRelSsEch & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeySet(),aTree->Get("KeySet",1)); //tototo 

   xml_init(anObj.KeyAssocCple(),aTree->Get("KeyAssocCple",1)); //tototo 

   xml_init(anObj.SeuilBasNbPts(),aTree->Get("SeuilBasNbPts",1)); //tototo 

   xml_init(anObj.SeuilHautNbPts(),aTree->Get("SeuilHautNbPts",1)); //tototo 

   xml_init(anObj.NbMinCple(),aTree->Get("NbMinCple",1)); //tototo 
}


cTplValGesInit< std::string > & cFiltreDeRelationOrient::KeyEquiv()
{
   return mKeyEquiv;
}

const cTplValGesInit< std::string > & cFiltreDeRelationOrient::KeyEquiv()const 
{
   return mKeyEquiv;
}


std::string & cFiltreDeRelationOrient::KeyOri()
{
   return FiltreEmprise().Val().KeyOri();
}

const std::string & cFiltreDeRelationOrient::KeyOri()const 
{
   return FiltreEmprise().Val().KeyOri();
}


double & cFiltreDeRelationOrient::RatioMin()
{
   return FiltreEmprise().Val().RatioMin();
}

const double & cFiltreDeRelationOrient::RatioMin()const 
{
   return FiltreEmprise().Val().RatioMin();
}


cTplValGesInit< bool > & cFiltreDeRelationOrient::MemoFile()
{
   return FiltreEmprise().Val().MemoFile();
}

const cTplValGesInit< bool > & cFiltreDeRelationOrient::MemoFile()const 
{
   return FiltreEmprise().Val().MemoFile();
}


cTplValGesInit< std::string > & cFiltreDeRelationOrient::Tag()
{
   return FiltreEmprise().Val().Tag();
}

const cTplValGesInit< std::string > & cFiltreDeRelationOrient::Tag()const 
{
   return FiltreEmprise().Val().Tag();
}


cTplValGesInit< cFiltreEmprise > & cFiltreDeRelationOrient::FiltreEmprise()
{
   return mFiltreEmprise;
}

const cTplValGesInit< cFiltreEmprise > & cFiltreDeRelationOrient::FiltreEmprise()const 
{
   return mFiltreEmprise;
}


cTplValGesInit< std::string > & cFiltreDeRelationOrient::FiltreAdjMatrix()
{
   return mFiltreAdjMatrix;
}

const cTplValGesInit< std::string > & cFiltreDeRelationOrient::FiltreAdjMatrix()const 
{
   return mFiltreAdjMatrix;
}


cTplValGesInit< Pt2di > & cFiltreDeRelationOrient::EcartFiltreMatr()
{
   return mEcartFiltreMatr;
}

const cTplValGesInit< Pt2di > & cFiltreDeRelationOrient::EcartFiltreMatr()const 
{
   return mEcartFiltreMatr;
}


std::string & cFiltreDeRelationOrient::KeySet()
{
   return FiltreByRelSsEch().Val().KeySet();
}

const std::string & cFiltreDeRelationOrient::KeySet()const 
{
   return FiltreByRelSsEch().Val().KeySet();
}


std::string & cFiltreDeRelationOrient::KeyAssocCple()
{
   return FiltreByRelSsEch().Val().KeyAssocCple();
}

const std::string & cFiltreDeRelationOrient::KeyAssocCple()const 
{
   return FiltreByRelSsEch().Val().KeyAssocCple();
}


IntSubst & cFiltreDeRelationOrient::SeuilBasNbPts()
{
   return FiltreByRelSsEch().Val().SeuilBasNbPts();
}

const IntSubst & cFiltreDeRelationOrient::SeuilBasNbPts()const 
{
   return FiltreByRelSsEch().Val().SeuilBasNbPts();
}


IntSubst & cFiltreDeRelationOrient::SeuilHautNbPts()
{
   return FiltreByRelSsEch().Val().SeuilHautNbPts();
}

const IntSubst & cFiltreDeRelationOrient::SeuilHautNbPts()const 
{
   return FiltreByRelSsEch().Val().SeuilHautNbPts();
}


IntSubst & cFiltreDeRelationOrient::NbMinCple()
{
   return FiltreByRelSsEch().Val().NbMinCple();
}

const IntSubst & cFiltreDeRelationOrient::NbMinCple()const 
{
   return FiltreByRelSsEch().Val().NbMinCple();
}


cTplValGesInit< cFiltreByRelSsEch > & cFiltreDeRelationOrient::FiltreByRelSsEch()
{
   return mFiltreByRelSsEch;
}

const cTplValGesInit< cFiltreByRelSsEch > & cFiltreDeRelationOrient::FiltreByRelSsEch()const 
{
   return mFiltreByRelSsEch;
}

cElXMLTree * ToXMLTree(const cFiltreDeRelationOrient & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"FiltreDeRelationOrient",eXMLBranche);
   if (anObj.KeyEquiv().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("KeyEquiv"),anObj.KeyEquiv().Val())->ReTagThis("KeyEquiv"));
   if (anObj.FiltreEmprise().IsInit())
      aRes->AddFils(ToXMLTree(anObj.FiltreEmprise().Val())->ReTagThis("FiltreEmprise"));
   if (anObj.FiltreAdjMatrix().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("FiltreAdjMatrix"),anObj.FiltreAdjMatrix().Val())->ReTagThis("FiltreAdjMatrix"));
   if (anObj.EcartFiltreMatr().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("EcartFiltreMatr"),anObj.EcartFiltreMatr().Val())->ReTagThis("EcartFiltreMatr"));
   if (anObj.FiltreByRelSsEch().IsInit())
      aRes->AddFils(ToXMLTree(anObj.FiltreByRelSsEch().Val())->ReTagThis("FiltreByRelSsEch"));
  return aRes;
}

void xml_init(cFiltreDeRelationOrient & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeyEquiv(),aTree->Get("KeyEquiv",1)); //tototo 

   xml_init(anObj.FiltreEmprise(),aTree->Get("FiltreEmprise",1)); //tototo 

   xml_init(anObj.FiltreAdjMatrix(),aTree->Get("FiltreAdjMatrix",1)); //tototo 

   xml_init(anObj.EcartFiltreMatr(),aTree->Get("EcartFiltreMatr",1),Pt2di(1,1)); //tototo 

   xml_init(anObj.FiltreByRelSsEch(),aTree->Get("FiltreByRelSsEch",1)); //tototo 
}


std::vector< cCpleString > & cSauvegardeNamedRel::Cple()
{
   return mCple;
}

const std::vector< cCpleString > & cSauvegardeNamedRel::Cple()const 
{
   return mCple;
}

cElXMLTree * ToXMLTree(const cSauvegardeNamedRel & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"SauvegardeNamedRel",eXMLBranche);
  for
  (       std::vector< cCpleString >::const_iterator it=anObj.Cple().begin();
      it !=anObj.Cple().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Cple"),(*it))->ReTagThis("Cple"));
  return aRes;
}

void xml_init(cSauvegardeNamedRel & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Cple(),aTree->GetAll("Cple",false,1));
}


std::list< std::string > & cSauvegardeSetString::Name()
{
   return mName;
}

const std::list< std::string > & cSauvegardeSetString::Name()const 
{
   return mName;
}

cElXMLTree * ToXMLTree(const cSauvegardeSetString & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"SauvegardeSetString",eXMLBranche);
  for
  (       std::list< std::string >::const_iterator it=anObj.Name().begin();
      it !=anObj.Name().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Name"),(*it))->ReTagThis("Name"));
  return aRes;
}

void xml_init(cSauvegardeSetString & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Name(),aTree->GetAll("Name",false,1));
}


std::string & cClassEquivDescripteur::KeySet()
{
   return mKeySet;
}

const std::string & cClassEquivDescripteur::KeySet()const 
{
   return mKeySet;
}


std::string & cClassEquivDescripteur::KeyAssocRep()
{
   return mKeyAssocRep;
}

const std::string & cClassEquivDescripteur::KeyAssocRep()const 
{
   return mKeyAssocRep;
}


std::string & cClassEquivDescripteur::KeyClass()
{
   return mKeyClass;
}

const std::string & cClassEquivDescripteur::KeyClass()const 
{
   return mKeyClass;
}

cElXMLTree * ToXMLTree(const cClassEquivDescripteur & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ClassEquivDescripteur",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("KeySet"),anObj.KeySet())->ReTagThis("KeySet"));
   aRes->AddFils(::ToXMLTree(std::string("KeyAssocRep"),anObj.KeyAssocRep())->ReTagThis("KeyAssocRep"));
   aRes->AddFils(::ToXMLTree(std::string("KeyClass"),anObj.KeyClass())->ReTagThis("KeyClass"));
  return aRes;
}

void xml_init(cClassEquivDescripteur & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeySet(),aTree->Get("KeySet",1)); //tototo 

   xml_init(anObj.KeyAssocRep(),aTree->Get("KeyAssocRep",1)); //tototo 

   xml_init(anObj.KeyClass(),aTree->Get("KeyClass",1)); //tototo 
}


std::vector<std::string> & cOneSpecDelta::Soms()
{
   return mSoms;
}

const std::vector<std::string> & cOneSpecDelta::Soms()const 
{
   return mSoms;
}


std::vector<int>  & cOneSpecDelta::Delta()
{
   return mDelta;
}

const std::vector<int>  & cOneSpecDelta::Delta()const 
{
   return mDelta;
}

cElXMLTree * ToXMLTree(const cOneSpecDelta & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"OneSpecDelta",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Soms"),anObj.Soms())->ReTagThis("Soms"));
   aRes->AddFils(::ToXMLTree(std::string("Delta"),anObj.Delta())->ReTagThis("Delta"));
  return aRes;
}

void xml_init(cOneSpecDelta & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Soms(),aTree->Get("Soms",1)); //tototo 

   xml_init(anObj.Delta(),aTree->Get("Delta",1)); //tototo 
}


std::string & cGrByDelta::KeySet()
{
   return mKeySet;
}

const std::string & cGrByDelta::KeySet()const 
{
   return mKeySet;
}


std::list< cOneSpecDelta > & cGrByDelta::OneSpecDelta()
{
   return mOneSpecDelta;
}

const std::list< cOneSpecDelta > & cGrByDelta::OneSpecDelta()const 
{
   return mOneSpecDelta;
}

cElXMLTree * ToXMLTree(const cGrByDelta & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"GrByDelta",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("KeySet"),anObj.KeySet())->ReTagThis("KeySet"));
  for
  (       std::list< cOneSpecDelta >::const_iterator it=anObj.OneSpecDelta().begin();
      it !=anObj.OneSpecDelta().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("OneSpecDelta"));
  return aRes;
}

void xml_init(cGrByDelta & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeySet(),aTree->Get("KeySet",1)); //tototo 

   xml_init(anObj.OneSpecDelta(),aTree->GetAll("OneSpecDelta",false,1));
}


std::list< cCpleString > & cRelByGrapheExpl::Cples()
{
   return mCples;
}

const std::list< cCpleString > & cRelByGrapheExpl::Cples()const 
{
   return mCples;
}


std::list< std::vector<std::string> > & cRelByGrapheExpl::CpleSymWithFirt()
{
   return mCpleSymWithFirt;
}

const std::list< std::vector<std::string> > & cRelByGrapheExpl::CpleSymWithFirt()const 
{
   return mCpleSymWithFirt;
}


std::list< std::vector<std::string> > & cRelByGrapheExpl::ProdCartesien()
{
   return mProdCartesien;
}

const std::list< std::vector<std::string> > & cRelByGrapheExpl::ProdCartesien()const 
{
   return mProdCartesien;
}


cTplValGesInit< std::string > & cRelByGrapheExpl::Prefix2Name()
{
   return mPrefix2Name;
}

const cTplValGesInit< std::string > & cRelByGrapheExpl::Prefix2Name()const 
{
   return mPrefix2Name;
}


cTplValGesInit< std::string > & cRelByGrapheExpl::Postfix2Name()
{
   return mPostfix2Name;
}

const cTplValGesInit< std::string > & cRelByGrapheExpl::Postfix2Name()const 
{
   return mPostfix2Name;
}


std::list< cGrByDelta > & cRelByGrapheExpl::GrByDelta()
{
   return mGrByDelta;
}

const std::list< cGrByDelta > & cRelByGrapheExpl::GrByDelta()const 
{
   return mGrByDelta;
}

cElXMLTree * ToXMLTree(const cRelByGrapheExpl & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"RelByGrapheExpl",eXMLBranche);
  for
  (       std::list< cCpleString >::const_iterator it=anObj.Cples().begin();
      it !=anObj.Cples().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Cples"),(*it))->ReTagThis("Cples"));
  for
  (       std::list< std::vector<std::string> >::const_iterator it=anObj.CpleSymWithFirt().begin();
      it !=anObj.CpleSymWithFirt().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("CpleSymWithFirt"),(*it))->ReTagThis("CpleSymWithFirt"));
  for
  (       std::list< std::vector<std::string> >::const_iterator it=anObj.ProdCartesien().begin();
      it !=anObj.ProdCartesien().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("ProdCartesien"),(*it))->ReTagThis("ProdCartesien"));
   if (anObj.Prefix2Name().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Prefix2Name"),anObj.Prefix2Name().Val())->ReTagThis("Prefix2Name"));
   if (anObj.Postfix2Name().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Postfix2Name"),anObj.Postfix2Name().Val())->ReTagThis("Postfix2Name"));
  for
  (       std::list< cGrByDelta >::const_iterator it=anObj.GrByDelta().begin();
      it !=anObj.GrByDelta().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("GrByDelta"));
  return aRes;
}

void xml_init(cRelByGrapheExpl & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Cples(),aTree->GetAll("Cples",false,1));

   xml_init(anObj.CpleSymWithFirt(),aTree->GetAll("CpleSymWithFirt",false,1));

   xml_init(anObj.ProdCartesien(),aTree->GetAll("ProdCartesien",false,1));

   xml_init(anObj.Prefix2Name(),aTree->Get("Prefix2Name",1)); //tototo 

   xml_init(anObj.Postfix2Name(),aTree->Get("Postfix2Name",1)); //tototo 

   xml_init(anObj.GrByDelta(),aTree->GetAll("GrByDelta",false,1));
}


std::vector< std::string > & cByAdjDeGroupes::KeySets()
{
   return mKeySets;
}

const std::vector< std::string > & cByAdjDeGroupes::KeySets()const 
{
   return mKeySets;
}


int & cByAdjDeGroupes::DeltaMin()
{
   return mDeltaMin;
}

const int & cByAdjDeGroupes::DeltaMin()const 
{
   return mDeltaMin;
}


int & cByAdjDeGroupes::DeltaMax()
{
   return mDeltaMax;
}

const int & cByAdjDeGroupes::DeltaMax()const 
{
   return mDeltaMax;
}

cElXMLTree * ToXMLTree(const cByAdjDeGroupes & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ByAdjDeGroupes",eXMLBranche);
  for
  (       std::vector< std::string >::const_iterator it=anObj.KeySets().begin();
      it !=anObj.KeySets().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("KeySets"),(*it))->ReTagThis("KeySets"));
   aRes->AddFils(::ToXMLTree(std::string("DeltaMin"),anObj.DeltaMin())->ReTagThis("DeltaMin"));
   aRes->AddFils(::ToXMLTree(std::string("DeltaMax"),anObj.DeltaMax())->ReTagThis("DeltaMax"));
  return aRes;
}

void xml_init(cByAdjDeGroupes & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeySets(),aTree->GetAll("KeySets",false,1));

   xml_init(anObj.DeltaMin(),aTree->Get("DeltaMin",1)); //tototo 

   xml_init(anObj.DeltaMax(),aTree->Get("DeltaMax",1)); //tototo 
}


std::list< cCpleString > & cByGroupesDImages::CplesKey()
{
   return mCplesKey;
}

const std::list< cCpleString > & cByGroupesDImages::CplesKey()const 
{
   return mCplesKey;
}


std::list< cByAdjDeGroupes > & cByGroupesDImages::ByAdjDeGroupes()
{
   return mByAdjDeGroupes;
}

const std::list< cByAdjDeGroupes > & cByGroupesDImages::ByAdjDeGroupes()const 
{
   return mByAdjDeGroupes;
}


cTplValGesInit< cFiltreDeRelationOrient > & cByGroupesDImages::Filtre()
{
   return mFiltre;
}

const cTplValGesInit< cFiltreDeRelationOrient > & cByGroupesDImages::Filtre()const 
{
   return mFiltre;
}


cTplValGesInit< bool > & cByGroupesDImages::Sym()
{
   return mSym;
}

const cTplValGesInit< bool > & cByGroupesDImages::Sym()const 
{
   return mSym;
}


cTplValGesInit< bool > & cByGroupesDImages::Reflexif()
{
   return mReflexif;
}

const cTplValGesInit< bool > & cByGroupesDImages::Reflexif()const 
{
   return mReflexif;
}

cElXMLTree * ToXMLTree(const cByGroupesDImages & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ByGroupesDImages",eXMLBranche);
  for
  (       std::list< cCpleString >::const_iterator it=anObj.CplesKey().begin();
      it !=anObj.CplesKey().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("CplesKey"),(*it))->ReTagThis("CplesKey"));
  for
  (       std::list< cByAdjDeGroupes >::const_iterator it=anObj.ByAdjDeGroupes().begin();
      it !=anObj.ByAdjDeGroupes().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("ByAdjDeGroupes"));
   if (anObj.Filtre().IsInit())
      aRes->AddFils(ToXMLTree(anObj.Filtre().Val())->ReTagThis("Filtre"));
   if (anObj.Sym().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Sym"),anObj.Sym().Val())->ReTagThis("Sym"));
   if (anObj.Reflexif().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Reflexif"),anObj.Reflexif().Val())->ReTagThis("Reflexif"));
  return aRes;
}

void xml_init(cByGroupesDImages & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.CplesKey(),aTree->GetAll("CplesKey",false,1));

   xml_init(anObj.ByAdjDeGroupes(),aTree->GetAll("ByAdjDeGroupes",false,1));

   xml_init(anObj.Filtre(),aTree->Get("Filtre",1)); //tototo 

   xml_init(anObj.Sym(),aTree->Get("Sym",1),bool(true)); //tototo 

   xml_init(anObj.Reflexif(),aTree->Get("Reflexif",1),bool(false)); //tototo 
}


cTplValGesInit< double > & cFiltreDelaunay::DMaxDelaunay()
{
   return mDMaxDelaunay;
}

const cTplValGesInit< double > & cFiltreDelaunay::DMaxDelaunay()const 
{
   return mDMaxDelaunay;
}

cElXMLTree * ToXMLTree(const cFiltreDelaunay & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"FiltreDelaunay",eXMLBranche);
   if (anObj.DMaxDelaunay().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("DMaxDelaunay"),anObj.DMaxDelaunay().Val())->ReTagThis("DMaxDelaunay"));
  return aRes;
}

void xml_init(cFiltreDelaunay & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.DMaxDelaunay(),aTree->Get("DMaxDelaunay",1),double(1e9)); //tototo 
}


double & cFiltreDist::DistMax()
{
   return mDistMax;
}

const double & cFiltreDist::DistMax()const 
{
   return mDistMax;
}

cElXMLTree * ToXMLTree(const cFiltreDist & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"FiltreDist",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("DistMax"),anObj.DistMax())->ReTagThis("DistMax"));
  return aRes;
}

void xml_init(cFiltreDist & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.DistMax(),aTree->Get("DistMax",1)); //tototo 
}


cTplValGesInit< double > & cModeFiltreSpatial::DMaxDelaunay()
{
   return FiltreDelaunay().Val().DMaxDelaunay();
}

const cTplValGesInit< double > & cModeFiltreSpatial::DMaxDelaunay()const 
{
   return FiltreDelaunay().Val().DMaxDelaunay();
}


cTplValGesInit< cFiltreDelaunay > & cModeFiltreSpatial::FiltreDelaunay()
{
   return mFiltreDelaunay;
}

const cTplValGesInit< cFiltreDelaunay > & cModeFiltreSpatial::FiltreDelaunay()const 
{
   return mFiltreDelaunay;
}


double & cModeFiltreSpatial::DistMax()
{
   return FiltreDist().Val().DistMax();
}

const double & cModeFiltreSpatial::DistMax()const 
{
   return FiltreDist().Val().DistMax();
}


cTplValGesInit< cFiltreDist > & cModeFiltreSpatial::FiltreDist()
{
   return mFiltreDist;
}

const cTplValGesInit< cFiltreDist > & cModeFiltreSpatial::FiltreDist()const 
{
   return mFiltreDist;
}

cElXMLTree * ToXMLTree(const cModeFiltreSpatial & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ModeFiltreSpatial",eXMLBranche);
   if (anObj.FiltreDelaunay().IsInit())
      aRes->AddFils(ToXMLTree(anObj.FiltreDelaunay().Val())->ReTagThis("FiltreDelaunay"));
   if (anObj.FiltreDist().IsInit())
      aRes->AddFils(ToXMLTree(anObj.FiltreDist().Val())->ReTagThis("FiltreDist"));
  return aRes;
}

void xml_init(cModeFiltreSpatial & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.FiltreDelaunay(),aTree->Get("FiltreDelaunay",1)); //tototo 

   xml_init(anObj.FiltreDist(),aTree->Get("FiltreDist",1)); //tototo 
}


cTplValGesInit< std::string > & cByFiltreSpatial::ByFileTrajecto()
{
   return mByFileTrajecto;
}

const cTplValGesInit< std::string > & cByFiltreSpatial::ByFileTrajecto()const 
{
   return mByFileTrajecto;
}


std::string & cByFiltreSpatial::KeyOri()
{
   return mKeyOri;
}

const std::string & cByFiltreSpatial::KeyOri()const 
{
   return mKeyOri;
}


std::string & cByFiltreSpatial::KeySet()
{
   return mKeySet;
}

const std::string & cByFiltreSpatial::KeySet()const 
{
   return mKeySet;
}


cTplValGesInit< std::string > & cByFiltreSpatial::TagCentre()
{
   return mTagCentre;
}

const cTplValGesInit< std::string > & cByFiltreSpatial::TagCentre()const 
{
   return mTagCentre;
}


cTplValGesInit< bool > & cByFiltreSpatial::Sym()
{
   return mSym;
}

const cTplValGesInit< bool > & cByFiltreSpatial::Sym()const 
{
   return mSym;
}


cTplValGesInit< cFiltreDeRelationOrient > & cByFiltreSpatial::FiltreSup()
{
   return mFiltreSup;
}

const cTplValGesInit< cFiltreDeRelationOrient > & cByFiltreSpatial::FiltreSup()const 
{
   return mFiltreSup;
}


cTplValGesInit< double > & cByFiltreSpatial::DMaxDelaunay()
{
   return ModeFiltreSpatial().FiltreDelaunay().Val().DMaxDelaunay();
}

const cTplValGesInit< double > & cByFiltreSpatial::DMaxDelaunay()const 
{
   return ModeFiltreSpatial().FiltreDelaunay().Val().DMaxDelaunay();
}


cTplValGesInit< cFiltreDelaunay > & cByFiltreSpatial::FiltreDelaunay()
{
   return ModeFiltreSpatial().FiltreDelaunay();
}

const cTplValGesInit< cFiltreDelaunay > & cByFiltreSpatial::FiltreDelaunay()const 
{
   return ModeFiltreSpatial().FiltreDelaunay();
}


double & cByFiltreSpatial::DistMax()
{
   return ModeFiltreSpatial().FiltreDist().Val().DistMax();
}

const double & cByFiltreSpatial::DistMax()const 
{
   return ModeFiltreSpatial().FiltreDist().Val().DistMax();
}


cTplValGesInit< cFiltreDist > & cByFiltreSpatial::FiltreDist()
{
   return ModeFiltreSpatial().FiltreDist();
}

const cTplValGesInit< cFiltreDist > & cByFiltreSpatial::FiltreDist()const 
{
   return ModeFiltreSpatial().FiltreDist();
}


cModeFiltreSpatial & cByFiltreSpatial::ModeFiltreSpatial()
{
   return mModeFiltreSpatial;
}

const cModeFiltreSpatial & cByFiltreSpatial::ModeFiltreSpatial()const 
{
   return mModeFiltreSpatial;
}

cElXMLTree * ToXMLTree(const cByFiltreSpatial & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ByFiltreSpatial",eXMLBranche);
   if (anObj.ByFileTrajecto().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("ByFileTrajecto"),anObj.ByFileTrajecto().Val())->ReTagThis("ByFileTrajecto"));
   aRes->AddFils(::ToXMLTree(std::string("KeyOri"),anObj.KeyOri())->ReTagThis("KeyOri"));
   aRes->AddFils(::ToXMLTree(std::string("KeySet"),anObj.KeySet())->ReTagThis("KeySet"));
   if (anObj.TagCentre().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("TagCentre"),anObj.TagCentre().Val())->ReTagThis("TagCentre"));
   if (anObj.Sym().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Sym"),anObj.Sym().Val())->ReTagThis("Sym"));
   if (anObj.FiltreSup().IsInit())
      aRes->AddFils(ToXMLTree(anObj.FiltreSup().Val())->ReTagThis("FiltreSup"));
   aRes->AddFils(ToXMLTree(anObj.ModeFiltreSpatial())->ReTagThis("ModeFiltreSpatial"));
  return aRes;
}

void xml_init(cByFiltreSpatial & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.ByFileTrajecto(),aTree->Get("ByFileTrajecto",1)); //tototo 

   xml_init(anObj.KeyOri(),aTree->Get("KeyOri",1)); //tototo 

   xml_init(anObj.KeySet(),aTree->Get("KeySet",1)); //tototo 

   xml_init(anObj.TagCentre(),aTree->Get("TagCentre",1),std::string("Centre")); //tototo 

   xml_init(anObj.Sym(),aTree->Get("Sym",1),bool(true)); //tototo 

   xml_init(anObj.FiltreSup(),aTree->Get("FiltreSup",1)); //tototo 

   xml_init(anObj.ModeFiltreSpatial(),aTree->Get("ModeFiltreSpatial",1)); //tototo 
}


std::vector< std::string > & cByAdjacence::KeySets()
{
   return mKeySets;
}

const std::vector< std::string > & cByAdjacence::KeySets()const 
{
   return mKeySets;
}


cTplValGesInit< IntSubst > & cByAdjacence::DeltaMax()
{
   return mDeltaMax;
}

const cTplValGesInit< IntSubst > & cByAdjacence::DeltaMax()const 
{
   return mDeltaMax;
}


cTplValGesInit< IntSubst > & cByAdjacence::DeltaMin()
{
   return mDeltaMin;
}

const cTplValGesInit< IntSubst > & cByAdjacence::DeltaMin()const 
{
   return mDeltaMin;
}


cTplValGesInit< cFiltreDeRelationOrient > & cByAdjacence::Filtre()
{
   return mFiltre;
}

const cTplValGesInit< cFiltreDeRelationOrient > & cByAdjacence::Filtre()const 
{
   return mFiltre;
}


cTplValGesInit< bool > & cByAdjacence::Sym()
{
   return mSym;
}

const cTplValGesInit< bool > & cByAdjacence::Sym()const 
{
   return mSym;
}


cTplValGesInit< bool > & cByAdjacence::Circ()
{
   return mCirc;
}

const cTplValGesInit< bool > & cByAdjacence::Circ()const 
{
   return mCirc;
}

cElXMLTree * ToXMLTree(const cByAdjacence & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ByAdjacence",eXMLBranche);
  for
  (       std::vector< std::string >::const_iterator it=anObj.KeySets().begin();
      it !=anObj.KeySets().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("KeySets"),(*it))->ReTagThis("KeySets"));
   if (anObj.DeltaMax().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("DeltaMax"),anObj.DeltaMax().Val())->ReTagThis("DeltaMax"));
   if (anObj.DeltaMin().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("DeltaMin"),anObj.DeltaMin().Val())->ReTagThis("DeltaMin"));
   if (anObj.Filtre().IsInit())
      aRes->AddFils(ToXMLTree(anObj.Filtre().Val())->ReTagThis("Filtre"));
   if (anObj.Sym().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Sym"),anObj.Sym().Val())->ReTagThis("Sym"));
   if (anObj.Circ().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Circ"),anObj.Circ().Val())->ReTagThis("Circ"));
  return aRes;
}

void xml_init(cByAdjacence & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeySets(),aTree->GetAll("KeySets",false,1));

   xml_init(anObj.DeltaMax(),aTree->Get("DeltaMax",1),IntSubst(10000000)); //tototo 

   xml_init(anObj.DeltaMin(),aTree->Get("DeltaMin",1)); //tototo 

   xml_init(anObj.Filtre(),aTree->Get("Filtre",1)); //tototo 

   xml_init(anObj.Sym(),aTree->Get("Sym",1),bool(true)); //tototo 

   xml_init(anObj.Circ(),aTree->Get("Circ",1),bool(false)); //tototo 
}


std::list< std::string > & cNameRelDescriptor::NameFileIn()
{
   return mNameFileIn;
}

const std::list< std::string > & cNameRelDescriptor::NameFileIn()const 
{
   return mNameFileIn;
}


cTplValGesInit< bool > & cNameRelDescriptor::Reflexif()
{
   return mReflexif;
}

const cTplValGesInit< bool > & cNameRelDescriptor::Reflexif()const 
{
   return mReflexif;
}


cTplValGesInit< std::string > & cNameRelDescriptor::NameFileSauvegarde()
{
   return mNameFileSauvegarde;
}

const cTplValGesInit< std::string > & cNameRelDescriptor::NameFileSauvegarde()const 
{
   return mNameFileSauvegarde;
}


std::list< cRelByGrapheExpl > & cNameRelDescriptor::RelByGrapheExpl()
{
   return mRelByGrapheExpl;
}

const std::list< cRelByGrapheExpl > & cNameRelDescriptor::RelByGrapheExpl()const 
{
   return mRelByGrapheExpl;
}


std::list< cByGroupesDImages > & cNameRelDescriptor::ByGroupesDImages()
{
   return mByGroupesDImages;
}

const std::list< cByGroupesDImages > & cNameRelDescriptor::ByGroupesDImages()const 
{
   return mByGroupesDImages;
}


std::list< cByFiltreSpatial > & cNameRelDescriptor::ByFiltreSpatial()
{
   return mByFiltreSpatial;
}

const std::list< cByFiltreSpatial > & cNameRelDescriptor::ByFiltreSpatial()const 
{
   return mByFiltreSpatial;
}


std::list< cByAdjacence > & cNameRelDescriptor::ByAdjacence()
{
   return mByAdjacence;
}

const std::list< cByAdjacence > & cNameRelDescriptor::ByAdjacence()const 
{
   return mByAdjacence;
}


std::list< cCpleString > & cNameRelDescriptor::CplesExcl()
{
   return mCplesExcl;
}

const std::list< cCpleString > & cNameRelDescriptor::CplesExcl()const 
{
   return mCplesExcl;
}

cElXMLTree * ToXMLTree(const cNameRelDescriptor & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"NameRelDescriptor",eXMLBranche);
  for
  (       std::list< std::string >::const_iterator it=anObj.NameFileIn().begin();
      it !=anObj.NameFileIn().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("NameFileIn"),(*it))->ReTagThis("NameFileIn"));
   if (anObj.Reflexif().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Reflexif"),anObj.Reflexif().Val())->ReTagThis("Reflexif"));
   if (anObj.NameFileSauvegarde().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NameFileSauvegarde"),anObj.NameFileSauvegarde().Val())->ReTagThis("NameFileSauvegarde"));
  for
  (       std::list< cRelByGrapheExpl >::const_iterator it=anObj.RelByGrapheExpl().begin();
      it !=anObj.RelByGrapheExpl().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("RelByGrapheExpl"));
  for
  (       std::list< cByGroupesDImages >::const_iterator it=anObj.ByGroupesDImages().begin();
      it !=anObj.ByGroupesDImages().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("ByGroupesDImages"));
  for
  (       std::list< cByFiltreSpatial >::const_iterator it=anObj.ByFiltreSpatial().begin();
      it !=anObj.ByFiltreSpatial().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("ByFiltreSpatial"));
  for
  (       std::list< cByAdjacence >::const_iterator it=anObj.ByAdjacence().begin();
      it !=anObj.ByAdjacence().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("ByAdjacence"));
  for
  (       std::list< cCpleString >::const_iterator it=anObj.CplesExcl().begin();
      it !=anObj.CplesExcl().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("CplesExcl"),(*it))->ReTagThis("CplesExcl"));
  return aRes;
}

void xml_init(cNameRelDescriptor & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.NameFileIn(),aTree->GetAll("NameFileIn",false,1));

   xml_init(anObj.Reflexif(),aTree->Get("Reflexif",1),bool(false)); //tototo 

   xml_init(anObj.NameFileSauvegarde(),aTree->Get("NameFileSauvegarde",1)); //tototo 

   xml_init(anObj.RelByGrapheExpl(),aTree->GetAll("RelByGrapheExpl",false,1));

   xml_init(anObj.ByGroupesDImages(),aTree->GetAll("ByGroupesDImages",false,1));

   xml_init(anObj.ByFiltreSpatial(),aTree->GetAll("ByFiltreSpatial",false,1));

   xml_init(anObj.ByAdjacence(),aTree->GetAll("ByAdjacence",false,1));

   xml_init(anObj.CplesExcl(),aTree->GetAll("CplesExcl",false,1));
}


std::string & cExeRequired::Exe()
{
   return mExe;
}

const std::string & cExeRequired::Exe()const 
{
   return mExe;
}


std::string & cExeRequired::Make()
{
   return mMake;
}

const std::string & cExeRequired::Make()const 
{
   return mMake;
}

cElXMLTree * ToXMLTree(const cExeRequired & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ExeRequired",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Exe"),anObj.Exe())->ReTagThis("Exe"));
   aRes->AddFils(::ToXMLTree(std::string("Make"),anObj.Make())->ReTagThis("Make"));
  return aRes;
}

void xml_init(cExeRequired & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Exe(),aTree->Get("Exe",1)); //tototo 

   xml_init(anObj.Make(),aTree->Get("Make",1)); //tototo 
}


std::list< std::string > & cFileRequired::Pattern()
{
   return mPattern;
}

const std::list< std::string > & cFileRequired::Pattern()const 
{
   return mPattern;
}


cTplValGesInit< int > & cFileRequired::NbMin()
{
   return mNbMin;
}

const cTplValGesInit< int > & cFileRequired::NbMin()const 
{
   return mNbMin;
}


cTplValGesInit< int > & cFileRequired::NbMax()
{
   return mNbMax;
}

const cTplValGesInit< int > & cFileRequired::NbMax()const 
{
   return mNbMax;
}

cElXMLTree * ToXMLTree(const cFileRequired & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"FileRequired",eXMLBranche);
  for
  (       std::list< std::string >::const_iterator it=anObj.Pattern().begin();
      it !=anObj.Pattern().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Pattern"),(*it))->ReTagThis("Pattern"));
   if (anObj.NbMin().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NbMin"),anObj.NbMin().Val())->ReTagThis("NbMin"));
   if (anObj.NbMax().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NbMax"),anObj.NbMax().Val())->ReTagThis("NbMax"));
  return aRes;
}

void xml_init(cFileRequired & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Pattern(),aTree->GetAll("Pattern",false,1));

   xml_init(anObj.NbMin(),aTree->Get("NbMin",1),int(1)); //tototo 

   xml_init(anObj.NbMax(),aTree->Get("NbMax",1)); //tototo 
}


std::list< cExeRequired > & cBatchRequirement::ExeRequired()
{
   return mExeRequired;
}

const std::list< cExeRequired > & cBatchRequirement::ExeRequired()const 
{
   return mExeRequired;
}


std::list< cFileRequired > & cBatchRequirement::FileRequired()
{
   return mFileRequired;
}

const std::list< cFileRequired > & cBatchRequirement::FileRequired()const 
{
   return mFileRequired;
}

cElXMLTree * ToXMLTree(const cBatchRequirement & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"BatchRequirement",eXMLBranche);
  for
  (       std::list< cExeRequired >::const_iterator it=anObj.ExeRequired().begin();
      it !=anObj.ExeRequired().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("ExeRequired"));
  for
  (       std::list< cFileRequired >::const_iterator it=anObj.FileRequired().begin();
      it !=anObj.FileRequired().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("FileRequired"));
  return aRes;
}

void xml_init(cBatchRequirement & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.ExeRequired(),aTree->GetAll("ExeRequired",false,1));

   xml_init(anObj.FileRequired(),aTree->GetAll("FileRequired",false,1));
}


cTplValGesInit< Pt3dr > & cExportApero2MM::DirVertLoc()
{
   return mDirVertLoc;
}

const cTplValGesInit< Pt3dr > & cExportApero2MM::DirVertLoc()const 
{
   return mDirVertLoc;
}


cTplValGesInit< double > & cExportApero2MM::ProfInVertLoc()
{
   return mProfInVertLoc;
}

const cTplValGesInit< double > & cExportApero2MM::ProfInVertLoc()const 
{
   return mProfInVertLoc;
}

cElXMLTree * ToXMLTree(const cExportApero2MM & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ExportApero2MM",eXMLBranche);
   if (anObj.DirVertLoc().IsInit())
      aRes->AddFils(ToXMLTree(std::string("DirVertLoc"),anObj.DirVertLoc().Val())->ReTagThis("DirVertLoc"));
   if (anObj.ProfInVertLoc().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("ProfInVertLoc"),anObj.ProfInVertLoc().Val())->ReTagThis("ProfInVertLoc"));
  return aRes;
}

void xml_init(cExportApero2MM & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.DirVertLoc(),aTree->Get("DirVertLoc",1)); //tototo 

   xml_init(anObj.ProfInVertLoc(),aTree->Get("ProfInVertLoc",1)); //tototo 
}


std::string & cCameraEntry::Name()
{
   return mName;
}

const std::string & cCameraEntry::Name()const 
{
   return mName;
}


Pt2dr & cCameraEntry::SzCaptMm()
{
   return mSzCaptMm;
}

const Pt2dr & cCameraEntry::SzCaptMm()const 
{
   return mSzCaptMm;
}


std::string & cCameraEntry::ShortName()
{
   return mShortName;
}

const std::string & cCameraEntry::ShortName()const 
{
   return mShortName;
}


cTplValGesInit< bool > & cCameraEntry::BayerSwapRB()
{
   return mBayerSwapRB;
}

const cTplValGesInit< bool > & cCameraEntry::BayerSwapRB()const 
{
   return mBayerSwapRB;
}


cTplValGesInit< bool > & cCameraEntry::DevRawBasic()
{
   return mDevRawBasic;
}

const cTplValGesInit< bool > & cCameraEntry::DevRawBasic()const 
{
   return mDevRawBasic;
}

cElXMLTree * ToXMLTree(const cCameraEntry & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"CameraEntry",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Name"),anObj.Name())->ReTagThis("Name"));
   aRes->AddFils(::ToXMLTree(std::string("SzCaptMm"),anObj.SzCaptMm())->ReTagThis("SzCaptMm"));
   aRes->AddFils(::ToXMLTree(std::string("ShortName"),anObj.ShortName())->ReTagThis("ShortName"));
   if (anObj.BayerSwapRB().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("BayerSwapRB"),anObj.BayerSwapRB().Val())->ReTagThis("BayerSwapRB"));
   if (anObj.DevRawBasic().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("DevRawBasic"),anObj.DevRawBasic().Val())->ReTagThis("DevRawBasic"));
  return aRes;
}

void xml_init(cCameraEntry & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Name(),aTree->Get("Name",1)); //tototo 

   xml_init(anObj.SzCaptMm(),aTree->Get("SzCaptMm",1)); //tototo 

   xml_init(anObj.ShortName(),aTree->Get("ShortName",1)); //tototo 

   xml_init(anObj.BayerSwapRB(),aTree->Get("BayerSwapRB",1),bool(false)); //tototo 

   xml_init(anObj.DevRawBasic(),aTree->Get("DevRawBasic",1),bool(false)); //tototo 
}


std::list< cCameraEntry > & cMMCameraDataBase::CameraEntry()
{
   return mCameraEntry;
}

const std::list< cCameraEntry > & cMMCameraDataBase::CameraEntry()const 
{
   return mCameraEntry;
}

cElXMLTree * ToXMLTree(const cMMCameraDataBase & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"MMCameraDataBase",eXMLBranche);
  for
  (       std::list< cCameraEntry >::const_iterator it=anObj.CameraEntry().begin();
      it !=anObj.CameraEntry().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("CameraEntry"));
  return aRes;
}

void xml_init(cMMCameraDataBase & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.CameraEntry(),aTree->GetAll("CameraEntry",false,1));
}


std::string & cMakeDataBase::KeySetCollectXif()
{
   return mKeySetCollectXif;
}

const std::string & cMakeDataBase::KeySetCollectXif()const 
{
   return mKeySetCollectXif;
}


std::list< std::string > & cMakeDataBase::KeyAssocNameSup()
{
   return mKeyAssocNameSup;
}

const std::list< std::string > & cMakeDataBase::KeyAssocNameSup()const 
{
   return mKeyAssocNameSup;
}


cTplValGesInit< std::string > & cMakeDataBase::NameFile()
{
   return mNameFile;
}

const cTplValGesInit< std::string > & cMakeDataBase::NameFile()const 
{
   return mNameFile;
}

cElXMLTree * ToXMLTree(const cMakeDataBase & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"MakeDataBase",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("KeySetCollectXif"),anObj.KeySetCollectXif())->ReTagThis("KeySetCollectXif"));
  for
  (       std::list< std::string >::const_iterator it=anObj.KeyAssocNameSup().begin();
      it !=anObj.KeyAssocNameSup().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("KeyAssocNameSup"),(*it))->ReTagThis("KeyAssocNameSup"));
   if (anObj.NameFile().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("NameFile"),anObj.NameFile().Val())->ReTagThis("NameFile"));
  return aRes;
}

void xml_init(cMakeDataBase & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeySetCollectXif(),aTree->Get("KeySetCollectXif",1)); //tototo 

   xml_init(anObj.KeyAssocNameSup(),aTree->GetAll("KeyAssocNameSup",false,1));

   xml_init(anObj.NameFile(),aTree->Get("NameFile",1),std::string("MicMacDataBase")); //tototo 
}


cTplValGesInit< cBatchRequirement > & cBatchChantDesc::Requirement()
{
   return mRequirement;
}

const cTplValGesInit< cBatchRequirement > & cBatchChantDesc::Requirement()const 
{
   return mRequirement;
}


std::string & cBatchChantDesc::Key()
{
   return mKey;
}

const std::string & cBatchChantDesc::Key()const 
{
   return mKey;
}


std::list< std::string > & cBatchChantDesc::Line()
{
   return mLine;
}

const std::list< std::string > & cBatchChantDesc::Line()const 
{
   return mLine;
}

cElXMLTree * ToXMLTree(const cBatchChantDesc & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"BatchChantDesc",eXMLBranche);
   if (anObj.Requirement().IsInit())
      aRes->AddFils(ToXMLTree(anObj.Requirement().Val())->ReTagThis("Requirement"));
   aRes->AddFils(::ToXMLTree(std::string("Key"),anObj.Key())->ReTagThis("Key"));
  for
  (       std::list< std::string >::const_iterator it=anObj.Line().begin();
      it !=anObj.Line().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Line"),(*it))->ReTagThis("Line"));
  return aRes;
}

void xml_init(cBatchChantDesc & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Requirement(),aTree->Get("Requirement",1)); //tototo 

   xml_init(anObj.Key(),aTree->Get("Key",1)); //tototo 

   xml_init(anObj.Line(),aTree->GetAll("Line",false,1));
}


std::list< std::string > & cOneShowChantDesc::LineBefore()
{
   return mLineBefore;
}

const std::list< std::string > & cOneShowChantDesc::LineBefore()const 
{
   return mLineBefore;
}


cTplValGesInit< bool > & cOneShowChantDesc::ShowKeys()
{
   return mShowKeys;
}

const cTplValGesInit< bool > & cOneShowChantDesc::ShowKeys()const 
{
   return mShowKeys;
}


std::list< std::string > & cOneShowChantDesc::KeyRels()
{
   return mKeyRels;
}

const std::list< std::string > & cOneShowChantDesc::KeyRels()const 
{
   return mKeyRels;
}


std::list< std::string > & cOneShowChantDesc::KeySets()
{
   return mKeySets;
}

const std::list< std::string > & cOneShowChantDesc::KeySets()const 
{
   return mKeySets;
}


std::list< std::string > & cOneShowChantDesc::LineAfter()
{
   return mLineAfter;
}

const std::list< std::string > & cOneShowChantDesc::LineAfter()const 
{
   return mLineAfter;
}

cElXMLTree * ToXMLTree(const cOneShowChantDesc & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"OneShowChantDesc",eXMLBranche);
  for
  (       std::list< std::string >::const_iterator it=anObj.LineBefore().begin();
      it !=anObj.LineBefore().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("LineBefore"),(*it))->ReTagThis("LineBefore"));
   if (anObj.ShowKeys().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("ShowKeys"),anObj.ShowKeys().Val())->ReTagThis("ShowKeys"));
  for
  (       std::list< std::string >::const_iterator it=anObj.KeyRels().begin();
      it !=anObj.KeyRels().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("KeyRels"),(*it))->ReTagThis("KeyRels"));
  for
  (       std::list< std::string >::const_iterator it=anObj.KeySets().begin();
      it !=anObj.KeySets().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("KeySets"),(*it))->ReTagThis("KeySets"));
  for
  (       std::list< std::string >::const_iterator it=anObj.LineAfter().begin();
      it !=anObj.LineAfter().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("LineAfter"),(*it))->ReTagThis("LineAfter"));
  return aRes;
}

void xml_init(cOneShowChantDesc & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.LineBefore(),aTree->GetAll("LineBefore",false,1));

   xml_init(anObj.ShowKeys(),aTree->Get("ShowKeys",1),bool(true)); //tototo 

   xml_init(anObj.KeyRels(),aTree->GetAll("KeyRels",false,1));

   xml_init(anObj.KeySets(),aTree->GetAll("KeySets",false,1));

   xml_init(anObj.LineAfter(),aTree->GetAll("LineAfter",false,1));
}


std::list< cOneShowChantDesc > & cShowChantDesc::OneShowChantDesc()
{
   return mOneShowChantDesc;
}

const std::list< cOneShowChantDesc > & cShowChantDesc::OneShowChantDesc()const 
{
   return mOneShowChantDesc;
}


std::string & cShowChantDesc::File()
{
   return mFile;
}

const std::string & cShowChantDesc::File()const 
{
   return mFile;
}

cElXMLTree * ToXMLTree(const cShowChantDesc & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ShowChantDesc",eXMLBranche);
  for
  (       std::list< cOneShowChantDesc >::const_iterator it=anObj.OneShowChantDesc().begin();
      it !=anObj.OneShowChantDesc().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("OneShowChantDesc"));
   aRes->AddFils(::ToXMLTree(std::string("File"),anObj.File())->ReTagThis("File"));
  return aRes;
}

void xml_init(cShowChantDesc & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.OneShowChantDesc(),aTree->GetAll("OneShowChantDesc",false,1));

   xml_init(anObj.File(),aTree->Get("File",1)); //tototo 
}


std::string & cMatrixSplitBox::KeyMatr()
{
   return mKeyMatr;
}

const std::string & cMatrixSplitBox::KeyMatr()const 
{
   return mKeyMatr;
}


cTplValGesInit< double > & cMatrixSplitBox::Rab()
{
   return mRab;
}

const cTplValGesInit< double > & cMatrixSplitBox::Rab()const 
{
   return mRab;
}

cElXMLTree * ToXMLTree(const cMatrixSplitBox & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"MatrixSplitBox",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("KeyMatr"),anObj.KeyMatr())->ReTagThis("KeyMatr"));
   if (anObj.Rab().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Rab"),anObj.Rab().Val())->ReTagThis("Rab"));
  return aRes;
}

void xml_init(cMatrixSplitBox & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeyMatr(),aTree->Get("KeyMatr",1)); //tototo 

   xml_init(anObj.Rab(),aTree->Get("Rab",1),double(0.0)); //tototo 
}


cTplValGesInit< std::string > & cContenuAPrioriImage::KeyAutoAdaptScale()
{
   return mKeyAutoAdaptScale;
}

const cTplValGesInit< std::string > & cContenuAPrioriImage::KeyAutoAdaptScale()const 
{
   return mKeyAutoAdaptScale;
}


cTplValGesInit< double > & cContenuAPrioriImage::PdsMaxAdaptScale()
{
   return mPdsMaxAdaptScale;
}

const cTplValGesInit< double > & cContenuAPrioriImage::PdsMaxAdaptScale()const 
{
   return mPdsMaxAdaptScale;
}


cTplValGesInit< double > & cContenuAPrioriImage::Scale()
{
   return mScale;
}

const cTplValGesInit< double > & cContenuAPrioriImage::Scale()const 
{
   return mScale;
}


cTplValGesInit< double > & cContenuAPrioriImage::Teta()
{
   return mTeta;
}

const cTplValGesInit< double > & cContenuAPrioriImage::Teta()const 
{
   return mTeta;
}


cTplValGesInit< Box2di > & cContenuAPrioriImage::BoiteEnglob()
{
   return mBoiteEnglob;
}

const cTplValGesInit< Box2di > & cContenuAPrioriImage::BoiteEnglob()const 
{
   return mBoiteEnglob;
}


cTplValGesInit< std::string > & cContenuAPrioriImage::ElInt_CaPImAddedSet()
{
   return mElInt_CaPImAddedSet;
}

const cTplValGesInit< std::string > & cContenuAPrioriImage::ElInt_CaPImAddedSet()const 
{
   return mElInt_CaPImAddedSet;
}


cTplValGesInit< std::string > & cContenuAPrioriImage::ElInt_CaPImMyKey()
{
   return mElInt_CaPImMyKey;
}

const cTplValGesInit< std::string > & cContenuAPrioriImage::ElInt_CaPImMyKey()const 
{
   return mElInt_CaPImMyKey;
}


std::string & cContenuAPrioriImage::KeyMatr()
{
   return MatrixSplitBox().Val().KeyMatr();
}

const std::string & cContenuAPrioriImage::KeyMatr()const 
{
   return MatrixSplitBox().Val().KeyMatr();
}


cTplValGesInit< double > & cContenuAPrioriImage::Rab()
{
   return MatrixSplitBox().Val().Rab();
}

const cTplValGesInit< double > & cContenuAPrioriImage::Rab()const 
{
   return MatrixSplitBox().Val().Rab();
}


cTplValGesInit< cMatrixSplitBox > & cContenuAPrioriImage::MatrixSplitBox()
{
   return mMatrixSplitBox;
}

const cTplValGesInit< cMatrixSplitBox > & cContenuAPrioriImage::MatrixSplitBox()const 
{
   return mMatrixSplitBox;
}

cElXMLTree * ToXMLTree(const cContenuAPrioriImage & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ContenuAPrioriImage",eXMLBranche);
   if (anObj.KeyAutoAdaptScale().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("KeyAutoAdaptScale"),anObj.KeyAutoAdaptScale().Val())->ReTagThis("KeyAutoAdaptScale"));
   if (anObj.PdsMaxAdaptScale().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("PdsMaxAdaptScale"),anObj.PdsMaxAdaptScale().Val())->ReTagThis("PdsMaxAdaptScale"));
   if (anObj.Scale().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Scale"),anObj.Scale().Val())->ReTagThis("Scale"));
   if (anObj.Teta().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Teta"),anObj.Teta().Val())->ReTagThis("Teta"));
   if (anObj.BoiteEnglob().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("BoiteEnglob"),anObj.BoiteEnglob().Val())->ReTagThis("BoiteEnglob"));
   if (anObj.ElInt_CaPImAddedSet().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("ElInt_CaPImAddedSet"),anObj.ElInt_CaPImAddedSet().Val())->ReTagThis("ElInt_CaPImAddedSet"));
   if (anObj.ElInt_CaPImMyKey().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("ElInt_CaPImMyKey"),anObj.ElInt_CaPImMyKey().Val())->ReTagThis("ElInt_CaPImMyKey"));
   if (anObj.MatrixSplitBox().IsInit())
      aRes->AddFils(ToXMLTree(anObj.MatrixSplitBox().Val())->ReTagThis("MatrixSplitBox"));
  return aRes;
}

void xml_init(cContenuAPrioriImage & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeyAutoAdaptScale(),aTree->Get("KeyAutoAdaptScale",1)); //tototo 

   xml_init(anObj.PdsMaxAdaptScale(),aTree->Get("PdsMaxAdaptScale",1),double(0.5)); //tototo 

   xml_init(anObj.Scale(),aTree->Get("Scale",1),double(1.0)); //tototo 

   xml_init(anObj.Teta(),aTree->Get("Teta",1),double(0.0)); //tototo 

   xml_init(anObj.BoiteEnglob(),aTree->Get("BoiteEnglob",1)); //tototo 

   xml_init(anObj.ElInt_CaPImAddedSet(),aTree->Get("ElInt_CaPImAddedSet",1)); //tototo 

   xml_init(anObj.ElInt_CaPImMyKey(),aTree->Get("ElInt_CaPImMyKey",1)); //tototo 

   xml_init(anObj.MatrixSplitBox(),aTree->Get("MatrixSplitBox",1)); //tototo 
}


std::list< std::string > & cAPrioriImage::Names()
{
   return mNames;
}

const std::list< std::string > & cAPrioriImage::Names()const 
{
   return mNames;
}


cTplValGesInit< std::string > & cAPrioriImage::KeyedAddedSet()
{
   return mKeyedAddedSet;
}

const cTplValGesInit< std::string > & cAPrioriImage::KeyedAddedSet()const 
{
   return mKeyedAddedSet;
}


cTplValGesInit< std::string > & cAPrioriImage::Key()
{
   return mKey;
}

const cTplValGesInit< std::string > & cAPrioriImage::Key()const 
{
   return mKey;
}


cTplValGesInit< std::string > & cAPrioriImage::KeyAutoAdaptScale()
{
   return ContenuAPrioriImage().KeyAutoAdaptScale();
}

const cTplValGesInit< std::string > & cAPrioriImage::KeyAutoAdaptScale()const 
{
   return ContenuAPrioriImage().KeyAutoAdaptScale();
}


cTplValGesInit< double > & cAPrioriImage::PdsMaxAdaptScale()
{
   return ContenuAPrioriImage().PdsMaxAdaptScale();
}

const cTplValGesInit< double > & cAPrioriImage::PdsMaxAdaptScale()const 
{
   return ContenuAPrioriImage().PdsMaxAdaptScale();
}


cTplValGesInit< double > & cAPrioriImage::Scale()
{
   return ContenuAPrioriImage().Scale();
}

const cTplValGesInit< double > & cAPrioriImage::Scale()const 
{
   return ContenuAPrioriImage().Scale();
}


cTplValGesInit< double > & cAPrioriImage::Teta()
{
   return ContenuAPrioriImage().Teta();
}

const cTplValGesInit< double > & cAPrioriImage::Teta()const 
{
   return ContenuAPrioriImage().Teta();
}


cTplValGesInit< Box2di > & cAPrioriImage::BoiteEnglob()
{
   return ContenuAPrioriImage().BoiteEnglob();
}

const cTplValGesInit< Box2di > & cAPrioriImage::BoiteEnglob()const 
{
   return ContenuAPrioriImage().BoiteEnglob();
}


cTplValGesInit< std::string > & cAPrioriImage::ElInt_CaPImAddedSet()
{
   return ContenuAPrioriImage().ElInt_CaPImAddedSet();
}

const cTplValGesInit< std::string > & cAPrioriImage::ElInt_CaPImAddedSet()const 
{
   return ContenuAPrioriImage().ElInt_CaPImAddedSet();
}


cTplValGesInit< std::string > & cAPrioriImage::ElInt_CaPImMyKey()
{
   return ContenuAPrioriImage().ElInt_CaPImMyKey();
}

const cTplValGesInit< std::string > & cAPrioriImage::ElInt_CaPImMyKey()const 
{
   return ContenuAPrioriImage().ElInt_CaPImMyKey();
}


std::string & cAPrioriImage::KeyMatr()
{
   return ContenuAPrioriImage().MatrixSplitBox().Val().KeyMatr();
}

const std::string & cAPrioriImage::KeyMatr()const 
{
   return ContenuAPrioriImage().MatrixSplitBox().Val().KeyMatr();
}


cTplValGesInit< double > & cAPrioriImage::Rab()
{
   return ContenuAPrioriImage().MatrixSplitBox().Val().Rab();
}

const cTplValGesInit< double > & cAPrioriImage::Rab()const 
{
   return ContenuAPrioriImage().MatrixSplitBox().Val().Rab();
}


cTplValGesInit< cMatrixSplitBox > & cAPrioriImage::MatrixSplitBox()
{
   return ContenuAPrioriImage().MatrixSplitBox();
}

const cTplValGesInit< cMatrixSplitBox > & cAPrioriImage::MatrixSplitBox()const 
{
   return ContenuAPrioriImage().MatrixSplitBox();
}


cContenuAPrioriImage & cAPrioriImage::ContenuAPrioriImage()
{
   return mContenuAPrioriImage;
}

const cContenuAPrioriImage & cAPrioriImage::ContenuAPrioriImage()const 
{
   return mContenuAPrioriImage;
}

cElXMLTree * ToXMLTree(const cAPrioriImage & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"APrioriImage",eXMLBranche);
  for
  (       std::list< std::string >::const_iterator it=anObj.Names().begin();
      it !=anObj.Names().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Names"),(*it))->ReTagThis("Names"));
   if (anObj.KeyedAddedSet().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("KeyedAddedSet"),anObj.KeyedAddedSet().Val())->ReTagThis("KeyedAddedSet"));
   if (anObj.Key().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("Key"),anObj.Key().Val())->ReTagThis("Key"));
   aRes->AddFils(ToXMLTree(anObj.ContenuAPrioriImage())->ReTagThis("ContenuAPrioriImage"));
  return aRes;
}

void xml_init(cAPrioriImage & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Names(),aTree->GetAll("Names",false,1));

   xml_init(anObj.KeyedAddedSet(),aTree->Get("KeyedAddedSet",1)); //tototo 

   xml_init(anObj.Key(),aTree->Get("Key",1),std::string("DefKey")); //tototo 

   xml_init(anObj.ContenuAPrioriImage(),aTree->Get("ContenuAPrioriImage",1)); //tototo 
}


cTplValGesInit< bool > & cKeyedNamesAssociations::IsParametrized()
{
   return mIsParametrized;
}

const cTplValGesInit< bool > & cKeyedNamesAssociations::IsParametrized()const 
{
   return mIsParametrized;
}


std::list< cAssocNameToName > & cKeyedNamesAssociations::Calcs()
{
   return mCalcs;
}

const std::list< cAssocNameToName > & cKeyedNamesAssociations::Calcs()const 
{
   return mCalcs;
}


std::string & cKeyedNamesAssociations::Key()
{
   return mKey;
}

const std::string & cKeyedNamesAssociations::Key()const 
{
   return mKey;
}


cTplValGesInit< std::string > & cKeyedNamesAssociations::SubDirAutoMake()
{
   return mSubDirAutoMake;
}

const cTplValGesInit< std::string > & cKeyedNamesAssociations::SubDirAutoMake()const 
{
   return mSubDirAutoMake;
}


cTplValGesInit< bool > & cKeyedNamesAssociations::SubDirAutoMakeRec()
{
   return mSubDirAutoMakeRec;
}

const cTplValGesInit< bool > & cKeyedNamesAssociations::SubDirAutoMakeRec()const 
{
   return mSubDirAutoMakeRec;
}

cElXMLTree * ToXMLTree(const cKeyedNamesAssociations & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"KeyedNamesAssociations",eXMLBranche);
   if (anObj.IsParametrized().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("IsParametrized"),anObj.IsParametrized().Val())->ReTagThis("IsParametrized"));
  for
  (       std::list< cAssocNameToName >::const_iterator it=anObj.Calcs().begin();
      it !=anObj.Calcs().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("Calcs"));
   aRes->AddFils(::ToXMLTree(std::string("Key"),anObj.Key())->ReTagThis("Key"));
   if (anObj.SubDirAutoMake().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("SubDirAutoMake"),anObj.SubDirAutoMake().Val())->ReTagThis("SubDirAutoMake"));
   if (anObj.SubDirAutoMakeRec().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("SubDirAutoMakeRec"),anObj.SubDirAutoMakeRec().Val())->ReTagThis("SubDirAutoMakeRec"));
  return aRes;
}

void xml_init(cKeyedNamesAssociations & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.IsParametrized(),aTree->Get("IsParametrized",1),bool(false)); //tototo 

   xml_init(anObj.Calcs(),aTree->GetAll("Calcs",false,1));

   xml_init(anObj.Key(),aTree->Get("Key",1)); //tototo 

   xml_init(anObj.SubDirAutoMake(),aTree->Get("SubDirAutoMake",1),std::string("")); //tototo 

   xml_init(anObj.SubDirAutoMakeRec(),aTree->Get("SubDirAutoMakeRec",1),bool(false)); //tototo 
}


cTplValGesInit< bool > & cKeyedSetsOfNames::IsParametrized()
{
   return mIsParametrized;
}

const cTplValGesInit< bool > & cKeyedSetsOfNames::IsParametrized()const 
{
   return mIsParametrized;
}


cSetNameDescriptor & cKeyedSetsOfNames::Sets()
{
   return mSets;
}

const cSetNameDescriptor & cKeyedSetsOfNames::Sets()const 
{
   return mSets;
}


std::string & cKeyedSetsOfNames::Key()
{
   return mKey;
}

const std::string & cKeyedSetsOfNames::Key()const 
{
   return mKey;
}

cElXMLTree * ToXMLTree(const cKeyedSetsOfNames & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"KeyedSetsOfNames",eXMLBranche);
   if (anObj.IsParametrized().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("IsParametrized"),anObj.IsParametrized().Val())->ReTagThis("IsParametrized"));
   aRes->AddFils(ToXMLTree(anObj.Sets())->ReTagThis("Sets"));
   aRes->AddFils(::ToXMLTree(std::string("Key"),anObj.Key())->ReTagThis("Key"));
  return aRes;
}

void xml_init(cKeyedSetsOfNames & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.IsParametrized(),aTree->Get("IsParametrized",1),bool(false)); //tototo 

   xml_init(anObj.Sets(),aTree->Get("Sets",1)); //tototo 

   xml_init(anObj.Key(),aTree->Get("Key",1)); //tototo 
}


cTplValGesInit< bool > & cKeyedSetsORels::IsParametrized()
{
   return mIsParametrized;
}

const cTplValGesInit< bool > & cKeyedSetsORels::IsParametrized()const 
{
   return mIsParametrized;
}


cNameRelDescriptor & cKeyedSetsORels::Sets()
{
   return mSets;
}

const cNameRelDescriptor & cKeyedSetsORels::Sets()const 
{
   return mSets;
}


std::string & cKeyedSetsORels::Key()
{
   return mKey;
}

const std::string & cKeyedSetsORels::Key()const 
{
   return mKey;
}

cElXMLTree * ToXMLTree(const cKeyedSetsORels & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"KeyedSetsORels",eXMLBranche);
   if (anObj.IsParametrized().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("IsParametrized"),anObj.IsParametrized().Val())->ReTagThis("IsParametrized"));
   aRes->AddFils(ToXMLTree(anObj.Sets())->ReTagThis("Sets"));
   aRes->AddFils(::ToXMLTree(std::string("Key"),anObj.Key())->ReTagThis("Key"));
  return aRes;
}

void xml_init(cKeyedSetsORels & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.IsParametrized(),aTree->Get("IsParametrized",1),bool(false)); //tototo 

   xml_init(anObj.Sets(),aTree->Get("Sets",1)); //tototo 

   xml_init(anObj.Key(),aTree->Get("Key",1)); //tototo 
}


cImMatrixStructuration & cKeyedMatrixStruct::Matrix()
{
   return mMatrix;
}

const cImMatrixStructuration & cKeyedMatrixStruct::Matrix()const 
{
   return mMatrix;
}


std::string & cKeyedMatrixStruct::Key()
{
   return mKey;
}

const std::string & cKeyedMatrixStruct::Key()const 
{
   return mKey;
}

cElXMLTree * ToXMLTree(const cKeyedMatrixStruct & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"KeyedMatrixStruct",eXMLBranche);
   aRes->AddFils(ToXMLTree(anObj.Matrix())->ReTagThis("Matrix"));
   aRes->AddFils(::ToXMLTree(std::string("Key"),anObj.Key())->ReTagThis("Key"));
  return aRes;
}

void xml_init(cKeyedMatrixStruct & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Matrix(),aTree->Get("Matrix",1)); //tototo 

   xml_init(anObj.Key(),aTree->Get("Key",1)); //tototo 
}


cTplValGesInit< bool > & cChantierDescripteur::ExitOnBrkp()
{
   return mExitOnBrkp;
}

const cTplValGesInit< bool > & cChantierDescripteur::ExitOnBrkp()const 
{
   return mExitOnBrkp;
}


std::list< std::string > & cChantierDescripteur::Symb()
{
   return mSymb;
}

const std::list< std::string > & cChantierDescripteur::Symb()const 
{
   return mSymb;
}


std::list< std::string > & cChantierDescripteur::eSymb()
{
   return meSymb;
}

const std::list< std::string > & cChantierDescripteur::eSymb()const 
{
   return meSymb;
}


cTplValGesInit< cMMCameraDataBase > & cChantierDescripteur::LocCamDataBase()
{
   return mLocCamDataBase;
}

const cTplValGesInit< cMMCameraDataBase > & cChantierDescripteur::LocCamDataBase()const 
{
   return mLocCamDataBase;
}


std::string & cChantierDescripteur::KeySetCollectXif()
{
   return MakeDataBase().Val().KeySetCollectXif();
}

const std::string & cChantierDescripteur::KeySetCollectXif()const 
{
   return MakeDataBase().Val().KeySetCollectXif();
}


std::list< std::string > & cChantierDescripteur::KeyAssocNameSup()
{
   return MakeDataBase().Val().KeyAssocNameSup();
}

const std::list< std::string > & cChantierDescripteur::KeyAssocNameSup()const 
{
   return MakeDataBase().Val().KeyAssocNameSup();
}


cTplValGesInit< std::string > & cChantierDescripteur::NameFile()
{
   return MakeDataBase().Val().NameFile();
}

const cTplValGesInit< std::string > & cChantierDescripteur::NameFile()const 
{
   return MakeDataBase().Val().NameFile();
}


cTplValGesInit< cMakeDataBase > & cChantierDescripteur::MakeDataBase()
{
   return mMakeDataBase;
}

const cTplValGesInit< cMakeDataBase > & cChantierDescripteur::MakeDataBase()const 
{
   return mMakeDataBase;
}


cTplValGesInit< std::string > & cChantierDescripteur::KeySuprAbs2Rel()
{
   return mKeySuprAbs2Rel;
}

const cTplValGesInit< std::string > & cChantierDescripteur::KeySuprAbs2Rel()const 
{
   return mKeySuprAbs2Rel;
}


std::list< cBatchChantDesc > & cChantierDescripteur::BatchChantDesc()
{
   return mBatchChantDesc;
}

const std::list< cBatchChantDesc > & cChantierDescripteur::BatchChantDesc()const 
{
   return mBatchChantDesc;
}


std::list< cShowChantDesc > & cChantierDescripteur::ShowChantDesc()
{
   return mShowChantDesc;
}

const std::list< cShowChantDesc > & cChantierDescripteur::ShowChantDesc()const 
{
   return mShowChantDesc;
}


std::list< cAPrioriImage > & cChantierDescripteur::APrioriImage()
{
   return mAPrioriImage;
}

const std::list< cAPrioriImage > & cChantierDescripteur::APrioriImage()const 
{
   return mAPrioriImage;
}


std::list< cKeyedNamesAssociations > & cChantierDescripteur::KeyedNamesAssociations()
{
   return mKeyedNamesAssociations;
}

const std::list< cKeyedNamesAssociations > & cChantierDescripteur::KeyedNamesAssociations()const 
{
   return mKeyedNamesAssociations;
}


std::list< cKeyedSetsOfNames > & cChantierDescripteur::KeyedSetsOfNames()
{
   return mKeyedSetsOfNames;
}

const std::list< cKeyedSetsOfNames > & cChantierDescripteur::KeyedSetsOfNames()const 
{
   return mKeyedSetsOfNames;
}


std::list< cKeyedSetsORels > & cChantierDescripteur::KeyedSetsORels()
{
   return mKeyedSetsORels;
}

const std::list< cKeyedSetsORels > & cChantierDescripteur::KeyedSetsORels()const 
{
   return mKeyedSetsORels;
}


std::list< cKeyedMatrixStruct > & cChantierDescripteur::KeyedMatrixStruct()
{
   return mKeyedMatrixStruct;
}

const std::list< cKeyedMatrixStruct > & cChantierDescripteur::KeyedMatrixStruct()const 
{
   return mKeyedMatrixStruct;
}


std::list< cClassEquivDescripteur > & cChantierDescripteur::KeyedClassEquiv()
{
   return mKeyedClassEquiv;
}

const std::list< cClassEquivDescripteur > & cChantierDescripteur::KeyedClassEquiv()const 
{
   return mKeyedClassEquiv;
}


cTplValGesInit< cBaseDataCD > & cChantierDescripteur::BaseDatas()
{
   return mBaseDatas;
}

const cTplValGesInit< cBaseDataCD > & cChantierDescripteur::BaseDatas()const 
{
   return mBaseDatas;
}


std::list< std::string > & cChantierDescripteur::FilesDatas()
{
   return mFilesDatas;
}

const std::list< std::string > & cChantierDescripteur::FilesDatas()const 
{
   return mFilesDatas;
}

cElXMLTree * ToXMLTree(const cChantierDescripteur & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ChantierDescripteur",eXMLBranche);
   if (anObj.ExitOnBrkp().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("ExitOnBrkp"),anObj.ExitOnBrkp().Val())->ReTagThis("ExitOnBrkp"));
  for
  (       std::list< std::string >::const_iterator it=anObj.Symb().begin();
      it !=anObj.Symb().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Symb"),(*it))->ReTagThis("Symb"));
  for
  (       std::list< std::string >::const_iterator it=anObj.eSymb().begin();
      it !=anObj.eSymb().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("eSymb"),(*it))->ReTagThis("eSymb"));
   if (anObj.LocCamDataBase().IsInit())
      aRes->AddFils(ToXMLTree(anObj.LocCamDataBase().Val())->ReTagThis("LocCamDataBase"));
   if (anObj.MakeDataBase().IsInit())
      aRes->AddFils(ToXMLTree(anObj.MakeDataBase().Val())->ReTagThis("MakeDataBase"));
   if (anObj.KeySuprAbs2Rel().IsInit())
      aRes->AddFils(::ToXMLTree(std::string("KeySuprAbs2Rel"),anObj.KeySuprAbs2Rel().Val())->ReTagThis("KeySuprAbs2Rel"));
  for
  (       std::list< cBatchChantDesc >::const_iterator it=anObj.BatchChantDesc().begin();
      it !=anObj.BatchChantDesc().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("BatchChantDesc"));
  for
  (       std::list< cShowChantDesc >::const_iterator it=anObj.ShowChantDesc().begin();
      it !=anObj.ShowChantDesc().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("ShowChantDesc"));
  for
  (       std::list< cAPrioriImage >::const_iterator it=anObj.APrioriImage().begin();
      it !=anObj.APrioriImage().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("APrioriImage"));
  for
  (       std::list< cKeyedNamesAssociations >::const_iterator it=anObj.KeyedNamesAssociations().begin();
      it !=anObj.KeyedNamesAssociations().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("KeyedNamesAssociations"));
  for
  (       std::list< cKeyedSetsOfNames >::const_iterator it=anObj.KeyedSetsOfNames().begin();
      it !=anObj.KeyedSetsOfNames().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("KeyedSetsOfNames"));
  for
  (       std::list< cKeyedSetsORels >::const_iterator it=anObj.KeyedSetsORels().begin();
      it !=anObj.KeyedSetsORels().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("KeyedSetsORels"));
  for
  (       std::list< cKeyedMatrixStruct >::const_iterator it=anObj.KeyedMatrixStruct().begin();
      it !=anObj.KeyedMatrixStruct().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("KeyedMatrixStruct"));
  for
  (       std::list< cClassEquivDescripteur >::const_iterator it=anObj.KeyedClassEquiv().begin();
      it !=anObj.KeyedClassEquiv().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("KeyedClassEquiv"));
   if (anObj.BaseDatas().IsInit())
      aRes->AddFils(ToXMLTree(anObj.BaseDatas().Val())->ReTagThis("BaseDatas"));
  for
  (       std::list< std::string >::const_iterator it=anObj.FilesDatas().begin();
      it !=anObj.FilesDatas().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("FilesDatas"),(*it))->ReTagThis("FilesDatas"));
  return aRes;
}

void xml_init(cChantierDescripteur & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.ExitOnBrkp(),aTree->Get("ExitOnBrkp",1)); //tototo 

   xml_init(anObj.Symb(),aTree->GetAll("Symb",false,1));

   xml_init(anObj.eSymb(),aTree->GetAll("eSymb",false,1));

   xml_init(anObj.LocCamDataBase(),aTree->Get("LocCamDataBase",1)); //tototo 

   xml_init(anObj.MakeDataBase(),aTree->Get("MakeDataBase",1)); //tototo 

   xml_init(anObj.KeySuprAbs2Rel(),aTree->Get("KeySuprAbs2Rel",1)); //tototo 

   xml_init(anObj.BatchChantDesc(),aTree->GetAll("BatchChantDesc",false,1));

   xml_init(anObj.ShowChantDesc(),aTree->GetAll("ShowChantDesc",false,1));

   xml_init(anObj.APrioriImage(),aTree->GetAll("APrioriImage",false,1));

   xml_init(anObj.KeyedNamesAssociations(),aTree->GetAll("KeyedNamesAssociations",false,1));

   xml_init(anObj.KeyedSetsOfNames(),aTree->GetAll("KeyedSetsOfNames",false,1));

   xml_init(anObj.KeyedSetsORels(),aTree->GetAll("KeyedSetsORels",false,1));

   xml_init(anObj.KeyedMatrixStruct(),aTree->GetAll("KeyedMatrixStruct",false,1));

   xml_init(anObj.KeyedClassEquiv(),aTree->GetAll("KeyedClassEquiv",false,1));

   xml_init(anObj.BaseDatas(),aTree->Get("BaseDatas",1)); //tototo 

   xml_init(anObj.FilesDatas(),aTree->GetAll("FilesDatas",false,1));
}


int & cXML_Date::year()
{
   return myear;
}

const int & cXML_Date::year()const 
{
   return myear;
}


int & cXML_Date::month()
{
   return mmonth;
}

const int & cXML_Date::month()const 
{
   return mmonth;
}


int & cXML_Date::day()
{
   return mday;
}

const int & cXML_Date::day()const 
{
   return mday;
}


int & cXML_Date::hour()
{
   return mhour;
}

const int & cXML_Date::hour()const 
{
   return mhour;
}


int & cXML_Date::minute()
{
   return mminute;
}

const int & cXML_Date::minute()const 
{
   return mminute;
}


int & cXML_Date::second()
{
   return msecond;
}

const int & cXML_Date::second()const 
{
   return msecond;
}


std::string & cXML_Date::time_system()
{
   return mtime_system;
}

const std::string & cXML_Date::time_system()const 
{
   return mtime_system;
}

cElXMLTree * ToXMLTree(const cXML_Date & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"XML_Date",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("year"),anObj.year())->ReTagThis("year"));
   aRes->AddFils(::ToXMLTree(std::string("month"),anObj.month())->ReTagThis("month"));
   aRes->AddFils(::ToXMLTree(std::string("day"),anObj.day())->ReTagThis("day"));
   aRes->AddFils(::ToXMLTree(std::string("hour"),anObj.hour())->ReTagThis("hour"));
   aRes->AddFils(::ToXMLTree(std::string("minute"),anObj.minute())->ReTagThis("minute"));
   aRes->AddFils(::ToXMLTree(std::string("second"),anObj.second())->ReTagThis("second"));
   aRes->AddFils(::ToXMLTree(std::string("time_system"),anObj.time_system())->ReTagThis("time_system"));
  return aRes;
}

void xml_init(cXML_Date & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.year(),aTree->Get("year",1)); //tototo 

   xml_init(anObj.month(),aTree->Get("month",1)); //tototo 

   xml_init(anObj.day(),aTree->Get("day",1)); //tototo 

   xml_init(anObj.hour(),aTree->Get("hour",1)); //tototo 

   xml_init(anObj.minute(),aTree->Get("minute",1)); //tototo 

   xml_init(anObj.second(),aTree->Get("second",1)); //tototo 

   xml_init(anObj.time_system(),aTree->Get("time_system",1)); //tototo 
}


double & cpt3d::x()
{
   return mx;
}

const double & cpt3d::x()const 
{
   return mx;
}


double & cpt3d::y()
{
   return my;
}

const double & cpt3d::y()const 
{
   return my;
}


double & cpt3d::z()
{
   return mz;
}

const double & cpt3d::z()const 
{
   return mz;
}

cElXMLTree * ToXMLTree(const cpt3d & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"pt3d",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("x"),anObj.x())->ReTagThis("x"));
   aRes->AddFils(::ToXMLTree(std::string("y"),anObj.y())->ReTagThis("y"));
   aRes->AddFils(::ToXMLTree(std::string("z"),anObj.z())->ReTagThis("z"));
  return aRes;
}

void xml_init(cpt3d & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.x(),aTree->Get("x",1)); //tototo 

   xml_init(anObj.y(),aTree->Get("y",1)); //tototo 

   xml_init(anObj.z(),aTree->Get("z",1)); //tototo 
}


double & cXML_LinePt3d::x()
{
   return pt3d().x();
}

const double & cXML_LinePt3d::x()const 
{
   return pt3d().x();
}


double & cXML_LinePt3d::y()
{
   return pt3d().y();
}

const double & cXML_LinePt3d::y()const 
{
   return pt3d().y();
}


double & cXML_LinePt3d::z()
{
   return pt3d().z();
}

const double & cXML_LinePt3d::z()const 
{
   return pt3d().z();
}


cpt3d & cXML_LinePt3d::pt3d()
{
   return mpt3d;
}

const cpt3d & cXML_LinePt3d::pt3d()const 
{
   return mpt3d;
}

cElXMLTree * ToXMLTree(const cXML_LinePt3d & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"XML_LinePt3d",eXMLBranche);
   aRes->AddFils(ToXMLTree(anObj.pt3d())->ReTagThis("pt3d"));
  return aRes;
}

void xml_init(cXML_LinePt3d & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.pt3d(),aTree->Get("pt3d",1)); //tototo 
}


std::string & cauxiliarydata::image_name()
{
   return mimage_name;
}

const std::string & cauxiliarydata::image_name()const 
{
   return mimage_name;
}


std::string & cauxiliarydata::stereopolis()
{
   return mstereopolis;
}

const std::string & cauxiliarydata::stereopolis()const 
{
   return mstereopolis;
}


cXML_Date & cauxiliarydata::image_date()
{
   return mimage_date;
}

const cXML_Date & cauxiliarydata::image_date()const 
{
   return mimage_date;
}


std::list< std::string > & cauxiliarydata::samples()
{
   return msamples;
}

const std::list< std::string > & cauxiliarydata::samples()const 
{
   return msamples;
}

cElXMLTree * ToXMLTree(const cauxiliarydata & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"auxiliarydata",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("image_name"),anObj.image_name())->ReTagThis("image_name"));
   aRes->AddFils(::ToXMLTree(std::string("stereopolis"),anObj.stereopolis())->ReTagThis("stereopolis"));
   aRes->AddFils(ToXMLTree(anObj.image_date())->ReTagThis("image_date"));
  for
  (       std::list< std::string >::const_iterator it=anObj.samples().begin();
      it !=anObj.samples().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("samples"),(*it))->ReTagThis("samples"));
  return aRes;
}

void xml_init(cauxiliarydata & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.image_name(),aTree->Get("image_name",1)); //tototo 

   xml_init(anObj.stereopolis(),aTree->Get("stereopolis",1)); //tototo 

   xml_init(anObj.image_date(),aTree->Get("image_date",1)); //tototo 

   xml_init(anObj.samples(),aTree->GetAll("samples",false,1));
}


double & ceuclidien::x()
{
   return mx;
}

const double & ceuclidien::x()const 
{
   return mx;
}


double & ceuclidien::y()
{
   return my;
}

const double & ceuclidien::y()const 
{
   return my;
}

cElXMLTree * ToXMLTree(const ceuclidien & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"euclidien",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("x"),anObj.x())->ReTagThis("x"));
   aRes->AddFils(::ToXMLTree(std::string("y"),anObj.y())->ReTagThis("y"));
  return aRes;
}

void xml_init(ceuclidien & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.x(),aTree->Get("x",1)); //tototo 

   xml_init(anObj.y(),aTree->Get("y",1)); //tototo 
}


ceuclidien & csysteme::euclidien()
{
   return meuclidien;
}

const ceuclidien & csysteme::euclidien()const 
{
   return meuclidien;
}


std::string & csysteme::geodesique()
{
   return mgeodesique;
}

const std::string & csysteme::geodesique()const 
{
   return mgeodesique;
}

cElXMLTree * ToXMLTree(const csysteme & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"systeme",eXMLBranche);
   aRes->AddFils(ToXMLTree(anObj.euclidien())->ReTagThis("euclidien"));
   aRes->AddFils(::ToXMLTree(std::string("geodesique"),anObj.geodesique())->ReTagThis("geodesique"));
  return aRes;
}

void xml_init(csysteme & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.euclidien(),aTree->Get("euclidien",1)); //tototo 

   xml_init(anObj.geodesique(),aTree->Get("geodesique",1)); //tototo 
}


double & csommet::easting()
{
   return measting;
}

const double & csommet::easting()const 
{
   return measting;
}


double & csommet::northing()
{
   return mnorthing;
}

const double & csommet::northing()const 
{
   return mnorthing;
}


double & csommet::altitude()
{
   return maltitude;
}

const double & csommet::altitude()const 
{
   return maltitude;
}

cElXMLTree * ToXMLTree(const csommet & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"sommet",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("easting"),anObj.easting())->ReTagThis("easting"));
   aRes->AddFils(::ToXMLTree(std::string("northing"),anObj.northing())->ReTagThis("northing"));
   aRes->AddFils(::ToXMLTree(std::string("altitude"),anObj.altitude())->ReTagThis("altitude"));
  return aRes;
}

void xml_init(csommet & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.easting(),aTree->Get("easting",1)); //tototo 

   xml_init(anObj.northing(),aTree->Get("northing",1)); //tototo 

   xml_init(anObj.altitude(),aTree->Get("altitude",1)); //tototo 
}


cXML_LinePt3d & cmat3d::l1()
{
   return ml1;
}

const cXML_LinePt3d & cmat3d::l1()const 
{
   return ml1;
}


cXML_LinePt3d & cmat3d::l2()
{
   return ml2;
}

const cXML_LinePt3d & cmat3d::l2()const 
{
   return ml2;
}


cXML_LinePt3d & cmat3d::l3()
{
   return ml3;
}

const cXML_LinePt3d & cmat3d::l3()const 
{
   return ml3;
}

cElXMLTree * ToXMLTree(const cmat3d & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"mat3d",eXMLBranche);
   aRes->AddFils(ToXMLTree(anObj.l1())->ReTagThis("l1"));
   aRes->AddFils(ToXMLTree(anObj.l2())->ReTagThis("l2"));
   aRes->AddFils(ToXMLTree(anObj.l3())->ReTagThis("l3"));
  return aRes;
}

void xml_init(cmat3d & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.l1(),aTree->Get("l1",1)); //tototo 

   xml_init(anObj.l2(),aTree->Get("l2",1)); //tototo 

   xml_init(anObj.l3(),aTree->Get("l3",1)); //tototo 
}


bool & crotation::Image2Ground()
{
   return mImage2Ground;
}

const bool & crotation::Image2Ground()const 
{
   return mImage2Ground;
}


cXML_LinePt3d & crotation::l1()
{
   return mat3d().l1();
}

const cXML_LinePt3d & crotation::l1()const 
{
   return mat3d().l1();
}


cXML_LinePt3d & crotation::l2()
{
   return mat3d().l2();
}

const cXML_LinePt3d & crotation::l2()const 
{
   return mat3d().l2();
}


cXML_LinePt3d & crotation::l3()
{
   return mat3d().l3();
}

const cXML_LinePt3d & crotation::l3()const 
{
   return mat3d().l3();
}


cmat3d & crotation::mat3d()
{
   return mmat3d;
}

const cmat3d & crotation::mat3d()const 
{
   return mmat3d;
}

cElXMLTree * ToXMLTree(const crotation & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"rotation",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Image2Ground"),anObj.Image2Ground())->ReTagThis("Image2Ground"));
   aRes->AddFils(ToXMLTree(anObj.mat3d())->ReTagThis("mat3d"));
  return aRes;
}

void xml_init(crotation & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Image2Ground(),aTree->Get("Image2Ground",1)); //tototo 

   xml_init(anObj.mat3d(),aTree->Get("mat3d",1)); //tototo 
}


ceuclidien & cextrinseque::euclidien()
{
   return systeme().euclidien();
}

const ceuclidien & cextrinseque::euclidien()const 
{
   return systeme().euclidien();
}


std::string & cextrinseque::geodesique()
{
   return systeme().geodesique();
}

const std::string & cextrinseque::geodesique()const 
{
   return systeme().geodesique();
}


csysteme & cextrinseque::systeme()
{
   return msysteme;
}

const csysteme & cextrinseque::systeme()const 
{
   return msysteme;
}


std::string & cextrinseque::grid_alti()
{
   return mgrid_alti;
}

const std::string & cextrinseque::grid_alti()const 
{
   return mgrid_alti;
}


double & cextrinseque::easting()
{
   return sommet().easting();
}

const double & cextrinseque::easting()const 
{
   return sommet().easting();
}


double & cextrinseque::northing()
{
   return sommet().northing();
}

const double & cextrinseque::northing()const 
{
   return sommet().northing();
}


double & cextrinseque::altitude()
{
   return sommet().altitude();
}

const double & cextrinseque::altitude()const 
{
   return sommet().altitude();
}


csommet & cextrinseque::sommet()
{
   return msommet;
}

const csommet & cextrinseque::sommet()const 
{
   return msommet;
}


bool & cextrinseque::Image2Ground()
{
   return rotation().Image2Ground();
}

const bool & cextrinseque::Image2Ground()const 
{
   return rotation().Image2Ground();
}


cXML_LinePt3d & cextrinseque::l1()
{
   return rotation().mat3d().l1();
}

const cXML_LinePt3d & cextrinseque::l1()const 
{
   return rotation().mat3d().l1();
}


cXML_LinePt3d & cextrinseque::l2()
{
   return rotation().mat3d().l2();
}

const cXML_LinePt3d & cextrinseque::l2()const 
{
   return rotation().mat3d().l2();
}


cXML_LinePt3d & cextrinseque::l3()
{
   return rotation().mat3d().l3();
}

const cXML_LinePt3d & cextrinseque::l3()const 
{
   return rotation().mat3d().l3();
}


cmat3d & cextrinseque::mat3d()
{
   return rotation().mat3d();
}

const cmat3d & cextrinseque::mat3d()const 
{
   return rotation().mat3d();
}


crotation & cextrinseque::rotation()
{
   return mrotation;
}

const crotation & cextrinseque::rotation()const 
{
   return mrotation;
}

cElXMLTree * ToXMLTree(const cextrinseque & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"extrinseque",eXMLBranche);
   aRes->AddFils(ToXMLTree(anObj.systeme())->ReTagThis("systeme"));
   aRes->AddFils(::ToXMLTree(std::string("grid_alti"),anObj.grid_alti())->ReTagThis("grid_alti"));
   aRes->AddFils(ToXMLTree(anObj.sommet())->ReTagThis("sommet"));
   aRes->AddFils(ToXMLTree(anObj.rotation())->ReTagThis("rotation"));
  return aRes;
}

void xml_init(cextrinseque & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.systeme(),aTree->Get("systeme",1)); //tototo 

   xml_init(anObj.grid_alti(),aTree->Get("grid_alti",1)); //tototo 

   xml_init(anObj.sommet(),aTree->Get("sommet",1)); //tototo 

   xml_init(anObj.rotation(),aTree->Get("rotation",1)); //tototo 
}


int & cimage_size::width()
{
   return mwidth;
}

const int & cimage_size::width()const 
{
   return mwidth;
}


int & cimage_size::height()
{
   return mheight;
}

const int & cimage_size::height()const 
{
   return mheight;
}

cElXMLTree * ToXMLTree(const cimage_size & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"image_size",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("width"),anObj.width())->ReTagThis("width"));
   aRes->AddFils(::ToXMLTree(std::string("height"),anObj.height())->ReTagThis("height"));
  return aRes;
}

void xml_init(cimage_size & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.width(),aTree->Get("width",1)); //tototo 

   xml_init(anObj.height(),aTree->Get("height",1)); //tototo 
}


double & cppa::c()
{
   return mc;
}

const double & cppa::c()const 
{
   return mc;
}


double & cppa::l()
{
   return ml;
}

const double & cppa::l()const 
{
   return ml;
}


double & cppa::focale()
{
   return mfocale;
}

const double & cppa::focale()const 
{
   return mfocale;
}

cElXMLTree * ToXMLTree(const cppa & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ppa",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("c"),anObj.c())->ReTagThis("c"));
   aRes->AddFils(::ToXMLTree(std::string("l"),anObj.l())->ReTagThis("l"));
   aRes->AddFils(::ToXMLTree(std::string("focale"),anObj.focale())->ReTagThis("focale"));
  return aRes;
}

void xml_init(cppa & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.c(),aTree->Get("c",1)); //tototo 

   xml_init(anObj.l(),aTree->Get("l",1)); //tototo 

   xml_init(anObj.focale(),aTree->Get("focale",1)); //tototo 
}


double & cpps::c()
{
   return mc;
}

const double & cpps::c()const 
{
   return mc;
}


double & cpps::l()
{
   return ml;
}

const double & cpps::l()const 
{
   return ml;
}

cElXMLTree * ToXMLTree(const cpps & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"pps",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("c"),anObj.c())->ReTagThis("c"));
   aRes->AddFils(::ToXMLTree(std::string("l"),anObj.l())->ReTagThis("l"));
  return aRes;
}

void xml_init(cpps & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.c(),aTree->Get("c",1)); //tototo 

   xml_init(anObj.l(),aTree->Get("l",1)); //tototo 
}


cpps & cdistortion::pps()
{
   return mpps;
}

const cpps & cdistortion::pps()const 
{
   return mpps;
}


double & cdistortion::r1()
{
   return mr1;
}

const double & cdistortion::r1()const 
{
   return mr1;
}


double & cdistortion::r3()
{
   return mr3;
}

const double & cdistortion::r3()const 
{
   return mr3;
}


double & cdistortion::r5()
{
   return mr5;
}

const double & cdistortion::r5()const 
{
   return mr5;
}


double & cdistortion::r7()
{
   return mr7;
}

const double & cdistortion::r7()const 
{
   return mr7;
}

cElXMLTree * ToXMLTree(const cdistortion & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"distortion",eXMLBranche);
   aRes->AddFils(ToXMLTree(anObj.pps())->ReTagThis("pps"));
   aRes->AddFils(::ToXMLTree(std::string("r1"),anObj.r1())->ReTagThis("r1"));
   aRes->AddFils(::ToXMLTree(std::string("r3"),anObj.r3())->ReTagThis("r3"));
   aRes->AddFils(::ToXMLTree(std::string("r5"),anObj.r5())->ReTagThis("r5"));
   aRes->AddFils(::ToXMLTree(std::string("r7"),anObj.r7())->ReTagThis("r7"));
  return aRes;
}

void xml_init(cdistortion & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.pps(),aTree->Get("pps",1)); //tototo 

   xml_init(anObj.r1(),aTree->Get("r1",1)); //tototo 

   xml_init(anObj.r3(),aTree->Get("r3",1)); //tototo 

   xml_init(anObj.r5(),aTree->Get("r5",1)); //tototo 

   xml_init(anObj.r7(),aTree->Get("r7",1)); //tototo 
}


std::string & csensor::name()
{
   return mname;
}

const std::string & csensor::name()const 
{
   return mname;
}


cXML_Date & csensor::calibration_date()
{
   return mcalibration_date;
}

const cXML_Date & csensor::calibration_date()const 
{
   return mcalibration_date;
}


std::string & csensor::serial_number()
{
   return mserial_number;
}

const std::string & csensor::serial_number()const 
{
   return mserial_number;
}


int & csensor::width()
{
   return image_size().width();
}

const int & csensor::width()const 
{
   return image_size().width();
}


int & csensor::height()
{
   return image_size().height();
}

const int & csensor::height()const 
{
   return image_size().height();
}


cimage_size & csensor::image_size()
{
   return mimage_size;
}

const cimage_size & csensor::image_size()const 
{
   return mimage_size;
}


cppa & csensor::ppa()
{
   return mppa;
}

const cppa & csensor::ppa()const 
{
   return mppa;
}


cpps & csensor::pps()
{
   return distortion().pps();
}

const cpps & csensor::pps()const 
{
   return distortion().pps();
}


double & csensor::r1()
{
   return distortion().r1();
}

const double & csensor::r1()const 
{
   return distortion().r1();
}


double & csensor::r3()
{
   return distortion().r3();
}

const double & csensor::r3()const 
{
   return distortion().r3();
}


double & csensor::r5()
{
   return distortion().r5();
}

const double & csensor::r5()const 
{
   return distortion().r5();
}


double & csensor::r7()
{
   return distortion().r7();
}

const double & csensor::r7()const 
{
   return distortion().r7();
}


cdistortion & csensor::distortion()
{
   return mdistortion;
}

const cdistortion & csensor::distortion()const 
{
   return mdistortion;
}

cElXMLTree * ToXMLTree(const csensor & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"sensor",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("name"),anObj.name())->ReTagThis("name"));
   aRes->AddFils(ToXMLTree(anObj.calibration_date())->ReTagThis("calibration_date"));
   aRes->AddFils(::ToXMLTree(std::string("serial_number"),anObj.serial_number())->ReTagThis("serial_number"));
   aRes->AddFils(ToXMLTree(anObj.image_size())->ReTagThis("image_size"));
   aRes->AddFils(ToXMLTree(anObj.ppa())->ReTagThis("ppa"));
   aRes->AddFils(ToXMLTree(anObj.distortion())->ReTagThis("distortion"));
  return aRes;
}

void xml_init(csensor & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.name(),aTree->Get("name",1)); //tototo 

   xml_init(anObj.calibration_date(),aTree->Get("calibration_date",1)); //tototo 

   xml_init(anObj.serial_number(),aTree->Get("serial_number",1)); //tototo 

   xml_init(anObj.image_size(),aTree->Get("image_size",1)); //tototo 

   xml_init(anObj.ppa(),aTree->Get("ppa",1)); //tototo 

   xml_init(anObj.distortion(),aTree->Get("distortion",1)); //tototo 
}


std::string & cintrinseque::name()
{
   return sensor().name();
}

const std::string & cintrinseque::name()const 
{
   return sensor().name();
}


cXML_Date & cintrinseque::calibration_date()
{
   return sensor().calibration_date();
}

const cXML_Date & cintrinseque::calibration_date()const 
{
   return sensor().calibration_date();
}


std::string & cintrinseque::serial_number()
{
   return sensor().serial_number();
}

const std::string & cintrinseque::serial_number()const 
{
   return sensor().serial_number();
}


int & cintrinseque::width()
{
   return sensor().image_size().width();
}

const int & cintrinseque::width()const 
{
   return sensor().image_size().width();
}


int & cintrinseque::height()
{
   return sensor().image_size().height();
}

const int & cintrinseque::height()const 
{
   return sensor().image_size().height();
}


cimage_size & cintrinseque::image_size()
{
   return sensor().image_size();
}

const cimage_size & cintrinseque::image_size()const 
{
   return sensor().image_size();
}


cppa & cintrinseque::ppa()
{
   return sensor().ppa();
}

const cppa & cintrinseque::ppa()const 
{
   return sensor().ppa();
}


cpps & cintrinseque::pps()
{
   return sensor().distortion().pps();
}

const cpps & cintrinseque::pps()const 
{
   return sensor().distortion().pps();
}


double & cintrinseque::r1()
{
   return sensor().distortion().r1();
}

const double & cintrinseque::r1()const 
{
   return sensor().distortion().r1();
}


double & cintrinseque::r3()
{
   return sensor().distortion().r3();
}

const double & cintrinseque::r3()const 
{
   return sensor().distortion().r3();
}


double & cintrinseque::r5()
{
   return sensor().distortion().r5();
}

const double & cintrinseque::r5()const 
{
   return sensor().distortion().r5();
}


double & cintrinseque::r7()
{
   return sensor().distortion().r7();
}

const double & cintrinseque::r7()const 
{
   return sensor().distortion().r7();
}


cdistortion & cintrinseque::distortion()
{
   return sensor().distortion();
}

const cdistortion & cintrinseque::distortion()const 
{
   return sensor().distortion();
}


csensor & cintrinseque::sensor()
{
   return msensor;
}

const csensor & cintrinseque::sensor()const 
{
   return msensor;
}

cElXMLTree * ToXMLTree(const cintrinseque & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"intrinseque",eXMLBranche);
   aRes->AddFils(ToXMLTree(anObj.sensor())->ReTagThis("sensor"));
  return aRes;
}

void xml_init(cintrinseque & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.sensor(),aTree->Get("sensor",1)); //tototo 
}


ceuclidien & cgeometry::euclidien()
{
   return extrinseque().systeme().euclidien();
}

const ceuclidien & cgeometry::euclidien()const 
{
   return extrinseque().systeme().euclidien();
}


std::string & cgeometry::geodesique()
{
   return extrinseque().systeme().geodesique();
}

const std::string & cgeometry::geodesique()const 
{
   return extrinseque().systeme().geodesique();
}


csysteme & cgeometry::systeme()
{
   return extrinseque().systeme();
}

const csysteme & cgeometry::systeme()const 
{
   return extrinseque().systeme();
}


std::string & cgeometry::grid_alti()
{
   return extrinseque().grid_alti();
}

const std::string & cgeometry::grid_alti()const 
{
   return extrinseque().grid_alti();
}


double & cgeometry::easting()
{
   return extrinseque().sommet().easting();
}

const double & cgeometry::easting()const 
{
   return extrinseque().sommet().easting();
}


double & cgeometry::northing()
{
   return extrinseque().sommet().northing();
}

const double & cgeometry::northing()const 
{
   return extrinseque().sommet().northing();
}


double & cgeometry::altitude()
{
   return extrinseque().sommet().altitude();
}

const double & cgeometry::altitude()const 
{
   return extrinseque().sommet().altitude();
}


csommet & cgeometry::sommet()
{
   return extrinseque().sommet();
}

const csommet & cgeometry::sommet()const 
{
   return extrinseque().sommet();
}


bool & cgeometry::Image2Ground()
{
   return extrinseque().rotation().Image2Ground();
}

const bool & cgeometry::Image2Ground()const 
{
   return extrinseque().rotation().Image2Ground();
}


cXML_LinePt3d & cgeometry::l1()
{
   return extrinseque().rotation().mat3d().l1();
}

const cXML_LinePt3d & cgeometry::l1()const 
{
   return extrinseque().rotation().mat3d().l1();
}


cXML_LinePt3d & cgeometry::l2()
{
   return extrinseque().rotation().mat3d().l2();
}

const cXML_LinePt3d & cgeometry::l2()const 
{
   return extrinseque().rotation().mat3d().l2();
}


cXML_LinePt3d & cgeometry::l3()
{
   return extrinseque().rotation().mat3d().l3();
}

const cXML_LinePt3d & cgeometry::l3()const 
{
   return extrinseque().rotation().mat3d().l3();
}


cmat3d & cgeometry::mat3d()
{
   return extrinseque().rotation().mat3d();
}

const cmat3d & cgeometry::mat3d()const 
{
   return extrinseque().rotation().mat3d();
}


crotation & cgeometry::rotation()
{
   return extrinseque().rotation();
}

const crotation & cgeometry::rotation()const 
{
   return extrinseque().rotation();
}


cextrinseque & cgeometry::extrinseque()
{
   return mextrinseque;
}

const cextrinseque & cgeometry::extrinseque()const 
{
   return mextrinseque;
}


std::string & cgeometry::name()
{
   return intrinseque().sensor().name();
}

const std::string & cgeometry::name()const 
{
   return intrinseque().sensor().name();
}


cXML_Date & cgeometry::calibration_date()
{
   return intrinseque().sensor().calibration_date();
}

const cXML_Date & cgeometry::calibration_date()const 
{
   return intrinseque().sensor().calibration_date();
}


std::string & cgeometry::serial_number()
{
   return intrinseque().sensor().serial_number();
}

const std::string & cgeometry::serial_number()const 
{
   return intrinseque().sensor().serial_number();
}


int & cgeometry::width()
{
   return intrinseque().sensor().image_size().width();
}

const int & cgeometry::width()const 
{
   return intrinseque().sensor().image_size().width();
}


int & cgeometry::height()
{
   return intrinseque().sensor().image_size().height();
}

const int & cgeometry::height()const 
{
   return intrinseque().sensor().image_size().height();
}


cimage_size & cgeometry::image_size()
{
   return intrinseque().sensor().image_size();
}

const cimage_size & cgeometry::image_size()const 
{
   return intrinseque().sensor().image_size();
}


cppa & cgeometry::ppa()
{
   return intrinseque().sensor().ppa();
}

const cppa & cgeometry::ppa()const 
{
   return intrinseque().sensor().ppa();
}


cpps & cgeometry::pps()
{
   return intrinseque().sensor().distortion().pps();
}

const cpps & cgeometry::pps()const 
{
   return intrinseque().sensor().distortion().pps();
}


double & cgeometry::r1()
{
   return intrinseque().sensor().distortion().r1();
}

const double & cgeometry::r1()const 
{
   return intrinseque().sensor().distortion().r1();
}


double & cgeometry::r3()
{
   return intrinseque().sensor().distortion().r3();
}

const double & cgeometry::r3()const 
{
   return intrinseque().sensor().distortion().r3();
}


double & cgeometry::r5()
{
   return intrinseque().sensor().distortion().r5();
}

const double & cgeometry::r5()const 
{
   return intrinseque().sensor().distortion().r5();
}


double & cgeometry::r7()
{
   return intrinseque().sensor().distortion().r7();
}

const double & cgeometry::r7()const 
{
   return intrinseque().sensor().distortion().r7();
}


cdistortion & cgeometry::distortion()
{
   return intrinseque().sensor().distortion();
}

const cdistortion & cgeometry::distortion()const 
{
   return intrinseque().sensor().distortion();
}


csensor & cgeometry::sensor()
{
   return intrinseque().sensor();
}

const csensor & cgeometry::sensor()const 
{
   return intrinseque().sensor();
}


cintrinseque & cgeometry::intrinseque()
{
   return mintrinseque;
}

const cintrinseque & cgeometry::intrinseque()const 
{
   return mintrinseque;
}

cElXMLTree * ToXMLTree(const cgeometry & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"geometry",eXMLBranche);
   aRes->AddFils(ToXMLTree(anObj.extrinseque())->ReTagThis("extrinseque"));
   aRes->AddFils(ToXMLTree(anObj.intrinseque())->ReTagThis("intrinseque"));
  return aRes;
}

void xml_init(cgeometry & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.extrinseque(),aTree->Get("extrinseque",1)); //tototo 

   xml_init(anObj.intrinseque(),aTree->Get("intrinseque",1)); //tototo 
}


double & corientation::version()
{
   return mversion;
}

const double & corientation::version()const 
{
   return mversion;
}


std::string & corientation::image_name()
{
   return auxiliarydata().image_name();
}

const std::string & corientation::image_name()const 
{
   return auxiliarydata().image_name();
}


std::string & corientation::stereopolis()
{
   return auxiliarydata().stereopolis();
}

const std::string & corientation::stereopolis()const 
{
   return auxiliarydata().stereopolis();
}


cXML_Date & corientation::image_date()
{
   return auxiliarydata().image_date();
}

const cXML_Date & corientation::image_date()const 
{
   return auxiliarydata().image_date();
}


std::list< std::string > & corientation::samples()
{
   return auxiliarydata().samples();
}

const std::list< std::string > & corientation::samples()const 
{
   return auxiliarydata().samples();
}


cauxiliarydata & corientation::auxiliarydata()
{
   return mauxiliarydata;
}

const cauxiliarydata & corientation::auxiliarydata()const 
{
   return mauxiliarydata;
}


ceuclidien & corientation::euclidien()
{
   return geometry().extrinseque().systeme().euclidien();
}

const ceuclidien & corientation::euclidien()const 
{
   return geometry().extrinseque().systeme().euclidien();
}


std::string & corientation::geodesique()
{
   return geometry().extrinseque().systeme().geodesique();
}

const std::string & corientation::geodesique()const 
{
   return geometry().extrinseque().systeme().geodesique();
}


csysteme & corientation::systeme()
{
   return geometry().extrinseque().systeme();
}

const csysteme & corientation::systeme()const 
{
   return geometry().extrinseque().systeme();
}


std::string & corientation::grid_alti()
{
   return geometry().extrinseque().grid_alti();
}

const std::string & corientation::grid_alti()const 
{
   return geometry().extrinseque().grid_alti();
}


double & corientation::easting()
{
   return geometry().extrinseque().sommet().easting();
}

const double & corientation::easting()const 
{
   return geometry().extrinseque().sommet().easting();
}


double & corientation::northing()
{
   return geometry().extrinseque().sommet().northing();
}

const double & corientation::northing()const 
{
   return geometry().extrinseque().sommet().northing();
}


double & corientation::altitude()
{
   return geometry().extrinseque().sommet().altitude();
}

const double & corientation::altitude()const 
{
   return geometry().extrinseque().sommet().altitude();
}


csommet & corientation::sommet()
{
   return geometry().extrinseque().sommet();
}

const csommet & corientation::sommet()const 
{
   return geometry().extrinseque().sommet();
}


bool & corientation::Image2Ground()
{
   return geometry().extrinseque().rotation().Image2Ground();
}

const bool & corientation::Image2Ground()const 
{
   return geometry().extrinseque().rotation().Image2Ground();
}


cXML_LinePt3d & corientation::l1()
{
   return geometry().extrinseque().rotation().mat3d().l1();
}

const cXML_LinePt3d & corientation::l1()const 
{
   return geometry().extrinseque().rotation().mat3d().l1();
}


cXML_LinePt3d & corientation::l2()
{
   return geometry().extrinseque().rotation().mat3d().l2();
}

const cXML_LinePt3d & corientation::l2()const 
{
   return geometry().extrinseque().rotation().mat3d().l2();
}


cXML_LinePt3d & corientation::l3()
{
   return geometry().extrinseque().rotation().mat3d().l3();
}

const cXML_LinePt3d & corientation::l3()const 
{
   return geometry().extrinseque().rotation().mat3d().l3();
}


cmat3d & corientation::mat3d()
{
   return geometry().extrinseque().rotation().mat3d();
}

const cmat3d & corientation::mat3d()const 
{
   return geometry().extrinseque().rotation().mat3d();
}


crotation & corientation::rotation()
{
   return geometry().extrinseque().rotation();
}

const crotation & corientation::rotation()const 
{
   return geometry().extrinseque().rotation();
}


cextrinseque & corientation::extrinseque()
{
   return geometry().extrinseque();
}

const cextrinseque & corientation::extrinseque()const 
{
   return geometry().extrinseque();
}


std::string & corientation::name()
{
   return geometry().intrinseque().sensor().name();
}

const std::string & corientation::name()const 
{
   return geometry().intrinseque().sensor().name();
}


cXML_Date & corientation::calibration_date()
{
   return geometry().intrinseque().sensor().calibration_date();
}

const cXML_Date & corientation::calibration_date()const 
{
   return geometry().intrinseque().sensor().calibration_date();
}


std::string & corientation::serial_number()
{
   return geometry().intrinseque().sensor().serial_number();
}

const std::string & corientation::serial_number()const 
{
   return geometry().intrinseque().sensor().serial_number();
}


int & corientation::width()
{
   return geometry().intrinseque().sensor().image_size().width();
}

const int & corientation::width()const 
{
   return geometry().intrinseque().sensor().image_size().width();
}


int & corientation::height()
{
   return geometry().intrinseque().sensor().image_size().height();
}

const int & corientation::height()const 
{
   return geometry().intrinseque().sensor().image_size().height();
}


cimage_size & corientation::image_size()
{
   return geometry().intrinseque().sensor().image_size();
}

const cimage_size & corientation::image_size()const 
{
   return geometry().intrinseque().sensor().image_size();
}


cppa & corientation::ppa()
{
   return geometry().intrinseque().sensor().ppa();
}

const cppa & corientation::ppa()const 
{
   return geometry().intrinseque().sensor().ppa();
}


cpps & corientation::pps()
{
   return geometry().intrinseque().sensor().distortion().pps();
}

const cpps & corientation::pps()const 
{
   return geometry().intrinseque().sensor().distortion().pps();
}


double & corientation::r1()
{
   return geometry().intrinseque().sensor().distortion().r1();
}

const double & corientation::r1()const 
{
   return geometry().intrinseque().sensor().distortion().r1();
}


double & corientation::r3()
{
   return geometry().intrinseque().sensor().distortion().r3();
}

const double & corientation::r3()const 
{
   return geometry().intrinseque().sensor().distortion().r3();
}


double & corientation::r5()
{
   return geometry().intrinseque().sensor().distortion().r5();
}

const double & corientation::r5()const 
{
   return geometry().intrinseque().sensor().distortion().r5();
}


double & corientation::r7()
{
   return geometry().intrinseque().sensor().distortion().r7();
}

const double & corientation::r7()const 
{
   return geometry().intrinseque().sensor().distortion().r7();
}


cdistortion & corientation::distortion()
{
   return geometry().intrinseque().sensor().distortion();
}

const cdistortion & corientation::distortion()const 
{
   return geometry().intrinseque().sensor().distortion();
}


csensor & corientation::sensor()
{
   return geometry().intrinseque().sensor();
}

const csensor & corientation::sensor()const 
{
   return geometry().intrinseque().sensor();
}


cintrinseque & corientation::intrinseque()
{
   return geometry().intrinseque();
}

const cintrinseque & corientation::intrinseque()const 
{
   return geometry().intrinseque();
}


cgeometry & corientation::geometry()
{
   return mgeometry;
}

const cgeometry & corientation::geometry()const 
{
   return mgeometry;
}

cElXMLTree * ToXMLTree(const corientation & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"orientation",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("version"),anObj.version())->ReTagThis("version"));
   aRes->AddFils(ToXMLTree(anObj.auxiliarydata())->ReTagThis("auxiliarydata"));
   aRes->AddFils(ToXMLTree(anObj.geometry())->ReTagThis("geometry"));
  return aRes;
}

void xml_init(corientation & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.version(),aTree->Get("version",1)); //tototo 

   xml_init(anObj.auxiliarydata(),aTree->Get("auxiliarydata",1)); //tototo 

   xml_init(anObj.geometry(),aTree->Get("geometry",1)); //tototo 
}


std::list< std::string > & cOneSolImageSec::Images()
{
   return mImages;
}

const std::list< std::string > & cOneSolImageSec::Images()const 
{
   return mImages;
}


double & cOneSolImageSec::Coverage()
{
   return mCoverage;
}

const double & cOneSolImageSec::Coverage()const 
{
   return mCoverage;
}


double & cOneSolImageSec::Score()
{
   return mScore;
}

const double & cOneSolImageSec::Score()const 
{
   return mScore;
}

cElXMLTree * ToXMLTree(const cOneSolImageSec & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"OneSolImageSec",eXMLBranche);
  for
  (       std::list< std::string >::const_iterator it=anObj.Images().begin();
      it !=anObj.Images().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Images"),(*it))->ReTagThis("Images"));
   aRes->AddFils(::ToXMLTree(std::string("Coverage"),anObj.Coverage())->ReTagThis("Coverage"));
   aRes->AddFils(::ToXMLTree(std::string("Score"),anObj.Score())->ReTagThis("Score"));
  return aRes;
}

void xml_init(cOneSolImageSec & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Images(),aTree->GetAll("Images",false,1));

   xml_init(anObj.Coverage(),aTree->Get("Coverage",1)); //tototo 

   xml_init(anObj.Score(),aTree->Get("Score",1)); //tototo 
}


std::string & cImSecOfMaster::Master()
{
   return mMaster;
}

const std::string & cImSecOfMaster::Master()const 
{
   return mMaster;
}


std::list< cOneSolImageSec > & cImSecOfMaster::Sols()
{
   return mSols;
}

const std::list< cOneSolImageSec > & cImSecOfMaster::Sols()const 
{
   return mSols;
}

cElXMLTree * ToXMLTree(const cImSecOfMaster & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ImSecOfMaster",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("Master"),anObj.Master())->ReTagThis("Master"));
  for
  (       std::list< cOneSolImageSec >::const_iterator it=anObj.Sols().begin();
      it !=anObj.Sols().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("Sols"));
  return aRes;
}

void xml_init(cImSecOfMaster & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Master(),aTree->Get("Master",1)); //tototo 

   xml_init(anObj.Sols(),aTree->GetAll("Sols",false,1));
}


std::list< std::string > & cXmlExivEntry::Names()
{
   return mNames;
}

const std::list< std::string > & cXmlExivEntry::Names()const 
{
   return mNames;
}


double & cXmlExivEntry::Focale()
{
   return mFocale;
}

const double & cXmlExivEntry::Focale()const 
{
   return mFocale;
}

cElXMLTree * ToXMLTree(const cXmlExivEntry & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"XmlExivEntry",eXMLBranche);
  for
  (       std::list< std::string >::const_iterator it=anObj.Names().begin();
      it !=anObj.Names().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Names"),(*it))->ReTagThis("Names"));
   aRes->AddFils(::ToXMLTree(std::string("Focale"),anObj.Focale())->ReTagThis("Focale"));
  return aRes;
}

void xml_init(cXmlExivEntry & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.Names(),aTree->GetAll("Names",false,1));

   xml_init(anObj.Focale(),aTree->Get("Focale",1)); //tototo 
}


int & cXmlDataBase::MajNumVers()
{
   return mMajNumVers;
}

const int & cXmlDataBase::MajNumVers()const 
{
   return mMajNumVers;
}


int & cXmlDataBase::MinNumVers()
{
   return mMinNumVers;
}

const int & cXmlDataBase::MinNumVers()const 
{
   return mMinNumVers;
}


std::list< cXmlExivEntry > & cXmlDataBase::Exiv()
{
   return mExiv;
}

const std::list< cXmlExivEntry > & cXmlDataBase::Exiv()const 
{
   return mExiv;
}

cElXMLTree * ToXMLTree(const cXmlDataBase & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"XmlDataBase",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("MajNumVers"),anObj.MajNumVers())->ReTagThis("MajNumVers"));
   aRes->AddFils(::ToXMLTree(std::string("MinNumVers"),anObj.MinNumVers())->ReTagThis("MinNumVers"));
  for
  (       std::list< cXmlExivEntry >::const_iterator it=anObj.Exiv().begin();
      it !=anObj.Exiv().end();
      it++
  ) 
      aRes->AddFils(ToXMLTree((*it))->ReTagThis("Exiv"));
  return aRes;
}

void xml_init(cXmlDataBase & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.MajNumVers(),aTree->Get("MajNumVers",1)); //tototo 

   xml_init(anObj.MinNumVers(),aTree->Get("MinNumVers",1)); //tototo 

   xml_init(anObj.Exiv(),aTree->GetAll("Exiv",false,1));
}


std::string & cListImByDelta::KeySplitName()
{
   return mKeySplitName;
}

const std::string & cListImByDelta::KeySplitName()const 
{
   return mKeySplitName;
}


std::list< int > & cListImByDelta::Delta()
{
   return mDelta;
}

const std::list< int > & cListImByDelta::Delta()const 
{
   return mDelta;
}

cElXMLTree * ToXMLTree(const cListImByDelta & anObj)
{
  cElXMLTree * aRes = new cElXMLTree((cElXMLTree *)0,"ListImByDelta",eXMLBranche);
   aRes->AddFils(::ToXMLTree(std::string("KeySplitName"),anObj.KeySplitName())->ReTagThis("KeySplitName"));
  for
  (       std::list< int >::const_iterator it=anObj.Delta().begin();
      it !=anObj.Delta().end();
      it++
  ) 
      aRes->AddFils(::ToXMLTree(std::string("Delta"),(*it))->ReTagThis("Delta"));
  return aRes;
}

void xml_init(cListImByDelta & anObj,cElXMLTree * aTree)
{
   if (aTree==0) return;

   xml_init(anObj.KeySplitName(),aTree->Get("KeySplitName",1)); //tototo 

   xml_init(anObj.Delta(),aTree->GetAll("Delta",false,1));
}

};
