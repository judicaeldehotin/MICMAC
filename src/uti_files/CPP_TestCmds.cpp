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

void GenerateMakeFile(std::string aNameFile, std::string aDataDir, bool doAll)
{
	std::string chantDir, aCom; 

	FILE * aFP = FopenNN(aNameFile.c_str(),false ? "a" : "w","TestCmds_GenerateMakeFile");

	chantDir = aDataDir + "/ExempleDoc/Boudha";

	aCom = "all:\n\t";
	aCom += "mm3d Tapioca MulScale " + chantDir + "/IMG_[0-9]{4}.tif 300 -1 ExpTxt=1\n\t";
	aCom += "mm3d Apero " + chantDir + "/Apero-5.xml\n\t";
	aCom += "mm3d MICMAC " + chantDir + "/Param-6-Ter.xml\n\t";	

	if (doAll)
	{
		chantDir = aDataDir + "/ExempleDoc/StreetSaintMartin";

		aCom += "mm3d Tapioca All \"" + chantDir + "/IMGP41((1[8-9])|(2[0-2])).JPG\" 1000\n\t";
		aCom += "mm3d Tapioca All \"" + chantDir + "/IMGP41((5[2-8])).JPG\" 1000\n\t";
		aCom += "mm3d Tapioca All \"" + chantDir + "/IMGP41((2[3-9])|[3-4][0-9]|(5[0-1])).JPG\" 1000\n\t";
		aCom += "mm3d Tapas RadialExtended \"" + chantDir + "/IMGP416[0-5].JPG\" Out=Calib\n\t";	
		aCom += "mm3d Tapas AutoCal \"" + chantDir + "/IMGP41((6[7-9])|([7-8][0-9])).JPG\" InCal=Calib Out=Test-5\n\t";
		aCom += "mm3d Tapas FishEyeEqui \"" + chantDir + "/IMGP41((1[8-9])|(2[0-2])).JPG\" Out=Calib10\n\t";
		aCom += "mm3d Tapas FishEyeEqui \"" + chantDir + "/IMGP41((5[2-8])).JPG\" Out=Calib17\n\t";
		aCom += "mm3d Tapas AutoCal \"" + chantDir + "/IMGP41((2[3-9])|[3-4][0-9]|(5[0-1])).JPG\" InCal=Calib10 Focs=[9,11] Out=Tmp1\n\t";
		aCom += std::string(SYS_CP) + ' ' + chantDir + "/Ori-Calib17/AutoCal170.xml " + chantDir +"/Ori-Tmp1/ \n\t";
		aCom += "mm3d Tapas FishEyeEqui \"" + chantDir + "/IMGP41((2[3-9])|[3-4][0-9]|(5[0-1])).JPG\" InOri=Tmp1 Out=all\n\t";
		aCom += "mm3d AperiCloud \"" + chantDir + "/IMGP41((2[3-9])|[3-4][0-9]|(5[0-1])).JPG\" all\n\t";

		chantDir = aDataDir + "/ExempleDoc/Vincennes";

		aCom += "mm3d Tapioca All \"" + chantDir + "/Calib-IMGP[0-9]{4}.JPG\" 1000\n\t";
		aCom += "mm3d Tapioca Line \""+ chantDir + "/Face1-IMGP[0-9]{4}.JPG\" 1000 5\n\t";
		aCom += "mm3d Tapioca Line \""+ chantDir + "/Face2-IMGP[0-9]{4}.JPG\" 1000 5\n\t";
		aCom += "mm3d Tapioca All \"" + chantDir + "/((Lnk12-IMGP[0-9]{4})|(Face1-IMGP529[0-9])|(Face2-IMGP531[0-9])).JPG\" 1000\n\t";

		aCom += "mm3d Tapas RadialStd \""+ chantDir + "/Calib-IMGP[0-9]{4}.JPG\" Out=Calib\n\t";
		aCom += "mm3d Tapas RadialStd \""+ chantDir + "/(Face1|Face2|Lnk12)-IMGP[0-9]{4}.JPG\" Out=All InCal=Calib\n\t";

		aCom += "mm3d AperiCloud \""+ chantDir + "/(Face|Lnk).*JPG\" All Out=AllCam.ply &&";
		
		aCom += "mm3d GCPBascule \""+ chantDir +  "/(Face1|Face2|Lnk12)-IMGP[0-9]{4}.JPG\" All Ground Mesure-TestApInit-3D.xml Mesure-TestApInit.xml\n\t";

		aCom += "mm3d RepLocBascule \""+ chantDir +  "/(Face1)-IMGP[0-9]{4}.JPG\" Ground  MesureBascFace1.xml Ortho-Cyl1.xml PostPlan=_MasqPlanFace1 OrthoCyl=true\n\t";
		aCom += "mm3d Tarama \""+ chantDir +  "/(Face1)-IMGP[0-9]{4}.JPG\" Ground  Repere=Ortho-Cyl1.xml  Out=TA-OC-F1 Zoom=4\n\t";
		aCom += "mm3d Malt Ortho \""+ chantDir +  "/(Face1)-IMGP[0-9]{4}.JPG\" Ground  Repere=Ortho-Cyl1.xml  SzW=1 ZoomF=1  DirMEC=Malt-OC-F1 DirTA=TA-OC-F1\n\t";
		aCom += "mm3d Tawny \""+ chantDir +  "/Ortho-UnAnam-Malt-OC-F1/\n\t";
		aCom += "mm3d Nuage2Ply "+ chantDir +  "/Malt-OC-F1/NuageImProf_Malt-Ortho-UnAnam_Etape_1.xml Attr="+ chantDir +  "/Ortho-UnAnam-Malt-OC-F1/Ortho-Eg-Test-Redr.tif Scale=3\n\t";

		aCom += "mm3d RepLocBascule \""+ chantDir +  "/(Face2)-IMGP[0-9]{4}.JPG\" Ground  MesureBascFace2.xml Ortho-Cyl2.xml PostPlan=_MasqPlanFace2 OrthoCyl=true\n\t";
		aCom += "mm3d Tarama \""+ chantDir +  "/(Face2)-IMGP[0-9]{4}.JPG\" Ground  Repere=Ortho-Cyl2.xml  Out=TA-OC-F2 Zoom=4\n\t";
		aCom += "mm3d Malt Ortho \""+ chantDir +  "/(Face2)-IMGP[0-9]{4}.JPG\" Ground  Repere=Ortho-Cyl2.xml  SzW=1 ZoomF=1  DirMEC=Malt-OC-F2 DirTA=TA-OC-F2 NbVI=2\n\t";
		aCom += "mm3d Tawny "+ chantDir +  "/Ortho-UnAnam-Malt-OC-F2/\n\t";
		aCom += "mm3d Tawny "+ chantDir +  "/Ortho-UnAnam-Malt-OC-F2/  DEq=0\n\t";
		aCom += "mm3d Nuage2Ply "+ chantDir +  "/Malt-OC-F2/NuageImProf_Malt-Ortho-UnAnam_Etape_1.xml Attr="+ chantDir +  "/Ortho-UnAnam-Malt-OC-F2/Ortho-Eg-Test-Redr.tif Scale=3\n\t";

		aCom += "mm3d SBGlobBascule \""+ chantDir +  "/(Face1|Face2|Lnk12)-IMGP[0-9]{4}.JPG\" All MesureBascFace1.xml  Glob PostPlan=_MasqPlanFace1  DistFS=2.0 Rep=ij\n\t";
	}

	fprintf(aFP,"%s",aCom.c_str());	

	ElFclose(aFP);
}

int TestCmds_main(int argc,char ** argv)
{
	std::string aDataDir, MkFile;
	int doAll = 0;

	ElInitArgMain
    (
		argc,argv,
		LArgMain()  << EAMC(aDataDir,"micmac_data directory"),
		LArgMain()  << EAM(doAll,"DoAll",true,"run the tool chain on all the data sets (def=false : run only on boudha data set)")	
	);

	MkFile = "makefile";

	GenerateMakeFile(MkFile, aDataDir, doAll==1);

	std::string aMk = g_externalToolHandler.get( "make" ).callName()+" all -f " + MkFile;
    System(aMk,true);

	std::cout << " *************************************************\n";
	std::cout << " **                                             **\n";
	std::cout << " **               Test finished                 **\n";
	std::cout << " **                                             **\n";
	std::cout << " **          You may check .ply files!          **\n";
	std::cout << " **                                             **\n";
	std::cout << " *************************************************\n";

    return 1;
}





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
