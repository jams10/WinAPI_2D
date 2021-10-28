#include "Minion.h"
#include "../Core.h"

CMinion::CMinion()
	:
	m_fFireTime( 0.f ),
	m_fFireLimitTime( 1.13f )
{
}

CMinion::CMinion( const CMinion& minion )
	:
	CMoveObject( minion )
{
	m_eDir = minion.m_eDir;
	m_fFireTime = minion.m_fFireTime;
	m_fFireLimitTime = minion.m_fFireLimitTime;
}

CMinion::~CMinion()
{
}

bool CMinion::Init()
{
	SetPos( 800.f, 100.f );
	SetSize( 100.f, 100.f );
	SetSpeed( 300.f );
	SetPivot( 0.5f, 0.5f );

	SetTexture( "Minion", L"monster.bmp" );

	m_eDir = MD_FRONT;

	return true;
}

int CMinion::Update( float fDeltaTime )
{
	CMoveObject::Update( fDeltaTime );

	MoveYAsSpeed( fDeltaTime, m_eDir );

	RESOLUTION res = GETRESOLUTION;

	if( m_tPos.y + m_tSize.y >= res.iH )
	{
		m_tPos.y = res.iH - m_tSize.y;
		m_eDir = MD_BACK;
	}

	else if( m_tPos.y <= 0.f )
	{
		m_tPos.y = 0.f;
		m_eDir = MD_FRONT;
	}

	m_fFireTime += fDeltaTime;

	if( m_fFireTime >= m_fFireLimitTime )
	{
		m_fFireTime -= m_fFireLimitTime;
		Fire();
	}

	return 0;
}

int CMinion::LateUpdate( float fDeltaTime )
{
	CMoveObject::LateUpdate( fDeltaTime );
	return 0;
}

void CMinion::Collision( float fDeltaTime )
{
	CMoveObject::Collision( fDeltaTime );
}

void CMinion::Render( HDC hDC, float fDeltaTime )
{
	CMoveObject::Render( hDC, fDeltaTime );
}

CMinion* CMinion::Clone()
{
	return new CMinion( *this );
}

void CMinion::Fire()
{
	CObject* pBullet = CMoveObject::CreateCloneObj( "Bullet", "MinionBullet", m_pLayer );

	((CMoveObject*)pBullet)->SetAngle( PI );

	float x = GetLeft() - (pBullet->GetSize().x * (1.f - pBullet->GetPivot().x));
	float y = GetCenter().y;

	pBullet->SetPos( x, y );
}
