#include "Bullet.h"
#include "../Resources/Texture.h"

CBullet::CBullet()
	:
	m_fLimitDist(500.f),
	m_fDist(0.f)
{
}

CBullet::CBullet( const CBullet& bullet )
	:
	CMoveObject( bullet )
{
	m_fLimitDist = bullet.m_fLimitDist;
	m_fDist = bullet.m_fDist;
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	SetSpeed( 500.f );

	SetPivot( 0.5f, 0.5f );
	SetTexture( "Bullet", L"Bullet.bmp" );

	m_pTexture->SetColorKey( RGB( 255, 0, 255 ) );

	return true;
}

int CBullet::Update( float fDeltaTime )
{
	CMoveObject::Update( fDeltaTime );

	MoveAngle( fDeltaTime );

	m_fDist += GetSpeed() * fDeltaTime;

	if( m_fDist >= m_fLimitDist )
	{
		Die();
	}

	return 0;
}

int CBullet::LateUpdate( float fDeltaTime )
{
	CMoveObject::LateUpdate( fDeltaTime );

	return 0;
}

void CBullet::Collision( float fDeltaTime )
{
	CMoveObject::Collision( fDeltaTime );
}

void CBullet::Render( HDC hDC, float fDeltaTime )
{
	CMoveObject::Render( hDC, fDeltaTime );
}

CBullet* CBullet::Clone()
{
	return new CBullet(*this);
}
