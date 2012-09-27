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
                                



/* Merci Numerical recipes (Press,Flannery,Teukolsky,Vetterling ...).
*/

#define ROTATE(a,i,j,k,l) g=a[i][j];h=a[k][l];a[i][j]=g-s*(h+g*tau);\
	a[k][l]=h+s*(g-h*tau);


/*************************************************************/
/*************************************************************/
/*************************************************************/
/*************************************************************/


INT NR_jacobi (REAL ** A ,INT n ,REAL *d ,REAL ** V)
{
	INT j,iq,ip,i;
	REAL tresh,theta,tau,t,sm,s,h,g,c;

	d--;

	static ElFilo<REAL *> a;  NR_InitNrMat(a,A,n);
	static ElFilo<REAL *> v;  NR_InitNrMat(v,V,n);

	static ElFilo<REAL> b;  NR_InitVect(b,n);
	static ElFilo<REAL> z;  NR_InitVect(z,n);

	for (ip=1;ip<=n;ip++) {
		for (iq=1;iq<=n;iq++) v[ip][iq]=0.0;
		v[ip][ip]=1.0;
	}
	for (ip=1;ip<=n;ip++) {
		b[ip]=d[ip]=a[ip][ip];
		z[ip]=0.0;
	}
	for (i=1;i<=50;i++) {
		sm=0.0;
		for (ip=1;ip<=n-1;ip++) {
			for (iq=ip+1;iq<=n;iq++)
				sm += fabs(a[ip][iq]);
		}
		if (sm == 0.0) {
			return(1);
		}
		if (i < 4)
			tresh=0.2*sm/(n*n);
		else
			tresh=0.0;
		for (ip=1;ip<=n-1;ip++) {
			for (iq=ip+1;iq<=n;iq++) {
				g=100.0*fabs(a[ip][iq]);
				if (i > 4 && fabs(d[ip])+g == fabs(d[ip])
					&& fabs(d[iq])+g == fabs(d[iq]))
					a[ip][iq]=0.0;
				else if (fabs(a[ip][iq]) > tresh) {
					h=d[iq]-d[ip];
					if (fabs(h)+g == fabs(h))
						t=(a[ip][iq])/h;
					else {
						theta=0.5*h/(a[ip][iq]);
						t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
						if (theta < 0.0) t = -t;
					}
					c=1.0/sqrt(1+t*t);
					s=t*c;
					tau=s/(1.0+c);
					h=t*a[ip][iq];
					z[ip] -= h;
					z[iq] += h;
					d[ip] -= h;
					d[iq] += h;
					a[ip][iq]=0.0;
					for (j=1;j<=ip-1;j++) {
						ROTATE(a,j,ip,j,iq)
					}
					for (j=ip+1;j<=iq-1;j++) {
						ROTATE(a,ip,j,j,iq)
					}
					for (j=iq+1;j<=n;j++) {
						ROTATE(a,ip,j,iq,j)
					}
					for (j=1;j<=n;j++) {
						ROTATE(v,j,ip,j,iq)
					}
				}
			}
		}
		for (ip=1;ip<=n;ip++) {
			b[ip] += z[ip];
			d[ip]=b[ip];
			z[ip]=0.0;
		}
	}
	return(0);
}

#undef ROTATE


static ElMatrix<REAL> * THEVP;

class cCmpTHEVP
{
    public :
       bool operator ()(const int & i1,const int & i2)
       {
            return (*THEVP)(i1,0) < (*THEVP)(i2,0);
       }
};

static cCmpTHEVP the_cCmpTHEVP;

std::vector<int> jacobi
     (
          const ElMatrix<REAL> &  aMat0,
          ElMatrix<REAL>  & aValP,
          ElMatrix<REAL> &  aVecP
     )
{
    ElMatrix<REAL>   aMatSym = aMat0;
    INT n = aMatSym.tx();
    ELISE_ASSERT(n==aMatSym.ty(),"Not Squre in jacobi");

    aVecP.set_to_size(n,n);
    aValP.set_to_size(n,1);
    NR_jacobi(aMatSym.data(),n,aValP.data()[0],aVecP.data());

    std::vector<int> aRes;
    for (int aK=0 ; aK<n ; aK++)
        aRes.push_back(aK);

    THEVP =  &aValP;
    std::sort(aRes.begin(),aRes.end(),the_cCmpTHEVP);

   return aRes;
}

void MatLigneToDiag
     (
         const  ElMatrix<REAL> & aLine,
	 ElMatrix<REAL> &        aDiag
     )
{
   ELISE_ASSERT(aLine.ty()==1,"Not a Line Matrix in MatLigneToDiag");
   INT n =  aLine.tx();
   aDiag.set_to_size(n,n);

   for (INT anX=0; anX<n ; anX++)
       for (INT anY=0; anY<n ; anY++)
           aDiag(anX,anY) = (anX==anY) ? aLine(anX,0) : 0;
}

std::vector<int> jacobi_diag
     (
          const ElMatrix<REAL> &  aMatSym,
          ElMatrix<REAL>  & aValP,
          ElMatrix<REAL> &  aVecP
     )
{
   ElMatrix<REAL> aLineVP(aMatSym.tx(),1);

   std::vector<int>  aRes = jacobi(aMatSym,aLineVP,aVecP);
    
   MatLigneToDiag(aLineVP,aValP);
   return aRes;
}

        


/*  #define PYTHAG(a,b) ((at=fabs(a)) > (bt=fabs(b)) ? \
  (ct=bt/at,at*sqrt(1.0+ct*ct)) : (bt ? (ct=at/bt,bt*sqrt(1.0+ct*ct)): 0.0))
*/

static inline double  PYTHAG(const double & a,const double & b)
{
   double at=ElAbs(a);
   double bt=ElAbs(b);
   
   if (at>bt)
   {
       double ct = bt/at;
       return at*sqrt(1.0+ElSquare(ct));
   }
   else
   {
       double ct = at/bt;
       return bt*sqrt(1.0+ElSquare(ct));
   }
   
}
// #define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
static double  SIGN(const double & a,const double & b) 
{
	return ((b)>=0.0 ? ElAbs(a) : -ElAbs(a));
}


void NR_svdcmp(double ** A,int m,int n,double * w,double ** V)
{
	int flag,i,its,j,jj,k,l=-1,nm=-1;
	double c,f,h,s,x,y,z;
	double anorm=0.0,g=0.0,scale=0.0;

	ELISE_ASSERT( (m == n),"SVDCMP: You must augment A with extra zero rows");
	w--;
	static ElFilo<REAL *> a; NR_InitNrMat(a,A,n); 
	static ElFilo<REAL *> v; NR_InitNrMat(v,V,n); 
	static ElFilo<REAL> rv1;  NR_InitVect(rv1,n);


	//  Dans NR, la condition etait, (m >= n)
	for (i=1;i<=n;i++) {
		l=i+1;
		rv1[i]=scale*g;
		g=s=scale=0.0;
		if (i <= m) {
			for (k=i;k<=m;k++) scale += fabs(a[k][i]);
			if (scale) {
				for (k=i;k<=m;k++) {
					a[k][i] /= scale;
					s += a[k][i]*a[k][i];
				}
				f=a[i][i];
				g = -SIGN(sqrt(s),f);
				h=f*g-s;
				a[i][i]=f-g;
				if (i != n) {
					for (j=l;j<=n;j++) {
						for (s=0.0,k=i;k<=m;k++) s += a[k][i]*a[k][j];
						f=s/h;
						for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
					}
				}
				for (k=i;k<=m;k++) a[k][i] *= scale;
			}
		}
		w[i]=scale*g;
		g=s=scale=0.0;
		if (i <= m && i != n) {
			for (k=l;k<=n;k++) scale += fabs(a[i][k]);
			if (scale) {
				for (k=l;k<=n;k++) {
					a[i][k] /= scale;
					s += a[i][k]*a[i][k];
				}
				f=a[i][l];
				g = -SIGN(sqrt(s),f);
				h=f*g-s;
				a[i][l]=f-g;
				for (k=l;k<=n;k++) rv1[k]=a[i][k]/h;
				if (i != m) {
					for (j=l;j<=m;j++) {
						for (s=0.0,k=l;k<=n;k++) s += a[j][k]*a[i][k];
						for (k=l;k<=n;k++) a[j][k] += s*rv1[k];
					}
				}
				for (k=l;k<=n;k++) a[i][k] *= scale;
			}
		}
		anorm=ElMax(anorm,(fabs(w[i])+fabs(rv1[i])));
	}
	for (i=n;i>=1;i--) {
		if (i < n) {
			if (g) {
				for (j=l;j<=n;j++)
					v[j][i]=(a[i][j]/a[i][l])/g;
				for (j=l;j<=n;j++) {
					for (s=0.0,k=l;k<=n;k++) s += a[i][k]*v[k][j];
					for (k=l;k<=n;k++) v[k][j] += s*v[k][i];
				}
			}
			for (j=l;j<=n;j++) v[i][j]=v[j][i]=0.0;
		}
		v[i][i]=1.0;
		g=rv1[i];
		l=i;
	}
	for (i=n;i>=1;i--) {
		l=i+1;
		g=w[i];
		if (i < n)
			for (j=l;j<=n;j++) a[i][j]=0.0;
		if (g) {
			g=1.0/g;
			if (i != n) {
				for (j=l;j<=n;j++) {
					for (s=0.0,k=l;k<=m;k++) s += a[k][i]*a[k][j];
					f=(s/a[i][i])*g;
					for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
				}
			}
			for (j=i;j<=m;j++) a[j][i] *= g;
		} else {
			for (j=i;j<=m;j++) a[j][i]=0.0;
		}
		++a[i][i];
	}
	for (k=n;k>=1;k--) {
		for (its=1;its<=30;its++) {
			flag=1;
			for (l=k;l>=1;l--) {
				nm=l-1;
				if (fabs(rv1[l])+anorm == anorm) {
					flag=0;
					break;
				}
				if (fabs(w[nm])+anorm == anorm) break;
			}
			if (flag) {
				c=0.0;
				s=1.0;
				for (i=l;i<=k;i++) {
					f=s*rv1[i];
					if (fabs(f)+anorm != anorm) {
						g=w[i];
						h=PYTHAG(f,g);
						w[i]=h;
						h=1.0/h;
						c=g*h;
						s=(-f*h);
						for (j=1;j<=m;j++) {
							y=a[j][nm];
							z=a[j][i];
							a[j][nm]=y*c+z*s;
							a[j][i]=z*c-y*s;
						}
					}
				}
			}
			z=w[k];
			if (l == k) {
				if (z < 0.0) {
					w[k] = -z;
					for (j=1;j<=n;j++) v[j][k]=(-v[j][k]);
				}
				break;
			}
			ELISE_ASSERT
                        (
				 its <= 30,
				 "No convergence in 30 SVDCMP iterations"
                        );
			x=w[l];
			nm=k-1;
			y=w[nm];
			g=rv1[nm];
			h=rv1[k];
			f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);
			g=PYTHAG(f,1.0);
			f=((x-z)*(x+z)+h*((y/(f+SIGN(g,f)))-h))/x;
			c=s=1.0;
			for (j=l;j<=nm;j++) {
				i=j+1;
				g=rv1[i];
				y=w[i];
				h=s*g;
				g=c*g;
				z=PYTHAG(f,h);
				rv1[j]=z;
				c=f/z;
				s=h/z;
				f=x*c+g*s;
				g=g*c-x*s;
				h=y*s;
				y=y*c;
				for (jj=1;jj<=n;jj++) {
					x=v[jj][j];
					z=v[jj][i];
					v[jj][j]=x*c+z*s;
					v[jj][i]=z*c-x*s;
				}
				z=PYTHAG(f,h);
				w[j]=z;
				if (z) {
					z=1.0/z;
					c=f*z;
					s=h*z;
				}
				f=(c*g)+(s*y);
				x=(c*y)-(s*g);
				for (jj=1;jj<=m;jj++) {
					y=a[jj][j];
					z=a[jj][i];
					a[jj][j]=y*c+z*s;
					a[jj][i]=z*c-y*s;
				}
			}
			rv1[l]=0.0;
			rv1[k]=f;
			w[k]=x;
		}
	}
}

static REAL SetToMatDirecte(ElMatrix<REAL> & aMat)
{
   if (aMat.Det() >0)
     return 1;

   for (int y=0; y<aMat.ty() ; y++)
       aMat(0,y) *= -1;
   return -1;
}

ElMatrix<REAL> NearestRotation ( const ElMatrix<REAL> & aMat)
{
     INT n = aMat.tx();
     ElMatrix<REAL> anU(n),aV(n),aDiag(n);

     svdcmp_diag(aMat,anU,aDiag,aV,true);

     

     ElMatrix<REAL> aMul (n);

     for (int aK=0 ; aK < n ; aK++)
       aMul(aK,aK) = (aDiag(aK,aK) > 0) ? 1 : -1;


     return anU *  aMul * aV;
}

/*
void MakeRONConservByPrio(Pt3dr & aV1,Pt3dr & aV2,Pt3dr & aV3)
{
    aV1 = vunit(aV1);
    aV2 = vunit(aV2);
    aV3 = aV1 ^ aV2;
    aV2 = aV3 ^aV1;

    aV2 = vunit(aV2);
}
*/

void MakeRONWith1Vect(Pt3dr & aV1,Pt3dr & aV2,Pt3dr & aV3)
{
    aV1 = vunit(aV1);
    if (ElAbs(aV1.x) < ElAbs(aV1.y))
       aV2 = Pt3dr(0,aV1.z,-aV1.y);
    else
       aV2 = Pt3dr(aV1.z,0,-aV1.x);

   aV2 = vunit(aV2);
   aV3 = aV1 ^ aV2;
}

Pt3dr MakeOrthon(Pt3dr & aV1,Pt3dr & aV2)
{
   Pt3dr aU1 = vunit(aV1);
   Pt3dr aU2 = vunit(aV2);

   aV1 = vunit(aU1+aU2);
   aV2 = vunit(aU1-aU2);
   return aV1 ^ aV2;
}

ElMatrix<double>  MakeMatON(Pt3dr aV1,Pt3dr aV2)
{
   Pt3dr aV3 = MakeOrthon(aV1,aV2);

   return MatFromCol(aV1,aV2,aV3);
}


ElMatrix<REAL> ComplemRotation
               (
                    const Pt3dr & anAnt1,
                    const Pt3dr & anAnt2,
                    const Pt3dr & anIm1,
                    const Pt3dr & anIm2
               )
{
  return    MakeMatON(anIm1,anIm2)
         *  MakeMatON(anAnt1,anAnt2).transpose();
}


void svdcmp
     (
          const ElMatrix<REAL> & aMat,
	  ElMatrix<REAL> & anU,
	  ElMatrix<REAL> & aDiag,
	  ElMatrix<REAL> & aV,
          bool             direct
     )
{
     anU  = aMat;
     INT n = anU.tx();
     ELISE_ASSERT(n==anU.ty(),"Not Squre in jacobi");
     aDiag.set_to_size(n,1);
     aV.set_to_size(n,n);

     NR_svdcmp(anU.data(),n,n,aDiag.data()[0],aV.data());

     if (direct)
     {
         REAL sign = SetToMatDirecte(anU) * SetToMatDirecte(aV);
         if (sign < 0)
            aDiag(0,0) *= -1;
     }
     aV.self_transpose();
}

void svdcmp_diag
     (
          const ElMatrix<REAL> & aMat,
	  ElMatrix<REAL> & anU,
	  ElMatrix<REAL> & aDiag,
	  ElMatrix<REAL> & aV,
          bool             direct
     )
{
   ElMatrix<REAL> aLineVP(aMat.tx(),1);
   svdcmp(aMat,anU,aLineVP,aV,direct);
   MatLigneToDiag(aLineVP,aDiag);
}

#undef SIGN
#undef MAX
#undef PYTHAG

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
