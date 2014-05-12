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


 // cEqHomogFormelle   cHomogFormelle

void cAppliReduc::AmelioHomLocal(cImagH & anIm)
{
bool DebugRHH= false;

    double aPdsLVMStd = 1.1;
    double aPdsFreezC = 100;
    double aPdsEvol = 10;;


    std::cout << "INIT AmelioHomLocal \n";
    const std::vector<cLink2Img*> & aVLImC = mImCAmel->VLink();
    for (int aKL=0 ; aKL<int(aVLImC.size()) ; aKL++)
    {
         cLink2Img * aLnK = aVLImC[aKL];
         cImagH * anI = aLnK->Dest();
         anI->C2CI() = true;

         anI->HF()->ReinitHom(aLnK->Hom12().Inverse());
         // anI->HF()->ReinitHom(aLnK->Hom12());
    }

    for (int aKIm=0 ; aKIm<int(mIms.size()) ; aKIm++)
    {
         cImagH * anI = mIms[aKIm];
         if (!anI->C2CI())
            anI->HF()->ReinitHom(cElHomographie::Id());
    }
    mImCAmel->C2CI() = true;
  


    for (int aNbIter =0 ; aNbIter < 20 ; aNbIter ++)
    {
         std::cout << "Begin AmelioHomLocal , Iter " << aNbIter << "\n";
         mSetEq.SetPhaseEquation();

         double aSomEr=0;
         double aSomP=0;


         for (int aKIm1=0 ; aKIm1<int(mIms.size()) ; aKIm1++)
         {
              cImagH * anI1 = mIms[aKIm1];
              anI1->AddViscositty((anI1== mImCAmel) ? aPdsFreezC : aPdsLVMStd);
              cElHomographie  aCurH1 = anI1->HF()->HomCur();
                
              if (anI1->C2CI())
              {
                   double aPdsE = aPdsEvol /  anI1->PdsEchant();
                   const std::vector<cLink2Img*> & aVL = anI1->VLink();
                   for (int aKL=0 ; aKL<int(aVL.size()) ; aKL++)
                   {
                        cLink2Img * aLnk = aVL[aKL];
                        cImagH* anI2 = aLnk->Dest();
                        cElHomographie  aCurH2 = anI2->HF()->HomCur();
                        cElHomographie  aCurH2Inv = aCurH2.Inverse();
                        if (anI2->C2CI())
                        {
                            double aSomRes = 0;
                            double aSomCtrl = 0;
                            cElHomographie aH12 = aLnk->Hom12();
                            const std::vector<Pt3dr> & anEch = aLnk->EchantP1();
                            cEqHomogFormelle * anEq = aLnk->EqHF();
                            int aNbPts = DebugRHH ? 1 : anEch.size();

                            for (int aKEch = 0 ; aKEch<int(aNbPts) ; aKEch++)
                            {
                                 Pt3dr  aP3d = DebugRHH ? Pt3dr(0.25,0.25,1) :  anEch[aKEch];
                                 Pt2dr aP1(aP3d.x,aP3d.y);
// std::cout << aP1 << "\n";
                                 Pt2dr aP2 = aH12.Direct(aP1);
                                 double aPds = aP3d.z * aPdsE;

                                 Pt2dr aRes = anEq->StdAddLiaisonP1P2(aP1,aP2,aPds,false);
                                 Pt2dr aCtrl = aCurH2Inv.Direct(aCurH1.Direct(aP1)) - aP2;
                                 aSomRes += euclid(aRes);
                                 aSomCtrl += euclid(aCtrl);


                                 double anEr = square_euclid(aRes);

                                 aSomEr+= anEr * aPds;
                                 aSomP+= aPds;
                            }

/*
                            std::cout  << anEq
                                       << " N12=" << anI1->Name() << " " << anI2->Name() 
                                       << " ; RES = " << aSomRes/aNbPts << " Ctrl=" << aSomCtrl/aNbPts << "\n";
*/
                        }
                   }
              }
              // getchar();

              // anI->HF()->SetModeCtrl(cNameSpaceEqF::eHomFigee);
         }
         std::cout << "ERR = " << sqrt(aSomEr/aSomP) << "\n";




         mSetEq.SolveResetUpdate();
    }
    
     std::cout << "END AmelioHomLocal\n";
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
