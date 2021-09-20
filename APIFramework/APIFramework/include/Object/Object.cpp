#include "Object.h"

CObject::CObject()
	:
	m_iRef( 1 )
{
}

CObject::~CObject()
{
}

bool CObject::Init()
{
	return true;
}

void CObject::Input( float fDeltaTime )
{
}

int CObject::Update( float fDeltaTime )
{
	return 0;
}

int CObject::LateUpdate( float fDeltaTime )
{
	return 0;
}

void CObject::Collision( float fDeltaTime )
{
}

void CObject::Render( HDC hDC, float fDeltaTime )
{
}
