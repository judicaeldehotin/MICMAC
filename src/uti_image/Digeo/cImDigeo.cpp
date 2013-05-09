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

#include "Digeo.h"

Video_Win * aW1Digeo;
// Video_Win * aW2Digeo;
// Video_Win * aW3Digeo;
// Video_Win * aW4Digeo;
Video_Win * aW5Digeo;

void  calc_norm_grad
      (
            double ** out,
            double *** in,
            const Simple_OPBuf_Gen & arg
      )
{
    Tjs_El_User.ElAssert
    (
          arg.dim_in() == 1,
          EEM0 << "calc_norm_grad requires dim out = 1 for func"
    );

   double * l0 = in[0][0];
   double * l1 = in[0][1];

   double * g2 = out[0];

   for (INT x=arg.x0() ;  x<arg.x1() ; x++)
   {
       g2[x] = ElSquare(l0[x+1]-l0[x]) + ElSquare(l1[x]-l0[x]);
   }
}

Fonc_Num norm_grad(Fonc_Num f)
{
     return create_op_buf_simple_tpl
            (
                0,  // Nouvelle syntaxe
                calc_norm_grad,
                f,
                1,
                Box2di(Pt2di(0,0),Pt2di(1,1))
            );
}




/****************************************/
/*                                      */
/*             cImDigeo                 */
/*                                      */
/****************************************/

cImDigeo::cImDigeo
(
   int                 aNum,
   const cImageDigeo & aIMD,
   const std::string & aName,
   cAppliDigeo &       anAppli
) :
  mName        (aName),
  mAppli       (anAppli),
  mIMD         (aIMD),
  mNum         (aNum),
  // mTifF        (new Tiff_Im(Tiff_Im::StdConv(mAppli.DC()+mName))),
  mTifF        (new Tiff_Im(Tiff_Im::StdConvGen(mAppli.DC()+mName,1,true))),
  mResol       (aIMD.ResolInit().Val()),
  mSzGlobR1    (mTifF->sz()),
  mBoxGlobR1   (Pt2di(0,0),mSzGlobR1),
  mBoxImR1     (Inf(mIMD.BoxImR1().ValWithDef(mBoxGlobR1),mBoxGlobR1)),
  mBoxImCalc   (round_ni(Pt2dr(mBoxImR1._p0)/mResol),round_ni(Pt2dr(mBoxImR1._p1)/mResol)),

  mSzMax       (0,0),
  mVisu        (0),
  mG2MoyIsCalc (false),
  mDyn         (1.0),
  mFileInMem   (0)
{
   //Provisoire
   ELISE_ASSERT(! aIMD.PredicteurGeom().IsInit(),"Asservissement pas encore gere");

   Pt2di aSzIR1 = mBoxImR1.sz();
   double aNbLoad  = (double(aSzIR1.x) * double(aSzIR1.y)  * mTifF->bitpp() ) /8.0;
   if (aNbLoad<aIMD.NbOctetLimitLoadImageOnce().Val())
   {
      mFileInMem = Ptr_D2alloc_im2d(mTifF->type_el(),aSzIR1.x,aSzIR1.y);
      ELISE_COPY
      (
           mFileInMem->all_pts(),
           trans(mTifF->in(),mBoxImR1._p0),
           mFileInMem->out()
      );
      mG2MoyIsCalc= true;
      mGradMoy = sqrt(mFileInMem->MoyG2());
   }
   else
   {
        Pt2di aSz = mTifF->sz() - Pt2di(1,1);
        double aSom;
        ELISE_COPY
        (
              rectangle(Pt2di(0,0),aSz),
              norm_grad(mTifF->in()),
              sigma(aSom)
        );
        aSom /= aSz.x * double(aSz.y);
        mG2MoyIsCalc= true;
        mGradMoy = sqrt(aSom);
   }

   // Verification de coherence
   if (aNum==0)
   {
        ELISE_ASSERT(! aIMD.PredicteurGeom().IsInit(),"Asservissement sur image maitresse ?? ");
   }
   else
   {
       if ( aIMD.PredicteurGeom().IsInit())
       {
          //Provisoire
          ELISE_ASSERT(!aIMD.BoxImR1().IsInit()," Asservissement et Box Im sec => redondant ?");
       }
       else
       {
          ELISE_ASSERT
          (
             ! mAppli.DigeoDecoupageCarac().IsInit(),
             "Decoupage+Multimage => Asservissement requis"
          );
          
       }
   }
}

Tiff_Im cImDigeo::TifF()
{
   ELISE_ASSERT(mTifF!=0,"cImDigeo::TifF");
   return *mTifF;
}

double cImDigeo::Resol() const
{
   return mResol;
}


const Box2di & cImDigeo::BoxImCalc() const
{
   return mBoxImCalc;
}

const std::vector<cOctaveDigeo *> &   cImDigeo::Octaves() const
{
   return mOctaves;
}


void cImDigeo::NotifUseBox(const Box2di & aBox)
{
  if (mIMD.PredicteurGeom().IsInit())
  {
       ELISE_ASSERT(false,"NotifUseBox :: Asservissement pas encore gere");
  }
  else
  {
      mSzMax.SetSup(aBox.sz());
  }
}



GenIm::type_el  cImDigeo::TypeOfDeZoom(int aDZ,cModifGCC * aMGCC) const
{
   if (aMGCC)
      return Xml2EL(aMGCC->TypeNum());
// std::cout << "cImDigeo::TypeOfDeZoom " << aMGCC << "\n";
   GenIm::type_el aRes = mTifF->type_el();
   if  (! type_im_integral(aRes))  
   {
      return aRes;
   }
   if (aRes==GenIm::int4)
      return GenIm::real8;

   int aDZMax = -10000000;
   for 
   (
       std::list<cTypeNumeriqueOfNiv>::const_iterator itP=mAppli.TypeNumeriqueOfNiv().begin();
       itP!=mAppli.TypeNumeriqueOfNiv().end();
       itP++
   )
   {
      int aNiv = itP->Niv();
      if  ((aNiv>=aDZMax) && (aNiv<=aDZ))
      {
         aRes = Xml2EL(itP->Type());
         aDZMax = aNiv;
      }
   }
   return aRes;
}


void cImDigeo::AllocImages()
{
   cModifGCC * aMGCC = mAppli.ModifGCC();
   Pt2di aSz = mSzMax;
   mNiv=0;

   const cTypePyramide & aTP = mAppli.TypePyramide();
   if (aTP.NivPyramBasique().IsInit())
      mNiv = aTP.NivPyramBasique().Val();
   else if (aTP.PyramideGaussienne().IsInit())
      mNiv = aTP.PyramideGaussienne().Val().NivOctaveMax();
   else
   {
        ELISE_ASSERT(false,"cImDigeo::AllocImages PyramideImage");
   }

   int aNivDZ = 0;

   cOctaveDigeo * aLastOct = 0;
   for (int aDz = 1 ; aDz <=mNiv ; aDz*=2)
   {
       cOctaveDigeo * anOct =   aLastOct                                                   ?
                                aLastOct->AllocDown(TypeOfDeZoom(aDz,aMGCC),*this,aDz,aSz)       :
                                cOctaveDigeo::AllocTop(TypeOfDeZoom(aDz,aMGCC),*this,aDz,aSz)       ;
       mOctaves.push_back(anOct);
       if (aTP.NivPyramBasique().IsInit())
       {
          // mVIms.push_back(cImInMem::Alloc (*this,aSz,TypeOfDeZoom(aDz), *anOct, 1.0));
 // C'est l'image Bas qui servira
 //         mVIms.push_back(anOct->AllocIm(1.0,0));
 
       }
       else if (aTP.PyramideGaussienne().IsInit())
       {
            const cPyramideGaussienne &  aPG = aTP.PyramideGaussienne().Val();
            int aNbIm = aPG.NbByOctave().Val();
            if (aMGCC)
               aNbIm = aMGCC->NbByOctave();

            if (aPG.NbInLastOctave().IsInit() && (aDz*2>mNiv))
               aNbIm = aPG.NbInLastOctave().Val();
            int aK0 = 0;
            if (aDz==1)
               aK0 = aPG.IndexFreqInFirstOctave().Val();
           anOct->SetNbImOri(aNbIm);
            for (int aK=aK0 ; aK< aNbIm+3 ; aK++)
            {
                double aSigma =  pow(2.0,aK/double(aNbIm));
                //mVIms.push_back(cImInMem::Alloc (*this,aSz,TypeOfDeZoom(aDz), *anOct,aSigma));
                mVIms.push_back((anOct->AllocIm(aSigma,aK,aNivDZ*aNbIm+(aK-aK0))));
            }
                
       }
       aSz = (aSz+Pt2di(1,1)) /2 ;
       aNivDZ++;

       aLastOct = anOct;
   }

   for (int aK=1 ; aK<int(mVIms.size()) ; aK++)
   {
      mVIms[aK]->SetMere(mVIms[aK-1]);
   }
}

bool cImDigeo::PtResolCalcSauv(const Pt2dr & aP)
{
   return    (aP.x>=mBoxCurOut._p0.x)
          && (aP.x <mBoxCurOut._p1.x)
          && (aP.y>=mBoxCurOut._p0.y)
          && (aP.y <mBoxCurOut._p1.y) ;
}


void cImDigeo::LoadImageAndPyram(const Box2di & aBoxIn,const Box2di & aBoxOut)
{
    const cTypePyramide & aTP = mAppli.TypePyramide();

    mBoxCurIn = aBoxIn;
    mBoxCurOut = aBoxOut;
    ElTimer aChrono;
    mSzCur = aBoxIn.sz();
    mP0Cur = aBoxIn._p0;

    for (int aK=0 ; aK<int(mOctaves.size()) ; aK++)
    {
       mOctaves[aK]->SetBoxInOut(aBoxIn,aBoxOut);
    }


    // Fonc_Num aF = trans(aF,aBoxIn._p0);
    Fonc_Num aF = mTifF->in_proj();
    if (mFileInMem)
    {
       aF = trans(mFileInMem->in_proj(),-mBoxImR1._p0);
    }


    if (0)
    {
        aW1Digeo = Video_Win::PtrWStd(Pt2di(500,300));
        aW5Digeo = Video_Win::PtrWStd(Pt2di(500,300)); aW5Digeo->set_title("55555");

        Fonc_Num aFT = ((Abs(FX-100-FY)<10)||(Abs(FX-200-FY)<10))*128;
        aFT = 128 * ((FX-50)>FY);
        aFT = 255 * (((FX/20)+(FY/30))%2);
        ELISE_COPY(aW1Digeo->all_pts(),aFT,aW1Digeo->ogray());
        getchar();
        ELISE_COPY(aW1Digeo->all_pts(),GaussSepFilter(aFT,5.25,1e-3),aW5Digeo->ogray());
        getchar();
    }


    if (aTP.PyramideGaussienne().IsInit())
    {
        double aSigma = aTP.PyramideGaussienne().Val().Sigma0().Val();

// Dans les deux cas le changement d'echelle rajoute du flou
        if (mResol > 1.0)
        {
           aSigma = sqrt(ElMax(0.0,ElSquare(aSigma)-ElSquare(1/mResol)));
        }
        else if (mResol<1.0)
        {
           aSigma = sqrt(ElMax(0.0,ElSquare(aSigma)-ElSquare(1/mResol)));
        }

        aF = GaussSepFilter(aF,aSigma,1e-3);
    }

// std::cout << "Rrrrrrrrrrr "<< mResol << " " << mFileInMem << "\n";
    Pt2dr aTrR = Pt2dr(aBoxIn._p0) *mResol;
    Pt2dr aPSc = Pt2dr(mResol,mResol);

    aF = (mResol==1.0)                             ?
         trans(aF,aBoxIn._p0)                      :
         (
            (mResol < 1)                       ?
            StdFoncChScale_Bilin(aF,aTrR,aPSc) :
            StdFoncChScale(aF,aTrR,aPSc) 
         );

    mOctaves[0]->FirstImage()->LoadFile(aF,aBoxIn,mTifF->type_el());
    // mVIms[0]->LoadFile(*mTifF,aBox);

    double aTLoad = aChrono.uval();
    aChrono.reinit();
   
/*
    if (aTP.PyramideGaussienne().IsInit())
    {
         mVIms[0]->MakeConvolInit(aTP.ConvolFirstImage().Val());
         mVIms[0]->SauvIm();
    }
*/


    
    for (int aK=0 ; aK< int(mVIms.size()) ; aK++)
    {
       if (aK>0)
       {
          if (aTP.NivPyramBasique().IsInit())
          {
             mVIms[aK]->VMakeReduce_121(*(mVIms[aK-1]));
          }
          else if (aTP.PyramideGaussienne().IsInit())
          {
             mVIms[aK]->ReduceGaussienne();
          }
       }
       mVIms[aK]->SauvIm();
    }

    for (int aKOct=0 ; aKOct<int(mOctaves.size()) ; aKOct++)
    {
        mOctaves[aKOct]->PostPyram();
    }


    double aTPyram = aChrono.uval();
    aChrono.reinit();

    if (mAppli.ShowTimes().Val())
    {
        std::cout << "Time,  load : " << aTLoad << " ; Pyram : " << aTPyram << "\n";
    }

}

void cImDigeo::DoExtract()
{
    if (mIMD.VisuCarac().IsInit())
    {
        const cParamVisuCarac & aPVC = mIMD.VisuCarac().Val();
        mVisu = new cVisuCaracDigeo
                    (
                       mAppli,
                       mSzCur,
                       aPVC.Zoom().Val(),
                       mOctaves[0]->FirstImage()->Im().in_proj() * aPVC.Dyn(),
                       aPVC
                    );
    }
    ElTimer aChrono;

    DoSiftExtract();

    if (mAppli.ShowTimes().Val())
    {
        std::cout << "Time,  Extrema : " << aChrono.uval() << "\n";
    }

    if (mVisu)
    {
       mVisu->Save(mName);
       delete mVisu;
       mVisu = 0;
    }
}


void cImDigeo::DoCalcGradMoy(int aDZ)
{
   if (mG2MoyIsCalc)
      return;

   mG2MoyIsCalc = true;

   if (mAppli.MultiBloc())
   {
      ELISE_ASSERT(false,"DoCalcGradMoy : Multi Bloc a gerer");
   }

   ElTimer aChrono;
   mGradMoy = sqrt(GetOctOfDZ(aDZ).FirstImage()->CalcGrad2Moy());

   std::cout << "Grad = " << GradMoyCorrecDyn() <<  " Time =" << aChrono.uval() << "\n";
}


void cImDigeo::DoSiftExtract()
{
   ELISE_ASSERT(false,"cImDigeo::DoSiftExtract deprecated");
/*
std::cout << "SIFT " << (mAppli.SiftCarac() != 0) << "\n";
    if (!mAppli.SiftCarac())
       return;
    const cSiftCarac &  aSC =  *(mAppli.SiftCarac());
    DoCalcGradMoy(aSC.NivEstimGradMoy().Val());
    ELISE_ASSERT(mAppli.PyramideGaussienne().IsInit(),"Sift require Gauss Pyr");
    for (int aKoct=0; aKoct<int(mOctaves.size());aKoct++)
    {
         mOctaves[aKoct]->DoSiftExtract(aSC);
    }
*/
    
}

cOctaveDigeo * cImDigeo::SVPGetOctOfDZ(int aDZ)
{
   for (int aK=0 ; aK<int(mOctaves.size()) ; aK++)
   {
      if (mOctaves[aK]->Niv() == aDZ)
      {
          return mOctaves[aK];
      }
   }
   return 0;
}

cOctaveDigeo & cImDigeo::GetOctOfDZ(int aDZ)
{
   cOctaveDigeo * aRes = SVPGetOctOfDZ(aDZ);

   ELISE_ASSERT(aRes!=0,"cAppliDigeo::GetOctOfDZ");

   return *aRes;
}


double cImDigeo::GetDyn() const
{
    return mDyn;
}

void cImDigeo::SetDyn(double aDyn)
{
    mDyn = aDyn;
}

REAL8 cImDigeo::GetMaxValue() const
{
    return mMaxValue;
}

void cImDigeo::SetMaxValue(REAL8 i_maxValue)
{
    mMaxValue = i_maxValue;
}

const Pt2di& cImDigeo::SzCur() const {return mSzCur;}
const Pt2di& cImDigeo::P0Cur() const {return mP0Cur;}


const std::string  &  cImDigeo::Name() const {return mName;}
cAppliDigeo &  cImDigeo::Appli() {return mAppli;}
const cImageDigeo &  cImDigeo::IMD() {return mIMD;}
cVisuCaracDigeo  *   cImDigeo::CurVisu() {return mVisu;}

double cImDigeo::GradMoyCorrecDyn() const 
{
   ELISE_ASSERT(mG2MoyIsCalc,"cImDigeo::G2Moy");
   return mGradMoy * mDyn;
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
