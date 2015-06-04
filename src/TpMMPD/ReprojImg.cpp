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
 * ReprojImg: reprojects an image into geometry of another
 * Inputs:
 *  - Ori of all images
 *  - correlation directory with reference image DEM
 *  - reference image name
 *  - name of image to reproject
 *
 * Output:
 *  - image reprojected into reference orientation
 *
 * */

//color value class
class cReprojColor
{
  public:
    cReprojColor(U_INT1 r,U_INT1 g,U_INT1 b):mR(r),mG(g),mB(b){}
    void setR(U_INT1 r){mR=r;}
    void setG(U_INT1 g){mG=g;}
    void setB(U_INT1 b){mB=b;}
    U_INT1 r(){return mR;}
    U_INT1 g(){return mG;}
    U_INT1 b(){return mB;}
  protected:
    U_INT1 mR;
    U_INT1 mG;
    U_INT1 mB;
};

//----------------------------------------------------------------------------

//Color image
//TODO: use std::vector<Im2DGen *>  aV = aFTmp.ReadVecOfIm();
class cReprojColorImg
{
  public:
    cReprojColorImg(std::string filename);
    cReprojColorImg(Pt2di sz);
    ~cReprojColorImg();
    cReprojColor get(Pt2di pt);
    cReprojColor getr(Pt2dr pt);
    void set(Pt2di pt, cReprojColor color);
    void write(std::string filename);
    Pt2di sz(){return mImgSz;}
  protected:
    std::string mImgName;
    Pt2di mImgSz;
    Im2D<U_INT1,INT4> *mImgR;
    Im2D<U_INT1,INT4> *mImgG;
    Im2D<U_INT1,INT4> *mImgB;
    TIm2D<U_INT1,INT4> *mImgRT;
    TIm2D<U_INT1,INT4> *mImgGT;
    TIm2D<U_INT1,INT4> *mImgBT;
};

cReprojColorImg::cReprojColorImg(std::string filename) :
  mImgName(filename)
{
    Tiff_Im mTiffImg(mImgName.c_str());
    mImgSz.x=mTiffImg.sz().x;
    mImgSz.y=mTiffImg.sz().y;
    mImgR=new Im2D<U_INT1,INT4>(mImgSz.x,mImgSz.y);
    mImgG=new Im2D<U_INT1,INT4>(mImgSz.x,mImgSz.y);
    mImgB=new Im2D<U_INT1,INT4>(mImgSz.x,mImgSz.y);
    mImgRT=new TIm2D<U_INT1,INT4>(*mImgR);
    mImgGT=new TIm2D<U_INT1,INT4>(*mImgG);
    mImgBT=new TIm2D<U_INT1,INT4>(*mImgB);
    ELISE_COPY(mImgR->all_pts(),mTiffImg.in(),Virgule(mImgR->out(),mImgG->out(),mImgB->out()));
}


cReprojColorImg::cReprojColorImg(Pt2di sz) :
  mImgName(""),
  mImgSz(sz)
{
    mImgR=new Im2D<U_INT1,INT4>(mImgSz.x,mImgSz.y);
    mImgG=new Im2D<U_INT1,INT4>(mImgSz.x,mImgSz.y);
    mImgB=new Im2D<U_INT1,INT4>(mImgSz.x,mImgSz.y);
    mImgRT=new TIm2D<U_INT1,INT4>(*mImgR);
    mImgGT=new TIm2D<U_INT1,INT4>(*mImgG);
    mImgBT=new TIm2D<U_INT1,INT4>(*mImgB);
}

cReprojColorImg::~cReprojColorImg()
{
    delete mImgR;
    delete mImgG;
    delete mImgB;
    delete mImgRT;
    delete mImgGT;
    delete mImgBT;
}

cReprojColor cReprojColorImg::get(Pt2di pt)
{
    return cReprojColor(mImgRT->get(pt),mImgGT->get(pt),mImgBT->get(pt));
}

cReprojColor cReprojColorImg::getr(Pt2dr pt)
{
    return cReprojColor(mImgRT->getr(pt),mImgGT->getr(pt),mImgBT->getr(pt));
}

void cReprojColorImg::set(Pt2di pt, cReprojColor color)
{
    U_INT1 ** aImRData=mImgR->data();
    U_INT1 ** aImGData=mImgG->data();
    U_INT1 ** aImBData=mImgB->data();
    aImRData[pt.y][pt.x]=color.r();
    aImGData[pt.y][pt.x]=color.g();
    aImBData[pt.y][pt.x]=color.b();
}


void cReprojColorImg::write(std::string filename)
{
    ELISE_COPY
    (
        mImgR->all_pts(),
        Virgule( mImgR->in(), mImgG->in(), mImgB->in()) ,
        Tiff_Im(
            filename.c_str(),
            mImgSz,
            GenIm::u_int1,
            Tiff_Im::No_Compr,
            Tiff_Im::RGB,
            Tiff_Im::Empty_ARG ).out()
    );

/*    ELISE_COPY
    (
        mChannels[0]->all_pts(),
        Virgule( mChannels[0]->in(), mChannels[1]->in(), mChannels[2]->in()) ,
        Tiff_Im(
            i_filename.c_str(),
            Pt2di( mWidth, mHeight ),
            GenIm::u_int1,
            Tiff_Im::No_Compr,
            colorSpace,
            Tiff_Im::Empty_ARG ).out()
    );*/
}


//----------------------------------------------------------------------------

// RefImage class
class cRefImReprojImg
{
  public:
    cRefImReprojImg
    (
      std::string aOriIn,std::string aDepthRefImageName,
      std::string aNameRefImage,
      std::string * aAutoMaskImageName,
      cInterfChantierNameManipulateur * aICNM
    );
    Pt2di getSize(){return mRefImgSz;}
    TIm2D<U_INT1,INT4> * getAutoMask(){return & mAutoMaskImageT;}
    TIm2D<REAL4,REAL8> * getDepth(){return & mDepthImageT;}
    CamStenope         * getCam(){return mCamRef;}
  protected:
    std::string        mNameRefImage;//reference image name
    std::string        mDepthRefImageName;//reference image DEM file name
    std::string        mAutoMaskImageName; //automask image filename
    CamStenope         * mCamRef;
    std::string        mNameRefImageTif;
    Tiff_Im            mRefTiffIm;
    Pt2di              mRefImgSz;
    TIm2D<REAL4,REAL8> mDepthImageT;
    Im2D<REAL4,REAL8>  mDepthImage;
    TIm2D<U_INT1,INT4> mAutoMaskImageT;
    Im2D<U_INT1,INT4>  mAutoMaskImage;
};


cRefImReprojImg::cRefImReprojImg
      ( std::string aOriIn,std::string aDepthRefImageName,
        std::string aNameRefImage,
        std::string * aAutoMaskImageName,
        cInterfChantierNameManipulateur * aICNM):
  mNameRefImage     (aNameRefImage),
  mDepthRefImageName(aDepthRefImageName),
  mAutoMaskImageName(*aAutoMaskImageName),
  mNameRefImageTif  (NameFileStd(mNameRefImage,3,false,true,true,true)),
  mRefTiffIm        (mNameRefImageTif.c_str()),
  mRefImgSz         (mRefTiffIm.sz()),
  mDepthImageT      (mRefImgSz),
  mDepthImage       (mDepthImageT._the_im),
  mAutoMaskImageT   (mRefImgSz),
  mAutoMaskImage    (mAutoMaskImageT._the_im)
{
  std::string aOriRef=aOriIn+"Orientation-"+mNameRefImage+".xml";
  mCamRef=CamOrientGenFromFile(aOriRef,aICNM);

  std::cout<<"DepthRefImageName: "<<mDepthRefImageName<<std::endl;
  Tiff_Im aRefDepthTiffIm(mDepthRefImageName.c_str());
  Pt2di aRefDepthImgSz=aRefDepthTiffIm.sz();
  ELISE_ASSERT(mRefImgSz==aRefDepthImgSz,"Depth image is not at DeZoom 1!");
  std::cout<<"mRefTiffIm.nb_chan(): "<<mRefTiffIm.nb_chan()<<std::endl;

  ELISE_COPY(mDepthImage.all_pts(),aRefDepthTiffIm.in(),mDepthImage.out());

  //automask part
  if (EAMIsInit(aAutoMaskImageName))
  {
    std::cout<<"AutoMaskImageName: "<<mAutoMaskImageName<<std::endl;
    Tiff_Im aAutoMaskTiffIm(mAutoMaskImageName.c_str());
    Pt2di aAutoMaskImgSz=aAutoMaskTiffIm.sz();
    ELISE_ASSERT(mRefImgSz==aAutoMaskImgSz,"AutoMask image is not at DeZoom 1!");
    ELISE_COPY(mAutoMaskImage.all_pts(),aAutoMaskTiffIm.in(),mAutoMaskImage.out());
  }else{
    //if no automask given, suppose it's all white
    std::cout<<"No AutoMask"<<std::endl;
    ELISE_COPY(mAutoMaskImage.all_pts(),1,mAutoMaskImage.out());
  }


}

//----------------------------------------------------------------------------

int ReprojImg_main(int argc,char ** argv)
{
    std::string aOriIn;//Orientation containing all images and calibrations
    std::string aNameRefImage;//reference image name
    std::string aNameRepImage;//name of image to reproject
    std::string aDepthRefImageName;//reference image DEM file name
    std::string aAutoMaskImageName; //automask image filename

    ElInitArgMain
    (
    argc,argv,
    //mandatory arguments
    LArgMain()  << EAMC(aOriIn, "Directory of input orientation",  eSAM_IsExistDirOri)
                << EAMC(aDepthRefImageName, "Reference DEM filename", eSAM_IsExistFile)
                << EAMC(aNameRefImage, "Reference image name",  eSAM_IsExistFile)
                << EAMC(aNameRepImage, "Name of image to reproject",  eSAM_IsExistFile),
    //optional arguments
    LArgMain()  << EAM(aAutoMaskImageName,"AutoMask",true,"AutoMask filename", eSAM_IsExistFile)
    );

    if (MMVisualMode) return EXIT_SUCCESS;

    MakeFileDirCompl(aOriIn);
    std::cout<<"OrinIn dir: "<<aOriIn<<std::endl;
    //get orientation file name
    std::string aOriRep=aOriIn+"Orientation-"+aNameRepImage+".xml";

    // Initialize name manipulator & files
    std::string aDir;
    std::string aRefImgTmpName;
    SplitDirAndFile(aDir,aRefImgTmpName,aNameRefImage);
    std::cout<<"Working dir: "<<aDir<<std::endl;
    std::cout<<"RefImgTmpName: "<<aRefImgTmpName<<std::endl;

    cInterfChantierNameManipulateur * aICNM=cInterfChantierNameManipulateur::BasicAlloc(aDir);

    cRefImReprojImg aRefIm(aOriIn,aDepthRefImageName,aNameRefImage,&aAutoMaskImageName,aICNM);

    CamStenope * aCamRep=CamOrientGenFromFile(aOriRep,aICNM);

    std::string aNameRepImageTif = NameFileStd(aNameRepImage,3,false,true,true,true);
    cReprojColorImg aRepIm(aNameRepImageTif.c_str());
    Pt2di aRepImgSz=aRepIm.sz();

    //Output image
    cReprojColorImg aOutputIm(aRefIm.getSize());

    //Mask of reprojected image
    Im2D_U_INT1 aMaskRepIm(aRefIm.getSize().x,aRefIm.getSize().y);
    //access to each pixel value
    U_INT1 ** aMaskRepImData=aMaskRepIm.data();

    cReprojColor black(0,0,0);
    //for each pixel of reference image,
     for (int anY=0 ; anY<aRefIm.getSize().y ; anY++)
     {
         for (int anX=0 ; anX<aRefIm.getSize().x ; anX++)
         {
              //create 2D point in Ref image
              Pt2di aPImRef(anX,anY);

              //check if depth exists
              if (aRefIm.getAutoMask()->get(aPImRef)!=1)
              {
                aOutputIm.set(aPImRef,black);
                aMaskRepImData[anY][anX]=0;
                continue;
              }

              //get depth in aRefDepthTiffIm
              float aProf=1/aRefIm.getDepth()->get(aPImRef);
              //get 3D point
              Pt3dr aPGround=aRefIm.getCam()->ImEtProf2Terrain((Pt2dr)aPImRef,aProf);
              //project 3D point into Rep image
              Pt2dr aPImRep=aCamRep->R3toF2(aPGround);
              //check that aPImRep is in Rep image

              //debug
              /*if ((anX==2115)&&(anY==912))
              {
                std::cout<<"For pixel ("<<anX<<" "<<anY<<"): z="<<aProf<<std::endl;
                std::cout<<"Reprojection is ("<<aPImRep.x<<" "<<aPImRep.y<<")"<<std::endl;
              }*/

              //TODO: create output mask?
              if ((aPImRep.x<0) ||(aPImRep.x>=aRepImgSz.x-1) ||(aPImRep.y<0) ||(aPImRep.y>=aRepImgSz.y-1))
              {
                aOutputIm.set(aPImRef,black);
                aMaskRepImData[anY][anX]=0;
                continue;
              }

              //get color of this point in Rep image
              cReprojColor color=aRepIm.getr(aPImRep);
              //copy this color into output image
              aOutputIm.set(aPImRef,color);
              aMaskRepImData[anY][anX]=255;
         }
     }

    std::cout<<"Write reproj image..."<<std::endl;
    aOutputIm.write(aNameRefImage+"_"+aNameRepImage+".tif");
    Tiff_Im::CreateFromIm(aMaskRepIm,aNameRefImage+"_"+aNameRepImage+"_mask.tif");//TODO: make a xml file? convert to indexed colors?
    //TODO: create image difference!
    //use MM2D for image analysis

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
