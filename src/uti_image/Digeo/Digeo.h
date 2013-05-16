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

/*

   Cas d'utilisation des espaces :

      - Ful Im1  - Ful Im2  

      - Ful Im1 Decoupe  -  Im2 asservi

      - Box Im1  - Box Im2

      - Box Im1  - Im2 asservi

     Cas incompatible :
         - Un decoupage,
         - Plusieurs images
         - pas d'asservissement

     Cas incompatible :
         - asservissement avec BoxIm (caso


        - Decoupage + 
*/

#ifndef _ELISE_DIGEO_H_
#define _ELISE_DIGEO_H_

#include "cParamDigeo.h"

using namespace NS_ParamChantierPhotogram;


//  cRotationFormelle::AddRappOnCentre


//=======================================================
//   Represente un image d'une octave a une resolution donnee
class cImInMem;
template <class Type> class cTplImInMem ;
/*
         cTplOctDig<Type> & mTOct;  => son octave
         tIm    mIm;
         tTIm   mTIm;
         tTImMem *  mTMere;
         tTImMem *  mTFille;
         tTImMem *  mOrigOct;
*/

//=======================================================
//  Represente une octave !! Contient autant cImInMem que de sigma de gaussienne
class cOctaveDigeo;
template <class Type> class cTplOctDig ;

/*
        std::vector<cTplImInMem<Type> *>  mVTplIms; 
        std::vector<Type **>  mVDatas;
        Type ***              mCube;
        cTplImInMem<Type> *  mImBase;   => premiere image de l'octave
    
*/


//=======================================================
//   Represente une image ; contient autant d'octave que necessaire
class cImDigeo;


/*
    Class virtuelle , d'interface avec les classe permettant de correler rapidemnt
  selon une ligne.

        virtual void Convol(Type * Out,Type * In,int aK0,int aK1) :

             -  methode par defaut, correlation standar
             -  classe derivee : le code genere

        static cConvolSpec<Type> * Get(tBase* aFilter,int aDeb,int aFin,int aNbShitX,bool ForGC);
             - renvoie une classe compilee si il en existe  (on teste que le filtre et le reste a exactement
               ce qui est attendu);


        cConvolSpec(tBase* aFilter,int aDeb,int aFin,int aNbShitX,bool ForGC);
*/
template <class Type> class cConvolSpec;

class cAppliDigeo;
class cVisuCaracDigeo;
const int PackTranspo = 4;
class cParamAppliDigeo;
class cPtsCaracDigeo;


typedef enum
{
  eTES_Uncalc,
  eTES_instable,
  eTES_GradFaible,
  eTES_TropAllonge,
  eTES_Ok
} eTypeExtreSift;

class cPtsCaracDigeo
{
    public :
       cPtsCaracDigeo(const Pt2dr & aP,eTypeTopolPt aType);
       Pt2dr         mPt;
       eTypeTopolPt  mType;
};


   // Permt de shifter les entiers (+ rapide que la div) sans rien faire pour
   // les flottants
inline double ShiftDr(const double & aD,const int &) { return aD; }
inline double ShiftG(const double & aD,const int &) { return aD; }
inline double InitFromDiv(double ,double *) { return 0; }

inline int ShiftDr(const int & aD,const int & aShift) { return aD >> aShift; }
inline int ShiftG(const int & aD,const int & aShift) { return aD << aShift; }
inline int InitFromDiv(int aDiv,int *) { return aDiv/2; }


/*****************************************************************/
/*                                                               */
/*   Fonctions elementaires de noyaux 1D faits notamment pour    */
/* permettre le calcul de noyau enchaine                         */
/*                                                               */
/*****************************************************************/

//  Resout l'equation  aI o I2 = aI3 , au sens des moindres carres
Im1D_REAL8 DeConvol
(
     int aC2,   // Indexe 0 dans I2
     int aSz2,  // Taille I2
     Im1D_REAL8 aI1,   // Kernel 1
     int aC1,          // Indexe 0 dans I1
     Im1D_REAL8 aI3,   // Kernel 3
     int aC3           // Indexe 0 dans I3
);
// Paramametrage standardA  0 en centre image
Im1D_REAL8 DeConvol(int aDemISz2,Im1D_REAL8 aI1,Im1D_REAL8 aI3);



// Convolution C1 et C2 = indexe 0,  lent ; pour verif DeConvol
Im1D_REAL8 Convol(Im1D_REAL8 aI1,int aC1,Im1D_REAL8 aI2,int aC2);
// Parametrage stantdard 
Im1D_REAL8 Convol(Im1D_REAL8 aI1,Im1D_REAL8 aI2);

// Force l'image à une integrale donnee
Im1D_REAL8 MakeSom(Im1D_REAL8 aIm,double aSomCible);
Im1D_REAL8 MakeSom1(Im1D_REAL8 aIm);

//  Calcul un noyau gaussien en faisant pour chaque pixel la valeur integrale.
Im1D_REAL8  GaussianKernel(double aSigma,int aNb,int aSurEch);

//  Calcul le nombre d'element pour que la gaussiennne puisse etre tronquee a Residu pres
int NbElemForGausKern(double aSigma,double aResidu);

//  Calcule un noyau gaussien
Im1D_REAL8  GaussianKernelFromResidu(double aSigma,double aResidu,int aSurEch);


// Conversion d'un noyau double (de somme 1) en entier, en conservant la somme
// (Pour une image entiere qui sera interpretee comme rationnele de quotient aMul)
Im1D_INT4 ToIntegerKernel(Im1D_REAL8 aRK,int aMul,bool aForceSym);

cConvolSpec<INT>*   IGausCS(double aSigma,double anEpsilon);
cConvolSpec<double>*   RGausCS(double aSigma,double anEpsilon);


Fonc_Num GaussSepFilter(Fonc_Num   aFonc,double aSigma,double anEpsilon);






     //     Pour representer une image

class cImInMem
{
     public :

         GenIm::type_el  TypeEl() const;
         int  RGlob() const;
         double ROct() const;
         Pt2di Sz() const;
         cImInMem *  Mere();
         cOctaveDigeo & Oct();
         void  SetMere(cImInMem *);
         void SauvIm(const std::string & = "");

         // void MakeReduce_121();

         virtual void VMakeReduce_121(cImInMem &)=0;
         virtual void VMakeReduce_010(cImInMem &)=0;
         virtual void VMakeReduce_11(cImInMem &)=0;

         void MakeReduce(cImInMem &,eReducDemiImage);

         void ResizeOctave(const Pt2di & aSz);
         virtual void ResizeImage(const Pt2di & aSz) =0;

         // virtual void Resize(const Pt2di & aSz) = 0;
         virtual void LoadFile(Fonc_Num aFile,const Box2di & aBox,GenIm::type_el) = 0;
         virtual Im2DGen Im() = 0;

         // La relation mere-fille a meme DZ se fait entre image de mm type
         // virtual void  SetMereSameDZ(cImInMem *)=0;

         // virtual void MakeConvolInit(double aSigm )= 0;
         virtual void ReduceGaussienne() = 0;

         virtual double CalcGrad2Moy() = 0;

         double ScaleInOct() const;
         double ScaleInit()  const;

         std::vector<cPtsCaracDigeo> & VPtsCarac();

     protected :

         cImInMem(cImDigeo &,const Pt2di & aSz,GenIm::type_el,cOctaveDigeo &,double aResolOctaveBase,int aKInOct,int IndexSigma);
         cAppliDigeo &    mAppli;
         cImDigeo &       mImGlob;
         cOctaveDigeo &   mOct;
         Pt2di            mSz;
         GenIm::type_el   mType;
         int              mResolGlob;
         double           mResolOctaveBase;  // Le sigma / a la premier image del'octave
         int              mKInOct;
         int              mIndexSigma;
         int              mNbShift;
         cImInMem *       mMere;
         cImInMem *       mFille;

         Im1D_REAL8 mKernelTot;  // Noyaux le reliant a l'image de base de l'octave
         bool mFirstSauv;
         std::vector<cPtsCaracDigeo> mVPtsCarac;
     private :
        cImInMem(const cImInMem &);  // N.I.
};


template <class Type> class cTplImInMem : public cImInMem
{
     public :
        typedef typename El_CTypeTraits<Type>::tBase tBase;
        typedef Im2D<Type,tBase>   tIm;
        typedef TIm2D<Type,tBase>  tTIm;
        typedef cTplImInMem<Type>  tTImMem;
        Im1D<tBase,tBase> ImGaussianKernel(double aSigma);


        cTplImInMem(cImDigeo &,const Pt2di & aSz,GenIm::type_el,cTplOctDig<Type> &,double aResolOctaveBase,int aKInOct,int IndexSigma);


        void SetConvolSepXY
             (
                  bool   Increm,  // Increm et Sigma, renseignement sur l'origine du noyau
                  double aSigma,  // permet de generer des commentaires dans code auto
                  const cTplImInMem<Type> & aImIn,
                  Im1D<tBase,tBase> aKerXY,
                  int  aNbShitXY
             );


        //tTIm  & TIm() {return TIm;}
        //const tTIm  & TIm() const {return TIm;}
        tIm  TIm() const {return mIm;}
        void LoadFile(Fonc_Num aFonc,const Box2di & aBox,GenIm::type_el) ;
        bool InitRandom();

        void VMakeReduce_121(cImInMem &);
        void VMakeReduce_010(cImInMem &);
        void VMakeReduce_11(cImInMem &);
        void ResizeImage(const Pt2di & aSz);
        double CalcGrad2Moy();
        Im2DGen Im() ;
        void  SetMereSameDZ(cTplImInMem<Type> *);
        // void  SetOrigOct(cTplImInMem<Type> *);
        // void MakeConvolInit(double aSigm );
        void ReduceGaussienne();

        void ExtractExtremaDOG
             (
                   const cSiftCarac & aSC,
                   cTplImInMem<Type> & aPrec,
                   cTplImInMem<Type> & aNext1,
                   cTplImInMem<Type> & aNext2
             );
         static void MakeClassConvolSpec(bool Increm,double aSigma,FILE *,FILE *,tBase* aFilter,int aDeb,int aFin,int aNbShit); 
     private :

        void ResizeBasic(const Pt2di & aSz);
        eTypeExtreSift CalculateDiff(Type***aC,int anX,int anY,int aNiv);

/*
        SetConvolBordX :
 
          Pour la "colonne" X, calcul dans ImOut toute les convolution en gerant 
       les effets de bord :

       aDebX  , aFinX : borne du filtre, typiquement de -SzKer , + SzKer (inclus)

  Utilise 
  
template <class tBase> tBase ClipForConvol(int aSz,int aKXY,tBase * aData,int & aDeb,int & aFin) :

    Clip l'intervalle (genre [-SzKe,+SzK] au depart) pour que la convol ne deborde 
    pas de [0,aSz[


inline tBase CorrelLine(tBase aSom,const Type * aData1,const tBase *  aData2,const int & aDeb,const int & aFin)

    Produit scalaire tout a fait basique, utilise pour correler les bord


*/


        static void SetConvolBordX
             (
                  Im2D<Type,tBase> aImOut,
                  Im2D<Type,tBase> aImIn,
                  int aX,
                  tBase *,int DebX,int aFinX
             );

        static void SetConvolSepX
             (
                  Im2D<Type,tBase> aImOut,
                  Im2D<Type,tBase> aImIn,
                  // tBase *,int DebX,int aFinX,
                  int  aNbShitX,
                  cConvolSpec<Type> *
             );




        void SetConvolSepX
             (
                  const cTplImInMem<Type> & aImIn,
                  // tBase *,int DebX,int aFinX,
                  int  aNbShitX,
                  cConvolSpec<Type> *
             );


        void SelfSetConvolSepY
             (
                  int  aNbShitY,
                  cConvolSpec<Type> *
             );

         template <class TMere> void  MakeReduce_121(const cTplImInMem<TMere> &);
         template <class TMere> void  MakeReduce_010(const cTplImInMem<TMere> &);
         template <class TMere> void  MakeReduce_11(const cTplImInMem<TMere> &);



         void  ExtramDOG(Type *** aC,const Pt2di & aP,bool & isMax,bool & isMin);
         bool  SupDOG(Type *** aC,const Pt3di& aP1,const Pt3di& aP2);
         tBase DOG(Type *** aC,const Pt3di& aP1);



         cTplOctDig<Type> & mTOct;
         tIm    mIm;
         tTIm   mTIm;
         tTImMem *  mTMere;
         tTImMem *  mTFille;
         // tTImMem *  mOrigOct;
         Type **    mData;
         tBase      mDogPC;  // Dif of Gauss du pixel courrant

         
     private :
          cTplImInMem(const cTplImInMem<Type> &);  // N.I.
          void ExploiteExtrem(int anX,int anY);


          static tBase  ** theMDog;

          double            mSeuilTr2Det;
          double            mSeuilGrad;
          int               mBrd;
          int               mIx;
          int               mIy;
          Pt2dr             mP;
          double            mGX;
          double            mGY;
          double            mDxx;
          double            mDyy;
          double            mDxy;
          double            mTrX;
          double            mTrY;

          eTypeExtreSift    mResDifSift;
          int               mNbExtre;
          int               mNbExtreOK;
};


class cOctaveDigeo
{
    public :
        static cOctaveDigeo * AllocTop(GenIm::type_el,cImDigeo &,int aNiv,Pt2di aSzMax);

        int NbIm() const;
        cImInMem * KthIm(int aK) const;
        int                      Niv() const;

        bool OkForSift(int aK) const;
        void DoAllExtract(int aK);
        void DoAllExtract();

        // void AddIm(cImInMem *);

        virtual cImInMem * AllocIm(double aResolOctaveBase,int aK,int IndexSigma) = 0;
        virtual cImInMem * GetImOfSigma(double aSig) = 0;
        virtual  cImInMem * FirstImage() = 0;
        void SetNbImOri(int aNbIm);
        int  NbImOri() const;

        // virtual void DoSiftExtract(const cSiftCarac &) = 0;
        // virtual void DoSiftExtract(int aK) = 0;
        virtual void DoSiftExtract(int aK,const cSiftCarac &) = 0;
        virtual void PostPyram() = 0;

        virtual cOctaveDigeo * AllocDown(GenIm::type_el,cImDigeo &,int aNiv,Pt2di aSzMax) = 0;

        Pt2dr P0CurMyResol() const;
        void ResizeAllImages(const Pt2di &);

        const Box2di  &      BoxImCalc () const;
        const Box2dr  &      BoxCurIn () const;
        const Box2di  &      BoxCurOut () const;

        void SetBoxInOut(const Box2di & aBoxIn,const Box2di & aBoxOut);
        cOctaveDigeo *  OctUp();
        const std::vector<cImInMem *> &  VIms();

        virtual cTplOctDig<U_INT2> * U_Int2_This() = 0;
        virtual cTplOctDig<REAL4> *  REAL4_This() = 0;

        bool Pt2Sauv(const Pt2dr&) const;
        Pt2dr  ToPtImCalc(const Pt2dr& aP0) const;  // Renvoie dans l'image sur/sous-resolue
        Pt2dr  ToPtImR1(const Pt2dr& aP0) const;  // Renvoie les coordonnees dans l'image initiale

		REAL8 GetMaxValue() const;
    protected :
        static cOctaveDigeo * AllocGen(cOctaveDigeo * Mere,GenIm::type_el,cImDigeo &,int aNiv,Pt2di aSzMax);
       
        cOctaveDigeo(cOctaveDigeo * OctUp,GenIm::type_el,cImDigeo &,int aNiv,Pt2di aSzMax);


        GenIm::type_el           mType;
        cImDigeo &               mIm;
        cAppliDigeo &            mAppli;
        cOctaveDigeo *           mOctUp;
        int                      mNiv;
        std::vector<cImInMem *>  mVIms;
        Pt2di                    mSzMax;
        int                      mNbImOri;  // de NbByOctave()
        Box2di                   mBoxImCalc;
        Box2dr                   mBoxCurIn;
        Box2di                   mBoxCurOut;
     private :
        cOctaveDigeo(const cOctaveDigeo &);  // N.I.
};


template <class Type> class cTplOctDig  : public cOctaveDigeo
{
    public :
         cTplOctDig(cOctaveDigeo* Up,GenIm::type_el,cImDigeo &,int aNiv,Pt2di aSzMax);
         cImInMem * AllocIm(double aResolOctaveBase,int aK,int IndexSigma);
         cImInMem * GetImOfSigma(double aSig);

         Type*** Cube();

         cImInMem * FirstImage();
         cTplImInMem<Type> * TypedFirstImage();
        

         cOctaveDigeo * AllocDown(GenIm::type_el,cImDigeo &,int aNiv,Pt2di aSzMax) ;
         cTplImInMem<Type> * TypedGetImOfSigma(double aSig);
         cTplOctDig<U_INT2> * U_Int2_This() ;
         cTplOctDig<REAL4> *  REAL4_This() ;

         const std::vector<cTplImInMem<Type> *> &  VTplIms() const;
         void DoSiftExtract(int aK);
    private :

         void DoSiftExtract(int aK,const cSiftCarac &) ;
         void DoSiftExtract(const cSiftCarac &) ;
         void PostPyram() ;
         cTplImInMem<Type> * AllocTypedIm(double aResolOctaveBase,int aK,int IndexSigma);

        std::vector<cTplImInMem<Type> *>  mVTplIms;
        std::vector<Type **>  mVDatas;
        Type ***              mCube;
        // cTplImInMem<Type> *  mImBase;
    private :
        cTplOctDig(const cTplOctDig<Type> &);  // N.I.
};



class cImDigeo
{
     public :
         cImDigeo
         (
              int aNum,
              const cImageDigeo &,
              const std::string & aName,
              cAppliDigeo &
         );

        // Est ce que le point a la resolution de calcul doit etre sauve
        bool PtResolCalcSauv(const Pt2dr & aP);
        // void ComputeCarac();
        const std::string  &  Name() const;
        cAppliDigeo &  Appli();
        const Box2di & BoxImCalc() const;

 // Pour pouvoir se dimentionner au "pire" des cas, chaque image est
 // d'abord notifiee de l'existence d'une box
        void NotifUseBox(const Box2di &);
        void AllocImages();
        void LoadImageAndPyram(const Box2di & aBoxIn,const Box2di & aBoxOut);
        void DoCalcGradMoy(int aDZ);



       void DoExtract();
       const cImageDigeo &  IMD();  // La structure XML !!!
       double Resol() const;
       cVisuCaracDigeo  *  CurVisu();
       cOctaveDigeo & GetOctOfDZ(int aDZ); 
       cOctaveDigeo * SVPGetOctOfDZ(int aDZ); 

       const Pt2di& SzCur() const;
       const Pt2di& P0Cur() const;

       void SetDyn(double);
       double GetDyn() const;
       void SetMaxValue(REAL8);
       REAL8 GetMaxValue() const;
       double GradMoyCorrecDyn() const;
       const Box2di &   BoxCurIn ();
       const Box2di &   BoxCurOut ();
       const std::vector<cOctaveDigeo *> &   Octaves() const;
       Tiff_Im TifF();
     private :


        void DoSiftExtract();

        GenIm::type_el  TypeOfDeZoom(int aDZ,cModifGCC *) const;

        std::string                   mName;
        cAppliDigeo &                 mAppli;
        const cImageDigeo &           mIMD;
        int                           mNum;
        std::vector<cImInMem *>       mVIms;
        Tiff_Im *                     mTifF;
        double                        mResol;

        Pt2di                         mSzGlobR1;
        Box2di                        mBoxGlobR1;
        Box2di                        mBoxImR1;
        Box2di                        mBoxImCalc;

        Pt2di                         mSzCur;
        Pt2di                         mP0Cur;
        Box2di                        mBoxCurIn;
        Box2di                        mBoxCurOut;
        std::vector<cOctaveDigeo *>   mOctaves;
        Pt2di                         mSzMax;
        int                           mNiv;
        cVisuCaracDigeo  *  mVisu;

        bool                         mG2MoyIsCalc;
        double                       mGradMoy;
        double                       mDyn;
		REAL8			  			 mMaxValue; // valeur max d'un pixel, utilisée pour la normalisation du gradient
        Im2DGen *                    mFileInMem;
     private :
        cImDigeo(const cImDigeo &);  // N.I.
        
};

template <class Type> class cConvolSpec
{
    public :
        typedef typename El_CTypeTraits<Type>::tBase tBase;

        virtual void Convol(Type * Out,Type * In,int aK0,int aK1) ;

        virtual void ConvolCol(Type * Out,Type **In,int aX0,int aX1,int anYIn) ;


        static cConvolSpec<Type> * GetExisting(tBase* aFilter,int aDeb,int aFin,int aNbShitX,bool ForGC);
        static cConvolSpec<Type> * GetOrCreate(tBase* aFilter,int aDeb,int aFin,int aNbShitX,bool ForGC);

        cConvolSpec(tBase* aFilter,int aDeb,int aFin,int aNbShitX,bool ForGC);
        virtual bool IsCompiled() const;
        int Deb() const;
        int Fin() const;
        bool Sym() const;
        tBase *  DataCoeff();
    protected :

    private :
        bool Match(tBase *  aDFilter,int aDebX,int aFinX,int  aNbShitX,bool ForGC);
        static std::vector<cConvolSpec<Type> *>   theVec;
        

        int mNbShift;
        int mDeb;
        int mFin;
        std::vector<tBase>  mCoeffs;
// Quand on veut les generer, certain existent deja, pour ne pas les confondre dans la gestion
// de l'unicite, on rajoute ce booleen
        bool mForGC;
        tBase *             mDataCoeff;
        bool                mSym;
        bool                mFirstGet;
        

        cConvolSpec(const cConvolSpec<Type> &); // N.I.
};


class cVisuCaracDigeo
{
     public :
        cVisuCaracDigeo(cAppliDigeo &,Pt2di aSz,int aZ,Fonc_Num aF,const cParamVisuCarac &); 
        void Save(const std::string&);
        void SetPtsCarac 
             (
                 const Pt2dr & aP,
                 bool aMax,
                 double aSigma,
                 int  aIndSigma,
                 eTypeExtreSift
                 
             );
     private :
        cAppliDigeo &      mAppli;
        Pt2di              mSz1;
        int                mZ;
        Pt2di              mSzZ;
        Im2D_U_INT1        mIm;
        TIm2D<U_INT1,INT>  mTIm;
        const cParamVisuCarac & mParam;
        int          mDynG;
};


class cAppliDigeo : public cParamDigeo
{
    public : 
       friend cAppliDigeo * DigeoCPP
              (
                    const std::string & aFullNameIm,
                    const cParamAppliDigeo  aParam
              );

       cAppliDigeo
       ( 
              cResultSubstAndStdGetFile<cParamDigeo> aParam,
              cAppliDigeo *                          aMaterAppli,
              cModifGCC *                            aModif,
              bool                                   IsLastGCC

       );

        void DoAll();
        const std::string & DC() const;
        cInterfChantierNameManipulateur * ICNM();
        void DoOneInterv(int aK,bool DoExtract);
        void LoadOneInterv(int aKB);
        int  NbInterv() const;



       FILE *  FileGGC_H();
       FILE *  FileGGC_Cpp();
       bool    MultiBloc() const;

       cModifGCC *      ModifGCC() const;

       cImDigeo & SingleImage();
       cSiftCarac *  RequireSiftCarac();
       cSiftCarac *  SiftCarac();


    private :
       void InitAllImage();
       void DoAllInterv();
       
       static void InitConvolSpec();


       void AllocImages();

       std::string                       mDC;
       cInterfChantierNameManipulateur * mICNM;
       std::vector<cImDigeo *>           mVIms;

       cAppliDigeo *                     mMaster;
       cModifGCC *                       mModifGCC;
       bool                              mLastGCC;
       FILE *                            mFileGGC_H;
       FILE *                            mFileGGC_Cpp;
       cDecoupageInterv2D                mDecoupInt;
       Box2di                            mBoxIn;
       Box2di                            mBoxOut;

       cSiftCarac *                     mSiftCarac;

     private :
        cAppliDigeo(const cAppliDigeo &);  // N.I.
        

};

#define InstantiateClassTplDigeo(aClass)\
template  class aClass<U_INT1>;\
template  class aClass<U_INT2>;\
template  class aClass<REAL4>;\
template  class aClass<REAL8>;\
template  class aClass<INT>;

// =========================  INTERFACE EXTERNE ======================


class cParamAppliDigeo
{
    public :

        double   mSigma0;
        double   mResolInit;  // 0.5 means -1 with usual Sift++ convention ; 1.0 means 0 ....
        int      mOctaveMax;
        int      mNivByOctave;
        bool     mExigeCodeCompile;
        int      mNivFloatIm;        // Ne depend pas de la resolution
        bool     mSauvPyram;        // Pour Mise au point, sauve ttes les pyramides
        double   mRatioGrad;  // Le gradient doit etre > a mRatioGrad le gradient moyen

        cParamAppliDigeo() :
            mSigma0           (1.6),
            mResolInit        (1.0),
            mOctaveMax        (32),
            mNivByOctave      (3),
            mExigeCodeCompile (false),
            mNivFloatIm       (4),
            mSauvPyram        (false),
            mRatioGrad        (0.05)
        {

        }
};

cAppliDigeo * DigeoCPP
              (
                    const std::string & aFullNameIm,
                    const cParamAppliDigeo  aParam
              );




#endif //  _ELISE_DIGEO_H_




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
