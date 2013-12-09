#include "GpGpu/GpGpu_ParamCorrelation.cuh"
#include "GpGpu/GpGpu_TextureTools.cuh"
#include "GpGpu/GpGpu_TextureCorrelation.cuh"
#include "GpGpu/SData2Correl.h"


/// \file       GpGpuCudaCorrelation.cu
/// \brief      Kernel
/// \author     GC
/// \version    0.2
/// \date       mars 2013

static __constant__ invParamCorrel  invPc;

extern "C" void CopyParamInvTodevice( pCorGpu param )
{
  checkCudaErrors(cudaMemcpyToSymbol(invPc, &param.invPC, sizeof(invParamCorrel)));
}


/// \fn template<int TexSel> __global__ void correlationKernel( uint *dev_NbImgOk, float* cachVig, uint2 nbActThrd)
/// \brief Kernel fonction GpGpu Cuda
/// Calcul les vignettes de correlation pour toutes les images
///
template<int TexSel> __global__ void correlationKernel( uint *dev_NbImgOk, float* cachVig, uint2 nbActThrd,HDParamCorrel HdPc)
{

  extern __shared__ float cacheImg[];

  // Coordonn�es du terrain global avec bordure // __umul24!!!! A voir

  const uint2 ptHTer = make_uint2(blockIdx) * nbActThrd + make_uint2(threadIdx);

  // Si le processus est hors du terrain, nous sortons du kernel

  if (oSE(ptHTer,HdPc.dimDTer)) return;

  const float2 ptProj = GetProjection<TexSel>(ptHTer,invPc.sampProj,blockIdx.z);

  uint pitZ,modZ;

  if (oI(ptProj,0))

      return;

  else
  {
      pitZ  = blockIdx.z / invPc.nbImages;

      modZ  = blockIdx.z - pitZ * invPc.nbImages;

      cacheImg[threadIdx.y*BLOCKDIM + threadIdx.x] = GetImageValue(ptProj,modZ);
  }

  __syncthreads();

  const int2 ptTer = make_int2(ptHTer) - make_int2(invPc.rayVig);

  // Nous traitons uniquement les points du terrain du bloque ou Si le processus est hors du terrain global, nous sortons du kernel

  // Simplifier!!!
  if (oSE(threadIdx, nbActThrd + invPc.rayVig) || oI(threadIdx , invPc.rayVig) || oSE( ptTer, HdPc.dimTer) || oI(ptTer, 0))
    return;

  if(tex2D(TexS_MaskGlobal, ptTer.x + HdPc.rTer.pt0.x , ptTer.y + HdPc.rTer.pt0.y) == 0) return;

  const short2 c0	= make_short2(threadIdx) - invPc.rayVig;
  const short2 c1	= make_short2(threadIdx) + invPc.rayVig;

  // Intialisation des valeurs de calcul
  float aSV = 0.0f, aSVV = 0.0f;
  short2 pt;

  #pragma unroll // ATTENTION PRAGMA FAIT AUGMENTER LA quantit� MEMOIRE des registres!!!
  for (pt.y = c0.y ; pt.y <= c1.y; pt.y++)
  {
        const int pic = pt.y*BLOCKDIM;
      #pragma unroll
      for (pt.x = c0.x ; pt.x <= c1.x; pt.x++)
      {
          const float val = cacheImg[pic+ pt.x];	// Valeur de l'image
          //        if (val ==  cH.floatDefault) return;
          aSV  += val;          // Somme des valeurs de l'image cte
          aSVV += (val*val);	// Somme des carr�s des vals image cte
      }
  }

  aSV   = fdividef(aSV,(float)invPc.sizeVig );

  aSVV  = fdividef(aSVV,(float)invPc.sizeVig );

  aSVV -=	(aSV * aSV);

  if ( aSVV <= invPc.mAhEpsilon) return;

  aSVV =	rsqrtf(aSVV); // racine carre inverse

  const uint pitchCache = blockIdx.z * HdPc.sizeCach + ptTer.x * invPc.dimVig.x;

  const uint pitchCachY = ptTer.y * invPc.dimVig.y ;

#pragma unroll
  for ( pt.y = c0.y ; pt.y <= c1.y; pt.y++)
    {
      float* cImg = cacheImg + pt.y*BLOCKDIM;
      float* cVig = cachVig + pitchCache + (pitchCachY + (pt.y - c0.y))* HdPc.dimCach.x - c0.x;
#pragma unroll
      for ( pt.x = c0.x ; pt.x <= c1.x; pt.x++)
        cVig[ pt.x ] = (cImg[pt.x] -aSV)*aSVV;

    }

  const int ZPitch	= pitZ * HdPc.sizeTer;

  const int idN		= ZPitch + to1D(ptTer,HdPc.dimTer);

  atomicAdd( &dev_NbImgOk[idN], 1U);

}

/// \brief Fonction qui lance les kernels de correlation
extern "C" void	 LaunchKernelCorrelation(const int s,cudaStream_t stream,pCorGpu &param,SData2Correl &data2cor)
{

    dim3	threads( BLOCKDIM, BLOCKDIM, 1);
    uint2	thd2D		= make_uint2(threads);
    uint2	nbActThrd	= thd2D - 2 * param.invPC.rayVig;
    uint2	block2D		= iDivUp(param.HdPc.dimDTer,nbActThrd);
    dim3	blocks(block2D.x , block2D.y, param.invPC.nbImages * param.ZCInter);

  switch (s)
    {
    case 0:
      correlationKernel<0><<<blocks, threads, BLOCKDIM * BLOCKDIM * sizeof(float), stream>>>( data2cor.DeviVolumeNOK(0), data2cor.DeviVolumeCache(0), nbActThrd,param.HdPc);
      getLastCudaError("Basic Correlation kernel failed stream 0");
      break;
    case 1:
      correlationKernel<1><<<blocks, threads, BLOCKDIM * BLOCKDIM* sizeof(float), stream>>>( data2cor.DeviVolumeNOK(1), data2cor.DeviVolumeCache(1), nbActThrd,param.HdPc);
      getLastCudaError("Basic Correlation kernel failed stream 1");
      break;
    }
}

/// \brief Kernel Calcul "rapide"  de la multi-correlation en utilisant la formule de Huygens n utilisant pas des fonctions atomiques
__global__ void multiCorrelationKernel(float *dTCost, float* cacheVign, uint* dev_NbImgOk, uint2 nbActThr,HDParamCorrel HdPc)
{

  __shared__ float aSV [ SBLOCKDIM ][ SBLOCKDIM ];          // Somme des valeurs
  __shared__ float aSVV[ SBLOCKDIM  ][ SBLOCKDIM ];         // Somme des carr�s des valeurs
  __shared__ float resu[ SBLOCKDIM/2 ][ SBLOCKDIM/2 ];		// resultat
  __shared__ ushort nbIm[ SBLOCKDIM/2][ SBLOCKDIM/2 ];		// nombre d'images correcte

  // coordonn�es des threads
  const uint2 t = make_uint2(threadIdx);

  aSV [t.y][t.x]        = 0.0f;

  aSVV[t.y][t.x]        = 0.0f;

  resu[t.y/2][t.x/2]	= 0.0f;

  nbIm[t.y/2][t.x/2]	= 0;

  if ( oSE( t, nbActThr))	return; // si le thread est inactif, il sort

  // Coordonn�es 2D du cache vignette
  const uint2 ptCach = make_uint2(blockIdx) * nbActThr + t;

  // Si le thread est en dehors du cache
  if ( oSE(ptCach, HdPc.dimCach))	return;

  const uint2	ptTer	= ptCach / invPc.dimVig; // Coordonn�es 2D du terrain

  if(!tex2D(TexS_MaskGlobal, ptTer.x + HdPc.rTer.pt0.x , ptTer.y + HdPc.rTer.pt0.y)) return;

  const uint	iTer	= blockIdx.z * HdPc.sizeTer + to1D(ptTer, HdPc.dimTer);     // Coordonn�es 1D dans le terrain avec prise en compte des differents Z

  const uint2   thTer	= t / invPc.dimVig;                                        // Coordonn�es 2D du terrain dans le repere des threads

  //if(aEq(t,thTer * cH.dimVig))
  nbIm[thTer.y][thTer.x] = (ushort)dev_NbImgOk[iTer];

  //__syncthreads();

  if ( nbIm[thTer.y][thTer.x]  < 2) return;

  const uint pitLayerCache  = blockIdx.z * HdPc.sizeCachAll + to1D( ptCach, HdPc.dimCach );	// Taille du cache vignette pour une image
  //const uint pit  = blockIdx.z * cH.nbImages;

 #pragma unroll
  for(uint i = 0;i< HdPc.sizeCachAll;i+=HdPc.sizeCach)
  //for(uint l = pit ;l< pit + cH.nbImages;l++)
    {
      const float val  = cacheVign[pitLayerCache  + i];
      //const float val  = tex2DLayered( TexL_Cache,ptCach.x , ptCach.y,l);

      //if(val!= cH.floatDefault) A verifier si pas d'influence
        //{
          // Coordonn�es 1D du cache vignette

          aSV[t.y][t.x]   += val;
          aSVV[t.y][t.x]  += val * val;
        //}
    }

  __syncthreads();

  atomicAdd(&(resu[thTer.y][thTer.x]),aSVV[t.y][t.x] - fdividef(aSV[t.y][t.x] * aSV[t.y][t.x],(float)nbIm[thTer.y][thTer.x]));

  if (!aEq(t - thTer*invPc.dimVig,0)) return;

  __syncthreads();

  // Normalisation pour le ramener a un equivalent de 1-Correl
  const float cost = fdividef( resu[thTer.y][thTer.x], (float)( nbIm[thTer.y][thTer.x] -1.0f) * (invPc.sizeVig));

  dTCost[iTer] = 1.0f - max (-1.0, min(1.0f,1.0f - cost));

}


/// \brief Fonction qui lance les kernels de multi-Correlation n'utilisant pas des fonctions atomiques
extern "C" void LaunchKernelMultiCorrelation(cudaStream_t stream, pCorGpu &param, SData2Correl &dataCorrel)
{

    //-------------	calcul de dimension du kernel de multi-correlation NON ATOMIC ------------
    uint2	nbActThr	= SBLOCKDIM - make_uint2( SBLOCKDIM % param.invPC.dimVig.x, SBLOCKDIM % param.invPC.dimVig.y);
    dim3	threads(SBLOCKDIM, SBLOCKDIM, 1);
    uint2	block2D	= iDivUp(param.HdPc.dimCach,nbActThr);
    dim3	blocks(block2D.x,block2D.y,param.ZCInter);

    multiCorrelationKernel<<<blocks, threads, 0, stream>>>(dataCorrel.DeviVolumeCost(0), dataCorrel.DeviVolumeCache(0), dataCorrel.DeviVolumeNOK(0), nbActThr,param.HdPc);
    getLastCudaError("Multi-Correlation NON ATOMIC kernel failed");

}
