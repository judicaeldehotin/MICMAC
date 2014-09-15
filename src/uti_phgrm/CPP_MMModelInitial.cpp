/*Header-MicMac-eLiSe-25/06/2007peroChImMM_main

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

extern const std::string TheDIRMergTiepForEPI();

std::string DirFusMMInit() {return "Fusion-MMMI/";}

class cAppli_Enveloppe_Main : public  cAppliWithSetImage
{
    public :
       cAppli_Enveloppe_Main(int argc,char ** argv);
       std::string NameFileLoc(const std::string & aPost ,int aZoom)
       {
           std::string aStrZoom =  std::string("Env_DeZoom") +ToString(aZoom );
           return  Dir() + TheDIRMergTiepForEPI() + "-" +   mNameIm + "/" + aStrZoom + "_" + aPost + ".tif";

       }

       std::string NameFileGlob(const std::string & aPref) { return  aPref + mNameIm + ".tif"; }
       std::string NameFileGlobWithDir(const std::string & aPref)
       {
           return  Dir() + DirFusMMInit() + NameFileGlob(aPref);

       }
    private :
      int mZoom0;
      int mZoomEnd;
      std::string mNameIm;
      bool mCalledByP;
};



cAppli_Enveloppe_Main::cAppli_Enveloppe_Main(int argc,char ** argv) :
   cAppliWithSetImage(argc-1,argv+1,0),
   mCalledByP (false)
{
   std::string Masq3D;
   std::string aPat,anOri;

   ElInitArgMain
   (
        argc,argv,
        LArgMain()  << EAMC(aPat,"Full Directory (Dir+Pattern)",eSAM_IsPatFile)
                    << EAMC(anOri,"Orientation ", eSAM_IsExistDirOri)
                    << EAMC(mZoom0,"Zoom lowest resol ", eSAM_IsExistDirOri)
                    << EAMC(mZoomEnd,"Zoom largest resol ", eSAM_IsExistDirOri),
        LArgMain()  << EAM(Masq3D,"Masq3D",true,"Masq3D pour filtrer")
                    << EAM(mCalledByP,"InternalCalledByP",true)
   );

   if (! (mCalledByP))
   {
       ELISE_fp::MkDir(Dir() + DirFusMMInit() );
       std::list<std::string>  aLCom = ExpandCommand(3,"InternalCalledByP=true");

       for (std::list<std::string>::iterator itS=aLCom.begin() ; itS!=aLCom.end() ; itS++)
           std::cout << *itS << "\n";

       return;
   }


   if (!mModeHelp)
   {
       ELISE_ASSERT(mVSoms.size()==1,"Only one image for cAppli_Enveloppe_Main");
       mNameIm = mVSoms[0]->attr().mIma->mNameIm;
   }



   Im2D_REAL4   aEnvMax(1,1);
   Im2D_REAL4   aEnvMin(1,1);
   Im2D_U_INT1  aMasqEnv(1,1);
   for (int aZoom = mZoom0 ; aZoom >= mZoomEnd ; aZoom /= 2)
   {
          std::string aCom =    MM3dBinFile("MMInitialModel ")
                              + mEASF.mFullName + " "
                              + Ori() 
                              + std::string(" DoMatch=false  Do2Z=false   ExportEnv=true  Zoom=")
                              + ToString(aZoom);
          if (EAMIsInit(&Masq3D)) aCom = aCom + " Masq3D=" + Masq3D;

          System(aCom);
          std::string aNameMax = NameFileLoc("Max",aZoom);
          std::string aNameMin = NameFileLoc("Min",aZoom);
          std::string aNameMasq = NameFileLoc("Masq",aZoom);

          if (aZoom==mZoom0)
          {
              aEnvMax = Im2D_REAL4::FromFileStd(aNameMax);
              aEnvMin = Im2D_REAL4::FromFileStd(aNameMin);

//std::cout << "AAAAAAAA \n" ; getchar();
              aMasqEnv = Im2D_U_INT1::FromFileStd(aNameMasq);
//std::cout << "BBBBBB \n" ; getchar();

 //Tiff_Im::CreateFromIm(aMasqEnv,"Test.tif");getchar();

          }
          else
          {
               ELISE_COPY
               (
                  aEnvMax.all_pts(),
                  Max(aEnvMax.in(),Tiff_Im(aNameMax.c_str()).in()),
                  aEnvMax.out()
               );
               ELISE_COPY
               (
                  aEnvMin.all_pts(),
                  Min(aEnvMin.in(),Tiff_Im(aNameMin.c_str()).in()),
                  aEnvMin.out()
               );
               ELISE_COPY
               (
                  aMasqEnv.all_pts(),
                  aMasqEnv.in() || Tiff_Im(aNameMasq.c_str()).in(),
                  aMasqEnv.out()
               );
          }
   }
   Tiff_Im::CreateFromIm(aEnvMax, NameFileGlobWithDir("Fusion-Max"));
   Tiff_Im::CreateFromIm(aEnvMin, NameFileGlobWithDir("Fusion-Min"));
   Tiff_Im::CreateFromFonc(NameFileGlobWithDir("Fusion-Masq"),aMasqEnv.sz(),aMasqEnv.in(),GenIm::bits1_msbf);
}

int MMEnveloppe_Main(int argc,char ** argv)
{
   cAppli_Enveloppe_Main(argc,argv);
   return 1;
}



  //=========================================

int MMInitialModel_main(int argc,char ** argv)
{
    MMD_InitArgcArgv(argc,argv);

    std::string  aDir,aPat,aFullDir;
    std::string  AeroIn;
    std::string  ImSec;
    bool         Visu = false;
    bool         ExportEnv = false;
    bool         DoPly = false;
    bool         DoMatch = true;

    int aZoom = 8;
    bool aDo2Z = true;
    double aReducePly=3.0;
    std::string aMasq3D;


    ElInitArgMain
    (
    argc,argv,
    LArgMain()  << EAMC(aFullDir,"Dir + Pattern", eSAM_IsPatFile)
                    << EAMC(AeroIn,"Orientation", eSAM_IsExistDirOri),
    LArgMain()
                    << EAM(Visu,"Visu",true,"Interactif Visualization (tuning purpose, program will stop at breakpoint)", eSAM_IsBool)
                    << EAM(DoPly,"DoPly",true,"Generate ply ,for tuning purpose (Def=false)", eSAM_IsBool)
                    << EAM(aZoom,"Zoom",true,"Zoom of computed models (Def=8)")
                    << EAM(aReducePly,"ReduceExp",true,"Down scaling of cloud , XML and ply (Def=3)")
                    << EAM(aDo2Z,"Do2Z",true,"Excute a first step at 2*Zoom (Def=true)", eSAM_IsBool)
                    << EAM(DoMatch,"DoMatch",true,"Do \"classical\" MicMac at end (Def=true)", eSAM_IsBool)
                    << EAM(aMasq3D,"Masq3D",true,"3D masq when exist (Def=true)", eSAM_IsBool)
                    << EAM(ExportEnv,"ExportEnv",true,"Export Max Min surfaces (Def=false)", eSAM_IsBool)
    );

    #if (ELISE_windows)
        replace( aFullDir.begin(), aFullDir.end(), '\\', '/' );
    #endif
    SplitDirAndFile(aDir,aPat,aFullDir);
    StdCorrecNameOrient(AeroIn,aDir);

    cInterfChantierNameManipulateur * aICNM =  cInterfChantierNameManipulateur::BasicAlloc(aDir);

    if (! EAMIsInit(&ImSec))
       ImSec = AeroIn;

    // Genere les pryramides pour que le paral ne s'ecrase pas les 1 les autres
    {
         std::string aComPyr =  MM3dBinFile("MMPyram")
                                + QUOTE(aFullDir) + " "
                                + AeroIn + " "
                                + "ImSec=" +ImSec;

         VoidSystem(aComPyr.c_str());
    }

    const cInterfChantierNameManipulateur::tSet * aSetIm = aICNM->Get(aPat);

    std::list<std::string> aLCom;

    for (int aKIm=0 ; aKIm<int(aSetIm->size()) ; aKIm++)
    {
          std::string aCom =   MM3dBinFile("MICMAC")
                              //  + XML_MM_File("MM-ModelInitial.xml")
                              + XML_MM_File("MM-TieP.xml")
                              + std::string(" WorkDir=") +aDir +  std::string(" ")
                              + std::string(" +Im1=") + QUOTE((*aSetIm)[aKIm]) + std::string(" ")
                              + std::string(" +Ori=-") + AeroIn
                              + std::string(" +ImSec=-") + ImSec
                              + " +DoPly=" + ToString(DoPly) + " "
                              + " +DoMatch=" + ToString(DoMatch) + " "
                    ;

          if (ExportEnv)
              aCom = aCom + " +ExportEnv=true";

          if (Visu)
              aCom = aCom + " +Visu=" + ToString(Visu) + " ";

          if (EAMIsInit(&aZoom))
             aCom = aCom + " +Zoom=" + ToString(aZoom) + " ";

          if (EAMIsInit(&aDo2Z))
             aCom = aCom + " +Do2Z=" + ToString(aDo2Z) + " ";

          if (EAMIsInit(&aReducePly))
             aCom = aCom + " +ReduceExp=" + ToString(aReducePly) + " ";
          if (EAMIsInit(&aMasq3D))
             aCom = aCom + " +UseMasq3D=true +FileMasq3D=" + aMasq3D + " ";
          std::cout << "Com = " << aCom << "\n";
          aLCom.push_back(aCom);
  }

  cEl_GPAO::DoComInParal(aLCom,"MkMMInit");
 // int aRes = system_call(aCom.c_str());


   return 0;
}





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
