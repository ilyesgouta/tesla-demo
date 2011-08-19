

#ifndef _POLKA_LIKE_HPP_
#define _POLKA_LIKE_HPP_

#include "Effect.hpp"

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

        void Init( CVector& cPos0, CVector& cDelPos, float fAngleZ0 ) {

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
public:
        Track_c() {
          m_pTrackElems = 0;
          m_iTrackElems = 0;

          m_fInitAngleZ = 0;
          m_fInitAngleChange = 0;

          m_cInitPos = CVector(0, 0, 0);
          m_fInitPos = 0;
          m_fInitPosChange = 0;
        }

        ~Track_c() {
          if ( m_pTrackElems ) delete[] m_pTrackElems;
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
};

class PolkaLike_c : public CEffect {

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
};

#endif

