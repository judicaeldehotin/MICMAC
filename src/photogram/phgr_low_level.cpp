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

// Classe generique , a rebalancer dans la future BB 
// d'optimisation generale

#include <vector>

class RacineFonc1D
{
     public :

         void solutions_1prof
              (
                  ElSTDNS vector<REAL> &,
                  ElSTDNS vector<REAL> &,
                  REAL x0,
                  REAL x1,
                  INT  nb_step
                  
              );
  virtual ~RacineFonc1D() {}
     private :

         virtual REAL ValRF1D(REAL x,bool & def) =0;
        
};


void RacineFonc1D::solutions_1prof
     (
         ElSTDNS vector<REAL> & bsup,
         ElSTDNS vector<REAL> & binf,
         REAL X0,
         REAL X1,
         INT  nb_step
     )
{
    bsup.clear();
    binf.clear();

    bool ok0 = true;
    REAL x0 = X0;
    REAL v0 = ValRF1D(x0,ok0);
    for (INT k=1 ; k <= nb_step ; k++)
    {
         bool ok1 = true;
         REAL x1 = (k*X1 + (nb_step-k) *X0) / nb_step;
         REAL v1 = ValRF1D(x1,ok1);

         if (ok0 && ok1 && ((v0>0) != (v1>0)))
         {
            binf.push_back(x0);
            bsup.push_back(x1);
         }
         ok0 = ok1;
         x0 =  x1;
         v0 =  v1;
    }
}


class  ResProfChamp 
{
     public :
        ResProfChamp(REAL DistBC,Pt3dr pa,Pt3dr pb,Pt3dr pc,REAL rhoA,REAL rhoC);


        void ListeC(ElSTDNS list<Pt3dr>&  res);

     private :

        bool OkSolC(REAL c);

        REAL BfromC(REAL c,bool & OK);
        // virtual REAL ValRF1D(REAL x,bool & def);

        REAL   _DistBC;
        Pt3dr  _PA;
        Pt3dr  _PB;
        Pt3dr  _PC;

        REAL   _A2;
        REAL   _B2;
        REAL   mC2;
        REAL   _AB;
        REAL   _AC;
        REAL   _BC;

        REAL   _rhoA;
        REAL   _rhoC;

        REAL   _g;
        REAL   _gam0;
        REAL   _gam1;
        REAL   _gam2;
        ElPolynome<REAL> _Gamma;

        REAL             _omega0;
        REAL             _omega1;
        REAL             _omega2;
        ElPolynome<REAL> _Omega;
        ElPolynome<REAL> _Alpha;
        ElPolynome<REAL> _Resolv;
        ElSTDNS vector<REAL>     mRoots;

        INT    _signdisc;
};

ResProfChamp::ResProfChamp
(
     REAL  DistBC,
     Pt3dr pa,
     Pt3dr pb,
     Pt3dr pc,
     REAL rhoA,
     REAL rhoC
)  :
   _DistBC      (DistBC),
   _PA          (pa),
   _PB          (pb),
   _PC          (pc),
   _A2          (square_euclid(pa)),
   _B2          (square_euclid(pb)),
   mC2          (square_euclid(pc)),
   _AB          (scal(pa,pb)),
   _AC          (scal(pa,pc)),
   _BC          (scal(pb,pc)),

   _rhoA        (rhoA),
   _rhoC        (rhoC),

   _g           (_AB/_B2),
   _gam0        (ElSquare(_AB/_B2)+(_rhoA-1)*(_A2/_B2)),
   _gam1        (-2*_rhoA * (_AC/_B2)),
   _gam2        (_rhoA * mC2 /_B2),
   _Gamma       (_gam0,_gam1,_gam2),

   _omega0      (_rhoC*_A2 -_g*_g*_B2 -_B2*_gam0),
   _omega1      (2*(_g*_BC-_rhoC*_AC)-_B2*_gam1),
   _omega2      ((_rhoC-1)*mC2 -_B2*_gam2),
   _Omega       (_omega0,_omega1,_omega2),

   _Alpha       (_B2*_g,-_BC),
   _Resolv      (_Omega *_Omega -_Gamma*_Alpha*_Alpha *4.0),

   _signdisc    (1)
{
}



REAL ResProfChamp::BfromC(REAL c,bool & OK)
{
     REAL Gamma = _Gamma(c);


     OK = (Gamma >=0);
     if (! OK) 
        return 1e60;

     return _g + _signdisc * sqrt(Gamma);
}

bool ResProfChamp::OkSolC(REAL c)
{
     REAL Gamma = _Gamma(c);


     if (Gamma <0)
        return false;

     if (ElAbs(_Omega(c) - 2 * _signdisc * sqrt(Gamma) * (_B2*_g -_BC*c))> 1e-4)
        return false;

     return true;
}


void ResProfChamp::ListeC(ElSTDNS list<Pt3dr>&  res)
{
     res.clear();

     RealRootsOfRealPolynome(mRoots,_Resolv,1e-10,100);

     for (_signdisc =-1; _signdisc <=1 ; _signdisc+=2)
     {
         for (INT k=0; k<(INT) mRoots.size(); k++) 
         {
            REAL c = mRoots[k];
            if (OkSolC(c))
            {
               bool OK;
               REAL b = BfromC(c,OK);
               ELISE_ASSERT(OK,"Incoh in ResProfChamp::ListeC");

               REAL RatA =   square_euclid(_PA-_PB*b)
                           / square_euclid(_PA-_PC*c);
               REAL RatC =   square_euclid(_PB*b-_PC*c)
                           / square_euclid(_PA-_PC*c);
               if ( 
                        (ElAbs(RatA-_rhoA) < 1e-4)
                    &&  (ElAbs(RatC-_rhoC) < 1e-4)
                  )
               {
                   REAL ratio = _DistBC / euclid(_PB*b-_PC*c);
                   res.push_back(Pt3dr(1,b,c)*ratio);
               }
            }
         }
     }
}


Pt3dr   ElPhotogram::PProj(Pt2dr p)
{
    return Pt3dr(p.x,p.y,1);
}


void ElPhotogram::ProfChampsFromDist
     (
                 ElSTDNS list<Pt3dr>&  res,  // liste de triplets de prof de champs
                 Pt3dr A,Pt3dr B,Pt3dr C, // points de projection
                 REAL dAB, REAL dAC, REAL dBC
     )
{
    ResProfChamp  RPC(dBC,A,B,C,ElSquare(dAB/dAC),ElSquare(dBC/dAC));
    RPC.ListeC(res);
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
