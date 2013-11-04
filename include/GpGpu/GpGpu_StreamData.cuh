#ifndef _GPGPUSTREAMDATA_H_
#define _GPGPUSTREAMDATA_H_

#include "GpGpu/GpGpu_Data.h"

using namespace std;

static __constant__ ushort  dMapIndex[WARPSIZE];

/// \class CDeviceStream
/// \brief Classe gerant un flux de donn�es en memoire video
template< class T >
class CDeviceStream
{
public:

    __device__ CDeviceStream(T* buf,T* stream, uint sizeStream):
        _bufferData(buf),
        _streamData(stream),
        _curStreamId(0),
        _curBufferId(WARPSIZE),
        _sizeStream(sizeStream)
    {}

    __device__ virtual short getLen2ReadAV(short2 &index)
    {
        index = make_short2(0,0);
        return 1;
    }

    __device__ virtual short getLen2ReadAR(short2 &index)
    {
        index = make_short2(0,0);
        return 1;
    }

    template<bool sens, class D> __device__ short2 read(D* destData, ushort tid, T def);

private:

    template<bool sens> __device__ short vec(){ return 1 - 2 * !sens; }

    template<bool sens> __device__ short GetNbToCopy(ushort nTotal,ushort nCopied)
    {
        return min(nTotal - nCopied , MaxReadBuffer<sens>());
    }

    template<bool sens> __device__ ushort MaxReadBuffer()
    {
        return sens ? ((ushort)WARPSIZE - _curBufferId) : _curBufferId;
    }


    T*                          _bufferData;
    T*                          _streamData;
    uint                        _curStreamId;
    ushort                      _curBufferId;
    uint                        _sizeStream;
};

template< class T > template<bool sens, class D>  __device__
short2 CDeviceStream<T>::read(D *destData, ushort tid, T def)
{
    short2  index;
    ushort  NbCopied    = 0 , NbTotalToCopy = sens ? getLen2ReadAV(index) : getLen2ReadAR(index);
    short   PitSens     = !sens * WARPSIZE;

    while(NbCopied < NbTotalToCopy)
    {
        ushort NbToCopy = GetNbToCopy<sens>(NbTotalToCopy,NbCopied);

        if(!NbToCopy)
        {
            uint idStream =_curStreamId + threadIdx.x - 2 * PitSens;
            if(idStream < _sizeStream)
                _bufferData[threadIdx.x] = _streamData[idStream];
            _curBufferId   = PitSens;            
            _curStreamId   = _curStreamId  + (vec<sens>()<<5); // * 32

            NbToCopy = GetNbToCopy<sens>(NbTotalToCopy,NbCopied);
        }

        ushort idDest = tid + (sens ? NbCopied : NbTotalToCopy - NbCopied - NbToCopy);

        if(!(idDest>>8)) // < 256
        {
            if (tid < NbToCopy && idDest < NbTotalToCopy)
                destData[idDest] = _bufferData[_curBufferId + tid - !sens * NbToCopy];
            else if (idDest >= NbTotalToCopy)
                destData[idDest] = def;

        }
        _curBufferId  = _curBufferId + vec<sens>() * NbToCopy;
        NbCopied     += NbToCopy;
   }

   return index;
}


template< class T >
class CDeviceDataStream : public CDeviceStream<T>
{
public:

    __device__ CDeviceDataStream(T* buf,T* stream,short2* bufId,short2* streamId, uint sizeStream, uint sizeStreamId):
        CDeviceStream<T>(buf,stream,sizeStream),
        _streamIndex(bufId,streamId,sizeStreamId)
    {}


    __device__ short getLen2ReadAV(short2 &index)
    {       

        _streamIndex.read<eAVANT>(&index,0,make_short2(0,0));

        return diffYX(index);
    }

    __device__ short getLen2ReadAR(short2 &index)
    {

        _streamIndex.read<eARRIERE>(&index,0,make_short2(0,0));

        return diffYX(index);
    }

private:

    CDeviceStream<short2>       _streamIndex;

};

#define sgn s<sens>
#define max_cost 1e9

template< bool sens,class T>
__device__ inline int s(T v)
{
    return sens ? v : -v;
}

template<class T>
class SimpleStream
{
public:

    __device__ SimpleStream(   T*      globalStream,
                    ushort  sizeBuffer);

    template<bool sens> __device__ void read(T* sharedBuffer);

    template<bool sens,class S>
                        __device__ void readFrom(S* sharedBuffer,uint delta = 0);

    template<bool sens> __device__ void incre();

    template<bool sens> __device__ void ReverseIncre();

    T                   __device__  GetValue(int id);

    void                __device__  SetValue(int id, T value);

    uint                __device__  GetGiD(){return _idG;}

    template<bool sens> __device__  void reverse();

    void                __device__  output();

private:

    T*      _globalStream;
    int    _idG;
    ushort  _sizeBuffer;
};

template<class T> __device__
SimpleStream<T>::SimpleStream( T *globalStream, ushort sizeBuffer):
    _globalStream(globalStream + threadIdx.x),
    _idG(0),
    _sizeBuffer(sizeBuffer)
{}

template<class T> __device__
T SimpleStream<T>::GetValue(int id)
{
    return _globalStream[_idG + id];
}

template<class T> __device__
void SimpleStream<T>::SetValue(int id, T value)
{
    _globalStream[_idG + id] = value;
}

template<class T> __device__
void SimpleStream<T>::output()
{
    if(!threadIdx.x)
    {
        printf("----------------------------------\n");
        printf("_sizeBuffer = %d\n",_sizeBuffer);
        printf("_idG        = %d\n",_idG);
        printf("----------------------------------\n");
    }
}

template<class T> template<bool sens> __device__
void SimpleStream<T>::reverse()
{
    _idG += sgn(WARPSIZE);
}

template<class T> template<bool sens> __device__
void SimpleStream<T>::read(T *sharedBuffer)
{        
    readFrom<sens>(sharedBuffer);
    incre<sens>();
}

template<class T> template<bool sens,class S> __device__
void SimpleStream<T>::readFrom(S *sharedBuffer,uint delta)
{
    T* gLocal = _globalStream  + _idG + sgn(delta);

    for(ushort i = 0; i < _sizeBuffer; i += WARPSIZE)
        *(sharedBuffer + sgn(i)) = *(gLocal+sgn(i));
}

template<class T> template<bool sens> __device__
void SimpleStream<T>::incre()
{
    _idG += sgn(_sizeBuffer);
}

template<class T> template<bool sens> __device__
void SimpleStream<T>::ReverseIncre()
{
    reverse<sens>();
    incre<sens>();
}

#endif
