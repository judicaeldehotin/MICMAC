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


/**
 * Zlimit: crop a MNT in depth
 * */

//
//----------------------------------------------------------------------------

int Zlimit_main(int argc,char ** argv)
{
    std::string aNameOriMNT;
    double aMaxZ,aMinZ;
    
    cout<<"Zlimit: create masq for depth image."<<endl;
    ElInitArgMain
    (
    argc,argv,
    //mandatory arguments
    LArgMain()  << EAMC(aNameOriMNT, "MNT xml file name", eSAM_IsExistFile)
                << EAMC(aMinZ, "Min Z (m)")
                << EAMC(aMaxZ, "Max Z (m)"),
    //optional arguments
    LArgMain()  //<< EAM(aAutoMaskImageName,"AutoMask",true,"AutoMask filename", eSAM_IsExistFile)
    );

    if (MMVisualMode) return EXIT_SUCCESS;
    
    ELISE_ASSERT(aMinZ<aMaxZ,"Please try with MinZ<MaxZ...");
    
    string aMasqTifName=aNameOriMNT+"_MasqZminmax.tif";
    string aMasqXmlName=aNameOriMNT+"_MasqZminmax.xml";
    
    cFileOriMnt aOriMnt = StdGetFromPCP(aNameOriMNT,FileOriMnt);
    cout<<aOriMnt.OriginePlani()<<" "<<aOriMnt.ResolutionPlani()<<endl;

    string aNameFileMnt=aOriMnt.NameFileMnt();
    string aNameFileMasque="";
    
    if (aOriMnt.NameFileMasque().IsInit())
        aNameFileMasque=aOriMnt.NameFileMasque().Val();
    double aOrigineAlti=aOriMnt.OrigineAlti();
    double aResolutionAlti=aOriMnt.ResolutionAlti();
    cout<<"z: *"<<aResolutionAlti<<" +"<<aOrigineAlti<<endl;
    cout<<"MinZ: "<<aMinZ<<"    MaxZ:"<<aMaxZ<<endl;
    
    Tiff_Im aFileMnt(aNameFileMnt.c_str());
    TIm2D<U_INT1,INT4> tmpImage1T(aOriMnt.NombrePixels());//image for max
    Im2D<U_INT1,INT4>  tmpImage1(tmpImage1T._the_im);
    TIm2D<U_INT1,INT4> tmpImage2T(aOriMnt.NombrePixels());//image for min
    Im2D<U_INT1,INT4>  tmpImage2(tmpImage2T._the_im);

    TIm2D<U_INT1,INT4> masqImageT(aOriMnt.NombrePixels());//image for masq
    Im2D<U_INT1,INT4>  masqImage(masqImageT._the_im);

    ELISE_COPY(tmpImage1.all_pts(),((1/(aFileMnt.in()*aResolutionAlti+aOrigineAlti))<aMaxZ),tmpImage1.out());
    ELISE_COPY(tmpImage2.all_pts(),((1/(aFileMnt.in()*aResolutionAlti+aOrigineAlti))>aMinZ),tmpImage2.out());
    ELISE_COPY(masqImage.all_pts(),(tmpImage1.in()*tmpImage2.in())*255,masqImage.out());
    Tiff_Im::CreateFromIm(masqImage,aMasqTifName);

    //for debug
    /*ELISE_COPY(tmpImage1.all_pts(),((1/(aFileMnt.in()*aResolutionAlti+aOrigineAlti))<aMaxZ)*255,tmpImage1.out());
    ELISE_COPY(tmpImage2.all_pts(),((1/(aFileMnt.in()*aResolutionAlti+aOrigineAlti))>aMinZ)*255,tmpImage2.out());
    Tiff_Im::CreateFromIm(tmpImage1,"tmp1.tif");
    Tiff_Im::CreateFromIm(tmpImage2,"tmp2.tif");*/

    
    cFileOriMnt anOriMasq;
    anOriMasq.NameFileMnt() = aMasqTifName;
    anOriMasq.NombrePixels() = aOriMnt.NombrePixels();
    anOriMasq.OriginePlani() = Pt2dr(0,0);
    anOriMasq.ResolutionPlani() = Pt2dr(1.0,1.0);
    anOriMasq.OrigineAlti() = 0.0;
    anOriMasq.ResolutionAlti() = 1.0;
    anOriMasq.Geometrie() = eGeomMNTFaisceauIm1PrCh_Px1D;
    MakeFileXML(anOriMasq,aMasqXmlName);
    
    cout<<"New masq created: "<<aMasqTifName<<endl;
    
    //for debug
    /*TIm2D<REAL4,REAL8> mDepthImageT(aFileMnt.sz());
    Im2D<REAL4,REAL8>  mDepthImage(mDepthImageT._the_im);
    ELISE_COPY(mDepthImage.all_pts(),aFileMnt.in(),mDepthImage.out());
    double min=5000;
    double max=-5000;
    double val;
    for (int anY=0 ; anY<mDepthImage.sz().y ; anY++)
    {
        for (int anX=0 ; anX<mDepthImage.sz().x ; anX++)
        {
            Pt2di aP(anX,anY);
            val=1/(mDepthImageT.get(aP)*aResolutionAlti+aOrigineAlti);
            //cout<<val<<" ";
            if (val<min) min=val;
            if (val>max) max=val;
        }
        //cout<<endl;
    }
    cout<<"min: "<<min<<"   max: "<<max<<endl;*/
    
    
    /*ELISE_COPY(tmpImage2.all_pts(),(1/(aFileMnt.in()*aResolutionAlti+aOrigineAlti)),tmpImage2.out());
    Tiff_Im::CreateFromIm(tmpImage2,"out.tif");*/


    return EXIT_SUCCESS;
}

/* Footer-MicMac-eLiSe-25/06/2007

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
Footer-MicMac-eLiSe-25/06/2007/*/
