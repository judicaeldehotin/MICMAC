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


using namespace NS_SaisiePts;

cAppli_SaisiePts::cAppli_SaisiePts(cResultSubstAndStdGetFile<cParamSaisiePts> aP2) :
     mParam   (*aP2.mObj),
     mICNM    (aP2.mICNM),
     mDC      (aP2.mDC),
     mRefInvis (mParam.RefInvis().Val()),
     mShowDet  (mParam.ShowDet().Val()),
     mWZ       (0),
     mWEnter       (0),
     mSzRech   (100,100),
     mImRechVisu   (mSzRech.x,mSzRech.y),
     mImRechAlgo   (mSzRech.x,mSzRech.y),
     mSzWZ         (mParam.SectionWindows().SzWZ().ValWithDef(round_ni(Pt2dr(mParam.SzTotIm().Val())*0.6)))
{

    Tiff_Im::SetDefTileFile(100000);

     InitImages();
     InitInPuts();
     InitWindows();
}

bool  cAppli_SaisiePts::HasWZ() const
{
    return mWZ!=0;
}
Video_Win & cAppli_SaisiePts::WZ()
{
    return *mWZ;
}


const Pt2di &  cAppli_SaisiePts::SzRech() const {return mSzRech;}
Pt2di &        cAppli_SaisiePts::DecRech()      {return mDecRech;}
Im2D_INT4      cAppli_SaisiePts::ImRechVisu() const {return mImRechVisu;}
Im2D_INT4      cAppli_SaisiePts::ImRechAlgo() const {return mImRechAlgo;}
const Pt2di &  cAppli_SaisiePts::SzWZ() const   {return mSzWZ;}
cFenOuiNon *   cAppli_SaisiePts::ZFON() {return mZFON;}


bool cAppli_SaisiePts::RefInvis() const
{
   return mRefInvis;
}

bool & cAppli_SaisiePts::ShowDet() 
{
   return mShowDet;
}

const cParamSaisiePts & cAppli_SaisiePts::Param() const { return mParam; }
const std::string & cAppli_SaisiePts::DC() const { return mDC; }
cSetOfSaisiePointeIm  & cAppli_SaisiePts::SOSPI() {return mSOSPI;}

cInterfChantierNameManipulateur * cAppli_SaisiePts::ICNM() const {return mICNM;}



void cAppli_SaisiePts::InitImages()
{
   std::list<std::string>  aListeNameIm = mICNM->StdGetListOfFile(mParam.SetOfImages(),1);

   for 
   (
        std::list<std::string>::const_iterator itN=aListeNameIm.begin();
        itN!=aListeNameIm.end();
        itN++
   )
   {
         if (! ImageOfNameSVP(*itN))
         {
             mImages.push_back(new cImage(*itN,*this));
             mMapIms[*itN] = mImages.back();
         }
   }
   mNbIm = mImages.size();
}

cImage *  cAppli_SaisiePts::ImageOfNameSVP(const std::string & aName)
{
     std::map<std::string,cImage *>::iterator iT = mMapIms.find(aName);
     if (iT == mMapIms.end()) return 0;
     return iT->second;
}
cSP_PointGlob *  cAppli_SaisiePts::PGlobOfNameSVP(const std::string & aName)
{
     std::map<std::string,cSP_PointGlob *>::iterator iT = mMapPG.find(aName);
     if (iT == mMapPG.end()) return 0;
     return iT->second;
}





void cAppli_SaisiePts::InitWindows()
{
   cSectionWindows & aSW = mParam.SectionWindows();
   mNb2W = aSW.NbFenIm().Val();

    mNbW = mNb2W.x * mNb2W.y;
    if (mNbIm < mNbW)
    {
         mNbW = mNbIm;
         mNb2W.x = round_up(sqrt(mNbW-0.01));
         mNb2W.y = round_up((double(mNbW)-0.01)/mNb2W.x);
    }

   Pt2di aSzF =  aSW.SzTotIm().Val().dcbyc(mNb2W);;

   int aCpt=0;
   Video_Win * aLastW = 0;
   Video_Win * aLastWX0 = 0;
   Video_Win * aWTitle = 0;
   Video_Win * aWY0XMax = 0;
   Pt2di aSzTitle(aSzF.x,15);
   for (int aKY =0 ; aKY<mNb2W.y ; aKY++)
   {
       for (int aKX =0 ; aKX<mNb2W.x ; aKX++)
       {
          if (aCpt<mNbW)
          {
             Video_Win * aRes = 0;
             if (aCpt==0)
             {
                   aWTitle = Video_Win::PtrWStd(aSzTitle,true);
                   aRes = new Video_Win(*aWTitle,Video_Win::eBasG,aSzF);
                   // aRes = Video_Win::PtrWStd(aSzF,true);
                   aLastWX0 = aRes;
                   mDisp = new Video_Display(aRes->disp());
             }
             else
             {
                 if (aKX==0)
                 {
                     aWTitle = new Video_Win(*aLastWX0,Video_Win::eBasG,aSzTitle);
                     aRes = new Video_Win(*aWTitle,Video_Win::eBasG,aSzF);
                     aLastWX0 = aRes;
                 }
                 else
                 {
                     aWTitle = new Video_Win(*aLastW,Video_Win::eDroiteH,aSzTitle);
                     aRes = new Video_Win(*aWTitle,Video_Win::eBasG,aSzF);
                 }
                     
             }
             ELISE_COPY(aWTitle->all_pts(),P8COL::yellow,aWTitle->odisc());
             ELISE_COPY(aRes->all_pts(),P8COL::blue,aRes->odisc());
             aLastW = aWTitle;
             mWins.push_back(new cWinIm(*this,*aRes,*aWTitle,*mImages[aCpt]));
             if ((aKY==0) && (aKX==(mNb2W.x -1)))
             {
                 aWY0XMax = aWTitle;
             }
          }
          aCpt++;
       }
   }

   mWZ =  new Video_Win(*aWY0XMax,Video_Win::eDroiteH,mSzWZ);
   mZFON = new cFenOuiNon(*mWZ,Pt2di(200,20));


   mVNameCase.push_back(cCaseNamePoint("Cancel",eCaseCancel));

   if (mParam.EnterName().Val())
   {
         mVNameCase.push_back(cCaseNamePoint("Enter New",eCaseSaisie));
   }

   std::string aNameAuto = mParam.NameAuto().Val();
   if (aNameAuto != "NONE")
   {
      mVNameCase.push_back
      (
            cCaseNamePoint(aNameAuto+ToString(GetCptMax()+1),eCaseAutoNum)
      );
   }

   for 
   (
        std::list<std::string>::const_iterator itN=mParam.FixedName().begin();
        itN !=mParam.FixedName().end();
        itN++
   )
   {
      // const std::string aName = itN->c_str();
      std::vector<std::string> aNew = mICNM->StdGetVecStr(*itN);
      for (int aK=0 ; aK<int(aNew.size()) ; aK++)
         mVNameCase.push_back(cCaseNamePoint(aNew[aK],eCaseStd));
   }

   for (int aK=0 ; aK<int(mVNameCase.size()); aK++)
   {
       mMapNC[mVNameCase[aK].mName] = & mVNameCase[aK];
   }

   for (int aK=0 ; aK<int(mPG.size()) ; aK++)
   {
      ChangeFreeNameP(mPG[aK]->PG()->Name(),false);
   }

   mMenuNamePoint = new cFenMenu(*mWZ,Pt2di(120,20),Pt2di(1,mVNameCase.size()));

   if (mParam.EnterName().Val())
   {
       mWEnter =  new Video_Win(mMenuNamePoint->W(),Video_Win::eDroiteH,Pt2di(150,20));
       mWEnter->move_translate(Pt2di(0,20));
       ELISE_COPY(mWEnter->all_pts(),P8COL::yellow,mWEnter->odisc());
       //mWEnter->move_to(Pt2di(100,20));
       mWEnter->lower();
   }

   ELISE_COPY(mWZ->all_pts(),P8COL::green,mWZ->odisc());
}


cFenMenu * cAppli_SaisiePts::MenuNamePoint()
{
   return mMenuNamePoint;
}

void cAppli_SaisiePts::ChangeFreeNameP(const std::string & aName,bool SetFree)
{
    std::map<std::string,cCaseNamePoint *>::iterator it = mMapNC.find(aName);
    if (it== mMapNC.end()) 
       return;
    if (it->second->mTCP== eCaseStd)
    {
        it->second->mFree = SetFree;
    }
}

cCaseNamePoint *  cAppli_SaisiePts::GetIndexNamePt()
{
   Video_Win aW = mMenuNamePoint->W();
   aW.raise();

   for (int aK=0 ; aK<int(mVNameCase.size()) ; aK++)
   {
      int aGr = (aK%2) ? 255 : 200 ;
      Pt2di aPCase(0,aK);
      mMenuNamePoint->ColorieCase(aPCase,aW.prgb()(aGr,aGr,aGr),1);
      cCaseNamePoint & aCNP = mVNameCase[aK];
      mMenuNamePoint->StringCase(aPCase,aCNP.mFree ?  aCNP.mName : "***" ,true);
   }

   Clik aClk = aW.clik_in();
   //aW.lower();

   Pt2di aKse = mMenuNamePoint->Pt2Case(Pt2di(aClk._pt));
   cCaseNamePoint * aRes =  &(mVNameCase[aKse.y]);

   if (! aRes->mFree) return 0;

   return aRes;
} 



cCaseNamePoint::cCaseNamePoint(const std::string & aName,eTypeCasePt aTCP) :
   mName      (aName),
   mTCP       (aTCP),
   mFree      (true)
{
}

void cAppli_SaisiePts:: ErreurFatale(const std::string & aName)
{
    std::cout << "Erreur, sortie de programme, resultats sauvegardes dans dup";
    std::cout << "\n";
    std::cout <<  "ER = " << aName << "\n";
    std::cout << "\n";
    exit(-1);
}


void  cAppli_SaisiePts::RenameIdPt(std::string & anId)
{

    std::string aPref = mParam.Prefix2Add2IdPt().Val();

    if (aPref=="") return;

    int  aCmp = anId.compare(0,aPref.size(),aPref);
    if (aCmp==0)  return;  // DEJA PREFIXE

    anId = aPref + anId;
    //  std::cout << "RenameIdPt [" << aPref << "] == [" << anId << "] " << aCmp << "\n";


    
   
}

cSP_PointGlob * cAppli_SaisiePts::AddPointGlob(cPointGlob aPG,bool OkRessucite,bool Init)
{

   if (Init)
      RenameIdPt(aPG.Name());


   std::map<std::string,cSP_PointGlob *>::iterator iT = mMapPG.find(aPG.Name());
   if (iT == mMapPG.end())
   {
      mSPG.PointGlob().push_back(aPG);
      mPG.push_back(new cSP_PointGlob(*this,&(mSPG.PointGlob().back())));
      mMapPG[aPG.Name()] = mPG.back();
// std::cout << "== APG CREAT3 "  << aPG.Disparu().ValWithDef(false) << "\n";
      return mPG.back();
   }
/*
*/
   if (iT->second->PG()->Disparu().ValWithDef(false) && OkRessucite)
   {
       if (! iT->second->PG()->FromDico().ValWithDef(false))
       {
           *(iT->second->PG()) = aPG;
       }
      
       iT->second->PG()->Disparu().SetNoInit();
       return iT->second;
   }
   return 0;
}

void cAppli_SaisiePts::InitPG()
{

    mNameSauvPG = mDC + mParam.NamePointsGlobal().Val();
    mDupNameSauvPG = mNameSauvPG + ".dup";
    if (ELISE_fp::exist_file(mNameSauvPG))
    {
       cSetPointGlob aSPG = StdGetObjFromFile<cSetPointGlob>
                            (
                                mNameSauvPG,
                                StdGetFileXMLSpec("ParamSaisiePts.xml"),
                                "SetPointGlob",
                                "SetPointGlob"
                            );

      for 
      (
           std::list<cPointGlob>::iterator itP=aSPG.PointGlob().begin();
           itP!=aSPG.PointGlob().end();
           itP++
      )
      {
          if ( itP->Disparu().ValWithDef(false)  && (! itP->FromDico().ValWithDef(false)))
          {
          }
          else
          {
             AddPointGlob(*itP,false,true);
          }
      }
   }

   for 
   (
       std::list<cImportFromDico>::iterator itIm=mParam.ImportFromDico().begin();
       itIm != mParam.ImportFromDico().end();
       itIm++
   )
   {
        cDicoAppuisFlottant aDic = StdGetObjFromFile<cDicoAppuisFlottant>
                                   (
                                       mDC+itIm->File(),
                                       StdGetFileXMLSpec("ParamChantierPhotogram.xml"),
                                       "DicoAppuisFlottant",
                                       "DicoAppuisFlottant"
                                   );

         for 
         (
            std::list<cOneAppuisDAF>::iterator itA=aDic.OneAppuisDAF().begin();
            itA != aDic.OneAppuisDAF().end();
            itA++
         )
         {
            cPointGlob aPG;
            aPG.Type() = itIm->TypePt();
            aPG.Name() = itA->NamePt() ;
            aPG.LargeurFlou().SetVal(itIm->LargeurFlou().Val());
            aPG.P3D().SetVal(itA->Pt());
            aPG.Incert().SetVal(itA->Incertitude());
            aPG.ContenuPt().SetNoInit();
            aPG.FromDico().SetVal(true);
            AddPointGlob(aPG,false,true);
         }

   }
}


void cAppli_SaisiePts::IniPointeIm()
{
    mNameSauvPtIm = mDC + mParam.NamePointesImage().Val();
    mDupNameSauvPtIm = mNameSauvPtIm + ".dup";
    if (ELISE_fp::exist_file(mNameSauvPtIm))
    {
            mSOSPI = StdGetObjFromFile<cSetOfSaisiePointeIm>
                     (
                         mNameSauvPtIm,
                         StdGetFileXMLSpec("ParamSaisiePts.xml"),
                         "SetOfSaisiePointeIm",
                         "SetOfSaisiePointeIm"
                     );
   }

   for 
   (
      std::list<cSaisiePointeIm>::iterator itS=mSOSPI.SaisiePointeIm().begin();
      itS != mSOSPI.SaisiePointeIm().end();
      itS++
   )
   {
          static bool FirstNoIm = true;
          cImage * anIm = ImageOfNameSVP(itS->NameIm());
          if (FirstNoIm && (!anIm))
          {
              FirstNoIm = false;
              std::cout << "There exist image in Pointe with NO  corresponding loaded image \n"; 
              std::cout << " Firts one is " << itS->NameIm() << "\n";
          }

          if (anIm)
          {
             anIm->SetSPIM(&(*itS));
             for
             (
                std::list<cOneSaisie>::iterator itOS=itS->OneSaisie().begin();
                itOS!=itS->OneSaisie().end();
                itOS++
             )
             {
                if (itOS->Etat() != eEPI_Disparu) 
                {
                    RenameIdPt(itOS->NamePt());
                    static bool FirstNoPG = true;
                    cSP_PointGlob * aPG = PGlobOfNameSVP(itOS->NamePt());
                    if (FirstNoPG && (!aPG))
                    {
                        FirstNoPG = false;
                        std::cout << "There exist  a point 2D in image with no global homologue \n"; 
                        std::cout << " Firts one is " <<  itOS->NamePt() << " in " << itS->NameIm() << "\n";
                    }
                    if (aPG)
                    {
                         
                        anIm->AddAPointe(&(*itOS),aPG,true);
                    }
                 }
              }
          }
   }

   for (std::vector<cSP_PointGlob*>::iterator itP=mPG.begin(); itP!=mPG.end() ; itP++)
   {
       AddPGInAllImage(*itP);
   }
}

void cAppli_SaisiePts::AddPGInAllImage(cSP_PointGlob  * aSPG)
{
   if (mParam.KeyAssocOri().IsInit())
   {
      for (std::vector<cImage*>::iterator itI=mImages.begin(); itI!=mImages.end() ; itI++)
      {
          AddOnePGInImage(aSPG,**itI);
      }
   }
}

void cAppli_SaisiePts::AddOnePGInImage(cSP_PointGlob  * aSPG,cImage & anI)
{
     const cPointGlob & aPG = *(aSPG->PG());

     Pt2dr aPIm  = anI.PointArbitraire();
     bool OkInIm = true;

     if (aPG.P3D().IsInit())
     {
        Pt3dr aP3 = aPG.P3D().Val();
        cCapture3D * aCapt3D = anI.Capt3d();
        if (aCapt3D) 
        {
            aPIm =  aCapt3D->Ter2Capteur(aP3); //  : anI.PointArbitraire();

            if (! aCapt3D->PIsVisibleInImage(aP3)) 
            {
               OkInIm = false;
            }
        }
     }

/// std::cout << "XccByyt "<< aSPG->PG()->Name() << " " << OkInIm << "\n";

     cSP_PointeImage * aPointeIm = anI.PointeOfNameGlobSVP(aPG.Name());

     if (aPointeIm)
     {
        if (aPointeIm->Saisie()->Etat()==eEPI_NonSaisi)
        {
           if ( OkInIm && anI.InImage(aPIm))
           {
              aPointeIm->Saisie()->PtIm() = aPIm;
           }
           else
           {
              aPointeIm->Visible() = false;
           }
        }
     }
     else
     {
        if (OkInIm && anI.InImage(aPIm))
        {
           cOneSaisie anOS;
           anOS.Etat() = eEPI_NonSaisi;
           anOS.NamePt() = aPG.Name();
           anOS.PtIm() = aPIm;
           anI.AddAPointe(&anOS,aSPG,false);
        }
     }

}

void cAppli_SaisiePts::GlobChangStatePointe
     (
           const std::string & aName,
           const eEtatPointeImage aState
     )
{
    for 
    (
        std::list<cSaisiePointeIm>::iterator itSPI=mSOSPI.SaisiePointeIm().begin();
        itSPI!=mSOSPI.SaisiePointeIm().end();
        itSPI++
    )
    {
        for 
        (
            std::list<cOneSaisie>::iterator itS=itSPI->OneSaisie().begin();
            itS!=itSPI->OneSaisie().end();
            itS++
        )
        {
           if (itS->NamePt() == aName)
           {
              itS->Etat() = aState;
           }
        }
    }
}



void cAppli_SaisiePts::InitInPuts()
{
//std::cout << "SPTS::CCCCC\n"; getchar();
    InitPG();
//std::cout << "SPTS::DDDDDD\n"; getchar();
    IniPointeIm();
//std::cout << "SPTS::EEEEEE\n"; getchar();
    Sauv();
//std::cout << "SPTS::FFFFF\n"; getchar();
}

cSetOfSaisiePointeIm PurgeSOSPI(const cSetOfSaisiePointeIm & aSOSPI)
{
    cSetOfSaisiePointeIm aRes;
    for 
    (
        std::list<cSaisiePointeIm>::const_iterator itSPI=aSOSPI.SaisiePointeIm().begin();
        itSPI!=aSOSPI.SaisiePointeIm().end();
        itSPI++
    )
    {
        cSaisiePointeIm aSSP;
        aSSP.NameIm() = itSPI->NameIm();
        for 
        (
            std::list<cOneSaisie>::const_iterator itS=itSPI->OneSaisie().begin();
            itS!=itSPI->OneSaisie().end();
            itS++
        )
        {
           if (
                     (itS->Etat() != eEPI_Disparu)
                  && (itS->Etat() != eEPI_NonValue)
              )
           {
              aSSP.OneSaisie().push_back(*itS);
           }
        }
        aRes.SaisiePointeIm().push_back(aSSP);
    }
    return aRes;
}

void cAppli_SaisiePts::Sauv()
{
     cSetOfSaisiePointeIm aSOSPI = PurgeSOSPI(mSOSPI);
     MakeFileXML(aSOSPI,mDupNameSauvPtIm);
     MakeFileXML(aSOSPI,mNameSauvPtIm);

     MakeFileXML(mSPG,mDupNameSauvPG);
     MakeFileXML(mSPG,mNameSauvPG);

     if (mParam.ExportPointeImage().IsInit())
     {
        cSetOfMesureAppuisFlottants aSOMAF;
        for 
        (
               std::list<cSaisiePointeIm>::const_iterator itSP = mSOSPI.SaisiePointeIm().begin();
               itSP != mSOSPI.SaisiePointeIm().end();
               itSP++
        )
        {
             cMesureAppuiFlottant1Im aMAF;
             aMAF.NameIm() = itSP->NameIm();

             for 
             (
                   std::list<cOneSaisie>::const_iterator itS=itSP->OneSaisie().begin();
                   itS!=itSP->OneSaisie().end();
                   itS++
             )
             {
                 if (itS->Etat()==eEPI_Valide) 
                 {
                    cOneMesureAF1I aM;
                    aM.NamePt() = itS->NamePt();
                    aM.PtIm() = itS->PtIm();
                    aMAF.OneMesureAF1I().push_back(aM);
                 }
             }

             aSOMAF.MesureAppuiFlottant1Im().push_back(aMAF);
        }
        std::string aNameExp = DC()+StdPrefix(mParam.ExportPointeImage().Val());

        MakeFileXML(aSOMAF, aNameExp + "-S2D.xml");


        cDicoAppuisFlottant aDico;
        for (std::list<cPointGlob>::const_iterator itP=mSPG.PointGlob().begin(); itP!=mSPG.PointGlob().end(); itP++)
        {
            if (itP->Mes3DExportable().ValWithDef(false) && itP->P3D().IsInit())
            {
               cOneAppuisDAF anAP;
               anAP.Pt() = itP->P3D().Val();
               anAP.NamePt() = itP->Name();
               anAP.Incertitude() = Pt3dr(1,1,1);

               aDico.OneAppuisDAF().push_back(anAP);
            }
        }

        MakeFileXML(aDico, aNameExp + "-S3D.xml");

/*
*/
     }
/*
  a voir si pb de versions sous commit
<<<<<<< .mine
    <DicoAppuisFlottant>
          <OneAppuisDAF>
               <Pt>  103 -645 5</Pt>
               <NamePt>Coin-Gauche </NamePt>
               <Incertitude>  10 10 10  </Incertitude>
          </OneAppuisDAF>

=======
     A FUSIONNER AVEC LA VERSION SUR PC IGN, pas commite ???
     if (mParam.ExportPointeTerrain().IsInit())
     {
        cDicoAppuisFlottant aDic;
        for 
        (
            std::list<cPointGlob>::iterator itP=mSPG.PointGlob().begin();
            itP!=mSPG.PointGlob().end();
            itP++
        )
        {
            if (itP->Mes3DExportable().ValWithDef(false))
            {
               cOneAppuisDAF anAp;
               anAp.Pt() = itP->P3D.Val();
               anAp.NamePt() = itP->Name();
               anAp.Incertitude() = Pt3dr(1,1,1);
               aDic.OneAppuisDAF().push_back(anAp);
            }
        }
        MakeFileXML(aDic, DC()+(mParam.ExportPointeTerrain().Val()));
     }
>>>>>>> .r889
*/
}

void cAppli_SaisiePts::Exit()
{
     Sauv();
     exit(-1);
}


class cCmpIm
{
    public :

        bool operator ()(const tImPtr & aI1,const tImPtr & aI2)
        {
            if (aI2->WAff() && (! aI1->WAff()))
              return true;
            if (aI1->WAff() && (! aI2->WAff()))
              return false;

            if (aI1->Prio() > aI2->Prio()) return true;
            if (aI1->Prio() < aI2->Prio()) return false;

            return aI1->Name() < aI2->Name();
        }
};

double cAppli_SaisiePts::StatePriority(eEtatPointeImage aState)
{
   switch(aState)
   {
        case   eEPI_NonSaisi :
               return 1e3;
        break;

        case   eEPI_Refute :
               return mRefInvis ? 0 : 1e-3;
        break;

        case   eEPI_Douteux :
               return 1;
        break;

        case eEPI_Valide :
               return 1e-6;
        break;

        case  eEPI_Disparu :
               return 0;
        break;
        

        case eEPI_NonValue :
        break;
   }

   ELISE_ASSERT(false,"Unhandled Priority");
   return 0;
}

void cAppli_SaisiePts::ChangeImages
     (
          cSP_PointGlob * PointPrio,
          const std::vector<cWinIm *>  &  aW2Ch
     )
{
   for (int aKI=0 ; aKI<int(mImages.size()); aKI++) 
   {
       cImage & anIm = *(mImages[aKI]);
       anIm.SetPrio(anIm.CalcPriority(PointPrio));
       
   }

   cCmpIm aCmpIm;
   std::sort(mImages.begin(),mImages.end(),aCmpIm);

   for (int aKW =0 ; aKW < int(aW2Ch.size()) ; aKW++)
   {
       aW2Ch[aKW]->SetNoImage();
   }

   int aKW =0 ;
   int aKI =0;

   while (aKW <int(aW2Ch.size()) )
   {
        ELISE_ASSERT(aKI<int(mImages.size()),"Incoh in cAppli_SaisiePts::ChangeImages");

        cImage * anIm = mImages[aKI];
        if (!anIm->WAff())
        {
            aW2Ch[aKW]->SetNewImage(anIm);
            aKW++;
        }
        aKI++;
   }
}

void cAppli_SaisiePts::KillSom(cSP_PointGlob * aSG)
{
    if (! mZFON->Get("Kill " + aSG->PG()->Name() + "?")) return;
    aSG->SetKilled();

    ChangeFreeNameP(aSG->PG()->Name(),true);
    ReaffAllW();
}


bool cAppli_SaisiePts::HasOrientation() const
{
   return    mParam.KeyAssocOri().IsInit()
          && (mParam.KeyAssocOri().Val() != "NONE");
}




/*
*/


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
