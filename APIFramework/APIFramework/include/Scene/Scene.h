#pragma once

#include "../Game.h"

class CScene
{
protected:

	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene() = 0; // 순수 가상함수. 추상클래스.

private:
	static unordered_map<string, class CObject*> m_mapPrototype;

public:
	static void ErasePrototype( const string& strTag );
	static void ErasePrototype();
	static CObject* FindPrototype( const string& strKey );

protected:
	list<class CLayer*> m_LayerList;

public:
	class CLayer* CreateLayer( const string& strTag, int iZOrder = 0 );
	CLayer* FindLayer( const string& strTag );

public:
	virtual bool Init();
	virtual void Input( float fDeltaTime );
	virtual int Update( float fDeltaTime );
	virtual int LateUpdate( float fDeltaTime );
	virtual void Collision( float fDeltaTime );
	virtual void Render( HDC hDC, float fDeltaTime );

public:
	static bool LayerSort( CLayer* pL1, CLayer* pL2 );

	template <typename T>
	static T* CreatePrototype( const string& strTag )
	{
		T* pObj = new T;

		pObj->SetTag( strTag );

		if( !pObj->Init() )
		{
			SAFE_RELEASE( pObj );
			return nullptr;
		}

		pObj->AddRef();
		m_mapPrototype.insert( make_pair( strTag, pObj ) );

		return pObj;
	}
};

