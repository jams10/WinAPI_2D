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

void CMoveObject::MoveAngle( float fSpeed )
{
	m_tPos.x += cosf( m_fAngle ) * fSpeed;
	m_tPos.y += sinf( m_fAngle ) * fSpeed;
}

void CMoveObject::MoveAngle( float fSpeed, float fDeltaTime )
{
	m_tPos.x += cosf( m_fAngle ) * fSpeed * fDeltaTime;
	m_tPos.y += sinf( m_fAngle ) * fSpeed * fDeltaTime;
}

void CMoveObject::Input( float fDeltaTime )
{
}

int CMoveObject::Update( float fDeltaTime )
{
	return 0;
}

int CMoveObject::LateUpdate( float fDeltaTime )
{
	return 0;
}

void CMoveObject::Collision( float fDeltaTime )
{
}

void CMoveObject::Render( HDC hDC, float fDeltaTime )
{
}
