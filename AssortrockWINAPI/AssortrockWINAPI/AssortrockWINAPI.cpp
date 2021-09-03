// AssortrockWINAPI.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "AssortrockWINAPI.h"
#include <list>

#define MAX_LOADSTRING 100

typedef struct _tagRectangle
{
    float l, t, r, b;
}RECTANGLE, *PRECTANGLE;

typedef struct _tagBullet
{
    RECTANGLE rc;
    float     fDist;
    float     fLimitDist;
}BULLET, * PBULLET;

typedef struct _tagMonster
{
    RECTANGLE tRC;
    float     fSpeed;
    float     fTime;
    float     fLimitTime;
    int       iDir;
}MONSTER, * PMONSTER;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND g_hWnd;
HDC  g_hDC;
bool g_bLoop = true;

RECTANGLE g_tPlayerRC = { 100, 100, 200, 200 };
MONSTER g_tMonster;

// 플레이어 총알 리스트
std::list<BULLET> g_PlayerBulletList;

// 몬스터 총알
std::list<BULLET> g_MonsterBulletList;

// 시간을 구하기 위한 변수들
LARGE_INTEGER g_tSecond;
LARGE_INTEGER g_tTime;
float         g_fDeltaTime;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Run();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASSORTROCKWINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 화면 그리기용 DC 생성.
    g_hDC = GetDC( g_hWnd );

    // 몬스터 초기화
    g_tMonster.tRC.l = 800.f - 100.f;
    g_tMonster.tRC.t = 0.f;
    g_tMonster.tRC.r = 800.f;
    g_tMonster.tRC.b = 100.f;
    g_tMonster.fSpeed = 300.f;
    g_tMonster.fLimitTime = 1.2f;
    g_tMonster.iDir = 1;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSORTROCKWINAPI));

    MSG msg;

    QueryPerformanceFrequency( &g_tSecond );
    // 이전 Tick(초기 Tick)
    QueryPerformanceCounter( &g_tTime );

    // Main message loop:
    while( g_bLoop )
    {
        if ( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // 윈도우 데드 타임일 경우
        else
        {
            Run();
        }
    }

    ReleaseDC( g_hWnd, g_hDC );

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSORTROCKWINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL; //MAKEINTRESOURCEW(IDC_ASSORTROCKWINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   // 윈도우 핸들 전역변수에 생성한 윈도우 핸들 넣기.
   g_hWnd = hWnd;

   // 실제 윈도우 타이틀바나 메뉴를 포함한 윈도우 크기를 구해줌.
   RECT rc = { 0,0,800,600 };
   AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );

   // 위에서 구해준 전체 윈도우 크기를 통해 클라이언트 영역의 크기를 원하는 크기로 맞춰줘야 함.
   SetWindowPos( hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER );

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...

            EndPaint(hWnd, &ps);
        }
        break;
        // 윈도우를 종료시킬 때 들어오는 메시지.
    case WM_DESTROY:
        g_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void Run()
{
    // DeltaTime
    LARGE_INTEGER tTime;
    // 현재 프레임의 틱을 뽑아옴.
    QueryPerformanceCounter( &tTime );

    // (현재 Tick - 이전 Tick) / 초당 Tick
    g_fDeltaTime = static_cast<float> ((tTime.QuadPart - g_tTime.QuadPart)) / g_tSecond.QuadPart;

    g_tTime = tTime;

    /* 플레이어 이동 */

    // 슬로우 모션 ( 타임 스케일 이용 )
    static float fTimeScale = 1.f;

    // 플레이어 초당 이동속도 : 300에 30%만큼 더 빠르게 움직임.(아이템 먹었을 때 이동 속도 퍼센트 단위로 올리기)
    float fSpeed = (300 + 300 * 0.3f) * g_fDeltaTime * fTimeScale;

    if( GetAsyncKeyState( VK_F1 ) & 0x8000 )
    {
        fTimeScale -= g_fDeltaTime;
        if( fTimeScale < 0.f )
        {
            fTimeScale = 0.f;
        }
    }

    if( GetAsyncKeyState( VK_F2 ) & 0x8000 )
    {
        fTimeScale += g_fDeltaTime;
        if( fTimeScale > 1.f )
        {
            fTimeScale = 1.f;
        }
    }

    RECT clientRect;
    GetClientRect( g_hWnd, &clientRect );

    // 화면 갱신 임시방편으로 쓰기 위해 클라이언트 크기를 일시적으로 조정.
    SetRect( &clientRect, 0, 0, 800, 600 );

    if( GetAsyncKeyState( 'D' ) & 0x8000 )
    {
        g_tPlayerRC.l += fSpeed;
        g_tPlayerRC.r += fSpeed;
        if( g_tPlayerRC.r > clientRect.right )
        {
            g_tPlayerRC.r = clientRect.right;
            g_tPlayerRC.l = clientRect.right - 100;
        }
    }
    if( GetAsyncKeyState( 'A' ) & 0x8000 )
    {
        g_tPlayerRC.l -= fSpeed;
        g_tPlayerRC.r -= fSpeed;
        if( g_tPlayerRC.l < clientRect.left )
        {
            g_tPlayerRC.l = 0;
            g_tPlayerRC.r = clientRect.left + 100;
        }
    }
    if( GetAsyncKeyState( 'W' ) & 0x8000 )
    {
        g_tPlayerRC.t -= fSpeed;
        g_tPlayerRC.b -= fSpeed;
        if( g_tPlayerRC.t < clientRect.top )
        {
            g_tPlayerRC.t = clientRect.top;
            g_tPlayerRC.b = clientRect.top + 100;
        }
    }
    if( GetAsyncKeyState( 'S' ) & 0x8000 )
    {
        g_tPlayerRC.t += fSpeed;
        g_tPlayerRC.b += fSpeed;
        if( g_tPlayerRC.b > clientRect.bottom )
        {
            g_tPlayerRC.b = clientRect.bottom;
            g_tPlayerRC.t = clientRect.bottom - 100;
        }
    }
    /* 플레이어 총알 생성 */
    if( GetAsyncKeyState( VK_SPACE ) & 0x8000 )
    {
        BULLET tBullet = {};

        tBullet.rc.l = g_tPlayerRC.r;
        tBullet.rc.r = tBullet.rc.l + 50.f;
        tBullet.rc.t = (g_tPlayerRC.t + g_tPlayerRC.b) / 2.0f - 25.f;
        tBullet.rc.b = tBullet.rc.t + 50.f;
        tBullet.fDist = 0.f;
        tBullet.fLimitDist = 500.f;

        g_PlayerBulletList.push_back( tBullet );
    }
 
    /* 몬스터 이동 */
    g_tMonster.tRC.t += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;
    g_tMonster.tRC.b += g_tMonster.fSpeed * g_fDeltaTime * fTimeScale * g_tMonster.iDir;

    if( g_tMonster.tRC.b >= 600 )
    {
        g_tMonster.iDir = -1;
        g_tMonster.tRC.b = 600;
        g_tMonster.tRC.t = 500;
    }

    else if( g_tMonster.tRC.t <= 0 )
    {
        g_tMonster.iDir = 1;
        g_tMonster.tRC.b = 100;
        g_tMonster.tRC.t = 0;
    }

    /* 몬스터 총알 생성 */
    g_tMonster.fTime += g_fDeltaTime * fTimeScale;

    if( g_tMonster.fTime >= g_tMonster.fLimitTime )
    {
        g_tMonster.fTime -= g_tMonster.fLimitTime;

        BULLET tBullet = {};

        tBullet.rc.r = g_tMonster.tRC.l;
        tBullet.rc.l = tBullet.rc.r - 50.f;
        tBullet.rc.t = (g_tMonster.tRC.t + g_tMonster.tRC.b) / 2.0f - 25.f;
        tBullet.rc.b = tBullet.rc.t + 50.f;
        tBullet.fDist = 0.f;
        tBullet.fLimitDist = 800.f;

        g_MonsterBulletList.push_back( tBullet );
    }

    /* 플레이어 총알 이동 */
    std::list<BULLET>::iterator iter;
    std::list<BULLET>::iterator iterEnd = g_PlayerBulletList.end();

    // 총알의 이동속도
    fSpeed = 600.f * g_fDeltaTime * fTimeScale;

    for( iter = g_PlayerBulletList.begin(); iter != iterEnd; )
    {
        iter->rc.l += fSpeed;
        iter->rc.r += fSpeed;

        iter->fDist += fSpeed;

        if( iter->fDist >= iter->fLimitDist )
        {
            iter = g_PlayerBulletList.erase( iter );
            iterEnd = g_PlayerBulletList.end();
        }

        else if( iter->rc.l > clientRect.right )
        {
            iter = g_PlayerBulletList.erase( iter );
            iterEnd = g_PlayerBulletList.end();
        }
        else
        {
            ++iter;
        }
    }

    /* 몬스터 총알 이동 */
    iterEnd = g_MonsterBulletList.end();
    for( iter = g_MonsterBulletList.begin(); iter != iterEnd; )
    {
        iter->rc.l -= fSpeed;
        iter->rc.r -= fSpeed;

        iter->fDist += fSpeed;


        if( iter->fDist >= iter->fLimitDist )
        {
            iter = g_MonsterBulletList.erase( iter );
            iterEnd = g_MonsterBulletList.end();
        }

        else if( iter->rc.r <= 0 )
        {
            iter = g_MonsterBulletList.erase( iter );
            iterEnd = g_MonsterBulletList.end();
        }

        // 충돌 조건
        else if( g_tPlayerRC.l <= iter->rc.r && iter->rc.l <= g_tPlayerRC.r &&
            g_tPlayerRC.t <= iter->rc.b && iter->rc.t <= g_tPlayerRC.b )
        {
            iter = g_MonsterBulletList.erase( iter );
            iterEnd = g_MonsterBulletList.end();
        }

        else
        {
            ++iter;
        }
    }

    /* 출력 */
    // 몬스터 출력
    Rectangle( g_hDC, g_tMonster.tRC.l, g_tMonster.tRC.t, g_tMonster.tRC.r, g_tMonster.tRC.b );

    // 플레이어 출력
    Rectangle( g_hDC, g_tPlayerRC.l, g_tPlayerRC.t, g_tPlayerRC.r, g_tPlayerRC.b );

    // 플레이어 총알 출력
    iterEnd = g_PlayerBulletList.end();
    for( iter = g_PlayerBulletList.begin(); iter != iterEnd; ++iter )
    {
        Rectangle( g_hDC, iter->rc.l, iter->rc.t, iter->rc.r, iter->rc.b );
    }

    // 몬스터 총알 출력
    iterEnd = g_MonsterBulletList.end();
    for( iter = g_MonsterBulletList.begin(); iter != iterEnd; ++iter )
    {
        Rectangle( g_hDC, iter->rc.l, iter->rc.t, iter->rc.r, iter->rc.b );
    }

    // 800*600 사각형으로 화면 덮기
    // Rectangle( g_hDC, 0, 0, 800, 600 );
}