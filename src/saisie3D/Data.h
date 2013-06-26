#ifndef DATA_H
#define DATA_H


#include "StdAfx.h"
#include "Cloud.h"

using namespace Cloud_;

class cData
{
    public:

        cData();
        ~cData();

        void addCamera(CamStenope *);
        void addCloud(Cloud *);

        void addCameras(vector <CamStenope *>);
        void addClouds(vector <Cloud *>);

        void clearCameras();
        void clearClouds();

        int NbCameras(){return m_Cameras.size();}
        int NbClouds(){return m_Clouds.size();}

        CamStenope * & getCamera(int aK) {return m_Cameras[aK];}
        Cloud * & getCloud(int aK) {return m_Clouds[aK];}

        void    getBB(Cloud *);

        int     getSizeClouds();

        void    reset();

        //Bounding box, center and diameter of all clouds
        float m_minX, m_maxX, m_minY, m_maxY, m_minZ, m_maxZ, m_cX, m_cY, m_cZ, m_diam;

   private:

        vector <CamStenope *> m_Cameras;
        vector <Cloud *>      m_Clouds;
};
#endif // DATA_H
