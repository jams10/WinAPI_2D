#include "Minion.h"
#include "../Core.h"

CMinion::CMinion()
{
}

CMinion::CMinion( const CMinion& minion )
	:
	CMoveObject( minion )
{
	m_eDir = minion.m_eDir;
}

CMinion::~CMinion()
{
}

bool CMinion::Init()
{
	SetPos( 800, 100.f );
	SetSize( 100.f, 100.f );
	SetSpeed( 300.f );

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
	Rectangle( hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y );
}

CMinion* CMinion::Clone()
{
	return new CMinion( *this );
}
