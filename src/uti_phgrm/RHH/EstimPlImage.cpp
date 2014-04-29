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
#include "ReducHom.h"

NS_RHH_BEGIN


/*************************************************/
/*                                               */
/*                  cImagH                       */
/*                                               */
/*************************************************/


double DistNorm(const cElemMepRelCoplan & anEl)
{
   Pt3dr aVert(0,0,1);
   return euclid(aVert-anEl.Norm());
}


class cCmpNormPlan
{
   public :
      bool operator () (const cElemMepRelCoplan & anEl1,const cElemMepRelCoplan & anEl2)
      {
          // return anEl1.Norm().z > anEl2.Norm().z;
          return DistNorm(anEl1) < DistNorm(anEl2);
      }
};


class cTestPlIm
{
    public :
        cTestPlIm(cLink2Img * aLnk,const cElemMepRelCoplan & aRMCP) :
             mLnk    (aLnk),
             mRMCP   (aRMCP),
             mHomI2T (mRMCP.HomCam2Plan())
        {
            std::cout << "  PLL " << aLnk->Dest()->Name()
                      << mRMCP.Norm()
                      << mHomI2T.Direct(Pt2dr(0.5,0.5))
                      << "\n";
        }
       
        cLink2Img *       mLnk;
        cElemMepRelCoplan  mRMCP;
        cElHomographie     mHomI2T;
};


double TestCohHomogr(const cTestPlIm & aPL1,const cTestPlIm & aPL2)
{
/*
   std::vector<int> aVInd;
   for (int aK=0 ; aK<4 ; aK++)
      aVInd.push_back(aK);
*/
    const std::vector<Pt3dr> & aV =  aPL1.mLnk->EchantP1();

   L2SysSurResol aSys(4,true);
   double aCoeff[4];  // A B TrX TrY

   for (int aK=0 ; aK<int(aV.size()) ; aK++)
   {
       Pt2dr aP(aV[aK].x,aV[aK].y);
       double aPds =aV[aK].z;

       Pt2dr aPt1 = aPL1.mHomI2T.Direct(aP);
       Pt2dr aPt2 = aPL2.mHomI2T.Direct(aP);
       
       aCoeff[0] = aPt1.x;
       aCoeff[1] = -aPt1.y;
       aCoeff[2] = 1;
       aCoeff[3] = 0;
       aSys.AddEquation(aPds,aCoeff,aPt2.x);
       //  
       aCoeff[0] = aPt1.y;
       aCoeff[1] = aPt1.x;
       aCoeff[2] = 0;
       aCoeff[3] = 1;
       aSys.AddEquation(aPds,aCoeff,aPt2.y);
   }
   bool Ok;
   Im1D_REAL8 aSol = aSys.Solve(&Ok);
   double aResidu = aSys.ResiduOfSol(aSol.data());


   if (1)
   {
       double * aDS = aSol.data();
       Pt2dr aMul(aDS[0] ,aDS[1]);
       Pt2dr aTR(aDS[2] ,aDS[3]);


       double aSomV = 0;

       for (int aK=0 ; aK<int(aV.size()) ; aK++)
       {
           Pt2dr aP(aV[aK].x,aV[aK].y);
           double aPds =aV[aK].z;

           Pt2dr aPt1 = aPL1.mHomI2T.Direct(aP);
           Pt2dr aPt2 = aPL2.mHomI2T.Direct(aP);

           Pt2dr aDif = aPt1 * aMul + aTR - aPt2;

           aSomV += aPds * square_euclid(aDif);
        }

    }




    return aResidu;
}



void cImagH::EstimatePlan()
{
     std::pair<Pt2dr,Pt2dr> aPair(Pt2dr(0,0),Pt2dr(0,0));
     std::vector<cTestPlIm> aVPlIm;

     std::cout << " =========== Begin EstimatePlan " << mName << "\n";
     for (tMapName2Link::iterator itL = mLnks.begin(); itL != mLnks.end(); itL++)
     {
          cLink2Img * aLnk   = itL->second;

          // ElPackHomologue & aPack = aLnk->Pack();
          cElHomographie &   aHom = aLnk->Hom12();

          // std::cout << "  " << aLnk->Dest()->Name()  << " Sz " << aPack.size() << " Qual  " << aLnk->QualHom() << " " ;

          cResMepRelCoplan aRCP = ElPackHomologue::MepRelCoplan(1,aHom,aPair);
          std::vector<cElemMepRelCoplan>  aVSol = aRCP.VElOk();
          cCmpNormPlan aCmp;
          std::sort(aVSol.begin(),aVSol.end(),aCmp);

          if (aVSol.size() >=2) 
          {
              double aS0 = DistNorm(aVSol[0]);
              double aS1 = DistNorm(aVSol[1]);

              if (aS0 + mAppli.SeuilDistNorm() < aS1)
              {
                  aVPlIm.push_back(cTestPlIm(aLnk,aVSol[0]));
              }
                    
          }
     }

      for (int aK1 = 0 ; aK1<int(aVPlIm.size()) ; aK1++)
      {
          for (int aK2 = 0 ; aK2<int(aVPlIm.size()) ; aK2++)
          {
             double aResidu =    TestCohHomogr(aVPlIm[aK1],aVPlIm[aK2]);
             std::cout << "RESIDU " << aResidu  << "  "  << (aK1==aK2) << "\n";
          }
      }

     
     std::cout << " =========== End  EstimatePlan \n";
     getchar();
}


NS_RHH_END


/*
*/
/*
*/




/*Footer-MicMac-eLiSe-25/06/2007

Ce logiciel est un programme informatique servant � la mise en
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
associ�s au chargement,  � l'utilisation,  � la modification et/ou au
d�veloppement et � la reproduction du logiciel par l'utilisateur �tant
donn� sa sp�cificit� de logiciel libre, qui peut le rendre complexe �
manipuler et qui le r�serve donc � des d�veloppeurs et des professionnels
avertis poss�dant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invit�s � charger  et  tester  l'ad�quation  du
logiciel � leurs besoins dans des conditions permettant d'assurer la
s�curit� de leurs syst�mes et ou de leurs donn�es et, plus g�n�ralement,
� l'utiliser et l'exploiter dans les m�mes conditions de s�curit�.

Le fait que vous puissiez acc�der � cet en-t�te signifie que vous avez
pris connaissance de la licence CeCILL-B, et que vous en avez accept� les
termes.
Footer-MicMac-eLiSe-25/06/2007*/
