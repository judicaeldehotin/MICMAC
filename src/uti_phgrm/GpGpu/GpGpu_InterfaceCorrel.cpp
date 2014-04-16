#include "GpGpu/GpGpu_InterCorrel.h"

/// \brief Constructeur GpGpuInterfaceCorrel
GpGpuInterfaceCorrel::GpGpuInterfaceCorrel():
    CSimpleJobCpuGpu(true),
     NoMasked(false),
     copyInvParam(false)

{
    for (int s = 0;s<NSTREAM;s++)
        checkCudaErrors( cudaStreamCreate(GetStream(s)));

    CreateJob();
}

GpGpuInterfaceCorrel::~GpGpuInterfaceCorrel()
{
    for (int s = 0;s<NSTREAM;s++)
        checkCudaErrors( cudaStreamDestroy(*(GetStream(s))));

}
void GpGpuInterfaceCorrel::ReallocHostData(uint interZ,ushort idBuff)
{
    _data2Cor.ReallocHostData(interZ,_param[idBuff],idBuff);
}

uint2 &GpGpuInterfaceCorrel::DimTerrainGlob()
{
    return _m_DimTerrainGlob;
}

std::vector<cellules> &GpGpuInterfaceCorrel::MaskVolumeBlock()
{
    return _m_MaskVolumeBlock;
}

uint GpGpuInterfaceCorrel::InitCorrelJob(int Zmin, int Zmax)
{

    uint interZ = min(INTERZ, abs(Zmin - Zmax));

    if(UseMultiThreading())
    {
        ResetIdBuffer();
        SetPreComp(true);
    }

    return interZ;
}

/// \brief Initialisation des parametres constants
void GpGpuInterfaceCorrel::SetParameter(int nbLayer , ushort2 dRVig , uint2 dimImg, float mAhEpsilon, uint samplingZ, int uvINTDef, ushort nClass )
{

    if(!copyInvParam || _param[0].invPC.nbImages != (uint)nbLayer || _param[1].invPC.nbImages != (uint)nbLayer)
    {
        copyInvParam = true;
        _param[0].invPC.SetParamInva( dRVig * 2 + 1,dRVig, dimImg, mAhEpsilon, samplingZ, uvINTDef, nbLayer,nClass);
        _param[1].invPC.SetParamInva( dRVig * 2 + 1,dRVig, dimImg, mAhEpsilon, samplingZ, uvINTDef, nbLayer,nClass);
        CopyParamInvTodevice(_param[0]);
    }
}

void GpGpuInterfaceCorrel::BasicCorrelation(uint ZInter)
{

    // Re-allocation les structures de donn�es si elles ont �t� modifi�es

    Data().ReallocDeviceData(Param(GetIdBuf()));

    // copie des donnees du host vers le device

    Data().copyHostToDevice(Param(GetIdBuf()));

    // Indique que la copie est termin�e pour le thread de calcul des projections
    SetPreComp(true);

    // COPIE Les parametres � Virer!!
    //CopyParamTodevice(_param[GetIdBuf()]);

    //Param(GetIdBuf()).CopyParamToDevice();

    // Lancement du calcul de correlation
    CorrelationGpGpu(GetIdBuf());

    // relacher la texture de projection

    Data().UnBindTextureProj();

    // Lancement du calcul de multi-correlation
    MultiCorrelationGpGpu(GetIdBuf());

    // Copier les resultats de calcul des couts du device vers le host!

    Data().CopyDevicetoHost(GetIdBuf());

}

cudaStream_t* GpGpuInterfaceCorrel::GetStream( int stream )
{
    return &(_stream[stream]);
}

void GpGpuInterfaceCorrel::threadCompute()
{
    ResetIdBuffer();
    while (true)
    {
        if (GetCompute())
        {
            uint interZ = GetCompute();
            SetCompute(0);

            while(Param(GetIdBuf()).invPC.nbImages > 4096)
                boost::this_thread::sleep(boost::posix_time::microsec(1));

            BasicCorrelation(interZ);

            while(GetDataToCopy());

            SwitchIdBuffer();

            SetDataToCopy(interZ);
        }
        else
            boost::this_thread::sleep(boost::posix_time::microsec(5));
    }
}

void GpGpuInterfaceCorrel::freezeCompute()
{
    SetDataToCopy(0);
    SetCompute(0);
    SetPreComp(false);
    //KillJob();
}

void GpGpuInterfaceCorrel::IntervalZ(uint &interZ, int anZProjection, int aZMaxTer)
{
    uint intZ = (uint)abs(aZMaxTer - anZProjection );
    if (interZ >= intZ  &&  anZProjection != (aZMaxTer - 1) )
        interZ = intZ;
}

float *GpGpuInterfaceCorrel::VolumeCost(ushort id)
{
    return UseMultiThreading() ? Data().HostVolumeCost(id) : Data().HostVolumeCost(0);
}

bool GpGpuInterfaceCorrel::TexturesAreLoaded()
{
    return _TexturesAreLoaded;
}

void GpGpuInterfaceCorrel::SetTexturesAreLoaded(bool load)
{
    _TexturesAreLoaded = load;
    NoMasked = false;
}

void GpGpuInterfaceCorrel::CorrelationGpGpu(ushort idBuf,const int s )
{
    LaunchKernelCorrelation(s, *(GetStream(s)),_param[idBuf], _data2Cor);
    //LaunchKernelCorrelationZ(s,_param[idBuf],_data2Cor);
}

void GpGpuInterfaceCorrel::MultiCorrelationGpGpu(ushort idBuf, const int s)
{
    LaunchKernelMultiCorrelation( *(GetStream(s)),_param[idBuf],  _data2Cor);
}

pCorGpu& GpGpuInterfaceCorrel::Param(ushort idBuf)
{
    return _param[idBuf];
}

void GpGpuInterfaceCorrel::signalComputeCorrel(uint dZ)
{
    SetPreComp(false);
    SetCompute(dZ);
}

SData2Correl &GpGpuInterfaceCorrel::Data()
{
    return _data2Cor;
}
