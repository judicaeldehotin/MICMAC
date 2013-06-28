#include "Engine.h"
#include "general/bitm.h"

cLoader::cLoader()
 : m_FilenamesIn(),
   m_FilenamesOut()
{}

void cLoader::SetFilenamesOut()
{
    m_FilenamesOut.clear();

    for (int aK=0;aK < m_FilenamesIn.size();++aK)
    {
        QFileInfo fi(m_FilenamesIn[aK]);

        m_FilenamesOut.push_back(fi.path() + QDir::separator() + fi.completeBaseName() + "_masq.tif");
    }
}

Cloud* cLoader::loadCloud( string i_ply_file, void (*incre)(int,void*), void* obj )
{
    return Cloud::loadPly( i_ply_file, incre, obj );
}

vector <CamStenope *> cLoader::loadCameras()
{
   vector <CamStenope *> a_res;

   m_FilenamesIn = QFileDialog::getOpenFileNames(NULL, tr("Open Camera Files"), m_Dir.path(), tr("Files (*.xml)"));

   for (int aK=0;aK < m_FilenamesIn.size();++aK)
   {
       a_res.push_back(loadCamera(m_FilenamesIn[aK].toStdString()));
   }

   SetFilenamesOut();

   return a_res;
}

// File structure is assumed to be a typical Micmac workspace structure:
// .ply files are in /MEC folder and orientations files in /Ori- folder
// /MEC and /Ori- are in the main working directory (m_Dir)

CamStenope* cLoader::loadCamera(string aNameFile)
{
    string DirChantier = (m_Dir.absolutePath()+ QDir::separator()).toStdString();

    cInterfChantierNameManipulateur * anICNM = cInterfChantierNameManipulateur::BasicAlloc(DirChantier);

    return CamOrientGenFromFile(aNameFile.substr(DirChantier.size(),aNameFile.size()),anICNM);
}

//****************************************
//   cEngine

cEngine::cEngine():    
    m_Loader(new cLoader),
    m_Data(new cData)
{}

cEngine::~cEngine()
{
   delete m_Data;
   delete m_Loader;
}

void cEngine::loadClouds(QStringList filenames, void (*incre)(int,void*), void* obj)
{
    for (int i=0;i<filenames.size();++i)
    {
        getData()->getBB(m_Loader->loadCloud(filenames[i].toStdString(), incre,obj));
    }
}

void cEngine::loadCloudsWin(QStringList filenames)
{
    for (int i=0;i<filenames.size();++i)
    {
        getData()->getBB(m_Loader->loadCloud(filenames[i].toStdString()));
    }
}

void cEngine::loadCameras(QStringList filenames)
{
    for (int i=0;i<filenames.size();++i)
    {
        m_Data->addCamera(m_Loader->loadCamera(filenames[i].toStdString()));
    }
}

void cEngine::loadCameras()
{
    m_Data->addCameras(m_Loader->loadCameras());
}

void cEngine::doMasks()
{
    if (m_Data->NbClouds()==0) return;

    CamStenope* pCam;
    Cloud *pCloud;
    Vertex vert;
    Pt2dr ptIm;

    for (int cK=0;cK < m_Data->NbCameras();++cK)
    {
        pCam = m_Data->getCamera(cK);

        Im2D_BIN mask = Im2D_BIN(pCam->Sz(), 0);

        for (int aK=0; aK < m_Data->NbClouds();++aK)
        {
            pCloud  = m_Data->getCloud(aK);

            for (int bK=0; bK < pCloud->size();++bK)
            {
                vert = pCloud->getVertex(bK);                

                if (vert.isVisible())  //visible = selected in GLWidget
                {
                    Pt3dr pt(vert.getCoord());

                    if (pCam->PIsVisibleInImage(pt)) //visible = projected inside image
                    {
                        ptIm = pCam->Ter2Capteur(pt);
                        mask.set(floor(ptIm.x), floor(ptIm.y), 1);
                    }
                }
            }
        }

        string aOut = m_Loader->GetFilenamesOut()[cK].toStdString();
        #ifdef _DEBUG
            printf ("Saving %s\n", aOut);
        #endif

        Tiff_Im::CreateFromIm(mask, aOut);

        #ifdef _DEBUG
            printf ("Done\n");
        #endif  
    }
}

void cEngine::saveSelectInfos(string)
{
   /* for (int aK=0; aK < m_infos.size() ; ++aK )
    {
        //TODO: if (m_infos[aK].pose == m_infos[aK-1].pose) aK++;
        //else write block pose
    }*/
}

void cEngine::unloadAll()
{
    m_Data->clearClouds();
    m_Data->clearCameras();
}


//********************************************************************************

ViewportParameters::ViewportParameters()
    : zoom(1.0f)
    , PointSize(1.0f)
    , LineWidth(1.0f)
{}

ViewportParameters::ViewportParameters(const ViewportParameters& params)
    : zoom(params.zoom)
    , PointSize(params.PointSize)
    , LineWidth(params.LineWidth)
{}

ViewportParameters::~ViewportParameters(){}

//********************************************************************************

cSelectInfos::cSelectInfos(){}

cSelectInfos::~cSelectInfos(){}

cSelectInfos::cSelectInfos(ViewportParameters par, std::vector<Pt2df> polyline, SELECTION_MODE selMode)
{
    m_params = par;
    m_poly = polyline;
    m_selection_mode = selMode;
}
