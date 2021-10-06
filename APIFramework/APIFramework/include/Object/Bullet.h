#pragma once

#include "MoveObject.h"

class CBullet : public CMoveObject
{
private:
	friend class CObject;
	friend class CScene;

public:
	CBullet();
	CBullet( const CBullet& bullet );
	~CBullet();

private:
	float		m_fLimitDist;
	float		m_fDist;

public:
	void SetBulletDistance(float fDist)
	{
		m_fLimitDist = fDist;
	}

public:
	virtual bool Init();
	virtual int Update( float fDeltaTime );
	virtual int LateUpdate( float fDeltaTime );
	virtual void Collision( float fDeltaTime );
	virtual void Render( HDC hDC, float fDeltaTime );
	virtual CBullet* Clone();
};

