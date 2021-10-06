#include "Object.h"
#include "../Scene/Layer.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"

list<CObject*> CObject::m_ObjList;

CObject::CObject()
{
}

CObject::CObject( const CObject& obj )
{
	*this = obj;
}

CObject::~CObject()
{
}

void CObject::AddObj( CObject* pObj )
{
	pObj->AddRef();
	m_ObjList.push_back( pObj );
}

CObject* CObject::FindObject( const string& strTag )
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for( iter = m_ObjList.begin(); iter != iterEnd; ++iter )
	{
		if( (*iter)->GetTag() == strTag )
		{
			(*iter)->AddRef();
			return *iter;
		}
	}

	return nullptr;
}

void CObject::EraseObj( CObject* pObj )
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for( iter = m_ObjList.begin(); iter != iterEnd; ++iter )
	{
		if( *iter == pObj )
		{
			SAFE_RELEASE( (*iter) );
			iter = m_ObjList.erase( iter );
			return;
		}
	}
}

void CObject::EraseObj( const string& strTag )
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for( iter = m_ObjList.begin(); iter != iterEnd; ++iter )
	{
		if( (*iter )->GetTag() == strTag )
		{
			SAFE_RELEASE( (*iter) );
			iter = m_ObjList.erase( iter );
			return;
		}
	}
}

void CObject::EraseObj()
{
	Safe_Release_VecList( m_ObjList );
}

void CObject::Input( float fDeltaTime )
{
}

int CObject::Update( float fDeltaTime )
{
	return 0;
}

int CObject::LateUpdate( float fDeltaTime )
{
	return 0;
}

void CObject::Collision( float fDeltaTime )
{
}

void CObject::Render( HDC hDC, float fDeltaTime )
{
}

CObject* CObject::CreateCloneObj( const string& strPrototypeKey, const string& strTag, CLayer* pLayer )
{
	CObject* pProto = CScene::FindPrototype( strPrototypeKey );

	if( !pProto ) return nullptr;

	CObject* pObj = pProto->Clone();

	pObj->SetTag( strTag );

	if( pLayer )
	{
		pLayer->AddObject( pObj );
	}

	AddObj( pObj );

	return pObj;
}
