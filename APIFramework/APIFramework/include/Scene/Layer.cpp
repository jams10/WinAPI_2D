#include "Layer.h"
#include "../Object/Object.h"

CLayer::CLayer()
	:
	m_strTag( "" ),
	m_iZOrder( 0 ),
	m_pScene( nullptr ),
	m_bLife( true ),
	m_bEnable( true )
{
}

CLayer::~CLayer()
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for( iter = m_ObjList.begin(); iter != iterEnd; ++iter)
	{
		CObject::EraseObj( *iter );
		SAFE_RELEASE( (*iter) );
	}

	m_ObjList.clear();
}

void CLayer::AddObject( CObject* pObject )
{
	pObject->SetScene( m_pScene );
	pObject->SetLayer( this );
	pObject->AddRef();

	m_ObjList.push_back( pObject );
}

void CLayer::Input( float fDeltaTime )
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for( iter = m_ObjList.begin(); iter != iterEnd; )
	{
		if( !(*iter)->GetEnable() )
		{
			++iter;
			continue;
		}

		(*iter)->Input( fDeltaTime );

		if( !(*iter)->GetLife() )
		{
			CObject::EraseObj( *iter );
			SAFE_RELEASE( (*iter) );
			iter = m_ObjList.erase( iter );
			iterEnd = m_ObjList.end();
		}

		else
			++iter;
	}
}

int CLayer::Update( float fDeltaTime )
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for( iter = m_ObjList.begin(); iter != iterEnd; )
	{
		if( !(*iter)->GetEnable() )
		{
			++iter;
			continue;
		}

		(*iter)->Update( fDeltaTime );

		if( !(*iter)->GetLife() )
		{
			CObject::EraseObj( *iter );
			SAFE_RELEASE( (*iter) );
			iter = m_ObjList.erase( iter );
			iterEnd = m_ObjList.end();
		}

		else
			++iter;
	}
	return 0;
}

int CLayer::LateUpdate( float fDeltaTime )
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for( iter = m_ObjList.begin(); iter != iterEnd; )
	{
		if( !(*iter)->GetEnable() )
		{
			++iter;
			continue;
		}

		(*iter)->LateUpdate( fDeltaTime );

		if( !(*iter)->GetLife() )
		{
			CObject::EraseObj( *iter );
			SAFE_RELEASE( (*iter) );
			iter = m_ObjList.erase( iter );
			iterEnd = m_ObjList.end();
		}

		else
			++iter;
	}
	return 0;
}

void CLayer::Collision( float fDeltaTime )
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for( iter = m_ObjList.begin(); iter != iterEnd; )
	{
		if( !(*iter)->GetEnable() )
		{
			++iter;
			continue;
		}

		(*iter)->Collision( fDeltaTime );

		if( !(*iter)->GetLife() )
		{
			CObject::EraseObj( *iter );
			SAFE_RELEASE( (*iter) );
			iter = m_ObjList.erase( iter );
			iterEnd = m_ObjList.end();
		}

		else
			++iter;
	}
}

void CLayer::Render( HDC hDC, float fDeltaTime )
{
	list<CObject*>::iterator iter;
	list<CObject*>::iterator iterEnd = m_ObjList.end();

	for( iter = m_ObjList.begin(); iter != iterEnd; )
	{
		if( !(*iter)->GetEnable() )
		{
			++iter;
			continue;
		}

		(*iter)->Render( hDC, fDeltaTime );

		if( !(*iter)->GetLife() )
		{
			CObject::EraseObj( *iter );
			SAFE_RELEASE( (*iter) );
			iter = m_ObjList.erase( iter );
			iterEnd = m_ObjList.end();
		}

		else
			++iter;
	}
}
