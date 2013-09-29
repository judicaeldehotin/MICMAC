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
#include "../src/uti_phgrm/MICMAC/MICMAC.h"


namespace NS_ParamMICMAC
{

class cQckInterpolEpip;
class cCensusGr;
class cOnePCGr;


static int VX[4] = {1,1,0,-1};
static int VY[4] = {0,1,1,1};

class cQckInterpolEpip
{
    public :
        cQckInterpolEpip(float X) :
            mX0     (round_down(X)) ,
            mPds1   (X-mX0),
            mPds0   (1-mPds1)
        {
        } 

        int mX0;
        float mPds1;
        float mPds0;

         inline double  GetVal(float *aV)
         {
              return mPds0 * aV[0] + mPds1 * aV[1];
         }

         inline double  GetVal(float **aV, Pt2di aP)
         {
              float * aL = aV[aP.y] + aP.x + mX0;
              return mPds0 * aL[0] + mPds1 * aL[1];
         }
        
};

class cSomGr
{
     public :
        cSomGr(const Pt2di & aV,const int & aP,const int & aNum) :
             mV   (aV),
             mP   (aP),
             mNum (aNum),
             mFlag(1<<aNum)
        {
        }

       Pt2di mV;
       int   mP;
       int   mNum;
       int   mFlag;

};

class cOnePCGr
{
    friend class cCensusGr;
    public :
        cOnePCGr (const Pt2di & aP0) :
            mP0 (aP0)
        {
        }
        void AddV(const Pt2di & aV,const int & aP,int aNum)
        {
            mV.push_back(cSomGr(aV,aP,aNum));
        }

    private :
        Pt2di mP0;
        std::vector<cSomGr>  mV;
};

class cCensusGr
{
    public :
       // FactDepond =>  0 aucune depond  ; 1 => le pds theo est 1 pour 00 et 0 pour 
       cCensusGr(const Pt2di & aV,const double & FactDepond,bool DoFlag,cCensusGr * aGrShareFlag = 0);
       double GainBasic(float ** Im1,float ** Im2,int  aPx2);
       double CostFlag(int aFlag)
       {
            return mDCF[aFlag] / double(mSomP);
       }

       Im2D_INT4 CalcFlag(Im2D_REAL4 anIm);

    private :
       int FlagVois(float ** Im);
       cCensusGr(const cCensusGr&);
       double                mFactDepond;
       std::vector<cOnePCGr> mPCGR; 
       int                   mSomP;
       Pt2di                 mSzV;
       int                   mNbSom;

       static const int     mMulPds = 1000;
       int                  mNbFlag;
       Im1D_INT4            mCostFlag;
       INT4 *               mDCF;
};

template <class Type> class cBufOnImage
{
    public :
        cBufOnImage(Type **,Box2di aBoxDef,Box2di aBoxCalc);
        
        Type ** data() {return mData;}
        void AvanceX();
        void AvanceY() {mData++;}
    private :
        void InitY();
        Box2di mBoxDef;
        Box2di mBoxCalc;
        Box2di mBoxTot;
        std::vector<Type *> mVData;
        Type **             mData;
        Type **             mData0;
        int                 mNbL;
        int                 mRabY;
        
};



//==================================================================================



cCensusGr::cCensusGr(const Pt2di & aSzV,const double & FactDepond,bool DoFlag,cCensusGr * aGrShareFlag) :
   mFactDepond (FactDepond),
   mSomP  (0),
   mSzV   (aSzV),
   mNbSom (0),
   mCostFlag (1)
{
     for (int aDy1=-1 ; aDy1<=1 ; aDy1++)
     {
          for (int aDx1=-1 ; aDx1<= 1 ; aDx1++)
          {
              Pt2di aP1(aDx1*aSzV.x,aDy1*aSzV.y);
              cOnePCGr aPcGR(aP1);
              for (int aK=0 ; aK<4 ; aK++)
              {
                   int aDx2 = aP1.x+VX[aK]*aSzV.x;
                   int aDy2 = aP1.y+VY[aK]*aSzV.y;
                   if  ((aDx2>=-aSzV.x) && (aDx2<=aSzV.x) && (aDy2>=-aSzV.y) && (aDy2<=aSzV.y))
                   {
                       Pt2di aP2(aDx2,aDy2);

                       double aD = (euclid(aP1)+euclid(aP2)) / 2.0;
                       double aRatio = aD / euclid(aSzV);
                       double aPds = 1 - aRatio;
                       aPds = (1-FactDepond) + FactDepond * aPds;
                       int IPds = round_ni(aPds*mMulPds);

                       aPcGR.AddV(aP2,IPds,mNbSom);
                       mSomP += IPds;
                       mNbSom++;
                   }
              }
              mPCGR.push_back(aPcGR);

          }
     }
     ElTimer aChrono;
     if (DoFlag)
     {
         mNbFlag = 1 << mNbSom;
         if (aGrShareFlag)
         {
             ELISE_ASSERT(aGrShareFlag->mFactDepond==mFactDepond,"Fact Depond duf in Gr Share Flag");
             mCostFlag = aGrShareFlag->mCostFlag;
             mDCF      = aGrShareFlag->mDCF;
         }
         else
         {
             mCostFlag.Resize(mNbFlag);
             mDCF =  mCostFlag.data();
             for (int aFlag=0 ; aFlag<mNbFlag; aFlag++)
             {
                 int aSomP = 0;
                 for (int aK1=0 ; aK1<int(mPCGR.size()) ; aK1++)
                 {
                    cOnePCGr & aSG = mPCGR[aK1];
                    for (int aK2=0 ; aK2<int(aSG.mV.size()) ; aK2++)
                    {
                         if (!(aFlag & (aSG.mV[aK2].mFlag)))
                         {
                             aSomP += aSG.mV[aK2].mP;
                         }
                    }
                 }
                 mDCF[aFlag] = aSomP;
//std::cout << "FLGAP " << aFlag << " " << aSomP << "\n";
             }
         }
     }
//getchar();
}

Im2D_INT4 cCensusGr::CalcFlag(Im2D_REAL4 anIm)
{
    Pt2di aSz = anIm.sz();
    Im2D_INT4 aRes(aSz.x,aSz.y);
    Box2di aBoxDef(Pt2di(0,0),anIm.sz());

    float ** aDIm = anIm.data();
    cBufOnImage<float> aBOI(aDIm,aBoxDef,aBoxDef);
    INT ** aDFlag = aRes.data();

    for (int anX=0 ; anX < aSz.x - mSzV.x ; anX++)
    {
         if (anX>=mSzV.x)
         {
             for (int anY=0 ; anY < aSz.y - mSzV.y ; anY++)
             {
                 if (anY>=mSzV.x)
                 {
                     aDFlag[anY][anX] = FlagVois(aBOI.data());
                 }
                 aBOI.AvanceY();
             }
         }
         aBOI.AvanceX();
    }


   return aRes;
    
}

int cCensusGr::FlagVois(float ** Im1)
{
   int aFlag=0;
   for (int aK1=0 ; aK1<int(mPCGR.size()) ; aK1++)
   {
       cOnePCGr & aSG = mPCGR[aK1];
       const Pt2di & aP1 = aSG.mP0;
       float aV1 = Im1[aP1.y][aP1.x];
       for (int aK2=0 ; aK2<int(aSG.mV.size()) ; aK2++)
       {
           const Pt2di & aP2 = aSG.mV[aK2].mV; 
           float aW1 = Im1[aP2.y][aP2.x];

           if (aV1<aW1) 
              aFlag  |=  aSG.mV[aK2].mFlag;
       }
   }


   return aFlag;
}


double cCensusGr::GainBasic(float ** Im1,float ** Im2,int  aPx2)
{
   int aSomLoc=0;
   for (int aK1=0 ; aK1<int(mPCGR.size()) ; aK1++)
   {
       cOnePCGr & aSG = mPCGR[aK1];
       const Pt2di & aP1 = aSG.mP0;
       float aV1 = Im1[aP1.y][aP1.x];
       float aV2 = Im2[aP1.y][aP1.x+aPx2];
       for (int aK2=0 ; aK2<int(aSG.mV.size()) ; aK2++)
       {
           const Pt2di & aP2 = aSG.mV[aK2].mV; 
           float aW1 = Im1[aP2.y][aP2.x];
           float aW2 = Im2[aP2.y][aP2.x+aPx2];

           if ((aV1<aW1) == (aV2<aW2))
              aSomLoc+= aSG.mV[aK2].mP;
       }
   }


   return aSomLoc / double(mSomP);
}



double CorrelBasic(float ** Im1,Pt2di aP1,float ** Im2,float X2,int Y2,Pt2di aSzV,float anEpsilon)
{
     cQckInterpolEpip aQI2(X2);
     RMat_Inertie aMat;
     for (int aDy=-aSzV.y ; aDy<=aSzV.y ; aDy++)
     {
          float * aL1 = Im1[aP1.y+aDy] + aP1.x;
          float * aL2 = Im2[Y2+aDy] + aQI2.mX0;
          for (int aDx=-aSzV.x ; aDx<= aSzV.x ; aDx++)
          {
               aMat.add_pt_en_place(aL1[aDx],aQI2.GetVal(aL2+aDx));
          }
     }
     return aMat.correlation(anEpsilon);
}

double CorrelBasic_ImInt(float ** Im1,Pt2di aP1,float ** Im2,Pt2di aP2,Pt2di aSzV,float anEpsilon)
{
     RMat_Inertie aMat;
     for (int aDy=-aSzV.y ; aDy<=aSzV.y ; aDy++)
     {
          float * aL1 = Im1[aP1.y+aDy] + aP1.x;
          float * aL2 = Im2[aP2.y+aDy] + aP2.x;
          for (int aDx=-aSzV.x ; aDx<= aSzV.x ; aDx++)
          {
               aMat.add_pt_en_place(aL1[aDx],aL2[aDx]);
          }
     }
     return aMat.correlation(anEpsilon);
}

double CorrelBasic_Center(float ** Im1,float ** Im2,int  aPx2,Pt2di aSzV,float anEpsilon)
{
// std::cout << "AAAAAA\n";
     RMat_Inertie aMat;
     for (int aDy=-aSzV.y ; aDy<=aSzV.y ; aDy++)
     {
          float * aL1 = Im1[aDy] ;
          float * aL2 = Im2[aDy] + aPx2;
          for (int aDx=-aSzV.x ; aDx<= aSzV.x ; aDx++)
          {
// std::cout << "ccccc " << aDx << " " << aDy << "\n";
               aMat.add_pt_en_place(aL1[aDx],aL2[aDx]);
// std::cout << "KKKKKKK\n";
          }
     }
// std::cout << "BBBBBBB\n";
     return aMat.correlation(anEpsilon);
}


double CensusBasicCenter(float ** Im1,float ** Im2,int aPx2,Pt2di aSzV)
{
     float aC1 = **Im1;
     float aC2 = Im2[0][aPx2];
     int aNbOk = 0;
     for (int aDy=-aSzV.y ; aDy<=aSzV.y ; aDy++)
     {
          float * aL1 = Im1[aDy] ;
          float * aL2 = Im2[aDy] + aPx2;
          for (int aDx=-aSzV.x ; aDx<= aSzV.x ; aDx++)
          {
              bool Inf1 = (aL1[aDx]<aC1);
              bool Inf2 = (aL2[aDx]<aC2);
              if (Inf1==Inf2) aNbOk++;
          }
     }
     return ((double) aNbOk) / ((1+2*aSzV.x)*(1+2*aSzV.y));
}

double CensusBasic(float ** Im1,Pt2di aP1,float ** Im2,float X2,int Y2,Pt2di aSzV)
{
     cQckInterpolEpip aQI2(X2);
     float aC1 =  Im1[aP1.y][aP1.x];
     float aC2 =  aQI2.GetVal(Im2[aP1.y]+ aQI2.mX0);
     int aNbOk = 0;


     for (int aDy=-aSzV.y ; aDy<=aSzV.y ; aDy++)
     {
          float * aL1 = Im1[aP1.y+aDy] + aP1.x;
          float * aL2 = Im2[Y2+aDy] + aQI2.mX0;
          for (int aDx=-aSzV.x ; aDx<= aSzV.x ; aDx++)
          {
              float aV1 = aL1[aDx];
              float aV2 = aQI2.GetVal(aL2+aDx);
              // if ((aDx==0) && (aDy==0)) std::cout << "TTTt " << (aC1-aV1) << " " << (aC2-aV2) << "\n";

              bool Inf1 = (aV1<aC1);
              bool Inf2 = (aV2<aC2);
              if (Inf1==Inf2) aNbOk++;
          }
     }
     return ((double) aNbOk) / ((1+2*aSzV.x)*(1+2*aSzV.y));
}







double CensusGraphePlein(float ** Im1,Pt2di aP1,float ** Im2,float X2,int Y2,Pt2di aSzV)
{
     cQckInterpolEpip aQI2(X2);
     int aNbOk = 0;
     int aNbMiss = 0;


     for (int aDy=-aSzV.y ; aDy<=aSzV.y ; aDy++)
     {
          float * aL1 = Im1[aP1.y+aDy] + aP1.x;
          float * aL2 = Im2[Y2+aDy] + aQI2.mX0;
          for (int aDx=-aSzV.x ; aDx<= aSzV.x ; aDx++)
          {
              float aV1 = aL1[aDx];
              float aV2 = aQI2.GetVal(aL2+aDx);
              for (int aK=0 ; aK<4 ; aK++)
              {
                   int aDx2 = aDx+VX[aK];
                   int aDy2 = aDy+VY[aK];
                   if  ((aDx2>=-aSzV.x) && (aDx2<=aSzV.x) && (aDy2>=-aSzV.y) && (aDy2<=aSzV.y))
                   {
                       float aW1 = Im1[aP1.y+aDy2][aP1.x+aDx2];
                       float aW2 = aQI2.GetVal(Im2,Pt2di(aDx2,Y2+aDy2));
                       bool Inf1 = (aV1<aW1);
                       bool Inf2 = (aV2<aW2);
                       
                       if (Inf1==Inf2)
                          aNbOk++;
                       else          
                           aNbMiss++;
                   }
              }

          }
     }
     return ((double) aNbOk) / (aNbOk+aNbMiss);
}

double CensusGraphe_ImInt(float ** Im1,Pt2di aP1,float ** Im2,Pt2di aP2,Pt2di aSzV)
{
     int aNbOk = 0;
     int aNbMiss = 0;


     for (int aDyA=-aSzV.y ; aDyA<=aSzV.y ; aDyA += aSzV.y)
     {
          float * aL1 = Im1[aP1.y+aDyA] + aP1.x;
          float * aL2 = Im2[aP2.y+aDyA] + aP2.x;
          for (int aDxA=-aSzV.x ; aDxA<= aSzV.x ; aDxA+=aSzV.x)
          {
              float aV1 = aL1[aDxA];
              float aV2 = aL2[aDxA];
              for (int aK=0 ; aK<4 ; aK++)
              {
                   int aDxB = aDxA+VX[aK]*aSzV.x;
                   int aDyB = aDyA+VY[aK]*aSzV.y;
                   if  ((aDxB>=-aSzV.x) && (aDxB<=aSzV.x) && (aDyB>=-aSzV.y) && (aDyB<=aSzV.y))
                   {
                       float aW1 = Im1[aP1.y+aDyB][aP1.x+aDxB];
                       float aW2 = Im2[aP2.y+aDyB][aP2.x+aDxB];
                       bool Inf1 = (aV1<aW1);
                       bool Inf2 = (aV2<aW2);
                       
                       if (Inf1==Inf2)
                          aNbOk++;
                       else          
                           aNbMiss++;
                   }
              }

          }
     }
     return ((double) aNbOk) / (aNbOk+aNbMiss);
}






     // float aValStd = aQI2.GetVal(aDataIm1,Pt2di(0,anY+anOff1.y));
     // float aValNew = aDataC[anY+anOff1.y][anX+anOff1.x+anOffset];







template <class Type> cBufOnImage<Type>::cBufOnImage(Type ** aDataIm,Box2di aBoxDef,Box2di aBoxCalc) :
   mBoxDef  (aBoxDef),
   mBoxCalc (aBoxCalc),
   mBoxTot  (Sup(mBoxDef,mBoxCalc))  
{
    
    mNbL = 0;

    for (int anY=mBoxTot._p0.y ; anY<mBoxTot._p1.y ; anY++)
    {
         if ( (anY>=mBoxDef._p0.y) && (anY<aBoxDef._p1.y))
             mVData.push_back(aDataIm[anY]+aBoxCalc._p0.x);
         else 
             mVData.push_back(0);

         mNbL++;
    }
    mData0 = &mVData[0];
    InitY();

}
template <class Type> void cBufOnImage<Type>::InitY()
{
    mData = mData0 -mBoxDef._p0.y + mBoxCalc._p0.y;
}

template <class Type> void cBufOnImage<Type>::AvanceX()
{
    // mData = &(mVData[0]);
    InitY();
    for (int aK=0 ; aK<mNbL ; aK++)
        mData0[aK]++;
}



double TolNbByPix=1e-5;
void cAppliMICMAC::DoCensusCorrel(const Box2di & aBox,const cCensusCost & aCC)
{
   
  bool Verif = false;
  bool DoGraphe = (aCC.TypeCost() ==eMCC_GrCensus);
  bool DoCensusBasic = (aCC.TypeCost() ==eMCC_CensusBasic);
  

   std::vector<float> aVPms;
   double aSomPms=0;

   if (CMS())
   {
       const std::vector<cOneParamCMS> & aVP = CMS()->OneParamCMS();
       for (int aK=0 ; aK<int(aVP.size()) ; aK++)
       {
          aVPms.push_back(aVP[aK].Pds());
          aSomPms += aVPms.back();
          // std::cout << "SOMP " << aSomPms << "\n";
       }
   }
   else
   {
       aVPms.push_back(1.0);
       aSomPms = 1.0;
   }
   int aNbScale = aVPms.size();
   float * aDataPms = & (aVPms[0]);


   cGPU_LoadedImGeom &   anI0 = *(mVLI[0]);
   cGPU_LoadedImGeom &   anI1 = *(mVLI[1]);
   const std::vector<cGPU_LoadedImGeom *> & aVSLGI0 = anI0.MSGLI();

   ELISE_ASSERT((mX0Ter==0)&&(mY0Ter==0),"Origin Assumption in cAppliMICMAC::DoCensusCorrel");
   // Pt2di aSzT = aBox.sz();

  //  Censur Graphe
   bool DoFlag = DoGraphe;
   std::vector<cCensusGr *> aVCG;
   cCensusGr * aCG = 0;
   if (DoGraphe)
   {
       for (int aK=0 ; aK<int(aVSLGI0.size()) ; aK++)
       {
            aVCG.push_back(new cCensusGr(aVSLGI0[aK]->SzV0(),0.0,DoFlag, (aK==0)?0:aVCG[0]));
       }
       aCG = aVCG[0];
   }



 //  ====  VERIFICATION DYNAMIQUE DES ARGUMENTS ==========

 //  ====  1. GEOMETRIE EPIPOLAIRE BASIQUE
    ELISE_ASSERT
    (
         GeomImages() == eGeomImage_EpipolairePure,
         "Not epipolar geometry for census "
    );


 //  ====  1. GEOMETRIE EPIPOLAIRE BASIQUE
    ELISE_ASSERT
    (
       mNbIm <= 2,
       "Image > 2  in Census"
    );



    double aStepPix = mStepZ / mCurEtape->DeZoomTer();

 //  ====  2. Pas quotient d'entier
    double aRealNbByPix = 1/ aStepPix;
    int mNbByPix = round_ni(aRealNbByPix);

    if (ElAbs(aRealNbByPix-mNbByPix) > TolNbByPix)
    {
         std::cout << "For Step = " << mStepZ  << " GotDif " << aRealNbByPix-mNbByPix << "\n";
         ELISE_ASSERT(false,"in DoCensusCorre step is not 1/INT");
    }
/*
*/


    Pt2di anOff0 = anI0.OffsetIm();
    Pt2di anOff1 = anI1.OffsetIm();


// std::cout << anOff0 << anOff1 << "\n";

    // std::cout << mX0Ter  << " " << mY0Ter << "\n";

    // mCurSzVMax 

    float ** aDataIm0 =  anI0.VDataIm()[0];
    float ** aDataIm1 =  anI1.VDataIm()[0];
    // cInterpolateurIm2D<float> * anInt = CurEtape()->InterpFloat();


    Box2di aBoxCalc0 = aBox.trans(anOff0);
    Box2di aBoxCalc1 = aBox.trans(anOff1);

   Box2di aBoxDef0 (Pt2di(0,0),mPDV1->LoadedIm().SzIm());
   Box2di aBoxDef1 (Pt2di(0,0),mPDV2->LoadedIm().SzIm());
    

    std::vector<Im2D_INT4> mImFlag0;
    std::vector<INT4 **  > mVIF0 ;
    INT4 ***               mDIF0=0;

    // La phase code le decalage sub pixel, on impose un pas en 1/N pour n'avoir que N image 
    // interpolee a creer
    for (int aPhase = 0 ; aPhase<mNbByPix ; aPhase++)
    {
        
        std::vector<Im2D_INT4> mImFlag1;
        std::vector<INT4 **  > mVIF1;
        INT4 ***               mDIF1=0;
        int aPhaseCompl = mNbByPix - aPhase;
      
        for (int aK=0 ; aK<int(mBufCensusIm2.size()) ; aK++)
        {
            float ** aDataIm1 = anI1.VDataIm()[aK]; 
            float ** aDataC   = mDataBufC[aK];
            Pt2di aSz = mBufCensusIm2[aK].sz();

            // On calcule l'image interpolee
            for (int anY = 0 ; anY < aSz.y ; anY++)
            {
                 float * aL1 = aDataIm1[anY] ;
                 float * aC1 = aDataC[anY] ;
                 if (aPhase!=0)
                 {
                    int aNbX = aSz.x-1;
                    for (int anX=0 ; anX<aNbX ; anX++)
                    {
                        *aC1 =  (aPhase * aL1[1] + aPhaseCompl*aL1[0]) / mNbByPix;
                        aL1++;
                        aC1++;
                    }
                }
                else
                {
                   memcpy(aC1,aL1,sizeof(*aC1)*aSz.x);
                }
            }
            if (DoFlag)
            {

                 mImFlag1.push_back(aCG->CalcFlag(mBufCensusIm2[aK]));
                 mVIF1.push_back( mImFlag1.back().data());
                 if (aPhase==0)
                 {
                    mImFlag0.push_back(aCG->CalcFlag(*anI0.FloatIm(aK)));
                    mVIF0.push_back( mImFlag0.back().data());
                 }
            }
        }
        if (DoFlag)
        {
            mDIF0 = &(mVIF0[0]);
            mDIF1 = &(mVIF1[0]);
        }
        float ** aDataC =  mDataBufC[0];


        std::vector<cBufOnImage<float> *> aVBOI0;
        std::vector<cBufOnImage<float> *> aVBOIC;
        if (DoCensusBasic)
        {
             for (int aKC=0 ; aKC<aNbScale ; aKC++)
             {
                 aVBOI0.push_back(new  cBufOnImage<float> (anI0.VDataIm()[aKC],aBoxDef0,aBoxCalc0));
                 aVBOIC.push_back(new  cBufOnImage<float> (     mDataBufC[aKC],aBoxDef1,aBoxCalc1));
             }
        }
        int aNbBOI = aVBOI0.size();

        cBufOnImage<float> aBOI0(aDataIm0,aBoxDef0,aBoxCalc0);
        cBufOnImage<float> aBOIC(aDataC  ,aBoxDef1,aBoxCalc1);


        for (int anX = mX0Ter ; anX <  mX1Ter ; anX++)
        {
            for (int anY = mY0Ter ; anY < mY1Ter ; anY++)
            {
                Pt2di aPIm0 = Pt2di(anX,anY) + anOff0;
                bool OkIm0 = anI0.IsOkErod(aPIm0.x,aPIm0.y);
                int aZ0 =  mTabZMin[anY][anX];
                int aZ1 =  mTabZMax[anY][anX];


               int aXIm1SsPx = anX+anOff1.x;
               int aYIm1SsPx = anY+anOff1.y;


                while (mod(aZ0,mNbByPix) != aPhase) aZ0++;
                int anOffset = Elise_div(aZ0,mNbByPix);

                for (int aZI=aZ0 ; aZI< aZ1 ; aZI+=mNbByPix)
                {
                        // double aZR = aZI * aStepPix;
                        double aCost = mAhDefCost;
                        if (OkIm0)
                        {
                            Pt2di aPIm1(aXIm1SsPx+anOffset,aYIm1SsPx);
                            if (anI1.IsOkErod(aPIm1.x,aPIm1.y))
                            {
                                if (DoGraphe)
                                {
                                     float aCostGr = 0;
                                     for (int aKS =0 ; aKS<aNbScale ; aKS++)
                                     {
                                         int aFlag0  = mDIF0[aKS][aPIm0.y][aPIm0.x];
                                         int aFlag1  = mDIF1[aKS][aPIm1.y][aPIm1.x];
                                         int aDFlag = aFlag0 ^ aFlag1;
                                         aCostGr +=  aDataPms[aKS] * aCG->CostFlag(aDFlag);
                                     }
                                     aCost = aCostGr / aSomPms;
                                     if (Verif) // Verification de cost Cennsus
                                     {
                                         Pt2dr aPRIm1 = Pt2dr(aPIm1) + Pt2dr(aPhase/double(mNbByPix),0);
                                         double aCostGrBas =CensusGraphePlein(aDataIm0,aPIm0,aDataIm1,aPRIm1.x,aPIm1.y,mCurSzVMax);
                                         double aC3 = aCG->GainBasic(aBOI0.data(),aBOIC.data(),anOffset);
                                         // Peut pas forcer a 0, car interpol diff peut creer except une variation
                                         if ((ElAbs(aCostGrBas-aCost)>1e-4) || (ElAbs(aC3-aCost)>1e-4))
                                         {
                                             std::cout << "Verfi Gr " << aCost << " " << aCostGrBas  << " " << aC3 << "==============================\n";
                                         }
                                     }
                                }
                                else if (DoCensusBasic)
                                {
                                     Pt2dr aPRIm1 = Pt2dr(aPIm1) + Pt2dr(aPhase/double(mNbByPix),0);
                                     // aCost = CensusGraphePlein(aDataIm0,aPIm0,aDataIm1,aPRIm1.x,aPIm1.y,mCurSzVMax);
                                     aCost = CensusBasicCenter(aVBOI0[0]->data(),aVBOIC[0]->data(),anOffset,mCurSzVMax);
                                     if (Verif)
                                     {
                                          double aC2 = CensusBasic(aDataIm0,aPIm0,aDataIm1,aPRIm1.x,aPIm1.y,mCurSzVMax);
                                          if (ElAbs(aCost-aC2) > 1e-4)
                                          {
                                             std::cout << "Verfi Basic " << aCost <<  " "<< aC2 << "===================================\n";
                                          }
                                     }
                                     // double aC3 = CensusBasicCenter(aBOI0.data(),aBOIC.data(),anOffset,mCurSzVMax);
                                }


// std::cout << " CCCcc " << aCost << "\n";



/*
                              aCost = CorrelBasic_ImInt(aDataIm0,aPIm0,aDataC,Pt2di(anX+anOff1.x+anOffset,anY+anOff1.y),mCurSzVMax,mAhEpsilon);
                              double aC2  = CorrelBasic_Center(aBOI0.data(),aBOIC.data(),anOffset,mCurSzVMax,mAhEpsilon);
                              double aC1 = CensusGraphe_ImInt(aDataIm0,aPIm0,aDataC,Pt2di(anX+anOff1.x+anOffset,anY+anOff1.y),mCurSzVMax);
                              double aC2 = CensusGraphe(aDataIm0,aPIm0,aDataIm1,anX+anOff1.x+aZR,anY+anOff1.y,mCurSzVMax,mAhEpsilon);
                              double aC3 = aCG->GainBasic(aBOI0.data(),aBOIC.data(),anOffset);

*/
                                aCost = mStatGlob->CorrelToCout(aCost);
                            }
                        }
                        mSurfOpt->SetCout(Pt2di(anX,anY),&aZI,aCost);
                        anOffset++;
// std::cout << "ZZZZ " << aZI << " " << aCost << "\n";
                }
                for (int aK=0 ; aK<aNbBOI ; aK++)
                {
                    aVBOI0[aK]->AvanceY();
                    aVBOIC[aK]->AvanceY();
                }
                aBOI0.AvanceY();
                aBOIC.AvanceY();
             }
             for (int aK=0 ; aK<aNbBOI ; aK++)
             {
                 aVBOI0[aK]->AvanceX();
                 aVBOIC[aK]->AvanceX();
             }
             aBOI0.AvanceX();
             aBOIC.AvanceX();
        }
        DeleteAndClear(aVBOI0);
        DeleteAndClear(aVBOIC);
    }


     DeleteAndClear(aVCG);
}

}



/*Footer-MicMac-eLiSe-25/06/2007

Ce logiciel est un programme informatique servant �  la mise en
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
associ�s au chargement,  �  l'utilisation,  �  la modification et/ou au
d�veloppement et �  la reproduction du logiciel par l'utilisateur �tant
donn� sa sp�cificit� de logiciel libre, qui peut le rendre complexe �
manipuler et qui le r�serve donc �  des d�veloppeurs et des professionnels
avertis poss�dant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invit�s �  charger  et  tester  l'ad�quation  du
logiciel �  leurs besoins dans des conditions permettant d'assurer la
s�curit� de leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement,
�  l'utiliser et l'exploiter dans les m�mes conditions de s�curit�.

Le fait que vous puissiez acc�der �  cet en-t�te signifie que vous avez
pris connaissance de la licence CeCILL-B, et que vous en avez accept� les
termes.
Footer-MicMac-eLiSe-25/06/2007*/
