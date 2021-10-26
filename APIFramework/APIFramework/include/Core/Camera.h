#pragma once

#include "../Game.h"

class CCamera
{
private:
	POSITION	m_tPos;
	RESOLUTION	m_tClientRS;
	RESOLUTION	m_tWorldRS;
	POSITION	m_tPivot;
	class CObject* m_pTarget;

public:
	POSITION GetPos() const
	{
		return m_tPos;
	}

public:
	void SetTarget( class CObject* pObj );

	void SetPivot( const POSITION& tPivot )
	{
		m_tPivot = tPivot;
	}
	void SetPivot( float x, float y )
	{
		m_tPivot = POSITION( x, y );
	}

	void SetPos( const POSITION& tPos )
	{
		m_tPos = tPos;
	}
	void SetPos( float x, float y )
	{
		m_tPos = POSITION( x, y );
	}
	void SetClientResolution( const RESOLUTION& tRs )
	{
		m_tClientRS = tRs;
	}
	void SetClientResolution( int x, int y )
	{
		m_tClientRS = RESOLUTION( x, y );
	}
	void SetWorldResolution( const RESOLUTION& tRs )
	{
		m_tWorldRS = tRs;
	}
	void SetWorldResolution( int x, int y )
	{
		m_tWorldRS = RESOLUTION( x, y );
	}

public:
	bool Init( const POSITION& tPos, const RESOLUTION& tRS, const RESOLUTION& tWorldRS );

	void Input( float DeltaTime );

	void Update( float DeltaTime );

	DECLARE_SINGLE( CCamera )
};

