#ifndef ENGINE_H
#define ENGINE_H


#include "cgldata.h"



class ViewportParameters
{
public:
    //! Default constructor
    ViewportParameters();

    //! Copy constructor
    ViewportParameters(const ViewportParameters& params);

    //! Destructor
    ~ViewportParameters();

    //!
    ViewportParameters & operator = (const ViewportParameters &);

    void    reset();

    void    ptSizeUp(bool up);

    float   changeZoom(float DChange)
    {
        if      (DChange > 0) m_zoom *= pow(2.f,  DChange *.05f);
        else if (DChange < 0) m_zoom /= pow(2.f, -DChange *.05f);

        return  m_zoom;
    }

    //! Current zoom
    float m_zoom;

    //! Point size
    int m_pointSize;

    //! Rotation and translation speed
    float m_speed;
};

class deviceIOTieFile
{
public:
	virtual void  load(QString aNameFile,QPolygonF& poly) = 0;
};

class deviceIOCamera
{
public:
	virtual cCamHandler*  loadCamera(QString aNameFile) = 0;
};

class deviceIOImage
{
public:
	virtual QImage*	loadImage(QString aNameFile,bool OPENGL = true) = 0;

	virtual QImage*	loadMask(QString aNameFile) = 0;

	virtual void	doMaskImage(QImage &mask,QString &aNameFile) = 0;
};

class cLoader
{

public:

    cLoader();

	cCamHandler* loadCamera(QString aNameFile);

    GlCloud*    loadCloud(string i_ply_file , int *incre = NULL);

	void        loadImage(QString aNameFile, QMaskedImage *maskedImg, float scaleFactor = 1.f);

	void        loadMask(QString aNameFile, QMaskedImage *maskedImg, float scaleFactor = 1.f);

    void        setFilenames(QStringList const &strl);
    void        setFilenameOut(QString str);

    QStringList& getFilenamesIn()        { return _FilenamesIn;  }
    QStringList& getFilenamesOut()       { return _FilenamesOut; }
    QStringList& getSelectionFilenames() { return _SelectionOut; }

    void        setPostFix(QString str);

	void memory();

	deviceIOCamera* devIOCamera() const;
	void setDevIOCamera(deviceIOCamera* devIOCamera);

	deviceIOImage* devIOImageAlter() const;
	void setDevIOImageAlter(deviceIOImage* devIOImageAlter);

private:
	QStringList _FilenamesIn;
	QStringList _FilenamesOut; //binary masks
	QStringList _SelectionOut; //selection infos
    QString     _postFix;

	deviceIOCamera* _devIOCamera;

	deviceIOImage*  _devIOImageAlter;
};

class cGLData;


enum idGPU_Vendor
{
    NVIDIA,
    AMD,
    ATI,
    INTEL,
    NOMODEL
};


class cEngine
{
public:

    cEngine();
    ~cEngine();

    //! Set appli params
    void    setParams(cParameters *params){ _params = params; }

    //! Set input filenames
    void    setFilenames(QStringList const &strl){ _Loader->setFilenames(strl); }

    QStringList& getFilenamesIn(){return _Loader->getFilenamesIn();}

    QStringList& getFilenamesOut(){return _Loader->getFilenamesOut();}

    //! Set output filename
    void    setFilenameOut(QString filename){_Loader->setFilenameOut(filename);}

    QStringList& getSelectionFilenamesOut() { return _Loader->getSelectionFilenames(); }

    //! Set postfix
    void    setPostFix(){_Loader->setPostFix(_params->getPostFix());}

    //! Load point cloud .ply files
    void    loadClouds(QStringList, int *incre = NULL);

    //! Load cameras .xml files
    void    loadCameras(QStringList, int *incre = NULL);

    //! Load images  files
    void    loadImages(QStringList, int *incre = NULL);

    //! Load image (and mask) file
	void    loadImage(QString imgName, float scaleFactor = 1.f);

    //void    reloadImage(int appMode, int aK);
    void    reloadMask(int appMode, int aK);

    //! Load object

    void    addObject(cObject*);

    void    unloadAll();

    void    unload(int aK);

    //! Compute mask binary images: projection of visible points into loaded cameras
//    void    do3DMasks();

    //! Creates binary image from selection and saves
    void    doMaskImage(ushort idCur, bool isFirstAction);

    void    saveBox2D(ushort idCur);

    void    saveMask(ushort idCur, bool isFirstAction);

    cData*  getData()  {return _Data;}

    //!looks for data and creates GLobjects
    void    allocAndSetGLData(int appMode, cParameters aParams);

    void    reallocAndSetGLData(int appMode, cParameters aParams, int aK);

    //!sends GLObjects to GLWidget
    cGLData* getGLData(int WidgetIndex);

    int     nbGLData(){return (int)_vGLData.size();}

	float	computeScaleFactor(QStringList &filenames);
    bool    extGLIsSupported(const char *strExt);
    void    setGLMaxTextureSize(int size) { _glMaxTextSize = size; }

	cLoader* Loader() const;
	void setLoader(cLoader* Loader);

private:

	cLoader*            _Loader;
	cData*              _Data;

    QVector <cGLData*>  _vGLData;

    cParameters*        _params;

    int                 _glMaxTextSize;
};

#endif // ENGINE_H
