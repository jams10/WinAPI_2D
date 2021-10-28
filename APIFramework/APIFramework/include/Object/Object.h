#pragma once

#include "../Game.h"
#include "../Ref.h"
#include "../Scene/Layer.h"

class CObject : public CRef
{
protected:
	friend class CScene;

protected:
	CObject();
	CObject( const CObject& obj );
	virtual ~CObject();

private:
	static list<CObject*>	m_ObjList;

public:
	static void AddObj( CObject* pObj );
	static CObject* FindObject( const string& strTag );
	static void EraseObj( CObject* pObj );
	static void EraseObj( const string& strTag );
	static void EraseObj();

protected:
	class CScene* m_pScene;
	class CLayer* m_pLayer;

protected:
	string			m_strTag;
	POSITION		m_tPos;
	_SIZE			m_tSize;
	POSITION		m_tPivot;
	class CTexture* m_pTexture;

public:
	float GetLeft() const
	{
		return m_tPos.x - m_tSize.x * m_tPivot.x;
	}
	float GetRight() const
	{
		return GetLeft() + m_tSize.x;
	}
	float GetTop() const
	{
		return m_tPos.y - m_tSize.y * m_tPivot.y;
	}
	float GetBottom() const
	{
		return GetTop() + m_tSize.y;
	}
	POSITION GetCenter() const
	{
		return POSITION( GetLeft() + m_tSize.x / 2.f, GetTop() + m_tSize.y / 2.f );
	}

	CScene* GetScene() const
	{
		return m_pScene;
	}
	CLayer* GetLayer() const
	{
		return m_pLayer;
	}
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
	// scene
	void SetScene( class CScene* pScene )
	{
		m_pScene = pScene;
	}
	// layer
	void SetLayer( class CLayer* pLayer )
	{
		m_pLayer = pLayer;
	}
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
	// pivot
	POSITION GetPivot() const
	{
		return m_tPivot;
	}
	void SetPivtot( const POSITION& tPivot )
	{
		m_tPivot = tPivot;
	}
	void SetPivtot( const POINT& pivot )
	{
		m_tPivot = pivot;
	}
	void SetPivot( float x, float y )
	{
		m_tPivot.x = x;
		m_tPivot.y = y;
	}
	// texture
	void SetTexture( class CTexture* pTexture );
	void SetTexture( const string& strKey,
		const wchar_t* pFileName = NULL,
		const string& strPathKey = TEXTURE_PATH );

public:
	virtual bool Init() = 0;
	virtual void Input( float fDeltaTime );
	virtual int Update( float fDeltaTime );
	virtual int LateUpdate( float fDeltaTime );
	virtual void Collision( float fDeltaTime );
	virtual void Render( HDC hDC, float fDeltaTime );
	virtual CObject* Clone() = 0;

public:
	template <typename T>
	static T* CreateObj( const string& strTag, class CLayer* pLayer = nullptr )
	{
		T* pObj = new T;

		pObj->SetTag( strTag );

		if( !pObj->Init() )
		{
			SAFE_RELEASE( pObj );
			return nullptr;
		}

		if( pLayer )
		{
			pLayer->AddObject( pObj );
		}

		AddObj( pObj );

		return pObj;
	}

	static CObject* CreateCloneObj( const string& strPrototypeKey, const string& strTag, CLayer* pLayer = nullptr );
};