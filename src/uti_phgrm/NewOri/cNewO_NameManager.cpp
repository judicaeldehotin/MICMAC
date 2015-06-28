/*Header-MicMac-eLiSe-25/06/2007

    MicMac : Multi Image Correspondances par Methodes Automatiques de Correlation
    eLiSe  : ELements of an Image Software Environnement

    www.micmac.ign.fr

   
    Copyright : Institut Geographique National
    Author : Marc Pierrot Deseilligny
    Contributors : Gregoire Maillet, Didier Boldo.

[1] M. Pierrot-Deseilligny, N. Paparoditis.
    "A multiresolution and optimization-based image matching approach:
    An application to surface reconstruction from SPOT5-HRS stereo imagery."
    In IAPRS vol XXXVI-1/W41 in ISPRS Workshop On Topographic Mapping From Space
    (With Special Emphasis on Small Satellites), Ankara, Turquie, 02-2006.

[2] M. Pierrot-Deseilligny, "MicMac, un lociel de mise en correspondance
    d'images, adapte au contexte geograhique" to appears in 
    Bulletin d'information de l'Institut Geographique National, 2007.

Francais :

   MicMac est un logiciel de mise en correspondance d'image adapte 
   au contexte de recherche en information geographique. Il s'appuie sur
   la bibliotheque de manipulation d'image eLiSe. Il est distibue sous la
   licences Cecill-B.  Voir en bas de fichier et  http://www.cecill.info.


English :

    MicMac is an open source software specialized in image matching
    for research in geographic information. MicMac is built on the
    eLiSe image library. MicMac is governed by the  "Cecill-B licence".
    See below and http://www.cecill.info.

Header-MicMac-eLiSe-25/06/2007*/

#include "NewOri.h"


const std::string  cNewO_NameManager::PrefixDirTmp = "NewOriTmp";


cNewO_NameManager::cNewO_NameManager
(
     bool                 Quick,
     const std::string  & aDir,
     const std::string  & anOriCal,
     const std::string  & aPostHom
) :
    mICNM        (cInterfChantierNameManipulateur::BasicAlloc(aDir)),
    mDir         (aDir),
    mPrefOriCal  (anOriCal),
    mPostHom     (aPostHom),
    mQuick       (Quick)
{
   StdCorrecNameOrient(mPrefOriCal,mDir);
   mPostfixDir    =   mPrefOriCal + std::string(mQuick ? "Quick" : "Std");
   mDirTmp      =   std::string(PrefixDirTmp) + mPostfixDir + "/";
}

const std::string & cNewO_NameManager::Dir() const
{
   return mDir;
}


std::string cNewO_NameManager::KeySetCpleOri() const
{
   return "NKS-Set-NewOri-CplIm2OriRel@"+mPostfixDir +"@dmp";
}

std::string cNewO_NameManager::KeyAssocCpleOri() const
{
   return "NKS-Assoc-NewOri-CplIm2OriRel@"+mPostfixDir +"@dmp";
}




ElPackHomologue cNewO_NameManager::PackOfName(const std::string & aN1,const std::string & aN2) const
{
    std::string aNameH = mICNM->Assoc1To2("NKS-Assoc-CplIm2Hom@@"+mPostHom,aN1,aN2,true);
    if (!  ELISE_fp::exist_file(aNameH))
       return ElPackHomologue();

    return ElPackHomologue::FromFile(aNameH);
}

cInterfChantierNameManipulateur *  cNewO_NameManager::ICNM()
{
   return mICNM;
}


CamStenope * cNewO_NameManager::CamOfName(const std::string  & aName) 
{

   cMetaDataPhoto aMTD = cMetaDataPhoto::CreateExiv2(mDir+aName);

   if (mPrefOriCal =="")
   {
        std::vector<double> aPAF;
        double aFPix  = aMTD.FocPix();
        Pt2di  aSzIm  = aMTD.XifSzIm();
        Pt2dr  aPP = Pt2dr(aSzIm) / 2.0;

        bool IsFE;
        FromString(IsFE,mICNM->Assoc1To1("NKS-IsFishEye",aName,true));
        std::string aNameCal = "CamF" + ToString(aFPix) +"_Sz"+ToString(aSzIm) + "FE"+ToString(IsFE);
        if (DicBoolFind(mDicoCam,aNameCal))
           return mDicoCam[aNameCal];
        CamStenope * aRes = 0;

        if (IsFE)
        {
            std::vector<double> aVP;
            std::vector<double> aVE;
            aVE.push_back(aFPix);
            aVP.push_back(aPP.x);
            aVP.push_back(aPP.y);
            aRes = new cCamLin_FishEye_10_5_5
                       (
                            false,
                            aFPix,aPP,Pt2dr(aSzIm),
                            aPAF,
                            &aVP,
                            &aVE
                       );

        }
        else
        {
             aRes = new CamStenopeIdeale(false,aFPix,aPP,aPAF);
        }
        aRes->SetSz(aSzIm);
        mDicoCam[aNameCal] =  aRes;
        return aRes;
   }


   std::string  aNC = mICNM->StdNameCalib(mPrefOriCal,aName);

   if (DicBoolFind(mDicoCam,aNC))
      return mDicoCam[aNC];

   mDicoCam[aNC] =  CamOrientGenFromFile(aNC,mICNM);

   return mDicoCam[aNC];
}
/*
*/
CamStenope *  cInterfChantierNameManipulateur::StdCamOfNames(const std::string & aNameIm,const std::string & anOri)
{

     std::string aKey = "NKS-Assoc-Im2Orient@-"+ anOri ;
     std::string aNameCam =  Assoc1To1(aKey,aNameIm,true);
     return CamOrientGenFromFile(aNameCam,this);
}

CamStenope * cNewO_NameManager::CamOriOfName(const std::string & aNameIm,const std::string & anOri)
{
    return mICNM->StdCamOfNames(aNameIm,anOri);
/*
     std::string aKey = "NKS-Assoc-Im2Orient@-"+ anOri ;
     std::string aNameCam =  mICNM->Assoc1To1(aKey,aNameIm,true);
     return CamOrientGenFromFile(aNameCam,mICNM);
*/
}
const std::string &   cNewO_NameManager::OriCal() const {return mPrefOriCal;}



std::string cNewO_NameManager::NameXmlOri2Im(cNewO_OneIm* aI1,cNewO_OneIm* aI2,bool Bin) const
{
    return NameXmlOri2Im(aI1->Name(),aI2->Name(),Bin);
}

std::string cNewO_NameManager::NameXmlOri2Im(const std::string & aN1,const std::string & aN2,bool Bin) const
{
    return Dir3POneImage(aN1,true) + "OriRel-" + aN2 +  (Bin ? ".dmp" : ".xml");
}
/*
*/



/*
*/

std::string cNewO_NameManager::NameTimingOri2Im() const
{
    return  Dir3P(true)  + "Timing2Im.xml";
}

cXml_Ori2Im cNewO_NameManager::GetOri2Im(const std::string & aN1,const std::string & aN2)
{
   return StdGetFromSI(mDir + NameXmlOri2Im(aN1,aN2,true),Xml_Ori2Im);
}


/************************  TRIPLETS *****************/

std::string  cNewO_NameManager::Dir3P(bool WithMakeDir) const
{
    std::string aRes = mDir + mDirTmp ;
    if (WithMakeDir)  ELISE_fp::MkDir(aRes);
    return aRes;
}

std::string  cNewO_NameManager::Dir3POneImage(const std::string & aName,bool WithMakeDir) const
{
    std::string aRes = Dir3P(WithMakeDir) + aName + "/";
    if (WithMakeDir)  ELISE_fp::MkDir(aRes);
    return aRes;
}

std::string  cNewO_NameManager::Dir3POneImage(cNewO_OneIm * anIm,bool WithMakeDir) const
{
    return Dir3POneImage(anIm->Name(),WithMakeDir);
}




std::string  cNewO_NameManager::Dir3PDeuxImage(cNewO_OneIm * anI1,cNewO_OneIm * anI2,bool WithMakeDir)
{
    std::string aRes = Dir3POneImage(anI1,WithMakeDir) + anI2->Name() + "/";
    if (WithMakeDir)  ELISE_fp::MkDir(aRes);
    return aRes;
}

std::string cNewO_NameManager::NameHomFloat(cNewO_OneIm * anI1,cNewO_OneIm * anI2)
{
   return Dir3PDeuxImage(anI1,anI2,false) + "HomFloatSym"  + ".dat";
}



std::string cNewO_NameManager::NameTripletsOfCple(cNewO_OneIm * anI1,cNewO_OneIm * anI2,bool ModeBin)
{
     return  Dir3PDeuxImage(anI1,anI2,false) + "ImsOfTriplets." + std::string(ModeBin ? "dmp" : "xml");
}


//========================

std::string cNewO_NameManager::NameAttribTriplet
            (
               const std::string & aPrefix,const std::string & aPost,
               cNewO_OneIm * aI1,cNewO_OneIm * aI2,cNewO_OneIm * aI3,
               bool WithMakeDir
            )

{
    ELISE_ASSERT(aI1->Name()<aI2->Name(),"cNO_P3_NameM::NameAttribTriplet");
    ELISE_ASSERT(aI2->Name()<aI3->Name(),"cNO_P3_NameM::NameAttribTriplet");

    std::string aDir = Dir3PDeuxImage(aI1,aI2,WithMakeDir);

    return aDir + "Triplet-" + aPrefix + "-" + aI3->Name() + "." + aPost;
}

std::string cNewO_NameManager::NameHomTriplet(cNewO_OneIm *aI1,cNewO_OneIm *aI2,cNewO_OneIm *aI3,bool WithMakeDir)
{
    return NameAttribTriplet("Hom","dat",aI1,aI2,aI3,WithMakeDir);
}

std::string cNewO_NameManager::NameOriInitTriplet(bool ModeBin,cNewO_OneIm *aI1,cNewO_OneIm *aI2,cNewO_OneIm *aI3,bool WithMakeDir)
{
    return NameAttribTriplet("Ori0",(ModeBin ? "dmp" : "xml"),aI1,aI2,aI3,WithMakeDir);
}

std::string cNewO_NameManager::NameOriOptimTriplet(bool ModeBin,cNewO_OneIm *aI1,cNewO_OneIm *aI2,cNewO_OneIm *aI3,bool WithMakeDir)
{
    return NameAttribTriplet("OriOpt",(ModeBin ? "dmp" : "xml"),aI1,aI2,aI3,WithMakeDir);
}

std::string cNewO_NameManager::NameTopoTriplet(bool aModeBin)
{
    return Dir3P() + "ListeTriplets" + mPrefOriCal +"." + (aModeBin ? "dmp" : "xml");
}

std::string cNewO_NameManager::NameCpleOfTopoTriplet(bool aModeBin)
{
    return Dir3P() + "ListeCpleOfTriplets" + mPrefOriCal +"." + (aModeBin ? "dmp" : "xml");
}



std::string cNewO_NameManager::NameOriGenTriplet(bool Quick,bool ModeBin,cNewO_OneIm *aI1,cNewO_OneIm *aI2,cNewO_OneIm *aI3)
{
   return Quick                                    ?
          NameOriInitTriplet (ModeBin,aI1,aI2,aI3) :
          NameOriOptimTriplet(ModeBin,aI1,aI2,aI3) ;
}





/*Footer-MicMac-eLiSe-25/06/2007

Ce logiciel est un programme informatique servant à la mise en
correspondances d'images pour la reconstruction du relief.

Ce logiciel est régi par la licence CeCILL-B soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL-B telle que diffusée par le CEA, le CNRS et l'INRIA 
sur le site "http://www.cecill.info".

En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme,  le
titulaire des droits patrimoniaux et les concédants successifs.

A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant 
donné sa spécificité de logiciel libre, qui peut le rendre complexe à 
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation  du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement, 
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité. 

Le fait que vous puissiez accéder à cet en-tête signifie que vous avez 
pris connaissance de la licence CeCILL-B, et que vous en avez accepté les
termes.
Footer-MicMac-eLiSe-25/06/2007*/
