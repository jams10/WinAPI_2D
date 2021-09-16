#pragma once

#include "../Game.h"

class CLayer
{
private:
	friend class CScene;

private:
	CLayer();

public:
	~CLayer();

private:
	class CScene*	m_pScene;
	string			m_strTag;
	int				m_iZOrder;

public:
	void SetScene( class CScene* pScene )
	{
		m_pScene = pScene;
	}

	void SetTag( const string& strTag )
	{
		m_strTag = strTag;
	}

	void SetZOrder( int iZOrder )
	{
		m_iZOrder = iZOrder;
	}

	CScene* GetScene()
	{
		return m_pScene;
	}

	string GetTag() const
	{
		return m_strTag;
	}

	int GetZOrder() const
	{
		return m_iZOrder;
	}

};

