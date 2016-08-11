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

#ifndef _TiepGeo_H_
#define _TiepGeo_H_


#include "StdAfx.h"


class cLnk2ImTiepGeo;
class cImageTiepGeo;
//AAAAAclass cPMulTiepGeo;
class cAppliTiepGeo;

//class cImageGridGeo;

class cImageTiepGeo
{
    public:

        cImageTiepGeo(cAppliTiepGeo & aAppli, const std::string & aNameOri, std::string aNameIm="");
		
		const Box2dr & BoxSol() const;
		bool		   HasInter(const cImageTiepGeo & aIm2) const;
		double		   AltiSol() const;
		int			   AltiSolInc() const;
	
		const std::string & NameIm();
		const int & Num() const;
		void SetNum(int &aNum);


    private:
		cAppliTiepGeo & mAppli;

        CameraRPC * mCamRPC;
		int         mNum;

		std::string mNameIm;	
};

class cLnk2ImTiepGeo
{
    public:
        cLnk2ImTiepGeo(cImageTiepGeo *aIm1, cImageTiepGeo *aIm2, 
                       const std::string &aCorName, 
                       const std::string &aPx1Name, 
                       const std::string &aPx2Name);


		cImageTiepGeo & Im1();
		cImageTiepGeo & Im2();
		
    
	private:
        cImageTiepGeo * mIm1;
        cImageTiepGeo * mIm2;
        
        const std::string mCorName;
        const std::string mPx1Name;
        const std::string mPx2Name;

        //homologous points (consistent with tMergeStr)
		std::vector<Pt2df> mVP1; 
		std::vector<Pt2df> mVP2; 

};

class cAppliTiepGeo
{
    public:
        cAppliTiepGeo(int argc,char **argv);

        void Exe();

    private :
		void DoMaster();
        void DoPx1Px2();
        void DoTapioca();
		void DoStereo();
        
        const std::string  & Dir() const;
		const std::string    NamePxDir(const std::string & aIm1,const std::string & aIm2) const;


		void AddLnk(cLnk2ImTiepGeo *);


        Box2dr mGlobBox; //global footprint, necessary maybe later

		std::string									mMasterImStr;
		cImageTiepGeo *								mMasterIm;
		std::map<std::string,cImageTiepGeo *>		mMapIm;//not yet sure if necessary
		std::vector<cImageTiepGeo *>				mVIm;
        std::list<cLnk2ImTiepGeo *>					mLnk2Im;//not yet sure if necessary
        std::vector<std::vector<cLnk2ImTiepGeo *> > mVVLnk;
    
        double mCor;
        int mZoom0;
		int mNum;

        cInterfChantierNameManipulateur* mICNM;
        const std::vector<std::string> * mFilesIm;

        std::string  mPatImage;
        std::string  mOri;
        std::string  mDir;
};


#endif 

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
footer-MicMac-eLiSe-25/06/2007*/
