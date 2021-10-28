#pragma once

#include "Object.h"

class CStaticObject : public CObject
{
protected:
	CStaticObject();
	CStaticObject( const CStaticObject& obj );
	virtual ~CStaticObject();

public:
	virtual bool Init() = 0;
	virtual void Input( float fDeltaTime );
	virtual int Update( float fDeltaTime );
	virtual int LateUpdate( float fDeltaTime );
	virtual void Collision( float fDeltaTime );
	virtual void Render( HDC hDC, float fDeltaTime );
	virtual CStaticObject* Clone() = 0;
};

