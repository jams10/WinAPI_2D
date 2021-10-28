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
    CObject::Input( fDeltaTime );
}

int CStaticObject::Update( float fDeltaTime )
{
    CObject::Update( fDeltaTime );
    return 0;
}

int CStaticObject::LateUpdate( float fDeltaTime )
{
    CObject::LateUpdate( fDeltaTime );
    return 0;
}

void CStaticObject::Collision( float fDeltaTime )
{
    CObject::Collision( fDeltaTime );
}

void CStaticObject::Render( HDC hDC, float fDeltaTime )
{
    CObject::Render( hDC, fDeltaTime );
}
