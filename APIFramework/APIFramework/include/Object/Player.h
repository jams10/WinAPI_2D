#pragma once

#include "MoveObject.h"

class CPlayer : public CMoveObject
{
private:
	friend class CObject;
	friend class CScene;

private:
	CPlayer();
	CPlayer( const CPlayer& player );
	~CPlayer();

public:
	virtual bool Init();
	virtual void Input( float fDeltaTime );
	virtual int Update( float fDeltaTime );
	virtual int LateUpdate( float fDeltaTime );
	virtual void Collision( float fDeltaTime );
	virtual void Render( HDC hDC, float fDeltaTime );
	virtual CPlayer* Clone();

private:
	void Fire();
};

