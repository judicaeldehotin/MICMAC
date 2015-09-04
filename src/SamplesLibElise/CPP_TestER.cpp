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
#include "../uti_phgrm/MICMAC/CameraRPC.h"

void CheckBounds(Pt2dr & aPmin, Pt2dr & aPmax, const Pt2dr & aP, bool & IS_INI);

//do matching in push-broom and pick salient points
int TestER_main(int argc,char ** argv)
{
    std::string aDirTmp = "Tmp-TIL", aPrefixName = "_TIL_";
    std::string aTmp;
    std::string aIm1Name, aIm2Name;
    std::string aNameType;
    eTypeImporGenBundle aType;
    std::string aLayersNum="10";

    int aK1,aK2;
    int aZoomF=32;
 
    Pt2di aImTilSz(10000,9000), aImTilSzTmp;
    Pt2di aImTilGrid(0,0);

    GenIm::type_el aTypeOut = GenIm::u_int1;

    ElInitArgMain
    (
        argc, argv,
        LArgMain() << EAMC(aIm1Name,"First Image")
	           << EAMC(aIm2Name,"Second Image"),
        LArgMain() << EAM(aNameType,"Type",true,"Type of sensor (see eTypeImporGenBundle)")	
	           << EAM(aZoomF,"ZoomF",true,"Zoom init,  pow of 2  in [4,1], Def=32")
    );

    //(0) divide the imgs to tiles
    //   (a) select tie in the left and create a tif
    //   (b) get the vol in space
    //   (c) project the vol to the right img
    //   (d) create the tif
    //(1) run PASTIS with two tiles

    bool aModeHelp;
    StdReadEnum(aModeHelp,aType,aNameType,eTIGB_NbVals);


    CameraRPC aCRPC1(aIm1Name,aType);
    CameraRPC aCRPC2(aIm2Name,aType);

    Tiff_Im aIm1 = Tiff_Im::StdConv(aCRPC1.GetImName() + std::string(".tif"));
    Tiff_Im aIm2 = Tiff_Im::StdConv(aCRPC2.GetImName() + std::string(".tif"));


    /* Create tiles & save to hard-drive */
    aImTilGrid.x = round_up(double(aCRPC1.SzBasicCapt3D().x)/aImTilSz.x);
    aImTilGrid.y = round_up(double(aCRPC1.SzBasicCapt3D().y)/aImTilSz.y);
  

    ELISE_fp::MkDirSvp(aDirTmp);

    for(aK1=0; aK1<aImTilGrid.x; aK1++)
    {
        for(aK2=0; aK2<aImTilGrid.y; aK2++)
	{

	    //check if marginal tiles (this shall include image validity)
	    if(aK1 < (aImTilGrid.x-1))
	        aImTilSzTmp.x = aImTilSz.x;
	    else
	        aImTilSzTmp.x = aCRPC1.SzBasicCapt3D().x - aK1*aImTilSz.x;

	    if(aK2 < (aImTilGrid.y-1))
	        aImTilSzTmp.y = aImTilSz.y;
	    else
	        aImTilSzTmp.y = aCRPC1.SzBasicCapt3D().y - aK2*aImTilSz.y;


            aTmp = aDirTmp + "//" + aIm1Name.substr(0,aIm1Name.size()-4) + aPrefixName + ToString(aK1) + "_" + ToString(aK2);

            Tiff_Im aTilCur = Tiff_Im
	    (
                aTmp.c_str(),
	        aImTilSzTmp,
	        aTypeOut,
	        Tiff_Im::No_Compr,
	        aIm1.phot_interp(),
	        Tiff_Im::Empty_ARG
	    );
		           
	    ELISE_COPY
	    (
                aTilCur.all_pts(),
	        trans(aIm1.in(), Pt2di(aK1*aImTilSzTmp.x, aK2*aImTilSzTmp.y)), 
	        aTilCur.out()
	    );
	}
   }

   /* For eqch tile in the left image,
    * (a) define the volume in 3D space that it sees, and
    * (b) project that volume to the second image;
    * (c) form an image to contain the backprojected zone
    * (d) save the the pair to an XML file
    * (e) run Tapioca */ 

    //(a) corner start in top left corner and 
    //    follow clockwise direction
    //    V3D1H - 1st corner in 3D at height=last_height
    //    V3D1L - 1st corner in 3D at height=first_height
    //    V2D1  - 1st corner in 2D
    Pt3dr aV3D1H, aV3D2H, aV3D3H, aV3D4H;
    Pt3dr aV3D1L, aV3D2L, aV3D3L, aV3D4L;
    Pt2dr aV2D1, aV2D2, aV2D3, aV2D4, aV2DTmp;
   
    for(aK1=0; aK1<aImTilGrid.x; aK1++)
    {
        for(aK2=0; aK2<aImTilGrid.y; aK2++)
	{
            Pt2dr aMax, aMin;

	    //check if marginal tiles (this shall include imge validity)
	    if(aK1 < (aImTilGrid.x-1))
	    {
		aV2D2.x = (aK1+1)*aImTilSz.x;
		aV2D3.x = (aK1+1)*aImTilSz.x;
	    }
	    else
	    {
	        aV2D2.x = aCRPC1.SzBasicCapt3D().x -1;
	        aV2D3.x = aCRPC1.SzBasicCapt3D().x -1;
	    }
	    if(aK2 < (aImTilGrid.y-1))
	    {
		aV2D3.y = (aK2+1)*aImTilSz.y;
		aV2D4.y = (aK2+1)*aImTilSz.y;
	    }
	    else
	    {
		aV2D3.y = aCRPC1.SzBasicCapt3D().y -1;
		aV2D4.y = aCRPC1.SzBasicCapt3D().y -1;
	    }

            aV2D1.x = aK1*aImTilSz.x;
	    aV2D4.x = aK1*aImTilSz.x;
	    aV2D1.y = aK2*aImTilSz.y;
	    aV2D2.y = aK2*aImTilSz.y;

            std::cout << aV2D1 << " " << aV2D2 << " " << aV2D3 << " " << aV2D4 << "\n";

	    //3d volume
	    aV3D1H = aCRPC1.ImEtZ2Terrain(aV2D1, aCRPC1.GetRPC().last_height);
	    aV3D1L = aCRPC1.ImEtZ2Terrain(aV2D1, aCRPC1.GetRPC().first_height);
            
	    aV3D2H = aCRPC1.ImEtZ2Terrain(aV2D2, aCRPC1.GetRPC().last_height);
	    aV3D2L = aCRPC1.ImEtZ2Terrain(aV2D2, aCRPC1.GetRPC().first_height);

	    aV3D3H = aCRPC1.ImEtZ2Terrain(aV2D3, aCRPC1.GetRPC().last_height);
	    aV3D3L = aCRPC1.ImEtZ2Terrain(aV2D3, aCRPC1.GetRPC().first_height);

	    aV3D4H = aCRPC1.ImEtZ2Terrain(aV2D4, aCRPC1.GetRPC().last_height);
	    aV3D4L = aCRPC1.ImEtZ2Terrain(aV2D4, aCRPC1.GetRPC().first_height);


	    //backproject to aCRPC2
            bool IS_INI=false;
	    if(aCRPC2.PIsVisibleInImage(aV3D1H))
	    {
                aV2DTmp = aCRPC2.Ter2Capteur(aV3D1H);
//	        if((aV2DTmp.x<aIm2.sz().x) && (aV2DTmp.y<aIm2.sz().y))
		{
		    CheckBounds(aMin, aMax, aV2DTmp, IS_INI);    

	        std::cout << "1hIS_INI " << IS_INI << " " << aV2DTmp << "\n";	
	        std::cout << "min " << aMin << "\n";	
	        std::cout << "max " << aMax << "\n";	
		}
	    }

	    if(aCRPC2.PIsVisibleInImage(aV3D1L))
	    {
                aV2DTmp = aCRPC2.Ter2Capteur(aV3D1L);
	        CheckBounds(aMin, aMax, aV2DTmp, IS_INI);    	
//	        if((aV2DTmp.x<aIm2.sz().x) && (aV2DTmp.y<aIm2.sz().y))
		{
	        std::cout << "1lIS_INI " << IS_INI << " " << aV2DTmp << "\n";	
	        std::cout << "min " << aMin << "\n";	
	        std::cout << "max " << aMax << "\n";	
		}
	    }

	    if(aCRPC2.PIsVisibleInImage(aV3D2H))
	    {
                aV2DTmp = aCRPC2.Ter2Capteur(aV3D2H);
//	        if((aV2DTmp.x<aIm2.sz().x) && (aV2DTmp.y<aIm2.sz().y))
		{
	        CheckBounds(aMin, aMax, aV2DTmp, IS_INI);    	
	        std::cout << "2hIS_INI " << IS_INI << " " << aV2DTmp << "\n";	
	        std::cout << "min " << aMin << "\n";	
	        std::cout << "max " << aMax << "\n";	
		}
	    }
	    if(aCRPC2.PIsVisibleInImage(aV3D2L))
	    {
                aV2DTmp = aCRPC2.Ter2Capteur(aV3D2L);
//	        if((aV2DTmp.x<aIm2.sz().x) && (aV2DTmp.y<aIm2.sz().y))
		{
	        CheckBounds(aMin, aMax, aV2DTmp, IS_INI);    	
	        std::cout << "2lIS_INI " << IS_INI << " " << aV2DTmp << "\n";	
	        std::cout << "min " << aMin << "\n";	
	        std::cout << "max " << aMax << "\n";	
		}
	    }

	    if(aCRPC2.PIsVisibleInImage(aV3D3H))
	    {
                aV2DTmp = aCRPC2.Ter2Capteur(aV3D3H);
//	        if((aV2DTmp.x<aIm2.sz().x) && (aV2DTmp.y<aIm2.sz().y))
		{
	        CheckBounds(aMin, aMax, aV2DTmp, IS_INI);    	
	        std::cout << "3hIS_INI " << IS_INI << " " << aV2DTmp << "\n";	
	        std::cout << "min " << aMin << "\n";	
	        std::cout << "max " << aMax << "\n";	
		}
	    }
	    if(aCRPC2.PIsVisibleInImage(aV3D3L))
	    {
                aV2DTmp = aCRPC2.Ter2Capteur(aV3D3L);
//	        if((aV2DTmp.x<aIm2.sz().x) && (aV2DTmp.y<aIm2.sz().y))
		{
	        CheckBounds(aMin, aMax, aV2DTmp, IS_INI);    	
	        std::cout << "3lIS_INI " << IS_INI << " " << aV2DTmp << "\n";	
	        std::cout << "min " << aMin << "\n";	
	        std::cout << "max " << aMax << "\n";	
		}
	    }

	    if(aCRPC2.PIsVisibleInImage(aV3D4H))
	    {
                aV2DTmp = aCRPC2.Ter2Capteur(aV3D4H);
//	        if((aV2DTmp.x<aIm2.sz().x) && (aV2DTmp.y<aIm2.sz().y))
		{
	        CheckBounds(aMin, aMax, aV2DTmp, IS_INI);    	
	        std::cout << "4hIS_INI " << IS_INI << " " << aV2DTmp << "\n";	
	        std::cout << "min " << aMin << "\n";	
	        std::cout << "max " << aMax << "\n";	
		}
	    }
	    if(aCRPC2.PIsVisibleInImage(aV3D4L))
	    {
                aV2DTmp = aCRPC2.Ter2Capteur(aV3D4L);
//	        if((aV2DTmp.x<aIm2.sz().x) && (aV2DTmp.y<aIm2.sz().y))
		{
	        CheckBounds(aMin, aMax, aV2DTmp, IS_INI);    	
	        std::cout << "4lIS_INI " << IS_INI << " " << aV2DTmp << "\n";	
	        std::cout << "min " << aMin << "\n";	
	        std::cout << "max " << aMax << "\n";	
		}
	    }
	
	    if(IS_INI)
	    {
		aMin.x = round_down(aMin.x);
		aMax.x = round_down(aMax.x);
		aMin.y = round_down(aMin.y);
		aMax.y = round_down(aMax.y);
                
		aImTilSzTmp.x = (aMax.x - aMin.x);
                aImTilSzTmp.y = (aMax.y - aMin.y);
                if( aImTilSzTmp.x>0 && aImTilSzTmp.y>0 )
		{
	        //save img
                aTmp = aDirTmp + "//" + aIm2Name.substr(0,aIm1Name.size()-4) + aPrefixName + ToString(aK1) + "_" + ToString(aK2);

		std::cout << "aImTilSzTmp " << aImTilSzTmp << "\n";
		std::cout << "aMin " << aMin << "\n";

		Tiff_Im aTilCur = Tiff_Im
	        (
                    aTmp.c_str(),
	            aImTilSzTmp,
	            aTypeOut,
	            Tiff_Im::No_Compr,
	            aIm1.phot_interp(),
	            Tiff_Im::Empty_ARG
	        );
		           
	        ELISE_COPY
	        (
                    aTilCur.all_pts(),
	            trans(aIm2.in(), Pt2di(aMin.x,aMin.y)), 
	            aTilCur.out()
	        );
	
                //save GraphHom
		}

	    }
	}
    }

   return EXIT_SUCCESS;
}

void CheckBounds(Pt2dr & aPmin, Pt2dr & aPmax, const Pt2dr & aP, bool & IS_INI)
{

    if(IS_INI)
    {
        if(aP.x < aPmin.x) 
           aPmin.x = aP.x;
        if(aP.x > aPmax.x)
    	   aPmax.x = aP.x;
	if(aP.y < aPmin.y) 
	   aPmin.y = aP.y;
	if(aP.y > aPmax.y)
	   aPmax.y = aP.y;

    }
    else
    {
        aPmin = aP;
        aPmax = aP;

	IS_INI = true;
    }


}

//some tests taken from intro0
int TestER_main5(int argc,char ** argv)
{
    std::string aImName;

    ElInitArgMain
    (
        argc, argv,
	LArgMain() << EAMC(aImName,"Image name"),
	LArgMain()
    );

    Pt2di SZ(256,256);

    Tiff_Im aIm = Tiff_Im::StdConv(aImName);
    Im2D_U_INT1 I(256,256);

    Gray_Pal  Pgr (30);
    RGB_Pal   Prgb  (5,5,5);
    Disc_Pal  Pdisc = Disc_Pal::PNCOL();
    Circ_Pal  Pcirc = Circ_Pal::PCIRC6(30);

    Elise_Set_Of_Palette SOP(NewLElPal(Pdisc)+Elise_Palette(Pgr)+Elise_Palette(Prgb)+Elise_Palette(Pcirc));

    Video_Display Ecr((char *) NULL);
    Ecr.load(SOP);
    Video_Win   W  (Ecr,SOP,Pt2di(50,50),Pt2di(SZ.x,SZ.y));

    W.set_title("Une fenetre");

    ELISE_COPY
    (
        I.all_pts(),
	aIm.in(),
        W.out(Prgb)
    );
    getchar();

    std::cout << "dddddddffff" << "\n";

    return EXIT_SUCCESS;
}

//test OpticalCenterOfPixel
int TestER_main4(int argc,char ** argv)
{
    std::string aFullName;
    std::string aDir;
    std::string aNameOri;
    std::list<std::string> aListFile;

    std::string aNameType;
    eTypeImporGenBundle aType;

    ElInitArgMain
    (
        argc, argv,
        LArgMain() << EAMC(aFullName,"Orientation file full name (Dir+OriPattern)"),
	LArgMain() << EAM(aNameType,"Type",true,"Type of sensor (see eTypeImporGenBundle)",eSAM_None,ListOfVal(eTT_NbVals,"eTT_"))
    );

    std::cout << aFullName << std::endl;
   
    bool aModeHelp;
    StdReadEnum(aModeHelp,aType,aNameType,eTIGB_NbVals);

    CameraRPC aRPC(aFullName, aType);
    //aRPC.OpticalCenterPerLine();

    //Pt3dr aP1, aP2, aP3;
    //aP1 = aRPC.OpticalCenterOfPixel(Pt2dr(1,1));
    //aP2 = aRPC.OpticalCenterOfPixel(Pt2dr(10,10));
    //aP3 = aRPC.OpticalCenterOfPixel(Pt2dr(aRPC.SzBasicCapt3D().x-1,
//			             aRPC.SzBasicCapt3D().y-1));

  //  std::cout <<  aP1.x << " " << aP1.y << " " << aP1.z << "\n";
  //  std::cout <<  aP2.x << " " << aP2.y << " " << aP2.z << "\n";
  //  std::cout <<  aP3.x << " " << aP3.y << " " << aP3.z << "\n";

    return EXIT_SUCCESS;
}

//test camera affine
int TestER_main3(int argc,char ** argv)
{
    //cInterfChantierNameManipulateur * aICNM;
    std::string aFullName;
    std::string aDir;
    std::string aNameOri;
    std::list<std::string> aListFile;

    ElInitArgMain
    (
        argc, argv,
        LArgMain() << EAMC(aFullName,"Orientation file full name (Dir+OriPattern)"),
	LArgMain()
    );

    std::cout << aFullName << std::endl;

    CameraAffine aCamAF(aFullName);
    aCamAF.ShowInfo();

    return EXIT_SUCCESS;
}
//test export of a CamStenope into bundles of rays
int TestER_main2(int argc,char ** argv)
{
    cInterfChantierNameManipulateur * aICNM;
    std::string aFullName;
    std::string aDir;
    std::string aNameOri;
    std::list<std::string> aListFile;

    Pt2di aGridSz;

    ElInitArgMain
    (
        argc, argv,
        LArgMain() << EAMC(aFullName,"Orientation file full name (Dir+OriPattern)"),
        LArgMain() << EAM(aGridSz,"GrSz",true)
    );
    
    SplitDirAndFile(aDir, aNameOri, aFullName);

    aICNM = cInterfChantierNameManipulateur::BasicAlloc(aDir);
    aListFile = aICNM->StdGetListOfFile(aNameOri);


    for(std::list<std::string>::iterator itL = aListFile.begin(); itL != aListFile.end(); itL++ )
    {
        CamStenope * aCurCamSten = CamStenope::StdCamFromFile(true, aDir+(*itL), aICNM);
        aCurCamSten->ExpImp2Bundle(aGridSz, *itL);
    }

    return EXIT_SUCCESS;
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
