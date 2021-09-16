#pragma once

#include "../Game.h"

class CScene
{
protected:

	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene() = 0; // ���� �����Լ�. �߻�Ŭ����.

protected:
	list<class CLayer*> m_LayerList;

public:
	class CLayer* CreateLayer( const string& strTag, int iZOrder = 0 );

public:
	virtual bool Init();

public:
	static bool LayerSort( CLayer* pL1, CLayer* pL2 );
};

