#include "StaticObject.h"

CStaticObject::CStaticObject()
{
}

CStaticObject::CStaticObject( const CStaticObject& obj )
    :
    CObject( obj )
{
}

CStaticObject::~CStaticObject()
{
}

void CStaticObject::Input( float fDeltaTime )
{
}

int CStaticObject::Update( float fDeltaTime )
{
    return 0;
}

int CStaticObject::LateUpdate( float fDeltaTime )
{
    return 0;
}

void CStaticObject::Collision( float fDeltaTime )
{
}

void CStaticObject::Render( HDC hDC, float fDeltaTime )
{
}
