
#if !defined (_SINUS_HPP_)
#define _SINUS_HPP_

class CSinPulse {

public:
        CSinPulse(float fMin, float fMax, float fFrequency, float fF0) {
          m_fMin = fMin;
          m_fMax = fMax;
          m_fFrequency = fFrequency;
          m_fF0 = fF0;
        }

        float Calculate(float fTime) {
          return (float)((m_fMax - m_fMin)*.5f*sin(m_fFrequency*fTime + m_fF0) + (m_fMax + m_fMin)*.5f);
        }

        float m_fMin, m_fMax;
        float m_fFrequency;
        float m_fF0;


};

class CSinWave {
public:
        CSinWave() {};

        CSinWave(float fAmplidude, float fFrequency, float fF0) {
          m_fAmplitude = fAmplidude;
          m_fFrequency = fFrequency;
          m_fF0 = fF0;
        }

        float Calculate(float fTime) {
          return (float)(m_fAmplitude*sin(m_fFrequency*fTime + m_fF0));
        }

        float m_fAmplitude;
        float m_fFrequency;
        float m_fF0;
};

#endif