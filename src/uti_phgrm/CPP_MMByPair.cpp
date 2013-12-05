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



class cAppliClipChantier : public cAppliWithSetImage
{
    public :
        cAppliClipChantier(int argc,char ** argv);

        std::string  mNameMasterIm;
        Box2di       mBox;
        cImaMM *  mMasterIm;
};


class cAppliMMByPair : public cAppliWithSetImage
{
    public :
      cAppliMMByPair(int argc,char ** argv);
      int Exe();
    private :
      void DoMDT();
      void DoCorrelAndBasculeStd();
      void DoCorrelAndBasculeEpip();
      std::string MatchEpipOnePair(cImaMM & anI1,cImaMM & anI2 );
      void DoFusion();

      std::string mDo;
      int mZoom0;
      int mZoomF;
      bool mParalMMIndiv;
      bool mDelaunay;
      bool mAddMMImSec;
      int mDiffInStrip;
      bool mStripIsFirt;
      std::string  mPairByStrip;
      std::string  mDirBasc;
      int          mNbStep;
      double       mIntIncert;
      bool         mSkipCorDone;
      eTypeMMByP   mType;
      std::string  mStrType;
      bool         mModeHelp;
      bool         mByMM1P;
      Box2di       mBoxOfImage;
      std::string  mImageOfBox;
      std::string  mStrQualOr;
      eTypeQuality mQualOr;
};

/*****************************************************************/
/*                                                               */
/*                            cImaMM                             */
/*                                                               */
/*****************************************************************/

int TiffDev_main(int argc,char ** argv)
{
    std::string aNameFile;
    int aNbChan = -1 ;
    bool B16 = true;
    bool ExigNoCompr = false;

    ElInitArgMain
    (
        argc,argv,
        LArgMain()  << EAMC(aNameFile,"A Name File"),
        LArgMain()  << EAM(aNbChan,"NbChan",true,"Nb Channel")
                    << EAM(B16,"16B",true,"Conserv in 16 Bits if possible")
                    << EAM(ExigNoCompr,"ENC",true,"Exig No Compr")
    );

    Tiff_Im::StdConvGen(aNameFile,aNbChan,B16,ExigNoCompr);

    return 0;
}

void Paral_Tiff_Dev
    (
         const std::string & aDir,
         const std::vector<std::string> & aLFile,
         int                            aNbChan,
         bool                           Cons16B
    )
{
    std::list<std::string> aLCom;
    for (std::vector<std::string>::const_iterator itS=aLFile.begin(); itS!=aLFile.end(); itS++)
    {
         std::string aCom =    MMBinFile(MM3DStr) + " TifDev " + aDir+*itS 
                              + " NbChan=" + ToString(aNbChan)
                              + " 16B=" + ToString(Cons16B)
                            ;
         aLCom.push_back(aCom);
         // std::cout << aCom << "\n";
    }

    cEl_GPAO::DoComInParal(aLCom);
}


/*****************************************************************/
/*                                                               */
/*                            cImaMM                             */
/*                                                               */
/*****************************************************************/

cImaMM::cImaMM(const std::string & aName,cAppliWithSetImage & anAppli) :
   mNameIm     (aName),
   mBande      (""),
   mNumInBande (-1),
   mCam        (anAppli.CamOfName(mNameIm)),
   mC3         (mCam->PseudoOpticalCenter()),
   mC2         (mC3.x,mC3.y),
   mAppli      (anAppli),
   mPtrTiff    (0)
{
}

Tiff_Im  &   cImaMM::Tiff()
{
    if (mPtrTiff==0)
    {
        std::string aFullName =  mAppli.Dir() + mNameIm;
        mPtrTiff = new Tiff_Im(Tiff_Im::UnivConvStd(aFullName.c_str()));
    }
    return *mPtrTiff;
}

/*****************************************************************/
/*                                                               */
/*                      cAppliWithSetImage                       */
/*                                                               */
/*****************************************************************/

static std::string aBlank(" ");

void cAppliWithSetImage::Develop(bool EnGray,bool Cons16B)
{
    Paral_Tiff_Dev(mDir,*mSetIm,(EnGray?1:3),Cons16B);
}

cAppliWithSetImage::cAppliWithSetImage(int argc,char ** argv,int aFlag)  :
   mSym       (true),
   mShow      (false),
   mPb        (""),
   mAverNbPix (0.0)
{
   if (argc<2)
   {
      mPb = "Not Enough Arg in cAppliWithSetImage";
      return;
   }


   mFullName = argv[0];
#if (ELISE_windows)
        replace( mFullName.begin(), mFullName.end(), '\\', '/' );
#endif
   SplitDirAndFile(mDir,mPat,mFullName);



   mICNM = cInterfChantierNameManipulateur::BasicAlloc(mDir);
   mSetIm = mICNM->Get(mPat);


   if (aFlag & FlagDev16BGray) Develop(true,true);
   if (aFlag & FlagDev8BGray) Develop(true,false);


   if (mSetIm->size()==0)
   {
       std::cout << "For Pat= [" << mPat << "]\n";
       ELISE_ASSERT(false,"Empty pattern");
   }

   mOri = argv[1];
   mKeyOri =  "NKS-Assoc-Im2Orient@-" + mOri;

   for (int aKV=0 ; aKV<int(mSetIm->size()) ; aKV++)
   {
       const std::string & aName = (*mSetIm)[aKV];
       mImages.push_back(new cImaMM(aName,*this));
       mDicIm[aName] = mImages.back();
       Pt2di  aSz =  mImages.back()->Tiff().sz();
       mAverNbPix += double(aSz.x) * double(aSz.y);  
   }
   mAverNbPix /= mSetIm->size();
}

//  aSz * 2 ^ (LogDeZoom * 2) = mAverNbPix;
int  cAppliWithSetImage::DeZoomOfSize(double aSz) const
{
    double aRatio = mAverNbPix / aSz;
    double aRL2 = log2(aRatio) / 2;
    int aL2 = ElMax(0,round_ni(aRL2));
    return 1 << aL2;
}



const std::string & cAppliWithSetImage::Dir() const
{
   return mDir;
}
void cAppliWithSetImage::VerifAWSI()
{
   ELISE_ASSERT(mPb=="",mPb.c_str());
}

CamStenope * cAppliWithSetImage::CamOfName(const std::string & aNameIm)
{
   if (mOri=="NONE")
   {
      cOrientationConique anOC = StdGetFromPCP(Basic_XML_MM_File("Template-OrCamAngWithInterne.xml"),OrientationConique);
     
      Tiff_Im aTF = Tiff_Im::StdConv(mDir+aNameIm);

      Pt2dr  aSz = Pt2dr(aTF.sz());
      anOC.Interne().Val().F() = euclid(aSz);
      anOC.Interne().Val().PP() = aSz/2.0;
      anOC.Interne().Val().SzIm() = round_ni(aSz);
      anOC.Interne().Val().CalibDistortion()[0].ModRad().Val().CDist() =  aSz/2.0;

      MakeFileXML(anOC,Basic_XML_MM_File("TmpCam.xml"));
      // return Std_Cal_From_File(Basic_XML_MM_File("TmpCam.xml"));
      return CamOrientGenFromFile(Basic_XML_MM_File("TmpCam.xml"),0);


     // return ;
   }
   std::string aNameOri =  mICNM->Assoc1To1(mKeyOri,aNameIm,true);
   return   CamOrientGenFromFile(aNameOri,mICNM);
}

void  cAppliWithSetImage::MakeStripStruct(const std::string & aPairByStrip,bool StripIsFirst)
{

  cElRegex anAutom(aPairByStrip.c_str(),10);
  std::string aExpStrip = StripIsFirst ? "$1" : "$2";
  std::string aExpNumInStrip = StripIsFirst ? "$2" : "$1";

  for (int aKI=0;  aKI<int(mImages.size()) ; aKI++)
  {
      cImaMM & anI = *(mImages[aKI]);
      
      std::string aBande = MatchAndReplace(anAutom,anI.mNameIm,aExpStrip);
      std::string aNumInBande = MatchAndReplace(anAutom,anI.mNameIm,aExpNumInStrip);

      bool OkNum = FromString(anI.mNumInBande,aNumInBande);
      ELISE_ASSERT(OkNum,"Num in bande is not numeric");
      if (mShow)
         std::cout << " Strip " << anI.mNameIm << " " << aBande <<  ";;" << anI.mNumInBande << "\n";
      anI.mBande = aBande;
  }
}

Pt2dr PtOfcImaMM   (const cImaMM & aCam) {return aCam.mC2;}
Pt2dr PtOfcImaMMPtr(const cImaMM * aCam) {return PtOfcImaMM(*aCam);}

void cAppliWithSetImage::AddDelaunayCple()
{
  Delaunay_Mediatrice
  (
      &(mImages[0]),
      &(mImages[0])+mImages.size(),
       PtOfcImaMMPtr,
       *this,
       1e10,
       (cImaMM **) 0
  );

}

void cAppliWithSetImage::AddCoupleMMImSec()
{
      std::string aCom = MMDir() + "bin/mm3d AperoChImSecMM "
                         + aBlank + mFullName 
                         + aBlank + mOri;
      System(aCom);
      for (int aKI=0 ; aKI<int(mSetIm->size()) ; aKI++)
      {
          const std::string & aName1 = (*mSetIm)[aKI];
          cImSecOfMaster aISOM = StdGetISOM(mICNM,aName1,mOri);
          const std::list<std::string > *  aLIm = GetBestImSec(aISOM);
          for (std::list<std::string>::const_iterator itN=aLIm->begin(); itN!=aLIm->end() ; itN++)
          {
              const std::string & aName2 = *itN;
              AddPair(ImOfName(aName1),ImOfName(aName2));
          }
      }

}

void cAppliWithSetImage::ComputeStripPair(int aDif)
{
    for (int aK1=0 ; aK1<int(mImages.size()) ; aK1++)
    {
        cImaMM & anI1 = *(mImages[aK1]);
        for (int aK2=0 ; aK2<int(mImages.size()) ; aK2++)
        {
            cImaMM & anI2 = *(mImages[aK2]);
            if (anI1.mBande==anI2.mBande)
            {
               int aN1 = anI1.mNumInBande;
               int aN2 = anI2.mNumInBande;
               if ((aN1>aN2) && (aN1<=aN2+aDif))
               {
                    bool OK = true;
                    if (OK && EAMIsInit(&mTetaBande))
                    {
                       Pt3dr aV3 = anI2.mCam->PseudoOpticalCenter() - anI1.mCam->PseudoOpticalCenter();
                       Pt2dr aV2(aV3.x,aV3.y);
                       aV2 = vunit(aV2); 
                       Pt2dr aDirS = Pt2dr::FromPolar(1,mTetaBande * (PI/180));
                       double aTeta = ElAbs(angle_de_droite(aV2,aDirS));
                       OK = (aTeta < (PI/4));
                    }

                    if (OK)
                    {
 /// std::cout << "MMByP " << anI1.mNameIm << " " << anI2.mNameIm << "\n";
                        AddPair(&anI1,&anI2);
                    }
               }
            }
        }
    }
}


void cAppliWithSetImage::operator()(cImaMM* anI1,cImaMM* anI2,bool)   // Delaunay call back
{
     AddPair(anI1,anI2);
}

void cAppliWithSetImage::AddPair(cImaMM * anI1,cImaMM * anI2)
{
    if (anI1>anI2) 
       ElSwap(anI1,anI2);
    AddPairASym(anI1,anI2);
    if (mSym)
       AddPairASym(anI2,anI1);
}

void cAppliWithSetImage::AddPairASym(cImaMM * anI1,cImaMM * anI2)
{
    tPairIm aPair(anI1,anI2);

    if (mPairs.find(aPair) != mPairs.end())
       return;
    
    mPairs.insert(aPair);

    if (mShow)
       std::cout << "Add Pair " << anI1->mNameIm << " " << anI2->mNameIm << "\n";
}

void cAppliWithSetImage::DoPyram()
{
    std::string aCom =    MMBinFile(MM3DStr) + " MMPyram " + QUOTE(mFullName) + " " + mOri;
    if (mShow)
       std::cout << aCom << "\n";
    System(aCom);
}

cImaMM * cAppliWithSetImage::ImOfName(const std::string & aName)
{
    cImaMM * aRes = mDicIm[aName];
    if (aRes==0)
    {
       std::cout << "For name = " << aName << "\n";
       ELISE_ASSERT(false,"Cannot get image");
    }
    return aRes;
}
/*****************************************************************/
/*                                                               */
/*              cAppliClipChantier                               */
/*                                                               */
/*****************************************************************/


cAppliClipChantier::cAppliClipChantier(int argc,char ** argv) :
    cAppliWithSetImage (argc-1,argv+1,0)
{
  std::string aPrefClip = "Cliped_";
  std::string aOriOut;
  double      aMinSz = 500;

  ElInitArgMain
  (
        argc,argv,
        LArgMain()  << EAMC(mFullName,"Full Name (Dir+Pattern)")
                    << EAMC(mOri,"Orientation")
                    << EAMC(mNameMasterIm,"Image corresponding to the box")
                    << EAMC(mBox,"Box to clip"),
        LArgMain()  << EAM(aPrefClip,"PrefCliped","def= Cliped")
                    << EAM(aOriOut,"OriOut","Out Orientation, def = input")
                    << EAM(aMinSz,"MinSz","Min sz to select cliped def = 500")
   );

   if (!EAMIsInit(&aOriOut)) 
      aOriOut = mOri;

   mMasterIm  =  ImOfName(mNameMasterIm);

   double aZ = mMasterIm->mCam->GetAltiSol();

   Pt2di aCornIm[4];
   mBox.Corners(aCornIm);

   std::vector<Pt3dr>  mVIm;

   for (int aK=0 ; aK < 4 ; aK++)
   {
       mVIm.push_back(mMasterIm->mCam->ImEtZ2Terrain(Pt2dr(aCornIm[aK]),aZ));
   }

   for (int aKIm = 0 ; aKIm <int(mImages.size()) ; aKIm++)
   {
       cImaMM & anI = *(mImages[aKIm]);
       CamStenope * aCS = anI.mCam;
       // Pt2dr aP1(0,0);
       // Pt2dr aP0 = Pt2dr(aCS->Sz());
       Pt2di aP0(1e9,1e9);
       Pt2di aP1(-1e9,-1e9);

       for (int aKP=0 ; aKP < 4 ; aKP++)
       {
           Pt2di aPIm = round_ni(aCS->R3toF2(mVIm[aKP]));
           aP0.SetInf(aPIm);
           aP1.SetSup(aPIm);
       }
       Box2di aBoxIm(aP0,aP1);
       Box2di aBoxCam(Pt2di(0,0),aCS->Sz());

       if (! InterVide(aBoxIm,aBoxCam))
       {
           Box2di aBoxRes = Inf(aBoxIm,aBoxCam);
           Pt2di aDec = aBoxRes._p0;
           Pt2di aSZ = aBoxRes.sz();
           if ((aSZ.x>aMinSz) && (aSZ.y>aMinSz))
           {
                std::cout << "Box " << anI.mNameIm << aDec << aSZ << "\n";
           
                std::string aNewIm = aPrefClip + anI.mNameIm;
                cOrientationConique  aCO = aCS->StdExportCalibGlob();

                std::string aNameOut =  mICNM->Assoc1To1("NKS-Assoc-Im2Orient@-" + aOriOut,aNewIm,true);
                cCalibrationInternConique * aCIO = aCO.Interne().PtrVal();
                cCalibrationInterneRadiale * aMR =aCIO->CalibDistortion().back().ModRad().PtrVal();
                if (1)
                {
                                ElAffin2D aM2C0 = Xml2EL(aCO.OrIntImaM2C());
                                ElAffin2D  aM2CCliped = ElAffin2D::trans(-Pt2dr(aDec))   * aM2C0;
                                aCO.OrIntImaM2C().SetVal(El2Xml(aM2CCliped));
                // aCO.Interne().Val().SzIm() = aSZ;
                }
                else
                {
                     if (aMR)
                     {
                         aCIO->PP() = aCIO->PP() - Pt2dr(aDec);
                         aMR->CDist() = aMR->CDist() - Pt2dr(aDec);
                         aCO.Interne().Val().SzIm() = aSZ;
                     }
                     else
                     {
                         cOrIntGlob anOIG;
                         anOIG.Affinite() = El2Xml(ElAffin2D::trans(-Pt2dr(aDec)));
                         anOIG.C2M() = false;
                         aCO.Interne().Val().OrIntGlob().SetVal(anOIG);
                     }
                }
                MakeFileXML(aCO,aNameOut);


                std::string aCom =      MMBinFile(MM3DStr) 
                                     + " ClipIm "
                                     + mDir + anI.mNameIm + aBlank
                                     + ToString(aDec) + aBlank
                                     + ToString(aSZ) + aBlank
                                     + " Out=" + aNewIm;

                std::cout << aCom << "\n";
                System(aCom);
            }
       }
       
   }
   
}

/*****************************************************************/
/*                                                               */
/*              clip_im                                          */
/*                                                               */
/*****************************************************************/

int ClipIm_main(int argc,char ** argv)
{

    std::string aNameIn;
    std::string aNameOut;
    Pt2di P0;
    Pt2di Sz;

    ElInitArgMain
    (
        argc,argv,
        LArgMain()  << EAM(aNameIn)
                    << EAM(P0)
                    << EAM(Sz)  ,
        LArgMain()  << EAM(aNameOut,"Out",true)
    );


    Tiff_Im tiff = Tiff_Im::BasicConvStd(aNameIn.c_str());


    if (aNameOut == "")
    {
       if (IsPostfixed(aNameIn))
          aNameOut = StdPrefix(aNameIn)+std::string("_Clip.tif");
       else
          aNameOut = aNameIn+std::string("_Clip.tif");
    }

    L_Arg_Opt_Tiff aLArg = Tiff_Im::Empty_ARG;
    aLArg = aLArg + Arg_Tiff(Tiff_Im::ANoStrip());


    Tiff_Im TiffOut  =     (tiff.phot_interp() == Tiff_Im::RGBPalette)  ?
                           Tiff_Im
                           (
                              aNameOut.c_str(),
                              Sz,
                              tiff.type_el(),
                              Tiff_Im::No_Compr,
                              tiff.pal(),
                              aLArg
                          )                    :
                           Tiff_Im
                           (
                              aNameOut.c_str(),
                              Sz,
                              tiff.type_el(),
                              Tiff_Im::No_Compr,
                              tiff.phot_interp(),
                              aLArg
                          );

    ELISE_COPY
    (
         TiffOut.all_pts(),
         trans(tiff.in(0),P0),
         TiffOut.out()
    );

     return 0;
}



/*****************************************************************/
/*                                                               */
/*              cAppliMMByPair                                   */
/*                                                               */
/*****************************************************************/

cAppliMMByPair::cAppliMMByPair(int argc,char ** argv) :
    cAppliWithSetImage (argc-2,argv+2,FlagDev16BGray),
    mDo           ("PMCF"),
    mZoom0        (64),
    mZoomF        (1),
    mParalMMIndiv (false),
    mDelaunay     (false),
    mAddMMImSec      (false),
    mDiffInStrip  (1),
    mStripIsFirt  (true),
    mDirBasc      ("MTD-Nuage"),
    mIntIncert    (1.25),
    mSkipCorDone  (false),
    mByMM1P       (true),
    mStrQualOr    ("Low")
{
  if (argc>=2)
  {
     ELISE_ASSERT(argc >= 2,"Not enough arg");
     mStrType = argv[1];
     StdReadEnum(mModeHelp,mType,mStrType,eNbTypeMMByP);
  }



  ElInitArgMain
  (
        argc,argv,
        LArgMain()  << EAMC(mStrType,"Type in enumerated values")
                    << EAMC(mFullName,"Full Name (Dir+Pattern)")
                    << EAMC(mOri,"Orientation"),
        LArgMain()  << EAM(mZoom0,"Zoom0",true,"Zoom Init, Def=64")
                    << EAM(mZoomF,"ZoomF",true,"Zoom Final, Def=1")
                    << EAM(mDelaunay,"Delaunay","Add delaunay edges in pair to macth, Def=False")
                    << EAM(mAddMMImSec,"MMImSec","Add pair from AperoChImSecMM,  Def=true in mode Statute")
                    << EAM(mPairByStrip,"ByStrip",true,"Pair in same strip , first () : strip, second () : num in strip (or reverse with StripIsFisrt)")
                    << EAM(mStripIsFirt,"StripIsFisrt",true,"If true : first expr is strip, second is num in strip Def=true")
                    << EAM(mDiffInStrip,"DeltaStrip",true,"Delta in same strip (Def=1,apply with mPairByStrip)")
                    << EAM(mSym,"Sym",true,"Symetrise all pair (Def=true)")
                    << EAM(mShow,"Show",true,"Show details (def = false))")
                    << EAM(mIntIncert,"Inc",true,"Uncertaincy interval (def  = 1.25) ")
                    << EAM(mTetaBande,"TetaStrip",true,"If used, cut strip when dir of vector > 45 degre from TetaStrip")
                    << EAM(mSkipCorDone,"SMD",true,"Skip Matching When Already Done (Def=false)")
                    << EAM(mDo,"Do",true,"Step to Do in [Pyram,MetaData,Correl,Fusion], Def \"PMCF\" (i.e. All Step)")
                    << EAM(mByMM1P,"ByMM1P",true,"Do match using new MM1P , def = true")
                    << EAM(mImageOfBox,"ImOfBox",true,"Image to define box for MTD (test purpose to limit size of result)")
                    << EAM(mBoxOfImage,"BoxOfIm",true,"Associated to ImOfBox, def = full")
                    << EAM(mParalMMIndiv,"ParMMI",true,"If true each MM if // (\" expert\" option, Def=false currently)")
                    << EAM(mStrQualOr,"QualOr",true,"Quality orient (in High, Average, Low, Def= Low)",eSAM_None,ListOfVal(eNbTypeQual,"eQual_"))
  );
  mQualOr = Str2eTypeQuality("eQual_"+mStrQualOr);
  if (! EAMIsInit(&mAddMMImSec))
     mAddMMImSec = (mType==eStatute);
  if (mModeHelp) 
      exit(0);
  if (! EAMIsInit(&mZoom0))
     mZoom0 =  DeZoomOfSize(7e4);
  VerifAWSI();

  if (EAMIsInit(&mPairByStrip))
  {
      MakeStripStruct(mPairByStrip,mStripIsFirt);
      ComputeStripPair(mDiffInStrip);
  }
  if (mDelaunay)
     AddDelaunayCple();
  if (mAddMMImSec)
     AddCoupleMMImSec();

  mNbStep = round_ni(log2(mZoom0/double(mZoomF))) + 3 ;
}

void cAppliMMByPair::DoCorrelAndBasculeEpip()
{
   std::list<std::string> aLCom;
   for ( tSetPairIm::const_iterator itP= mPairs.begin(); itP!=mPairs.end() ; itP++)
   {
        cImaMM & anI1 = *(itP->first);
        cImaMM & anI2 = *(itP->second);
        if (anI1.mNameIm < anI2.mNameIm)
        {
             std::string aCom =  MatchEpipOnePair(anI1,anI2);
             if (aCom != "")
                aLCom.push_back(aCom);
        }
   }
   if (mParalMMIndiv)
   {
        cEl_GPAO::DoComInSerie(aLCom);
   }
   else
   {
        cEl_GPAO::DoComInParal(aLCom);
   }
}

std::string cAppliMMByPair::MatchEpipOnePair(cImaMM & anI1,cImaMM & anI2 )
{
     bool mByEpi = true;
     std::string aMatchCom =     MMBinFile(MM3DStr)
                         +  " MM1P"
                         +  aBlank + anI1.mNameIm
                         +  aBlank + anI2.mNameIm
                         +  aBlank + mOri
                         +  " ZoomF=" + ToString(mZoomF)
                         +  " CreateE=" + ToString(mByEpi)
                         +  " InParal=" + ToString(mParalMMIndiv)
                         +  " QualOr=" +  mStrQualOr
                      ;

     if (mType == eGround)
       aMatchCom = aMatchCom + " BascMTD=MTD-Nuage/NuageImProf_LeChantier_Etape_1.xml ";

     std::string aNameIm1 = anI1.mNameIm;
     std::string aNameIm2 = anI2.mNameIm;
     if (mByEpi)
     {
        cCpleEpip * aCpleE = StdCpleEpip(mDir,mOri,aNameIm1,aNameIm2);
        aNameIm1 = aCpleE->LocNameImEpi(aNameIm1);
        aNameIm2 = aCpleE->LocNameImEpi(aNameIm2);
     }




     std::vector<std::string> aBascCom;
     std::vector<std::string> aVTarget;
     bool AllDoneMatch = true;

     for (int aK= 0 ; aK< 2 ; aK++)
     {
         std::string aDirMatch = mDir + LocDirMec2Im((aK==0) ? aNameIm1:aNameIm2,(aK==0) ? aNameIm2:aNameIm1);
         std::string aNuageIn =  aDirMatch          + std::string("NuageImProf_Chantier-Ori_Etape_Last.xml");
         AllDoneMatch  = AllDoneMatch && ELISE_fp::exist_file(aNuageIn);
         


/*
         std::string aNuageGeom =    mDir +  std::string("MTD-Nuage/NuageImProf_LeChantier_Etape_1.xml");
         std::string aNuageTarget =  mDir +  std::string("MTD-Nuage/Basculed-") 
                                          + ((aK==0) ? anI1.mNameIm : anI2.mNameIm ) 
                                          + "-" + ((aK==0) ? anI2.mNameIm :anI1.mNameIm) + ".xml";

 
         AllDoneMatch = AllDoneMatch && ELISE_fp::exist_file(aNuageIn);
*/
     }

     // std::cout << aMatchCom << "\n";
     if ((!AllDoneMatch) || (! mSkipCorDone))
        return aMatchCom;

     return "";
}




void cAppliMMByPair::DoCorrelAndBasculeStd()
{
   for ( tSetPairIm::const_iterator itP= mPairs.begin(); itP!=mPairs.end() ; itP++)
   {
        cImaMM & anI1 = *(itP->first);
        cImaMM & anI2 = *(itP->second);

   // ====   Correlation =========================

       bool DoneCor = false;
       if (mSkipCorDone)
       {
           std::string aFile = mDir + "MEC2Im-" + anI1.mNameIm + "-" + anI2.mNameIm + "/MM_Avancement_LeChantier.xml";

           if (ELISE_fp::exist_file(aFile))
           {
                 cMM_EtatAvancement anEAv = StdGetFromMM(aFile,MM_EtatAvancement);
                 DoneCor = anEAv.AllDone();
           }

           // std::cout << "DOCCC " << aFile << " " << Done << "\n";
       }

       if (! DoneCor)
       {
           std::string aComCor =    MMBinFile("MICMAC")
                                 +  XML_MM_File("MM-Param2Im.xml")
                                 +  std::string(" WorkDir=") + mDir          + aBlank
                                 +  std::string(" +Ori=") + mOri + aBlank
                                 +  std::string(" +Im1=")    + anI1.mNameIm  + aBlank
                                 +  std::string(" +Im2=")    + anI2.mNameIm  + aBlank
                                 +  std::string(" +Zoom0=")  + ToString(mZoom0)  + aBlank
                                 +  std::string(" +ZoomF=")  + ToString(mZoomF)  + aBlank
                               ;

           if (EAMIsInit(&mIntIncert))
              aComCor = aComCor + " +MulZMax=" +ToString(mIntIncert);

           if (mShow)
              std::cout << aComCor << "\n";
           System(aComCor);
       }

   // ====   Bascule =========================

       std::string aPreFileBasc =   mDir + mDirBasc +  "/Basculed-"+ anI1.mNameIm + "-" + anI2.mNameIm ;
       bool DoneBasc = false;

       if (mSkipCorDone)
       {
            std::string aFileBasc = aPreFileBasc + ".xml";
            if (ELISE_fp::exist_file(aFileBasc))
            {
                DoneBasc = true;
            }
       }

       if (! DoneBasc)
       {

            std::string aComBasc =    MMBinFile(MM3DStr) + " NuageBascule "
                                    + mDir+ "MEC2Im-" + anI1.mNameIm + "-" +  anI2.mNameIm + "/NuageImProf_LeChantier_Etape_" +ToString(mNbStep)+".xml "
                                    + mDir + mDirBasc + "/NuageImProf_LeChantier_Etape_1.xml "
                                    + aPreFileBasc + " "
                                 ;
                             //  + mDir + mDirBasc +  "/Basculed-"+ anI1.mNameIm + "-" + anI2.mNameIm + " "
                             
            if (mShow)
               std::cout  << aComBasc << "\n";
           System(aComBasc);
       }

   }
}

/*
void cAppliMMByPair::DoBascule()
{
   for ( tSetPairIm::const_iterator itP= mPairs.begin(); itP!=mPairs.end() ; itP++)
   {
        cImaMM & anI1 = *(itP->first);
        cImaMM & anI2 = *(itP->second);
        std::string aCom =    MMBinFile(MM3DStr) + " NuageBascule "
                             + mDir+ "MEC2Im-" + anI1.mNameIm + "-" +  anI2.mNameIm + "/NuageImProf_LeChantier_Etape_" +ToString(mNbStep)+".xml "
                             + mDir + mDirBasc + "/NuageImProf_LeChantier_Etape_1.xml "
                             + mDir + mDirBasc +  "/Basculed-"+ anI1.mNameIm + "-" + anI2.mNameIm + " "
                             
                            ;
        if (mShow)
           std::cout  << aCom << "\n";
        System(aCom);
   }
}
*/

void cAppliMMByPair::DoFusion()
{
    std::string aCom =    MMBinFile(MM3DStr) + " MergeDepthMap "
                       +   XML_MM_File("Fusion-MMByP.xml") + aBlank
                       +   "  WorkDirPFM=" + mDir + mDirBasc + "/ ";
    if (mShow)
       std::cout  << aCom << "\n";
    System(aCom);
}


void cAppliMMByPair::DoMDT()
{
   std::string aCom =     MMBinFile("MICMAC")
                       +  XML_MM_File("MM-GenMTDNuage.xml")
                       +  std::string(" WorkDir=") + mDir          + aBlank
                       +  " +PatternAllIm=" +  mPat + aBlank
                       +  std::string(" +Ori=") + mOri + aBlank
                       +  std::string(" +Zoom=")  + ToString(mZoomF)  + aBlank
                       +  std::string(" +DirMEC=")  + mDirBasc  + aBlank
                    ;

   if (EAMIsInit(&mImageOfBox))
   {
        Box2di aBox;
        if (EAMIsInit(&mBoxOfImage))
        {
           aBox = mBoxOfImage;
        }
        else
        {
           cImaMM * anIma = ImOfName(mImageOfBox);
           aBox = Box2di(Pt2di(0,0),anIma->Tiff().sz());
        }
        aCom =   aCom
                  + " +WithBox=true"
                  + std::string(" +ImIncluse=") + mImageOfBox
                  + std::string(" +X0=") + ToString(aBox._p0.x)
                  + std::string(" +Y0=") + ToString(aBox._p0.y)
                  + std::string(" +X1=") + ToString(aBox._p1.x)
                  + std::string(" +Y1=") + ToString(aBox._p1.y)
              ;
   }

   System(aCom);
 
   std::string aStrN = mDir+mDirBasc+"/NuageImProf_LeChantier_Etape_1.xml";
   cXML_ParamNuage3DMaille aNuage = StdGetFromSI(aStrN,XML_ParamNuage3DMaille);
   aNuage.PN3M_Nuage().Image_Profondeur().Val().OrigineAlti() = 0;
   aNuage.PN3M_Nuage().Image_Profondeur().Val().ResolutionAlti() = 1;
   MakeFileXML(aNuage,aStrN);



   std::string aStrZ = mDir+mDirBasc+"/Z_Num1_DeZoom"+ToString(mZoomF)+ "_LeChantier.xml";
   cFileOriMnt aFileZ = StdGetFromPCP(aStrZ,FileOriMnt);
   aFileZ.OrigineAlti() = 0;
   aFileZ.ResolutionAlti() = 1;
   MakeFileXML(aFileZ,aStrZ);
}



int cAppliMMByPair::Exe()
{
  
   if (BoolFind(mDo,'P') && ((!mByMM1P) || (mQualOr= eQual_Low)))
   {
      DoPyram();
   }
   if (BoolFind(mDo,'M') && (mType == eGround))
   {
      DoMDT();
   }
   if (BoolFind(mDo,'C'))
   {
      if (mByMM1P)
      {
         DoCorrelAndBasculeEpip();
      }
      else
      {
         DoCorrelAndBasculeStd();
      }
   }
/*
   if (BoolFind(mDo,'F'))
      DoFusion();
*/
   return 1;
}


int MMByPair_main(int argc,char ** argv)
{
   MMD_InitArgcArgv(argc,argv);
   cAppliMMByPair anAppli(argc,argv);


   int aRes = anAppli.Exe();
   BanniereMM3D();
   return aRes;
}


int ChantierClip_main(int argc,char ** argv)
{
   MMD_InitArgcArgv(argc,argv);
   cAppliClipChantier anAppli(argc,argv);


   BanniereMM3D();

    return 1;
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
