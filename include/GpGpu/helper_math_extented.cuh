#pragma once

#include <cuda_runtime.h>
#include <helper_functions.h>
#include <helper_math.h>
#include <helper_cuda.h>

#ifdef __GNUC__
#define SUPPRESS_NOT_USED_WARN __attribute__ ((unused))
#else
#define SUPPRESS_NOT_USED_WARN
#endif

#define NEGARECT Rect(-1,-1,-1,-1)

/// \struct Rect
/// \brief Cette structure represente un rectangle definie par deux points
struct Rect
{
    /// \brief point haut et gauche du rectangle
	int2 pt0;
    /// \brief point bas et droite du rectangle
	int2 pt1;

	__device__ __host__ Rect(){};

    /// \brief Definie les points du rectangle avec des points entiers
    /// \param p0 : point haut et gauche du rectangle
    /// \param p1 : point bas et droite du rectangle
	Rect(int2 p0, int2 p1)
	{
		pt0 = p0;
		pt1 = p1;
    }

    /// \brief Definie les points du rectangle avec des points entiers non signes
    /// \param p0 : point haut et gauche du rectangle
    /// \param p1 : point bas et droite du rectangle
	Rect(uint2 p0, uint2 p1)
	{

		pt0 = make_int2(p0);
		pt1 = make_int2(p1);
    }

    /// \brief Definie les points du rectangle avec des 4 entiers, fonction host et device
    /// \param p0x : abscisse du point haut et gauche du rectangle
    /// \param p0y : ordonnee du point haut et gauche du rectangle
    /// \param p1x : abscisse du point bas et droite du rectangle
    /// \param p1y : ordonnee du point bas et droite du rectangle
	__device__ __host__ Rect(int p0x,int p0y,int p1x,int p1y)
	{

		pt0 = make_int2(p0x,p0y);
		pt1 = make_int2(p1x,p1y);
    }

    /// \brief Renvoie la dimension du rectangle
	uint2 dimension()
	{
		return make_uint2(pt1-pt0);
    }

    bool operator==(const Rect &other) const {
        return ( this->pt0.x == other.pt0.x && this->pt0.y == other.pt0.y && this->pt1.x == other.pt1.x && this->pt1.y == other.pt1.y);
    }

#ifdef __cplusplus

	void out()
	{
		std::cout << "(" << pt0.x << "," <<  pt0.y << ")" << " -> (" << pt1.x << "," <<  pt1.y << ") ";
	}

#endif
};

static int iDivUp(int a, int b)
{
	return (a % b != 0) ? (a / b + 1) : (a / b);
}

SUPPRESS_NOT_USED_WARN static uint2 iDivUp(uint2 a, uint b)
{
	return make_uint2(iDivUp(a.x,b),iDivUp(a.y,b));
}

SUPPRESS_NOT_USED_WARN static uint2 iDivUp(uint2 a, uint2 b)
{
	return make_uint2(iDivUp(a.x,b.x),iDivUp(a.y,b.y));
}

SUPPRESS_NOT_USED_WARN static int2 iDivUp(int2 a, uint b)
{
	return make_int2(iDivUp(a.x,b),iDivUp(a.y,b));
}

inline __device__ __host__ uint size(uint2 v)
{
	return v.x * v.y;
}

inline __device__ __host__ uint size(int2 v)
{
	return v.x * v.y;
}

inline __host__ __device__ uint2 operator/(uint2 a, uint2 b)
{
	return make_uint2(a.x / b.x, a.y / b.y);
}

inline __host__ __device__ short diffYX(short2 a)
{
    return a.y  - a.x;
}

inline __host__ __device__ uint2 operator/(uint2 a, int b)
{
	return make_uint2(a.x / b, a.y / b);
}

inline __host__ __device__ int2 operator/(int2 a, uint b)
{
	return make_int2(a.x / b, a.y / b);
}

inline __host__ __device__ int2 operator/(int2 a, uint2 b)
{
	return make_int2(a.x / ((int)(b.x)), a.y / ((int)(b.y)));
}

inline __host__ __device__ float2 operator/(float2 a, uint2 b)
{
	return make_float2(a.x / ((float)(b.x)), a.y / ((float)(b.y)));
}

inline __host__ __device__ uint2 operator*(int2 a, uint2 b)
{
	return make_uint2(a.x * b.x, a.y * b.y);
}

inline __host__ __device__ int2 operator+(int2 a, uint2 b)
{
	return make_int2(a.x + b.x, a.y + b.y);
}

inline __host__ __device__ uint2 make_uint2(dim3 a)
{
	return make_uint2((uint3)a);
}

inline __host__ __device__ int2 make_int2(dim3 a)
{
	return make_int2(a.x,a.y);
}

inline __host__ __device__ short2 make_short2(uint3 a)
{
	return make_short2((short)a.x,(short)a.y);
}

inline __host__ __device__ int2 operator-(const uint3 a, uint2 b)
{
	return make_int2(a.x - b.x, a.y - b.y);
}

inline __host__ __device__ int2 operator-(const int2 a, uint2 b)
{
	return make_int2(a.x - b.x, a.y - b.y);
}

inline __host__ __device__ short2 operator-(short2 a, uint2 b)
{
	return make_short2(a.x - b.x, a.y - b.y);
}


inline __host__ __device__ short2 operator+(short2 a, uint2 b)
{
	return make_short2(a.x + b.x, a.y + b.y);
}

inline __host__ __device__ int2 operator+(const uint3 a, uint2 b)
{
	return make_int2(a.x + b.x, a.y + b.y);
}

inline __host__ __device__ int mdlo(uint a, uint b)
{

	if (b == 0 ) return 0;
	return ((int)a) - (((int)a )/((int)b))*((int)b);

}

inline __host__ __device__ bool aSE(int2 a, int b)
{
	return ((a.x >= b) && (a.y >= b));
}


inline __host__ __device__ bool oSE(uint2 a, uint2 b)
{
	return ((a.x >= b.x) || (a.y >= b.y));
}

inline __host__ __device__ bool oSE(int2 a, uint2 b)
{
	return ((a.x >= (int)b.x) || (a.y >= (int)b.y));
}

inline __host__ __device__ bool oSE(uint3 a, uint2 b)
{
	return ((a.x >= b.x) || (a.y >= b.y));
}

inline __host__ __device__ bool oEq(float2 a, float b)
{
	return ((a.x == b) || (a.y == b));
}

inline __host__ __device__ bool oI(float2 a, float b)
{
	return ((a.x < b) || (a.y < b));
}

inline __host__ __device__ bool oEq(uint2 a, int b)
{
	return ((a.x == (uint)b) || (a.y == (uint)b));
}


inline __host__ __device__ bool aEq(int2 a, int b)
{
	return ((a.x == b) && (a.y == b));
}

inline __host__ __device__ bool aEq(uint2 a, uint2 b)
{
	return ((a.x == b.x) && (a.y == b.y));
}

inline __host__ __device__ bool aEq(uint2 a, int b)
{
	return ((a.x == (uint)b) && (a.y == (uint)b));
}

inline __host__ __device__ bool oI(uint2 a, uint2 b)
{
	return ((a.x < b.x) || (a.y < b.y));
}

inline __host__ __device__ bool oI(int2 a, int b)
{
	return ((a.x < b) || (a.y < b));
}

inline __host__ __device__ bool aI(int2 a, int2 b)
{
	return ((a.x < b.x) && (a.y < b.y));
}

inline __host__ __device__ bool oI(uint3 a, uint2 b)
{
	return ((a.x < b.x) || (a.y < b.y));
}

inline __host__ __device__ uint to1D( uint2 c2D, uint2 dim)
{
	return c2D.y * dim.x + c2D.x;
}

inline __host__ __device__ uint to1D( int2 c2D, uint2 dim)
{
	return c2D.y * dim.x + c2D.x;
}

inline __host__ __device__ uint to1D( uint3 c2D, uint3 dim)
{
    return (dim.y * c2D.z + c2D.y) * dim.x + c2D.x;
}


