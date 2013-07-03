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

    MicMa cis an open source software specialized in image matching
    for research in geographic information. MicMac is built on the
    eLiSe image library. MicMac is governed by the  "Cecill-B licence".
    See below and http://www.cecill.info.

Header-MicMac-eLiSe-25/06/2007*/

#include "../../include/StdAfx.h"
#include "../src/uti_image/Arsenic.h"
#include "hassan/reechantillonnage.h"
#include <algorithm>
#include <functional>
#include <numeric>

void Arsenic_Banniere()
{
    std::cout <<  "\n";
    std::cout <<  " **********************************\n";
    std::cout <<  " *     A-utomated                 *\n";
    std::cout <<  " *     R-adiometric               *\n";
    std::cout <<  " *     S-hift                     *\n";
    std::cout <<  " *     E-qualization              *\n";
    std::cout <<  " *     N-ormalization             *\n";
    std::cout <<  " *     I-nter-images              *\n";
    std::cout <<  " *     C-orrection                *\n";
    std::cout <<  " **********************************\n\n";
}

vector<ArsenicImage> LoadGrpImages(string aDir, std::string aPatIm, int SzMMInit, string InVig)
{
	cInterfChantierNameManipulateur * aICNM = cInterfChantierNameManipulateur::BasicAlloc(aDir);
	const std::vector<std::string> * aSetIm = aICNM->Get(aPatIm);
	std::vector<std::string> aVectIm=*aSetIm;

	//Scaling the images the comply with MM-Initial-Model
	list<string> ListConvert, ListVig;
	vector<std::string> VectImSc,VectMasq;
	int nbIm=aVectIm.size();
	char SzMMInitch[3];sprintf(SzMMInitch, "%02d", SzMMInit);
	//If a vignette correction is entered
	string postfix="";
	if(InVig!=""){
		string cmdVig=MMDir() + "bin/mm3d Vodka " + aPatIm + " DoCor=1 Out=" + InVig + " InCal=" + InVig;
		postfix="_Vodka.tif";
		ListVig.push_back(cmdVig);
		cEl_GPAO::DoComInParal(ListVig,aDir + "MkVig");
	}


	for (int aK1=0 ; aK1<nbIm ; aK1++)
    {
		string cmdConv=MMDir() + "bin/ScaleIm " + InVig + (aVectIm)[aK1] + postfix + " " + (string)SzMMInitch + " F8B=1 Out=" + (aVectIm)[aK1] + "_Scaled.tif";
		ListConvert.push_back(cmdConv);

		VectMasq.push_back("Masq-TieP-" + (aVectIm)[aK1] + "/RN" + (aVectIm)[aK1] + "_Masq.tif");
		VectImSc.push_back((aVectIm)[aK1]+std::string("_Scaled.tif"));
	}
	cEl_GPAO::DoComInParal(ListConvert,aDir + "MkScale24");

	vector<ArsenicImage> aGrIm;

	for (int aK1=0 ; aK1<int(nbIm) ; aK1++)
	{
		ArsenicImage aIm;
		//reading 3D info
		cElNuage3DMaille * info3D1 = cElNuage3DMaille::FromFileIm("Masq-TieP-" + (aVectIm)[aK1] + "/NuageImProf_LeChantier_Etape_4.xml");
		//cElNuage3DMaille * info3D1 = cElNuage3DMaille::FromFileIm("MM-Malt-Img-" + StdPrefix((*aVectIm)[aK1]) + "/NuageImProf_STD-MALT_Etape_7.xml");

		aIm.info3D=info3D1;

		Tiff_Im aTF1= Tiff_Im::StdConvGen(aDir + VectImSc[aK1],3,false);
		Tiff_Im aTFM= Tiff_Im::StdConvGen(aDir + VectMasq[aK1],1,false);
		Pt2di aSz = aTF1.sz();
		Im2D_REAL4  aIm1R(aSz.x,aSz.y);
		Im2D_REAL4  aIm1G(aSz.x,aSz.y);
		Im2D_REAL4  aIm1B(aSz.x,aSz.y);
		Im2D_INT1  aMasq(aSz.x,aSz.y);
		ELISE_COPY
			(
				aTF1.all_pts(),
				aTF1.in(),
				Virgule(aIm1R.out(),aIm1G.out(),aIm1B.out())
			);
		
		ELISE_COPY
			(
				aTFM.all_pts(),
				aTFM.in(),
				aMasq.out()
			);

		aIm.Mask=aMasq;
		aIm.RChan=aIm1R;
		aIm.GChan=aIm1G;
		aIm.BChan=aIm1B;
		aIm.SZ=aSz;
		aGrIm.push_back(aIm);
	}

	return aGrIm;
}

double DistBetween(Pt3d<double> aP1, Pt3d<double> aP2 ){
	return (double)std::sqrt(pow(double(aP1.x-aP2.x),2)+pow(double(aP1.y-aP2.y),2)+pow(double(aP1.z-aP2.z),2));
}

PtsHom ReadPtsHom3D(string aDir,string aPatIm,string Extension, bool useMasq, string InVig, int SzMMInit)
{
	cInterfChantierNameManipulateur * aICNM = cInterfChantierNameManipulateur::BasicAlloc(aDir);
	const std::vector<std::string> * aSetIm = aICNM->Get(aPatIm);
	std::vector<std::string> aVectIm=*aSetIm;
	PtsHom aPtsHomol;
	int nbIm=aVectIm.size();
	vector<int> NbPtsCoupleInit(nbIm*nbIm,0);
	aPtsHomol.NbPtsCouple=NbPtsCoupleInit;

	//Loading all images
	vector<ArsenicImage> aGrIm=LoadGrpImages(aDir, aPatIm, SzMMInit, InVig);
	std::cout<<"===== "<<aGrIm.size()<< " images loaded"<<endl;

	//On parcours toutes les paires d'images diff�rentes (->test� dans le if)
    for (int aK1=0 ; aK1<nbIm ; aK1++)
    {
		cout<<"Extracting point from image "<<aK1+1<<" out of "<<nbIm<<endl;
		//going throug each point of image
		for (int aY=0 ; aY<aGrIm[aK1].SZ.y  ; aY++)
		{
			for (int aX=0 ; aX<aGrIm[aK1].SZ.x  ; aX++)
			{

				
				Pt2dr pos2DPtIm1;pos2DPtIm1.x=aX;pos2DPtIm1.y=aY;
				if(aGrIm[aK1].Mask.data()[aY][aX]==0){continue;}else{//If pts in masq, go look for 3D position
					Pt3d<double> pos3DPtIm1=aGrIm[aK1].info3D->PreciseCapteur2Terrain(pos2DPtIm1);					
						//Testing the position of the point in other images	
						vector<double> distances(nbIm,10000000); //distances between original 3D point and reprojection from other images
						vector<Pt2dr> pos2DOtherIm(nbIm);
						for (int aK2=0 ; aK2<int(nbIm) ; aK2++)
						{
							if (aK1!=aK2)
							{//cout<<aK2<<" "<<aY<<" "<<aX<<endl;
							Pt2dr pos2DPtIm2=aGrIm[aK2].info3D->Ter2Capteur(pos3DPtIm1);
									//if(vect3D[aK2]->PIsVisibleInImage(pos3DPtIm1)){//if pt in masq, go look for 2D position, then 3D position
							if(	pos2DPtIm2.x>0 && pos2DPtIm2.x<aGrIm[aK2].SZ.x && pos2DPtIm2.y>0 && pos2DPtIm2.y<aGrIm[aK2].SZ.y){
										//cout<<pos2DPtIm2.x<<" "<<pos2DPtIm2.y<<" " <<aGrIm[aK2].Mask.data()[int(pos2DPtIm2.y)][int(pos2DPtIm2.x)]<<endl;
										if(aGrIm[aK2].Mask.data()[int(pos2DPtIm2.y)][int(pos2DPtIm2.x)]){
											pos2DOtherIm[aK2]=pos2DPtIm2;
											//cout<<pos2DPtIm2.x<<" "<<pos2DPtIm2.y<<endl;
											Pt3d<double> pos3DPtIm2=aGrIm[aK2].info3D->PreciseCapteur2Terrain(pos2DPtIm2);
											distances[aK2]=DistBetween(pos3DPtIm1,pos3DPtIm2);
										}
									}
							}
						}
						//cout<<distances<<endl;
						double distMin=*min_element(distances.begin(),distances.end());//cout<<"distmin"<<distMin<<endl;
						for (int aK2=0 ; aK2<int(nbIm) ; aK2++){
							if(fabs(distances[aK2]/distMin-1)<0.20 && distances[aK2]!=10000000 && distMin<0.020){//id pos3DPtIm1~=pos3DPtIm2 -->pt is considered homologous,it is added to PtsHom (Gr1, R1, G1, B1, X1, Y1, idem 2, NbPtsCouple++)
								//cout<<"YES aK1 = " <<aK1<<" aK2 = " <<aK2<< " pos = " <<(aK1*nbIm)+aK2<<" pix1 = "<<aX<<" - "<<aY<<" pix2 = "<<pos2DOtherIm[aK2].x<<" - "<<pos2DOtherIm[aK2].y<<" with dist = "<<distances[aK2]<<endl;
								aPtsHomol.X1.push_back(SzMMInit*pos2DPtIm1.x) ;
								aPtsHomol.Y1.push_back(SzMMInit*pos2DPtIm1.y) ;
								aPtsHomol.X2.push_back(SzMMInit*pos2DOtherIm[aK2].x) ;
								aPtsHomol.Y2.push_back(SzMMInit*pos2DOtherIm[aK2].y) ;
								//Go looking for grey value of the point for each chan
								double Red1   =Reechantillonnage::biline(aGrIm[aK1].RChan.data(), aGrIm[aK1].SZ.x, aGrIm[aK1].SZ.y, pos2DPtIm1);
								double Green1 =Reechantillonnage::biline(aGrIm[aK1].GChan.data(), aGrIm[aK1].SZ.x, aGrIm[aK1].SZ.y, pos2DPtIm1);
								double Blue1  =Reechantillonnage::biline(aGrIm[aK1].BChan.data(), aGrIm[aK1].SZ.x, aGrIm[aK1].SZ.y, pos2DPtIm1);
								double Red2   =Reechantillonnage::biline(aGrIm[aK2].RChan.data(), aGrIm[aK2].SZ.x, aGrIm[aK2].SZ.y, pos2DOtherIm[aK2]);
								double Green2 =Reechantillonnage::biline(aGrIm[aK2].GChan.data(), aGrIm[aK2].SZ.x, aGrIm[aK2].SZ.y, pos2DOtherIm[aK2]);
								double Blue2  =Reechantillonnage::biline(aGrIm[aK2].BChan.data(), aGrIm[aK2].SZ.x, aGrIm[aK2].SZ.y, pos2DOtherIm[aK2]);
								aPtsHomol.Gr1.push_back((Red1+Green1+Blue1)/3);
								aPtsHomol.Gr2.push_back((Red2+Green2+Blue2)/3);
								aPtsHomol.R1.push_back(Red1);
								aPtsHomol.G1.push_back(Green1);
								aPtsHomol.B1.push_back(Blue1);
								aPtsHomol.R2.push_back(Red2);
								aPtsHomol.G2.push_back(Green2);
								aPtsHomol.B2.push_back(Blue2);
								aPtsHomol.NbPtsCouple[(aK1*nbIm)+aK2]++;
							}else{}//cout<<"NOT aK1 = " <<aK1<<" aK2 = " <<aK2<< " pos = " <<(aK1*nbIm)+aK2<<" aX = "<<aX<<" aY = "<<aY<<" with dist = "<<distances[aK2]<<endl;}
						}
				}
			}
		}
		
	}

		cout<<aPtsHomol.NbPtsCouple<<endl;
		return aPtsHomol;

}

PtsHom ReadPtsHom(string aDir,std::vector<std::string> * aSetIm,string Extension, bool useMasq, string InVig)
{
	PtsHom aPtsHomol;
	Pt2di aSz;
	//REAL4 ** aDataV1;
	//REAL4 ** aDataV2;

    // Permet de manipuler les ensemble de nom de fichier
    cInterfChantierNameManipulateur * aICNM = cInterfChantierNameManipulateur::BasicAlloc(aDir);

//On parcours toutes les paires d'images diff�rentes (->test� dans le if)
    for (int aK1=0 ; aK1<int(aSetIm->size()) ; aK1++)
    {
		/*
		//Read InVig
		if (InVig!=""){
			const cMetaDataPhoto & infoIm = cMetaDataPhoto::CreateExiv2(aDir + (*aSetIm)[aK1]);
			char foc[5],dia[4];
			sprintf(foc, "%04d", int(infoIm.FocMm()));
			sprintf(dia, "%03d", int(infoIm.Diaph()));
			string aNameVignette=InVig + "Foc" + (string)foc + "Diaph" + (string)dia + ".tif";
			std::ofstream file_out(aNameVignette.c_str());
			if(!file_out){
				cout<<"Couldn't find vignette tif file for "<<(*aSetIm)[aK1]<<" (Foc = "<<foc<<" Diaph = "<<dia<<endl;
			}else{
			//Reading the vignette
			Tiff_Im aTFV1= Tiff_Im::StdConvGen(aNameVignette,1,false);
			aSz = aTFV1.sz();
			Im2D_REAL4  aImV1(aSz.x,aSz.y);
			ELISE_COPY
				(
				   aTFV1.all_pts(),
				   aTFV1.in(),
				   aImV1.out()
				);

			aDataV1 = aImV1.data();
			}
		}
*/
		std::cout<<"Getting homologous points from: "<<(*aSetIm)[aK1]<<endl;
		//Reading the image and creating the objects to be manipulated
			Tiff_Im aTF1= Tiff_Im::StdConvGen(aDir + (*aSetIm)[aK1],3,false);
			aSz = aTF1.sz();
			Im2D_REAL4  aIm1R(aSz.x,aSz.y);
			Im2D_REAL4  aIm1G(aSz.x,aSz.y);
			Im2D_REAL4  aIm1B(aSz.x,aSz.y);
			ELISE_COPY
				(
				   aTF1.all_pts(),
				   aTF1.in(),
				   Virgule(aIm1R.out(),aIm1G.out(),aIm1B.out())
				);

			REAL4 ** aDataR1 = aIm1R.data();
			REAL4 ** aDataG1 = aIm1G.data();
			REAL4 ** aDataB1 = aIm1B.data();

		//read masq if activeted
		Im2D_U_INT1  aMasq(aSz.x,aSz.y);
		unsigned char ** aMasqData;
		if(useMasq){
			Tiff_Im aTFMasq= Tiff_Im::StdConvGen(aDir + (*aSetIm)[aK1] + "_Masq.tif",1,false);
			ELISE_COPY
				(
				   aTFMasq.all_pts(),
				   aTFMasq.in(),
				   aMasq.out()
				);

			aMasqData = aMasq.data();
			}


        for (int aK2=0 ; aK2<int(aSetIm->size()) ; aK2++)
        {
			if (aK1!=aK2)
            {
			Tiff_Im aTF2= Tiff_Im::StdConvGen(aDir + (*aSetIm)[aK2],3,false);
			Im2D_REAL4  aIm2R(aSz.x,aSz.y);
			Im2D_REAL4  aIm2G(aSz.x,aSz.y);
			Im2D_REAL4  aIm2B(aSz.x,aSz.y);
			ELISE_COPY
				(
				   aTF2.all_pts(),
				   aTF2.in(),
				   Virgule(aIm2R.out(),aIm2G.out(),aIm2B.out())
				);

			REAL4 ** aDataR2 = aIm2R.data();
			REAL4 ** aDataG2 = aIm2G.data();
			REAL4 ** aDataB2 = aIm2B.data();

			string prefixe="";
            
               std::string aNamePack =  aDir +  aICNM->Assoc1To2
                                        (
                                           "NKS-Assoc-CplIm2Hom@"+prefixe + "@" + Extension,
                                           (*aSetIm)[aK1],
                                           (*aSetIm)[aK2],
                                           true
                                        );

				   bool Exist = ELISE_fp::exist_file(aNamePack);
                   if (Exist)
                   {
                      ElPackHomologue aPack = ElPackHomologue::FromFile(aNamePack);
						int cpt=0;
							for 
							(
								ElPackHomologue::const_iterator itP=aPack.begin();
								itP!=aPack.end();
								itP++
							)
							{
								if(useMasq){
									if(Reechantillonnage::biline(aMasqData, aSz.x, aSz.y, itP->P1())<0.2){continue;}
								}
								cpt++;
								//Go looking for grey value of the point for each chan
								double Red1   =Reechantillonnage::biline(aDataR1, aSz.x, aSz.y, itP->P1());
								double Green1 =Reechantillonnage::biline(aDataG1, aSz.x, aSz.y, itP->P1());
								double Blue1  =Reechantillonnage::biline(aDataB1, aSz.x, aSz.y, itP->P1());
								double Red2   =Reechantillonnage::biline(aDataR2, aSz.x, aSz.y, itP->P2());
								double Green2 =Reechantillonnage::biline(aDataG2, aSz.x, aSz.y, itP->P2());
								double Blue2  =Reechantillonnage::biline(aDataB2, aSz.x, aSz.y, itP->P2());
							aPtsHomol.Gr1.push_back((Red1+Green1+Blue1)/3);
							aPtsHomol.Gr2.push_back((Red2+Green2+Blue2)/3);
							aPtsHomol.R1.push_back(Red1);
							aPtsHomol.G1.push_back(Green1);
							aPtsHomol.B1.push_back(Blue1);
							aPtsHomol.R2.push_back(Red2);
							aPtsHomol.G2.push_back(Green2);
							aPtsHomol.B2.push_back(Blue2);
							aPtsHomol.X1.push_back(itP->P1().x);
							aPtsHomol.Y1.push_back(itP->P1().y);
							aPtsHomol.X2.push_back(itP->P2().x);
							aPtsHomol.Y2.push_back(itP->P2().y);
							}
							aPtsHomol.NbPtsCouple.push_back(cpt);
				   }
                   else{
                      std::cout  << "     # NO PACK FOR  : " << aNamePack  << "\n";
					  aPtsHomol.NbPtsCouple.push_back(0);
				   }
            }
        }
    }
	int nbPts=aPtsHomol.Gr1.size();
	cout<<"--- Nb Pts read : "<<nbPts<<endl;
	//aPtsHomol.SZ=aSz;
   return aPtsHomol;
}

double oneParamRANSAC(vector<double> im1, vector<double> im2){

	srand(time(NULL));//Initiate the rand value
	double aScoreMax=5;
	double bestK=1;
	for(unsigned i=0;i<100;i++){
		int j=rand() % im1.size();
		double K=im1[j]/im2[j];

		//Counting Inliers
		double nbInliers=0;
		double aScore=0;
		for(unsigned m=0;m<im1.size();m++){
			if(fabs((im1[m]/im2[m])/K-1)<0.50){nbInliers++;aScore=aScore+fabs((im1[m]/im2[m])-K);}
		}
		aScore=aScore/nbInliers;
		if(0.3<nbInliers/im1.size() && aScoreMax>aScore){aScoreMax=aScore;bestK=K;}
	}
	//cout<<aScoreMax<< " - ";
return bestK;
}

Param3Chan SolveAndArrange(L2SysSurResol aSysR,L2SysSurResol aSysG,L2SysSurResol aSysB, int nbIm, int nbParam){
	
Param3Chan aParam3Chan;

bool Ok1,Ok2,Ok3;
Im1D_REAL8 aSolR = aSysR.GSSR_Solve(&Ok1);
Im1D_REAL8 aSolG = aSysG.GSSR_Solve(&Ok2);
Im1D_REAL8 aSolB = aSysB.GSSR_Solve(&Ok3);

if (Ok1 && Ok2 && Ok3)
{
    double* aDataR = aSolR.data();
    double* aDataG = aSolG.data();
    double* aDataB = aSolB.data();
	//cout<<aSysRInit.ResiduOfSol(aDataR)<<endl;
	//cout<<aSysGInit.ResiduOfSol(aDataG)<<endl;
	//cout<<aSysBInit.ResiduOfSol(aDataB)<<endl;
	for(unsigned i=0;i<int(nbIm*nbParam);i++){
		//cout<<"For im NUM "<<i<<" CorR = "<<aDataR[i]<<" CorG = "<<aDataG[i]<<" CorB = "<<aDataB[i]<<endl;
		aParam3Chan.parRed.push_back(aDataR[i]);
		aParam3Chan.parGreen.push_back(aDataG[i]);
		aParam3Chan.parBlue.push_back(aDataB[i]);
	}
	if (nbParam==1){
		//Normalize the result :
		double maxFactorR=1/(*max_element(aParam3Chan.parRed.begin(),aParam3Chan.parRed.end()));
		double maxFactorG=1/(*max_element(aParam3Chan.parGreen.begin(),aParam3Chan.parGreen.end()));
		double maxFactorB=1/(*max_element(aParam3Chan.parBlue.begin(),aParam3Chan.parBlue.end()));
		for(unsigned i=0;i<int(nbIm);i++){
			if(maxFactorR>1){aParam3Chan.parRed[i]  =aParam3Chan.parRed[i]  *maxFactorR;}
			if(maxFactorG>1){aParam3Chan.parGreen[i]=aParam3Chan.parGreen[i]*maxFactorG;}
			if(maxFactorB>1){aParam3Chan.parBlue[i] =aParam3Chan.parBlue[i] *maxFactorB;}
		}
	}
}

	return aParam3Chan;
}

Param3Chan Egalisation_factors(PtsHom aPtsHomol, int nbIm, int aMasterNum, int aDegPoly){

	vector<vector<double> > Gr(nbIm);

// Create L2SysSurResol to solve least square equation with nbIm unknown
	L2SysSurResol aSysRInit(nbIm);
	L2SysSurResol aSysGInit(nbIm);
	L2SysSurResol aSysBInit(nbIm);

	
//Finding and Selecting the brightest image for reference
int nbParcouru=0;
for (int i=0;i<int(aPtsHomol.NbPtsCouple.size());i++){

	int numImage1=(i/(nbIm));
	int numImage2=i-numImage1*(nbIm);

if (numImage1!=numImage2){
	if(aPtsHomol.NbPtsCouple[i]!=0){//if there are homologous points between images
		vector<double> GrIm1(aPtsHomol.Gr1.begin()+nbParcouru,aPtsHomol.Gr1.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> GrIm2(aPtsHomol.Gr2.begin()+nbParcouru,aPtsHomol.Gr2.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);

		nbParcouru=nbParcouru+aPtsHomol.NbPtsCouple[i];

		std::copy (GrIm1.begin(),GrIm1.end(),back_inserter(Gr[numImage1]));
		std::copy (GrIm2.begin(),GrIm2.end(),back_inserter(Gr[numImage2]));
	}
}
}

if(aMasterNum==-1){
	double Gmax = 0;
	for(int i=0;i<int(nbIm);i++)
	{
		double meanGr = std::accumulate(Gr[i].begin(),Gr[i].end(),0.0)/Gr[i].size();
		if(meanGr>Gmax){Gmax=meanGr;aMasterNum=i;}
	}
	cout<<"The brightest image (chosen as Master) is NUM "<<aMasterNum<<endl;
}

//Solve with equation : ( model is : alpha1*G1-alpha2*G2=0 )

for(int i=0;i<int(nbIm);i++){
	double grMax=*max_element(Gr[i].begin(),Gr[i].end());
	vector<double> aCoefsFixe(nbIm,0.0);
	aCoefsFixe[i]=1;
	double * coefsFixeAr=&aCoefsFixe[0];
	aSysRInit.AddEquation(pow(float(nbParcouru),2),coefsFixeAr,255/grMax);
	aSysGInit.AddEquation(pow(float(nbParcouru),2),coefsFixeAr,255/grMax);
	aSysBInit.AddEquation(pow(float(nbParcouru),2),coefsFixeAr,255/grMax);
}

//The brightest image is fixed, using superbig weight in least square:
double grMax=*max_element(Gr[aMasterNum].begin(),Gr[aMasterNum].end());
cout<<grMax<<endl;
vector<double> aCoefsFixe(nbIm,0.0);
aCoefsFixe[aMasterNum]=1;
double * coefsFixeAr=&aCoefsFixe[0];
aSysRInit.AddEquation(pow(float(nbParcouru),5),coefsFixeAr,255/grMax);
aSysGInit.AddEquation(pow(float(nbParcouru),5),coefsFixeAr,255/grMax);
aSysBInit.AddEquation(pow(float(nbParcouru),5),coefsFixeAr,255/grMax);

cout<<"Solution of zeros preventing equations written"<<endl;

nbParcouru=0;
//For each linked couples :
for (int i=0;i<int(aPtsHomol.NbPtsCouple.size());i++){

	int numImage1=(i/(nbIm));

	int numImage2=i-numImage1*(nbIm);
if (numImage1!=numImage2){
	if(aPtsHomol.NbPtsCouple[i]!=0){//if there are homologous points between images
		vector<double> RIm1(aPtsHomol.R1.begin()+nbParcouru,aPtsHomol.R1.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> GIm1(aPtsHomol.G1.begin()+nbParcouru,aPtsHomol.G1.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> BIm1(aPtsHomol.B1.begin()+nbParcouru,aPtsHomol.B1.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> RIm2(aPtsHomol.R2.begin()+nbParcouru,aPtsHomol.R2.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> GIm2(aPtsHomol.G2.begin()+nbParcouru,aPtsHomol.G2.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> BIm2(aPtsHomol.B2.begin()+nbParcouru,aPtsHomol.B2.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		nbParcouru=nbParcouru+aPtsHomol.NbPtsCouple[i];
		
		//adding equations for each point 
		for (int j=0;j<int(RIm1.size());j++){
			vector<double> aCoefsR(nbIm, 0.0);
			vector<double> aCoefsG(nbIm, 0.0);
			vector<double> aCoefsB(nbIm, 0.0);
			aCoefsR[numImage1]=RIm1[j];
			aCoefsG[numImage1]=GIm1[j];
			aCoefsB[numImage1]=BIm1[j];
			aCoefsR[numImage2]=-RIm2[j];
			aCoefsG[numImage2]=-GIm2[j];
			aCoefsB[numImage2]=-BIm2[j];
			double * coefsArR=&aCoefsR[0];
			double * coefsArG=&aCoefsG[0];
			double * coefsArB=&aCoefsB[0];
			double aPds=1;
			if(numImage1==aMasterNum || numImage2==aMasterNum){aPds=nbParcouru/nbIm;}
			aSysRInit.AddEquation(aPds,coefsArR,0);
			aSysGInit.AddEquation(aPds,coefsArG,0);
			aSysBInit.AddEquation(aPds,coefsArB,0);
		}
	}
}
}
cout<<nbParcouru<<" points were read"<<endl;
cout<<"Solving the initial system"<<endl;

Param3Chan aParam3Chan=SolveAndArrange(aSysRInit, aSysGInit, aSysBInit, nbIm, 1);

cout<<aParam3Chan.parRed<<endl;
cout<<aParam3Chan.parGreen<<endl;
cout<<aParam3Chan.parBlue<<endl;
/*****************************************************************************************************/
/*Introducing more parameters (model is : G1*poly(X1) + G1*poly(Y1) - G2*poly(X2) - G2*poly(Y2) = 0 )*/
/*****************************************************************************************************/

	int nbParam=aDegPoly*2+1;//nb param in the model
// Create L2SysSurResol to solve least square equation with nbParam*nbIm unknown
	L2SysSurResol aSysR(nbParam*nbIm);
	L2SysSurResol aSysG(nbParam*nbIm);
	L2SysSurResol aSysB(nbParam*nbIm);


for(int i=0;i<int(nbIm);i++){
	double grMax=*max_element(Gr[i].begin(),Gr[i].end());
	vector<double> aCoefsFixe(nbParam*nbIm,0.0);
	aCoefsFixe[nbParam*i]=1;
	double * coefsFixeAr=&aCoefsFixe[0];
	aSysR.AddEquation(pow(float(nbParcouru),3),coefsFixeAr,aParam3Chan.parRed[i]);
	aSysG.AddEquation(pow(float(nbParcouru),3),coefsFixeAr,aParam3Chan.parGreen[i]);
	aSysB.AddEquation(pow(float(nbParcouru),3),coefsFixeAr,aParam3Chan.parBlue[i]);
	for (int a=1;a<nbParam;a++){
		vector<double> aCoefsFixe(nbParam*nbIm,0.0);
		aCoefsFixe[nbParam*i+a]=1;
		double * coefsFixeAr=&aCoefsFixe[0];
		aSysR.AddEquation(pow(float(nbParcouru),3),coefsFixeAr,0);
		aSysG.AddEquation(pow(float(nbParcouru),3),coefsFixeAr,0);
		aSysB.AddEquation(pow(float(nbParcouru),3),coefsFixeAr,0);
	}
}

/*
		//The brightest image is fixed, using superbig weight in least square:
	vector<double> aCoefsFixe2(nbParam*nbIm,0.0);
	aCoefsFixe2[nbParam*aMasterNum]=1;
	double * coefsFixe2Ar=&aCoefsFixe2[0];
	aSysR.AddEquation(pow(float(nbParcouru),3),coefsFixe2Ar,255/grMax);
	aSysG.AddEquation(pow(float(nbParcouru),3),coefsFixe2Ar,255/grMax);
	aSysB.AddEquation(pow(float(nbParcouru),3),coefsFixe2Ar,255/grMax);
	for (int a=1;a<nbParam;a++){
		vector<double> aCoefsFixe(nbParam*nbIm,0.0);
		aCoefsFixe[nbParam*aMasterNum+a]=1;
		double * coefsFixeAr=&aCoefsFixe[0];
		aSysR.AddEquation(pow(float(nbParcouru),4),coefsFixeAr,0);
		aSysG.AddEquation(pow(float(nbParcouru),4),coefsFixeAr,0);
		aSysB.AddEquation(pow(float(nbParcouru),4),coefsFixeAr,0);
	}
*/

cout<<" --- Getting the equations from homologous points (model is : G1*poly(X1) + G1*poly(Y1) - G2*poly(X2) - G2*poly(Y2) = 0 )"<<endl;
nbParcouru=0;
//For each linked couples :
for (int i=0;i<int(aPtsHomol.NbPtsCouple.size());i++){

	int numImage1=(i/(nbIm));
	int numImage2=i-numImage1*(nbIm);

if (numImage1!=numImage2){
	if(aPtsHomol.NbPtsCouple[i]!=0){//if there are homologous points between images
		vector<double> RIm1(aPtsHomol.R1.begin()+nbParcouru,aPtsHomol.R1.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> GIm1(aPtsHomol.G1.begin()+nbParcouru,aPtsHomol.G1.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> BIm1(aPtsHomol.B1.begin()+nbParcouru,aPtsHomol.B1.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> RIm2(aPtsHomol.R2.begin()+nbParcouru,aPtsHomol.R2.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> GIm2(aPtsHomol.G2.begin()+nbParcouru,aPtsHomol.G2.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> BIm2(aPtsHomol.B2.begin()+nbParcouru,aPtsHomol.B2.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> X1(aPtsHomol.X1.begin()+nbParcouru,aPtsHomol.X1.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> Y1(aPtsHomol.Y1.begin()+nbParcouru,aPtsHomol.Y1.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> X2(aPtsHomol.X2.begin()+nbParcouru,aPtsHomol.X2.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		vector<double> Y2(aPtsHomol.Y2.begin()+nbParcouru,aPtsHomol.Y2.begin()+nbParcouru+aPtsHomol.NbPtsCouple[i]-1);
		nbParcouru=nbParcouru+aPtsHomol.NbPtsCouple[i];														 
																									 
		//adding equations for each point 
		for (int j=0;j<int(RIm1.size());j++){
			vector<double> aCoefsR(nbParam*nbIm, 0.0);
			vector<double> aCoefsG(nbParam*nbIm, 0.0);
			vector<double> aCoefsB(nbParam*nbIm, 0.0);
			aCoefsR[nbParam*numImage1]=RIm1[j];
			aCoefsG[nbParam*numImage1]=GIm1[j];
			aCoefsB[nbParam*numImage1]=BIm1[j];
			aCoefsR[nbParam*numImage2]=-RIm2[j];
			aCoefsG[nbParam*numImage2]=-GIm2[j];
			aCoefsB[nbParam*numImage2]=-BIm2[j];
			for(int k=1;k<=((nbParam-1)/2);k++){
				aCoefsR[nbParam*numImage1+2*k-1]=RIm1[j]*pow(X1[j],k);
				aCoefsG[nbParam*numImage1+2*k-1]=GIm1[j]*pow(X1[j],k);
				aCoefsB[nbParam*numImage1+2*k-1]=BIm1[j]*pow(X1[j],k);
				aCoefsR[nbParam*numImage1+2*k]=RIm1[j]*pow(Y1[j],k);
				aCoefsG[nbParam*numImage1+2*k]=GIm1[j]*pow(Y1[j],k);
				aCoefsB[nbParam*numImage1+2*k]=BIm1[j]*pow(Y1[j],k);

				aCoefsR[nbParam*numImage2+2*k-1]=-RIm2[j]*pow(X2[j],k);
				aCoefsG[nbParam*numImage2+2*k-1]=-GIm2[j]*pow(X2[j],k);
				aCoefsB[nbParam*numImage2+2*k-1]=-BIm2[j]*pow(X2[j],k);
				aCoefsR[nbParam*numImage2+2*k]=-RIm2[j]*pow(Y2[j],k);
				aCoefsG[nbParam*numImage2+2*k]=-GIm2[j]*pow(Y2[j],k);
				aCoefsB[nbParam*numImage2+2*k]=-BIm2[j]*pow(Y2[j],k);
			}
					
			//cout<<aCoefsR[0]<<" - "<<aCoefsR[1]<<" - "<<aCoefsR[2]<<" - "<<aCoefsR[3]<<" - "<<aCoefsR[4]<<" - "<<aCoefsR[5]<<" - "<<aCoefsR[6]<<" - "<<aCoefsR[7]<<" - "<<aCoefsR[8]<<" - "<<aCoefsR[9]<<" - "<<aCoefsR[10]<<" - "<<aCoefsR[11]<<" - "<<aCoefsR[12]<<" - "<<aCoefsR[13]<<" - "<<aCoefsR[14]<<" - "<<aCoefsR[15]<<" - "<<aCoefsR[16]<<" - "<<aCoefsR[17]<<endl;
			double * coefsArR=&aCoefsR[0];
			double * coefsArG=&aCoefsG[0];
			double * coefsArB=&aCoefsB[0];
			double aPds=1;
			if(numImage1==aMasterNum || numImage2==aMasterNum){aPds=1;}
			aSysR.AddEquation(aPds,coefsArR,0);
			aSysG.AddEquation(aPds,coefsArG,0);
			aSysB.AddEquation(aPds,coefsArB,0);
		}
	}
}
}

cout<<"Solving the final system"<<endl;

aParam3Chan=SolveAndArrange(aSysR, aSysG, aSysB, nbIm, nbParam);
cout<<aParam3Chan.parRed<<endl;
cout<<aParam3Chan.parGreen<<endl;
cout<<aParam3Chan.parBlue<<endl;
return aParam3Chan;
}

void Egal_correct(string aDir,std::vector<std::string> * aSetIm,Param3Chan  aParam3chan,string aDirOut, string InVig)
{
	//Bulding the output file system
    ELISE_fp::MkDirRec(aDir + aDirOut);
	//Reading input files
    int nbIm=(aSetIm)->size();
	int nbParam=aParam3chan.size()/nbIm;
	cout<<nbParam<<endl;
	string suffix="";if(InVig!=""){suffix="_Vodka.tif";}
    for(int i=0;i<nbIm;i++)
	{
	    string aNameIm=InVig + (*aSetIm)[i] + suffix;
		cout<<"Correcting "<<aNameIm<<endl;
		string aNameOut=aDir + aDirOut + (*aSetIm)[i] +"_egal.tif";

		//Reading the image and creating the objects to be manipulated
		Tiff_Im aTF= Tiff_Im::StdConvGen(aDir + aNameIm,3,false);
		Pt2di aSz = aTF.sz();

		Im2D_U_INT1  aImR(aSz.x,aSz.y);
		Im2D_U_INT1  aImG(aSz.x,aSz.y);
		Im2D_U_INT1  aImB(aSz.x,aSz.y);

		ELISE_COPY
		(
		   aTF.all_pts(),
		   aTF.in(),
		   Virgule(aImR.out(),aImG.out(),aImB.out())
		);

		U_INT1 ** aDataR = aImR.data();
		U_INT1 ** aDataG = aImG.data();
		U_INT1 ** aDataB = aImB.data();
		
		//cout<<"Correction factors for image n"<<i<<" -> R : "<<aParam3chan[0][0+nbParam*i]<<endl;//" + "<<aParam3chan[0][1+nbParam*i]<<" * X + "<<aParam3chan[0][2+nbParam*i]<<" * Y + "<<aParam3chan[0][3+nbParam*i]<<" * X^2 + "<<aParam3chan[0][4+nbParam*i]<<" * Y^2 + "<<aParam3chan[0][5+nbParam*i]<<" * X^3 + "<<aParam3chan[0][6+nbParam*i]<<" * Y^3"<<endl;
		//cout<<"Correction factors for image n"<<i<<" -> G : "<<aParam3chan[1][0+nbParam*i]<<endl;//" + "<<aParam3chan[1][1+nbParam*i]<<" * X + "<<aParam3chan[1][2+nbParam*i]<<" * Y + "<<aParam3chan[1][3+nbParam*i]<<" * X^2 + "<<aParam3chan[1][4+nbParam*i]<<" * Y^2 + "<<aParam3chan[1][5+nbParam*i]<<" * X^3 + "<<aParam3chan[1][6+nbParam*i]<<" * Y^3"<<endl;
		//cout<<"Correction factors for image n"<<i<<" -> B : "<<aParam3chan[2][0+nbParam*i]<<endl;//" + "<<aParam3chan[2][1+nbParam*i]<<" * X + "<<aParam3chan[2][2+nbParam*i]<<" * Y + "<<aParam3chan[2][3+nbParam*i]<<" * X^2 + "<<aParam3chan[2][4+nbParam*i]<<" * Y^2 + "<<aParam3chan[2][5+nbParam*i]<<" * X^3 + "<<aParam3chan[2][6+nbParam*i]<<" * Y^3"<<endl;
		for (int aY=0 ; aY<aSz.y  ; aY++)
			{
				for (int aX=0 ; aX<aSz.x  ; aX++)
				{

					double corR=aParam3chan.parRed[nbParam*i],corG=aParam3chan.parGreen[nbParam*i],corB=aParam3chan.parBlue[nbParam*i];
					for(int j=1;j<=(nbParam-1)/2;j++){
						corR = corR + pow(float(aX),j) *   aParam3chan.parRed[2*j-1+nbParam*i] + pow(float(aY),j) *   aParam3chan.parRed[2*j+nbParam*i] ;
						corG = corG + pow(float(aX),j) * aParam3chan.parGreen[2*j-1+nbParam*i] + pow(float(aY),j) * aParam3chan.parGreen[2*j+nbParam*i] ;
						corB = corB + pow(float(aX),j) *  aParam3chan.parBlue[2*j-1+nbParam*i] + pow(float(aY),j) *  aParam3chan.parBlue[2*j+nbParam*i] ;
					}
					double R = aDataR[aY][aX] * corR;
					double G = aDataG[aY][aX] * corG;
					double B = aDataB[aY][aX] * corB;
					if(R>255){aDataR[aY][aX]=255;}else if(R<0){aDataR[aY][aX]=0;}else{aDataR[aY][aX]=R;}
					if(G>255){aDataG[aY][aX]=255;}else if(G<0){aDataG[aY][aX]=0;}else{aDataG[aY][aX]=G;}
					if(B>255){aDataB[aY][aX]=255;}else if(B<0){aDataB[aY][aX]=0;}else{aDataB[aY][aX]=B;}
				}
		}

		 Tiff_Im  aTOut
			(
				aNameOut.c_str(),
				aSz,
				GenIm::u_int1,
				Tiff_Im::No_Compr,
				Tiff_Im::RGB
			);


		 ELISE_COPY
			 (
				 aTOut.all_pts(),
				 Virgule(aImR.in(),aImG.in(),aImB.in()),
				 aTOut.out()
			 );
	  
	}
}

int  Arsenic_main(int argc,char ** argv)
{

	std::string aFullPattern,aDirOut="Egal/",aMaster="",InVig="";
	bool InTxt=false,DoCor=false,useMasq=false;
	int aDegPoly=3;
	int SzMMInit=24;
	  //Reading the arguments
        ElInitArgMain
        (
            argc,argv,
            LArgMain()  << EAMC(aFullPattern,"Images Pattern"),
            LArgMain()  << EAM(aDirOut,"Out",true,"Output folder (end with /) and/or prefix (end with another char)")
						<< EAM(InVig,"InVig",true,"Input vignette tif file folder")
						<< EAM(InTxt,"InTxt",true,"True if homologous points have been exported in txt (Defaut=false)")
						<< EAM(DoCor,"DoCor",true,"Use the computed parameters to correct the images (Defaut=false)")
						<< EAM(aMaster,"Master",true,"Manually define a Master Image (to be used a reference)")
						<< EAM(aDegPoly,"DegPoly",true,"Set the dergree of the corretion polynom (Def=3)")
						//<< EAM(useMasq,"useMasq",true,"Activate the use of masqs (1 per image) (Def=false)")
						<< EAM(SzMMInit,"SzMMInit",true,"Size o MMInitial model masq (Def=24, with MMInitial option ReduceExport=3 and Zoom=8)")
        );
		std::string aDir,aPatIm;
		SplitDirAndFile(aDir,aPatIm,aFullPattern);

		std::string Extension = "dat";
		if (InTxt){Extension="txt";}

		cInterfChantierNameManipulateur * aICNM = cInterfChantierNameManipulateur::BasicAlloc(aDir);
		const std::vector<std::string> * aSetIm = aICNM->Get(aPatIm);

		std::vector<std::string> aVectIm=*aSetIm;
		int nbIm=aVectIm.size();

		//Looking for master image NUM:
		int aMasterNum=-1;
		for (int i=0;i<int(nbIm);i++){
			if(aVectIm[i]==aMaster){aMasterNum=i;cout<<"Found Master image "<<aMaster<<" as image NUM "<<i<<endl;}
		}

		//Reading homologous points
		PtsHom aPtsHomol=ReadPtsHom3D(aDir, aPatIm, Extension, useMasq, InVig, SzMMInit);
		
		cout<<"Computing equalization factors"<<endl;
		Param3Chan aParam3chan=Egalisation_factors(aPtsHomol,nbIm,aMasterNum,aDegPoly);

		if(aParam3chan.size()==0){
			cout<<"Couldn't compute parameters "<<endl;
		}else if(DoCor){
			Egal_correct(aDir, & aVectIm, aParam3chan, aDirOut, InVig);
		}
		
		Arsenic_Banniere();

		return 0;
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

