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
// #include "anag_all.h"

/*
void f()
{
    FILE * aFP = ElFopen(MMC,"w");
    ElFclose(aFP);
}

*/


#include "StdAfx.h"
#include "hassan/reechantillonnage.h"


#if (ELISE_X11)



using namespace NS_ParamChantierPhotogram;

#if (0)


#endif






Fonc_Num Correl(Fonc_Num aF1,Fonc_Num aF2,int aNb)
{
   Symb_FNum aM1 (Moy(aF1,aNb));
   Symb_FNum aM2 (Moy(aF2,aNb));

   Fonc_Num aEnct1 = Moy(Square(aF1),aNb) -Square(aM1);
   Fonc_Num aEnct2 = Moy(Square(aF2),aNb) -Square(aM2);


   return (Moy(aF1*aF2,aNb)  -aM1*aM2) / sqrt(Max(1e-5,aEnct1*aEnct2));
}

void AutoCorrel(const std::string & aName)
{
   Tiff_Im aTF(aName.c_str());
   Pt2di aSz = aTF.sz();
   Im2D_REAL4 anI(aSz.x,aSz.y);
   ELISE_COPY(aTF.all_pts(),aTF.in(),anI.out());

   int aNb = 2;

   Fonc_Num aF = 1.0;
   for (int aK=0 ; aK<4 ; aK++)
   {
      aF = Min(aF,Correl(anI.in(0),trans(anI.in(0),TAB_4_NEIGH[aK])*(aNb*2),aNb));
   }
  
   Tiff_Im::Create8BFromFonc
   (
       StdPrefix(aName)+"_AutoCor.tif",
       aSz,
       Min(255,Max(0,(1+aF)*128))
   );
}


Im2D_REAL4 Conv2Float(Im2DGen anI)
{
   Pt2di aSz = anI.sz();
   Im2D_REAL4 aRes(aSz.x,aSz.y);
   ELISE_COPY(anI.all_pts(),anI.in(),aRes.out());
   return aRes;
}




void TestKL()
{
   Pt2di aSZ(200,200);
   Im2D_Bits<1> aImMasqF(aSZ.x,aSZ.y,1);

   Im2D_Bits<1> aImMasqDef(aSZ.x,aSZ.y,1);
   ELISE_COPY(rectangle(Pt2di(70,0),Pt2di(130,200)),0,aImMasqDef.out());

   Im2D<U_INT2,INT> aImVal(aSZ.x,aSZ.y);
   ELISE_COPY(aImVal.all_pts(),FX,aImVal.out());

   Video_Win aW=Video_Win::WStd(aSZ,3.0);
   ELISE_COPY(aW.all_pts(),aImVal.in(),aW.ogray());
   ELISE_COPY(aW.all_pts(),aImMasqDef.in(),aW.odisc());
   getchar();


   aImVal = ImpaintL2(aImMasqDef,aImMasqF,aImVal);

   // NComplKLipsParLBas(aImMasqDef,aImMasqF,aImVal,1.0);

   ELISE_COPY(aW.all_pts(),aImVal.in(),aW.ogray());

   Tiff_Im::Create8BFromFonc("toto.tif",aSZ,aImVal.in());
   getchar();
}
#if (0)
#endif


extern void TestDigeoExt();


void TestXMLNuageNodData()
{
    std::string aN1 = "/media/data2/Aerien/Euro-SDR/Munich/Cloud-Fusion/CF-42_0502_PAN.xml";
    std::string aN2 = "/media/data2/Aerien/Euro-SDR/Munich/MEC2Im-true-42_0502_PAN.tif-41_0420_PAN.tif/NuageImProf_LeChantier_Etape_8.xml";
    for (int aK=0 ; aK<1000 ; aK++)
    {
       cElNuage3DMaille * aC1 =  NuageWithoutData(aN1);
       // cElNuage3DMaille * aC2 =  NuageWithoutData(aN2);
       cElNuage3DMaille * aC2 =  NuageWithoutDataWithModel(aN2,aN1);
       cElNuage3DMaille * aC3 =  NuageWithoutData(aN2);
       std::cout << "C1= " << aC1->SzData()  << " " << aC2->SzData()  << "\n";
       std::cout << "C1= " << aC1->SzGeom()  << " " << aC2->SzGeom()  << "\n";
       std::cout << "COMPAT " <<   GeomCompatForte(aC1,aC2) << "\n";
       std::cout << "COMPAT " <<   GeomCompatForte(aC1,aC3) << "\n";
       // std::cout << "C1= " << aC1->SzUnique()  << " " << aC2->SzUnique()  << "\n";
       getchar();
       delete aC1;
    }
}

void TestRound()
{
   while(1)
   {
       double aV,aBig;
       cin >> aV >> aBig;
       cDecimal aD  = StdRound(aV);
       double Arrond = aD.Arrondi(aBig);
       printf("%9.9f %9.9f\n",aD.RVal(),Arrond);
       std::cout << "Round " << aD.RVal() << "\n";
   }
}



void Test_Arrondi_LG()
{
    Pt2di aSz(100,100);
    double aVTest = 117;

    Im2D_REAL16 anIm(aSz.x,aSz.y);
    TIm2D<REAL16,REAL16> aTIm(anIm);

    ELISE_COPY(anIm.all_pts(),aVTest,anIm.out());

    while (1)
    {
         Pt2dr aP0 = Pt2dr(10,10) + Pt2dr(NRrandom3(),NRrandom3()) *50.123456701765;
         double aV0 = aTIm.getr(aP0);
         double aV1 = Reechantillonnage::biline(anIm.data(),aSz.x,aSz.y,aP0);
         
         std::cout << " TEST " << (aV0-aVTest) * 1e50 << " " << (aV1-aVTest) * 1e50  << " " << aP0 << "\n";
         getchar();
    }
}



void PbHom(const std::string & anOri)
{
   const std::string & aDir = "/media/data1/Calib-Sony/FacadePlane-2000/";
   const std::string & aIm1 = "DSC05180.ARW";
   const std::string & aIm2 = "DSC05182.ARW";


   cInterfChantierNameManipulateur * aICNM = cInterfChantierNameManipulateur::BasicAlloc(aDir);
   std::string    aKeyOri =  "NKS-Assoc-Im2Orient@-" + anOri;


    std::string aNameOri1 =  aICNM->Assoc1To1(aKeyOri,aIm1,true);
    std::string aNameOri2 =  aICNM->Assoc1To1(aKeyOri,aIm2,true);


    CamStenope * aCS1 = CamOrientGenFromFile(aNameOri1,aICNM);
    CamStenope * aCS2 = CamOrientGenFromFile(aNameOri2,aICNM);

    Pt2dr aP1 (774,443);
    Pt2dr aP2 (5541,3758);

    Pt3dr aTer1  = aCS1->ImEtProf2Terrain(aP1,1.0);
    Pt2dr aProj1 = aCS1->R3toF2(aTer1);

    std::cout << "P & Proj Init1" << aP1 << aProj1 << " " << euclid(aP1-aProj1) << "\n";
    

    Pt3dr aTer2  = aCS2->ImEtProf2Terrain(aP2,1.0);
    Pt2dr aProj2 = aCS2->R3toF2(aTer2);

    std::cout << "P & Proj Init2" << aP2 << aProj2 << " " << euclid(aP2-aProj2) << "\n";


    double aDist;
    Pt3dr aTerInter = aCS1->PseudoInter(aP1,*aCS2,aP2,&aDist);

    aProj1 = aCS1->R3toF2(aTerInter);
    aProj2 = aCS2->R3toF2(aTerInter);

    std::cout << "Proj Inter " << aDist << " " << (aP1-aProj1) << " " << (aP2-aProj2) << "\n";
    


    std::cout << "\n";
}


int MPDtest_main (int argc,char** argv)
{
   BanniereMM3D(); exit(0);
   PbHom("Test-Four");
   PbHom("RadialExtended");

   getchar();


   // ElList<Pt2di> aL = NewLPt2di(Pt2di(20,20));

   std::string aPref = "eTT_";
   std::list<std::string>  aL = ListOfVal(eTT_NbVals,aPref);
   for (std::list<std::string>::iterator it=aL.begin() ; it!=aL.end() ; it++)
   {
       std::cout << " fff [" <<  *it << "]\n";
   }

   std::cout << "BBBB " << BoolFind(std::string("ABC"),'B') << "\n";
   std::cout << "bbbb " << BoolFind(std::string("ABC"),'b') << "\n";

   double aDif;

   ELISE_COPY
   (
      rectangle(Pt2di(0,0),Pt2di(10,10)),
      Abs(trans(FX,Pt2di(2,2)) - StdFoncChScale(FX,Pt2dr(2.00,2),Pt2dr(1,1))),
      sigma(aDif)
   );

   std::cout << "DIF = " << aDif << "\n";

    
 
   return 0;

    return EXIT_SUCCESS;
}

#endif

/*Footer-MicMac-eLiSe-25/06/2007

Ce logiciel est un programme informatique servant �  la mise en
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
associés au chargement,  �  l'utilisation,  �  la modification et/ou au
développement et �  la reproduction du logiciel par l'utilisateur étant 
donné sa spécificité de logiciel libre, qui peut le rendre complexe �  
manipuler et qui le réserve donc �  des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies.  Les
utilisateurs sont donc invités �  charger  et  tester  l'adéquation  du
logiciel �  leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement, 
�  l'utiliser et l'exploiter dans les mêmes conditions de sécurité. 

Le fait que vous puissiez accéder �  cet en-tête signifie que vous avez 
pris connaissance de la licence CeCILL-B, et que vous en avez accepté les
termes.
Footer-MicMac-eLiSe-25/06/2007*/
