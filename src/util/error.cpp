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

int TheIntFuckingReturnValue=1234567;
char * TheCharPtrFuckingReturnValue=0;

bool TheExitOnBrkp = false;

int GetCharOnBrkp()
{
   if (TheExitOnBrkp)
      return 0;
   return getchar();
}

void EliseBRKP()
{
    if (!TheExitOnBrkp)
       getchar();
}


bool ELISE_DEBUG_USER = true;
bool ELISE_DEBUG_INTERNAL = false;

void elise_error_exit()
{
    message_copy_where_error();
    for (int k=0; k<10; k++) EliseBRKP();
    exit (1);
}

void elise_internal_error(const char * mes,const char * file,int line)
{
    for (int i = 0; i < 3 ; i++)
        ncout() <<  "INTERNAL ERROR IN ELISE !!!\n";
    ncout() << "\n\n The following error :\n";
    ncout() << "    " << mes << "\n";
    ncout() << "occured at line " << line << " of file " << file  << "\n";
 
    ncout()  << "please sent a bug report \n";

    elise_error_exit();
}


void  elise_test_error(const char * mes,const char * file,int line)
{
    ncout() << "KEEP COOL , everything is under control \n";
    ncout() << "        this is a test-fatal error \n";
    ncout() << "The following error : \n";
    ncout() << "    " << mes ;
    ncout() << "was to occur at line " << line << " of file " << file << "\n";

}



void cEliseFatalErrorHandler::SetCurHandler(cEliseFatalErrorHandler * aH)
{
    CurHandler(aH);
}

cEliseFatalErrorHandler * cEliseFatalErrorHandler::CurHandler()
{ 
    return CurHandler(0);
}


cEliseFatalErrorHandler * cEliseFatalErrorHandler::CurHandler(cEliseFatalErrorHandler * aH)
{
   static cEliseFatalErrorHandler * aRes = 0;
   if ((aH==0) && (aRes==0))
      aRes = new cEliseFatalErrorHandler;
    else
      aRes = aH;
   return aRes;
}


void cEliseFatalErrorHandler::cEFEH_OnErreur(const char * mes,const char * file,int line)
{
    ShowArgs();
    ncout() << "--------------------------------------------------\n"
         << "|   the following FATAL ERROR happened (sorry)    \n"
         << "|                                                 \n"
         << "|    " << mes  <<                                "\n"
         << "|                                                 \n";

    message_copy_where_error();

     ncout()    << "--------------------------------------------------------\n"
             << "|       (Elise's)  LOCATION :                           \n"
             << "|                                                       \n"
             << "| Error  was detected \n"
             << "|          at line : " << line  << "\n"
             << "|          of file : " << file  << "\n"
             << "--------------------------------------------------------\n";


    ncout() << "Bye  (tape enter)\n";

    EliseBRKP();
    exit (1);
}

void  elise_fatal_error(const char * mes,const char * file,int line)
{
   cEliseFatalErrorHandler::CurHandler()->cEFEH_OnErreur(mes,file,line);
}

/*****************************************************************/
/*****************************************************************/
/*****************************************************************/
/*****************************************************************/



void ElEM::mes_el() const
{
    switch(_type)
    {
        case _int    : ncout() << _data.i     ; break;
        case _real   : ncout() << _data.r     ; break;
        case _string : ncout() << _data.s     ; break;
        case _pt_pck :  _data.pack->show_kth(_data_2.i); 
                        break;
        case _tab_int : 
		{
              ncout() << "[";

              for (INT i  = 0 ; i <_data_2.i; i++)
              {
                  if (i) ncout() <<  " x ";
                  ncout() << _data.Pi[i];   
              }

              ncout() << "]";
		}
        break;

        case _tab_real : 
		{
              ncout() << "[";

              for (INT i  = 0 ; i <_data_2.i; i++)
              {
                  if (i) ncout() <<  " x ";
                  ncout() << _data.Pr[i];   
              }

              ncout() << "]";
		}
        break;

        case _pt2di :
             ncout() << "(" << _data.pt->x << "," << _data.pt->x << ")";
             break;

        case _box_2di :
             const  Box2di * box = _data.box;
             ncout() << "[" << box->_p0.x << "," << box->_p1.x << "]"
                  << "X"
                  << "[" << box->_p0.y << "," << box->_p1.y << "]";
             break;
    };
}

Elise_Pile_Mess_N::Elise_Pile_Mess_N() {}

Elise_Pile_Mess_N Elise_Pile_Mess_N::_the_one;

void Elise_Pile_Mess_0::display(const char * kind_of)
{
    ShowArgs();

    ncout() << "--------------------------------------------------\n"
         << "|   KIND OF ERR : " << kind_of <<                "\n"
         << "|   Sorry, the following FATAL ERROR happened     \n"
         << "|                                                 \n";
    ncout() << "|    "; 
    for (INT i=0 ; i<_nb ; i++)
    {
         _stack[i].mes_el();
    }
    ncout() << "\n";
    ncout() << "|                                                 \n"
         << "--------------------------------------------------\n";

    message_copy_where_error();
    ncout() << "Bye  (tape enter to quit)\n";

    EliseBRKP();
    exit (1);
}

INT Elise_Pile_Mess_0::_nb = 0;
ElEM Elise_Pile_Mess_0::_stack[100];



Elise_Pile_Mess_0 EEM0;


Elise_Assertion::Elise_Assertion(const char * kind_of) :
     _active (true),
     _kind_of (kind_of)
{
}


Elise_Assertion Tjs_El_User("User's error");
Elise_Assertion El_User_Dyn("User's  dynamic error");

Elise_Assertion El_Internal("Elise's internal error");


void Elise_Assertion::unactive_user()
{
    ELISE_DEBUG_USER = false;
    El_User_Dyn._active = false;
}



/********************  WARNS  *********************/

cElWarning cElWarning::BehindCam("Point behind camera after initialisation");
cElWarning cElWarning::FocInxifAndMM("Focal legnth specified both by xif and NKS-Assoc-STD-FOC");
cElWarning cElWarning::CamInxifAndMM("Camera name specified both by xif and NKS-Assoc-STD-FOC");
cElWarning  cElWarning::GeomIncompAdaptF2Or("Geometrie incompatible Cible/Xml, AdaptFoncFileOriMnt");
cElWarning cElWarning::GeomPointTooManyMeasured("Too many measuremnt, excess will be ignored");
cElWarning cElWarning::ToVerifNuage("The point verification point in nuage where not coherents");


cElWarning cElWarning::OrhoLocOnlyXCste("For now RedrLocAnam only workx with X=Cst Anamorphose");


int cElWarning::mNbTot = 0;

std::vector<cElWarning *> cElWarning::mWarns;


cElWarning::cElWarning(const std::string & aName) :
   mName    (aName),
   mNbWarns (0)
{
}


void cElWarning::AddWarn
     (
         const std::string &  aMes,
         int                  aLine,
         const std::string &  aFile
     )
{
   if (mNbWarns == 0)
   {
      mWarns.push_back(this);
      mMes = aMes;
      mLine = aLine;
      mFile = aFile;
   }
   mNbWarns ++;
   mNbTot++;
}


void cElWarning::ShowOneWarn(FILE  * aFP)
{
    fprintf(aFP,"%d occurence of warn type [%s]\n",mNbWarns,mName.c_str());
    fprintf(aFP,"First context  message : %s\n",mMes.c_str());
    fprintf(aFP,"First detected at line  :  %d of File %s\n",mLine,mFile.c_str());
}

void cElWarning::ShowWarns(const std::string & aFile)
{
   if (mNbTot == 0)
      return;

   std::cout << "\n\n";
   std::cout << "*** There were " << mNbTot << " warnings of " << mWarns.size() << " different type \n";
   std::cout << "***  See "  << aFile << " for all warnd descritption \n";
   std::cout << "***  First warn occured \n\n";
   mWarns[0]->ShowOneWarn(stdout);

   FILE * aFP= FopenNN(aFile.c_str(),"w","Warning file");

   for (int aK=0 ; aK<int(mWarns.size()) ; aK++)
   {
        fprintf(aFP,"=================================================================\n");
        mWarns[aK]->ShowOneWarn(aFP);
   }

   ElFclose(aFP);
   
}



// mWarns.push_back(this);




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
