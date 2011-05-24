

#if !defined (__MAIN_FRAME_HPP__)
#define __MAIN_FRAME_HPP__

#include <windows.h>
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
        _int64 m_liTimeFreq;
        _int64 m_liTimePrev;
        _int64 m_liTimeCurrent;
        _int64 m_liTimeStart;

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

        /* main frame states */
        virtual void SetWindowHandle( HWND hWnd );
        virtual HWND GetWindowHandle() const;

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

        /* create window */
        virtual bool InitWindow( HINSTANCE hInstance );

        /* message callback */        
        virtual LRESULT WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );


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
        HINSTANCE m_hInstance; // app instance
        HWND m_hWnd; // main window handle
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

