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

    // ������ Ŭ���� ���
    MyRegisterClass();

    // �ػ� ����
    m_tRs.iW = 1280;
    m_tRs.iH = 720;

    // ������ â ����
    Create();

    // ȭ�� DC ������ֱ�
    m_hDC = GetDC( m_hWnd );

    // Ÿ�̸� �ʱ�ȭ
    if( !GET_SINGLE( CTimer )->Init() )
    {
        return false;
    }

    // ��� ������ �ʱ�ȭ
    if( !GET_SINGLE( CPathManager )->Init() )
    {
        return false;
    }

    // ���ҽ� ������ �ʱ�ȭ
    if( !GET_SINGLE( CResourcesManager )->Init( m_hInst, m_hDC ) )
    {
        return false;
    }

    // ī�޶� ������ �ʱ�ȭ
    if( !GET_SINGLE( CCamera )->Init( POSITION( 0.f, 0.f ),
        m_tRs, RESOLUTION( 1500, 1200 ) ) )
    {
        return false;
    }

    // ��� ������ �ʱ�ȭ
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

        // ������ ���� Ÿ���� ���
        else
        {
            Logic();
        }
    }

    return (int)msg.wParam;
}

void CCore::Logic()
{
    // Ÿ�̸� ����
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
    // ���� �����츦 �����ϰ� ������ �ڵ鿡 ����
    m_hWnd = CreateWindowW( L"WINAPIFRAMEWORK", L"WINAPIFRAMEWORK", 
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr );

    if( !m_hWnd )
    {
        return FALSE;
    }

    // ���� ������ Ÿ��Ʋ�ٳ� �޴��� ������ ������ ũ�⸦ ������.
    RECT rc = { 0,0,m_tRs.iW,m_tRs.iH };
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );

    // ������ ������ ��ü ������ ũ�⸦ ���� Ŭ���̾�Ʈ ������ ũ�⸦ ���ϴ� ũ��� ������� ��.
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
        // �����츦 �����ų �� ������ �޽���.
        case WM_DESTROY:
            m_bLoop = false;
            PostQuitMessage( 0 );
            break;
        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
        }
    return 0;
}
