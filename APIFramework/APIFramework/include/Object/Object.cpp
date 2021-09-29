#include "Object.h"

CObject::CObject()
{
}

CObject::CObject( const CObject& obj )
{
	*this = obj;
}

CObject::~CObject()
{
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
