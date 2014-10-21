#include "StdAfx.h"
#include "../uti_phgrm/MICMAC/cCameraModuleOrientation.h"

/** Development based on
 CARTOSAT-1 DEM EXTRACTION CAPABILITY STUDY OVER SALON AREA
 R. Gachet & P. Fave
**/

class AffCamera
{
 public:
    AffCamera(string aFilename, int index): filename (aFilename), mIndex(index)
    {
        // Loading the GRID file
        ElAffin2D oriIntImaM2C;
        Pt2di Sz(10000,10000);
        mCamera =  new cCameraModuleOrientation(new OrientationGrille(filename),Sz,oriIntImaM2C);

        //Affinity parameters
        vP.push_back(0);
        vP.push_back(1);
        vP.push_back(0);
        vP.push_back(0);
        vP.push_back(0);
        vP.push_back(1);
    }

    ///
    /// \brief update affinity parameters
    /// \param sol unknowns matrix
    ///
    void updateParams(ElMatrix <double> const &sol)
    {
        std::cout << "Init solution: "<<std::endl;
        printParams();

        for (size_t aK=0; aK< vP.size(); aK++)
            vP[aK] += sol(0,aK);

        std::cout << "Updated solution: "<<std::endl;
        printParams();
    }

    void printParams()
    {
        for (size_t aK=0; aK< vP.size(); aK++)
            std::cout << vP[aK] <<" ";
        std::cout << std::endl;
    }

    ElCamera* Camera() { return mCamera; }

    // the 6 parameters of affinity
    // colc = vP[0] + vP[1] * col + vP[2] * lig
    // rowc = vP[3] + vP[4] * col + vP[5] * lig
    std::vector <double> vP;

    ///
    /// \brief image filename
    ///
    std::string filename;

    int mIndex;

    ~AffCamera()
    {
        if (mCamera)
            delete mCamera;
    }

protected:

    ElCamera* mCamera;
};

class CameraPair
{
public:
    CameraPair(AffCamera* aMaster, AffCamera* aSlave):master(aMaster), slave(aSlave){}

    AffCamera* master;
    AffCamera* slave;

    ///
    /// \brief compute the difference between the Ground Points for a given Tie Point and a given set of parameters (Z and affinity)
    /// \param ptImgMaster tie-point from master image
    /// \param ptImgSlave tie-point from slave image
    /// \param aZ   ground altitude
    /// \param aA0  affinity parameter
    /// \param aA1  affinity parameter
    /// \param aA2  affinity parameter
    /// \param aB0  affinity parameter
    /// \param aB1  affinity parameter
    /// \param aB2  affinity parameter
    /// \return Pt2Dr 2D difference between ground points
    ///
    Pt2dr compute2DGroundDifference(Pt2dr const &ptImgMaster,
                                    Pt2dr const &ptImgSlave,
                                    double aZ,
                                    double aA0,
                                    double aA1,
                                    double aA2,
                                    double aB0,
                                    double aB1,
                                    double aB2) const
    {
        Pt3dr ptTerMaster = master->Camera()->ImEtProf2Terrain(ptImgMaster,aZ);
        Pt2dr ptImgSlaveC(aA0 + aA1 * ptImgSlave.x + aA2 * ptImgSlave.y,
                          aB0 + aB1 * ptImgSlave.x + aB2 * ptImgSlave.y);
        Pt3dr ptTerSlave = slave->Camera()->ImEtProf2Terrain(ptImgSlaveC,aZ);
        return Pt2dr(ptTerMaster.x - ptTerSlave.x,ptTerMaster.y - ptTerSlave.y);
    }

    Pt2dr compute2DGroundDifference(Pt2dr const &ptImgMaster,
                                    Pt2dr const &ptImgSlave,
                                    double aZ) const
    {
        return compute2DGroundDifference(ptImgMaster,ptImgSlave,aZ,slave->vP[0],slave->vP[1],slave->vP[2],slave->vP[3],slave->vP[4],slave->vP[5]);
    }

    ~CameraPair()
    {
        if (master)
            delete master;
        if (slave)
            delete slave;
    }
};

struct ImageMeasure
{
    Pt2dr ptImg;  // image coordinates (in pixel)
    int   idx;    // index of AffCamera

    //bool valid; // should this measure be used for estimation
};

class TiePoint
{
public:
    TiePoint(std::map <int, AffCamera *> *aMap): valid(true), pMapCam(aMap){}

    Pt3dr getCoord();

    Pt2dr computeImageDifference(int index,  //index in vImgMeasure
                                 double aA0,
                                 double aA1,
                                 double aA2,
                                 double aB0,
                                 double aB1,
                                 double aB2);

    Pt2dr computeImageDifference(int index);

    std::vector <ImageMeasure> vImgMeasure;

    bool valid; // should this point be used for estimation?

    std::map <int, AffCamera *> *pMapCam;
};

Pt3dr TiePoint::getCoord()
{
    if (vImgMeasure.size() == 2)
    {
        map<int, AffCamera *>::iterator iter1, iter2;
        iter1 = pMapCam->find(vImgMeasure[0].idx);
        iter2 = pMapCam->find(vImgMeasure[1].idx);

        AffCamera* cam1 = iter1->second;
        AffCamera* cam2 = iter2->second;

        Pt2dr P1 = vImgMeasure[0].ptImg;
        Pt2dr P2 = vImgMeasure[1].ptImg;

        return cam1->Camera()->PseudoInter(P1,*cam2->Camera(),P2);
    }
    else
    {
        std::vector<ElSeg3D>  aVS;
        for ( size_t aK=0; aK < vImgMeasure.size(); aK++ )
        {
            map<int, AffCamera *>::iterator iter = pMapCam->find(vImgMeasure[aK].idx);

            if (iter != pMapCam->end())
            {
                AffCamera* aCam = iter->second;

                Pt2dr aPN = vImgMeasure[aK].ptImg;

                aVS.push_back(aCam->Camera()->F2toRayonR3(aPN));
            }
        }

        return ElSeg3D::L2InterFaisceaux(0,aVS);
    }
}

Pt2dr TiePoint::computeImageDifference(int index, double aA0, double aA1, double aA2, double aB0, double aB1, double aB2)
{
    ImageMeasure* aMes = &vImgMeasure[index];

    Pt2dr ptImg = aMes->ptImg;

    map<int, AffCamera *>::const_iterator iter;
    iter = pMapCam->find(aMes->idx);
    AffCamera* cam = iter->second;

    Pt2dr ptImgC(aA0 + aA1 * ptImg.x + aA2 * ptImg.y,
                 aB0 + aB1 * ptImg.x + aB2 * ptImg.y);

    Pt2dr proj = cam->Camera()->R3toF2(getCoord());

    return ptImgC - proj;
}

Pt2dr TiePoint::computeImageDifference(int index)
{
    ImageMeasure* aMes = &vImgMeasure[index];

    Pt2dr ptImg = aMes->ptImg;

    map<int, AffCamera *>::const_iterator iter;
    iter = pMapCam->find(aMes->idx);
    AffCamera* cam = iter->second;

    double aA0 = cam->vP[0];
    double aA1 = cam->vP[1];
    double aA2 = cam->vP[2];
    double aB0 = cam->vP[3];
    double aB1 = cam->vP[4];
    double aB2 = cam->vP[5];

    Pt2dr ptImgC(aA0 + aA1 * ptImg.x + aA2 * ptImg.y,
                 aB0 + aB1 * ptImg.x + aB2 * ptImg.y);

    Pt2dr proj = cam->Camera()->R3toF2(getCoord());

    return ptImgC - proj;
}

//! Abstract class for shared methods
class RefineModelAbs
{
protected:
    std::map <int, AffCamera*> mapCameras;

    std::vector <TiePoint*> vObs;

    ///
    /// \brief normal matrix for least squares estimation
    ///
    ElMatrix<double> _N;
    ///
    /// \brief matrix for least squares estimation
    ///
    ElMatrix<double> _Y;

public:

    ///
    /// \brief constructor (loads GRID files, tie-points and filter tie-points on 2D ground difference)
    /// \param aNameFileGridMaster Grid file for master image
    /// \param aNameFileGridSlave Grid file for slave image
    /// \param aNamefileTiePoints Tie-points file
    ///
    RefineModelAbs(std::string const &aFullDir):_N(1,1,0.),_Y(1,1,0.)
    {
        string aDir, aPat;
        SplitDirAndFile(aDir,aPat,aFullDir);

        list<string> aVFiles = RegexListFileMatch(aDir, aPat, 1, false);
        list<string>::iterator itr = aVFiles.begin();
        for(;itr != aVFiles.end(); itr++)
        {
            std::string aNameFileGrid1 = *itr;

            list<string>::iterator it = itr; it++;
            for(;it != aVFiles.end(); it++)
            {
                std::string aNameFileGrid2 = *it;

                // Loading the GRID file
                AffCamera* Cam1 = findCamera(aDir + aNameFileGrid1);
                mapCameras.insert(std::pair <int,AffCamera*>(mapCameras.size(), Cam1));

                AffCamera* Cam2 = findCamera(aDir + aNameFileGrid2);
                mapCameras.insert(std::pair <int,AffCamera*>(mapCameras.size(), Cam2));

                CameraPair *CamPair = new CameraPair(Cam1, Cam2);

                // Loading the Tie Points with altitude approximate estimation
                std::string filename = StdPrefixGen(aNameFileGrid1)+ "_" + StdPrefixGen(aNameFileGrid2);
                std::string aNameFileTiePoints = aDir + filename +".txt"; //.dat

                if ( !ELISE_fp::exist_file(aNameFileTiePoints) )
                    std::cout << "file missing: " << aNameFileTiePoints << endl;
                else
                {
                    std::cout << "reading: " << aNameFileTiePoints << endl;

                    std::ifstream fic(aNameFileTiePoints.c_str());

                    if (fic.good())
                    {
                        int rPts_nb = 0; //rejected points number
                        int TP_nb = 0;   //tie-points number

                        string line;

                        while ( getline (fic,line) )
                        {
                            //cout << line << std::endl;
                            istringstream iss(line);

                            Pt2dr P1,P2;
                            iss >> P1.x >> P1.y >> P2.x >> P2.y;

                            if ((P1 != Pt2dr(0,0)) && (P2 != Pt2dr(0,0)))
                            {
                                //std::cout << "P1 = "<<P1.x<<" " <<P1.y << std::endl;
                                //std::cout << "P2 = "<<P2.x<<" " <<P2.y << std::endl;

                                double z = Cam1->Camera()->PseudoInter(P1,*Cam2->Camera(),P2).z;
                                //std::cout << "z = "<<z<<std::endl;
                                Pt2dr D = CamPair->compute2DGroundDifference(P1,P2,z);

                                if (square_euclid(D)>100.)
                                {
                                    rPts_nb++;
                                    std::cout << "Point with 2D ground difference > 10 : "<< D.x << " " << D.y << " - rejected" << std::endl;
                                }
                                else
                                {
                                    TP_nb++;
                                    ImageMeasure imMes1, imMes2;

                                    imMes1.ptImg = P1;
                                    imMes2.ptImg = P2;

                                    imMes1.idx = Cam1->mIndex;
                                    imMes2.idx = Cam2->mIndex;

                                    //algo brute force (� am�liorer)
                                    bool found = false;
                                    for (size_t aK=0; aK < vObs.size(); ++aK)
                                    {
                                        TiePoint* TP = vObs[aK];
                                        for (size_t bK=0; bK < TP->vImgMeasure.size(); bK++)
                                        {
                                            ImageMeasure *imMes3 = &TP->vImgMeasure[bK];
                                            if ((imMes3->idx != Cam1->mIndex) && (imMes3->ptImg == P1))
                                            {
                                                TP->vImgMeasure.push_back(imMes2);
                                                std::cout << "multiple point: " << P1.x << " " << P1.y << " found in " << imMes3->idx << " and " << imMes1.idx << std::endl;
                                                found = true;
                                            }
                                            else if ((imMes3->idx != Cam2->mIndex) && (imMes3->ptImg == P2))
                                            {
                                                TP->vImgMeasure.push_back(imMes1);
                                                std::cout << "multiple point: " << P2.x << " " << P2.y << " found in " << imMes3->idx << " and " << imMes2.idx << std::endl;
                                                found = true;
                                            }
                                        }
                                    }

                                    if (!found)
                                    {
                                        TiePoint *TP = new TiePoint(&mapCameras);

                                        TP->vImgMeasure.push_back(imMes1);
                                        TP->vImgMeasure.push_back(imMes2);

                                        vObs.push_back(TP);

                                        std::cout << "vObs size : " << vObs.size() << std::endl;
                                    }
                                }
                            }
                        }
                        std::cout << "Number of rejected points: "<< rPts_nb << std::endl;
                        std::cout << "Number of tie points: "<< TP_nb << std::endl;

                        if (TP_nb ==0)
                            std::cout << "Error in RefineModelAbs: no tie-points" << std::endl;
                    }
                    else
                    {
                        std::cout << "Error reading file" << aNameFileTiePoints << endl;
                    }
                }
            }
        }
    }

    ///
    /// \brief 2D ground distance sum for all tie points (to compute RMS)
    /// \return sum of residuals (square distance - to avoid using sqrt (faster) )
    ///
    double sumRes() //TODO: verifier qu'on fait la bonne somme
    {
        double sumRes = 0.;
        for (size_t aK=0; aK < vObs.size();++aK)
        {
            for(size_t i=0;i<vObs[aK]->vImgMeasure.size();++i)
            {
                Pt2dr D = vObs[aK]->computeImageDifference(i);
                sumRes += square_euclid(D);
            }
        }
        return sumRes;
    }

    ///
    /// \brief debug matrix
    /// \param mat matrix to write
    ///
    void printMatrix(ElMatrix <double> const & mat)
    {
        std::cout << "-------------------------"<<std::endl;
        for(int i=0;i<mat.Sz().x;++i)
        {
            for(int j=0;j<mat.Sz().y;++j)
                std::cout << mat(i,j) <<" ";

            std::cout << std::endl;
        }
        std::cout << "-------------------------"<<std::endl;
    }

    ///
    /// \brief check if a new iteration should be run and write result file (at the step before exiting loop)
    /// \param iniRMS rms before system solve
    /// \param numObs system number of observations
    /// \return
    ///
    bool launchNewIter(double iniRMS, int numObs)
    {
        double curRMS = std::sqrt(sumRes()/numObs);

        if (curRMS>iniRMS)
        {
            std::cout << "curRMS = "<<curRMS<<" / iniRMS = "<<iniRMS<<std::endl;
            std::cout << "No improve: end"<<std::endl;
            return false;
        }

        //ecriture dans un fichier des coefficients en vue d'affiner la grille

        map<int, AffCamera *>::const_iterator iter = mapCameras.begin();
        for (size_t aK=0; iter != mapCameras.end();++iter, ++aK)
        {
            AffCamera* cam = iter->second;
            std::string name = StdPrefixGen(cam->filename);
            std::ofstream fic(("refine/" + name + ".txt").c_str());
            fic << std::setprecision(15);
            fic << cam->vP[0] <<" "<< cam->vP[1] <<" "<< cam->vP[2] <<" "<< cam->vP[3] <<" "<< cam->vP[4] <<" "<< cam->vP[5] <<" "<<std::endl;
        }
        std::cout << "RMS_after = " << curRMS << std::endl;
        return true;
    }

    ///
    /// \brief estimates affinity parameters
    ///
    virtual void solve()=0;

    ///
    /// \brief computes the observation matrix for one iteration
    /// \return boolean stating if system is solved (need new iteration)
    ///
    virtual bool computeObservationMatrix()=0;

    virtual ~RefineModelAbs(){}

    AffCamera *findCamera(std::string aFilename)
    {
        map<int, AffCamera *>::const_iterator it = mapCameras.begin();
        for (;it!=mapCameras.end();++it)
        {
            if (it->second->filename == aFilename) return it->second;
        }
        return new AffCamera(aFilename, mapCameras.size());
    }

    int nObs() { return vObs.size(); }
};

#ifdef tata

//! Implementation utilisant la suppression des inconnues auxiliaires (les Z)
class RefineModel:public RefineModelAbs
{

public:
    RefineModel(std::string const &aPat):RefineModelAbs(aPat)
    {
    }

    ///
    /// \brief add an observation to system
    /// \param obs observation matrix
    /// \param p weighting
    /// \param res residual
    ///
    void addObs(const ElMatrix<double> &obs, const double p, const double res)
    {
        //construction iterative de la matrice normale
        _N += (obs.transpose()*obs)*p;  //il existe certainement une norme ou une facon plus elegante de l'ecrire ...
        //idem pour Y
        _Y += obs.transpose()*res*p;

        //on elimine la premiere inconnue
        //a00Z + SUM(a0k.Xk) = b0;
        //ai0Z + SUM(aik.Xk) = bi; ...

        double piv = _N(0,0);
        //todo si pivot trop petit ... !

        //std::cout << "piv = "<<piv<<std::endl;

        const size_t numUnk = _N.Sz().x;

        //pour les autres lignes
        for(size_t line = 1;line < numUnk; line++)
        {
            double pivotLine = _N(0,line);

            if (pivotLine == 0.) continue;

            for(size_t col = 1; col < numUnk; col++)
                _N(col,line) -= _N(col,0)*pivotLine/piv;

            //meme principe pour le vecteur Y
            _Y(0,line) -= _Y(0,0)*pivotLine/piv;
        }

        //un peu de nettoyage : 1ere ligne
        for(size_t col = 0; col < numUnk; col++)
            _N(col,0) = 0.;

        for(size_t line = 1;line < numUnk; line++)
            _N(0,line) = 0.;

        _Y(0,0) = 0.;
    }

    void solve()
    {
        _N(0,0) = 1.;

        std::cout << "Matrix _N:"<<std::endl;
        printMatrix(_N);

        std::cout << "Matrix _Y:"<<std::endl;
        printMatrix(_Y);

        ElMatrix<double> inv = gaussj(_N);
        std::cout << "Matrix inv:"<<std::endl;
        printMatrix(inv);
        ElMatrix<double> sol = inv*_Y;

        std::cout << "Matrix sol:"<<std::endl;
        printMatrix(sol);

        //std::cout << "SOL_NORM = " << sol.NormC(2) << std::endl;

        map<int, AffCamera *>::const_iterator iter = mapCameras.begin();
        for (; iter != mapCameras.end() ; ++iter)
        {
            iter->second->updateParams(sol);
        }

        //estimation des Z
        /*
        double dZ = 0.5, sumDZ=0.;
        for(size_t i=0;i<vPtImgMaster.size();++i)
        {
            Pt2dr const &ptImgMaster = vPtImgMaster[i];
            Pt2dr const &ptImgSlave  = vPtImgSlave[i];
            double const Z = vZ[i];

            // ecart constate
            Pt2dr D = compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0,a1,a2,b0,b1,b2);

            Pt2dr vdZ  = Pt2dr(1./dZ,1./dZ)  * (compute2DGroundDifference(ptImgMaster,ptImgSlave,Z + dZ,a0,a1,a2,b0,b1,b2)-D);

            ElMatrix<double> mZ(1,2,0.);
            mZ(0,0) = vdZ.x;
            mZ(0,1) = vdZ.y;
            ElMatrix<double> NZ = mZ.transpose()*mZ;
            ElMatrix<double> resZ(1,2,0.);
            resZ(0,0) = -D.x;
            resZ(0,1) = -D.y;
            ElMatrix<double> YZ = mZ.transpose()*resZ;

            double deltaZ = YZ(0,0)/NZ(0,0);

            vZ[i] += deltaZ;
            sumDZ += deltaZ;

            std::cout << vZ[i] << std::endl;
        }
        std::cout << "SumDZ = " << sumDZ << std::endl;
        */
    }

    // compute the observation matrix for one iteration
    bool computeObservationMatrix()
    {
        size_t numUnk = 7;                       // Nombre d'inconnues par cam�ra

        // Remise a zero des matrices
        _N = ElMatrix<double>(numUnk*mNbPair,numUnk*mNbPair,0.);
        _Y = ElMatrix<double>(1,numUnk*mNbPair,0.);

        size_t cpt=0;
        for (size_t aK=0; aK < mNbPair; aK++) cpt +=  master(aK)->vPtImg.size();
        size_t numObs = 2*cpt + numUnk;  // Nombre d'observations (dont stabilisation des inconnues)

        double iniRMS = std::sqrt(sumRes()/numObs);

        std::cout << "RMS_ini = " << iniRMS << std::endl;

        double dZ =  0.5;
        double dA0 = 0.5;
        double dA1 = 0.01;
        double dA2 = 0.01;
        double dB0 = 0.5;
        double dB1 = 0.01;
        double dB2 = 0.01;

        //Ponderation
        double sigmaDelta = 1.; //m
        /*bool   weightByRes = false;
        //Ponderation stabilisation
        double sigmaTransX = 1.; //pix
        double sigmaTransY = 1.;  //pix
        double sigmaMat = 1./std::pow(0.001,2); //sans unite
        double sigmaMatA1 = 1./std::pow(0.0001,2);*/

        //pour chaque obs (ligne), y compris les eq de stabilisation
        //for( toutes les obs )

        for (size_t aK=0; aK < mNbPair; aK++)
        {
            for(size_t i=0;i< master(aK)->vPtImg.size();++i)
            {
                Pt2dr const &ptImgMaster = master(aK)->vPtImg[i];
                Pt2dr const &ptImgSlave  = slave(aK)->vPtImg[i];
                double const Z = vZ(aK)[i]; //todo: a remplacer

                ElMatrix<double> obs(numUnk,1,0.);
                //a remplir avec derivees partielles ...

                // ecart constate
                Pt2dr D = vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z);

                //todo : strategie d'elimination d'observations / ou ponderation

                // estimation des derivees partielles
                double a0 = slave(aK)->vP[0];
                double a1 = slave(aK)->vP[1];
                double a2 = slave(aK)->vP[2];
                double b0 = slave(aK)->vP[3];
                double b1 = slave(aK)->vP[4];
                double b2 = slave(aK)->vP[5];

                Pt2dr vdZ  = Pt2dr(1./dZ,1./dZ)   * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z + dZ)-D);
                Pt2dr vdA0 = Pt2dr(1./dA0,1./dA0) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0+dA0,a1,a2,b0,b1,b2)-D);
                Pt2dr vdA1 = Pt2dr(1./dA1,1./dA1) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0,a1+dA1,a2,b0,b1,b2)-D);
                Pt2dr vdA2 = Pt2dr(1./dA2,1./dA2) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0,a1,a2+dA2,b0,b1,b2)-D);
                Pt2dr vdB0 = Pt2dr(1./dB0,1./dB0) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0,a1,a2,b0+dB0,b1,b2)-D);
                Pt2dr vdB1 = Pt2dr(1./dB1,1./dB1) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0,a1,a2,b0,b1+dB1,b2)-D);
                Pt2dr vdB2 = Pt2dr(1./dB2,1./dB2) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0,a1,a2,b0,b1,b2+dB2)-D);

                obs(0+numUnk*aK,0) = vdZ.x;
                obs(1+numUnk*aK,0) = vdA0.x;
                obs(2+numUnk*aK,0) = vdA1.x;
                obs(3+numUnk*aK,0) = vdA2.x;
                obs(4+numUnk*aK,0) = vdB0.x;
                obs(5+numUnk*aK,0) = vdB1.x;
                obs(6+numUnk*aK,0) = vdB2.x;

                addObs(obs,sigmaDelta,0.-D.x);
                //ajout
                //if((D.x<2)&&(D.y<2)) {addObs(obs,1/std::sqrt(1+D.x*D.x),D.x);}
                //fin ajout
                obs(0+numUnk*aK,0) = vdZ.y;
                obs(1+numUnk*aK,0) = vdA0.y;
                obs(2+numUnk*aK,0) = vdA1.y;
                obs(3+numUnk*aK,0) = vdA2.y;
                obs(4+numUnk*aK,0) = vdB0.y;
                obs(5+numUnk*aK,0) = vdB1.y;
                obs(6+numUnk*aK,0) = vdB2.y;

                addObs(obs,sigmaDelta,0.-D.y);
                //ajout
                //if((D.x<2)&&(D.y<2)) {addObs(obs,1/std::sqrt(1+D.y*D.y),D.y);}
                //fin ajout
            }
        }
        //stabilisation
        /*
        addObs(1,sigmaTransX,   0.-a0);
        addObs(2,sigmaMat,		1.-a1);
        addObs(3,sigmaMat,      0.-a2);
        addObs(4,sigmaTransY,   0.-b0);
        addObs(5,sigmaMat,      0.-b1);
        addObs(6,sigmaMat,		1.-b2);
        */
        solve();

        return launchNewIter(iniRMS, numObs);
    }


    ~RefineModel()
    {
    }
};

//! Implementation basique (sans suppression des inconnues auxiliaires)
class RefineModelBasic: public RefineModelAbs
{

public:
    RefineModelBasic(std::string const &aPat):RefineModelAbs(aPat)
    {
    }

    void solve()
    {
        /*
        std::cout << "solve"<<std::endl;
        std::cout << "Matrice _N:"<<std::endl;
        printMatrix(_N);
        std::cout << "Matrice _Y:"<<std::endl;
        printMatrix(_Y);
        */
        ElMatrix<double> AtA = _N.transpose() * _N;
        //printMatrix(AtA);
        ElMatrix<double> AtB = _N.transpose() * _Y;
        //printMatrix(AtB);
        ElMatrix<double> sol = gaussj(AtA) * AtB;
        /*
        std::cout << "Matrice sol:"<<std::endl;
        printMatrix(sol);
        */
        //std::cout << "SOL_NORM = " << sol.NormC(2) << std::endl;

        for (size_t aK=0; aK < mNbPair; aK++)
        {
            slave(aK)->updateParams(sol, aK);

            //mise a jour des Z
                //TODO: lien entre les point de liaisons et les points 3D
            for(size_t i=0;i<master(aK)->vPtImg.size();++i)
            {
                vZ(aK)[i] += sol(0,6*mNbPair+i); //todo: a remplacer
                std::cout << vZ(aK)[i] << std::endl;
            }
        }

    }

    //! compute the observation matrix for one iteration
    bool computeObservationMatrix()
    {
        int cpt = 0;
        for (size_t aK=0; aK < mNbPair; aK++) cpt += vCamPair[aK]->vZ.size();
        int numObs = 2*cpt;
        double iniRMS = std::sqrt(sumRes()/numObs);
        std::cout << "RMS_ini = " << iniRMS << std::endl;

        double dZ  = 0.5;
        double dA0 = 0.5;
        double dA1 = 0.01;
        double dA2 = 0.01;
        double dB0 = 0.5;
        double dB1 = 0.01;
        double dB2 = 0.01;

        _N = ElMatrix<double>(6+cpt,numObs+6,0.);
        _Y = ElMatrix<double>(1,numObs+6,0.);

        //pour chaque obs (ligne), y compris les eq de stabilisation
        //for( toutes les obs )
        for (size_t aK=0; aK < mNbPair; aK++)
        {
            for(size_t i=0;i<master(aK)->vPtImg.size();++i)
            {
                //std::cout << "i = "<<i<<std::endl;
                Pt2dr const &ptImgMaster = master(aK)->vPtImg[i];
                Pt2dr const &ptImgSlave  = slave(aK)->vPtImg[i];
                double const Z = vZ(aK)[i]; //todo: a remplacer

                // ecart constate
                Pt2dr D = vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z);

                //todo : strategie d'elimination d'observations / ou ponderation

                // estimation des derivees partielles
                double a0 = slave(aK)->vP[0];
                double a1 = slave(aK)->vP[1];
                double a2 = slave(aK)->vP[2];
                double b0 = slave(aK)->vP[3];
                double b1 = slave(aK)->vP[4];
                double b2 = slave(aK)->vP[5];

                Pt2dr vdZ  = Pt2dr(1./dZ,1./dZ)   * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z+dZ) -D);
                Pt2dr vdA0 = Pt2dr(1./dA0,1./dA0) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0+dA0,a1,a2,b0,b1,b2)-D);
                Pt2dr vdA1 = Pt2dr(1./dA1,1./dA1) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0,a1+dA1,a2,b0,b1,b2)-D);
                Pt2dr vdA2 = Pt2dr(1./dA2,1./dA2) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0,a1,a2+dA2,b0,b1,b2)-D);
                Pt2dr vdB0 = Pt2dr(1./dB0,1./dB0) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0,a1,a2,b0+dB0,b1,b2)-D);
                Pt2dr vdB1 = Pt2dr(1./dB1,1./dB1) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0,a1,a2,b0,b1+dB1,b2)-D);
                Pt2dr vdB2 = Pt2dr(1./dB2,1./dB2) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0,a1,a2,b0,b1,b2+dB2)-D);

                _N(0,2*i) = vdA0.x;
                _N(1,2*i) = vdA1.x;
                _N(2,2*i) = vdA2.x;
                _N(3,2*i) = vdB0.x;
                _N(4,2*i) = vdB1.x;
                _N(5,2*i) = vdB2.x;
                _N(6+i,2*i) = vdZ.x;

                _N(0,2*i+1) = vdA0.y;
                _N(1,2*i+1) = vdA1.y;
                _N(2,2*i+1) = vdA2.y;
                _N(3,2*i+1) = vdB0.y;
                _N(4,2*i+1) = vdB1.y;
                _N(5,2*i+1) = vdB2.y;
                _N(6+i,2*i+1) = vdZ.y;

                _Y(0,2*i) = -D.x;
                _Y(0,2*i+1) = -D.y;
            }
            // Equation de stabilisation
            {
                double pdt = cpt;
                // A0 proche de 0
                _N(0,numObs) = 1 * pdt;
                _Y(0,numObs) = (0-slave(aK)->vP[0]) * pdt;
                // A1 proche de 1
                _N(1,numObs+1) = 1 * pdt;
                _Y(0,numObs+1) = (1-slave(aK)->vP[1]) * pdt;
                // A2 proche de 0
                _N(2,numObs+2) = 1 * pdt;
                _Y(0,numObs+2) = (0-slave(aK)->vP[2]) * pdt;
                // B0 proche de 0
                _N(3,numObs+3) = 1 * pdt;
                _Y(0,numObs+3) = (0-slave(aK)->vP[3]) * pdt;
                // B1 proche de 0
                _N(4,numObs+4) = 1 * pdt;
                _Y(0,numObs+4) = (0-slave(aK)->vP[4]) * pdt;
                // B2 proche de 1
                _N(5,numObs+5) = 1 * pdt;
                _Y(0,numObs+5) = (1-slave(aK)->vP[5]) * pdt;
            }
        }
        std::cout << "before solve"<<std::endl;

        solve();

        return launchNewIter(iniRMS, numObs);
    }

    ~RefineModelBasic()
    {
    }
};


//! Implementation basique simplifiee (uniquement la translation, pas d'estimation des 4 autres parametres)
class RefineModelTransBasic:public RefineModelAbs
{
    double zMoy;

public:
    RefineModelTransBasic(std::string const &aPat,
                     double Zmoy):RefineModelAbs(aPat), zMoy(Zmoy)
    {
    }

    void solve()
    {
        std::cout << "solve"<<std::endl;
        std::cout << "Matrice _N:"<<std::endl;
        printMatrix(_N);
        std::cout << "Matrice _Y:"<<std::endl;
        printMatrix(_Y);

        ElMatrix<double> AtA = _N.transpose() * _N;
        printMatrix(AtA);

        ElMatrix<double> AtB = _N.transpose() * _Y;
        printMatrix(AtB);

        ElMatrix<double> sol = gaussj(AtA) * AtB;

        printMatrix(sol);

        //std::cout << "SOL_NORM = " << sol.NormC(2) << std::endl;

        for (size_t aK=0; aK < mNbPair; aK++)
        {
            std::cout << "Solution ini : "<<std::endl;
            slave(aK)->printParams();

            slave(aK)->vP[0] -= sol(0,0);     //pourquoi -= ???
            slave(aK)->vP[3] -= sol(0,1);

            std::cout << "Solution mise a jour : "<<std::endl;
            slave(aK)->printParams();

            //mise a jour des Z
            //TODO
            for(size_t i=0;i<master(aK)->vPtImg.size();++i)
            {
                vZ(aK)[i] -= sol(0,2+i); //pourquoi -= ???
                std::cout << vZ(aK)[i] << std::endl;
            }
        }

    }

    //! compute the observation matrix for one iteration
    bool computeObservationMatrix()
    {
        size_t cpt = 0;
        for (size_t aK=0; aK < mNbPair; aK++) cpt += vCamPair[aK]->vZ.size();
        int numObs = 2*cpt;
        double iniRMS = std::sqrt(sumRes()/numObs);
        std::cout << "RMS_ini = " << iniRMS << std::endl;

        double dZ = 1;//0.5;
        double dA0 = 1;//0.5;
        double dB0 = 1;//0.5;

        //Ponderation
        /*double sigmaDelta = 1./std::pow(1.,2); //m
        bool   weightByRes = false;
        //Ponderation stabilisation
        double sigmaTransX = 1./std::pow(1.,2); //pix
        double sigmaTransY = 1./std::pow(0.05,0.2);  //pix
        double sigmaMat = 1./std::pow(0.001,2); //sans unite*/

        _N = ElMatrix<double>(2+cpt,2*cpt+3,0.);
        _Y = ElMatrix<double>(1,2*cpt+3,0.);

        //pour chaque obs (ligne), y compris les eq de stabilisation
        //for( toutes les obs )
        for (size_t aK=0; aK < mNbPair; aK++)
        {
            for(size_t i=0;i<master(aK)->vPtImg.size();++i)
            {
                std::cout << "i = "<<i<<std::endl;
                Pt2dr const &ptImgMaster = master(aK)->vPtImg[i];
                Pt2dr const &ptImgSlave  = slave(aK)->vPtImg[i];
                double const Z = vZ(aK)[i]; //todo: a remplacer

                // ecart constate
                Pt2dr D = vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z);

                //todo : strategie d'elimination d'observations / ou ponderation

                // estimation des derivees partielles

                double a0 = slave(aK)->vP[0];
                double a1 = slave(aK)->vP[1];
                double a2 = slave(aK)->vP[2];
                double b0 = slave(aK)->vP[3];
                double b1 = slave(aK)->vP[4];
                double b2 = slave(aK)->vP[5];

                Pt2dr vdZ  = Pt2dr(1./dZ,1./dZ)   * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z+ dZ)-D);
                Pt2dr vdA0 = Pt2dr(1./dA0,1./dA0) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0+dA0,a1,a2,b0,b1,b2)-D);
                Pt2dr vdB0 = Pt2dr(1./dB0,1./dB0) * (vCamPair[aK]->compute2DGroundDifference(ptImgMaster,ptImgSlave,Z,a0,a1,a2,b0+dB0,b1,b2)-D);

                _N(0,2*i) = vdA0.x;
                _N(1,2*i) = vdB0.x;
                _N(2+i,2*i) = vdZ.x;

                _N(0,2*i+1) = vdA0.y;
                _N(1,2*i+1) = vdB0.y;
                _N(2+i,2*i+1) = vdZ.y;

                _Y(0,2*i) = D.x;
                _Y(0,2*i+1) = D.y;
            }
            // Equation de stabilisation
            {
                // A0 proche de 0
                _N(0,2*cpt) = 1;
                _Y(0,2*cpt) = 0-slave(aK)->vP[0];
                // B0 proche de 0
                _N(1,2*cpt+1) = 1;
                _Y(0,2*cpt+1) = 0-slave(aK)->vP[3];
                // Moyenne alti
                double altiMoyenne = 0.;
                for(size_t i=0;i<cpt;++i)
                {
                    _N(2+i,2*cpt+2)=1;
                    altiMoyenne += vZ(aK)[i]; //todo: a remplacer
                }
                _Y(0,2*cpt+2) = zMoy-altiMoyenne/cpt;
            }
        }
        std::cout << "before solve"<<std::endl;

        solve();

        return launchNewIter(iniRMS, numObs);
    }


    ~RefineModelTransBasic()
    {
    }
};

#endif

//! Implementation basique (sans suppression des inconnues auxiliaires)
class RefineModelBasicSansZ: public RefineModelAbs
{

public:
    RefineModelBasicSansZ(std::string const &aPattern):RefineModelAbs(aPattern)
    {
    }

    void addObs(const ElMatrix<double> &obs, const double p, const double res)
    {
        //construction iterative de la matrice normale
        _N += (obs.transpose()*obs)*p;  //il existe certainement une norme ou une facon plus elegante de l'ecrire ...
        //idem pour Y
        _Y += obs.transpose()*res*p;
    }

    void solve()
    {
        ElMatrix<double> inv = gaussj(_N);
        std::cout << "Matrix inv:"<<std::endl;
        printMatrix(inv);
        ElMatrix<double> sol = inv*_Y;

        /*
         std::cout << "Matrice sol:"<<std::endl;
         printMatrix(sol);
         */
        //std::cout << "SOL_NORM = " << sol.NormC(2) << std::endl;

        map<int, AffCamera *>::const_iterator iter = mapCameras.begin();
        for (; iter != mapCameras.end();++iter)
        {
            iter->second->updateParams(sol);
        }

        //TODO
        // 3D coord update


    }

    //! compute the observation matrix for one iteration
    bool computeObservationMatrix()
    {
        size_t numUnk = 6;
        size_t numCam = mapCameras.size();

        //int cpt = 0;
        //for (size_t aK=0; aK < mNbPair; aK++) cpt += vCamPair[aK]->vZ.size();
        //int numObs = 2*cpt;
        int numObs = 2*vObs.size();
        double iniRMS = std::sqrt(sumRes()/numObs);
        std::cout << "RMS_ini = " << iniRMS << std::endl;

        double dA0 = 0.5;
        double dA1 = 0.01;
        double dA2 = 0.01;
        double dB0 = 0.5;
        double dB1 = 0.01;
        double dB2 = 0.01;

        _N = ElMatrix<double>(numUnk*numCam, numUnk*numCam/*+6*/,0.);
        _Y = ElMatrix<double>(1, numUnk*numCam,0.);

        //pour chaque obs (ligne), y compris les eq de stabilisation
        //for( toutes les obs )
        for (size_t aK=0; aK < vObs.size(); aK++)
        {
            TiePoint* aTP = vObs[aK];

            std::vector <ImageMeasure> vMes = aTP->vImgMeasure;

            for(size_t bK=0; bK < vMes.size();++bK)
            {
                map<int, AffCamera *>::iterator iter;
                iter = mapCameras.find(vMes[bK].idx);

                Pt2dr D = aTP->computeImageDifference(bK);
                double ecart2 = square_euclid(D);

                double pdt = 1./sqrt(1. + ecart2);

                //todo : strategie d'elimination d'observations / ou ponderation

                ElMatrix<double> obs(numUnk,1,0.);

                // estimation des derivees partielles
                AffCamera* cam = iter->second;

                double a0 = cam->vP[0];
                double a1 = cam->vP[1];
                double a2 = cam->vP[2];
                double b0 = cam->vP[3];
                double b1 = cam->vP[4];
                double b2 = cam->vP[5];

                Pt2dr vdA0 = Pt2dr(1./dA0,1./dA0) * (aTP->computeImageDifference(bK,a0+dA0,a1,a2,b0,b1,b2)-D);
                Pt2dr vdA1 = Pt2dr(1./dA1,1./dA1) * (aTP->computeImageDifference(bK,a0,a1+dA1,a2,b0,b1,b2)-D);
                Pt2dr vdA2 = Pt2dr(1./dA2,1./dA2) * (aTP->computeImageDifference(bK,a0,a1,a2+dA2,b0,b1,b2)-D);
                Pt2dr vdB0 = Pt2dr(1./dB0,1./dB0) * (aTP->computeImageDifference(bK,a0,a1,a2,b0+dB0,b1,b2)-D);
                Pt2dr vdB1 = Pt2dr(1./dB1,1./dB1) * (aTP->computeImageDifference(bK,a0,a1,a2,b0,b1+dB1,b2)-D);
                Pt2dr vdB2 = Pt2dr(1./dB2,1./dB2) * (aTP->computeImageDifference(bK,a0,a1,a2,b0,b1,b2+dB2)-D);

                obs(0,0) = vdA0.x;
                obs(1,0) = vdA1.x;
                obs(2,0) = vdA2.x;
                obs(3,0) = vdB0.x;
                obs(4,0) = vdB1.x;
                obs(5,0) = vdB2.x;

                addObs(obs,pdt,0.-D.x);
                //ajout
                //if((D.x<2)&&(D.y<2)) {addObs(obs,1/std::sqrt(1+D.x*D.x),D.x);}
                //fin ajout
                obs(0,0) = vdA0.y;
                obs(1,0) = vdA1.y;
                obs(2,0) = vdA2.y;
                obs(3,0) = vdB0.y;
                obs(4,0) = vdB1.y;
                obs(5,0) = vdB2.y;

                addObs(obs,pdt,0.-D.y);
            }
        }
        std::cout << "before solve"<<std::endl;

        solve();

        return launchNewIter(iniRMS, numObs);
    }

    ~RefineModelBasicSansZ()
    {
    }
};

int RefineModel_main(int argc, char **argv)
{
    std::string aPat; // GRID files pattern

    ElInitArgMain
    (
         argc, argv,
         LArgMain() << EAMC(aPat,"GRID files pattern"),
         LArgMain()
    );

    ELISE_fp::MkDirSvp("refine");

    RefineModelBasicSansZ model(aPat);

    bool ok= (model.nObs() > 3);
    for(size_t iter = 0; (iter < 100) & ok; iter++)
    {
        std::cout <<"iter="<<iter<<std::endl;
        ok = model.computeObservationMatrix();
    }

    return EXIT_SUCCESS;
}

int AddAffinity_main(int argc, char **argv)
{
    std::string aNameFile; // tie-points file
    bool addNoise = false;

    ElInitArgMain
    (
         argc, argv,
         LArgMain() << EAMC(aNameFile,"tie-points file"),
         LArgMain() << EAM(addNoise, "Noise", true, "Add noise (def=false)" )
    );

    std::vector <DigeoPoint> aList;
    DigeoPoint::readDigeoFile(aNameFile, true, aList);
    //TODO: handle versions

    std::cout << "pts nb: " << aList.size() << endl;

    double A0, A1, A2, B0, B1, B2;
    A0 = 0.1f;
    A1 = 0.999999985;
    A2 = -0.000174533;
    B0 = 0.05;
    B1 = 0.000174533;
    B2 = 0.999999985;

    for (size_t aK = 0 ; aK< aList.size(); aK++)
    {
        DigeoPoint pt = aList[aK];

        //std::cout << "pt avt " << pt.x << " " << pt.y << std::endl;
        Pt2dr ptt(A0 + A1 * pt.x + A2 * pt.y, B0 + B1 * pt.x + B2 * pt.y);

        if (addNoise)
        {
            Pt2dr aNoise(NRrandC(),NRrandC());
            ptt += aNoise;
        }

        //std::cout << "pt apr " << ptt.x << " " << ptt.y << endl;

        aList[aK].x = ptt.x;
        aList[aK].y = ptt.y;
    }

    std::string aOut = StdPrefixGen(aNameFile)+ "_transf.dat";
    DigeoPoint::writeDigeoFile(aOut, aList, 0, true);

    return EXIT_SUCCESS;
}
