#include "MoveObject.h"

CMoveObject::CMoveObject()
	:
	m_fAngle( 0.f ),
	m_fSpeed( 100.f )
{
}

CMoveObject::CMoveObject( const CMoveObject& obj )
	:
	CObject( obj )
{
	m_fAngle = obj.m_fAngle;
	m_fSpeed = obj.m_fSpeed;
}

CMoveObject::~CMoveObject()
{
}

void CMoveObject::Move( float x, float y )
{
	m_tPos.x += x;
	m_tPos.y += y;
}

void CMoveObject::Move( float x, float y, float fDeltaTime )
{
	m_tPos.x += x * fDeltaTime;
	m_tPos.y += y * fDeltaTime;
}

void CMoveObject::Move( const POSITION& tMove )
{
	m_tPos += tMove;
}

void CMoveObject::Move( const POSITION& tMove, float fDeltaTime )
{
	m_tPos += tMove * fDeltaTime;
}

void CMoveObject::MoveX( float x )
{
	m_tPos.x += x;
}

void CMoveObject::MoveX( float x, float fDeltaTime )
{
	m_tPos.x += x * fDeltaTime;
}

void CMoveObject::MoveXBySpeed( float fDeltaTime, MOVE_DIR eDir )
{
	m_tPos.x += m_fSpeed * fDeltaTime * eDir;
}

void CMoveObject::MoveY( float y )
{
	m_tPos.x += y;
}

void CMoveObject::MoveY( float y, float fDeltaTime )
{
	m_tPos.x += y * fDeltaTime;
}

void CMoveObject::MoveYAsSpeed( float fDeltaTime, MOVE_DIR eDir )
{
	m_tPos.y += m_fSpeed * fDeltaTime * eDir;
}

void CMoveObject::MoveAngle()
{
	m_tPos.x += cosf( m_fAngle ) * m_fSpeed;
	m_tPos.y += sinf( m_fAngle ) * m_fSpeed;
}

void CMoveObject::MoveAngle( float fDeltaTime )
{
	m_tPos.x += cosf( m_fAngle ) * m_fSpeed * fDeltaTime;
	m_tPos.y += sinf( m_fAngle ) * m_fSpeed * fDeltaTime;
}

void CMoveObject::Input( float fDeltaTime )
{
	CObject::Input( fDeltaTime );
}

int CMoveObject::Update( float fDeltaTime )
{
	CObject::Update( fDeltaTime );
	return 0;
}

int CMoveObject::LateUpdate( float fDeltaTime )
{
	CObject::LateUpdate( fDeltaTime );
	return 0;
}

void CMoveObject::Collision( float fDeltaTime )
{
	CObject::Collision( fDeltaTime );
}

void CMoveObject::Render( HDC hDC, float fDeltaTime )
{
	CObject::Render( hDC, fDeltaTime );
}
