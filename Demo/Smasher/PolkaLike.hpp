
#ifndef _POLKA_LIKE_HPP_
#define _POLKA_LIKE_HPP_

#include "3dlib/3dlib.h"
#include "base3d/CVector.hpp"
#include "base3d/CTexel.hpp"
#include "base3d/CColor.hpp"
#include "base3d/CMatrix.hpp"
#include "base3d/CVector.hpp"

#include "TexManager.hpp"

#include "Effect.hpp"

#include <GLES/gl.h>

#ifndef pi
#define pi 3.1415926535897932384626433832795
#endif

class TrackElem_c {

friend class Track_c;
public:
    TrackElem_c() {
        m_cDelPos = CVector(0, 0, 0);
        m_cPosition = CVector(0, 0, 0);
        m_fAnlgeZ = 0;
    }

    void Init( CVector& cPos0, CVector& cDelPos, float fAngleZ0 )
    {
        m_cDelPos = cDelPos;
        m_cPosition = cPos0;
        m_fAnlgeZ = fAngleZ0;
    }

    void Update( float fDelTime );

protected:
    CVector m_cDelPos;
    CVector m_cPosition;
    float m_fAnlgeZ;
};

class Track_c {

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

public:
    Track_c();

    ~Track_c() {
        if ( m_pTrackElems )
            delete[] m_pTrackElems;
    }

    void Init( int iElems, float fInitAngleChange, float fInitPosChange );
    void Render( float fDelTime, float fTime );

protected:
    TrackElem_c* m_pTrackElems;
    int m_iTrackElems;

    float m_fInitAngleZ;
    float m_fInitAngleChange;

    CVector m_cInitPos;
    float m_fInitPos;
    float m_fInitPosChange;

    int m_triBufSize, m_triCurrentIndex;

    void glPutFace(const CVector& cV1, const CVector& cV2, const CVector& cV3, const CVector& cV4);
    void glFlushFaces();

#ifdef GL_VERSION_ES_CM_1_1
private:
    CVertex *m_Vertex;
    CTex *m_Texture;
#endif
};

class PolkaLike_c : public CEffect {

typedef struct __attribute__ ((packed)) CVertex {
    float x, y, z;
} CVertex;

typedef struct __attribute__ ((packed)) CTex {
    float s0, t0;
} CTex;

public:
    PolkaLike_c();
    virtual ~PolkaLike_c();

    virtual void Do( float fTime, float fTimeStart = 0 );

protected:
    int m_iTexture;
    int m_iBack;

    Track_c* m_pTracks;
    int m_iTracks;

    void Init();

    void PutQuad( float fZ );

#ifdef GL_VERSION_ES_CM_1_1
private:
    CVertex m_Vertex[4];
    CTex m_Texture[4];
#endif
};

#endif
