#include "Core.h"
#include "Scene\SceneManager.h"
#include "Core/Timer.h"
#include "Core/PathManager.h"
#include "Resources/ResourcesManager.h"
#include "Resources/Texture.h"
#include "Core/Camera.h"

CCore* CCore::m_pInst;
bool CCore::m_bLoop = true;

CCore::CCore()
{
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    //_CrtSetBreakAlloc(234);
}

CCore::~CCore()
{
    DESTROY_SINGLE( CSceneManager );
    DESTROY_SINGLE( CCamera );
    DESTROY_SINGLE( CResourcesManager );
    DESTROY_SINGLE( CPathManager );
    DESTROY_SINGLE( CTimer );

    ReleaseDC( m_hWnd, m_hDC );
}

bool CCore::Init( HINSTANCE hInst )
{
    m_hInst = hInst;

    // 윈도우 클래스 등록
    MyRegisterClass();

    // 해상도 설정
    m_tRs.iW = 1280;
    m_tRs.iH = 720;

    // 윈도우 창 생성
    Create();

    // 화면 DC 만들어주기
    m_hDC = GetDC( m_hWnd );

    // 타이머 초기화
    if( !GET_SINGLE( CTimer )->Init() )
    {
        return false;
    }

    // 경로 관리자 초기화
    if( !GET_SINGLE( CPathManager )->Init() )
    {
        return false;
    }

    // 리소스 관리자 초기화
    if( !GET_SINGLE( CResourcesManager )->Init( m_hInst, m_hDC ) )
    {
        return false;
    }

    // 카메라 관리자 초기화
    if( !GET_SINGLE( CCamera )->Init( POSITION( 0.f, 0.f ),
        m_tRs, RESOLUTION( 1500, 1200 ) ) )
    {
        return false;
    }

    // 장면 관리자 초기화
    if( !GET_SINGLE( CSceneManager )->Init() )
    {
        return false;
    }

    return true;
}

int CCore::Run()
{
    MSG msg;

    // Main message loop:
    while( m_bLoop )
    {
        if( PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }

        // 윈도우 데드 타임일 경우
        else
        {
            Logic();
        }
    }

    return (int)msg.wParam;
}

void CCore::Logic()
{
    // 타이머 갱신
    GET_SINGLE( CTimer )->Update();

    float fDeltaTime = GET_SINGLE( CTimer )->GetDeltaTime();

    Input( fDeltaTime );
    Update( fDeltaTime );
    LateUpdate( fDeltaTime );
    Collision( fDeltaTime );
    Render( fDeltaTime );
}

void CCore::Input( float fDeltaTime )
{
    GET_SINGLE( CSceneManager )->Input( fDeltaTime );
    GET_SINGLE( CCamera )->Input( fDeltaTime );
}

int CCore::Update( float fDeltaTime )
{
    GET_SINGLE( CSceneManager )->Update( fDeltaTime );
    GET_SINGLE( CCamera )->Update( fDeltaTime );
    return 0;
}

int CCore::LateUpdate( float fDeltaTime )
{
    GET_SINGLE( CSceneManager )->LateUpdate( fDeltaTime );
    return 0;
}

void CCore::Collision( float fDeltaTime )
{
    GET_SINGLE( CSceneManager )->Collision( fDeltaTime );
}

void CCore::Render( float fDeltaTime )
{
    CTexture* pBackBuffer = GET_SINGLE( CResourcesManager )->GetBackBuffer();

    Rectangle( pBackBuffer->GetDC(), 0, 0, m_tRs.iW, m_tRs.iH );
    // Draw to back buffer
    GET_SINGLE( CSceneManager )->Render( pBackBuffer->GetDC(), fDeltaTime );

    // back buffer to main dc
    BitBlt( m_hDC, 0, 0, m_tRs.iW, m_tRs.iH, pBackBuffer->GetDC(), 0, 0, SRCCOPY );


    SAFE_RELEASE( pBackBuffer );
}

ATOM CCore::MyRegisterClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof( WNDCLASSEX );

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon( m_hInst, MAKEINTRESOURCE( IDI_ICON1 ) );
    wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_ASSORTROCKWINAPI);
    wcex.lpszClassName = L"WINAPIFRAMEWORK";
    wcex.hIconSm = LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_ICON1 ) );

    return RegisterClassExW( &wcex );
}

BOOL CCore::Create()
{
    // 메인 윈도우를 생성하고 윈도우 핸들에 저장
    m_hWnd = CreateWindowW( L"WINAPIFRAMEWORK", L"WINAPIFRAMEWORK", 
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr );

    if( !m_hWnd )
    {
        return FALSE;
    }

    // 실제 윈도우 타이틀바나 메뉴를 포함한 윈도우 크기를 구해줌.
    RECT rc = { 0,0,m_tRs.iW,m_tRs.iH };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );

    // 위에서 구해준 전체 윈도우 크기를 통해 클라이언트 영역의 크기를 원하는 크기로 맞춰줘야 함.
    SetWindowPos( m_hWnd, HWND_TOPMOST, 100, 100, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER );

    ShowWindow( m_hWnd, SW_SHOW );
    UpdateWindow( m_hWnd );

    return TRUE;
}

LRESULT CCore::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch( message )
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint( hWnd, &ps );
            // TODO: Add any drawing code that uses hdc here...

            EndPaint( hWnd, &ps );
        }
        break;
        // 윈도우를 종료시킬 때 들어오는 메시지.
        case WM_DESTROY:
            m_bLoop = false;
            PostQuitMessage( 0 );
            break;
        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
        }
    return 0;
}
