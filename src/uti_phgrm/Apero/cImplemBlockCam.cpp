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

/*     ==== MODELISATION MATHEMATIQUE-1 ====================
  
   Pour les notations on reprend la terminologie LR (Left-Right) et Time (date de prise de vue)

      Block Inc :
          LinkL  LinkR ...

      Pour un bloc a N Camera, il y a N rotation inconnue (donc une de plus que necessaire) qui lie la camera a
   un systeme de reference; en pratique le systeme de reference  se trouve etre de la "premiere" camera (c'est ce qui
   est fait lors de l'estimation. c'est ce qui est maintenu pour lever l'arbitraire des equations, mais a part cela
   la "premiere" camera ne joue aucun role particulier);

      Les valeurs stockees dans LinkL (t.q. stockees dans LiaisonsSHC, voir cImplemBlockCam.cpp  CONV-ORI)

          LinkL =   L  -> Ref
          LinkR =   R  -> Ref

      Time i : CamLi  CamRi   ...  ;  CamLi : Li  -> Monde
      Time j : CamLj  CamRj   ...
      Time k : CamLk  CamRk   ...


       Les equation sont du type :

          L to R =      CamRi-1  CamLi   =   CamRk -1 CamLk , qqs k,i (et L,R)

     On ecrit cela 
 
             CamRi-1  CamLi = LinkR-1 LinkL  ,  qqs i, L , R  (Eq1) 

*/

/*
     Soit L = (Tl,Wl)  avec TL matrice rotation et Tl centre de projection   L(P) = Wl* P + Tl
     Et R-1 (P) = Wr-1*P - Wr-1 * Tr = tWr * P - Tr  ;   R-1 = (Wr-1,- Wr-1* P)
    

      CamRi-1  CamLi  = (Wr-1,- Wr-1* Pr) X (Wl,Pl) = (Wr-1*Wl,- Wr-1* Pr +  Wr-1* Pl)
*/




namespace NS_ParamApero
{

class cIBC_ImsOneTime;
class cIBC_OneCam;
class cImplemBlockCam;

class cEqBlockCamera;

/***********************************************************/
/*                                                         */
/*                                                         */
/*                                                         */
/***********************************************************/

cTypeCodageMatr ExportMatr(const ElMatrix<double> & aMat)
{
    cTypeCodageMatr  aCM;

    aMat.GetLig(0, aCM.L1() );
    aMat.GetLig(1, aCM.L2() );
    aMat.GetLig(2, aCM.L3() );
    aCM.TrueRot().SetVal(true);

    return aCM;
}

ElMatrix<double> ImportMat(const cTypeCodageMatr & aCM)
{
   ElMatrix<double> aMat(3,3);

   SetLig(aMat,0,aCM.L1());
   SetLig(aMat,1,aCM.L2());
   SetLig(aMat,2,aCM.L3());

   return aMat;
}

/***********************************************************/
/*                                                         */
/*                      cEqBlockCamera                     */
/*                                                         */
/***********************************************************/


void RotationRel(Pt3d<Fonc_Num> & aC,ElMatrix<Fonc_Num> & aMat, cRotationFormelle & aRR,int aKFR,cRotationFormelle & aRL,int aKFL)
{

    ElMatrix<Fonc_Num> aMatRInv = aRR.MatFGLComplete(aKFR);
    aMatRInv.self_transpose();

    ElMatrix<Fonc_Num> aMatL =  aRL.MatFGLComplete(aKFL);
    aMat = aMatRInv * aMatL;
    aC = aMatRInv * (aRL.COpt() - aRR.COpt());
}

class cEqBlockCamera : public cNameSpaceEqF,
                       public cObjFormel2Destroy

{
     public :
           cEqBlockCamera();
           void SetOrients
                (
                    cRotationFormelle * aRotL1,
                    cRotationFormelle * aRotR1,
                    cRotationFormelle * aRotL2,
                    cRotationFormelle * aRotR2
                );

            void GenCode();

             void InitEqCompiledResidu();

     private  :
          static std::string mNameType;
          cSetEqFormelles *   mSet;
          cRotationFormelle * mRotL1;
          cRotationFormelle * mRotR1;
          cRotationFormelle * mRotL2;
          cRotationFormelle * mRotR2;
          cIncListInterv      mLInterv;
          cElCompiledFonc *   mEqResidu;
};


cEqBlockCamera::cEqBlockCamera()  :
    mSet (0),
    mRotL1 (0),
    mRotR1 (0),
    mRotL2 (0),
    mRotR2 (0),
    mEqResidu (0)
{
}

std::string cEqBlockCamera::mNameType = "cEqRigiditeBlock";

void  cEqBlockCamera::SetOrients
      (
         cRotationFormelle * aRotL1,
         cRotationFormelle * aRotR1,
         cRotationFormelle * aRotL2,
         cRotationFormelle * aRotR2
      )
{
    if (mSet!=0)
    {
       ELISE_ASSERT(mSet==aRotL1->Set(),"Variable set of equation in cEqBlockCamera::SetOrients");
    }
    else
    {
        mSet =  aRotL1->Set();
    }

    mRotL1 = aRotL1;
    mRotR1 = aRotR1;
    mRotL2 = aRotL2;
    mRotR2 = aRotR2;

    ELISE_ASSERT(mSet==aRotL1->Set(),"Variable set of equation in cEqBlockCamera::SetOrients");
    ELISE_ASSERT(mSet==aRotR1->Set(),"Variable set of equation in cEqBlockCamera::SetOrients");
    ELISE_ASSERT(mSet==aRotL2->Set(),"Variable set of equation in cEqBlockCamera::SetOrients");
    ELISE_ASSERT(mSet==aRotR2->Set(),"Variable set of equation in cEqBlockCamera::SetOrients");
   

    mRotL1->IncInterv().SetName("OriL1");
    mRotR1->IncInterv().SetName("OriR1");
    mRotL2->IncInterv().SetName("OriL2");
    mRotR2->IncInterv().SetName("OriR2");

    mLInterv.Init();
    mLInterv.AddInterv(mRotL1->IncInterv());
    mLInterv.AddInterv(mRotR1->IncInterv());
    mLInterv.AddInterv(mRotL2->IncInterv());
    mLInterv.AddInterv(mRotR2->IncInterv());
}

void cEqBlockCamera::GenCode()
{

    Pt3d<Fonc_Num> aC1;
    ElMatrix<Fonc_Num>  aM1(3,3);
    RotationRel(aC1,aM1,*mRotR1,1,*mRotL1,0);


    Pt3d<Fonc_Num> aC2;
    ElMatrix<Fonc_Num>  aM2(3,3);
    RotationRel(aC2,aM2,*mRotR2,3,*mRotL2,2);


    Pt3d<Fonc_Num> aC12 = aC2 - aC1;
    ElMatrix<Fonc_Num> aM12 = aM2 - aM1;
    std::vector<Fonc_Num> aV;

    aV.push_back(aC12.x);
    aV.push_back(aC12.y);
    aV.push_back(aC12.z);

    for (int aKy=0; aKy<3; aKy++)
    {
       for (int aKx=0; aKx<3; aKx++)
       {
           aV.push_back(aM12(aKx,aKy));
       }
    }
    cElCompileFN::DoEverything
    (
         "CodeGenere/photogram/",  // Directory ou est localise le code genere
         mNameType,  // donne les noms de fichier .cpp et .h ainsi que les nom de classe
         aV,  // expressions formelles 
         mLInterv  // intervalle de reference
    );

}

void cEqBlockCamera::InitEqCompiledResidu()
{
    mEqResidu = cElCompiledFonc::AllocFromName(mNameType);

    ELISE_ASSERT(mEqResidu!=0,"cEqBlockCamera::InitEqCompiledResidu");
}

/***********************************************************/
/*                                                         */
/*                                                         */
/*                                                         */
/***********************************************************/




class cIBC_ImsOneTime
{
    public :
        cIBC_ImsOneTime(int aNbCam,int aNum,const std::string& aNameTime) ;
        void  AddPose(cPoseCam *, int aNum);
        cPoseCam * Pose(int aKP);

    private :

        std::vector<cPoseCam *> mCams;
        int                     mNum;
        std::string             mNameTime;
};


class cIBC_OneCam
{
      public :
          cIBC_OneCam(const std::string & ,int aNum);
          const int & Num() const;
          const std::string & NameCam() const;
          const bool & V0Init() const;
          void Init0(const cParamOrientSHC & aPSH);
      private :
          std::string mNameCam;
          int         mNum;
          Pt3dr             mC0;
          ElMatrix<double>  mMat0;
          bool              mV0Init;
};



class cImplemBlockCam
{
    public :
         // static cImplemBlockCam * AllocNew(cAppliApero &,const cStructBlockCam,const std::string & anId);
         cImplemBlockCam(cAppliApero & anAppli,const cStructBlockCam,const std::string & anId );

         void EstimCurOri(const cEstimateOrientationInitBlockCamera &);
         void Export(const cExportBlockCamera &);

         void InitForCompens();
    private :

         cAppliApero &               mAppli;
         cStructBlockCam             mSBC;
         cLiaisonsSHC *              mLSHC;
         cStructBlockCam             mEstimSBC;
         std::string                 mId;

         std::map<std::string,cIBC_OneCam *>   mName2Cam;
         std::vector<cIBC_OneCam *>            mNum2Cam;
         int                                   mNbCam;
         int                                   mNbTime;

         std::map<std::string,cIBC_ImsOneTime *> mName2ITime;
         std::vector<cIBC_ImsOneTime *>          mNum2ITime;
         bool                                    mDoneIFC;
         cEqBlockCamera *                        mEBC;
};

    // =================================
    //              cIBC_ImsOneTime
    // =================================

cIBC_ImsOneTime::cIBC_ImsOneTime(int aNb,int aNum,const std::string & aNameTime) :
       mCams     (aNb),
       mNum      (aNum),
       mNameTime (aNameTime)
{
}

void  cIBC_ImsOneTime::AddPose(cPoseCam * aPC, int aNum) 
{
    cPoseCam * aPC0 =  mCams.at(aNum);
    if (aPC0 != 0)
    {
         std::cout <<  "For cameras " << aPC->Name() <<  "  and  " << aPC0->Name() << "\n";
         ELISE_ASSERT(false,"Conflicting name from KeyIm2TimeCam ");
    }
    
    mCams[aNum] = aPC;
}

cPoseCam * cIBC_ImsOneTime::Pose(int aKP)
{
   return mCams.at(aKP);
}
    // =================================
    //              cIBC_OneCam 
    // =================================

cIBC_OneCam::cIBC_OneCam(const std::string & aNameCam ,int aNum) :
    mNameCam (aNameCam ),
    mNum     (aNum),
    mMat0    (1,1),
    mV0Init  (false)
{
}

const int & cIBC_OneCam::Num() const {return mNum;}
const std::string & cIBC_OneCam::NameCam() const { return mNameCam; }
const bool & cIBC_OneCam::V0Init() const {return mV0Init;}

void cIBC_OneCam::Init0(const cParamOrientSHC & aPOS)
{
    mV0Init = true;
    mC0   = aPOS.Vecteur();
    mMat0 = ImportMat(aPOS.Rot());
    
}


    // =================================
    //       cImplemBlockCam
    // =================================

cImplemBlockCam::cImplemBlockCam(cAppliApero & anAppli,const cStructBlockCam aSBC,const std::string & anId) :
      mAppli      (anAppli),
      mSBC        (aSBC),
      mEstimSBC   (aSBC),
      mId         (anId),
      mDoneIFC    (false),
      mEBC        (0)
{
    const std::vector<cPoseCam*> & aVP = mAppli.VecAllPose();
   

    // On initialise les camera
    for (int aKP=0 ; aKP<int(aVP.size()) ; aKP++)
    {
          cPoseCam * aPC = aVP[aKP];
          std::string aNamePose = aPC->Name();
          std::pair<std::string,std::string> aPair =   mAppli.ICNM()->Assoc2To1(mSBC.KeyIm2TimeCam(),aNamePose,true);
          std::string aNameCam = aPair.second;
          if (! DicBoolFind(mName2Cam,aNameCam))
          {

               cIBC_OneCam *  aCam = new cIBC_OneCam(aNameCam,mNum2Cam.size());
               mName2Cam[aNameCam] = aCam;
               mNum2Cam.push_back(aCam); 
          }
    }
    mNbCam  = mNum2Cam.size();

    
    // On regroupe les images prises au meme temps
    for (int aKP=0 ; aKP<int(aVP.size()) ; aKP++)
    {
          cPoseCam * aPC = aVP[aKP];
          std::string aNamePose = aPC->Name();
          std::pair<std::string,std::string> aPair =   mAppli.ICNM()->Assoc2To1(mSBC.KeyIm2TimeCam(),aNamePose,true);
          std::string aNameTime = aPair.first;
          std::string aNameCam  = aPair.second;
          
          cIBC_ImsOneTime * aIms =  mName2ITime[aNameTime];
          if (aIms==0)
          {
               aIms = new cIBC_ImsOneTime(mNbCam,mNum2ITime.size(),aNameTime);
               mName2ITime[aNameTime] = aIms;
               mNum2ITime.push_back(aIms);
          }
          cIBC_OneCam * aCam = mName2Cam[aNameCam];
          aIms->AddPose(aPC,aCam->Num());
    }
    mNbTime = mNum2ITime.size();


    mLSHC = mSBC.LiaisonsSHC().PtrVal();
    if (mLSHC)
    {
       for 
       (
            std::list<cParamOrientSHC>::const_iterator itPOS=mLSHC->ParamOrientSHC().begin();
            itPOS !=mLSHC->ParamOrientSHC().end();
            itPOS++
       )
       {
             cIBC_OneCam * aCam = mName2Cam[itPOS->IdGrp()];
             ELISE_ASSERT(aCam!=0,"Cannot get cam from IdGrp");
             ELISE_ASSERT(! aCam->V0Init(),"Multiple Init For IdGrp");
// LA
             std::cout << "xxxxxxxxxxxxxxxx CCCaaaammm " << aCam << "\n";
       }
    }
}




void cImplemBlockCam::Export(const cExportBlockCamera & aEBC)
{
    MakeFileXML(mEstimSBC,mAppli.ICNM()->Dir()+aEBC.NameFile());
}



void cImplemBlockCam::EstimCurOri(const cEstimateOrientationInitBlockCamera & anEOIB)
{
   cLiaisonsSHC aLSHC;
   for (int aKC=0 ; aKC<mNbCam ; aKC++)
   {
       if (anEOIB.Show().Val())
          std::cout << "=================================================\n";
       Pt3dr aSomTr(0,0,0);
       double aSomP=0;
       ElMatrix<double> aSomM(3,3,0.0);
       for (int aKT=0 ; aKT<mNbTime ; aKT++)
       {
            cIBC_ImsOneTime *  aTime =  mNum2ITime[aKT];
            cPoseCam * aP0 = aTime->Pose(0);
            cPoseCam * aP1 = aTime->Pose(aKC);
            if (aP0 && aP1)
            {
                ElRotation3D  aR0toM = aP0->CurCam()->Orient().inv(); // CONV-ORI
                ElRotation3D  aR1toM = aP1->CurCam()->Orient().inv();

                ElRotation3D aR1to0 = aR0toM.inv() * aR1toM;  //  CONV-ORI

                if (anEOIB.Show().Val())
                {
                    std::cout << "  EstimCurOri " << aP0->Name() <<  " " << aP1->Name() << "\n";
                    std::cout << "    " <<  aR1to0.ImAff(Pt3dr(0,0,0)) 
                                      << " " << aR1to0.teta01() 
                                      << " " << aR1to0.teta02() 
                                      << " " << aR1to0.teta12() 
                                      << "\n";
                }
                aSomTr = aSomTr+ aR1to0.tr();
                aSomM += aR1to0.Mat();
                aSomP++;
            }
       }
       if (aSomP)
       {
           aSomTr = aSomTr / aSomP;
           aSomM *=  1.0/aSomP;
           aSomM = NearestRotation(aSomM);
           ElRotation3D aRMoy(aSomTr,aSomM,true);
           std::cout << "  ==========  AVERAGE =========== \n";
           std::cout << "    " <<  aRMoy.ImAff(Pt3dr(0,0,0))
                               << " " << aRMoy.teta01() 
                               << " " << aRMoy.teta02() 
                               << " " << aRMoy.teta12() 
                               << "\n";

           cParamOrientSHC aP;
           aP.IdGrp() = mNum2Cam[aKC]->NameCam();
           aP.Vecteur() = aRMoy.ImAff(Pt3dr(0,0,0));
           aP.Rot() = ExportMatr(aSomM);
           aLSHC.ParamOrientSHC().push_back(aP);
       }
   }
   
   mEstimSBC.LiaisonsSHC().SetVal(aLSHC);
}


void cImplemBlockCam::InitForCompens()
{
   if (mDoneIFC) return;
   mDoneIFC = true;

   ELISE_ASSERT(mLSHC!=0,"ObsBlockCamRig no LiaisonsSHC");

   mEBC = new cEqBlockCamera;
   mEBC->InitEqCompiledResidu();
}

    // =================================
    //       cAppliApero
    // =================================

void cAppliApero::InitBlockCameras()
{
  for 
  (
        std::list<cBlockCamera>::const_iterator itB= mParam.BlockCamera().begin();
        itB!=mParam.BlockCamera().end();
        itB++
  )
  {
       std::string anId = itB->Id().ValWithDef(itB->NameFile());
       cStructBlockCam aSB = StdGetObjFromFile<cStructBlockCam>
                             (
                                 mICNM->Dir() + itB->NameFile(),
                                 StdGetFileXMLSpec("ParamChantierPhotogram.xml"),
                                 "StructBlockCam",
                                 "StructBlockCam"
                             );
       cImplemBlockCam * aIBC = new cImplemBlockCam(*this,aSB,anId);
       mBlockCams[anId] = aIBC;
  }


  const cSectionCompensation & aSC  = mParam.SectionCompensation();
  for 
  (
     std::list<cEtapeCompensation>::const_iterator itSC = aSC.EtapeCompensation().begin();
     itSC != aSC.EtapeCompensation().end();
     itSC++
  )
  {
     const cSectionObservations & aSO = itSC->SectionObservations();
     for 
     ( 
         std::list<cObsBlockCamRig>::const_iterator itCOB = aSO.ObsBlockCamRig().begin();
         itCOB != aSO.ObsBlockCamRig().end();
         itCOB++
     )
     {
         cImplemBlockCam *  aIBC = GetBlockCam(itCOB->Id());
         aIBC->InitForCompens();
     }
  }
}


cImplemBlockCam * cAppliApero::GetBlockCam(const std::string & anId)
{
   cImplemBlockCam* aRes = mBlockCams[anId];
   ELISE_ASSERT(aRes!=0,"cAppliApero::GetBlockCam");

   return aRes;
}

void  cAppliApero::EstimateOIBC(const cEstimateOrientationInitBlockCamera & anEOIB)
{ 
    cImplemBlockCam * aBlock = GetBlockCam(anEOIB.Id());
    aBlock->EstimCurOri(anEOIB);
}


void cAppliApero:: ExportBlockCam(const cExportBlockCamera & aEBC)
{
    cImplemBlockCam * aBlock = GetBlockCam(aEBC.Id());
    aBlock->Export(aEBC);
}


};


using namespace NS_ParamApero;

void GenCodeRigiditeBlock()
{
   cSetEqFormelles aSet;
   ElRotation3D aR0(Pt3dr(0,0,0),0,0,0);

   cRotationFormelle * aRF1L = aSet.NewRotation(cNameSpaceEqF::eRotLibre,aR0);
   cRotationFormelle * aRF1R = aSet.NewRotation(cNameSpaceEqF::eRotLibre,aR0);
   cRotationFormelle * aRF2L = aSet.NewRotation(cNameSpaceEqF::eRotLibre,aR0);
   cRotationFormelle * aRF2R = aSet.NewRotation(cNameSpaceEqF::eRotLibre,aR0);

   cEqBlockCamera aBlock;
   aBlock.SetOrients(aRF1L,aRF1R,aRF2L,aRF2R);
   aBlock.GenCode();
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
