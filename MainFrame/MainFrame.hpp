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


#if !defined (__MAIN_FRAME_HPP__)
#define __MAIN_FRAME_HPP__

#ifdef WIN32
#include <windows.h>
#else
#include <X11/X.h>
#endif

#include <EGL/egl.h>
#include <EGL/eglplatform.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class TimerBase_c {

public:
        TimerBase_c();
        virtual ~TimerBase_c();

        virtual bool InitTimer() = 0;

        /* time in sek from app start */
        virtual float GetCurTime() = 0;
        virtual float GetPrevTime() = 0;
        virtual float GetDeltaTime() = 0;
        virtual float GetAppStartTime() = 0;

        virtual void Update() = 0;
};

class Timer_c : public TimerBase_c {

public:
        Timer_c();
        virtual ~Timer_c();

        virtual bool InitTimer();

        /* time in sek */
        virtual float GetCurTime() {
          return m_fTimeCurrent;
        }
        virtual float GetPrevTime() {
          return m_fTimePrev;
        }
        virtual float GetDeltaTime() {
          return m_fTimeDelta;
        }
        virtual float GetAppStartTime() {
          return m_fTimeAppStart;
        }

        virtual void Update();

protected:
        float m_fTimeCurrent;
        float m_fTimePrev;
        float m_fTimeDelta;

        float m_fTimeAppStart;

private:
#ifdef WIN32
        _int64 m_liTimeFreq;
        _int64 m_liTimePrev;
        _int64 m_liTimeCurrent;
        _int64 m_liTimeStart;
#endif

};

class MainFrame_c {
        
        friend void Start();
  
public:
        MainFrame_c();
        virtual ~MainFrame_c();

        /* user methods */
        virtual bool OnCreate();
        virtual bool OnPaint();
        virtual bool OnDestroy();

#ifdef WIN32
        /* main frame states */
        virtual void SetWindowHandle( HWND hWnd );
        virtual HWND GetWindowHandle() const;
#else
        virtual Display* GetDisplay() const { return m_display; }
#endif

        void SetWindowName( char* pszWindowName ) {
          if ( pszWindowName )
            strncpy( m_szWindowName, pszWindowName, strlen(pszWindowName) + 1 );
        }

        void SetWindowStyle( unsigned int dwStyle ) {
          m_dwWindowStyle = dwStyle;
        }

        char* GetWindowName() { return m_szWindowName; }

        bool GetWindowActive() const { return m_bWindowActive; };

        void SetFullScreen( bool bFullScreen ) {
          m_bFullScreen = bFullScreen;
        }
        bool GetFullScreen() { return m_bFullScreen; }

#ifdef WIN32
        /* create window */
        virtual bool InitWindow( HINSTANCE hInstance );
        /* message callback */
        virtual LRESULT WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
#else
        virtual bool InitWindow();
#endif

        int GetLastError() {
          return m_iError;
        }

        char* GetLastErrorMsg() {
            return m_szErrorMessage;
        }

        bool GetMessageBased() const {
          return m_bMessageBased;
        }

        void ErrorQuit( char* pszErrMsg, ... );

protected:
        /* windows crap */
#ifdef WIN32
        HINSTANCE m_hInstance; // app instance
        HWND m_hWnd; // main window handle
#else
        Display *m_display;
        Window m_window;
#endif
        bool m_bWindowActive;
        bool m_bFullScreen;
        bool m_bMessageBased;

        int m_iResourceIcon;
        unsigned int m_dwWindowStyle;

        /* errors */
        char m_szErrorMessage[512];
        int m_iError;

        /* init */
        bool m_bInitDone;

        /* window resolution */
        int m_iWindowWidth;
        int m_iWindowHeight;
        int m_iBitsPerPixel;

        /* window name */
        char m_szWindowName[64];


        /* timeing */
        TimerBase_c* m_pTimer;

private:

};

extern void Start();
extern void End();
extern MainFrame_c* g_pMainFrame;

#endif /*__MAIN_FRAME_HPP__*/

