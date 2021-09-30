#pragma once

#include "MoveObject.h"

class CMinion : public CMoveObject
{
private:

	friend class CObject;

private:
	CMinion();
	CMinion( const CMinion& minion );
	~CMinion();

private:

	MOVE_DIR m_eDir;

public:
	virtual bool Init();
	virtual int Update( float fDeltaTime );
	virtual int LateUpdate( float fDeltaTime );
	virtual void Collision( float fDeltaTime );
	virtual void Render( HDC hDC, float fDeltaTime );

};

