#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer( const CPlayer& player )
    :
    CMoveObject( player )
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    SetPos( 50.f, 50.f );
    SetSize( 100.f, 100.f );
    SetSpeed( 400.f );
    SetPivot( 0.5f, 0.5f );

    SetTexture( "Player", L"Kirby.bmp" );

    return true;
}

void CPlayer::Input( float fDeltaTime )
{
    CMoveObject::Input( fDeltaTime );

    if( GetAsyncKeyState( 'W' ) & 0x8000 )
    {
        MoveYAsSpeed( fDeltaTime, MD_BACK );
    }
    if( GetAsyncKeyState( 'S' ) & 0x8000 )
    {
        MoveYAsSpeed( fDeltaTime, MD_FRONT );
    }
    if( GetAsyncKeyState( 'A' ) & 0x8000 )
    {
        MoveXBySpeed( fDeltaTime, MD_BACK );
    }
    if( GetAsyncKeyState( 'D' ) & 0x8000 )
    {
        MoveXBySpeed( fDeltaTime, MD_FRONT );
    }
    if( GetAsyncKeyState( VK_SPACE ) & 0x8000 )
    {
        Fire();
    }
}

int CPlayer::Update( float fDeltaTime )
{
    CMoveObject::Update( fDeltaTime );

    return 0;
}

int CPlayer::LateUpdate( float fDeltaTime )
{
    CMoveObject::LateUpdate( fDeltaTime );

    return 0;
}

void CPlayer::Collision( float fDeltaTime )
{
    CMoveObject::Collision( fDeltaTime );
}

void CPlayer::Render( HDC hDC, float fDeltaTime )
{
    CMoveObject::Render( hDC, fDeltaTime );
    //Rectangle( hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y );
}

CPlayer* CPlayer::Clone()
{
    return new CPlayer(*this);
}

void CPlayer::Fire()
{
    CObject* pBullet = CMoveObject::CreateCloneObj( "Bullet", "PlayerBullet", m_pLayer );

    // Get middle point of right
    POSITION tPos;
    tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
    tPos.y = GetCenter().y;

    pBullet->SetPos( tPos );
}
