#pragma once

#include "../Game.h"

class CObject
{
protected:
	CObject();
	virtual ~CObject();

protected:
	int			m_iRef;

public:
	void AddRef()
	{
		++m_iRef;
	}

	int Release()
	{
		--m_iRef;

		if( m_iRef == 0 )
		{
			delete this;
			return 0;
		}
		return m_iRef;
	}

protected:
	string      m_strTag;
	POSITION	m_tPos;
	_SIZE		m_tSize;

public:
	string GetTag() const
	{
		return m_strTag;
	}

	POSITION GetPos() const
	{
		return m_tPos;
	}

	_SIZE GetSize() const
	{
		return m_tSize;
	}

public:
	// tag
	void SetTag( const string& strTag )
	{
		m_strTag = strTag;
	}
	// pos
	void SetPos( const POSITION& tPos )
	{
		m_tPos = tPos;
	}
	void SetPos( const POINT& pos )
	{
		m_tPos = pos;
	}
	void SetPos( float x, float y )
	{
		m_tPos.x = x;
		m_tPos.y = y;
	}
	// size
	void SetSize( const POSITION& tSize )
	{
		m_tSize = tSize;
	}
	void SetSize( const POINT& size )
	{
		m_tSize = size;
	}
	void SetSize( float x, float y )
	{
		m_tSize.x = x;
		m_tSize.y = y;
	}

public:
	virtual bool Init();
	virtual void Input( float fDeltaTime );
	virtual int Update( float fDeltaTime );
	virtual int LateUpdate( float fDeltaTime );
	virtual void Collision( float fDeltaTime );
	virtual void Render( HDC hDC, float fDeltaTime );
};

