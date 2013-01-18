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


using namespace NS_ParamChantierPhotogram;
using namespace NS_SuperposeImage;


cParamModifGeomMTDNuage::cParamModifGeomMTDNuage
(
            double aScale,
            Box2dr aBox  
) :
   mScale (aScale),
   mBox   (aBox)
{
}



/***********************************************/
/*                                             */
/*       cElNuage3DMaille_FromImProf           */
/*                                             */
/***********************************************/


template <class Type,class TBase> 
        class cElNuage3DMaille_FromImProf : public cElNuage3DMaille
{
     public :

         cElNuage3DMaille_FromImProf
         (
              const std::string &             aDir,
              const cXML_ParamNuage3DMaille & aNuage,
              Fonc_Num  aFMasq,
              Fonc_Num  aFProf
         );

/*
         cElNuage3DMaille_FromImProf
         (
               
               const cXML_ParamNuage3DMaille & aNuage
         );
*/

         bool HasProfondeur() const { return true; }


         Im2DGen *   ImProf() const
         {
             return & const_cast<cElNuage3DMaille_FromImProf *>(this)->mIm;
         }
         double ProfOfIndex(const tIndex2D & anI) const
         {
             return PTab2PReel(mTIm.get(anI));
         }

         double ProfOfIndexInterpol(const Pt2dr & aP) const
         {
             return PTab2PReel(mTIm.getr(aP));
         }

         double   ProfOfIndexInterpolWithDef(const Pt2dr  & aP,double aDef) const
         {
             return PTab2PReel(mTIm.getr(aP,ElStdTypeScal<TBase>::RtoT(aDef)));
         }

         void SetProfOfIndex(const tIndex2D & anI,double aProf) 
         {
              mTIm.oset
              (
                    anI,
                    // ElStdTypeScal<TBase>::RtoT((aProf-mProf0)/ mResolProf)
                    ElStdTypeScal<TBase>::RtoT(PReel2Tab(aProf))
              );
         }

         bool SetProfOfIndexIfSup(const tIndex2D & anI,double aProf)
         {
              // TBase aV = ElStdTypeScal<TBase>::RtoT((aProf-mProf0)/ mResolProf);
              TBase aV = ElStdTypeScal<TBase>::RtoT(PReel2Tab(aProf));
              if (aV > mTIm.get(anI))
              {
                  mTIm.oset(anI,aV);
                 return true;
              }
              return false;
         }


         void VerifParams() const;
         Pt3dr Loc_PtOfIndex(const tIndex2D & aP) const;

          void V_Save(const std::string & aNameP);

         Pt3dr Loc_IndexAndProfPixel2Euclid(const Pt2dr & anI,const double & anInvProf) const
         {
             return Loc_IndexAndProf2Euclid(anI,this->PTab2PReel(anInvProf));
         }

         Pt3dr Loc_Euclid2ProfPixelAndIndex(const   Pt3dr & aP) const
         {
              Pt3dr aRes = Loc_Euclid2ProfAndIndex(aP);
              return Pt3dr(aRes.x,aRes.y,PReel2Tab(aP.z));
         }

         double  ProfEnPixel(const Pt2di & aP) const
         {
              return this->mTIm.getproj(aP);
         }
         double  ProfInterpEnPixel(const Pt2dr & aP) const 
         {
              return this->mTIm.getprojR(aP);
         }

     protected :

         Im2D<Type,TBase> mIm;
         TIm2D<Type,TBase> mTIm;
         double            mProf0;
         double            mResolProf;
        
     private :
         double PTab2PReel(const double aProf) const
         {
             return  mProf0 + mResolProf * aProf;
         }
         double PReel2Tab(const double aProf) const
         {
             return  (aProf-mProf0)/mResolProf;
         }
};


template <class Type,class TBase>  void  cElNuage3DMaille_FromImProf<Type,TBase>::VerifParams() const
{
    const cXML_ParamNuage3DMaille&  aNuage =  this->Params(); 

    for
    (
          std::list<cVerifNuage>::const_iterator itVN=aNuage.VerifNuage().begin();
          itVN != aNuage.VerifNuage().end();
          itVN++
    )
    {
          Pt3dr aP1 = itVN->PointEuclid();
          Pt3dr aP2 = Loc_IndexAndProf2Euclid(itVN->IndIm(),PTab2PReel(itVN->Profondeur()));

          double aDist =  euclid(aP1-aP2);
          if (aDist>=aNuage.TolVerifNuage().Val())
          {
               cElWarning::ToVerifNuage.AddWarn
               (
                      "Dist = " + ToString(aDist) + " " + ToString(aP1.x) + " " +ToString(aP1.y) ,
                      __LINE__,
                     __FILE__
               );
          }
          // std::cout << " PIm " << itVN->IndIm() << "\n";
          // std::cout << itVN->Profondeur() << " " << PTab2PReel(itVN->Profondeur()) << "\n";
          // std::cout << euclid(aP1-aP2) << " "  << aP1 << aP2 << "\n";
    }
    // std::cout << "\n";
}
  

template <class Type,class TBase>  
         Pt3dr cElNuage3DMaille_FromImProf<Type,TBase>::Loc_PtOfIndex(const tIndex2D & anI) const
{
    return Loc_IndexAndProf2Euclid(Pt2dr(anI),ProfOfIndex(anI));
}

template <class Type,class TBase> 
    void cElNuage3DMaille_FromImProf<Type,TBase>::V_Save(const std::string & aNameP)
{
    Tiff_Im::CreateFromIm(mIm,mDir+aNameP);
}

template <class Type,class TBase>  cElNuage3DMaille_FromImProf<Type,TBase>::cElNuage3DMaille_FromImProf
(
     const std::string &             aDir,
     const cXML_ParamNuage3DMaille & aNuage,
     Fonc_Num  aFMasq,
     Fonc_Num  aFProf

)  :
   cElNuage3DMaille(aDir,aNuage,aFMasq), 
   mIm        (mSz.x,mSz.y),
   mTIm       (mIm),
   mProf0     (aNuage.Image_Profondeur().Val().OrigineAlti()),
   mResolProf (aNuage.Image_Profondeur().Val().ResolutionAlti())
{
    ELISE_COPY ( mIm.all_pts(), aFProf, mIm.out());
}

template class cElNuage3DMaille_FromImProf<INT2,INT>;
template class cElNuage3DMaille_FromImProf<float,double>;

/***********************************************/
/*                                             */
/*             cElN3D_EpipGen                  */
/*                                             */
/***********************************************/


/***********************************************/
/*                                             */
/*             cElN3D_EpipGen                  */
/*                                             */
/***********************************************/

   // Classe specialise dans le plus courant des nuages, celui
   // la geometrie epip generalisee (geometrie image et dyn en
   // 1/profondeur de champ)

template <class Type,class TBase> 
        class cElN3D_EpipGen : public cElNuage3DMaille_FromImProf<Type,TBase>
{
     public :

         cElN3D_EpipGen
         (
              const std::string &             aDir,
              const cXML_ParamNuage3DMaille & aNuage,
              Fonc_Num  aFMasq,
              Fonc_Num  aFProf,
              bool      aFaiscAndZ
         );


         typedef cElNuage3DMaille::tIndex2D tIndex2D;

         Pt3dr Loc_IndexAndProf2Euclid(const   Pt2dr &,const double &) const;
         Pt3dr Loc_Euclid2ProfAndIndex(const   Pt3dr &) const;
         void  V_SetPtOfIndex(const tIndex2D & anI,const Pt3dr & aP3);

         cElNuage3DMaille * Clone() const;
         cElN3D_EpipGen<Type,TBase> * TypedClone() const;


         cElNuage3DMaille * V_ReScale
                                    (
                                        const Box2dr &Box,
                                        double aScale,
                                        const cXML_ParamNuage3DMaille &,
                                        Im2D_REAL4 anImPds
                                    ) ;

     private :
        inline double CorZInv(const double & aZ) const
        {
           return mZIsInv ? 1/aZ : aZ;
        }

        double  ProfOfPtE(const Pt3dr & aPe) const
        {
            if (mProfIsZ) return aPe.z;

            return  CorZInv(mIsSpherik?euclid(aPe-mCentre):scal(aPe-mCentre,mDirPl));
        }

        Pt3dr        mCentre;
        Pt3dr        mDirPl;
        bool         mProfIsZ;
        bool         mZIsInv;
        bool         mIsSpherik;
        CamStenope*  mCS;
        double       mProfC;
};


template <class Type,class TBase> cElN3D_EpipGen<Type,TBase> *  cElN3D_EpipGen<Type,TBase>::TypedClone() const
{
    return new cElN3D_EpipGen<Type,TBase>
               (
                     this->mDir,
                     this->mParams,
                     Fonc_Num(0),
                     Fonc_Num(El_CTypeTraits<Type>::TronqueR(-1e5)),
                     mProfIsZ
                     // const_cast<cElN3D_EpipGen<Type,TBase> *>(this)->mImDef.in(),
                     // const_cast<cElN3D_EpipGen<Type,TBase> *>(this)->mIm.in()
               );
}

template <class Type,class TBase> cElNuage3DMaille *  cElN3D_EpipGen<Type,TBase>::Clone() const
{
   return TypedClone();
}


template <class Type,class TBase>  cElN3D_EpipGen<Type,TBase>::cElN3D_EpipGen
(
        const std::string &             aDir,
        const cXML_ParamNuage3DMaille & aNuage,
        Fonc_Num  aFMasq,
        Fonc_Num  aFProf,
        bool      aProfIsZ

)  :
   cElNuage3DMaille_FromImProf<Type,TBase>(aDir,aNuage,aFMasq,aFProf), 
   mProfIsZ   (aProfIsZ)
{
	mCentre	   = this->mCam->OrigineProf();
	mDirPl	   = this->Params().DirFaisceaux();
	mZIsInv    = this->Params().ZIsInverse();
	mIsSpherik = this->Params().IsSpherik().Val();
	mCS        = (mIsSpherik ? this->mCam->CS() : 0);
	mProfC     = scal(mDirPl,mCentre);
}

template <class Type,class TBase> cElNuage3DMaille * cElN3D_EpipGen<Type,TBase>::V_ReScale
                                    (
                                        const Box2dr &aBox,
                                        double aScale,
                                        const cXML_ParamNuage3DMaille & aNewParam,
                                        Im2D_REAL4 anImPds
                                    ) 
{
   return new cElN3D_EpipGen<float,double>
              (
                  this->mDir,
                  aNewParam,
                  anImPds.in(0) > 0.1,
                  this->ReScaleAndClip(this->mImDef.in(0)*this->mIm.in(0),aBox._p0,aScale)/Max(1e-5,anImPds.in()),
                  mProfIsZ
              );
}

template <class Type,class TBase>  
         Pt3dr cElN3D_EpipGen<Type,TBase>::Loc_IndexAndProf2Euclid(const Pt2dr & anI,const double & anInvProf) const
{

  if (mProfIsZ) 
  {
       // std::cout << anInvProf << " " << anI << " "  << this->mCam->F2AndZtoR3(anI,anInvProf)  << "\n";
      return  this->mCam->F2AndZtoR3(anI,anInvProf);
  }

   double aProf =   CorZInv(anInvProf);


   if (mIsSpherik)
   {
       return mCS->ImEtProfSpherik2Terrain(anI,aProf);
   }


    ElSeg3D aSeg =  this->mCam->F2toRayonR3(anI) ;
    Pt3dr aRay =aSeg.Tgt();
    Pt3dr aC  = aSeg.P0();

   return   aC
          + aRay * (aProf/scal(aRay,mDirPl));
}


template <class Type,class TBase>
  Pt3dr cElN3D_EpipGen<Type,TBase>::Loc_Euclid2ProfAndIndex(const   Pt3dr & aPe) const
{
    Pt2dr aPIm =  this->mCam->R3toF2(aPe);
    return Pt3dr(aPIm.x,aPIm.y,ProfOfPtE(aPe));
/*
    double aProf =   mIsSpherik                             ?
                     euclid(aPe-mCentre)                    :
                     scal(aPe-mCentre,mDirPl)               ;
    Pt2dr aPIm =  this->mCam->R3toF2(aPe);
    return Pt3dr(aPIm.x,aPIm.y,CorZInv(aProf));
*/
}




template <class Type,class TBase>  
         void cElN3D_EpipGen<Type,TBase>::V_SetPtOfIndex(const tIndex2D & anI,const Pt3dr & aP3)
{
   this->SetProfOfIndex(anI,ProfOfPtE(aP3));
/*
   double aProf =    mIsSpherik                             ?
                     euclid(aP3-mCentre)                    :
                     scal(mDirPl,aP3-mCentre)               ;
   this->SetProfOfIndex(anI, CorZInv(aProf));
*/
}


template class cElN3D_EpipGen<INT2,INT>;
template class cElN3D_EpipGen<float,double>;

/***********************************************/
/*                                             */
/*             cElNuage3DMaille                */
/*                                             */
/***********************************************/


cElNuage3DMaille * cElNuage3DMaille::FromParam
                   (
                       const cXML_ParamNuage3DMaille & aParamOri,
                       const std::string & aDir,
                       const std::string & aMasqSpec,
                       double ExagZ,
                       cParamModifGeomMTDNuage * aPMG
                   )
{
  cXML_ParamNuage3DMaille aParam = aParamOri;
  Box2di aBox(Pt2di(0,0),aParam.NbPixel());

  if (aPMG)
  {
       double aScale = aPMG->mScale;
       Pt2di  aP0 = round_down(aPMG->mBox._p0/aScale);
       Pt2di  aP1 = round_up(aPMG->mBox._p1/aScale);

       aBox = Inf(aBox,Box2di(aP0,aP1));

       aParam.NbPixel() = aBox.sz();

       ElAffin2D aAfM2C = Xml2EL(aParam.Orientation().OrIntImaM2C());
       
        aAfM2C   =   ElAffin2D::trans(-Pt2dr(aBox._p0)) * aAfM2C;
       aParam.Orientation().OrIntImaM2C().SetVal(El2Xml(aAfM2C));
  }


  std::string aMasq =  aDir+aParam.Image_Profondeur().Val().Masq();
  if (aMasqSpec!="")
         aMasq = aMasqSpec;

  Fonc_Num aFMasq =   trans(Tiff_Im::BasicConvStd(aMasq).in(0),aBox._p0);
  Tiff_Im aTP = Tiff_Im::BasicConvStd(aDir+aParam.Image_Profondeur().Val().Image());
  Fonc_Num aFProf =  trans(aTP.in_proj()*ExagZ,aBox._p0);


   if (aParam.Image_Profondeur().IsInit())
   {
      bool aFaiscClassik =  (   (aParam.Image_Profondeur().Val().GeomRestit()==eGeomMNTFaisceauIm1PrCh_Px1D)
                             || (aParam.Image_Profondeur().Val().GeomRestit()==eGeomMNTFaisceauIm1PrCh_Px2D)
                             || (aParam.Image_Profondeur().Val().GeomRestit()==eGeomMNTEuclid)
                             || (aParam.Image_Profondeur().Val().GeomRestit()==eGeomMNTFaisceauPrChSpherik)
                            );

      bool aProfIsZ =  (      (aParam.Image_Profondeur().Val().GeomRestit()==eGeomMNTFaisceauIm1ZTerrain_Px1D)
                             || (aParam.Image_Profondeur().Val().GeomRestit()==eGeomMNTFaisceauIm1ZTerrain_Px2D)
                         );


       if (aFaiscClassik || aProfIsZ)
       {
           switch (aTP.type_el())
           {
               case GenIm::int2 :
                    return new cElN3D_EpipGen<INT2,INT>(aDir,aParam,aFMasq,aFProf,aProfIsZ);
               break;
               case GenIm::real4 :
                    return new cElN3D_EpipGen<float,double>(aDir,aParam,aFMasq,aFProf,aProfIsZ);
               break;

               default :
                   std::cout << "NAME " << aDir+aParam.Image_Profondeur().Val().Image() << "\n";
                   ELISE_ASSERT(false,"Type Image non gere dans cElNuage3DMaille::FromParam");
               break;
           }
       }
   }

   ELISE_ASSERT(false,"cElNuage3DMaille::FromParam");
   return 0;
}

cElNuage3DMaille * cElNuage3DMaille::FromFileIm(const std::string & aFile)
{
   return FromFileIm(aFile,"XML_ParamNuage3DMaille");
}

cElNuage3DMaille * cElNuage3DMaille::FromFileIm
                   (
                          const std::string & aFile,
                          const std::string & aTag,
                          const std::string & aMasq,
                          double ExagZ
                   )
{
   std::string aDir,aNF;
   SplitDirAndFile(aDir,aNF,aFile);
   return FromParam
          (
                StdGetObjFromFile<cXML_ParamNuage3DMaille>
                (
                      aFile,
                      StdGetFileXMLSpec("SuperposImage.xml"),
                      aTag,
                      "XML_ParamNuage3DMaille"
                ),
                aDir,
                aMasq,
                ExagZ
         );
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
