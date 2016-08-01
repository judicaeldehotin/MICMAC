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


#include "../../uti_phgrm/NewOri/NewOri.h"
#include "InitOutil.h"
#include "Detector.h"
#include "PHO_MI.h"

//using namespace cv;


InitOutil::InitOutil   ( string aFullPattern, string aOriInput,
                         string aTypeD, vector<double> aParamD)
{
    cout<<"Init MicMac, lire pattern, former le cle.."<<endl;
    this->mOriInput = aOriInput;
    this->mFullPattern = aFullPattern;
    this->mTypeD = aTypeD;
    this->mParamD = aParamD;
    // Initialize name manipulator & files
    SplitDirAndFile(mDirImages, mPatIm, mFullPattern); //Working dir, Images pattern
    StdCorrecNameOrient(mOriInput, mDirImages);//remove "Ori-" if needed
    mICNM = cInterfChantierNameManipulateur::BasicAlloc(mDirImages);
    mSetIm = *(mICNM->Get(mPatIm));
    ELISE_ASSERT(mSetIm.size()>0,"ERROR: No image found!");
    //============================================================
       //anExt = ExpTxt ? "txt" : "dat";
       mHomolOutput = "_FilteredPly";
       mNameHomol = "Homol";
       mKHOut =   std::string("NKS-Assoc-CplIm2Hom@")
                           +  std::string(mHomolOutput)
                           +  std::string("@")
                           +  std::string("txt");

       mKHOutDat =   std::string("NKS-Assoc-CplIm2Hom@")
                           +  std::string(mHomolOutput)
                           +  std::string("@")
                           +  std::string("dat");

       mKHIn =   std::string("NKS-Assoc-CplIm2Hom@")
                          +  std::string(mNameHomol)
                          +  std::string("@")
                          +  std::string("dat");
}

PlyFile* InitOutil::read_file(string pathPlyFileS)
{
    cout<<" ++ Import mesh: "<<endl;
    PlyFile *ply;               /* description of PLY file */
    //------------------
    Vertex **vlist;             /* 3-space position of a vertex */
    Face **flist;               /* intensite, list vert_ind, n° vertex ind*/
    int nelems;
    char **elist;
    int file_type;
    float version;
    int nprops;
    int num_elems;
    char *elem_name;
    int num_comments;
    int num_obj_info;
    //read file ply header, give information about version, type element, n° element
    char *pathPlyFile = new char[pathPlyFileS.length() + 1];
    strcpy( pathPlyFile, pathPlyFileS.c_str() );

    ply = ply_open_for_reading(pathPlyFile, &nelems, &elist, &file_type, &version);
    cout<<"Object has "<<ply->nelems<<" elements "<<" , type = "<<file_type<<" ,version = "<<version<<endl;;
    for (int i=0; i<ply->nelems; i++)
    {   /*
                ply->elems[i]->name :name of elements types in file
                ply->elems[i]->num : number of element of this type
                ply->elems[i]->nprops : number of properties of this element type
            */
        cout<<" ++ "<<ply->elems[i]->name<<" : "<<ply->elems[i]->num<<" items, each has "<<ply->elems[i]->nprops<<" properties "<<endl;
        /*
                elems[i]->props[k]->name : name of property k of element type i
            */
        for (int k=0; k<ply->elems[i]->nprops; k++)
        {cout<<"     "<<ply->elems[i]->props[k]->name;}
        cout<<endl;
    }
    for (int i = 0; i < ply->nelems; i++)
    {   //scan through each element type
        elem_name = ply->elems[i]->name;
        ply_get_element_description (ply, elem_name , &num_elems, &nprops);  /*get properties of each element type*/
        if (equal_strings ("vertex", elem_name))
        {   //Vertex element type
            vlist = (Vertex **) malloc (sizeof (Vertex *) * num_elems);
            ply_get_property (ply, elem_name, &vert_props[0]);      //recuperer propertie [0] -x de element type vertex. vert_props containt definition of element Vertex in .h
            ply_get_property (ply, elem_name, &vert_props[1]);      //recuperer propertie [1] -y de element type vertex
            ply_get_property (ply, elem_name, &vert_props[2]);      //recuperer propertie [2] -z de element type vertex
            for (int j = 0; j < num_elems; j++)
            {   //scan all items of this element
                vlist[j] = (Vertex *) malloc (sizeof (Vertex));
                ply_get_element (ply, (void *) vlist[j]);           // Read one items of element from the file, element and property to read is define by ply_get_property() executed before
                /* DEBUG
                    cout<<"vertex: "<<vlist[j]->x<<" "<< vlist[j]->y<<" "<< vlist[j]->z<<endl;
                 */
                mVertexList.push_back(vlist[j]);
            }
        }
        if (equal_strings ("face", elem_name))
        {
            flist = (Face **) malloc (sizeof (Face *) * num_elems);
            ply_get_property (ply, elem_name, &face_props[0]);        //define properties, type of properties according with properties wrote in ply file
            ply_get_property (ply, elem_name, &face_props[1]);        //
            for (int j = 0; j < num_elems; j++)
            { //scan all items of this element
                flist[j] = (Face *) malloc (sizeof (Face));
                ply_get_element (ply, (void *) flist[j]);               //read item of element "face" to flist
                mFaceList.push_back(flist[j]);
                /*  DEBUG
                cout<<"Face "<<j<<" from "<<+flist[j]->nverts<<" vertex : ";
                for (int k = 0; k < flist[j]->nverts; k++)
                  {cout<<" "<<flist[j]->verts[k];}
                  cout<<endl;
                */
            }
        }
    }
    ply_get_comments (ply, &num_comments);
    ply_get_obj_info (ply, &num_obj_info);
    cout << "There are "<<num_comments<<" comments"<<endl;
    fclose (ply->fp);

    //-----------

    for (int i=0; i<ply->num_comments; i++)
    {cout<<ply->comments[i]<<endl;}
    cout << "There are "<<ply->num_obj_info<<" object info"<<endl;
    for (int i=0; i<ply->num_obj_info; i++)
    {cout<<ply->obj_info[i]<<endl;}
    cout<<"There are "<<ply->nelems<<" elements in file"<<endl;
    for (int i=0; i<ply->nelems; i++)
    {
        cout<<"Element "<<i<<" is "<<ply->elems[i]->name<<" have "<<ply->elems[i]->nprops<<" properties, "<<ply->elems[i]->num<<" items"<<endl;
        cout<<"  Properties: ";
        for (int j=0; j<ply->elems[i]->nprops; j++)
        {cout<<ply->elems[i]->props[j]->name<<"   ";  }
        cout<<endl;
    }
    cout<<"Display items in elements ? [y/n] new"<<endl;
    char ch = static_cast<char>(getc(stdin));
    if (ch == 'y')
    {
        cout<<"Yes "<<endl;
        for (int i=0; i<ply->nelems; i++)
        {
            cout<<"Display items in elements "<<ply->elems[i]->name<< " ? [y/n]"<<endl;
            char ch1 = static_cast<char>(getc(stdin));
            if (ch1 == 'y')
            {
                if(strcmp(ply->elems[i]->name, "vertex") == 0)
                {
                    for (int j=0; j<ply->elems[i]->num; j++)
                    {
                        cout<<ply->elems[i]->name<<" "<<j<<" : "<<mVertexList[j]->x<<" "<<mVertexList[j]->y<<" "<<mVertexList[j]->z<<endl;
                    }
                }
                if(strcmp(ply->elems[i]->name , "face") == 0)
                {
                    for (int j=0; j<ply->elems[i]->num; j++)
                    {
                        cout<<ply->elems[i]->name<<" "<<j<<" : ";
                        for (int k=0; k<mFaceList[j]->nverts; k++)
                        {cout<<mFaceList[j]->verts[k]<<" " ;}
                        cout<<endl;
                    }
                }
            }
        }
    }
    mPly = ply;
    return ply;
}

vector<pic*> InitOutil::load_Im()
{
    cout<<" ++ Load "<<mSetIm.size()<<" image"<<endl;
    for (uint i=0; i<mSetIm.size(); i++)
    {
        pic *aPic = new pic( &mSetIm[i], mOriInput, mICNM, i);
        mPtrListPic.push_back(aPic);
    }
    return mPtrListPic;
}

vector<triangle*> InitOutil::load_tri()
{
    cout<<" ++ Load "<<mFaceList.size()<<" triangles"<<endl;
    for (uint i=0; i<mFaceList.size(); i++)
    {
        triangle *aTri = new triangle(mFaceList[i], mVertexList, mPtrListPic.size(), i );
        mPtrListTri.push_back(aTri);
    }
    for (uint i=0; i<mPtrListPic.size(); i++)
        {mPtrListPic[i]->allTriangle = mPtrListTri;}
    return mPtrListTri;
}

void InitOutil::reprojectAllTriOnAllImg()
{
    cout<<" ++ Reproject"<<endl;
    //Access sommet of triangle i:
    //PtrListTri[i]->getSommet(0) -- Pt3d; ou PtrListTri[0]->getSommetV(0) -- Ptr to Vertex
    for (uint i=0; i<mPtrListTri.size(); i++)
    {
        for (uint j=0; j<mPtrListPic.size(); j++)
        {
            bool ok;
            Tri2d TriRepr;
            mPtrListTri[i]->reproject(mPtrListPic[j], ok, TriRepr, j);
        }
    }
    //Access to reprojection of triangle i on pic j by : *PtrListTri[i]->getReprSurImg()[j] -- return Tri2d;
}

//=====Creat pack homologue initial avec des autre images
/*
    *1. Si creatLikeHomoPackInit=true => chaque pic
    * sauvgarde vector<mPackHomoWithAnotherPic> contient pack homo avec tout les autre image
    * que les images qui a pack homo init avec ce pic la a taille =1
    * les images qui n'a pas pack homo init => taille = 0
    *
    * 2. Si creatLikeHomoPackInit=false => tout les couple
*/
void InitOutil::initHomoPackVide(bool creatLikeHomoPackInit = true)
{
    cout<<" ++Creat pack Homo vide"<<endl;
    //CREAT ALL NEW PACK HOMO
    for (uint i=0; i<mPtrListPic.size(); i++)
    {
        for (uint j=0; j<mPtrListPic.size(); j++)
        {
            pic *pic1 = mPtrListPic[i];
            pic *pic2 = mPtrListPic[j];
            PackHomo initPack;
            initPack.indPic1 = i;
            initPack.indPic2 = j;
            ElCplePtsHomologues initCpl(Pt2dr(0,0), Pt2dr(0,0));
            if (creatLikeHomoPackInit)
            {
                string HomoIn = mICNM->Assoc1To2(mKHIn, *pic1->mNameImg, *pic2->mNameImg, true);
                StdCorrecNameHomol_G(HomoIn,mDirImages);
                bool Exist = ELISE_fp::exist_file(HomoIn);
                if (Exist)
                    initPack.aPack.Cple_Add(initCpl);
            }
            else
                initPack.aPack.Cple_Add(initCpl);
            pic1->mPackHomoWithAnotherPic.push_back(initPack);
        }
    }
}


void InitOutil::initAll(string pathPlyFileS)
{
    cout<<"Init all.."<<endl;
    this->read_file(pathPlyFileS);
    this->load_Im();
    this->load_tri();
    this->reprojectAllTriOnAllImg();
    this->initHomoPackVide();
    cout<<"Init done..!"<<endl;
}

string InitOutil::getPrivMember(string aName)
{
    if (aName == "mKHIn")
        return this->mKHIn;
    if (aName == "mHomolOutput")
        return this->mHomolOutput;
    if (aName == "mNameHomol")
        return this->mNameHomol;
    if (aName == "mKHOut")
        return this->mKHOut;
    if (aName == "mKHOutDat")
        return this->mKHOutDat;
    if (aName == "mDirImages")
        return this->mDirImages;
    if (aName == "mPatIm")
        return this->mPatIm;
    if (aName == "mFullPattern")
        return this->mFullPattern;
    if (aName == "mOriInput")
        return this->mOriInput;
    if (aName == "mTypeD")
        return this->mTypeD;
}

//========les fonction outil supplementaire ===========//
std::string intToString ( int number )
{
  std::ostringstream oss;
  oss<< number;
  return oss.str();
}

std::string constStringToString(const string * aCString)
{
    return aCString->c_str();
}

