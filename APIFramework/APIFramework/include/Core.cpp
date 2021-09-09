#include "Core.h"

CCore* CCore::m_pInst;
bool CCore::m_bLoop = true;

CCore::CCore()
{
}

CCore::~CCore()
{
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
            
        }
    }

    return (int)msg.wParam;
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
