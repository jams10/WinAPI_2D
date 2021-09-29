#pragma once

#include "Object.h"

class CMoveObject : public CObject
{
protected:
	CMoveObject();
	CMoveObject( const CMoveObject& obj );
	virtual ~CMoveObject();

public:
	virtual bool Init() = 0;
	virtual void Input( float fDeltaTime );
	virtual int Update( float fDeltaTime );
	virtual int LateUpdate( float fDeltaTime );
	virtual void Collision( float fDeltaTime );
	virtual void Render( HDC hDC, float fDeltaTime );
};

