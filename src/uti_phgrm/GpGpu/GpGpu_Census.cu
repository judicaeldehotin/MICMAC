
#include "GpGpu/GpGpu_CommonHeader.h"
//#include "GpGpu/GpGpu_TextureTools.cuh"
#include "GpGpu/GpGpu_Interface_Census.h"

// Algorithme Correlation multi echelle sur ligne epipolaire

// Donn�es :
//  - 2 images avec diff�rents niveaux de floutage

//
// * Pr�-calcul et param�tres                                   |       GPU
// -------------------------------------------------------------|----------------------------------
// - Tableau de parcours des vignettes                          >>      constant 3d data short2
// - poids des echelles                                         >>      constant 2d data ???
// - Tableau du ZMin et ZMax de chaque coordonn�es terrain      >>      global 2D data short2
// - les offsets Terrain <--> Image Epi                         >>      constant 2 x int2
// - le masque erod� de l'image 1                               >>      1 texture pixel
// - 2 images x N echelles                                      >>      2 textures layered float


//
// Phase mNbByPix // pas utilise en GPU


/*  CPU
 *
 *  pour chaque
 *      - calcul des images interpol�es pour l'image 1
 *      - mise en vecteur des images interpol�es
 *      - Precalcul somme et somme quad
 *      - Parcour du terrain
 *      - Calcul des images interpol�
 *      - Parcours des Z
 *          - Calcul de la projection image 1
 *          - Calcul de la correlation Quick_MS_CorrelBasic_Center
 *              - pour chaque echelle
 *                  - Calcul de correlation
 *
 *      - set cost dans la matrice de regularisation
 */


///
static __constant__ constantParameterCensus     cParamCencus;

extern "C" void paramCencus2Device( constantParameterCensus &param )
{
  checkCudaErrors(cudaMemcpyToSymbol(cParamCencus, &param, sizeof(constantParameterCensus)));
}

texture< float,	cudaTextureType2DLayered >      texture_ImageEpi_00;
texture< float,	cudaTextureType2DLayered >      texture_ImageEpi_01;
texture< pixel,	cudaTextureType2DLayered >      Texture_Masq_Erod;

extern "C" textureReference& texture_ImageEpi(int nEpi){return nEpi == 0 ? texture_ImageEpi_00 : texture_ImageEpi_01;}

extern "C" textureReference* pTexture_ImageEpi(int nEpi){return nEpi == 0 ? &texture_ImageEpi_00 : &texture_ImageEpi_01;}

extern "C" textureReference& texture_Masq_Erod(){return Texture_Masq_Erod;}

__device__
inline    bool GET_Val_BIT(const U_INT1 * aData,int anX)
{
    return (aData[anX/8] >> (7-anX %8) ) & 1;
}

__device__
inline    bool okErod(uint3 pt)
{
    // TODO peut etre simplifier % et division
    pixel mask8b = tex2DLayered(Texture_Masq_Erod,pt.x/8 + 0.5f,pt.y + 0.5f ,pt.z);

    return (mask8b >> (7-pt.x %8) ) & 1;
}

__device__
inline    texture< float,	cudaTextureType2DLayered >  getTexture(ushort iDi)
{
    return iDi == 0 ? texture_ImageEpi_00 : texture_ImageEpi_01;
}

__device__
inline    float getValImage(uint2 pt,ushort iDi,ushort nScale)
{
    return tex2DLayered(getTexture(iDi),pt.x + 0.5f,pt.y + 0.5f ,nScale);
}

__device__
inline    void correl(uint2 pt,ushort iDi)
{
    float aGlobSom1 = 0;
    float aGlobSom2 = 0;
    float aGlobPds  = 0;

    for (int aKS=0 ; aKS< cParamCencus._NBScale ; aKS++)
    {
        float   aSom1   = 0;
        float   aSom2   = 0;
        short2 *aVP     = cParamCencus.w[aKS];
        ushort  aNbP    = cParamCencus.sizeW[aKS];
        float  aPdsK    = cParamCencus.poids[aKS];

        for (int aKP=0 ; aKP<aNbP ; aKP++)
        {
            const short2 aP = aVP[aKP];
            //const uint ptV  = make_uint2(pt.x+aP.x,)
            float aV = getValImage(pt+aP,iDi,aKS);
            aSom1 += aV;
            aSom2 += aV*aV;
        }
        aGlobSom1 += aSom1 * aPdsK;
        aGlobSom2 += aSom2 * aPdsK;
        aGlobPds += aPdsK * aNbP;

//        mData1[aKS][aYGlob][aXGlob] = aGlobSom1 / aGlobPds;
//        mData2[aKS][aYGlob][aXGlob] = aGlobSom2 / aGlobPds;
    }
}

__device__
inline    float CorrelBasic_Center(
    const uint2 & aPG1,
    const uint2 & aPG2,
    float ***  aSom1,
    float ***  aSom11,
    float ***  aSom2,
    float ***  aSom22,
    int  aPx2,
    bool ModeMax)
{
    float aMaxCor = -1;
    float aCovGlob = 0;
    float aPdsGlob = 0;
    int aNbScale = cParamCencus._NBScale;
    for (int aKS=0 ; aKS< aNbScale ; aKS++)
    {
         bool   aLast   = (aKS==(aNbScale-1));
         short2*aVP     = cParamCencus.w[aKS];
         float  aPds    = cParamCencus.poids[aKS];
         float  aCov    = 0;
         ushort  aNbP    = cParamCencus.sizeW[aKS];

         float ** anIm1; //= aVBOI1[aKS]->data();
         float ** anIm2;// = aVBOI2[aKS]->data();

         aPdsGlob += aPds * aNbP;
         for (int aKP=0 ; aKP<aNbP ; aKP++)
         {
             const short2 aP = aVP[aKP];
             aCov += anIm1[aP.y][aP.x]*anIm2[aP.y][aP.x+aPx2];
         }

         aCovGlob += aCov * aPds;

         if (ModeMax || aLast)
         {
             float aM1  = aSom1 [aKS][aPG1.y][aPG1.x];
             float aM2  = aSom2 [aKS][aPG2.y][aPG2.x];
             float aM11 = aSom11[aKS][aPG1.y][aPG1.x] - aM1*aM1;
             float aM22 = aSom22[aKS][aPG2.y][aPG2.x] - aM2*aM2;
             float aM12 = aCovGlob / aPdsGlob - aM1 * aM2;

             if (ModeMax)
             {
                float aCor = (aM12 * abs(aM12)) /max(cParamCencus.anEpsilon,aM11*aM22);
                aMaxCor = max(aMaxCor,aCor);
             }
             else
                return aM12 / sqrt(max(cParamCencus.anEpsilon,aM11*aM22));
        }

    }
    return (aMaxCor > 0) ? sqrt(aMaxCor) : - sqrt(-aMaxCor) ;
}

__global__
void projectionMasqImage(float * dataPixel,uint3 dTer)
{

    if(blockIdx.x > cParamCencus._dimTerrain.y || blockIdx.y > cParamCencus._dimTerrain.x)
        return;

    const uint3 pt = make_uint3(blockIdx.x,blockIdx.y,blockIdx.z);

    float valImage = tex2DLayered(pt.z == 0 ? texture_ImageEpi_00 : texture_ImageEpi_01 ,pt.x + 0.5f,pt.y + 0.5f ,0);

    dataPixel[to1D(pt,dTer)] = okErod(pt) ? valImage/(32768.f) : 0;
}

extern "C" void LaunchKernelCorrelationCensus(dataCorrelMS &data,constantParameterCensus &param)
{
    dim3	threads( 1, 1, 1);
    dim3	blocks(param._dimTerrain.y , param._dimTerrain.x, 2);

    CuHostData3D<float>     hData;
    CuDeviceData3D<float>   dData;

    uint3 dTer  = make_uint3(param._dimTerrain.y , param._dimTerrain.x,2);
    uint2 dTer2 = make_uint2(dTer);

    hData.Malloc(dTer2,2);
    dData.Malloc(dTer2,2);
    hData.Fill(0.f);
    dData.Memset(0);

    projectionMasqImage<<<blocks, threads>>>(dData.pData(),dTer);

    dData.CopyDevicetoHost(hData);

    GpGpuTools::Array1DtoImageFile(hData.pData()    ,"ET_HOP_0.pmg",hData.GetDimension());
    GpGpuTools::Array1DtoImageFile(hData.pLData(1)  ,"ET_HOP_1.pmg",hData.GetDimension());
}
