#include "Engine.h"
#include "general/bitm.h"

cLoader::cLoader()
 : _FilenamesIn(),
   _FilenamesOut(),
   _postFix("_Masq")
{}

void cLoader::setFilenamesOut()
{
    _FilenamesOut.clear();

    for (int aK=0;aK < _FilenamesIn.size();++aK)
    {
        QFileInfo fi(_FilenamesIn[aK]);

        _FilenamesOut.push_back(fi.path() + QDir::separator() + fi.completeBaseName() + _postFix + ".tif");
    }
}

void cLoader::setFilenameOut(QString str)
{
    _FilenamesOut.clear();

    _FilenamesOut.push_back(str);
}

void cLoader::setPostFix(QString str)
{
    _postFix = str;
}

void cLoader::setSelectionFilename()
{
    _SelectionOut = _Dir.absolutePath() + QDir::separator() + "SelectionInfos.xml";
}

Cloud* cLoader::loadCloud( string i_ply_file, int* incre )
{
    return Cloud::loadPly( i_ply_file, incre );
}

void cLoader::loadImage(QString aNameFile , QMaskedImage &maskedImg)
{    

    maskedImg._m_image = new QImage( aNameFile );

    QFileInfo fi(aNameFile);

    QString mask_filename = fi.path() + QDir::separator() + fi.completeBaseName() + "_Masq.tif";

    setFilenameOut(mask_filename);


    // TODO factoriser le chargement d'image
    if (maskedImg._m_image->isNull())
    {
        Tiff_Im aTF= Tiff_Im::StdConvGen(aNameFile.toStdString(),3,false);

        Pt2di aSz = aTF.sz();

        Im2D_U_INT1  aImR(aSz.x,aSz.y);
        Im2D_U_INT1  aImG(aSz.x,aSz.y);
        Im2D_U_INT1  aImB(aSz.x,aSz.y);

        ELISE_COPY
        (
           aTF.all_pts(),
           aTF.in(),
           Virgule(aImR.out(),aImG.out(),aImB.out())
        );

        U_INT1 ** aDataR = aImR.data();
        U_INT1 ** aDataG = aImG.data();
        U_INT1 ** aDataB = aImB.data();

        delete maskedImg._m_image;
        maskedImg._m_image = new QImage(aSz.x, aSz.y, QImage::Format_RGB32);

        for (int y=0; y<aSz.y; y++)
        {
            for (int x=0; x<aSz.x; x++)
            {
                QColor col(aDataR[y][x],aDataG[y][x],aDataB[y][x]);

                maskedImg._m_image->setPixel(x,y,col.rgb());
            }
        }
    }

    *(maskedImg._m_image) = QGLWidget::convertToGLFormat( *(maskedImg._m_image) );

    if (QFile::exists(mask_filename))
    {

        maskedImg._m_newMask = false;

        maskedImg._m_mask = new QImage( mask_filename );

        if (maskedImg._m_mask->isNull())
        {
            Tiff_Im imgMask( mask_filename.toStdString().c_str() );

            if( imgMask.can_elise_use() )
            {
                int w = imgMask.sz().x;
                int h = imgMask.sz().y;

                delete maskedImg._m_mask;
                maskedImg._m_mask = new QImage( w, h, QImage::Format_Mono);
                maskedImg._m_mask->fill(0);

                Im2D_Bits<1> aOut(w,h,1);
                ELISE_COPY(imgMask.all_pts(),imgMask.in(),aOut.out());

                for (int x=0;x< w;++x)
                    for (int y=0; y<h;++y)
                        if (aOut.get(x,y) == 1 )
                            maskedImg._m_mask->setPixel(x,y,1);

                *(maskedImg._m_mask) = QGLWidget::convertToGLFormat(*(maskedImg._m_mask));
            }
            else
            {
                QMessageBox::critical(NULL, "cLoader::loadMask","Cannot load mask image");
            }
        }
        else
            *(maskedImg._m_mask) = QGLWidget::convertToGLFormat(*(maskedImg._m_mask));

    }
    else
    {
        maskedImg._m_mask = new QImage(maskedImg._m_image->size(),QImage::Format_Mono);
        *(maskedImg._m_mask) = QGLWidget::convertToGLFormat(*(maskedImg._m_mask));
        maskedImg._m_mask->fill(Qt::white);
    }

}

// File structure is assumed to be a typical Micmac workspace structure:
// .ply files are in /MEC folder and orientations files in /Ori- folder
// /MEC and /Ori- are in the main working directory (m_Dir)

CamStenope* cLoader::loadCamera(QString aNameFile)
{
    string DirChantier = (_Dir.absolutePath()+ QDir::separator()).toStdString();
    string filename    = aNameFile.toStdString();

    #ifdef _DEBUG
        cout << "DirChantier : " << DirChantier << endl;
        cout << "filename : "    << filename << endl;
    #endif

    QFileInfo fi(aNameFile);

    _FilenamesOut.push_back(fi.path() + QDir::separator() + fi.completeBaseName() + "_Masq.tif");

    cInterfChantierNameManipulateur * anICNM = cInterfChantierNameManipulateur::BasicAlloc(DirChantier);

    return CamOrientGenFromFile(filename.substr(DirChantier.size(),filename.size()),anICNM);
}

//****************************************
//   cEngine

cEngine::cEngine():    
    _Loader(new cLoader),
    _Data(new cData),
    _Gamma(1.f)
{}

cEngine::~cEngine()
{

    delete _Loader;
    unloadAll();
    delete _Data;

}

void cEngine::loadClouds(QStringList filenames, int* incre)
{
    for (int i=0;i<filenames.size();++i)
    {
        _Data->addCloud(_Loader->loadCloud(filenames[i].toStdString(), incre));
    }

    _Data->getBB();
}

void cEngine::loadCameras(QStringList filenames)
{
    for (int i=0;i<filenames.size();++i)
    {
        _Data->addCamera(_Loader->loadCamera(filenames[i]));
    }

    _Data->getBB();
}

void cEngine::loadImages(QStringList filenames)
{
    for (int i=0;i<filenames.size();++i)
    {
        loadImage(filenames[i]);
    }

    _Loader->setFilenamesOut();
}

void  cEngine::loadImage(QString imgName)
{
    QMaskedImage maskedImg(_Gamma);

    _Loader->loadImage(imgName, maskedImg);

    _Data->PushBackMaskedImage(maskedImg);
}

void cEngine::do3DMasks()
{
    CamStenope* pCam;
    Cloud *pCloud;
    Vertex vert;
    Pt2dr ptIm;

    for (int cK=0;cK < _Data->getNbCameras();++cK)
    {
        pCam = _Data->getCamera(cK);

        Im2D_BIN mask = Im2D_BIN(pCam->Sz(), 0);

        for (int aK=0; aK < _Data->getNbClouds();++aK)
        {
            pCloud  = _Data->getCloud(aK);

            for (int bK=0; bK < pCloud->size();++bK)
            {
                vert = pCloud->getVertex(bK);

                if (vert.isVisible())  //visible = selected in GLWidget
                {
                    Pt3dr pt(vert.getPosition());

                    if (pCam->PIsVisibleInImage(pt)) //visible = projected inside image
                    {
                        ptIm = pCam->Ter2Capteur(pt);
                        mask.set(floor(ptIm.x), floor(ptIm.y), 1);
                    }
                }
            }
        }

        string aOut = _Loader->getFilenamesOut()[cK].toStdString();
#ifdef _DEBUG
        printf ("Saving %s\n", aOut);
#endif

        Tiff_Im::CreateFromIm(mask, aOut);

#ifdef _DEBUG
        printf ("Done\n");
#endif
    }
}

void cEngine::doMaskImage(ushort idCur)
{
    QImage pMask = _vGLData[idCur]->getMask()->mirrored().convertToFormat(QImage::Format_Mono);

    if (!pMask.isNull())
    {
        QString aOut = _Loader->getFilenamesOut()[idCur];

        pMask.save(aOut);

		cFileOriMnt anOri;

        anOri.NameFileMnt()		= aOut.toStdString();
        anOri.NombrePixels()	= Pt2di(pMask.width(),pMask.height());
		anOri.OriginePlani()	= Pt2dr(0,0);
		anOri.ResolutionPlani() = Pt2dr(1.0,1.0);
		anOri.OrigineAlti()		= 0.0;
		anOri.ResolutionAlti()	= 1.0;
		anOri.Geometrie()		= eGeomMNTFaisceauIm1PrCh_Px1D;

        MakeFileXML(anOri, StdPrefix(aOut.toStdString()) + ".xml");
	}
	else
    {
        QMessageBox::critical(NULL, "cEngine::doMaskImage","No alpha channel!!!");
    }
}

void cEngine::saveMask(ushort idCur)
{
    if (getData()->getNbImages())
        doMaskImage(idCur);
    else
        do3DMasks();
}

void cEngine::saveSelectInfos(const QVector<selectInfos> &Infos)
{
    QDomDocument doc;

    QFile outFile(_Loader->getSelectionFilename());
    if (!outFile.open(QIODevice::WriteOnly)) return;

    QDomElement SI = doc.createElement("SelectionInfos");

    QDomText t;
    for (int i = 0; i < Infos.size(); ++i)
    {
        QDomElement SII            = doc.createElement("Item");
        QDomElement mvMatrixElem   = doc.createElement("ModelViewMatrix");
        QDomElement ProjMatrixElem = doc.createElement("ProjMatrix");
        QDomElement glViewportElem = doc.createElement("glViewport");
        QDomElement Mode           = doc.createElement("Mode");

        const selectInfos &SInfo = Infos[i];

        if ((SInfo.mvmatrix != NULL) && (SInfo.projmatrix != NULL) && (SInfo.glViewport != NULL))
        {
            QString text1, text2;

            text1 = QString::number(SInfo.mvmatrix[0], 'f');
            text2 = QString::number(SInfo.projmatrix[0], 'f');

            for (int aK=0; aK < 16;++aK)
            {
                text1 += " " + QString::number(SInfo.mvmatrix[aK], 'f');
                text2 += " " + QString::number(SInfo.projmatrix[aK], 'f');
            }

            t = doc.createTextNode(text1);
            mvMatrixElem.appendChild(t);

            t = doc.createTextNode(text2);
            ProjMatrixElem.appendChild(t);

            text1 = QString::number(SInfo.glViewport[0]) ;
            for (int aK=1; aK < 4;++aK)
                text1 += " " + QString::number(SInfo.glViewport[aK]);

            t = doc.createTextNode(text1);
            glViewportElem.appendChild(t);

            SII.appendChild(mvMatrixElem);
            SII.appendChild(ProjMatrixElem);
            SII.appendChild(glViewportElem);

            QVector <QPointF> pts = SInfo.poly;

            for (int aK=0; aK < pts.size(); ++aK)
            {
                QDomElement Point    = doc.createElement("Pt");
                QString str = QString::number(pts[aK].x(), 'f',1) + " "  + QString::number(pts[aK].y(), 'f',1);

                t = doc.createTextNode( str );
                Point.appendChild(t);
                SII.appendChild(Point);
            }

            t = doc.createTextNode(QString::number(SInfo.selection_mode));
            Mode.appendChild(t);

            SII.appendChild(Mode);

            SI.appendChild(SII);
        }
        else
            cerr << "saveSelectInfos: null matrix";

    }

    doc.appendChild(SI);

    QTextStream content(&outFile);
    content << doc.toString();
    outFile.close();

#ifdef _DEBUG
        printf ( "File saved in: %s\n", _Loader->getSelectionFilename().toStdString().c_str());
#endif
}

void cEngine::unloadAll()
{
    _Data->clearAll();
    qDeleteAll(_vGLData);
    _vGLData.clear();
}

void cEngine::AllocAndSetGLData()
{
    _vGLData.clear();

    for (int aK = 0; aK < _Data->getNbImages();++aK)
        _vGLData.push_back(new cGLData(_Data->getMaskedImage(aK)));

    if (_Data->is3D())
        _vGLData.push_back(new cGLData(_Data));

}

cGLData* cEngine::getGLData(int WidgetIndex)
{
    if ((_vGLData.size() > 0) && (WidgetIndex < _vGLData.size()))
        return _vGLData[WidgetIndex];
    else
        return NULL;
}

//********************************************************************************

cGLData::cGLData():
    _diam(1.f){}

cGLData::cGLData(QMaskedImage &qMaskedImage):
    glMaskedImage(qMaskedImage),
    pQMask(qMaskedImage._m_mask),
    pBall(NULL),
    pAxis(NULL),
    pBbox(NULL)
{

}

cGLData::cGLData(cData *data):
    _diam(1.f)
{
    for (int aK = 0; aK < data->getNbClouds();++aK)
    {
        Cloud *pCloud = data->getCloud(aK);
        Clouds.push_back(pCloud);
        pCloud->setBufferGl();
    }

    Pt3dr center = data->getBBCenter();
    float scale = data->m_diam / 1.5f;

    pBall = new cBall(center, scale);
    pAxis = new cAxis(center, scale);
    pBbox = new cBBox(center, scale, data->m_min, data->m_max);

    for (int i=0; i< data->getNbCameras(); i++)
    {
        cCam *pCam = new cCam(data->getCamera(i), scale);

        Cams.push_back(pCam);
    }

    setBBmaxSize(data->getBBmaxSize());
    setBBCenter(data->getBBCenter());
}

cGLData::~cGLData()
{
    glMaskedImage.deallocImages();

   qDeleteAll(Cams);
    Cams.clear();

    if(pBall != NULL) delete pBall;
    if(pAxis != NULL) delete pAxis;
    if(pBbox != NULL) delete pBbox;

   //pas de delete des pointeurs dans Clouds c'est Data qui s'en charge
    Clouds.clear();
}

void cGLData::draw()
{
    enableOptionLine();

    for (int i=0; i<Clouds.size();i++)
        Clouds[i]->draw();

    pBall->draw();
    pAxis->draw();
    pBbox->draw();

    //cameras
    for (int i=0; i< Cams.size();i++) Cams[i]->draw();

    disableOptionLine();
}

//********************************************************************************

ViewportParameters::ViewportParameters()
    : m_zoom(1.f)
    , m_PointSize(1)
    , m_LineWidth(1.f)
    , m_speed(2.f)
{
    m_translationMatrix[0] = m_translationMatrix[1] = m_translationMatrix[2] = 0.f;
}

ViewportParameters::ViewportParameters(const ViewportParameters& params)
    : m_zoom(params.m_zoom)
    , m_PointSize(params.m_PointSize)
    , m_LineWidth(params.m_LineWidth)
{
    m_translationMatrix[0] = params.m_translationMatrix[0];
    m_translationMatrix[1] = params.m_translationMatrix[1];
    m_translationMatrix[2] = params.m_translationMatrix[2];
}

ViewportParameters::~ViewportParameters(){}

ViewportParameters& ViewportParameters::operator =(const ViewportParameters& par)
{
    if (this != &par)
    {
        m_zoom = par.m_zoom;
        m_PointSize = par.m_PointSize;

        m_translationMatrix[0] = par.m_translationMatrix[0];
        m_translationMatrix[1] = par.m_translationMatrix[1];
        m_translationMatrix[2] = par.m_translationMatrix[2];
        m_LineWidth = par.m_LineWidth;
    }

    return *this;
}

void ViewportParameters::reset()
{
    m_zoom = m_LineWidth = 1.f;
    m_PointSize = 1;

    m_translationMatrix[0] = m_translationMatrix[1] = m_translationMatrix[2] = 0.f;
}

void ViewportParameters::ptSizeUp(bool up)
{
    if (up)
        m_PointSize++;
    else
        m_PointSize--;

    if (m_PointSize == 0)
        m_PointSize = 1;

    glPointSize((GLfloat) m_PointSize);
}


