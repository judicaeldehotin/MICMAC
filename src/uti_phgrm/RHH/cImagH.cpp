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

#include "StdAfx.h"
#include "ReducHom.h"

NS_RHH_BEGIN


cXmlRHHResLnk  ComputeHomographie
               (
                  const std::string & aName
               )
{
  cXmlRHHResLnk  aRes;

  ElPackHomologue aPack = ElPackHomologue::FromFile(aName);

  double aQual;
  bool   aOk;
  cElHomographie   aHom = cElHomographie::RobustInit(&aQual,aPack,aOk,NB_RANSAC_H,90.0,1000);

  if (aOk)
     aRes.HomToIm() = aHom.ToXml();


  return aRes;
}

int Comput_HomMain(int argc,char ** argv)
{

   std::string aNameHom,aNameCal;
   std::string toto;

    ElInitArgMain
    (
         argc,argv,
         LArgMain()  << EAMC(aNameHom,"Hom points")
                     << EAMC(aNameCal,"Calib "),
         LArgMain()  << EAM(toto,"toto",true)
   );

   return 1;
}





/*************************************************/
/*                                               */
/*                cLink2Img                      */
/*                                               */
/*************************************************/

cLink2Img::cLink2Img(cImagH * aSrce,cImagH * aDest,const std::string & aNameH) :
   mNbPts      (0),
   mNbPtsAttr  (0),
   mSrce       (aSrce),
   mDest       (aDest),
   mAppli      (mSrce->Appli()),
   mNameH      (aNameH),
   mQualHom    (0),
   mHom12      (cElHomographie::Id()),
   mPckLoaded  (false),
   mHomLoaded  (false),
   mOkHom      (false)
{
}


void  cLink2Img::LoadHomographie(bool ExigOk)
{
     LoadPack();
     if (!mHomLoaded) 
     {
        mHomLoaded = true;
        if (NbPts() >=  mAppli.MinNbPtH())
        {
            mHom12 = cElHomographie::RobustInit(&mQualHom,mPack,mOkHom,NB_RANSAC_H,90.0,1000);
        }
     }
       
     if (ExigOk)
     {
         ELISE_ASSERT(mOkHom,"Cannot get Hom12 : mOkHom=false");
     }
}

void  cLink2Img::LoadHomographie(bool ExigOk) const
{
   const_cast<cLink2Img*>(this)->LoadHomographie(ExigOk);
}

void cLink2Img::LoadPack()
{
   if (mPckLoaded)
      return;
   mPckLoaded = true;
   mPack = ElPackHomologue::FromFile(mSrce->Appli().Dir()+mNameH);
   mNbPts =  mPack.size();

   std::vector<Pt2dr>  aVP2;
   for
   (
       ElPackHomologue::const_iterator itP=mPack.begin();
       itP != mPack.end();
       itP++
   )
   {
       Pt2dr aP1 = itP->P1();
       aVP2.push_back(aP1);
       // mEchantP1.push_back(Pt3dr(aP1.x,aP1.y,1.0));
   }

   Pt2di aSz (3,3);
   if (aVP2.size() > 100)
      aSz = Pt2di(4,4);
   if (aVP2.size() > 500)
      aSz = Pt2di(5,5);
   if (aVP2.size() > 2000)
      aSz = Pt2di(6,6);

   mEchantP1 = GetDistribRepresentative(mCdg1,aVP2,aSz);

}

void  cLink2Img::LoadPack() const
{
   const_cast<cLink2Img*>(this)->LoadPack();
}


const ElPackHomologue & cLink2Img::Pack() const
{
   LoadPack();
   return mPack;
}


// Compute the quality of the "closing" relation
//     mDest->Hi2t() * mHom12 = mSrce->Hi2t()
//     This quality is estimated on the weighted set mEchantP1


double cLink2Img::CoherenceH()
{
    LoadPack();

    cElHomographie aI2T_A = CalcSrceFromDest();
    cElHomographie aI2T_B = mSrce->Hi2t();

    double aSomP=0;
    double aSomDist=0;

    for (int aKP=0 ; aKP < int(mEchantP1.size()) ; aKP++)
    {
         Pt3dr aP3(mEchantP1[aKP]);
         double aPds (aP3.z);
         Pt2dr aP1 (aP3.x,aP3.y);

         Pt2dr aPA = aI2T_A.Direct(aP1);
         Pt2dr aPB = aI2T_B.Direct(aP1);
         double aDist = square_euclid(aPA-aPB);

         aSomP += aPds;
         aSomDist  += aDist * aPds;
    }

    return sqrt(aSomDist/aSomP);
}



cImagH * cLink2Img::Srce() const
{
   return mSrce;
}
cImagH * cLink2Img::Dest() const
{
   return mDest;
}

const std::string &  cLink2Img::NameH() const
{
    return mNameH;
}


const int   &  cLink2Img::NbPts() const
{
    LoadPack();
    return mNbPts;
}

/*
int   &  cLink2Img::NbPtsAttr()
{
    return mNbPtsAttr;
}
*/

const bool & cLink2Img::OkHom() const
{
   LoadHomographie(false);
   return mOkHom;
}


const double & cLink2Img::QualHom() const
{
   LoadHomographie(true);
   return mQualHom;
}

const cElHomographie &  cLink2Img::Hom12() const
{
    LoadHomographie(true);
    return mHom12;
}

cElHomographie cLink2Img::CalcSrceFromDest ()
{
    // return mHom12 * mSrce->Ht2i(); A CHANGER
    return mDest->Hi2t() * Hom12();
}

const std::vector<Pt3dr> & cLink2Img::EchantP1() const
{
    LoadPack();
    return mEchantP1;
}


cEqHomogFormelle * &  cLink2Img::EqHF()
{
    return mEqHF;
}


/*************************************************/
/*                                               */
/*                 cImagH                        */
/*                                               */
/*************************************************/


cImagH::cImagH(const std::string & aName,cAppliReduc & anAppli,int aNum) :
   mName     (aName),
   mAppli    (anAppli),
   mNum      (aNum),
   mNumTmp   (-1),
   mSomQual  (0),
   mSomNbPts (0),
   mHi2t     (cElHomographie::Id()),
   mHTmp     (cElHomographie::Id())
{
}

   //============ FONCTION DE GRAPHE IMAGE =========================

cLink2Img * cImagH::GetLinkOfImage(cImagH* anI2)
{
   tMapName2Link::iterator anIt = mLnks.find(anI2);
   if (anIt==mLnks.end())
      return 0;
   return anIt->second;
}


void cImagH::AddLink(cImagH * anI2,const std::string & aNameH)
{
      mLnks[anI2] = new cLink2Img(this,anI2,aNameH);
}

void cImagH::SetMarqued(int aK)
{
   mMarques.set_kth_true(aK);
}
void cImagH::SetUnMarqued(int aK)
{
   mMarques.set_kth_false(aK);
}
bool cImagH::Marqued(int aK) const
{
   return mMarques.kth(aK);
}

cElHomographie &   cImagH::Hi2t()
{
   return mHi2t;
}

cElHomographie &   cImagH::HTmp()
{
   return mHTmp;
}



   //============ FUSION DE POINT =========================

const std::string & cImagH::Name() const
{
  return mName;
}

void cImagH::AddOnePtToExistingH(cPtHom * aH1,const Pt2dr & aP1,cImagH * aI2,const Pt2dr & aP2)
{
    aH1->AddMesureInImage(aI2,aP2);
    // aI2->mMapH[aP2] = aH1;
}


void  cImagH::FusionneIn(cPtHom *aH1,const Pt2dr & aP1,cImagH *aI2,cPtHom *aH2,const Pt2dr & aP2)
{

   aH1->OkAbsorb(aH2);
   // aI2->mMapH[aP2] = aH1;
   // if
}

void  cImagH::SetPHom(const Pt2dr & aP,cPtHom * aH)
{
   mMapH[aP] = aH;
}

void cImagH::AddOnePair(const Pt2dr & aP1,cImagH * aI2,const Pt2dr & aP2)
{
    std::map<Pt2dr,cPtHom *>::iterator it1 = mMapH.find(aP1);
    std::map<Pt2dr,cPtHom *>::iterator it2 = aI2->mMapH.find(aP2);

    if ((it1==  mMapH.end()) && (it2==  aI2->mMapH.end()))
    {
        cPtHom * aH = cPtHom::NewGerm(this,aP1,aI2,aP2);
        mMapH[aP1] = aH;
        aI2->mMapH[aP2] = aH;
    }
    else if ((it1!= mMapH.end()) && (it2==  aI2->mMapH.end()))
    {
       it1->second->AddMesureInImage(aI2,aP2);
       // AddOnePtToExistingH(it1->second,aP1,aI2,aP2);
    }
    else if ((it1 == mMapH.end()) && (it2!=aI2->mMapH.end()))
    {
       it2->second->AddMesureInImage(this,aP1);
       // aI2->AddOnePtToExistingH(it2->second,aP2,this,aP1);
    }
    else if (it1->second==it2->second)
    {
         it1->second->IncrCptArc();
    }
    else
    {
         if (it1->second->NbIm() >= it2->second->NbIm())
            FusionneIn(it1->second,aP1,aI2,it2->second,aP2);
         else
            aI2->FusionneIn(it2->second,aP2,this,it1->second,aP1);
    }
}



void  cImagH::ComputePtsLink(cLink2Img & aLnk)
{
    const ElPackHomologue & aPack = aLnk.Pack();

    // std::cout << "    LNK " << aLnk.NameH() << "  " << aPack.size() << "\n";
    for
    (
       ElPackHomologue::const_iterator itP=aPack.begin();
       itP != aPack.end();
       itP++
    )
    {
        //  std::cout << itP->P1() << " " << itP->P2() << "\n";
         AddOnePair(itP->P1(),aLnk.Dest(),itP->P2());
    }
}


void cImagH::ComputePts()
{
    std::cout << "Compute " << mName << "\n";


    //  D'abod on complete avec les arcs
    for ( tMapName2Link::iterator itL=mLnks.begin(); itL!=mLnks.end(); itL++)
    {
        ComputePtsLink(*(itL->second));
    }
}


cHomogFormelle *  & cImagH::HF()
{
   return mHF;
}

cAppliReduc &     cImagH::Appli()
{
   return mAppli;
}

const tMapName2Link & cImagH::Lnks() const
{
   return mLnks;
}

NS_RHH_END

/*Footer-MicMac-eLiSe-25/06/2007

Ce logiciel est un programme informatique servant � la mise en
correspondances d'images pour la reconstruction du relief.

Ce logiciel est r�gi par la licence CeCILL-B soumise au droit fran�ais et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL-B telle que diffus�e par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".

En contrepartie de l'accessibilit� au code source et des droits de copie,
de modification et de redistribution accord�s par cette licence, il n'est
offert aux utilisateurs qu'une garantie limit�e.  Pour les m�mes raisons,
seule une responsabilit� restreinte p�se sur l'auteur du programme,  le
titulaire des droits patrimoniaux et les conc�dants successifs.

A cet �gard  l'attention de l'utilisateur est attir�e sur les risques
associ�s au chargement,  � l'utilisation,  � la modification et/ou au
d�veloppement et � la reproduction du logiciel par l'utilisateur �tant
donn� sa sp�cificit� de logiciel libre, qui peut le rendre complexe �
manipuler et qui le r�serve donc � des d�veloppeurs et des professionnels
avertis poss�dant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invit�s � charger  et  tester  l'ad�quation  du
logiciel � leurs besoins dans des conditions permettant d'assurer la
s�curit� de leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement,
� l'utiliser et l'exploiter dans les m�mes conditions de s�curit�.

Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez
pris connaissance de la licence CeCILL-B, et que vous en avez accept� les
termes.
Footer-MicMac-eLiSe-25/06/2007*/
