//
// tesla-demo, an OpenGL|ES 1.1 port of Sunflower's original Tesla demo.
//
// Original Tesla code, Copyright (C) 2000 Sunflower
// Linux EGL/X11 port by Ilyes Gouta, ilyes.gouta@gmail.com
//
// Port released under GNU General Public License with permission from
// Konrad Zagorowicz, original developer from Sunflower.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#if !defined (_SINUS_HPP_)
#define _SINUS_HPP_

#include <math.h>

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
