#ifndef _CODED_TARGET_H_
#define _CODED_TARGET_H_
#include "include/MMVII_all.h"
#include "include/MMVII_SetITpl.h"
#include "FilterCodedTarget.h"

namespace MMVII
{
namespace  cNS_CodedTarget
{

class cGeomSimDCT;
class cResSimul;
class cSetCodeOf1Circle;
class cCodesOf1Target;
class cParamCodedTarget;
class cDCT;


typedef cSetISingleFixed<tU_INT4>  tBinCodeTarg;
typedef std::vector<tBinCodeTarg> tVSetICT;
typedef cIm2D<tU_INT1>     tImTarget;
typedef cDataIm2D<tU_INT1> tDataImT;


/*   ==============  Simulation  =============  */

class cGeomSimDCT
{
    public :
       cGeomSimDCT();
       cGeomSimDCT(int aNum,const  cPt2dr& aC,const double& aR1,const double& aR2);
       bool Intersect(const cGeomSimDCT &  aG2) const ;

       cDCT * mResExtr;
       int    mNum;
       cPt2dr mC;            // Theoreticall center
       cPt2dr mCornEl1;     // Theoreticall corner 1 of ellipse
       cPt2dr mCornEl2;     // Theoreticall corner 2 of ellipse
       double mR1;
       double mR2;
};
void AddData(const  cAuxAr2007 & anAux,cGeomSimDCT & aGSD);

class cResSimul
{
     public :
       cResSimul() ;
       static  cResSimul  FromFile(const std::string&);

       double BorderGlob() const ;
       std::string                mCom;
       cPt2dr                     mRayMinMax;
       double                     mBorder;
       double                     mRatioMax;
       std::vector<cGeomSimDCT>   mVG;
};
void AddData(const  cAuxAr2007 & anAux,cResSimul & aRS);

/*   ==============  Result extract  =============  */

enum class eResDCT // Result Detect Code Target
{
     Ok,
     Divg,
     LowSym,
     LowSymMin,
     LowBin,
     LowRad
};

class  cDCT
{
     public  :
         cDCT(const cPt2di aPt,cAffineExtremum<tREAL4> & anAffEx);

         cPt2di  Pix()  const {return ToI(mPt);}
         cPt2di  Pix0() const {return mPix0;}

         cGeomSimDCT * mGT;
         cPt2di        mPix0;
         cPt2dr        mPt;
         eResDCT       mState;

         double        mSym;
         double        mBin;
         double        mRad;

};

/*   ==============  Target spec  =============  */


class cSetCodeOf1Circle
{
    public :
      cSetCodeOf1Circle(const std::vector<int> & aCards,int aN);
      int  NbSub() const;
      const tBinCodeTarg & CodeOfNum(int aNum) const;
      int N() const;
    private :
      std::vector<int>   mVCards;
      int      mN;
      tVSetICT mVSet ;  //   All the binary code of one target 
};


class cCodesOf1Target
{
   public :
      cCodesOf1Target(int aNum);

      void AddOneCode(const tBinCodeTarg &);
      void  Show();
      const tBinCodeTarg & CodeOfNumC(int) const;
      int   Num() const;
   private :
      int                        mNum;
      std::vector<tBinCodeTarg>  mCodes;
};




class cParamCodedTarget
{
    public :
       cParamCodedTarget();
       void InitFromFile(const std::string & aNameFile);

       int &     NbRedond();  // Redundancy = number of repetition of a pattern in a circle
       int &     NbCircle();  // Redundancy = number of repetition of a pattern in a circle
       double &  RatioBar();  // Ratio on codin bar
       void      Finish();

       int NbCodeAvalaible() const;         // Number of different code we can generate
       int BaseForNum() const;         // Base used for converting integer to string
       cCodesOf1Target CodesOfNum(int);     // One combinaison of binary code
       tImTarget  MakeIm(const cCodesOf1Target &);  // Generate the image of 1 combinaison
       tImTarget  MakeImCodeExt(const cCodesOf1Target &);  // Generate the image of 1 combinaison

       void AddData(const cAuxAr2007 & anAux);

       bool CodeBinOfPts(double aRho,double aTeta,const cCodesOf1Target & aSetCodesOfT,double aRho0,double aThRho);

       std::string NameOfNum(int) const; ///  Juste the apha num
       std::string NameFileOfNum(int) const; ///  Juste the apha num


       cPt2dr    mCenterF;   // symetry center at end
       cPt2di    mSzF;       // sz at end
       cPt2dr    mCornEl1;
       cPt2dr    mCornEl2;
       cPt2dr    mMidle;
    // private :

       cPt2dr    Pix2Norm(const cPt2di &) const;
       cPt2dr    Norm2PixR(const cPt2dr &) const;
       cPt2di    Norm2PixI(const cPt2dr &) const;


       int       mNbBit;  // Do not include parity, so 5=> gives 16 if parity used
       bool      mWithParity;  // Do we use parirty check
       int       mNbRedond;  // Redundancy = number of repetition of a pattern in a circle
       int       mNbCircle;  // Number of circles encoding information
       int       mNbPixelBin;        // Number of pixel  Binary image
       double    mSz_CCB;      // size of central chekcboard/target , everything prop to it, 1 by convention

       double    mThickN_WInt;  // Thickness white circle separating code/
       double    mThickN_Code;  // Thickness of coding part
       double    mThickN_WExt;  // Thickness of white separatio,
       double    mThickN_Car;  // thickness of black border (needed only on pannel)
       double    mThickN_BExt;  // thickness of black border (needed only on pannel)


       double          mRho_0_EndCCB;// End of Central CB , here Rho=ThickN ...
       double          mRho_1_BeginCode;// ray where begins the coding stuff
       double          mRho_2_EndCode;// ray where begins the coding stuff
       double          mRho_3_BeginCar;// ray where begins the coding stuff
       double          mRho_4_EndCar;  // ray where begins the coding stuff


       cPt2di    mSzBin;
       double    mScale;  // Sz of Pixel in normal coord

       std::vector<cSetCodeOf1Circle>     mVecSetOfCode;
       cDecomposPAdikVar                  mDecP;
};

void AddData(const  cAuxAr2007 & anAux,cParamCodedTarget & aPCT);
};
};
#endif // _CODED_TARGET_H_

