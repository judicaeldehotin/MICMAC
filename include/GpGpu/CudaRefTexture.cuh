#ifndef CUDAREFTEXTURE
#define CUDAREFTEXTURE

// ATTENTION : erreur de compilation avec l'option cudaReadModeNormalizedFloat et l'utilisation de la fonction tex2DLayered
texture< pixel,	cudaTextureType2D >			TexS_MaskTer;
texture< float,	cudaTextureType2DLayered >	TexL_Images;
TexFloat2Layered							TexL_Proj_00;
TexFloat2Layered							TexL_Proj_01;
TexFloat2Layered							TexL_Proj_02;
TexFloat2Layered							TexL_Proj_03;

template<int TexSel> __device__ __host__ TexFloat2Layered TexFloat2L();

template<> __device__ __host__ TexFloat2Layered TexFloat2L<0>() { return TexL_Proj_00; };
template<> __device__ __host__ TexFloat2Layered TexFloat2L<1>() { return TexL_Proj_01; };
template<> __device__ __host__ TexFloat2Layered TexFloat2L<2>() { return TexL_Proj_02; };
template<> __device__ __host__ TexFloat2Layered TexFloat2L<3>() { return TexL_Proj_03; };

inline __device__ float GetImageValue(float2 ptProj, uint mZ)
{
#if	INTERPOLA == NEAREST
	return tex2DLayered( TexL_Images,ptProj.x , ptProj.y,mZ);
#elif	INTERPOLA == LINEARINTER
	return tex2DLayeredPt( TexL_Images, ptProj, mZ);
#elif	INTERPOLA == BICUBIC
	return tex2DFastBicubic<float,float>(TexL_Images, ptProj.x, ptProj.y, dimImg,mZ);
#endif
}

template<int TexSel> inline  __device__ float2 GetProjection(uint2 ptTer, uint sampProj, uint BZ)
{
#if (SAMPLETERR == 1)
	return tex2DLayeredPt(TexFloat2L<TexSel>(),ptTer,BZ);
#else
	return tex2DLayeredPt(TexFloat2L<TexSel>(),ptTer,sampProj,BZ);
#endif
}


extern "C" textureReference& getMask(){	return TexS_MaskTer;}
extern "C" textureReference& getImage(){ return TexL_Images;}
extern "C" textureReference& getProjection(int TexSel)
{
	switch (TexSel)
	{
	case 0:
		return TexL_Proj_00;
	case 1:
		return TexL_Proj_01;
	case 2:
		return TexL_Proj_02;
	case 3:
		return TexL_Proj_03;
	default:
		return TexL_Proj_00;
	}								
}

#endif /*CUDAREFTEXTURE*/ 
