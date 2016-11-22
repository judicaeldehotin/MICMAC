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


#include "TiepTri.h"


/************************************************/
/*                                              */
/*          cImTieTri                           */
/*                                              */
/************************************************/

cImTieTri::cImTieTri(cAppliTieTri & anAppli ,const std::string& aNameIm,int aNum) :
   mAppli   (anAppli),
   mNameIm  (aNameIm),
   mTif     (Tiff_Im::StdConv(mAppli.Dir() + mNameIm)),
   mCam     (mAppli.ICNM()->StdCamOfNames(aNameIm,mAppli.Ori())),
   mImInit   (1,1),
   mTImInit  (mImInit),
   mMasqTri  (1,1),
   mTMasqTri (mMasqTri),
   mRab      (20),
   mW        (0),
   mNum      (aNum)
{

    std::cout << "OK " << mNameIm << " F=" << mCam->Focale() << " Num="<<mNum<<"\n";
}

bool cImTieTri::LoadTri(const cXml_Triangle3DForTieP &  aTri)
{
    if (
               (!mCam->PIsVisibleInImage(aTri.P1()))
            || (!mCam->PIsVisibleInImage(aTri.P2()))
            || (!mCam->PIsVisibleInImage(aTri.P3()))
       )
    {
        return  false;
    }


    mP1Glob = mCam->R3toF2(aTri.P1());
    mP2Glob = mCam->R3toF2(aTri.P2());
    mP3Glob = mCam->R3toF2(aTri.P3());
    mVTriGlob.clear();
    mVTriGlob.push_back(mP1Glob);
    mVTriGlob.push_back(mP2Glob);
    mVTriGlob.push_back(mP3Glob);

    if (IsMaster() && mAppli.HasPtSelecTri())
    {
         if (!PointInPoly(mVTriGlob,mAppli.PtsSelectTri()))
            return false;

         for (int aK=0 ; aK<int(mVTriGlob.size()) ; aK++)
             std::cout << "PTRI=" << mVTriGlob[aK] << "\n";
         std::cout << "PLOC " << mCam->R3toL3(aTri.P1()) << "\n";
         std::cout << "SIGNTRI= " <<  ((mP2Glob-mP1Glob) ^(mP3Glob-mP1Glob)) << "\n";
         getchar();
    }

    double aSurf =  (mP1Glob-mP2Glob) ^ (mP1Glob-mP3Glob);



    if (ElAbs(aSurf) < TT_SEUIL_SURF_TRI_PIXEL)
    {
        return  false;
    }

    // std::cout << "SURF = " << aSurf  << " " << mP1Glob << mP2Glob << mP3Glob << "\n";



    Pt2dr aP0 = Inf(Inf(mP1Glob,mP2Glob),mP3Glob) - Pt2dr(mRab,mRab);
    Pt2dr aP1 = Sup(Sup(mP1Glob,mP2Glob),mP3Glob) + Pt2dr(mRab,mRab);

    mDecal = round_down(aP0);
    mSzIm  = round_up(aP1-aP0);

    mP1Loc = mP1Glob - Pt2dr(mDecal);
    mP2Loc = mP2Glob - Pt2dr(mDecal);
    mP3Loc = mP3Glob - Pt2dr(mDecal);


    // Charge l'image
    mImInit.Resize(mSzIm);
    mTImInit =  TIm2D<tElTiepTri,tElTiepTri>(mImInit);
    ELISE_COPY(mImInit.all_pts(),trans(mTif.in(0),mDecal),mImInit.out());


    // Remplit l'image de masque avec les point qui sont dans le triangle
    mMasqTri =  Im2D_Bits<1>(mSzIm.x,mSzIm.y,0);
    mTMasqTri = TIm2DBits<1> (mMasqTri);
    ElList<Pt2di>  aLTri;
    aLTri = aLTri + round_ni(mP1Glob-Pt2dr(mDecal));
    aLTri = aLTri + round_ni(mP2Glob-Pt2dr(mDecal));
    aLTri = aLTri + round_ni(mP3Glob-Pt2dr(mDecal));
    ELISE_COPY(polygone(aLTri),1,mMasqTri.oclip());


    if (mAppli.NivInterac() > 0)
    {
        std::cout << "   LOAD " << mDecal << " " << mSzIm << "\n";
    }
    if ((mW ==0) && (mAppli.WithW()) && (IsMaster() || (mAppli.NumImageIsSelect(mNum))))
    {
         int aZ = mAppli.ZoomW();
         mW = Video_Win::PtrWStd(mAppli.SzW()*aZ,true,Pt2dr(aZ,aZ));
         mW = mW-> PtrChc(Pt2dr(0,0),Pt2dr(aZ,aZ),true);
         std::string aTitle = std::string(IsMaster() ? "*** " : "") + mNameIm;
         mW->set_title(aTitle.c_str());
    }

   
    if (mW)
    {
         ELISE_COPY(mImInit.all_pts(),Min(255,Max(0,255-mImInit.in())),mW->ogray());

         ELISE_COPY(select(mImInit.all_pts(),mMasqTri.in()),Min(255,Max(0,mImInit.in())),mW->ogray());


         // mW->clik_in();
    }
    return true;
}

/*
template <class Type> int  CmpValAndDec(const Type & aV1,const Type & aV2, const Pt2di & aDec)
{
   //    aV1 =>   aV1 + eps * aDec.x + eps * esp * aDec

   if (aV1 < aV2) return -1;
   if (aV1 > aV2) return  1;

   if (aDec.x<0)  return -1;
   if (aDec.x>0)  return  1;

   if (aDec.y<0)  return -1;
   if (aDec.y>0)  return  1;

   return 0;
}
*/

  
int cImTieTri::IsExtrema(const TIm2D<tElTiepTri,tElTiepTri> & anIm,Pt2di aP)
{
// bool aPSpec = (aP==Pt2di(90,69));
    tElTiepTri aValCentr = anIm.get(aP);
    const std::vector<Pt2di> &  aVE = mAppli.VoisExtr();



    int aCmp0 =0;
    for (int aKP=0 ; aKP<int(aVE.size()) ; aKP++)
    {
        int aCmp = CmpValAndDec(aValCentr,anIm.get(aP+aVE[aKP]),aVE[aKP]);
        if (aKP==0) 
        {
            aCmp0 = aCmp;
            if (aCmp0==0) return 0;
        }

        if (aCmp!=aCmp0) return 0;
    }
    return aCmp0;
}

Col_Pal  cImTieTri::ColOfType(eTypeTieTri aType)
{
    switch (aType)
    {
          case eTTTMax : return mW->pdisc()(P8COL::red);
          case eTTTMin : return mW->pdisc()(P8COL::blue);
          default :;
    }
   return mW->pdisc()(P8COL::yellow);
}



void  cImTieTri::MakeInterestPoint
      (
            std::list<cIntTieTriInterest> * aListPI,
            TIm2D<U_INT1,INT>  * aImLabel,
            const TIm2DBits<1> & aMasq,const TIm2D<tElTiepTri,tElTiepTri> & anIm
      )
{
    Pt2di aP;
    Pt2di aSzIm = anIm.sz();

    // Calcul des maxima et minima
    for (aP.x=0 ; aP.x<aSzIm.x ; aP.x++)
    {
        for (aP.y=0 ; aP.y<aSzIm.y ; aP.y++)
        {
             // bool aPSpec = (aP==Pt2di(90,69));


             // if (aPSpec) std::cout << "MASQ=" << aMasq.get(aP) << "\n";
            if (aMasq.get(aP))
            {
                int aCmp0 =  IsExtrema(anIm,aP);

                if (aCmp0)
                {
                   eTypeTieTri aType = (aCmp0==1)  ? eTTTMax : eTTTMin;
                   if (mW)
                   {
                       // mW->draw_circle_loc(Pt2dr(aP),2.0,mW->pdisc()(IsMax ? P8COL::red : P8COL::blue));
                       if ((IsMaster()) || (mAppli.NivInterac()>=2))
                       {
                           mW->draw_circle_loc(Pt2dr(aP),1.5,ColOfType(aType));
                       }
                   }
                   if  (aImLabel) 
                        aImLabel->oset(aP,aType);
                   if (aListPI)
                   {
                        aListPI->push_back(cIntTieTriInterest(aP,aType));
                   }
                }
            }
        }
    }
}


void  cImTieTri::MakeInterestPointFAST
      (
            std::list<cIntTieTriInterest> * aListPI,
            TIm2D<U_INT1,INT>  * aImLabel,
            const TIm2DBits<1> & aMasq,const TIm2D<tElTiepTri,tElTiepTri> & anIm
      )
{
    FastNew *aDec = new FastNew(anIm, 15, 3, aMasq);
    eTypeTieTri aType = eTTTMax;
    vector<Pt2dr> lstPt = aDec->lstPt();
    for (uint i=0; i<lstPt.size(); i++)
    {
        Pt2di aP = ToPt2di(lstPt[i]);
        if (mW)
            mW->draw_circle_loc(Pt2dr(aP),1.5,ColOfType(aType));
        if (aImLabel)
            aImLabel->oset(aP,aType);
        if (aListPI)
            aListPI->push_back(cIntTieTriInterest(aP,aType));
    }
}


Video_Win * cImTieTri::W() {return mW;}
const Pt2di & cImTieTri::Decal() const {return mDecal;}
const int & cImTieTri::Num() const {return mNum;}






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
aooter-MicMac-eLiSe-25/06/2007*/
