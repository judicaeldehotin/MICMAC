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
// #include "XML_GEN/all_tpl.h"

/*
*/




class  cReadOri : public cReadObject
{
    public :
        cReadOri(char aComCar,const std::string & aFormat) :
               cReadObject(aComCar,aFormat,"S"),
               mPt(-1,-1,-1),
               mInc3(-1,-1,-1),
               mInc (-1)
        {
              AddString("N",&mName,true);
              AddPt3dr("XYZ",&mPt,true);
              AddPt3dr("WPK",&mWPK,false);
        }

        std::string mName;
        Pt3dr       mPt;
        Pt3dr       mWPK;
        Pt3dr       mInc3;
        double      mInc;
};



//================================================

cTxtCam::cTxtCam() :
   mCam      (0),
   mRefCam   (0),
   mOC       (0),
   mSelC     (false),
   mVIsCalc  (false),
   mMTD      (0)
{
}

bool cCmpPtrCam::operator() (const cTxtCamPtr & aC1  ,const cTxtCamPtr & aC2)
{
    return aC1->mPrio < aC2->mPrio;
}
cCmpPtrCam TheCmp;

void cTxtCam::SetVitesse(const Pt3dr& aV)
{
    mVIsCalc = true;
    mV = aV;
}


class cAttrVoisSom
{
    public :
       cAttrVoisSom(cTxtCam * aCam) :
              mCam (aCam)
       {
       }

       cAttrVoisSom()   :
           mCam(0) 
       {}

       cTxtCam * mCam;
};

class cAttrVoisA
{
    public :
       cAttrVoisA()
       {
       }
};


typedef  ElSom<cAttrVoisSom,cAttrVoisA>    tSomVois;
typedef  ElArc<cAttrVoisSom,cAttrVoisA>    tArcVois;
typedef  ElSomIterator<cAttrVoisSom,cAttrVoisA> tItSVois;
typedef  ElArcIterator<cAttrVoisSom,cAttrVoisA> tItAVois;

typedef  ElGraphe<cAttrVoisSom,cAttrVoisA> tGrVois;



Pt2dr POfSom(const tSomVois & aSom)
{
      Pt3dr aP = aSom.attr().mCam->mC;
      return Pt2dr(aP.x,aP.y);
}
Pt2dr POfSomPtr(const tSomVois * aSom) {return POfSom(*aSom);}
Pt2dr POfSomPtrPtr(const tSomVois ** aSom) {return POfSom(**aSom);}


class cSubGrVois : public ElSubGraphe<cAttrVoisSom,cAttrVoisA>
{
    public :
        Pt2dr pt(tSomVois & aS) {return POfSom(aS);}
};


tSomVois & SomDif(const ElFilo<tArcVois *>& aF,const tSomVois & aS1,const tSomVois & aS2)
{
    for (int aK=0 ; aK<aF.nb() ; aK++)
    {
        tSomVois & aS = aF[aK]->s1();
        if ((aS.num() != aS1.num())  && (aS.num() != aS2.num()))
           return aS;
    }
    ELISE_ASSERT(false,"SomDif");
    return *((tSomVois*)0);
}


//================================================

                   // std::string  aKeyExport = "NKS-Assoc-Im2Orient@-" + VerifReexp;
                   // std::string aNOE = aICNM->Assoc1To1(aKeyExport,aNewCam.mNameIm,true);

class cAppli_Ori_Txt2Xml_main 
{
     public :
          cAppli_Ori_Txt2Xml_main (int argc,char ** argv);
         void operator()(tSomVois*,tSomVois*,bool);  // Delaunay Call back
     private :

         void AddArc(tSomVois*,tSomVois*,int aCoul);

         void ParseFile();
         void TestRef();
         void CalcImCenter();
         void DoTiePCenter();
         void CalcVitesse();
         void SauvOriFinal();
         void OnePasseElargV(int aK0, int aK1, int aStep);
         void SauvRel();
         void InitCamera(cTxtCam & aCam,Pt3dr  aC,Pt3dr  aWPK);

         void InitGrapheVois();
         void VoisInitDelaunay();
         void VoisInitDelaunayCroist();
         void VoisInitLine();

         void ShowSom(const tSomVois & aSom,int aCoul);
         void ShowArc(const tSomVois & aSom1,const tSomVois & aSom2,int aCoul);

         bool  OkArc(int aK1,int aK2) const;
         Pt3dr Vect(int aK1, int aK2) const
         {
             return mVCam[aK2]->mC-mVCam[aK1]->mC ;
         }
         Pt3dr VitesseIndice(int aK1, int aK2) const
         {
             return Vect(aK1,aK2) / double(aK2-aK1);
         }

         Pt2dr ToW(Pt2dr aP)
         {
             aP = (aP-mBoxC._p0)*mScaleV;
             return Pt2dr(mBordV,-mBordV) + Pt2dr(aP.x,mSzW.y-aP.y);
         }
         Pt2dr ToW(const tSomVois &aS) {return ToW(POfSom(aS));}



         std::string NameOrientation(const std::string &anOri,const cTxtCam & aCam)
         {
             return mICNM->Assoc1To1("NKS-Assoc-Im2Orient@-" +anOri,aCam.mNameIm,true);
         }


         std::string         mFilePtsIn;
         std::string         mOriOut;
         eTypeFichierOriTxt  mType;
         double              mDistNeigh;
         std::string         mKeyName2Image;
         bool                mAddCalib;
         std::string         mImC;
         int                 mNbImC;
         int                 mSizeRC; 
         std::string         mReexpMatr;
         std::string         mDir;
         cInterfChantierNameManipulateur * mICNM;
         std::string         mFormat;
         char                mComment;
         cCalibrationInternConique mCIO;
         cChSysCo *          mCSC;
         cOrientationConique mOC0;
         std::string         mPatternIm;
         std::vector<cTxtCam *> mVCam;
         std::vector<cTxtCam *> mVREF;
         cTxtCam *            mCamC;
         std::string          mFileCalib;
         std::string          mPatImCenter;
         int                  mNbCam;
         std::string          mNameCple;
         bool                 mAddDelaunay;
         bool                 mAddDelaunayCroist;
         double               mCostRegulAngle;
         int                  mCptMin;
         int                  mCptMax;
         double               mDifMaxV ;

         double               mRegul;
         double               mRelNewBr;
         double               mRelFiabl;
         bool                 mCalcV;
         double               mDelay;
         bool                 mHasWPK;
         bool                 mMTDOnce;
         bool                 mTetaFromCap;
         double               mOffsetTeta;
         std::string          mRefOri;
         int                  mSiftResol;
         int                  mSiftLowResol;
         bool                 mUseOnlyC;
         tGrVois              mGrVois;
         cSubGrVois              mSubAll;
         std::vector<tSomVois *> mVSomVois;
         Box2dr                  mBoxC;
         double                  mSzV;
         Pt2dr                   mSzW;
         double                  mScaleV;
         double                  mBordV;
         Video_Win *             mW;
         int                     mLine;
         eConventionsOrientation mConvOri;
         bool                 mCalibByFile;
         double               mAltiSol;
         double               mProf;
};

void cAppli_Ori_Txt2Xml_main::operator()(tSomVois* aS1,tSomVois* aS2,bool)  // Delaunay Call back
{
    AddArc(aS1,aS2,P8COL::blue);
}


void cAppli_Ori_Txt2Xml_main::AddArc(tSomVois* aS1,tSomVois* aS2,int aCoul)
{
    tArcVois * anAExist = mGrVois.arc_s1s2(*aS1,*aS2);
    if (! anAExist)
    {
       tArcVois & anArc = mGrVois.add_arc(*aS1,*aS2,cAttrVoisA());
       ShowArc(anArc.s1(),anArc.s2(),aCoul);
    }
}


void cAppli_Ori_Txt2Xml_main::ShowSom(const tSomVois & aSom,int aCoul)
{
  if (mW)
     mW->draw_circle_loc(ToW(aSom),2.0,mW->pdisc()(aCoul));
}
void cAppli_Ori_Txt2Xml_main::ShowArc(const tSomVois & aSom1,const tSomVois & aSom2,int aCoul)
{
   if (mW)
      mW->draw_seg(ToW(aSom1),ToW(aSom2),mW->pdisc()(aCoul));

}

/*

   On cherche à decomposer en un sous ensemble de sommets connexes.
Il y a 4 etat possible

   * debut de brin
   * fin de brin
   * milieu de brin
   * no brin 

   eVitMil  -> eVitMil, eVitApr, eNoVit,
   eVitAv   -> eVitMil, eVitApr, 
   eVitApr  -> eVitAv, eNoVit,
   eNoVit   -> eNoVit, eVitAv,

*/

typedef enum
{
     eDebTraj,
     eMilTraj,
     eFinTraj,
     eNoTraj
} eTyNdVit;


void  ComputeTransition(eTyNdVit  aTyN1,eTyNdVit  aTyN2,bool & Ok,bool & Innoc,bool & CreateBr)
{

    if ((aTyN1 == eDebTraj) || (aTyN1 == eMilTraj))
    {
         Ok = (aTyN2==eMilTraj) || (aTyN2==eFinTraj);
         Innoc = false;
    }
    else
    {
         Ok = (aTyN2==eNoTraj) || (aTyN2==eDebTraj);
         Innoc = true;
    }

    CreateBr = (aTyN1==eDebTraj);

}


class cAttrHypSomV
{
    public :
       cAttrHypSomV(cTxtCam * aCam,Pt3dr aV,bool Ok,eTyNdVit aTyN) :
              mCam (aCam),
              mV   (aV),
              mOK  (Ok),
              mTyN (aTyN)
       {
       }

       cAttrHypSomV()   :
           mCam(0) 
       {}

       cTxtCam * mCam;
       Pt3dr     mV;
       bool      mOK;
       eTyNdVit  mTyN;
};

class cHypAttrA
{
    public :
        double mCost;
};



class OriSubGr  : public ElSubGraphe<cAttrHypSomV,cHypAttrA> 
{
    public :
          REAL   pds(TArc & anArc) 
          {
             return anArc.attr().mCost;
          }

    private :
};


typedef ElSom<cAttrHypSomV,cHypAttrA>  tSom;



double AngleVect(const Pt3dr &aP1,const Pt3dr &aP2)
{
   double aScal = scal(vunit(aP1),vunit(aP2));
   if (aScal >= 1) return 0;
   if (aScal <= -1) return PI;

   return acos(aScal);
}

bool  cAppli_Ori_Txt2Xml_main::OkArc(int aK1,int aK2) const
{
   // set_min_max(aK1,aK2);
   // double aTeta = AngleVect(Vect(aK1,aK2),Vect(aK2-1,aK2));

   // return aTeta < 0.7;
   return true;
}

void  cAppli_Ori_Txt2Xml_main::OnePasseElargV(int aK0, int aK1, int aStep)
{
   for (int aK= aK0 ; aK!= aK1 ; aK+=aStep)
   {
       cTxtCam & aCamCur =  *(mVCam[aK]);
       cTxtCam & aCamNext =  *(mVCam[aK+aStep]);
       if ((! aCamCur.mVIsCalc) && aCamNext.mVIsCalc)
       {
           Pt3dr aVCur =  Vect(aK,aK+aStep);
           Pt3dr aVNext =  Vect(aK+aStep,aK+2*aStep);
           if (euclid(aVCur-aVNext)<mDifMaxV)
              aCamCur.SetVitesse(aVCur * double(aStep));
       }
   }

}


void cAppli_Ori_Txt2Xml_main::SauvOriFinal()
{
   for (int aK= 0 ; aK<mNbCam ; aK++)
   {
       cTxtCam & aCam = *(mVCam[aK]);
       MakeFileXML(*(aCam.mOC),aCam.mNameOri);
       if (EAMIsInit(&mReexpMatr))
       {
          cOrientationConique aOriEx = aCam.mCam->StdExportCalibGlob();
          MakeFileXML(aOriEx,NameOrientation(mReexpMatr,aCam));
       }
   }
}

void cAppli_Ori_Txt2Xml_main::CalcVitesse()
{
   
   if (mTetaFromCap)
      mHasWPK = true;


   ElGraphe<cAttrHypSomV,cHypAttrA> mGr;
   std::vector<tSom *> aVSom;

   for (int aK= 0 ; aK<mNbCam ; aK++)
   {
        cTxtCam * aCam = mVCam[aK];
        int aKPrec = ElMax(0,aK-1);
        int aKNext = ElMin(mNbCam-1,aK+1);

        aVSom.push_back(&mGr.new_som(cAttrHypSomV(aCam,VitesseIndice(aK,aKNext),(aKNext!=aK) ,eDebTraj)));
        aVSom.push_back(&mGr.new_som(cAttrHypSomV(aCam,VitesseIndice(aKPrec,aKNext),(aKPrec!=aK) && (aKNext!=aK),eMilTraj)));
        aVSom.push_back(&mGr.new_som(cAttrHypSomV(aCam,VitesseIndice(aKPrec,aK),(aKPrec!=aK) ,eFinTraj)));
        aVSom.push_back(&mGr.new_som(cAttrHypSomV(aCam,Pt3dr(0,0,0),true,eNoTraj)));
    }


    for (int aKS =0 ; aKS<int(aVSom.size()-4) ; aKS+=4)
    {
         for (int aKS1 = aKS ; aKS1<(aKS+4) ; aKS1++)
         {
             for (int aKS2 = aKS+4 ; aKS2<(aKS+8) ; aKS2++)
             {
                tSom * aS1 = aVSom[aKS1];
                const cAttrHypSomV & anAttr1 = aS1->attr();
                tSom * aS2 = aVSom[aKS2];
                const cAttrHypSomV & anAttr2 = aS2->attr();

                if (anAttr1.mOK && anAttr2.mOK)
                {
                    bool Ok,Innocuped,CreateBr;
                    ComputeTransition(anAttr1.mTyN,anAttr2.mTyN,Ok,Innocuped,CreateBr);

                    if (Ok)
                    {
                        cHypAttrA anAA;
                        anAA.mCost = Innocuped ? mRegul : euclid(anAttr1.mV-anAttr2.mV);

                        if (CreateBr)
                           anAA.mCost += mRegul * mRelNewBr;

                           
                         mGr.add_arc(*aS1,*aS2,anAA);
                    }
                }
             }
         }
    }

    ElFilo<tSom *> aBegin;
    for (int aK = 0; aK< 4 ; aK++)
        aBegin.pushlast(aVSom[aK]);

    ElFilo<tSom *> aEnd;
    for (int aK = aVSom.size()-4 ; aK< int(aVSom.size()) ; aK++)
        aEnd.pushlast(aVSom[aK]);

    ElSubGrapheInFilo<cAttrHypSomV,cHypAttrA> aGrBut(aEnd);


    ElPcc<cAttrHypSomV,cHypAttrA> aPcc;
    OriSubGr aSub;

    tSom * aRes = aPcc.pcc
                  (
                       aBegin,
                       aGrBut,
                       aSub,
                       eModePCC_Somme
                  );
    
     ELISE_ASSERT(aRes!=0,"Pcc inc in cAppli_Ori_Txt2Xml_main::CalcVitesse");
 
     ElFilo<tSom *> aPCC;
     aPcc.chemin(aPCC,*(aRes));

     int aCptTraj=-1;

     for (int aKPcc = aPCC.nb()-1 ; aKPcc >= 0 ; aKPcc--)
     {
         const cAttrHypSomV & anAttr = aPCC[aKPcc]->attr();
         eTyNdVit  aTyn = anAttr.mTyN ;
         cTxtCam * aCam = anAttr.mCam ;

         if ((aTyn==eDebTraj) || (aTyn==eNoTraj))
            aCptTraj++;
         aCam->mNumBande = aCptTraj;

         Pt3dr aV = anAttr.mV;

         bool Fiable = false;
         if (aTyn==eMilTraj)
         {
             Pt3dr aVPrec = Vect(aCam->mNum-1,aCam->mNum);
             Pt3dr aVNext = Vect(aCam->mNum,aCam->mNum+1);

             Fiable = euclid(aVPrec-aVNext) < mDifMaxV;
         }


         if (aTyn != eNoTraj)
         {
            aCam->mV = aV;
            aCam->mVIsCalc = true;
            aCam->mOC->Externe().Vitesse().SetVal(aV);
            aCam->mOC->Externe().VitesseFiable().SetVal(Fiable);
         }


         if (1)
         {
             if (aTyn==eDebTraj) std::cout << "[[\n";

             std::cout << "   Num " << aCam->mNum << " " << " Band " << aCam-> mNumBande << " " ;

 

              if (aTyn== eNoTraj)   
                 std::cout << " ******";
              else
              {
                 if (Fiable) 
                    std::cout  << "##";
                 else
                    std::cout  << "  ";
                 if (mHasWPK)
                 {
                    Pt3dr aWPK = aCam->mOC->Externe().ParamRotation().CodageAngulaire().Val();
                    double aKap = aWPK.z;
                    double aTeta = angle(Pt2dr(aV.x,aV.y)) * (180/PI);
                    std::cout << aV << "TETA " << aTeta <<  " Kap=" << aKap << " Dif=" << mod_real(aTeta-aKap,360) ;
                 }
              }
             


             std::cout << "\n";
             if (aTyn==eFinTraj) std::cout << "]]\n";
         }


     }

     if (EAMIsInit(&mDelay) || mTetaFromCap)
     {
         for (int aK= 0 ; aK<mNbCam ; aK++)
         {
             cTxtCam * aCam = mVCam[aK];
             if ( aCam->mOC->Externe().Vitesse().IsInit())
             {

                 Pt3dr aV  = aCam->mV;
                 Pt3dr aC  = aCam->mC + aV * mDelay;
                 Pt3dr aWPK  = aCam->mOC->Externe().ParamRotation().CodageAngulaire().ValWithDef(Pt3dr(0,0,0));
                 if (mTetaFromCap)
                    aWPK = Pt3dr(0,0, angle(Pt2dr(aV.x,aV.y)) * (180/PI) -80);

                 InitCamera(*aCam,aC,aWPK);
             }
         }
     }
}




cAppli_Ori_Txt2Xml_main::cAppli_Ori_Txt2Xml_main(int argc,char ** argv) :
    mType            (eOriTxtInFile),
    mDistNeigh       (0),
    mKeyName2Image   ("NKS-Assoc-Id"),
    mAddCalib        (true),
    mImC             (""),
    mNbImC           (10),
    mSizeRC          (300),
    mReexpMatr       (),
    mDir             (),
    mICNM            (),
    mFormat          (""),
    mComment         (0),
    mCSC             (0),
    mPatternIm       (""),
    mCamC            (0),
    mNbCam           (0),
    mCostRegulAngle  (5),
    mCptMin          (0),
    mCptMax          (int (1e9)),
    mRegul           (5.0),
    mRelNewBr        (0.4),
    mRelFiabl        (0.75),
    mCalcV           (false),
    mDelay           (0),
    mMTDOnce         (false),
    mTetaFromCap     (false),
    mSiftResol       (0),
    mSiftLowResol    (0),
    mUseOnlyC        (false),
    mSzV             (800),
    mBordV           (20),
    mW               (0),
    mLine            (3),
    mConvOri         (eConvAngPhotoMDegre),
    mCalibByFile     (true)
{

    bool Help;
    std::string aStrType; 
    if (argc >=2)
    {
        aStrType = argv[1];
        StdReadEnum(Help,mType,argv[1],eNbTypeOriTxt,true);

    }

    std::string aStrChSys;
    std::vector<std::string> aPrePost;
    std::vector<int>         aVCpt;
    

    ElInitArgMain
    (
           argc,argv,
           LArgMain() << EAMC(aStrType,"Format specification") 
                      << EAMC(mFilePtsIn,"Orientation   File") 
                      << EAMC(mOriOut,"Targeted orientation") ,
           LArgMain() 
                      << EAM(aStrChSys,"ChSys",true,"Change coordinate file")
                      << EAM(mFileCalib,"Calib",true,"External XML calibration file")
                      << EAM(mAddCalib,"AddCalib",true,"Try to add calibration, def=true")
                      << EAM(aPrePost,"PrePost",true,"[Prefix,Postfix] to generate name of image from id")
                      << EAM(mKeyName2Image,"KN2I",true,"Key 2 compute Name Image from Id in file")
                      << EAM(mDistNeigh,"DN",true,"Neighbooring distance for Image Graphe")
                      << EAM(mImC,"ImC",true,"Image \"Center\" for computing AltiSol")
                      << EAM(mNbImC,"NbImC",true,"Number of neigboor around Image \"Center\" (Def=50)")
                      << EAM(mSizeRC,"RedSizeSC",true,"Reduced Size of image to use for Tapioca for AltiSol (Def=1000)")
                      << EAM(mReexpMatr,"Reexp",true,"Reexport as Matrix (internal set up)")
                      << EAM(mRegul,"Regul",true,"Regularisation cost (Cost of hole), Def=5.0")
                      << EAM(mRelNewBr,"RegNewBr",true,"cost of creating a new branch (Def=0.4, prop to Regul)")
                      << EAM(mRelFiabl,"Reliab",true,"Threshold for reliable speed, Def=0.75 (prop to Regul)")
                      << EAM(mCalcV,"CalcV",true,"Calcul speed (def = false)")
                      << EAM(mDelay,"Delay",true,"Delay to take into accound after speed estimate")
                      << EAM(mTetaFromCap,"TFC",true,"Teta from cap : compute orientation from speed)")
                      << EAM(mRefOri,"RefOri",true,"Ref Orientation (internal purpose)")
                      << EAM(mSiftResol,"SiftR",true,"Resolution of sift point for Tapioca ,when ImC, (Def No Sift)")
                      << EAM(mSiftLowResol,"SiftLR",true,"Low Resolution of sift point for MultisCale ,when ImC (Def no multicale)")

                      << EAM(mNameCple,"NameCple",true,"Name of XML file to save couples")
                      << EAM(mAddDelaunay,"Delaunay",true,"Add delaunay arc when save couple (Def=true)")
                      << EAM(mAddDelaunayCroist,"DelaunayCross",true,"Complete delaunay with some crossing trick arc when save couple (Def=true)")

                      << EAM(aVCpt,"Cpt",true,"============ [CptMin,CptMax] for tuning purpose =======")
                      << EAM(mUseOnlyC,"UOC",true,"Use Only Center (tuning)")
                      << EAM(mMTDOnce,"MTD1",true,"Compute Metadata only for first image (tuning)")
                      << EAM(mLine,"Line",true,"Nb neighbour in the same line")
                      << EAM(mCalibByFile,"CBF",true,"Export calib as a link to existing file")
                      << EAM(mAltiSol,"AltiSol",true,"Average altitude of ground")
                      << EAM(mProf,"Prof",true,"Average Prof of images")
    );

    if (! EAMIsInit(&mAddDelaunay))
       mAddDelaunay = EAMIsInit(&mNameCple);

    if (! EAMIsInit(&mAddDelaunayCroist))
       mAddDelaunayCroist = mAddDelaunay ;
    else
       mAddDelaunayCroist = mAddDelaunayCroist &&  mAddDelaunayCroist;

    mCalcV  = mCalcV
             || EAMIsInit(&mDelay)
             || EAMIsInit(&mRelFiabl)
             || EAMIsInit(&mRelNewBr)
             || EAMIsInit(&mRegul)
             || mTetaFromCap;

    mDifMaxV    = mRegul * mRelFiabl;
    if (EAMIsInit(&aPrePost))
    {
        ELISE_ASSERT(aPrePost.size()==2,"PrePost must be exactly of size 2");
        mKeyName2Image = "NKS-Assoc-AddPrePost@" + aPrePost[0] + "@"+aPrePost[1];
    }
    if (EAMIsInit(&aVCpt))
    {
        ELISE_ASSERT(aVCpt.size()==2,"Cpt PrePost must be exactly of size 2");
        mCptMin = aVCpt[0];
        mCptMax = aVCpt[1];
    }


    mDir = DirOfFile(mFilePtsIn);
    mICNM =  cInterfChantierNameManipulateur::BasicAlloc(mDir);



    if (mType==eOriTxtAgiSoft)
    {
         mFormat     = "N  X Y Z K W P";
         mComment    = '#';
    }
    else if (mType==eOriBluh)
    {
         mFormat     = "N  W P K X Y Z";
         mComment    = '#';
         mConvOri    = eConvAngPhotoMGrade;
    }
    else if (mType==eOriTxtInFile)
    {
       bool Ok = cReadObject::ReadFormat(mComment,mFormat,mFilePtsIn,true);
       ELISE_ASSERT(Ok,"File do not begin by format specification");
    }
    else
    {
        bool Ok = cReadObject::ReadFormat(mComment,mFormat,aStrType,false);
        ELISE_ASSERT(Ok,"Arg0 is not a valid format specif");
    }

    // cCalibrationInternConique aCIO;
    bool CalibIsInit = EAMIsInit(&mFileCalib) && mAddCalib;
    mCalibByFile = mCalibByFile && CalibIsInit;

     mCIO=  StdGetObjFromFile<cCalibrationInternConique>
            (
                  CalibIsInit ? (mDir + mFileCalib) : Basic_XML_MM_File("Template-Calib-Basic.xml"),
                  StdGetFileXMLSpec("ParamChantierPhotogram.xml"),
                  "CalibrationInternConique",
                  "CalibrationInternConique"
            );


    if (aStrChSys!="")
       mCSC = cChSysCo::Alloc(aStrChSys,"");


    mOC0 =   StdGetObjFromFile<cOrientationConique>
             (
                 Basic_XML_MM_File("Template-OrCamAng.xml"),
                 StdGetFileXMLSpec("ParamChantierPhotogram.xml"),
                 "OrientationConique",
                 "OrientationConique"
             );


    ParseFile();
    CalcImCenter();


    DoTiePCenter();
    if (mCalcV)
    {
       CalcVitesse();
    }

    InitGrapheVois();
    TestRef();
    SauvOriFinal();
    SauvRel();

    std::cout << "PATC = " << mPatImCenter << "\n";
}




void  cAppli_Ori_Txt2Xml_main::InitGrapheVois()
{
    mBoxC._p0 = Pt2dr( 1e20, 1e20);
    mBoxC._p1 = Pt2dr(-1e20,-1e20);
    for (int aK=0 ; aK<int(mVCam.size()) ; aK++)
    {
       tSomVois & aSom = mGrVois.new_som(cAttrVoisSom(mVCam[aK]));
       mVSomVois.push_back(&aSom);
       mBoxC._p0.SetInf(POfSom(aSom));
       mBoxC._p1.SetSup(POfSom(aSom));
    }

	bool elise_x11 = false;
#ifdef ELISE_X11

	elise_x11 = true;
#endif

    if ((mSzV >0) && elise_x11)
    {
        mScaleV = mSzV / dist8(mBoxC.sz());
        mSzW = mBoxC.sz() * mScaleV + Pt2dr(mBordV,mBordV) * 2.0;
        mW = Video_Win::PtrWStd(round_ni(mSzW));
    }

    for (int aKS=0 ; aKS<int(mVSomVois.size()) ; aKS++)
       ShowSom(*(mVSomVois[aKS]),P8COL::red);

}

         // void VoisInitLine();

void cAppli_Ori_Txt2Xml_main::VoisInitDelaunay()
{
    Delaunay_Mediatrice
    (
      &(mVSomVois[0]),
      &(mVSomVois[0])+mVSomVois.size(),
       POfSomPtr,
       *this,
       1e10,
       (tSomVois **) 0
    );
}


void cAppli_Ori_Txt2Xml_main::VoisInitDelaunayCroist()
{

    std::vector<tSomVois *> aVQ1;
    std::vector<tSomVois *> aVQ2;
    for (tItSVois itS=mGrVois.begin(mSubAll) ; itS.go_on() ;itS++)
    {
        for (tItAVois itA= (*itS).begin(mSubAll) ; itA.go_on() ; itA++)
        {
             tSomVois & aS1 = (*itA).s1();
             tSomVois & aS2 = (*itA).s2();
             if ((*itA).IsOrientedNumCroissant())
             {
                ElFilo<tArcVois *> aF1;
                if (face_trigo(*itA,mSubAll,aF1))
                {

                   if (aF1.nb() == 3)
                   {
                       ElFilo<tArcVois*> aF2;
                       if (face_trigo((*itA).arc_rec(),mSubAll,aF2))
                       {
                           if (aF2.nb() == 3)
                           {
                               tSomVois & aQ1 =  SomDif(aF1,aS1,aS2);
                               tSomVois & aQ2 =  SomDif(aF2,aS1,aS2);
                               SegComp aSInit(POfSom(aS1),POfSom(aS2));
                               SegComp aSNew(POfSom(aQ1),POfSom(aQ2));

                               bool OK ;
                               aSInit.inter(SegComp::seg,aSNew,SegComp::seg,OK);
                               if (OK)
                               {
                                  aVQ1.push_back(&aQ1);
                                  aVQ2.push_back(&aQ2);
                               }
                           }
                       }
                   }
                }
             }
        }
    }

     for  (int aKq=0 ; aKq<int(aVQ1.size()) ; aKq++)
          AddArc(aVQ1[aKq],aVQ2[aKq],P8COL::green);



    // std::cout << "Viiissuu "<< mBoxC.sz() << " " << mScaleV << "\n"; getchar();
}

void  cAppli_Ori_Txt2Xml_main::InitCamera(cTxtCam & aCam,Pt3dr  aC,Pt3dr  aWPK)
{
    const cElDate & aDate =   aCam.mMTD->Date(true);
    const cElDate & aDate0 =   mVCam[0]->mMTD->Date(true);
    static bool allDateUnInit = true;
    allDateUnInit = allDateUnInit && aDate.IsNoDate() && aDate0.IsNoDate(); 

    {
       aCam.mOC->Externe().Centre() = aC;
       aCam.mTime =  (mMTDOnce | allDateUnInit)  ? aCam.mNum : aCam.mMTD->Date().DifInSec(mVCam[0]->mMTD->Date()) ;
               
       aCam.mOC->Externe().Time().SetVal(aCam.mTime);
       aCam.mC = aC;
    }

    // Calcul de la rotation
    if (mHasWPK)
    {
       // aCam.mOC->ConvOri().KnownConv().SetVal(eConvAngLPSDegre);
       aCam.mOC->ConvOri().KnownConv().SetVal(mConvOri);
       aCam.mOC->Externe().ParamRotation().CodageAngulaire().SetVal(aWPK);
       aCam.mWPK = aWPK;
    }
    if(EAMIsInit(&mAltiSol))
    {
        aCam.mOC->Externe().AltiSol().SetVal(mAltiSol);
    }
    if(EAMIsInit(&mProf))
    {
        aCam.mOC->Externe().AltiSol().SetVal(mProf);
    }
    MakeFileXML(*(aCam.mOC),aCam.mNameOri);
    aCam.mCam = CamOrientGenFromFile(aCam.mNameOri,mICNM);
}
/*
*/


void cAppli_Ori_Txt2Xml_main::ParseFile()
{
    std::cout << "Comment=[" << mComment<<"]\n";
    std::cout << "Format=[" << mFormat<<"]\n";
    cReadOri aReadApp(mComment,mFormat);
    ELISE_fp aFIn(mFilePtsIn.c_str(),ELISE_fp::READ);

    char * aLine;

    int aCpt = 0;
    
    const cMetaDataPhoto * aMTD0 = 0;
    while ((aLine = aFIn.std_fgets()))
    {
        if (aReadApp.Decode(aLine) && (aCpt>=mCptMin) && (aCpt<mCptMax))
        {
           {
              if (mNbCam==0) 
                 mHasWPK = aReadApp.IsDef(aReadApp.mWPK);
              ELISE_ASSERT(mHasWPK==aReadApp.IsDef(aReadApp.mWPK),"Incoherence in HasWPK");
           }
           cTxtCam  & aNewCam = *(new cTxtCam);
           mVCam.push_back(&aNewCam);
           aNewCam.mNum = mNbCam;
           aNewCam.mNameIm = mICNM->Assoc1To1(mKeyName2Image,aReadApp.mName,true);
           aNewCam.mNameOri = NameOrientation(mOriOut,aNewCam);



           const cMetaDataPhoto * aMTD=0;
           if ((!mMTDOnce) || (aMTD0==0))
           {
              aMTD = &cMetaDataPhoto::CreateExiv2(mDir+aNewCam.mNameIm);
              aMTD0 = aMTD;
           }
           else
               aMTD = aMTD0;

           aNewCam.mMTD =  aMTD;
           if (mAddCalib && (! EAMIsInit(&mFileCalib) ))
           {
              Pt2di aSz =  aMTD->XifSzIm();
              Pt2dr aPP = Pt2dr(aSz) / 2.0;

              mCIO.PP() = aPP;
              mCIO.F() = aMTD->FocPix();
              mCIO.SzIm() = aSz;
              mCIO.CalibDistortion()[0].ModRad().Val().CDist() = aPP;
           }

           aNewCam.mOC = new cOrientationConique(mOC0);
           if (mAddCalib)
           {
              if (mCalibByFile)
                 aNewCam.mOC->FileInterne().SetVal(mFileCalib);
              else
                 aNewCam.mOC->Interne().SetVal(mCIO);
           }

//===============================

           Pt3dr aC =  aReadApp.mPt;
           if (mCSC)
              aC = mCSC->Src2Cibl(aC);
           InitCamera(aNewCam,aC,mHasWPK  ? aReadApp.mWPK :Pt3dr(0,0,0));
           aNewCam.mPrio = aNewCam.mTime ;// + aNewCam.mNum * 1e-7;


           if (1)
           {
               if (mNbCam != 0)
               {
                   cTxtCam * aPrec = mVCam[mNbCam-1];
                   Pt3dr aV3 = aNewCam.mC - aPrec->mC;
                   Pt2dr aV2 (aV3.x,aV3.y);

                   double aTeta = angle(aV2);
                   aTeta = aTeta * (180/PI);
                   if (aTeta <0) aTeta += 360;
                   // std::cout  << "Annagle " <<  mod_real(aReadApp.mWPK.z - aTeta,360) << "\n";
               }
           }
           if (1)  
           {
               std::cout << "Read data for " << aNewCam.mNameIm  <<  "  NB=" << mNbCam  << " T=" <<  aNewCam.mCam->GetTime() << "\n";
               if (mNbCam != 0)
               {
                   cTxtCam * aPrec = mVCam[mNbCam-1];
                   std::cout << "    " << aNewCam.mC - aPrec->mC << "\n";
               }
           }


           if (EAMIsInit(&mImC) &&  (aNewCam.mNameIm == mImC))
           {
              mCamC = &aNewCam;
           }

           if (EAMIsInit(&mRefOri))
           {
               std::string aNameRef = NameOrientation(mRefOri,aNewCam);
               if (ELISE_fp::exist_file(aNameRef))
               {
                   aNewCam.mRefCam =  CamOrientGenFromFile(aNameRef,mICNM);
                   mVREF.push_back(&aNewCam);

               }
           }

           if (mNbCam==0)
              mPatternIm = aNewCam.mNameIm;
           else
              mPatternIm +=  "|"+aNewCam.mNameIm;

           mNbCam++;
        }
        aCpt++;
    }
    if (EAMIsInit(&mRefOri))
    {
        std::cout << "CMAC " << mCamC << "\n";
    }
    aFIn.close();

    std::sort(mVCam.begin(),mVCam.end(),TheCmp);
}

void cAppli_Ori_Txt2Xml_main::TestRef()
{
    if (mVREF.empty())
       return;

    for (int aKR=0 ; aKR<int(mVREF.size()) ; aKR++)
    {
        cTxtCam & aCam = *(mVREF[aKR]);
        if (aCam.mVIsCalc)
        {
           Pt3dr aV  = aCam.mV;
           ElRotation3D aR =  aCam.mRefCam->Orient();
           ElRotation3D aR2 =  aCam.mCam->Orient();
           double aRad = 180/PI;
           double aTeta = angle(Pt2dr(aV.x,aV.y)) ;
           std::cout << "xx" << aTeta * aRad << " " <<  (aR.teta01()-aTeta)*aRad << " " <<  (aR.teta01()-aR2.teta01())*aRad << "\n";

        }
    }
/*
    for (int aKR=0 ; aKR<int(mVREF.size()) ; aKR++)
    {
        cTxtCam & aCam0 = *(mVREF[aKR-1]);
        cTxtCam & aCam1 = *(mVREF[aKR]);
        std::cout << "REF " << aCam0.mNameIm  << " " <<  aCam1.mNameIm << "\n";
        ElMatrix<double> aM0 = aCam0.mRefCam->Orient().Mat();
        ElMatrix<double> aM1 = aCam1.mRefCam->Orient().Mat();

        ElRotation3D aR(Pt3dr(0,0,0),aM0*aM1.transpose(),true);
        ElRotation3D aR0 =  aCam0.mRefCam->Orient();

        double aRad = 180/PI;

        std::cout << aCam0.mWPK -aCam1.mWPK <<  " " << aR.teta02() *aRad<< " " << aR.teta12()*aRad << " " << aR.teta01()*aRad << "\n";

         std::cout << "xx" << aCam0.mWPK  << " " << aR0.teta02()*aRad << " " << aR0.teta12()*aRad << " "  << aR0.teta01()*aRad << "\n";
    }
*/
}

void cAppli_Ori_Txt2Xml_main::CalcImCenter()
{
    if (mCamC==0) return;

    mNbImC = ElMin(mNbImC,mNbCam);

    for (int aK1=0 ; aK1<mNbCam ; aK1++)
    {
        cTxtCam & aC1 = *(mVCam[aK1]);
        aC1.mPrio = euclid(aC1.mC-mCamC->mC);
    }
    std::vector<cTxtCam *> aVBIS = mVCam;
    std::sort(aVBIS.begin(),aVBIS.end(),TheCmp);
    for (int aK=0 ; aK<mNbImC ; aK++)
    {
        aVBIS[aK]->mSelC = true;
        if (aK!=0)
        {
           mPatImCenter += "|";
        }
        mPatImCenter += aVBIS[aK]->mNameIm;
    }
    if (mUseOnlyC)
    {
       std::vector<cTxtCam *>  aVSel;
       for (int aK1=0 ; aK1<mNbCam ; aK1++)
           if (mVCam[aK1]->mSelC)
              aVSel.push_back(mVCam[aK1]);

       mVCam = aVSel;
       mNbCam = mVCam.size();
    }
}

void cAppli_Ori_Txt2Xml_main::DoTiePCenter()
{
    if (mCamC==0) return;
    if (! EAMIsInit(&mSiftResol)) return;

    std::string aCom =    MM3DStr + std::string(" Tapioca ") + (EAMIsInit(&mSiftLowResol)?" MulScale ":" All ");

    aCom +=    std::string(" \"") + mPatImCenter + std::string("\"");

    if ( EAMIsInit(&mSiftLowResol))  aCom = aCom + std::string(" ") + ToString(mSiftLowResol) ;
    aCom = aCom + std::string(" ") + ToString(mSiftResol) ;

    system_call(aCom.c_str());
}

void cAppli_Ori_Txt2Xml_main::SauvRel()
{
    if (! EAMIsInit(&mNameCple))
       return;


   if (mAddDelaunay)
   {
        VoisInitDelaunay();
   }
   if (mAddDelaunayCroist)
   {
        VoisInitDelaunayCroist();
   }

   if (mLine > 0)
   {
       for (int aK1 = 0 ; aK1<int(mVCam.size()) ; aK1++)
       {
           int aK2Min = ElMax(0,aK1-mLine);
           int aK2Max = ElMin(int(mVCam.size())-1,aK1+mLine);
           for (int aK2=aK2Min ; aK2<aK2Max ; aK2++)
           {
                if (aK1 != aK2)
                   AddArc(mVSomVois[aK1],mVSomVois[aK2],P8COL::white);
           }
           
           std::cout << "TTttiim e " << mVSomVois[aK1]->attr().mCam->mTime << "\n";
       }
       //getchar();
   }

   cSauvegardeNamedRel  aRelIm;    

   for (tItSVois itS=mGrVois.begin(mSubAll) ; itS.go_on() ;itS++)
   {
       for (tItAVois itA= (*itS).begin(mSubAll) ; itA.go_on() ; itA++)
       {
             tSomVois & aS1 = (*itA).s1();
             tSomVois & aS2 = (*itA).s2();
             const cTxtCam * aC1 = aS1.attr().mCam;
             const cTxtCam * aC2 = aS2.attr().mCam;
             cCpleString aCpl(aC1->mNameIm,aC2->mNameIm);
             aRelIm.Cple().push_back(aCpl);
       }
   }
  

   MakeFileXML(aRelIm,mDir+mNameCple);
/*
    for (int aK1=0 ; aK1<mNbCam ; aK1++)
    {
        for (int aK2=0 ; aK2<mNbCam ; aK2++)
        {
           if (aK1 != aK2)
           {
               bool Ok = true;
               const cTxtCam & aC1 = *(mVCam[aK1]);
               const cTxtCam & aC2 = *(mVCam[aK2]);
               Pt3dr aP1 = aC1.mC;
               Pt3dr aP2 = aC2.mC;
               if (EAMIsInit(&mDistNeigh))
                  Ok = Ok && (euclid(aP1-aP2)<mDistNeigh);

               if (Ok)
               {
                   cCpleString aCpl(aC1.mNameIm,aC2.mNameIm);
                   aRelIm.Cple().push_back(aCpl);
               }
            }
        }
    }
*/
}


//================================================

int Ori_Txt2Xml_main(int argc,char ** argv)
{
    MMD_InitArgcArgv(argc,argv,3);
    cAppli_Ori_Txt2Xml_main(argc,argv);
    BanniereMM3D();
    return 0;
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
