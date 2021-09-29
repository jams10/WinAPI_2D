#include "MoveObject.h"

CMoveObject::CMoveObject()
{
}

CMoveObject::CMoveObject( const CMoveObject& obj )
	:
	CObject( obj )
{

}

CMoveObject::~CMoveObject()
{
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
