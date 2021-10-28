#pragma once
#include "StaticObject.h"


class CStage : public CStaticObject
{
private:
	friend class CObject;
	friend class CScene;

public:
	CStage();
	CStage( const CStage& stage );
	~CStage();

public:
	virtual bool Init();
	virtual void Input( float fDeltaTime );
	virtual int Update( float fDeltaTime );
	virtual int LateUpdate( float fDeltaTime );
	virtual void Collision( float fDeltaTime );
	virtual void Render( HDC hDC, float fDeltaTime );
	virtual CStage* Clone();
};

