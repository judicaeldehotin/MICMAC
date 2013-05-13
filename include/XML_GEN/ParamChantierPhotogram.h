#include "StdAfx.h"
//#include "general/all.h"
//#include "private/all.h"
#ifndef Define_NotPCP
#define Define_NotPCP
namespace NS_ParamChantierPhotogram{
typedef enum
{
  eOrtho,
  eUrbanMNE,
  eGeomImage,
  eNbTypesMNE
} eTypeMalt;
void xml_init(eTypeMalt & aVal,cElXMLTree * aTree);
std::string  eToString(const eTypeMalt & aVal);

eTypeMalt  Str2eTypeMalt(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypeMalt & anObj);

typedef enum
{
  eAppEgels,
  eAppGeoCub,
  eAppInFile,
  eAppXML,
  eNbTypeApp
} eTypeFichierApp;
void xml_init(eTypeFichierApp & aVal,cElXMLTree * aTree);
std::string  eToString(const eTypeFichierApp & aVal);

eTypeFichierApp  Str2eTypeFichierApp(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypeFichierApp & anObj);

typedef enum
{
  eOriTxtAgiSoft,
  eOriBluh,
  eOriTxtInFile,
  eNbTypeOriTxt
} eTypeFichierOriTxt;
void xml_init(eTypeFichierOriTxt & aVal,cElXMLTree * aTree);
std::string  eToString(const eTypeFichierOriTxt & aVal);

eTypeFichierOriTxt  Str2eTypeFichierOriTxt(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypeFichierOriTxt & anObj);

typedef enum
{
  eImpaintL2,
  eImpaintMNT
} eImpaintMethod;
void xml_init(eImpaintMethod & aVal,cElXMLTree * aTree);
std::string  eToString(const eImpaintMethod & aVal);

eImpaintMethod  Str2eImpaintMethod(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eImpaintMethod & anObj);

typedef enum
{
  eTN_u_int1,
  eTN_int1,
  eTN_u_int2,
  eTN_int2,
  eTN_int4,
  eTN_float,
  eTN_double,
  eTN_Bits1MSBF
} eTypeNumerique;
void xml_init(eTypeNumerique & aVal,cElXMLTree * aTree);
std::string  eToString(const eTypeNumerique & aVal);

eTypeNumerique  Str2eTypeNumerique(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypeNumerique & anObj);

typedef enum
{
  eComprTiff_None,
  eComprTiff_LZW,
  eComprTiff_FAX4,
  eComprTiff_PackBits
} eComprTiff;
void xml_init(eComprTiff & aVal,cElXMLTree * aTree);
std::string  eToString(const eComprTiff & aVal);

eComprTiff  Str2eComprTiff(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eComprTiff & anObj);

typedef enum
{
  ePCR_Atgt,
  ePCR_2SinAtgtS2
} eTypePreCondRad;
void xml_init(eTypePreCondRad & aVal,cElXMLTree * aTree);
std::string  eToString(const eTypePreCondRad & aVal);

eTypePreCondRad  Str2eTypePreCondRad(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypePreCondRad & anObj);

typedef enum
{
  eGeomMNTCarto,
  eGeomMNTEuclid,
  eGeomMNTFaisceauIm1PrCh_Px1D,
  eGeomMNTFaisceauIm1PrCh_Px2D,
  eGeomMNTFaisceauIm1ZTerrain_Px1D,
  eGeomMNTFaisceauIm1ZTerrain_Px2D,
  eGeomPxBiDim,
  eNoGeomMNT,
  eGeomMNTFaisceauPrChSpherik
} eModeGeomMNT;
void xml_init(eModeGeomMNT & aVal,cElXMLTree * aTree);
std::string  eToString(const eModeGeomMNT & aVal);

eModeGeomMNT  Str2eModeGeomMNT(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eModeGeomMNT & anObj);

typedef enum
{
  eModeLeBrisPP,
  eModeAutopano
} eModeBinSift;
void xml_init(eModeBinSift & aVal,cElXMLTree * aTree);
std::string  eToString(const eModeBinSift & aVal);

eModeBinSift  Str2eModeBinSift(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eModeBinSift & anObj);

typedef enum
{
  eSysPlein,
  eSysCreuxMap,
  eSysCreuxFixe,
  eSysL1Barrodale,
  eSysL2BlocSym
} eModeSolveurEq;
void xml_init(eModeSolveurEq & aVal,cElXMLTree * aTree);
std::string  eToString(const eModeSolveurEq & aVal);

eModeSolveurEq  Str2eModeSolveurEq(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eModeSolveurEq & anObj);

typedef enum
{
  eUniteAngleDegre,
  eUniteAngleGrade,
  eUniteAngleRadian
} eUniteAngulaire;
void xml_init(eUniteAngulaire & aVal,cElXMLTree * aTree);
std::string  eToString(const eUniteAngulaire & aVal);

eUniteAngulaire  Str2eUniteAngulaire(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eUniteAngulaire & anObj);

typedef enum
{
  eCPPFiges,
  eCPPLies,
  eCPPLibres
} eDegreLiberteCPP;
void xml_init(eDegreLiberteCPP & aVal,cElXMLTree * aTree);
std::string  eToString(const eDegreLiberteCPP & aVal);

eDegreLiberteCPP  Str2eDegreLiberteCPP(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eDegreLiberteCPP & anObj);

typedef enum
{
  eModeleEbner,
  eModeleDCBrown,
  eModelePolyDeg2,
  eModelePolyDeg3,
  eModelePolyDeg4,
  eModelePolyDeg5,
  eModelePolyDeg6,
  eModelePolyDeg7,
  eModele_FishEye_10_5_5,
  eModele_EquiSolid_FishEye_10_5_5,
  eModele_DRad_PPaEqPPs,
  eModele_Fraser_PPaEqPPs
} eModelesCalibUnif;
void xml_init(eModelesCalibUnif & aVal,cElXMLTree * aTree);
std::string  eToString(const eModelesCalibUnif & aVal);

eModelesCalibUnif  Str2eModelesCalibUnif(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eModelesCalibUnif & anObj);

typedef enum
{
  eProjStenope,
  eProjOrthographique
} eTypeProjectionCam;
void xml_init(eTypeProjectionCam & aVal,cElXMLTree * aTree);
std::string  eToString(const eTypeProjectionCam & aVal);

eTypeProjectionCam  Str2eTypeProjectionCam(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypeProjectionCam & anObj);

typedef enum
{
  eTC_WGS84,
  eTC_GeoCentr,
  eTC_RTL,
  eTC_Polyn,
  eTC_Unknown,
  eTC_Lambert93,
  eTC_LambertCC,
  eTC_Proj4
} eTypeCoord;
void xml_init(eTypeCoord & aVal,cElXMLTree * aTree);
std::string  eToString(const eTypeCoord & aVal);

eTypeCoord  Str2eTypeCoord(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTypeCoord & anObj);

class cMicMacConfiguration
{
    public:
        friend void xml_init(cMicMacConfiguration & anObj,cElXMLTree * aTree);


        std::string & DirInstall();
        const std::string & DirInstall()const ;

        int & NbProcess();
        const int & NbProcess()const ;
    private:
        std::string mDirInstall;
        int mNbProcess;
};
cElXMLTree * ToXMLTree(const cMicMacConfiguration &);

/******************************************************/
/******************************************************/
/******************************************************/
class cBasicSystemeCoord
{
    public:
        friend void xml_init(cBasicSystemeCoord & anObj,cElXMLTree * aTree);


        eTypeCoord & TypeCoord();
        const eTypeCoord & TypeCoord()const ;

        std::vector< double > & AuxR();
        const std::vector< double > & AuxR()const ;

        std::vector< int > & AuxI();
        const std::vector< int > & AuxI()const ;

        std::vector< std::string > & AuxStr();
        const std::vector< std::string > & AuxStr()const ;

        cTplValGesInit< bool > & ByFile();
        const cTplValGesInit< bool > & ByFile()const ;

        std::vector< eUniteAngulaire > & AuxRUnite();
        const std::vector< eUniteAngulaire > & AuxRUnite()const ;
    private:
        eTypeCoord mTypeCoord;
        std::vector< double > mAuxR;
        std::vector< int > mAuxI;
        std::vector< std::string > mAuxStr;
        cTplValGesInit< bool > mByFile;
        std::vector< eUniteAngulaire > mAuxRUnite;
};
cElXMLTree * ToXMLTree(const cBasicSystemeCoord &);

/******************************************************/
/******************************************************/
/******************************************************/
class cSystemeCoord
{
    public:
        friend void xml_init(cSystemeCoord & anObj,cElXMLTree * aTree);


        cTplValGesInit< std::string > & Comment();
        const cTplValGesInit< std::string > & Comment()const ;

        std::vector< cBasicSystemeCoord > & BSC();
        const std::vector< cBasicSystemeCoord > & BSC()const ;
    private:
        cTplValGesInit< std::string > mComment;
        std::vector< cBasicSystemeCoord > mBSC;
};
cElXMLTree * ToXMLTree(const cSystemeCoord &);

/******************************************************/
/******************************************************/
/******************************************************/
class cChangementCoordonnees
{
    public:
        friend void xml_init(cChangementCoordonnees & anObj,cElXMLTree * aTree);


        cSystemeCoord & SystemeSource();
        const cSystemeCoord & SystemeSource()const ;

        cSystemeCoord & SystemeCible();
        const cSystemeCoord & SystemeCible()const ;
    private:
        cSystemeCoord mSystemeSource;
        cSystemeCoord mSystemeCible;
};
cElXMLTree * ToXMLTree(const cChangementCoordonnees &);

/******************************************************/
/******************************************************/
/******************************************************/
class cFileOriMnt
{
    public:
        friend void xml_init(cFileOriMnt & anObj,cElXMLTree * aTree);


        std::string & NameFileMnt();
        const std::string & NameFileMnt()const ;

        cTplValGesInit< std::string > & NameFileMasque();
        const cTplValGesInit< std::string > & NameFileMasque()const ;

        Pt2di & NombrePixels();
        const Pt2di & NombrePixels()const ;

        Pt2dr & OriginePlani();
        const Pt2dr & OriginePlani()const ;

        Pt2dr & ResolutionPlani();
        const Pt2dr & ResolutionPlani()const ;

        double & OrigineAlti();
        const double & OrigineAlti()const ;

        double & ResolutionAlti();
        const double & ResolutionAlti()const ;

        cTplValGesInit< int > & NumZoneLambert();
        const cTplValGesInit< int > & NumZoneLambert()const ;

        eModeGeomMNT & Geometrie();
        const eModeGeomMNT & Geometrie()const ;

        cTplValGesInit< Pt2dr > & OrigineTgtLoc();
        const cTplValGesInit< Pt2dr > & OrigineTgtLoc()const ;
    private:
        std::string mNameFileMnt;
        cTplValGesInit< std::string > mNameFileMasque;
        Pt2di mNombrePixels;
        Pt2dr mOriginePlani;
        Pt2dr mResolutionPlani;
        double mOrigineAlti;
        double mResolutionAlti;
        cTplValGesInit< int > mNumZoneLambert;
        eModeGeomMNT mGeometrie;
        cTplValGesInit< Pt2dr > mOrigineTgtLoc;
};
cElXMLTree * ToXMLTree(const cFileOriMnt &);

/******************************************************/
/******************************************************/
/******************************************************/
class cRefPlani
{
    public:
        friend void xml_init(cRefPlani & anObj,cElXMLTree * aTree);


        Pt2dr & Origine();
        const Pt2dr & Origine()const ;

        Pt2dr & Resolution();
        const Pt2dr & Resolution()const ;
    private:
        Pt2dr mOrigine;
        Pt2dr mResolution;
};
cElXMLTree * ToXMLTree(const cRefPlani &);

/******************************************************/
/******************************************************/
/******************************************************/
class cRefAlti
{
    public:
        friend void xml_init(cRefAlti & anObj,cElXMLTree * aTree);


        double & Origine();
        const double & Origine()const ;

        double & Resolution();
        const double & Resolution()const ;
    private:
        double mOrigine;
        double mResolution;
};
cElXMLTree * ToXMLTree(const cRefAlti &);

class cGestionAltimetrie
{
    public:
        friend void xml_init(cGestionAltimetrie & anObj,cElXMLTree * aTree);


        cTplValGesInit< cRefAlti > & RefAlti();
        const cTplValGesInit< cRefAlti > & RefAlti()const ;

        cTplValGesInit< double > & ZMoyen();
        const cTplValGesInit< double > & ZMoyen()const ;
    private:
        cTplValGesInit< cRefAlti > mRefAlti;
        cTplValGesInit< double > mZMoyen;
};
cElXMLTree * ToXMLTree(const cGestionAltimetrie &);

/******************************************************/
/******************************************************/
/******************************************************/
class cXmlGeoRefFile
{
    public:
        friend void xml_init(cXmlGeoRefFile & anObj,cElXMLTree * aTree);


        cTplValGesInit< cSystemeCoord > & SysCo();
        const cTplValGesInit< cSystemeCoord > & SysCo()const ;

        cRefPlani & RefPlani();
        const cRefPlani & RefPlani()const ;

        cTplValGesInit< cRefAlti > & RefAlti();
        const cTplValGesInit< cRefAlti > & RefAlti()const ;

        cTplValGesInit< double > & ZMoyen();
        const cTplValGesInit< double > & ZMoyen()const ;

        cGestionAltimetrie & GestionAltimetrie();
        const cGestionAltimetrie & GestionAltimetrie()const ;
    private:
        cTplValGesInit< cSystemeCoord > mSysCo;
        cRefPlani mRefPlani;
        cGestionAltimetrie mGestionAltimetrie;
};
cElXMLTree * ToXMLTree(const cXmlGeoRefFile &);

/******************************************************/
/******************************************************/
/******************************************************/
class cSpecExtractFromFile
{
    public:
        friend void xml_init(cSpecExtractFromFile & anObj,cElXMLTree * aTree);


        std::string & NameFile();
        const std::string & NameFile()const ;

        std::string & NameTag();
        const std::string & NameTag()const ;

        cTplValGesInit< bool > & AutorizeNonExisting();
        const cTplValGesInit< bool > & AutorizeNonExisting()const ;
    private:
        std::string mNameFile;
        std::string mNameTag;
        cTplValGesInit< bool > mAutorizeNonExisting;
};
cElXMLTree * ToXMLTree(const cSpecExtractFromFile &);

/******************************************************/
/******************************************************/
/******************************************************/
class cSpecifFormatRaw
{
    public:
        friend void xml_init(cSpecifFormatRaw & anObj,cElXMLTree * aTree);


        std::string & NameFile();
        const std::string & NameFile()const ;

        Pt2di & Sz();
        const Pt2di & Sz()const ;

        bool & MSBF();
        const bool & MSBF()const ;

        int & NbBitsParPixel();
        const int & NbBitsParPixel()const ;

        bool & IntegerType();
        const bool & IntegerType()const ;

        bool & SignedType();
        const bool & SignedType()const ;
    private:
        std::string mNameFile;
        Pt2di mSz;
        bool mMSBF;
        int mNbBitsParPixel;
        bool mIntegerType;
        bool mSignedType;
};
cElXMLTree * ToXMLTree(const cSpecifFormatRaw &);

/******************************************************/
/******************************************************/
/******************************************************/
typedef enum
{
  eTotoGeomMECIm1
} eTotoModeGeomMEC;
void xml_init(eTotoModeGeomMEC & aVal,cElXMLTree * aTree);
std::string  eToString(const eTotoModeGeomMEC & aVal);

eTotoModeGeomMEC  Str2eTotoModeGeomMEC(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eTotoModeGeomMEC & anObj);

class cCM_Set
{
    public:
        friend void xml_init(cCM_Set & anObj,cElXMLTree * aTree);


        std::string & KeySet();
        const std::string & KeySet()const ;

        cTplValGesInit< std::string > & KeyAssoc();
        const cTplValGesInit< std::string > & KeyAssoc()const ;

        std::string & NameVarMap();
        const std::string & NameVarMap()const ;
    private:
        std::string mKeySet;
        cTplValGesInit< std::string > mKeyAssoc;
        std::string mNameVarMap;
};
cElXMLTree * ToXMLTree(const cCM_Set &);

class cModeCmdMapeur
{
    public:
        friend void xml_init(cModeCmdMapeur & anObj,cElXMLTree * aTree);


        cTplValGesInit< std::string > & CM_One();
        const cTplValGesInit< std::string > & CM_One()const ;

        std::string & KeySet();
        const std::string & KeySet()const ;

        cTplValGesInit< std::string > & KeyAssoc();
        const cTplValGesInit< std::string > & KeyAssoc()const ;

        std::string & NameVarMap();
        const std::string & NameVarMap()const ;

        cTplValGesInit< cCM_Set > & CM_Set();
        const cTplValGesInit< cCM_Set > & CM_Set()const ;
    private:
        cTplValGesInit< std::string > mCM_One;
        cTplValGesInit< cCM_Set > mCM_Set;
};
cElXMLTree * ToXMLTree(const cModeCmdMapeur &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCmdMapRel
{
    public:
        friend void xml_init(cCmdMapRel & anObj,cElXMLTree * aTree);


        std::string & KeyRel();
        const std::string & KeyRel()const ;

        std::string & NameArc();
        const std::string & NameArc()const ;
    private:
        std::string mKeyRel;
        std::string mNameArc;
};
cElXMLTree * ToXMLTree(const cCmdMapRel &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCMVA
{
    public:
        friend void xml_init(cCMVA & anObj,cElXMLTree * aTree);


        std::list< cCpleString > & NV();
        const std::list< cCpleString > & NV()const ;
    private:
        std::list< cCpleString > mNV;
};
cElXMLTree * ToXMLTree(const cCMVA &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCmdMappeur
{
    public:
        friend void xml_init(cCmdMappeur & anObj,cElXMLTree * aTree);


        bool & ActivateCmdMap();
        const bool & ActivateCmdMap()const ;

        cTplValGesInit< std::string > & CM_One();
        const cTplValGesInit< std::string > & CM_One()const ;

        std::string & KeySet();
        const std::string & KeySet()const ;

        cTplValGesInit< std::string > & KeyAssoc();
        const cTplValGesInit< std::string > & KeyAssoc()const ;

        std::string & NameVarMap();
        const std::string & NameVarMap()const ;

        cTplValGesInit< cCM_Set > & CM_Set();
        const cTplValGesInit< cCM_Set > & CM_Set()const ;

        cModeCmdMapeur & ModeCmdMapeur();
        const cModeCmdMapeur & ModeCmdMapeur()const ;

        std::string & KeyRel();
        const std::string & KeyRel()const ;

        std::string & NameArc();
        const std::string & NameArc()const ;

        cTplValGesInit< cCmdMapRel > & CmdMapRel();
        const cTplValGesInit< cCmdMapRel > & CmdMapRel()const ;

        std::list< cCMVA > & CMVA();
        const std::list< cCMVA > & CMVA()const ;

        cTplValGesInit< std::string > & ByMkF();
        const cTplValGesInit< std::string > & ByMkF()const ;

        cTplValGesInit< std::string > & KeyTargetMkF();
        const cTplValGesInit< std::string > & KeyTargetMkF()const ;
    private:
        bool mActivateCmdMap;
        cModeCmdMapeur mModeCmdMapeur;
        cTplValGesInit< cCmdMapRel > mCmdMapRel;
        std::list< cCMVA > mCMVA;
        cTplValGesInit< std::string > mByMkF;
        cTplValGesInit< std::string > mKeyTargetMkF;
};
cElXMLTree * ToXMLTree(const cCmdMappeur &);

/******************************************************/
/******************************************************/
/******************************************************/
class cOneCmdPar
{
    public:
        friend void xml_init(cOneCmdPar & anObj,cElXMLTree * aTree);


        std::list< std::string > & OneCmdSer();
        const std::list< std::string > & OneCmdSer()const ;
    private:
        std::list< std::string > mOneCmdSer;
};
cElXMLTree * ToXMLTree(const cOneCmdPar &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCmdExePar
{
    public:
        friend void xml_init(cCmdExePar & anObj,cElXMLTree * aTree);


        cTplValGesInit< std::string > & NameMkF();
        const cTplValGesInit< std::string > & NameMkF()const ;

        std::list< cOneCmdPar > & OneCmdPar();
        const std::list< cOneCmdPar > & OneCmdPar()const ;
    private:
        cTplValGesInit< std::string > mNameMkF;
        std::list< cOneCmdPar > mOneCmdPar;
};
cElXMLTree * ToXMLTree(const cCmdExePar &);

/******************************************************/
/******************************************************/
/******************************************************/
class cPt3drEntries
{
    public:
        friend void xml_init(cPt3drEntries & anObj,cElXMLTree * aTree);


        std::string & Key();
        const std::string & Key()const ;

        Pt3dr & Val();
        const Pt3dr & Val()const ;
    private:
        std::string mKey;
        Pt3dr mVal;
};
cElXMLTree * ToXMLTree(const cPt3drEntries &);

class cBasesPt3dr
{
    public:
        friend void xml_init(cBasesPt3dr & anObj,cElXMLTree * aTree);


        std::string & NameBase();
        const std::string & NameBase()const ;

        std::list< cPt3drEntries > & Pt3drEntries();
        const std::list< cPt3drEntries > & Pt3drEntries()const ;
    private:
        std::string mNameBase;
        std::list< cPt3drEntries > mPt3drEntries;
};
cElXMLTree * ToXMLTree(const cBasesPt3dr &);

/******************************************************/
/******************************************************/
/******************************************************/
class cScalEntries
{
    public:
        friend void xml_init(cScalEntries & anObj,cElXMLTree * aTree);


        std::string & Key();
        const std::string & Key()const ;

        double & Val();
        const double & Val()const ;
    private:
        std::string mKey;
        double mVal;
};
cElXMLTree * ToXMLTree(const cScalEntries &);

class cBasesScal
{
    public:
        friend void xml_init(cBasesScal & anObj,cElXMLTree * aTree);


        std::string & NameBase();
        const std::string & NameBase()const ;

        std::list< cScalEntries > & ScalEntries();
        const std::list< cScalEntries > & ScalEntries()const ;
    private:
        std::string mNameBase;
        std::list< cScalEntries > mScalEntries;
};
cElXMLTree * ToXMLTree(const cBasesScal &);

/******************************************************/
/******************************************************/
/******************************************************/
class cBaseDataCD
{
    public:
        friend void xml_init(cBaseDataCD & anObj,cElXMLTree * aTree);


        std::list< cBasesPt3dr > & BasesPt3dr();
        const std::list< cBasesPt3dr > & BasesPt3dr()const ;

        std::list< cBasesScal > & BasesScal();
        const std::list< cBasesScal > & BasesScal()const ;
    private:
        std::list< cBasesPt3dr > mBasesPt3dr;
        std::list< cBasesScal > mBasesScal;
};
cElXMLTree * ToXMLTree(const cBaseDataCD &);

/******************************************************/
/******************************************************/
/******************************************************/
class cParamVolChantierPhotogram
{
    public:
        friend void xml_init(cParamVolChantierPhotogram & anObj,cElXMLTree * aTree);


        std::string & Directory();
        const std::string & Directory()const ;

        cTplValGesInit< std::string > & DirOrientations();
        const cTplValGesInit< std::string > & DirOrientations()const ;

        cElRegex_Ptr & NameSelector();
        const cElRegex_Ptr & NameSelector()const ;

        cElRegex_Ptr & BandeIdSelector();
        const cElRegex_Ptr & BandeIdSelector()const ;

        std::string & NomBandeId();
        const std::string & NomBandeId()const ;

        std::string & NomIdInBande();
        const std::string & NomIdInBande()const ;

        std::string & NomImage();
        const std::string & NomImage()const ;

        cTplValGesInit< std::string > & DirImages();
        const cTplValGesInit< std::string > & DirImages()const ;
    private:
        std::string mDirectory;
        cTplValGesInit< std::string > mDirOrientations;
        cElRegex_Ptr mNameSelector;
        cElRegex_Ptr mBandeIdSelector;
        std::string mNomBandeId;
        std::string mNomIdInBande;
        std::string mNomImage;
        cTplValGesInit< std::string > mDirImages;
};
cElXMLTree * ToXMLTree(const cParamVolChantierPhotogram &);

/******************************************************/
/******************************************************/
/******************************************************/
class cParamChantierPhotogram
{
    public:
        friend void xml_init(cParamChantierPhotogram & anObj,cElXMLTree * aTree);


        std::list< cParamVolChantierPhotogram > & ParamVolChantierPhotogram();
        const std::list< cParamVolChantierPhotogram > & ParamVolChantierPhotogram()const ;
    private:
        std::list< cParamVolChantierPhotogram > mParamVolChantierPhotogram;
};
cElXMLTree * ToXMLTree(const cParamChantierPhotogram &);

/******************************************************/
/******************************************************/
/******************************************************/
class cPDV
{
    public:
        friend void xml_init(cPDV & anObj,cElXMLTree * aTree);


        std::string & Im();
        const std::string & Im()const ;

        std::string & Orient();
        const std::string & Orient()const ;

        std::string & IdInBande();
        const std::string & IdInBande()const ;

        std::string & Bande();
        const std::string & Bande()const ;
    private:
        std::string mIm;
        std::string mOrient;
        std::string mIdInBande;
        std::string mBande;
};
cElXMLTree * ToXMLTree(const cPDV &);

/******************************************************/
/******************************************************/
/******************************************************/
class cBandesChantierPhotogram
{
    public:
        friend void xml_init(cBandesChantierPhotogram & anObj,cElXMLTree * aTree);


        std::string & IdBande();
        const std::string & IdBande()const ;

        std::list< cPDV > & PDVs();
        const std::list< cPDV > & PDVs()const ;
    private:
        std::string mIdBande;
        std::list< cPDV > mPDVs;
};
cElXMLTree * ToXMLTree(const cBandesChantierPhotogram &);

class cVolChantierPhotogram
{
    public:
        friend void xml_init(cVolChantierPhotogram & anObj,cElXMLTree * aTree);


        std::list< cBandesChantierPhotogram > & BandesChantierPhotogram();
        const std::list< cBandesChantierPhotogram > & BandesChantierPhotogram()const ;
    private:
        std::list< cBandesChantierPhotogram > mBandesChantierPhotogram;
};
cElXMLTree * ToXMLTree(const cVolChantierPhotogram &);

/******************************************************/
/******************************************************/
/******************************************************/
class cChantierPhotogram
{
    public:
        friend void xml_init(cChantierPhotogram & anObj,cElXMLTree * aTree);


        std::list< cVolChantierPhotogram > & VolChantierPhotogram();
        const std::list< cVolChantierPhotogram > & VolChantierPhotogram()const ;
    private:
        std::list< cVolChantierPhotogram > mVolChantierPhotogram;
};
cElXMLTree * ToXMLTree(const cChantierPhotogram &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCplePDV
{
    public:
        friend void xml_init(cCplePDV & anObj,cElXMLTree * aTree);


        int & Id1();
        const int & Id1()const ;

        int & Id2();
        const int & Id2()const ;
    private:
        int mId1;
        int mId2;
};
cElXMLTree * ToXMLTree(const cCplePDV &);

/******************************************************/
/******************************************************/
/******************************************************/
class cGraphePdv
{
    public:
        friend void xml_init(cGraphePdv & anObj,cElXMLTree * aTree);


        Box2dr & BoxCh();
        const Box2dr & BoxCh()const ;

        std::vector< cPDV > & PDVs();
        const std::vector< cPDV > & PDVs()const ;

        std::list< cCplePDV > & CplePDV();
        const std::list< cCplePDV > & CplePDV()const ;
    private:
        Box2dr mBoxCh;
        std::vector< cPDV > mPDVs;
        std::list< cCplePDV > mCplePDV;
};
cElXMLTree * ToXMLTree(const cGraphePdv &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCercleRelief
{
    public:
        friend void xml_init(cCercleRelief & anObj,cElXMLTree * aTree);


        double & Rayon();
        const double & Rayon()const ;

        double & Profondeur();
        const double & Profondeur()const ;
    private:
        double mRayon;
        double mProfondeur;
};
cElXMLTree * ToXMLTree(const cCercleRelief &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCibleCalib
{
    public:
        friend void xml_init(cCibleCalib & anObj,cElXMLTree * aTree);


        int & Id();
        const int & Id()const ;

        cTplValGesInit< bool > & Negatif();
        const cTplValGesInit< bool > & Negatif()const ;

        Pt3dr & Position();
        const Pt3dr & Position()const ;

        Pt3dr & Normale();
        const Pt3dr & Normale()const ;

        std::vector< double > & Rayons();
        const std::vector< double > & Rayons()const ;

        bool & Ponctuel();
        const bool & Ponctuel()const ;

        bool & ReliefIsSortant();
        const bool & ReliefIsSortant()const ;

        std::vector< cCercleRelief > & CercleRelief();
        const std::vector< cCercleRelief > & CercleRelief()const ;

        std::string & NomType();
        const std::string & NomType()const ;

        int & Qualite();
        const int & Qualite()const ;

        cTplValGesInit< double > & FacteurElargRechCorrel();
        const cTplValGesInit< double > & FacteurElargRechCorrel()const ;

        cTplValGesInit< double > & FacteurElargRechRaffine();
        const cTplValGesInit< double > & FacteurElargRechRaffine()const ;
    private:
        int mId;
        cTplValGesInit< bool > mNegatif;
        Pt3dr mPosition;
        Pt3dr mNormale;
        std::vector< double > mRayons;
        bool mPonctuel;
        bool mReliefIsSortant;
        std::vector< cCercleRelief > mCercleRelief;
        std::string mNomType;
        int mQualite;
        cTplValGesInit< double > mFacteurElargRechCorrel;
        cTplValGesInit< double > mFacteurElargRechRaffine;
};
cElXMLTree * ToXMLTree(const cCibleCalib &);

/******************************************************/
/******************************************************/
/******************************************************/
class cPolygoneCalib
{
    public:
        friend void xml_init(cPolygoneCalib & anObj,cElXMLTree * aTree);


        std::string & Name();
        const std::string & Name()const ;

        std::vector< cCibleCalib > & Cibles();
        const std::vector< cCibleCalib > & Cibles()const ;
    private:
        std::string mName;
        std::vector< cCibleCalib > mCibles;
};
cElXMLTree * ToXMLTree(const cPolygoneCalib &);

/******************************************************/
/******************************************************/
/******************************************************/
class cPointesCibleAC
{
    public:
        friend void xml_init(cPointesCibleAC & anObj,cElXMLTree * aTree);


        std::string & NameIm();
        const std::string & NameIm()const ;

        Pt2dr & PtIm();
        const Pt2dr & PtIm()const ;
    private:
        std::string mNameIm;
        Pt2dr mPtIm;
};
cElXMLTree * ToXMLTree(const cPointesCibleAC &);

class cCibleACalcByLiaisons
{
    public:
        friend void xml_init(cCibleACalcByLiaisons & anObj,cElXMLTree * aTree);


        std::string & Name();
        const std::string & Name()const ;

        std::list< cPointesCibleAC > & PointesCibleAC();
        const std::list< cPointesCibleAC > & PointesCibleAC()const ;
    private:
        std::string mName;
        std::list< cPointesCibleAC > mPointesCibleAC;
};
cElXMLTree * ToXMLTree(const cCibleACalcByLiaisons &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCible2Rech
{
    public:
        friend void xml_init(cCible2Rech & anObj,cElXMLTree * aTree);


        cTplValGesInit< bool > & UseIt();
        const cTplValGesInit< bool > & UseIt()const ;

        std::vector< int > & Id();
        const std::vector< int > & Id()const ;
    private:
        cTplValGesInit< bool > mUseIt;
        std::vector< int > mId;
};
cElXMLTree * ToXMLTree(const cCible2Rech &);

/******************************************************/
/******************************************************/
/******************************************************/
class cIm2Select
{
    public:
        friend void xml_init(cIm2Select & anObj,cElXMLTree * aTree);


        cTplValGesInit< bool > & UseIt();
        const cTplValGesInit< bool > & UseIt()const ;

        std::vector< std::string > & Id();
        const std::vector< std::string > & Id()const ;
    private:
        cTplValGesInit< bool > mUseIt;
        std::vector< std::string > mId;
};
cElXMLTree * ToXMLTree(const cIm2Select &);

/******************************************************/
/******************************************************/
/******************************************************/
class cImageUseDirectPointeManuel
{
    public:
        friend void xml_init(cImageUseDirectPointeManuel & anObj,cElXMLTree * aTree);


        std::list< cElRegex_Ptr > & Id();
        const std::list< cElRegex_Ptr > & Id()const ;
    private:
        std::list< cElRegex_Ptr > mId;
};
cElXMLTree * ToXMLTree(const cImageUseDirectPointeManuel &);

/******************************************************/
/******************************************************/
/******************************************************/
class cExportAppuisAsDico
{
    public:
        friend void xml_init(cExportAppuisAsDico & anObj,cElXMLTree * aTree);


        std::string & NameDico();
        const std::string & NameDico()const ;

        Pt3dr & Incertitude();
        const Pt3dr & Incertitude()const ;
    private:
        std::string mNameDico;
        Pt3dr mIncertitude;
};
cElXMLTree * ToXMLTree(const cExportAppuisAsDico &);

/******************************************************/
/******************************************************/
/******************************************************/
class cComplParamEtalPoly
{
    public:
        friend void xml_init(cComplParamEtalPoly & anObj,cElXMLTree * aTree);


        std::list< cCibleACalcByLiaisons > & CibleACalcByLiaisons();
        const std::list< cCibleACalcByLiaisons > & CibleACalcByLiaisons()const ;

        cTplValGesInit< cCible2Rech > & Cible2Rech();
        const cTplValGesInit< cCible2Rech > & Cible2Rech()const ;

        cTplValGesInit< cIm2Select > & Im2Select();
        const cTplValGesInit< cIm2Select > & Im2Select()const ;

        cTplValGesInit< cImageUseDirectPointeManuel > & ImageUseDirectPointeManuel();
        const cTplValGesInit< cImageUseDirectPointeManuel > & ImageUseDirectPointeManuel()const ;

        std::string & NameDico();
        const std::string & NameDico()const ;

        Pt3dr & Incertitude();
        const Pt3dr & Incertitude()const ;

        cTplValGesInit< cExportAppuisAsDico > & ExportAppuisAsDico();
        const cTplValGesInit< cExportAppuisAsDico > & ExportAppuisAsDico()const ;
    private:
        std::list< cCibleACalcByLiaisons > mCibleACalcByLiaisons;
        cTplValGesInit< cCible2Rech > mCible2Rech;
        cTplValGesInit< cIm2Select > mIm2Select;
        cTplValGesInit< cImageUseDirectPointeManuel > mImageUseDirectPointeManuel;
        cTplValGesInit< cExportAppuisAsDico > mExportAppuisAsDico;
};
cElXMLTree * ToXMLTree(const cComplParamEtalPoly &);

/******************************************************/
/******************************************************/
/******************************************************/
class cOneAppuisDAF
{
    public:
        friend void xml_init(cOneAppuisDAF & anObj,cElXMLTree * aTree);


        Pt3dr & Pt();
        const Pt3dr & Pt()const ;

        std::string & NamePt();
        const std::string & NamePt()const ;

        Pt3dr & Incertitude();
        const Pt3dr & Incertitude()const ;
    private:
        Pt3dr mPt;
        std::string mNamePt;
        Pt3dr mIncertitude;
};
cElXMLTree * ToXMLTree(const cOneAppuisDAF &);

/******************************************************/
/******************************************************/
/******************************************************/
class cDicoAppuisFlottant
{
    public:
        friend void xml_init(cDicoAppuisFlottant & anObj,cElXMLTree * aTree);


        std::list< cOneAppuisDAF > & OneAppuisDAF();
        const std::list< cOneAppuisDAF > & OneAppuisDAF()const ;
    private:
        std::list< cOneAppuisDAF > mOneAppuisDAF;
};
cElXMLTree * ToXMLTree(const cDicoAppuisFlottant &);

/******************************************************/
/******************************************************/
/******************************************************/
class cOneModifIPF
{
    public:
        friend void xml_init(cOneModifIPF & anObj,cElXMLTree * aTree);


        std::string & KeyName();
        const std::string & KeyName()const ;

        Pt3dr & Incertitude();
        const Pt3dr & Incertitude()const ;

        cTplValGesInit< bool > & IsMult();
        const cTplValGesInit< bool > & IsMult()const ;
    private:
        std::string mKeyName;
        Pt3dr mIncertitude;
        cTplValGesInit< bool > mIsMult;
};
cElXMLTree * ToXMLTree(const cOneModifIPF &);

/******************************************************/
/******************************************************/
/******************************************************/
class cModifIncPtsFlottant
{
    public:
        friend void xml_init(cModifIncPtsFlottant & anObj,cElXMLTree * aTree);


        std::list< cOneModifIPF > & OneModifIPF();
        const std::list< cOneModifIPF > & OneModifIPF()const ;
    private:
        std::list< cOneModifIPF > mOneModifIPF;
};
cElXMLTree * ToXMLTree(const cModifIncPtsFlottant &);

/******************************************************/
/******************************************************/
/******************************************************/
class cOneMesureAF1I
{
    public:
        friend void xml_init(cOneMesureAF1I & anObj,cElXMLTree * aTree);


        std::string & NamePt();
        const std::string & NamePt()const ;

        Pt2dr & PtIm();
        const Pt2dr & PtIm()const ;
    private:
        std::string mNamePt;
        Pt2dr mPtIm;
};
cElXMLTree * ToXMLTree(const cOneMesureAF1I &);

class cMesureAppuiFlottant1Im
{
    public:
        friend void xml_init(cMesureAppuiFlottant1Im & anObj,cElXMLTree * aTree);


        std::string & NameIm();
        const std::string & NameIm()const ;

        std::list< cOneMesureAF1I > & OneMesureAF1I();
        const std::list< cOneMesureAF1I > & OneMesureAF1I()const ;
    private:
        std::string mNameIm;
        std::list< cOneMesureAF1I > mOneMesureAF1I;
};
cElXMLTree * ToXMLTree(const cMesureAppuiFlottant1Im &);

/******************************************************/
/******************************************************/
/******************************************************/
class cSetOfMesureAppuisFlottants
{
    public:
        friend void xml_init(cSetOfMesureAppuisFlottants & anObj,cElXMLTree * aTree);


        std::list< cMesureAppuiFlottant1Im > & MesureAppuiFlottant1Im();
        const std::list< cMesureAppuiFlottant1Im > & MesureAppuiFlottant1Im()const ;
    private:
        std::list< cMesureAppuiFlottant1Im > mMesureAppuiFlottant1Im;
};
cElXMLTree * ToXMLTree(const cSetOfMesureAppuisFlottants &);

/******************************************************/
/******************************************************/
/******************************************************/
class cMesureAppuis
{
    public:
        friend void xml_init(cMesureAppuis & anObj,cElXMLTree * aTree);


        cTplValGesInit< int > & Num();
        const cTplValGesInit< int > & Num()const ;

        Pt2dr & Im();
        const Pt2dr & Im()const ;

        Pt3dr & Ter();
        const Pt3dr & Ter()const ;
    private:
        cTplValGesInit< int > mNum;
        Pt2dr mIm;
        Pt3dr mTer;
};
cElXMLTree * ToXMLTree(const cMesureAppuis &);

/******************************************************/
/******************************************************/
/******************************************************/
class cListeAppuis1Im
{
    public:
        friend void xml_init(cListeAppuis1Im & anObj,cElXMLTree * aTree);


        cTplValGesInit< std::string > & NameImage();
        const cTplValGesInit< std::string > & NameImage()const ;

        std::list< cMesureAppuis > & Mesures();
        const std::list< cMesureAppuis > & Mesures()const ;
    private:
        cTplValGesInit< std::string > mNameImage;
        std::list< cMesureAppuis > mMesures;
};
cElXMLTree * ToXMLTree(const cListeAppuis1Im &);

/******************************************************/
/******************************************************/
/******************************************************/
class cVerifOrient
{
    public:
        friend void xml_init(cVerifOrient & anObj,cElXMLTree * aTree);


        double & Tol();
        const double & Tol()const ;

        cTplValGesInit< bool > & ShowMes();
        const cTplValGesInit< bool > & ShowMes()const ;

        std::list< cMesureAppuis > & Appuis();
        const std::list< cMesureAppuis > & Appuis()const ;

        cTplValGesInit< bool > & IsTest();
        const cTplValGesInit< bool > & IsTest()const ;

        cTplValGesInit< cListeAppuis1Im > & AppuisConv();
        const cTplValGesInit< cListeAppuis1Im > & AppuisConv()const ;
    private:
        double mTol;
        cTplValGesInit< bool > mShowMes;
        std::list< cMesureAppuis > mAppuis;
        cTplValGesInit< bool > mIsTest;
        cTplValGesInit< cListeAppuis1Im > mAppuisConv;
};
cElXMLTree * ToXMLTree(const cVerifOrient &);

/******************************************************/
/******************************************************/
/******************************************************/
typedef enum
{
  eConvInconnue,
  eConvApero_DistC2M,
  eConvApero_DistM2C,
  eConvOriLib,
  eConvMatrPoivillier_E,
  eConvAngErdas,
  eConvAngErdas_Grade,
  eConvAngAvionJaune,
  eConvAngSurvey,
  eConvAngPhotoMDegre,
  eConvAngPhotoMGrade,
  eConvAngLPSDegre
} eConventionsOrientation;
void xml_init(eConventionsOrientation & aVal,cElXMLTree * aTree);
std::string  eToString(const eConventionsOrientation & aVal);

eConventionsOrientation  Str2eConventionsOrientation(const std::string & aName);

cElXMLTree * ToXMLTree(const std::string & aNameTag,const eConventionsOrientation & anObj);

class cCalibrationInterneRadiale
{
    public:
        friend void xml_init(cCalibrationInterneRadiale & anObj,cElXMLTree * aTree);


        Pt2dr & CDist();
        const Pt2dr & CDist()const ;

        std::vector< double > & CoeffDist();
        const std::vector< double > & CoeffDist()const ;

        cTplValGesInit< double > & RatioDistInv();
        const cTplValGesInit< double > & RatioDistInv()const ;

        cTplValGesInit< bool > & PPaEqPPs();
        const cTplValGesInit< bool > & PPaEqPPs()const ;
    private:
        Pt2dr mCDist;
        std::vector< double > mCoeffDist;
        cTplValGesInit< double > mRatioDistInv;
        cTplValGesInit< bool > mPPaEqPPs;
};
cElXMLTree * ToXMLTree(const cCalibrationInterneRadiale &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCalibrationInternePghrStd
{
    public:
        friend void xml_init(cCalibrationInternePghrStd & anObj,cElXMLTree * aTree);


        cCalibrationInterneRadiale & RadialePart();
        const cCalibrationInterneRadiale & RadialePart()const ;

        cTplValGesInit< double > & P1();
        const cTplValGesInit< double > & P1()const ;

        cTplValGesInit< double > & P2();
        const cTplValGesInit< double > & P2()const ;

        cTplValGesInit< double > & b1();
        const cTplValGesInit< double > & b1()const ;

        cTplValGesInit< double > & b2();
        const cTplValGesInit< double > & b2()const ;
    private:
        cCalibrationInterneRadiale mRadialePart;
        cTplValGesInit< double > mP1;
        cTplValGesInit< double > mP2;
        cTplValGesInit< double > mb1;
        cTplValGesInit< double > mb2;
};
cElXMLTree * ToXMLTree(const cCalibrationInternePghrStd &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCalibrationInterneUnif
{
    public:
        friend void xml_init(cCalibrationInterneUnif & anObj,cElXMLTree * aTree);


        eModelesCalibUnif & TypeModele();
        const eModelesCalibUnif & TypeModele()const ;

        std::vector< double > & Params();
        const std::vector< double > & Params()const ;

        std::vector< double > & Etats();
        const std::vector< double > & Etats()const ;
    private:
        eModelesCalibUnif mTypeModele;
        std::vector< double > mParams;
        std::vector< double > mEtats;
};
cElXMLTree * ToXMLTree(const cCalibrationInterneUnif &);

/******************************************************/
/******************************************************/
/******************************************************/
class cTestNewGrid
{
    public:
        friend void xml_init(cTestNewGrid & anObj,cElXMLTree * aTree);


        std::string & A();
        const std::string & A()const ;

        Im2D_INT1 & Im();
        const Im2D_INT1 & Im()const ;

        std::string & Z();
        const std::string & Z()const ;
    private:
        std::string mA;
        Im2D_INT1 mIm;
        std::string mZ;
};
cElXMLTree * ToXMLTree(const cTestNewGrid &);

/******************************************************/
/******************************************************/
/******************************************************/
class cGridDeform2D
{
    public:
        friend void xml_init(cGridDeform2D & anObj,cElXMLTree * aTree);


        Pt2dr & Origine();
        const Pt2dr & Origine()const ;

        Pt2dr & Step();
        const Pt2dr & Step()const ;

        Im2D_REAL8 & ImX();
        const Im2D_REAL8 & ImX()const ;

        Im2D_REAL8 & ImY();
        const Im2D_REAL8 & ImY()const ;
    private:
        Pt2dr mOrigine;
        Pt2dr mStep;
        Im2D_REAL8 mImX;
        Im2D_REAL8 mImY;
};
cElXMLTree * ToXMLTree(const cGridDeform2D &);

/******************************************************/
/******************************************************/
/******************************************************/
class cGridDirecteEtInverse
{
    public:
        friend void xml_init(cGridDirecteEtInverse & anObj,cElXMLTree * aTree);


        cGridDeform2D & Directe();
        const cGridDeform2D & Directe()const ;

        cGridDeform2D & Inverse();
        const cGridDeform2D & Inverse()const ;

        bool & AdaptStep();
        const bool & AdaptStep()const ;
    private:
        cGridDeform2D mDirecte;
        cGridDeform2D mInverse;
        bool mAdaptStep;
};
cElXMLTree * ToXMLTree(const cGridDirecteEtInverse &);

/******************************************************/
/******************************************************/
/******************************************************/
class cPreCondRadial
{
    public:
        friend void xml_init(cPreCondRadial & anObj,cElXMLTree * aTree);


        Pt2dr & C();
        const Pt2dr & C()const ;

        double & F();
        const double & F()const ;

        eTypePreCondRad & Mode();
        const eTypePreCondRad & Mode()const ;
    private:
        Pt2dr mC;
        double mF;
        eTypePreCondRad mMode;
};
cElXMLTree * ToXMLTree(const cPreCondRadial &);

class cPreCondGrid
{
    public:
        friend void xml_init(cPreCondGrid & anObj,cElXMLTree * aTree);


        Pt2dr & C();
        const Pt2dr & C()const ;

        double & F();
        const double & F()const ;

        eTypePreCondRad & Mode();
        const eTypePreCondRad & Mode()const ;

        cTplValGesInit< cPreCondRadial > & PreCondRadial();
        const cTplValGesInit< cPreCondRadial > & PreCondRadial()const ;
    private:
        cTplValGesInit< cPreCondRadial > mPreCondRadial;
};
cElXMLTree * ToXMLTree(const cPreCondGrid &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCalibrationInterneGrid
{
    public:
        friend void xml_init(cCalibrationInterneGrid & anObj,cElXMLTree * aTree);


        Pt2dr & C();
        const Pt2dr & C()const ;

        double & F();
        const double & F()const ;

        eTypePreCondRad & Mode();
        const eTypePreCondRad & Mode()const ;

        cTplValGesInit< cPreCondRadial > & PreCondRadial();
        const cTplValGesInit< cPreCondRadial > & PreCondRadial()const ;

        cTplValGesInit< cPreCondGrid > & PreCondGrid();
        const cTplValGesInit< cPreCondGrid > & PreCondGrid()const ;

        cGridDirecteEtInverse & Grid();
        const cGridDirecteEtInverse & Grid()const ;
    private:
        cTplValGesInit< cPreCondGrid > mPreCondGrid;
        cGridDirecteEtInverse mGrid;
};
cElXMLTree * ToXMLTree(const cCalibrationInterneGrid &);

/******************************************************/
/******************************************************/
/******************************************************/
class cSimilitudePlane
{
    public:
        friend void xml_init(cSimilitudePlane & anObj,cElXMLTree * aTree);


        Pt2dr & Scale();
        const Pt2dr & Scale()const ;

        Pt2dr & Trans();
        const Pt2dr & Trans()const ;
    private:
        Pt2dr mScale;
        Pt2dr mTrans;
};
cElXMLTree * ToXMLTree(const cSimilitudePlane &);

/******************************************************/
/******************************************************/
/******************************************************/
class cAffinitePlane
{
    public:
        friend void xml_init(cAffinitePlane & anObj,cElXMLTree * aTree);


        Pt2dr & I00();
        const Pt2dr & I00()const ;

        Pt2dr & V10();
        const Pt2dr & V10()const ;

        Pt2dr & V01();
        const Pt2dr & V01()const ;
    private:
        Pt2dr mI00;
        Pt2dr mV10;
        Pt2dr mV01;
};
cElXMLTree * ToXMLTree(const cAffinitePlane &);

/******************************************************/
/******************************************************/
/******************************************************/
class cOrIntGlob
{
    public:
        friend void xml_init(cOrIntGlob & anObj,cElXMLTree * aTree);


        cAffinitePlane & Affinite();
        const cAffinitePlane & Affinite()const ;

        bool & C2M();
        const bool & C2M()const ;
    private:
        cAffinitePlane mAffinite;
        bool mC2M;
};
cElXMLTree * ToXMLTree(const cOrIntGlob &);

/******************************************************/
/******************************************************/
/******************************************************/
class cParamForGrid
{
    public:
        friend void xml_init(cParamForGrid & anObj,cElXMLTree * aTree);


        Pt2dr & StepGrid();
        const Pt2dr & StepGrid()const ;

        double & RayonInv();
        const double & RayonInv()const ;
    private:
        Pt2dr mStepGrid;
        double mRayonInv;
};
cElXMLTree * ToXMLTree(const cParamForGrid &);

/******************************************************/
/******************************************************/
/******************************************************/
class cModNoDist
{
    public:
        friend void xml_init(cModNoDist & anObj,cElXMLTree * aTree);


        cTplValGesInit< std::string > & Inutile();
        const cTplValGesInit< std::string > & Inutile()const ;
    private:
        cTplValGesInit< std::string > mInutile;
};
cElXMLTree * ToXMLTree(const cModNoDist &);

class cCalibDistortion
{
    public:
        friend void xml_init(cCalibDistortion & anObj,cElXMLTree * aTree);


        cTplValGesInit< std::string > & Inutile();
        const cTplValGesInit< std::string > & Inutile()const ;

        cTplValGesInit< cModNoDist > & ModNoDist();
        const cTplValGesInit< cModNoDist > & ModNoDist()const ;

        cTplValGesInit< cCalibrationInterneRadiale > & ModRad();
        const cTplValGesInit< cCalibrationInterneRadiale > & ModRad()const ;

        cTplValGesInit< cCalibrationInternePghrStd > & ModPhgrStd();
        const cTplValGesInit< cCalibrationInternePghrStd > & ModPhgrStd()const ;

        cTplValGesInit< cCalibrationInterneUnif > & ModUnif();
        const cTplValGesInit< cCalibrationInterneUnif > & ModUnif()const ;

        cTplValGesInit< cCalibrationInterneGrid > & ModGrid();
        const cTplValGesInit< cCalibrationInterneGrid > & ModGrid()const ;
    private:
        cTplValGesInit< cModNoDist > mModNoDist;
        cTplValGesInit< cCalibrationInterneRadiale > mModRad;
        cTplValGesInit< cCalibrationInternePghrStd > mModPhgrStd;
        cTplValGesInit< cCalibrationInterneUnif > mModUnif;
        cTplValGesInit< cCalibrationInterneGrid > mModGrid;
};
cElXMLTree * ToXMLTree(const cCalibDistortion &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCorrectionRefractionAPosteriori
{
    public:
        friend void xml_init(cCorrectionRefractionAPosteriori & anObj,cElXMLTree * aTree);


        std::string & FileEstimCam();
        const std::string & FileEstimCam()const ;

        cTplValGesInit< std::string > & NameTag();
        const cTplValGesInit< std::string > & NameTag()const ;

        double & CoeffRefrac();
        const double & CoeffRefrac()const ;

        cTplValGesInit< bool > & IntegreDist();
        const cTplValGesInit< bool > & IntegreDist()const ;
    private:
        std::string mFileEstimCam;
        cTplValGesInit< std::string > mNameTag;
        double mCoeffRefrac;
        cTplValGesInit< bool > mIntegreDist;
};
cElXMLTree * ToXMLTree(const cCorrectionRefractionAPosteriori &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCalibrationInternConique
{
    public:
        friend void xml_init(cCalibrationInternConique & anObj,cElXMLTree * aTree);


        cTplValGesInit< eConventionsOrientation > & KnownConv();
        const cTplValGesInit< eConventionsOrientation > & KnownConv()const ;

        std::vector< double > & ParamAF();
        const std::vector< double > & ParamAF()const ;

        Pt2dr & PP();
        const Pt2dr & PP()const ;

        double & F();
        const double & F()const ;

        Pt2di & SzIm();
        const Pt2di & SzIm()const ;

        cTplValGesInit< double > & RayonUtile();
        const cTplValGesInit< double > & RayonUtile()const ;

        std::vector< bool > & ComplIsC2M();
        const std::vector< bool > & ComplIsC2M()const ;

        cTplValGesInit< bool > & ScannedAnalogik();
        const cTplValGesInit< bool > & ScannedAnalogik()const ;

        cAffinitePlane & Affinite();
        const cAffinitePlane & Affinite()const ;

        bool & C2M();
        const bool & C2M()const ;

        cTplValGesInit< cOrIntGlob > & OrIntGlob();
        const cTplValGesInit< cOrIntGlob > & OrIntGlob()const ;

        Pt2dr & StepGrid();
        const Pt2dr & StepGrid()const ;

        double & RayonInv();
        const double & RayonInv()const ;

        cTplValGesInit< cParamForGrid > & ParamForGrid();
        const cTplValGesInit< cParamForGrid > & ParamForGrid()const ;

        std::vector< cCalibDistortion > & CalibDistortion();
        const std::vector< cCalibDistortion > & CalibDistortion()const ;

        std::string & FileEstimCam();
        const std::string & FileEstimCam()const ;

        cTplValGesInit< std::string > & NameTag();
        const cTplValGesInit< std::string > & NameTag()const ;

        double & CoeffRefrac();
        const double & CoeffRefrac()const ;

        cTplValGesInit< bool > & IntegreDist();
        const cTplValGesInit< bool > & IntegreDist()const ;

        cTplValGesInit< cCorrectionRefractionAPosteriori > & CorrectionRefractionAPosteriori();
        const cTplValGesInit< cCorrectionRefractionAPosteriori > & CorrectionRefractionAPosteriori()const ;
    private:
        cTplValGesInit< eConventionsOrientation > mKnownConv;
        std::vector< double > mParamAF;
        Pt2dr mPP;
        double mF;
        Pt2di mSzIm;
        cTplValGesInit< double > mRayonUtile;
        std::vector< bool > mComplIsC2M;
        cTplValGesInit< bool > mScannedAnalogik;
        cTplValGesInit< cOrIntGlob > mOrIntGlob;
        cTplValGesInit< cParamForGrid > mParamForGrid;
        std::vector< cCalibDistortion > mCalibDistortion;
        cTplValGesInit< cCorrectionRefractionAPosteriori > mCorrectionRefractionAPosteriori;
};
cElXMLTree * ToXMLTree(const cCalibrationInternConique &);

/******************************************************/
/******************************************************/
/******************************************************/
class cRepereCartesien
{
    public:
        friend void xml_init(cRepereCartesien & anObj,cElXMLTree * aTree);


        Pt3dr & Ori();
        const Pt3dr & Ori()const ;

        Pt3dr & Ox();
        const Pt3dr & Ox()const ;

        Pt3dr & Oy();
        const Pt3dr & Oy()const ;

        Pt3dr & Oz();
        const Pt3dr & Oz()const ;
    private:
        Pt3dr mOri;
        Pt3dr mOx;
        Pt3dr mOy;
        Pt3dr mOz;
};
cElXMLTree * ToXMLTree(const cRepereCartesien &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCodageMatr
{
    public:
        friend void xml_init(cCodageMatr & anObj,cElXMLTree * aTree);


        Pt3dr & L1();
        const Pt3dr & L1()const ;

        Pt3dr & L2();
        const Pt3dr & L2()const ;

        Pt3dr & L3();
        const Pt3dr & L3()const ;

        cTplValGesInit< bool > & TrueRot();
        const cTplValGesInit< bool > & TrueRot()const ;
    private:
        Pt3dr mL1;
        Pt3dr mL2;
        Pt3dr mL3;
        cTplValGesInit< bool > mTrueRot;
};
cElXMLTree * ToXMLTree(const cCodageMatr &);

/******************************************************/
/******************************************************/
/******************************************************/
class cRotationVect
{
    public:
        friend void xml_init(cRotationVect & anObj,cElXMLTree * aTree);


        Pt3dr & L1();
        const Pt3dr & L1()const ;

        Pt3dr & L2();
        const Pt3dr & L2()const ;

        Pt3dr & L3();
        const Pt3dr & L3()const ;

        cTplValGesInit< bool > & TrueRot();
        const cTplValGesInit< bool > & TrueRot()const ;

        cTplValGesInit< cCodageMatr > & CodageMatr();
        const cTplValGesInit< cCodageMatr > & CodageMatr()const ;

        cTplValGesInit< Pt3dr > & CodageAngulaire();
        const cTplValGesInit< Pt3dr > & CodageAngulaire()const ;

        cTplValGesInit< std::string > & CodageSymbolique();
        const cTplValGesInit< std::string > & CodageSymbolique()const ;
    private:
        cTplValGesInit< cCodageMatr > mCodageMatr;
        cTplValGesInit< Pt3dr > mCodageAngulaire;
        cTplValGesInit< std::string > mCodageSymbolique;
};
cElXMLTree * ToXMLTree(const cRotationVect &);

/******************************************************/
/******************************************************/
/******************************************************/
class cOrientationExterneRigide
{
    public:
        friend void xml_init(cOrientationExterneRigide & anObj,cElXMLTree * aTree);


        cTplValGesInit< double > & AltiSol();
        const cTplValGesInit< double > & AltiSol()const ;

        cTplValGesInit< double > & Profondeur();
        const cTplValGesInit< double > & Profondeur()const ;

        cTplValGesInit< double > & Time();
        const cTplValGesInit< double > & Time()const ;

        cTplValGesInit< eConventionsOrientation > & KnownConv();
        const cTplValGesInit< eConventionsOrientation > & KnownConv()const ;

        Pt3dr & Centre();
        const Pt3dr & Centre()const ;

        cTplValGesInit< Pt3dr > & Vitesse();
        const cTplValGesInit< Pt3dr > & Vitesse()const ;

        cTplValGesInit< bool > & VitesseFiable();
        const cTplValGesInit< bool > & VitesseFiable()const ;

        cTplValGesInit< Pt3dr > & IncCentre();
        const cTplValGesInit< Pt3dr > & IncCentre()const ;

        cRotationVect & ParamRotation();
        const cRotationVect & ParamRotation()const ;
    private:
        cTplValGesInit< double > mAltiSol;
        cTplValGesInit< double > mProfondeur;
        cTplValGesInit< double > mTime;
        cTplValGesInit< eConventionsOrientation > mKnownConv;
        Pt3dr mCentre;
        cTplValGesInit< Pt3dr > mVitesse;
        cTplValGesInit< bool > mVitesseFiable;
        cTplValGesInit< Pt3dr > mIncCentre;
        cRotationVect mParamRotation;
};
cElXMLTree * ToXMLTree(const cOrientationExterneRigide &);

/******************************************************/
/******************************************************/
/******************************************************/
class cConvExplicite
{
    public:
        friend void xml_init(cConvExplicite & anObj,cElXMLTree * aTree);


        bool & SensYVideo();
        const bool & SensYVideo()const ;

        bool & DistSenC2M();
        const bool & DistSenC2M()const ;

        bool & MatrSenC2M();
        const bool & MatrSenC2M()const ;

        Pt3dr & ColMul();
        const Pt3dr & ColMul()const ;

        Pt3dr & LigMul();
        const Pt3dr & LigMul()const ;

        eUniteAngulaire & UniteAngles();
        const eUniteAngulaire & UniteAngles()const ;

        Pt3di & NumAxe();
        const Pt3di & NumAxe()const ;

        bool & SensCardan();
        const bool & SensCardan()const ;

        cTplValGesInit< eConventionsOrientation > & Convention();
        const cTplValGesInit< eConventionsOrientation > & Convention()const ;
    private:
        bool mSensYVideo;
        bool mDistSenC2M;
        bool mMatrSenC2M;
        Pt3dr mColMul;
        Pt3dr mLigMul;
        eUniteAngulaire mUniteAngles;
        Pt3di mNumAxe;
        bool mSensCardan;
        cTplValGesInit< eConventionsOrientation > mConvention;
};
cElXMLTree * ToXMLTree(const cConvExplicite &);

class cConvOri
{
    public:
        friend void xml_init(cConvOri & anObj,cElXMLTree * aTree);


        cTplValGesInit< eConventionsOrientation > & KnownConv();
        const cTplValGesInit< eConventionsOrientation > & KnownConv()const ;

        bool & SensYVideo();
        const bool & SensYVideo()const ;

        bool & DistSenC2M();
        const bool & DistSenC2M()const ;

        bool & MatrSenC2M();
        const bool & MatrSenC2M()const ;

        Pt3dr & ColMul();
        const Pt3dr & ColMul()const ;

        Pt3dr & LigMul();
        const Pt3dr & LigMul()const ;

        eUniteAngulaire & UniteAngles();
        const eUniteAngulaire & UniteAngles()const ;

        Pt3di & NumAxe();
        const Pt3di & NumAxe()const ;

        bool & SensCardan();
        const bool & SensCardan()const ;

        cTplValGesInit< eConventionsOrientation > & Convention();
        const cTplValGesInit< eConventionsOrientation > & Convention()const ;

        cTplValGesInit< cConvExplicite > & ConvExplicite();
        const cTplValGesInit< cConvExplicite > & ConvExplicite()const ;
    private:
        cTplValGesInit< eConventionsOrientation > mKnownConv;
        cTplValGesInit< cConvExplicite > mConvExplicite;
};
cElXMLTree * ToXMLTree(const cConvOri &);

/******************************************************/
/******************************************************/
/******************************************************/
class cOrientationConique
{
    public:
        friend void xml_init(cOrientationConique & anObj,cElXMLTree * aTree);


        cTplValGesInit< cAffinitePlane > & OrIntImaM2C();
        const cTplValGesInit< cAffinitePlane > & OrIntImaM2C()const ;

        cTplValGesInit< eTypeProjectionCam > & TypeProj();
        const cTplValGesInit< eTypeProjectionCam > & TypeProj()const ;

        cTplValGesInit< cCalibrationInternConique > & Interne();
        const cTplValGesInit< cCalibrationInternConique > & Interne()const ;

        cTplValGesInit< std::string > & FileInterne();
        const cTplValGesInit< std::string > & FileInterne()const ;

        cTplValGesInit< bool > & RelativeNameFI();
        const cTplValGesInit< bool > & RelativeNameFI()const ;

        cOrientationExterneRigide & Externe();
        const cOrientationExterneRigide & Externe()const ;

        cTplValGesInit< cVerifOrient > & Verif();
        const cTplValGesInit< cVerifOrient > & Verif()const ;

        cTplValGesInit< eConventionsOrientation > & KnownConv();
        const cTplValGesInit< eConventionsOrientation > & KnownConv()const ;

        bool & SensYVideo();
        const bool & SensYVideo()const ;

        bool & DistSenC2M();
        const bool & DistSenC2M()const ;

        bool & MatrSenC2M();
        const bool & MatrSenC2M()const ;

        Pt3dr & ColMul();
        const Pt3dr & ColMul()const ;

        Pt3dr & LigMul();
        const Pt3dr & LigMul()const ;

        eUniteAngulaire & UniteAngles();
        const eUniteAngulaire & UniteAngles()const ;

        Pt3di & NumAxe();
        const Pt3di & NumAxe()const ;

        bool & SensCardan();
        const bool & SensCardan()const ;

        cTplValGesInit< eConventionsOrientation > & Convention();
        const cTplValGesInit< eConventionsOrientation > & Convention()const ;

        cTplValGesInit< cConvExplicite > & ConvExplicite();
        const cTplValGesInit< cConvExplicite > & ConvExplicite()const ;

        cConvOri & ConvOri();
        const cConvOri & ConvOri()const ;
    private:
        cTplValGesInit< cAffinitePlane > mOrIntImaM2C;
        cTplValGesInit< eTypeProjectionCam > mTypeProj;
        cTplValGesInit< cCalibrationInternConique > mInterne;
        cTplValGesInit< std::string > mFileInterne;
        cTplValGesInit< bool > mRelativeNameFI;
        cOrientationExterneRigide mExterne;
        cTplValGesInit< cVerifOrient > mVerif;
        cConvOri mConvOri;
};
cElXMLTree * ToXMLTree(const cOrientationConique &);

/******************************************************/
/******************************************************/
/******************************************************/
class cMNT2Cmp
{
    public:
        friend void xml_init(cMNT2Cmp & anObj,cElXMLTree * aTree);


        std::string & NameIm();
        const std::string & NameIm()const ;

        cTplValGesInit< std::string > & NameXml();
        const cTplValGesInit< std::string > & NameXml()const ;

        cTplValGesInit< int > & IdIsRef();
        const cTplValGesInit< int > & IdIsRef()const ;

        cTplValGesInit< std::string > & ShorName();
        const cTplValGesInit< std::string > & ShorName()const ;
    private:
        std::string mNameIm;
        cTplValGesInit< std::string > mNameXml;
        cTplValGesInit< int > mIdIsRef;
        cTplValGesInit< std::string > mShorName;
};
cElXMLTree * ToXMLTree(const cMNT2Cmp &);

/******************************************************/
/******************************************************/
/******************************************************/
class cContourPolyCM
{
    public:
        friend void xml_init(cContourPolyCM & anObj,cElXMLTree * aTree);


        std::list< Pt2di > & Pts();
        const std::list< Pt2di > & Pts()const ;
    private:
        std::list< Pt2di > mPts;
};
cElXMLTree * ToXMLTree(const cContourPolyCM &);

class cEnvellopeZoneCM
{
    public:
        friend void xml_init(cEnvellopeZoneCM & anObj,cElXMLTree * aTree);


        std::list< Pt2di > & Pts();
        const std::list< Pt2di > & Pts()const ;

        cTplValGesInit< cContourPolyCM > & ContourPolyCM();
        const cTplValGesInit< cContourPolyCM > & ContourPolyCM()const ;

        cTplValGesInit< Box2dr > & BoxContourCM();
        const cTplValGesInit< Box2dr > & BoxContourCM()const ;
    private:
        cTplValGesInit< cContourPolyCM > mContourPolyCM;
        cTplValGesInit< Box2dr > mBoxContourCM;
};
cElXMLTree * ToXMLTree(const cEnvellopeZoneCM &);

class cZoneCmpMnt
{
    public:
        friend void xml_init(cZoneCmpMnt & anObj,cElXMLTree * aTree);


        cTplValGesInit< std::string > & NomZone();
        const cTplValGesInit< std::string > & NomZone()const ;

        std::list< Pt2di > & Pts();
        const std::list< Pt2di > & Pts()const ;

        cTplValGesInit< cContourPolyCM > & ContourPolyCM();
        const cTplValGesInit< cContourPolyCM > & ContourPolyCM()const ;

        cTplValGesInit< Box2dr > & BoxContourCM();
        const cTplValGesInit< Box2dr > & BoxContourCM()const ;

        cEnvellopeZoneCM & EnvellopeZoneCM();
        const cEnvellopeZoneCM & EnvellopeZoneCM()const ;
    private:
        cTplValGesInit< std::string > mNomZone;
        cEnvellopeZoneCM mEnvellopeZoneCM;
};
cElXMLTree * ToXMLTree(const cZoneCmpMnt &);

/******************************************************/
/******************************************************/
/******************************************************/
class cEcartZ
{
    public:
        friend void xml_init(cEcartZ & anObj,cElXMLTree * aTree);


        double & DynVisu();
        const double & DynVisu()const ;
    private:
        double mDynVisu;
};
cElXMLTree * ToXMLTree(const cEcartZ &);

class cCorrelPente
{
    public:
        friend void xml_init(cCorrelPente & anObj,cElXMLTree * aTree);


        double & SzWCP();
        const double & SzWCP()const ;

        double & GrMinCP();
        const double & GrMinCP()const ;
    private:
        double mSzWCP;
        double mGrMinCP;
};
cElXMLTree * ToXMLTree(const cCorrelPente &);

class cMesureCmptMnt
{
    public:
        friend void xml_init(cMesureCmptMnt & anObj,cElXMLTree * aTree);


        double & DynVisu();
        const double & DynVisu()const ;

        cTplValGesInit< cEcartZ > & EcartZ();
        const cTplValGesInit< cEcartZ > & EcartZ()const ;

        double & SzWCP();
        const double & SzWCP()const ;

        double & GrMinCP();
        const double & GrMinCP()const ;

        cTplValGesInit< cCorrelPente > & CorrelPente();
        const cTplValGesInit< cCorrelPente > & CorrelPente()const ;

        cTplValGesInit< bool > & EcartPente();
        const cTplValGesInit< bool > & EcartPente()const ;
    private:
        cTplValGesInit< cEcartZ > mEcartZ;
        cTplValGesInit< cCorrelPente > mCorrelPente;
        cTplValGesInit< bool > mEcartPente;
};
cElXMLTree * ToXMLTree(const cMesureCmptMnt &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCompareMNT
{
    public:
        friend void xml_init(cCompareMNT & anObj,cElXMLTree * aTree);


        Pt2dr & ResolutionPlaniTerrain();
        const Pt2dr & ResolutionPlaniTerrain()const ;

        cTplValGesInit< int > & RabLoad();
        const cTplValGesInit< int > & RabLoad()const ;

        std::string & NameFileRes();
        const std::string & NameFileRes()const ;

        cTplValGesInit< bool > & VisuInter();
        const cTplValGesInit< bool > & VisuInter()const ;

        std::list< cMNT2Cmp > & MNT2Cmp();
        const std::list< cMNT2Cmp > & MNT2Cmp()const ;

        cTplValGesInit< std::string > & MasqGlobalCM();
        const cTplValGesInit< std::string > & MasqGlobalCM()const ;

        std::list< cZoneCmpMnt > & ZoneCmpMnt();
        const std::list< cZoneCmpMnt > & ZoneCmpMnt()const ;

        double & DynVisu();
        const double & DynVisu()const ;

        cTplValGesInit< cEcartZ > & EcartZ();
        const cTplValGesInit< cEcartZ > & EcartZ()const ;

        double & SzWCP();
        const double & SzWCP()const ;

        double & GrMinCP();
        const double & GrMinCP()const ;

        cTplValGesInit< cCorrelPente > & CorrelPente();
        const cTplValGesInit< cCorrelPente > & CorrelPente()const ;

        cTplValGesInit< bool > & EcartPente();
        const cTplValGesInit< bool > & EcartPente()const ;

        cMesureCmptMnt & MesureCmptMnt();
        const cMesureCmptMnt & MesureCmptMnt()const ;
    private:
        Pt2dr mResolutionPlaniTerrain;
        cTplValGesInit< int > mRabLoad;
        std::string mNameFileRes;
        cTplValGesInit< bool > mVisuInter;
        std::list< cMNT2Cmp > mMNT2Cmp;
        cTplValGesInit< std::string > mMasqGlobalCM;
        std::list< cZoneCmpMnt > mZoneCmpMnt;
        cMesureCmptMnt mMesureCmptMnt;
};
cElXMLTree * ToXMLTree(const cCompareMNT &);

/******************************************************/
/******************************************************/
/******************************************************/
class cDataBaseNameTransfo
{
    public:
        friend void xml_init(cDataBaseNameTransfo & anObj,cElXMLTree * aTree);


        cTplValGesInit< double > & AddFocMul();
        const cTplValGesInit< double > & AddFocMul()const ;

        cTplValGesInit< std::string > & Separateur();
        const cTplValGesInit< std::string > & Separateur()const ;
    private:
        cTplValGesInit< double > mAddFocMul;
        cTplValGesInit< std::string > mSeparateur;
};
cElXMLTree * ToXMLTree(const cDataBaseNameTransfo &);

/******************************************************/
/******************************************************/
/******************************************************/
class cInterpoleGrille
{
    public:
        friend void xml_init(cInterpoleGrille & anObj,cElXMLTree * aTree);


        cTplValGesInit< std::string > & Directory();
        const cTplValGesInit< std::string > & Directory()const ;

        std::string & Grille1();
        const std::string & Grille1()const ;

        std::string & Grille2();
        const std::string & Grille2()const ;

        std::string & Grille0();
        const std::string & Grille0()const ;

        cTplValGesInit< Pt2dr > & StepGrid();
        const cTplValGesInit< Pt2dr > & StepGrid()const ;

        double & Focale1();
        const double & Focale1()const ;

        double & Focale2();
        const double & Focale2()const ;

        double & Focale0();
        const double & Focale0()const ;

        cTplValGesInit< int > & NbPtsByIter();
        const cTplValGesInit< int > & NbPtsByIter()const ;

        cTplValGesInit< int > & DegPoly();
        const cTplValGesInit< int > & DegPoly()const ;

        cTplValGesInit< eDegreLiberteCPP > & LiberteCPP();
        const cTplValGesInit< eDegreLiberteCPP > & LiberteCPP()const ;
    private:
        cTplValGesInit< std::string > mDirectory;
        std::string mGrille1;
        std::string mGrille2;
        std::string mGrille0;
        cTplValGesInit< Pt2dr > mStepGrid;
        double mFocale1;
        double mFocale2;
        double mFocale0;
        cTplValGesInit< int > mNbPtsByIter;
        cTplValGesInit< int > mDegPoly;
        cTplValGesInit< eDegreLiberteCPP > mLiberteCPP;
};
cElXMLTree * ToXMLTree(const cInterpoleGrille &);

/******************************************************/
/******************************************************/
/******************************************************/
class cOneCalib2Visu
{
    public:
        friend void xml_init(cOneCalib2Visu & anObj,cElXMLTree * aTree);


        std::string & Name();
        const std::string & Name()const ;

        Pt3dr & Coul();
        const Pt3dr & Coul()const ;
    private:
        std::string mName;
        Pt3dr mCoul;
};
cElXMLTree * ToXMLTree(const cOneCalib2Visu &);

/******************************************************/
/******************************************************/
/******************************************************/
class cVisuCalibZoom
{
    public:
        friend void xml_init(cVisuCalibZoom & anObj,cElXMLTree * aTree);


        cTplValGesInit< std::string > & Directory();
        const cTplValGesInit< std::string > & Directory()const ;

        Pt2dr & SzIm();
        const Pt2dr & SzIm()const ;

        std::list< cOneCalib2Visu > & OneCalib2Visu();
        const std::list< cOneCalib2Visu > & OneCalib2Visu()const ;
    private:
        cTplValGesInit< std::string > mDirectory;
        Pt2dr mSzIm;
        std::list< cOneCalib2Visu > mOneCalib2Visu;
};
cElXMLTree * ToXMLTree(const cVisuCalibZoom &);

/******************************************************/
/******************************************************/
/******************************************************/
class cFilterLocalisation
{
    public:
        friend void xml_init(cFilterLocalisation & anObj,cElXMLTree * aTree);


        std::string & KeyAssocOrient();
        const std::string & KeyAssocOrient()const ;

        std::string & NameMasq();
        const std::string & NameMasq()const ;

        std::string & NameMTDMasq();
        const std::string & NameMTDMasq()const ;
    private:
        std::string mKeyAssocOrient;
        std::string mNameMasq;
        std::string mNameMTDMasq;
};
cElXMLTree * ToXMLTree(const cFilterLocalisation &);

/******************************************************/
/******************************************************/
/******************************************************/
class cKeyExistingFile
{
    public:
        friend void xml_init(cKeyExistingFile & anObj,cElXMLTree * aTree);


        std::list< std::string > & KeyAssoc();
        const std::list< std::string > & KeyAssoc()const ;

        bool & RequireExist();
        const bool & RequireExist()const ;

        bool & RequireForAll();
        const bool & RequireForAll()const ;
    private:
        std::list< std::string > mKeyAssoc;
        bool mRequireExist;
        bool mRequireForAll;
};
cElXMLTree * ToXMLTree(const cKeyExistingFile &);

/******************************************************/
/******************************************************/
/******************************************************/
class cNameFilter
{
    public:
        friend void xml_init(cNameFilter & anObj,cElXMLTree * aTree);


        std::list< Pt2drSubst > & FocMm();
        const std::list< Pt2drSubst > & FocMm()const ;

        cTplValGesInit< std::string > & Min();
        const cTplValGesInit< std::string > & Min()const ;

        cTplValGesInit< std::string > & Max();
        const cTplValGesInit< std::string > & Max()const ;

        cTplValGesInit< int > & SizeMinFile();
        const cTplValGesInit< int > & SizeMinFile()const ;

        std::list< cKeyExistingFile > & KeyExistingFile();
        const std::list< cKeyExistingFile > & KeyExistingFile()const ;

        cTplValGesInit< cFilterLocalisation > & KeyLocalisation();
        const cTplValGesInit< cFilterLocalisation > & KeyLocalisation()const ;
    private:
        std::list< Pt2drSubst > mFocMm;
        cTplValGesInit< std::string > mMin;
        cTplValGesInit< std::string > mMax;
        cTplValGesInit< int > mSizeMinFile;
        std::list< cKeyExistingFile > mKeyExistingFile;
        cTplValGesInit< cFilterLocalisation > mKeyLocalisation;
};
cElXMLTree * ToXMLTree(const cNameFilter &);

/******************************************************/
/******************************************************/
/******************************************************/
class cBasicAssocNameToName
{
    public:
        friend void xml_init(cBasicAssocNameToName & anObj,cElXMLTree * aTree);


        std::string & PatternTransform();
        const std::string & PatternTransform()const ;

        cTplValGesInit< cDataBaseNameTransfo > & NameTransfo();
        const cTplValGesInit< cDataBaseNameTransfo > & NameTransfo()const ;

        cTplValGesInit< std::string > & PatternSelector();
        const cTplValGesInit< std::string > & PatternSelector()const ;

        std::vector< std::string > & CalcName();
        const std::vector< std::string > & CalcName()const ;

        cTplValGesInit< std::string > & Separateur();
        const cTplValGesInit< std::string > & Separateur()const ;

        cTplValGesInit< cNameFilter > & Filter();
        const cTplValGesInit< cNameFilter > & Filter()const ;
    private:
        std::string mPatternTransform;
        cTplValGesInit< cDataBaseNameTransfo > mNameTransfo;
        cTplValGesInit< std::string > mPatternSelector;
        std::vector< std::string > mCalcName;
        cTplValGesInit< std::string > mSeparateur;
        cTplValGesInit< cNameFilter > mFilter;
};
cElXMLTree * ToXMLTree(const cBasicAssocNameToName &);

/******************************************************/
/******************************************************/
/******************************************************/
class cAssocNameToName
{
    public:
        friend void xml_init(cAssocNameToName & anObj,cElXMLTree * aTree);


        cTplValGesInit< Pt2di > & Arrite();
        const cTplValGesInit< Pt2di > & Arrite()const ;

        cBasicAssocNameToName & Direct();
        const cBasicAssocNameToName & Direct()const ;

        cTplValGesInit< cBasicAssocNameToName > & Inverse();
        const cTplValGesInit< cBasicAssocNameToName > & Inverse()const ;

        cTplValGesInit< bool > & AutoInverseBySym();
        const cTplValGesInit< bool > & AutoInverseBySym()const ;
    private:
        cTplValGesInit< Pt2di > mArrite;
        cBasicAssocNameToName mDirect;
        cTplValGesInit< cBasicAssocNameToName > mInverse;
        cTplValGesInit< bool > mAutoInverseBySym;
};
cElXMLTree * ToXMLTree(const cAssocNameToName &);

/******************************************************/
/******************************************************/
/******************************************************/
class cSetNameDescriptor
{
    public:
        friend void xml_init(cSetNameDescriptor & anObj,cElXMLTree * aTree);


        cTplValGesInit< bool > & AddDirCur();
        const cTplValGesInit< bool > & AddDirCur()const ;

        std::list< std::string > & PatternAccepteur();
        const std::list< std::string > & PatternAccepteur()const ;

        std::list< std::string > & PatternRefuteur();
        const std::list< std::string > & PatternRefuteur()const ;

        cTplValGesInit< int > & NivSubDir();
        const cTplValGesInit< int > & NivSubDir()const ;

        cTplValGesInit< bool > & NameCompl();
        const cTplValGesInit< bool > & NameCompl()const ;

        cTplValGesInit< std::string > & SubDir();
        const cTplValGesInit< std::string > & SubDir()const ;

        std::list< std::string > & Name();
        const std::list< std::string > & Name()const ;

        cTplValGesInit< std::string > & Min();
        const cTplValGesInit< std::string > & Min()const ;

        cTplValGesInit< std::string > & Max();
        const cTplValGesInit< std::string > & Max()const ;

        cTplValGesInit< cNameFilter > & Filter();
        const cTplValGesInit< cNameFilter > & Filter()const ;
    private:
        cTplValGesInit< bool > mAddDirCur;
        std::list< std::string > mPatternAccepteur;
        std::list< std::string > mPatternRefuteur;
        cTplValGesInit< int > mNivSubDir;
        cTplValGesInit< bool > mNameCompl;
        cTplValGesInit< std::string > mSubDir;
        std::list< std::string > mName;
        cTplValGesInit< std::string > mMin;
        cTplValGesInit< std::string > mMax;
        cTplValGesInit< cNameFilter > mFilter;
};
cElXMLTree * ToXMLTree(const cSetNameDescriptor &);

/******************************************************/
/******************************************************/
/******************************************************/
class cImMatrixStructuration
{
    public:
        friend void xml_init(cImMatrixStructuration & anObj,cElXMLTree * aTree);


        std::string & KeySet();
        const std::string & KeySet()const ;

        Pt2di & Period();
        const Pt2di & Period()const ;

        bool & XCroissants();
        const bool & XCroissants()const ;

        bool & YCroissants();
        const bool & YCroissants()const ;

        bool & XVarieFirst();
        const bool & XVarieFirst()const ;
    private:
        std::string mKeySet;
        Pt2di mPeriod;
        bool mXCroissants;
        bool mYCroissants;
        bool mXVarieFirst;
};
cElXMLTree * ToXMLTree(const cImMatrixStructuration &);

/******************************************************/
/******************************************************/
/******************************************************/
class cFiltreEmprise
{
    public:
        friend void xml_init(cFiltreEmprise & anObj,cElXMLTree * aTree);


        std::string & KeyOri();
        const std::string & KeyOri()const ;

        double & RatioMin();
        const double & RatioMin()const ;

        cTplValGesInit< bool > & MemoFile();
        const cTplValGesInit< bool > & MemoFile()const ;

        cTplValGesInit< std::string > & Tag();
        const cTplValGesInit< std::string > & Tag()const ;
    private:
        std::string mKeyOri;
        double mRatioMin;
        cTplValGesInit< bool > mMemoFile;
        cTplValGesInit< std::string > mTag;
};
cElXMLTree * ToXMLTree(const cFiltreEmprise &);

/******************************************************/
/******************************************************/
/******************************************************/
class cFiltreByRelSsEch
{
    public:
        friend void xml_init(cFiltreByRelSsEch & anObj,cElXMLTree * aTree);


        std::string & KeySet();
        const std::string & KeySet()const ;

        std::string & KeyAssocCple();
        const std::string & KeyAssocCple()const ;

        IntSubst & SeuilBasNbPts();
        const IntSubst & SeuilBasNbPts()const ;

        IntSubst & SeuilHautNbPts();
        const IntSubst & SeuilHautNbPts()const ;

        IntSubst & NbMinCple();
        const IntSubst & NbMinCple()const ;
    private:
        std::string mKeySet;
        std::string mKeyAssocCple;
        IntSubst mSeuilBasNbPts;
        IntSubst mSeuilHautNbPts;
        IntSubst mNbMinCple;
};
cElXMLTree * ToXMLTree(const cFiltreByRelSsEch &);

/******************************************************/
/******************************************************/
/******************************************************/
class cFiltreDeRelationOrient
{
    public:
        friend void xml_init(cFiltreDeRelationOrient & anObj,cElXMLTree * aTree);


        cTplValGesInit< std::string > & KeyEquiv();
        const cTplValGesInit< std::string > & KeyEquiv()const ;

        std::string & KeyOri();
        const std::string & KeyOri()const ;

        double & RatioMin();
        const double & RatioMin()const ;

        cTplValGesInit< bool > & MemoFile();
        const cTplValGesInit< bool > & MemoFile()const ;

        cTplValGesInit< std::string > & Tag();
        const cTplValGesInit< std::string > & Tag()const ;

        cTplValGesInit< cFiltreEmprise > & FiltreEmprise();
        const cTplValGesInit< cFiltreEmprise > & FiltreEmprise()const ;

        cTplValGesInit< std::string > & FiltreAdjMatrix();
        const cTplValGesInit< std::string > & FiltreAdjMatrix()const ;

        cTplValGesInit< Pt2di > & EcartFiltreMatr();
        const cTplValGesInit< Pt2di > & EcartFiltreMatr()const ;

        std::string & KeySet();
        const std::string & KeySet()const ;

        std::string & KeyAssocCple();
        const std::string & KeyAssocCple()const ;

        IntSubst & SeuilBasNbPts();
        const IntSubst & SeuilBasNbPts()const ;

        IntSubst & SeuilHautNbPts();
        const IntSubst & SeuilHautNbPts()const ;

        IntSubst & NbMinCple();
        const IntSubst & NbMinCple()const ;

        cTplValGesInit< cFiltreByRelSsEch > & FiltreByRelSsEch();
        const cTplValGesInit< cFiltreByRelSsEch > & FiltreByRelSsEch()const ;
    private:
        cTplValGesInit< std::string > mKeyEquiv;
        cTplValGesInit< cFiltreEmprise > mFiltreEmprise;
        cTplValGesInit< std::string > mFiltreAdjMatrix;
        cTplValGesInit< Pt2di > mEcartFiltreMatr;
        cTplValGesInit< cFiltreByRelSsEch > mFiltreByRelSsEch;
};
cElXMLTree * ToXMLTree(const cFiltreDeRelationOrient &);

/******************************************************/
/******************************************************/
/******************************************************/
class cSauvegardeNamedRel
{
    public:
        friend void xml_init(cSauvegardeNamedRel & anObj,cElXMLTree * aTree);


        std::vector< cCpleString > & Cple();
        const std::vector< cCpleString > & Cple()const ;
    private:
        std::vector< cCpleString > mCple;
};
cElXMLTree * ToXMLTree(const cSauvegardeNamedRel &);

/******************************************************/
/******************************************************/
/******************************************************/
class cSauvegardeSetString
{
    public:
        friend void xml_init(cSauvegardeSetString & anObj,cElXMLTree * aTree);


        std::list< std::string > & Name();
        const std::list< std::string > & Name()const ;
    private:
        std::list< std::string > mName;
};
cElXMLTree * ToXMLTree(const cSauvegardeSetString &);

/******************************************************/
/******************************************************/
/******************************************************/
class cClassEquivDescripteur
{
    public:
        friend void xml_init(cClassEquivDescripteur & anObj,cElXMLTree * aTree);


        std::string & KeySet();
        const std::string & KeySet()const ;

        std::string & KeyAssocRep();
        const std::string & KeyAssocRep()const ;

        std::string & KeyClass();
        const std::string & KeyClass()const ;
    private:
        std::string mKeySet;
        std::string mKeyAssocRep;
        std::string mKeyClass;
};
cElXMLTree * ToXMLTree(const cClassEquivDescripteur &);

/******************************************************/
/******************************************************/
/******************************************************/
class cOneSpecDelta
{
    public:
        friend void xml_init(cOneSpecDelta & anObj,cElXMLTree * aTree);


        std::vector<std::string> & Soms();
        const std::vector<std::string> & Soms()const ;

        std::vector<int>  & Delta();
        const std::vector<int>  & Delta()const ;
    private:
        std::vector<std::string> mSoms;
        std::vector<int>  mDelta;
};
cElXMLTree * ToXMLTree(const cOneSpecDelta &);

class cGrByDelta
{
    public:
        friend void xml_init(cGrByDelta & anObj,cElXMLTree * aTree);


        std::string & KeySet();
        const std::string & KeySet()const ;

        std::list< cOneSpecDelta > & OneSpecDelta();
        const std::list< cOneSpecDelta > & OneSpecDelta()const ;
    private:
        std::string mKeySet;
        std::list< cOneSpecDelta > mOneSpecDelta;
};
cElXMLTree * ToXMLTree(const cGrByDelta &);

class cRelByGrapheExpl
{
    public:
        friend void xml_init(cRelByGrapheExpl & anObj,cElXMLTree * aTree);


        std::list< cCpleString > & Cples();
        const std::list< cCpleString > & Cples()const ;

        std::list< std::vector<std::string> > & CpleSymWithFirt();
        const std::list< std::vector<std::string> > & CpleSymWithFirt()const ;

        std::list< std::vector<std::string> > & ProdCartesien();
        const std::list< std::vector<std::string> > & ProdCartesien()const ;

        cTplValGesInit< std::string > & Prefix2Name();
        const cTplValGesInit< std::string > & Prefix2Name()const ;

        cTplValGesInit< std::string > & Postfix2Name();
        const cTplValGesInit< std::string > & Postfix2Name()const ;

        std::list< cGrByDelta > & GrByDelta();
        const std::list< cGrByDelta > & GrByDelta()const ;
    private:
        std::list< cCpleString > mCples;
        std::list< std::vector<std::string> > mCpleSymWithFirt;
        std::list< std::vector<std::string> > mProdCartesien;
        cTplValGesInit< std::string > mPrefix2Name;
        cTplValGesInit< std::string > mPostfix2Name;
        std::list< cGrByDelta > mGrByDelta;
};
cElXMLTree * ToXMLTree(const cRelByGrapheExpl &);

/******************************************************/
/******************************************************/
/******************************************************/
class cByAdjDeGroupes
{
    public:
        friend void xml_init(cByAdjDeGroupes & anObj,cElXMLTree * aTree);


        std::vector< std::string > & KeySets();
        const std::vector< std::string > & KeySets()const ;

        int & DeltaMin();
        const int & DeltaMin()const ;

        int & DeltaMax();
        const int & DeltaMax()const ;
    private:
        std::vector< std::string > mKeySets;
        int mDeltaMin;
        int mDeltaMax;
};
cElXMLTree * ToXMLTree(const cByAdjDeGroupes &);

class cByGroupesDImages
{
    public:
        friend void xml_init(cByGroupesDImages & anObj,cElXMLTree * aTree);


        std::list< cCpleString > & CplesKey();
        const std::list< cCpleString > & CplesKey()const ;

        std::list< cByAdjDeGroupes > & ByAdjDeGroupes();
        const std::list< cByAdjDeGroupes > & ByAdjDeGroupes()const ;

        cTplValGesInit< cFiltreDeRelationOrient > & Filtre();
        const cTplValGesInit< cFiltreDeRelationOrient > & Filtre()const ;

        cTplValGesInit< bool > & Sym();
        const cTplValGesInit< bool > & Sym()const ;

        cTplValGesInit< bool > & Reflexif();
        const cTplValGesInit< bool > & Reflexif()const ;
    private:
        std::list< cCpleString > mCplesKey;
        std::list< cByAdjDeGroupes > mByAdjDeGroupes;
        cTplValGesInit< cFiltreDeRelationOrient > mFiltre;
        cTplValGesInit< bool > mSym;
        cTplValGesInit< bool > mReflexif;
};
cElXMLTree * ToXMLTree(const cByGroupesDImages &);

/******************************************************/
/******************************************************/
/******************************************************/
class cFiltreDelaunay
{
    public:
        friend void xml_init(cFiltreDelaunay & anObj,cElXMLTree * aTree);


        cTplValGesInit< double > & DMaxDelaunay();
        const cTplValGesInit< double > & DMaxDelaunay()const ;
    private:
        cTplValGesInit< double > mDMaxDelaunay;
};
cElXMLTree * ToXMLTree(const cFiltreDelaunay &);

class cFiltreDist
{
    public:
        friend void xml_init(cFiltreDist & anObj,cElXMLTree * aTree);


        double & DistMax();
        const double & DistMax()const ;
    private:
        double mDistMax;
};
cElXMLTree * ToXMLTree(const cFiltreDist &);

class cModeFiltreSpatial
{
    public:
        friend void xml_init(cModeFiltreSpatial & anObj,cElXMLTree * aTree);


        cTplValGesInit< double > & DMaxDelaunay();
        const cTplValGesInit< double > & DMaxDelaunay()const ;

        cTplValGesInit< cFiltreDelaunay > & FiltreDelaunay();
        const cTplValGesInit< cFiltreDelaunay > & FiltreDelaunay()const ;

        double & DistMax();
        const double & DistMax()const ;

        cTplValGesInit< cFiltreDist > & FiltreDist();
        const cTplValGesInit< cFiltreDist > & FiltreDist()const ;
    private:
        cTplValGesInit< cFiltreDelaunay > mFiltreDelaunay;
        cTplValGesInit< cFiltreDist > mFiltreDist;
};
cElXMLTree * ToXMLTree(const cModeFiltreSpatial &);

class cByFiltreSpatial
{
    public:
        friend void xml_init(cByFiltreSpatial & anObj,cElXMLTree * aTree);


        cTplValGesInit< std::string > & ByFileTrajecto();
        const cTplValGesInit< std::string > & ByFileTrajecto()const ;

        std::string & KeyOri();
        const std::string & KeyOri()const ;

        std::string & KeySet();
        const std::string & KeySet()const ;

        cTplValGesInit< std::string > & TagCentre();
        const cTplValGesInit< std::string > & TagCentre()const ;

        cTplValGesInit< bool > & Sym();
        const cTplValGesInit< bool > & Sym()const ;

        cTplValGesInit< cFiltreDeRelationOrient > & FiltreSup();
        const cTplValGesInit< cFiltreDeRelationOrient > & FiltreSup()const ;

        cTplValGesInit< double > & DMaxDelaunay();
        const cTplValGesInit< double > & DMaxDelaunay()const ;

        cTplValGesInit< cFiltreDelaunay > & FiltreDelaunay();
        const cTplValGesInit< cFiltreDelaunay > & FiltreDelaunay()const ;

        double & DistMax();
        const double & DistMax()const ;

        cTplValGesInit< cFiltreDist > & FiltreDist();
        const cTplValGesInit< cFiltreDist > & FiltreDist()const ;

        cModeFiltreSpatial & ModeFiltreSpatial();
        const cModeFiltreSpatial & ModeFiltreSpatial()const ;
    private:
        cTplValGesInit< std::string > mByFileTrajecto;
        std::string mKeyOri;
        std::string mKeySet;
        cTplValGesInit< std::string > mTagCentre;
        cTplValGesInit< bool > mSym;
        cTplValGesInit< cFiltreDeRelationOrient > mFiltreSup;
        cModeFiltreSpatial mModeFiltreSpatial;
};
cElXMLTree * ToXMLTree(const cByFiltreSpatial &);

/******************************************************/
/******************************************************/
/******************************************************/
class cByAdjacence
{
    public:
        friend void xml_init(cByAdjacence & anObj,cElXMLTree * aTree);


        std::vector< std::string > & KeySets();
        const std::vector< std::string > & KeySets()const ;

        cTplValGesInit< IntSubst > & DeltaMax();
        const cTplValGesInit< IntSubst > & DeltaMax()const ;

        cTplValGesInit< IntSubst > & DeltaMin();
        const cTplValGesInit< IntSubst > & DeltaMin()const ;

        cTplValGesInit< cFiltreDeRelationOrient > & Filtre();
        const cTplValGesInit< cFiltreDeRelationOrient > & Filtre()const ;

        cTplValGesInit< bool > & Sym();
        const cTplValGesInit< bool > & Sym()const ;

        cTplValGesInit< bool > & Circ();
        const cTplValGesInit< bool > & Circ()const ;
    private:
        std::vector< std::string > mKeySets;
        cTplValGesInit< IntSubst > mDeltaMax;
        cTplValGesInit< IntSubst > mDeltaMin;
        cTplValGesInit< cFiltreDeRelationOrient > mFiltre;
        cTplValGesInit< bool > mSym;
        cTplValGesInit< bool > mCirc;
};
cElXMLTree * ToXMLTree(const cByAdjacence &);

/******************************************************/
/******************************************************/
/******************************************************/
class cNameRelDescriptor
{
    public:
        friend void xml_init(cNameRelDescriptor & anObj,cElXMLTree * aTree);


        std::list< std::string > & NameFileIn();
        const std::list< std::string > & NameFileIn()const ;

        cTplValGesInit< bool > & Reflexif();
        const cTplValGesInit< bool > & Reflexif()const ;

        cTplValGesInit< std::string > & NameFileSauvegarde();
        const cTplValGesInit< std::string > & NameFileSauvegarde()const ;

        std::list< cRelByGrapheExpl > & RelByGrapheExpl();
        const std::list< cRelByGrapheExpl > & RelByGrapheExpl()const ;

        std::list< cByGroupesDImages > & ByGroupesDImages();
        const std::list< cByGroupesDImages > & ByGroupesDImages()const ;

        std::list< cByFiltreSpatial > & ByFiltreSpatial();
        const std::list< cByFiltreSpatial > & ByFiltreSpatial()const ;

        std::list< cByAdjacence > & ByAdjacence();
        const std::list< cByAdjacence > & ByAdjacence()const ;

        std::list< cCpleString > & CplesExcl();
        const std::list< cCpleString > & CplesExcl()const ;
    private:
        std::list< std::string > mNameFileIn;
        cTplValGesInit< bool > mReflexif;
        cTplValGesInit< std::string > mNameFileSauvegarde;
        std::list< cRelByGrapheExpl > mRelByGrapheExpl;
        std::list< cByGroupesDImages > mByGroupesDImages;
        std::list< cByFiltreSpatial > mByFiltreSpatial;
        std::list< cByAdjacence > mByAdjacence;
        std::list< cCpleString > mCplesExcl;
};
cElXMLTree * ToXMLTree(const cNameRelDescriptor &);

/******************************************************/
/******************************************************/
/******************************************************/
class cExeRequired
{
    public:
        friend void xml_init(cExeRequired & anObj,cElXMLTree * aTree);


        std::string & Exe();
        const std::string & Exe()const ;

        std::string & Make();
        const std::string & Make()const ;
    private:
        std::string mExe;
        std::string mMake;
};
cElXMLTree * ToXMLTree(const cExeRequired &);

/******************************************************/
/******************************************************/
/******************************************************/
class cFileRequired
{
    public:
        friend void xml_init(cFileRequired & anObj,cElXMLTree * aTree);


        std::list< std::string > & Pattern();
        const std::list< std::string > & Pattern()const ;

        cTplValGesInit< int > & NbMin();
        const cTplValGesInit< int > & NbMin()const ;

        cTplValGesInit< int > & NbMax();
        const cTplValGesInit< int > & NbMax()const ;
    private:
        std::list< std::string > mPattern;
        cTplValGesInit< int > mNbMin;
        cTplValGesInit< int > mNbMax;
};
cElXMLTree * ToXMLTree(const cFileRequired &);

/******************************************************/
/******************************************************/
/******************************************************/
class cBatchRequirement
{
    public:
        friend void xml_init(cBatchRequirement & anObj,cElXMLTree * aTree);


        std::list< cExeRequired > & ExeRequired();
        const std::list< cExeRequired > & ExeRequired()const ;

        std::list< cFileRequired > & FileRequired();
        const std::list< cFileRequired > & FileRequired()const ;
    private:
        std::list< cExeRequired > mExeRequired;
        std::list< cFileRequired > mFileRequired;
};
cElXMLTree * ToXMLTree(const cBatchRequirement &);

/******************************************************/
/******************************************************/
/******************************************************/
class cExportApero2MM
{
    public:
        friend void xml_init(cExportApero2MM & anObj,cElXMLTree * aTree);


        cTplValGesInit< Pt3dr > & DirVertLoc();
        const cTplValGesInit< Pt3dr > & DirVertLoc()const ;

        cTplValGesInit< double > & ProfInVertLoc();
        const cTplValGesInit< double > & ProfInVertLoc()const ;
    private:
        cTplValGesInit< Pt3dr > mDirVertLoc;
        cTplValGesInit< double > mProfInVertLoc;
};
cElXMLTree * ToXMLTree(const cExportApero2MM &);

/******************************************************/
/******************************************************/
/******************************************************/
class cCameraEntry
{
    public:
        friend void xml_init(cCameraEntry & anObj,cElXMLTree * aTree);


        std::string & Name();
        const std::string & Name()const ;

        Pt2dr & SzCaptMm();
        const Pt2dr & SzCaptMm()const ;

        std::string & ShortName();
        const std::string & ShortName()const ;

        cTplValGesInit< bool > & BayerSwapRB();
        const cTplValGesInit< bool > & BayerSwapRB()const ;

        cTplValGesInit< bool > & DevRawBasic();
        const cTplValGesInit< bool > & DevRawBasic()const ;
    private:
        std::string mName;
        Pt2dr mSzCaptMm;
        std::string mShortName;
        cTplValGesInit< bool > mBayerSwapRB;
        cTplValGesInit< bool > mDevRawBasic;
};
cElXMLTree * ToXMLTree(const cCameraEntry &);

/******************************************************/
/******************************************************/
/******************************************************/
class cMMCameraDataBase
{
    public:
        friend void xml_init(cMMCameraDataBase & anObj,cElXMLTree * aTree);


        std::list< cCameraEntry > & CameraEntry();
        const std::list< cCameraEntry > & CameraEntry()const ;
    private:
        std::list< cCameraEntry > mCameraEntry;
};
cElXMLTree * ToXMLTree(const cMMCameraDataBase &);

/******************************************************/
/******************************************************/
/******************************************************/
class cMakeDataBase
{
    public:
        friend void xml_init(cMakeDataBase & anObj,cElXMLTree * aTree);


        std::string & KeySetCollectXif();
        const std::string & KeySetCollectXif()const ;

        std::list< std::string > & KeyAssocNameSup();
        const std::list< std::string > & KeyAssocNameSup()const ;

        cTplValGesInit< std::string > & NameFile();
        const cTplValGesInit< std::string > & NameFile()const ;
    private:
        std::string mKeySetCollectXif;
        std::list< std::string > mKeyAssocNameSup;
        cTplValGesInit< std::string > mNameFile;
};
cElXMLTree * ToXMLTree(const cMakeDataBase &);

/******************************************************/
/******************************************************/
/******************************************************/
class cBatchChantDesc
{
    public:
        friend void xml_init(cBatchChantDesc & anObj,cElXMLTree * aTree);


        cTplValGesInit< cBatchRequirement > & Requirement();
        const cTplValGesInit< cBatchRequirement > & Requirement()const ;

        std::string & Key();
        const std::string & Key()const ;

        std::list< std::string > & Line();
        const std::list< std::string > & Line()const ;
    private:
        cTplValGesInit< cBatchRequirement > mRequirement;
        std::string mKey;
        std::list< std::string > mLine;
};
cElXMLTree * ToXMLTree(const cBatchChantDesc &);

/******************************************************/
/******************************************************/
/******************************************************/
class cOneShowChantDesc
{
    public:
        friend void xml_init(cOneShowChantDesc & anObj,cElXMLTree * aTree);


        std::list< std::string > & LineBefore();
        const std::list< std::string > & LineBefore()const ;

        cTplValGesInit< bool > & ShowKeys();
        const cTplValGesInit< bool > & ShowKeys()const ;

        std::list< std::string > & KeyRels();
        const std::list< std::string > & KeyRels()const ;

        std::list< std::string > & KeySets();
        const std::list< std::string > & KeySets()const ;

        std::list< std::string > & LineAfter();
        const std::list< std::string > & LineAfter()const ;
    private:
        std::list< std::string > mLineBefore;
        cTplValGesInit< bool > mShowKeys;
        std::list< std::string > mKeyRels;
        std::list< std::string > mKeySets;
        std::list< std::string > mLineAfter;
};
cElXMLTree * ToXMLTree(const cOneShowChantDesc &);

class cShowChantDesc
{
    public:
        friend void xml_init(cShowChantDesc & anObj,cElXMLTree * aTree);


        std::list< cOneShowChantDesc > & OneShowChantDesc();
        const std::list< cOneShowChantDesc > & OneShowChantDesc()const ;

        std::string & File();
        const std::string & File()const ;
    private:
        std::list< cOneShowChantDesc > mOneShowChantDesc;
        std::string mFile;
};
cElXMLTree * ToXMLTree(const cShowChantDesc &);

/******************************************************/
/******************************************************/
/******************************************************/
class cMatrixSplitBox
{
    public:
        friend void xml_init(cMatrixSplitBox & anObj,cElXMLTree * aTree);


        std::string & KeyMatr();
        const std::string & KeyMatr()const ;

        cTplValGesInit< double > & Rab();
        const cTplValGesInit< double > & Rab()const ;
    private:
        std::string mKeyMatr;
        cTplValGesInit< double > mRab;
};
cElXMLTree * ToXMLTree(const cMatrixSplitBox &);

class cContenuAPrioriImage
{
    public:
        friend void xml_init(cContenuAPrioriImage & anObj,cElXMLTree * aTree);


        cTplValGesInit< std::string > & KeyAutoAdaptScale();
        const cTplValGesInit< std::string > & KeyAutoAdaptScale()const ;

        cTplValGesInit< double > & PdsMaxAdaptScale();
        const cTplValGesInit< double > & PdsMaxAdaptScale()const ;

        cTplValGesInit< double > & Scale();
        const cTplValGesInit< double > & Scale()const ;

        cTplValGesInit< double > & Teta();
        const cTplValGesInit< double > & Teta()const ;

        cTplValGesInit< Box2di > & BoiteEnglob();
        const cTplValGesInit< Box2di > & BoiteEnglob()const ;

        cTplValGesInit< std::string > & ElInt_CaPImAddedSet();
        const cTplValGesInit< std::string > & ElInt_CaPImAddedSet()const ;

        cTplValGesInit< std::string > & ElInt_CaPImMyKey();
        const cTplValGesInit< std::string > & ElInt_CaPImMyKey()const ;

        std::string & KeyMatr();
        const std::string & KeyMatr()const ;

        cTplValGesInit< double > & Rab();
        const cTplValGesInit< double > & Rab()const ;

        cTplValGesInit< cMatrixSplitBox > & MatrixSplitBox();
        const cTplValGesInit< cMatrixSplitBox > & MatrixSplitBox()const ;
    private:
        cTplValGesInit< std::string > mKeyAutoAdaptScale;
        cTplValGesInit< double > mPdsMaxAdaptScale;
        cTplValGesInit< double > mScale;
        cTplValGesInit< double > mTeta;
        cTplValGesInit< Box2di > mBoiteEnglob;
        cTplValGesInit< std::string > mElInt_CaPImAddedSet;
        cTplValGesInit< std::string > mElInt_CaPImMyKey;
        cTplValGesInit< cMatrixSplitBox > mMatrixSplitBox;
};
cElXMLTree * ToXMLTree(const cContenuAPrioriImage &);

class cAPrioriImage
{
    public:
        friend void xml_init(cAPrioriImage & anObj,cElXMLTree * aTree);


        std::list< std::string > & Names();
        const std::list< std::string > & Names()const ;

        cTplValGesInit< std::string > & KeyedAddedSet();
        const cTplValGesInit< std::string > & KeyedAddedSet()const ;

        cTplValGesInit< std::string > & Key();
        const cTplValGesInit< std::string > & Key()const ;

        cTplValGesInit< std::string > & KeyAutoAdaptScale();
        const cTplValGesInit< std::string > & KeyAutoAdaptScale()const ;

        cTplValGesInit< double > & PdsMaxAdaptScale();
        const cTplValGesInit< double > & PdsMaxAdaptScale()const ;

        cTplValGesInit< double > & Scale();
        const cTplValGesInit< double > & Scale()const ;

        cTplValGesInit< double > & Teta();
        const cTplValGesInit< double > & Teta()const ;

        cTplValGesInit< Box2di > & BoiteEnglob();
        const cTplValGesInit< Box2di > & BoiteEnglob()const ;

        cTplValGesInit< std::string > & ElInt_CaPImAddedSet();
        const cTplValGesInit< std::string > & ElInt_CaPImAddedSet()const ;

        cTplValGesInit< std::string > & ElInt_CaPImMyKey();
        const cTplValGesInit< std::string > & ElInt_CaPImMyKey()const ;

        std::string & KeyMatr();
        const std::string & KeyMatr()const ;

        cTplValGesInit< double > & Rab();
        const cTplValGesInit< double > & Rab()const ;

        cTplValGesInit< cMatrixSplitBox > & MatrixSplitBox();
        const cTplValGesInit< cMatrixSplitBox > & MatrixSplitBox()const ;

        cContenuAPrioriImage & ContenuAPrioriImage();
        const cContenuAPrioriImage & ContenuAPrioriImage()const ;
    private:
        std::list< std::string > mNames;
        cTplValGesInit< std::string > mKeyedAddedSet;
        cTplValGesInit< std::string > mKey;
        cContenuAPrioriImage mContenuAPrioriImage;
};
cElXMLTree * ToXMLTree(const cAPrioriImage &);

/******************************************************/
/******************************************************/
/******************************************************/
class cKeyedNamesAssociations
{
    public:
        friend void xml_init(cKeyedNamesAssociations & anObj,cElXMLTree * aTree);


        cTplValGesInit< bool > & IsParametrized();
        const cTplValGesInit< bool > & IsParametrized()const ;

        std::list< cAssocNameToName > & Calcs();
        const std::list< cAssocNameToName > & Calcs()const ;

        std::string & Key();
        const std::string & Key()const ;

        cTplValGesInit< std::string > & SubDirAutoMake();
        const cTplValGesInit< std::string > & SubDirAutoMake()const ;

        cTplValGesInit< bool > & SubDirAutoMakeRec();
        const cTplValGesInit< bool > & SubDirAutoMakeRec()const ;
    private:
        cTplValGesInit< bool > mIsParametrized;
        std::list< cAssocNameToName > mCalcs;
        std::string mKey;
        cTplValGesInit< std::string > mSubDirAutoMake;
        cTplValGesInit< bool > mSubDirAutoMakeRec;
};
cElXMLTree * ToXMLTree(const cKeyedNamesAssociations &);

/******************************************************/
/******************************************************/
/******************************************************/
class cKeyedSetsOfNames
{
    public:
        friend void xml_init(cKeyedSetsOfNames & anObj,cElXMLTree * aTree);


        cTplValGesInit< bool > & IsParametrized();
        const cTplValGesInit< bool > & IsParametrized()const ;

        cSetNameDescriptor & Sets();
        const cSetNameDescriptor & Sets()const ;

        std::string & Key();
        const std::string & Key()const ;
    private:
        cTplValGesInit< bool > mIsParametrized;
        cSetNameDescriptor mSets;
        std::string mKey;
};
cElXMLTree * ToXMLTree(const cKeyedSetsOfNames &);

/******************************************************/
/******************************************************/
/******************************************************/
class cKeyedSetsORels
{
    public:
        friend void xml_init(cKeyedSetsORels & anObj,cElXMLTree * aTree);


        cTplValGesInit< bool > & IsParametrized();
        const cTplValGesInit< bool > & IsParametrized()const ;

        cNameRelDescriptor & Sets();
        const cNameRelDescriptor & Sets()const ;

        std::string & Key();
        const std::string & Key()const ;
    private:
        cTplValGesInit< bool > mIsParametrized;
        cNameRelDescriptor mSets;
        std::string mKey;
};
cElXMLTree * ToXMLTree(const cKeyedSetsORels &);

/******************************************************/
/******************************************************/
/******************************************************/
class cKeyedMatrixStruct
{
    public:
        friend void xml_init(cKeyedMatrixStruct & anObj,cElXMLTree * aTree);


        cImMatrixStructuration & Matrix();
        const cImMatrixStructuration & Matrix()const ;

        std::string & Key();
        const std::string & Key()const ;
    private:
        cImMatrixStructuration mMatrix;
        std::string mKey;
};
cElXMLTree * ToXMLTree(const cKeyedMatrixStruct &);

/******************************************************/
/******************************************************/
/******************************************************/
class cChantierDescripteur
{
    public:
        friend void xml_init(cChantierDescripteur & anObj,cElXMLTree * aTree);


        cTplValGesInit< bool > & ExitOnBrkp();
        const cTplValGesInit< bool > & ExitOnBrkp()const ;

        std::list< std::string > & Symb();
        const std::list< std::string > & Symb()const ;

        std::list< std::string > & eSymb();
        const std::list< std::string > & eSymb()const ;

        cTplValGesInit< cMMCameraDataBase > & LocCamDataBase();
        const cTplValGesInit< cMMCameraDataBase > & LocCamDataBase()const ;

        std::string & KeySetCollectXif();
        const std::string & KeySetCollectXif()const ;

        std::list< std::string > & KeyAssocNameSup();
        const std::list< std::string > & KeyAssocNameSup()const ;

        cTplValGesInit< std::string > & NameFile();
        const cTplValGesInit< std::string > & NameFile()const ;

        cTplValGesInit< cMakeDataBase > & MakeDataBase();
        const cTplValGesInit< cMakeDataBase > & MakeDataBase()const ;

        cTplValGesInit< std::string > & KeySuprAbs2Rel();
        const cTplValGesInit< std::string > & KeySuprAbs2Rel()const ;

        std::list< cBatchChantDesc > & BatchChantDesc();
        const std::list< cBatchChantDesc > & BatchChantDesc()const ;

        std::list< cShowChantDesc > & ShowChantDesc();
        const std::list< cShowChantDesc > & ShowChantDesc()const ;

        std::list< cAPrioriImage > & APrioriImage();
        const std::list< cAPrioriImage > & APrioriImage()const ;

        std::list< cKeyedNamesAssociations > & KeyedNamesAssociations();
        const std::list< cKeyedNamesAssociations > & KeyedNamesAssociations()const ;

        std::list< cKeyedSetsOfNames > & KeyedSetsOfNames();
        const std::list< cKeyedSetsOfNames > & KeyedSetsOfNames()const ;

        std::list< cKeyedSetsORels > & KeyedSetsORels();
        const std::list< cKeyedSetsORels > & KeyedSetsORels()const ;

        std::list< cKeyedMatrixStruct > & KeyedMatrixStruct();
        const std::list< cKeyedMatrixStruct > & KeyedMatrixStruct()const ;

        std::list< cClassEquivDescripteur > & KeyedClassEquiv();
        const std::list< cClassEquivDescripteur > & KeyedClassEquiv()const ;

        cTplValGesInit< cBaseDataCD > & BaseDatas();
        const cTplValGesInit< cBaseDataCD > & BaseDatas()const ;

        std::list< std::string > & FilesDatas();
        const std::list< std::string > & FilesDatas()const ;
    private:
        cTplValGesInit< bool > mExitOnBrkp;
        std::list< std::string > mSymb;
        std::list< std::string > meSymb;
        cTplValGesInit< cMMCameraDataBase > mLocCamDataBase;
        cTplValGesInit< cMakeDataBase > mMakeDataBase;
        cTplValGesInit< std::string > mKeySuprAbs2Rel;
        std::list< cBatchChantDesc > mBatchChantDesc;
        std::list< cShowChantDesc > mShowChantDesc;
        std::list< cAPrioriImage > mAPrioriImage;
        std::list< cKeyedNamesAssociations > mKeyedNamesAssociations;
        std::list< cKeyedSetsOfNames > mKeyedSetsOfNames;
        std::list< cKeyedSetsORels > mKeyedSetsORels;
        std::list< cKeyedMatrixStruct > mKeyedMatrixStruct;
        std::list< cClassEquivDescripteur > mKeyedClassEquiv;
        cTplValGesInit< cBaseDataCD > mBaseDatas;
        std::list< std::string > mFilesDatas;
};
cElXMLTree * ToXMLTree(const cChantierDescripteur &);

/******************************************************/
/******************************************************/
/******************************************************/
class cXML_Date
{
    public:
        friend void xml_init(cXML_Date & anObj,cElXMLTree * aTree);


        int & year();
        const int & year()const ;

        int & month();
        const int & month()const ;

        int & day();
        const int & day()const ;

        int & hour();
        const int & hour()const ;

        int & minute();
        const int & minute()const ;

        int & second();
        const int & second()const ;

        std::string & time_system();
        const std::string & time_system()const ;
    private:
        int myear;
        int mmonth;
        int mday;
        int mhour;
        int mminute;
        int msecond;
        std::string mtime_system;
};
cElXMLTree * ToXMLTree(const cXML_Date &);

/******************************************************/
/******************************************************/
/******************************************************/
class cpt3d
{
    public:
        friend void xml_init(cpt3d & anObj,cElXMLTree * aTree);


        double & x();
        const double & x()const ;

        double & y();
        const double & y()const ;

        double & z();
        const double & z()const ;
    private:
        double mx;
        double my;
        double mz;
};
cElXMLTree * ToXMLTree(const cpt3d &);

/******************************************************/
/******************************************************/
/******************************************************/
class cXML_LinePt3d
{
    public:
        friend void xml_init(cXML_LinePt3d & anObj,cElXMLTree * aTree);


        double & x();
        const double & x()const ;

        double & y();
        const double & y()const ;

        double & z();
        const double & z()const ;

        cpt3d & pt3d();
        const cpt3d & pt3d()const ;
    private:
        cpt3d mpt3d;
};
cElXMLTree * ToXMLTree(const cXML_LinePt3d &);

/******************************************************/
/******************************************************/
/******************************************************/
class cauxiliarydata
{
    public:
        friend void xml_init(cauxiliarydata & anObj,cElXMLTree * aTree);


        std::string & image_name();
        const std::string & image_name()const ;

        std::string & stereopolis();
        const std::string & stereopolis()const ;

        cXML_Date & image_date();
        const cXML_Date & image_date()const ;

        std::list< std::string > & samples();
        const std::list< std::string > & samples()const ;
    private:
        std::string mimage_name;
        std::string mstereopolis;
        cXML_Date mimage_date;
        std::list< std::string > msamples;
};
cElXMLTree * ToXMLTree(const cauxiliarydata &);

/******************************************************/
/******************************************************/
/******************************************************/
class ceuclidien
{
    public:
        friend void xml_init(ceuclidien & anObj,cElXMLTree * aTree);


        double & x();
        const double & x()const ;

        double & y();
        const double & y()const ;
    private:
        double mx;
        double my;
};
cElXMLTree * ToXMLTree(const ceuclidien &);

class csysteme
{
    public:
        friend void xml_init(csysteme & anObj,cElXMLTree * aTree);


        ceuclidien & euclidien();
        const ceuclidien & euclidien()const ;

        std::string & geodesique();
        const std::string & geodesique()const ;
    private:
        ceuclidien meuclidien;
        std::string mgeodesique;
};
cElXMLTree * ToXMLTree(const csysteme &);

class csommet
{
    public:
        friend void xml_init(csommet & anObj,cElXMLTree * aTree);


        double & easting();
        const double & easting()const ;

        double & northing();
        const double & northing()const ;

        double & altitude();
        const double & altitude()const ;
    private:
        double measting;
        double mnorthing;
        double maltitude;
};
cElXMLTree * ToXMLTree(const csommet &);

class cmat3d
{
    public:
        friend void xml_init(cmat3d & anObj,cElXMLTree * aTree);


        cXML_LinePt3d & l1();
        const cXML_LinePt3d & l1()const ;

        cXML_LinePt3d & l2();
        const cXML_LinePt3d & l2()const ;

        cXML_LinePt3d & l3();
        const cXML_LinePt3d & l3()const ;
    private:
        cXML_LinePt3d ml1;
        cXML_LinePt3d ml2;
        cXML_LinePt3d ml3;
};
cElXMLTree * ToXMLTree(const cmat3d &);

class crotation
{
    public:
        friend void xml_init(crotation & anObj,cElXMLTree * aTree);


        bool & Image2Ground();
        const bool & Image2Ground()const ;

        cXML_LinePt3d & l1();
        const cXML_LinePt3d & l1()const ;

        cXML_LinePt3d & l2();
        const cXML_LinePt3d & l2()const ;

        cXML_LinePt3d & l3();
        const cXML_LinePt3d & l3()const ;

        cmat3d & mat3d();
        const cmat3d & mat3d()const ;
    private:
        bool mImage2Ground;
        cmat3d mmat3d;
};
cElXMLTree * ToXMLTree(const crotation &);

class cextrinseque
{
    public:
        friend void xml_init(cextrinseque & anObj,cElXMLTree * aTree);


        ceuclidien & euclidien();
        const ceuclidien & euclidien()const ;

        std::string & geodesique();
        const std::string & geodesique()const ;

        csysteme & systeme();
        const csysteme & systeme()const ;

        std::string & grid_alti();
        const std::string & grid_alti()const ;

        double & easting();
        const double & easting()const ;

        double & northing();
        const double & northing()const ;

        double & altitude();
        const double & altitude()const ;

        csommet & sommet();
        const csommet & sommet()const ;

        bool & Image2Ground();
        const bool & Image2Ground()const ;

        cXML_LinePt3d & l1();
        const cXML_LinePt3d & l1()const ;

        cXML_LinePt3d & l2();
        const cXML_LinePt3d & l2()const ;

        cXML_LinePt3d & l3();
        const cXML_LinePt3d & l3()const ;

        cmat3d & mat3d();
        const cmat3d & mat3d()const ;

        crotation & rotation();
        const crotation & rotation()const ;
    private:
        csysteme msysteme;
        std::string mgrid_alti;
        csommet msommet;
        crotation mrotation;
};
cElXMLTree * ToXMLTree(const cextrinseque &);

class cimage_size
{
    public:
        friend void xml_init(cimage_size & anObj,cElXMLTree * aTree);


        int & width();
        const int & width()const ;

        int & height();
        const int & height()const ;
    private:
        int mwidth;
        int mheight;
};
cElXMLTree * ToXMLTree(const cimage_size &);

class cppa
{
    public:
        friend void xml_init(cppa & anObj,cElXMLTree * aTree);


        double & c();
        const double & c()const ;

        double & l();
        const double & l()const ;

        double & focale();
        const double & focale()const ;
    private:
        double mc;
        double ml;
        double mfocale;
};
cElXMLTree * ToXMLTree(const cppa &);

class cpps
{
    public:
        friend void xml_init(cpps & anObj,cElXMLTree * aTree);


        double & c();
        const double & c()const ;

        double & l();
        const double & l()const ;
    private:
        double mc;
        double ml;
};
cElXMLTree * ToXMLTree(const cpps &);

class cdistortion
{
    public:
        friend void xml_init(cdistortion & anObj,cElXMLTree * aTree);


        cpps & pps();
        const cpps & pps()const ;

        double & r1();
        const double & r1()const ;

        double & r3();
        const double & r3()const ;

        double & r5();
        const double & r5()const ;

        double & r7();
        const double & r7()const ;
    private:
        cpps mpps;
        double mr1;
        double mr3;
        double mr5;
        double mr7;
};
cElXMLTree * ToXMLTree(const cdistortion &);

class csensor
{
    public:
        friend void xml_init(csensor & anObj,cElXMLTree * aTree);


        std::string & name();
        const std::string & name()const ;

        cXML_Date & calibration_date();
        const cXML_Date & calibration_date()const ;

        std::string & serial_number();
        const std::string & serial_number()const ;

        int & width();
        const int & width()const ;

        int & height();
        const int & height()const ;

        cimage_size & image_size();
        const cimage_size & image_size()const ;

        cppa & ppa();
        const cppa & ppa()const ;

        cpps & pps();
        const cpps & pps()const ;

        double & r1();
        const double & r1()const ;

        double & r3();
        const double & r3()const ;

        double & r5();
        const double & r5()const ;

        double & r7();
        const double & r7()const ;

        cdistortion & distortion();
        const cdistortion & distortion()const ;
    private:
        std::string mname;
        cXML_Date mcalibration_date;
        std::string mserial_number;
        cimage_size mimage_size;
        cppa mppa;
        cdistortion mdistortion;
};
cElXMLTree * ToXMLTree(const csensor &);

class cintrinseque
{
    public:
        friend void xml_init(cintrinseque & anObj,cElXMLTree * aTree);


        std::string & name();
        const std::string & name()const ;

        cXML_Date & calibration_date();
        const cXML_Date & calibration_date()const ;

        std::string & serial_number();
        const std::string & serial_number()const ;

        int & width();
        const int & width()const ;

        int & height();
        const int & height()const ;

        cimage_size & image_size();
        const cimage_size & image_size()const ;

        cppa & ppa();
        const cppa & ppa()const ;

        cpps & pps();
        const cpps & pps()const ;

        double & r1();
        const double & r1()const ;

        double & r3();
        const double & r3()const ;

        double & r5();
        const double & r5()const ;

        double & r7();
        const double & r7()const ;

        cdistortion & distortion();
        const cdistortion & distortion()const ;

        csensor & sensor();
        const csensor & sensor()const ;
    private:
        csensor msensor;
};
cElXMLTree * ToXMLTree(const cintrinseque &);

class cgeometry
{
    public:
        friend void xml_init(cgeometry & anObj,cElXMLTree * aTree);


        ceuclidien & euclidien();
        const ceuclidien & euclidien()const ;

        std::string & geodesique();
        const std::string & geodesique()const ;

        csysteme & systeme();
        const csysteme & systeme()const ;

        std::string & grid_alti();
        const std::string & grid_alti()const ;

        double & easting();
        const double & easting()const ;

        double & northing();
        const double & northing()const ;

        double & altitude();
        const double & altitude()const ;

        csommet & sommet();
        const csommet & sommet()const ;

        bool & Image2Ground();
        const bool & Image2Ground()const ;

        cXML_LinePt3d & l1();
        const cXML_LinePt3d & l1()const ;

        cXML_LinePt3d & l2();
        const cXML_LinePt3d & l2()const ;

        cXML_LinePt3d & l3();
        const cXML_LinePt3d & l3()const ;

        cmat3d & mat3d();
        const cmat3d & mat3d()const ;

        crotation & rotation();
        const crotation & rotation()const ;

        cextrinseque & extrinseque();
        const cextrinseque & extrinseque()const ;

        std::string & name();
        const std::string & name()const ;

        cXML_Date & calibration_date();
        const cXML_Date & calibration_date()const ;

        std::string & serial_number();
        const std::string & serial_number()const ;

        int & width();
        const int & width()const ;

        int & height();
        const int & height()const ;

        cimage_size & image_size();
        const cimage_size & image_size()const ;

        cppa & ppa();
        const cppa & ppa()const ;

        cpps & pps();
        const cpps & pps()const ;

        double & r1();
        const double & r1()const ;

        double & r3();
        const double & r3()const ;

        double & r5();
        const double & r5()const ;

        double & r7();
        const double & r7()const ;

        cdistortion & distortion();
        const cdistortion & distortion()const ;

        csensor & sensor();
        const csensor & sensor()const ;

        cintrinseque & intrinseque();
        const cintrinseque & intrinseque()const ;
    private:
        cextrinseque mextrinseque;
        cintrinseque mintrinseque;
};
cElXMLTree * ToXMLTree(const cgeometry &);

/******************************************************/
/******************************************************/
/******************************************************/
class corientation
{
    public:
        friend void xml_init(corientation & anObj,cElXMLTree * aTree);


        double & version();
        const double & version()const ;

        std::string & image_name();
        const std::string & image_name()const ;

        std::string & stereopolis();
        const std::string & stereopolis()const ;

        cXML_Date & image_date();
        const cXML_Date & image_date()const ;

        std::list< std::string > & samples();
        const std::list< std::string > & samples()const ;

        cauxiliarydata & auxiliarydata();
        const cauxiliarydata & auxiliarydata()const ;

        ceuclidien & euclidien();
        const ceuclidien & euclidien()const ;

        std::string & geodesique();
        const std::string & geodesique()const ;

        csysteme & systeme();
        const csysteme & systeme()const ;

        std::string & grid_alti();
        const std::string & grid_alti()const ;

        double & easting();
        const double & easting()const ;

        double & northing();
        const double & northing()const ;

        double & altitude();
        const double & altitude()const ;

        csommet & sommet();
        const csommet & sommet()const ;

        bool & Image2Ground();
        const bool & Image2Ground()const ;

        cXML_LinePt3d & l1();
        const cXML_LinePt3d & l1()const ;

        cXML_LinePt3d & l2();
        const cXML_LinePt3d & l2()const ;

        cXML_LinePt3d & l3();
        const cXML_LinePt3d & l3()const ;

        cmat3d & mat3d();
        const cmat3d & mat3d()const ;

        crotation & rotation();
        const crotation & rotation()const ;

        cextrinseque & extrinseque();
        const cextrinseque & extrinseque()const ;

        std::string & name();
        const std::string & name()const ;

        cXML_Date & calibration_date();
        const cXML_Date & calibration_date()const ;

        std::string & serial_number();
        const std::string & serial_number()const ;

        int & width();
        const int & width()const ;

        int & height();
        const int & height()const ;

        cimage_size & image_size();
        const cimage_size & image_size()const ;

        cppa & ppa();
        const cppa & ppa()const ;

        cpps & pps();
        const cpps & pps()const ;

        double & r1();
        const double & r1()const ;

        double & r3();
        const double & r3()const ;

        double & r5();
        const double & r5()const ;

        double & r7();
        const double & r7()const ;

        cdistortion & distortion();
        const cdistortion & distortion()const ;

        csensor & sensor();
        const csensor & sensor()const ;

        cintrinseque & intrinseque();
        const cintrinseque & intrinseque()const ;

        cgeometry & geometry();
        const cgeometry & geometry()const ;
    private:
        double mversion;
        cauxiliarydata mauxiliarydata;
        cgeometry mgeometry;
};
cElXMLTree * ToXMLTree(const corientation &);

/******************************************************/
/******************************************************/
/******************************************************/
class cOneSolImageSec
{
    public:
        friend void xml_init(cOneSolImageSec & anObj,cElXMLTree * aTree);


        std::list< std::string > & Images();
        const std::list< std::string > & Images()const ;

        double & Coverage();
        const double & Coverage()const ;

        double & Score();
        const double & Score()const ;
    private:
        std::list< std::string > mImages;
        double mCoverage;
        double mScore;
};
cElXMLTree * ToXMLTree(const cOneSolImageSec &);

/******************************************************/
/******************************************************/
/******************************************************/
class cISOM_Vois
{
    public:
        friend void xml_init(cISOM_Vois & anObj,cElXMLTree * aTree);


        std::string & Name();
        const std::string & Name()const ;

        double & Angle();
        const double & Angle()const ;

        double & Nb();
        const double & Nb()const ;
    private:
        std::string mName;
        double mAngle;
        double mNb;
};
cElXMLTree * ToXMLTree(const cISOM_Vois &);

class cISOM_AllVois
{
    public:
        friend void xml_init(cISOM_AllVois & anObj,cElXMLTree * aTree);


        std::list< cISOM_Vois > & ISOM_Vois();
        const std::list< cISOM_Vois > & ISOM_Vois()const ;
    private:
        std::list< cISOM_Vois > mISOM_Vois;
};
cElXMLTree * ToXMLTree(const cISOM_AllVois &);

/******************************************************/
/******************************************************/
/******************************************************/
class cImSecOfMaster
{
    public:
        friend void xml_init(cImSecOfMaster & anObj,cElXMLTree * aTree);


        std::string & Master();
        const std::string & Master()const ;

        std::list< cOneSolImageSec > & Sols();
        const std::list< cOneSolImageSec > & Sols()const ;

        cTplValGesInit< cISOM_AllVois > & ISOM_AllVois();
        const cTplValGesInit< cISOM_AllVois > & ISOM_AllVois()const ;
    private:
        std::string mMaster;
        std::list< cOneSolImageSec > mSols;
        cTplValGesInit< cISOM_AllVois > mISOM_AllVois;
};
cElXMLTree * ToXMLTree(const cImSecOfMaster &);

/******************************************************/
/******************************************************/
/******************************************************/
class cXmlExivEntry
{
    public:
        friend void xml_init(cXmlExivEntry & anObj,cElXMLTree * aTree);


        std::list< std::string > & Names();
        const std::list< std::string > & Names()const ;

        double & Focale();
        const double & Focale()const ;
    private:
        std::list< std::string > mNames;
        double mFocale;
};
cElXMLTree * ToXMLTree(const cXmlExivEntry &);

/******************************************************/
/******************************************************/
/******************************************************/
class cXmlDataBase
{
    public:
        friend void xml_init(cXmlDataBase & anObj,cElXMLTree * aTree);


        int & MajNumVers();
        const int & MajNumVers()const ;

        int & MinNumVers();
        const int & MinNumVers()const ;

        std::list< cXmlExivEntry > & Exiv();
        const std::list< cXmlExivEntry > & Exiv()const ;
    private:
        int mMajNumVers;
        int mMinNumVers;
        std::list< cXmlExivEntry > mExiv;
};
cElXMLTree * ToXMLTree(const cXmlDataBase &);

/******************************************************/
/******************************************************/
/******************************************************/
class cListImByDelta
{
    public:
        friend void xml_init(cListImByDelta & anObj,cElXMLTree * aTree);


        std::string & KeySplitName();
        const std::string & KeySplitName()const ;

        std::list< int > & Delta();
        const std::list< int > & Delta()const ;
    private:
        std::string mKeySplitName;
        std::list< int > mDelta;
};
cElXMLTree * ToXMLTree(const cListImByDelta &);

/******************************************************/
/******************************************************/
/******************************************************/
};
#endif // Define_NotPCP
