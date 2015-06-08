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

/******************************/
/*	   Author: Luc Girod	  */
/******************************/

#include "StdAfx.h"
#include <algorithm>

void Prep4masq_Banniere()
{
    std::cout << "\n*************************************************\n";
    std::cout << "  **                                             **\n";
    std::cout << "  **                   Prep                      **\n";
    std::cout << "  **                     4                       **\n";
    std::cout << "  **                   Masq                      **\n";
    std::cout << "  **                                             **\n";
    std::cout << "  *************************************************\n";
}



int Prep4masq_main(int argc,char ** argv)
{
    std::string aFullPattern;
      //Reading the arguments
        ElInitArgMain
        (
            argc,argv,
            LArgMain()  << EAMC(aFullPattern,"Full Directory (Dir+Pattern)", eSAM_IsPatFile),
            LArgMain()
        );

        if (MMVisualMode) return EXIT_SUCCESS;

        std::string aDir,aPatIm;
        SplitDirAndFile(aDir,aPatIm,aFullPattern);

        cInterfChantierNameManipulateur * aICNM = cInterfChantierNameManipulateur::BasicAlloc(aDir);
        const std::vector<std::string> * aSetIm = aICNM->Get(aPatIm);
        std::vector<std::string> aVectIm=*aSetIm;

        list<string> ListConvert;
        for(int i=0;i<int(aVectIm.size());i++){
            //to make the file to manualy modify
            string aNameMasq=StdPrefix(aVectIm[i]) + "_Masq.tif";
            string cmdconv=MMDir() + "binaire-aux/convert -colorspace gray +compress " + aVectIm[i] + " " + aNameMasq;
            ListConvert.push_back(cmdconv);

            //to read Size
            Tiff_Im aTF1= Tiff_Im::StdConvGen(aDir + aVectIm[i],1,false);
            Pt2di aSz = aTF1.sz();

            cout<<"--- Writing XML"<<endl;
            string NameXML=StdPrefix(aVectIm[i]) + "_Masq.xml";
            std::ofstream file_out(NameXML.c_str(), ios::out);
                if(file_out)  // if file successfully opened
                {
                    file_out <<"<FileOriMnt>" <<endl;
                             file_out <<"<NameFileMnt>./"<<aNameMasq<<"</NameFileMnt>"<<endl;
                             file_out <<"<NombrePixels>"<<aSz.x<<" "<<aSz.y<<"</NombrePixels>"<<endl;
                             file_out <<"<OriginePlani>0 0</OriginePlani>"<<endl;
                             file_out <<"<ResolutionPlani>1 1</ResolutionPlani>"<<endl;
                             file_out <<"<OrigineAlti>0</OrigineAlti>"<<endl;
                             file_out <<"<ResolutionAlti>1</ResolutionAlti>"<<endl;
                             file_out <<"<Geometrie>eGeomMNTFaisceauIm1PrCh_Px1D</Geometrie>"<<endl;
                    file_out << "</FileOriMnt>" <<endl<<endl;
                    file_out.close();
                }
                else{ cerr << "Couldn't write file" << endl;}
        }
        cEl_GPAO::DoComInParal(ListConvert,aDir + "MkMasqFile");

        return 1;
}


int CPP_SetExif(int argc,char **argv)
{
    std::string aPat,aCam;
    double aFoc,aF35;
    bool aPurge=true;

    ElInitArgMain
    (
        argc,argv,
        LArgMain()  << EAMC(aPat,"Pattern of images", eSAM_IsPatFile),
        LArgMain()  << EAM(aFoc,"F",true,"Focal lenght")
                    << EAM(aF35,"F35",true,"Focal lenght equiv 35mm")
                    << EAM(aCam,"Cam",true,"Camera model")
                    << EAM(aPurge,"Purge",true,"Purge created exiv2 command file (Def=true)")
    );
    if (MMVisualMode) return EXIT_SUCCESS;

    cElemAppliSetFile anEASF(aPat);

    std::string aNameFile =  Dir2Write(anEASF.mDir) + "ExivBatchFile.txt";
    FILE * aFP = FopenNN(aNameFile,"w","CPP_SetExif");

    int aMul=1000;

    if (EAMIsInit(&aFoc))
         fprintf(aFP,"set Exif.Photo.FocalLength  Rational  %d/%d\n",round_ni(aFoc*aMul),aMul);

   
    if (EAMIsInit(&aFoc))
         // fprintf(aFP,"set Exif.Photo.FocalLengthIn35mmFilm Short  %d\n",aF35);
         fprintf(aFP,"set Exif.Photo.FocalLengthIn35mmFilm Rational  %d/%d\n",round_ni(aF35*aMul),aMul);

    if (EAMIsInit(&aCam))
         fprintf(aFP,"set Exif.Image.Model  Ascii  \"%s\"\n",aCam.c_str());

    fclose(aFP);


    std::list<std::string> aLCom;
    const cInterfChantierNameManipulateur::tSet * aVIm = anEASF.SetIm();

    for (int aKIm=0 ; aKIm<int(aVIm->size()) ; aKIm++)
    {
        std::string aCom ="exiv2 -m " + aNameFile + " " + (*aVIm)[aKIm];
        // std::cout << aCom<< "\n";
        aLCom.push_back(aCom);
        System(aCom);
    }
    cEl_GPAO::DoComInParal(aLCom);


    if (aPurge)
       ELISE_fp::RmFileIfExist(aNameFile);


    return EXIT_SUCCESS;
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
