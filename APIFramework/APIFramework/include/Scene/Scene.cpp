#include "Scene.h"
#include "Layer.h"

CScene::CScene()
{
    CLayer* pLayer = CreateLayer( "UI", INT_MAX );
    pLayer = CreateLayer( "Default" );
}

CScene::~CScene()
{
    Safe_Delete_VecList( m_LayerList );
}

CLayer* CScene::CreateLayer( const string& strTag, int iZOrder )
{
    CLayer* pLayer = new CLayer;

    pLayer->SetTag( strTag );
    pLayer->SetZOrder( iZOrder );
    pLayer->SetScene( this );

    m_LayerList.push_back( pLayer );

    if( m_LayerList.size() >= 2 )
    {
        m_LayerList.sort( CScene::LayerSort );
    }

    return pLayer;
}

CLayer* CScene::FindLayer( const string& strTag )
{
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for( iter = m_LayerList.begin(); iter != iterEnd; ++iter )
    {
        if( (*iter)->GetTag() == strTag )
            return *iter;
    }

    return nullptr;
}

bool CScene::Init()
{
    return true;
}

void CScene::Input( float fDeltaTime )
{
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for( iter = m_LayerList.begin(); iter != iterEnd; )
    {
        if( !(*iter)->GetEnable() )
        {
            ++iter;
            continue;
        }

        (*iter)->Input( fDeltaTime );

        if( !(*iter)->GetLife() )
        {
            SAFE_DELETE( (*iter) );
            iter = m_LayerList.erase( iter );
            iterEnd = m_LayerList.end();
        }

        else
            ++iter;
    }
}

int CScene::Update( float fDeltaTime )
{
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for( iter = m_LayerList.begin(); iter != iterEnd; )
    {
        if( !(*iter)->GetEnable() )
        {
            ++iter;
            continue;
        }

        (*iter)->Update( fDeltaTime );

        if( !(*iter)->GetLife() )
        {
            SAFE_DELETE( (*iter) );
            iter = m_LayerList.erase( iter );
            iterEnd = m_LayerList.end();
        }

        else
            ++iter;
    }
    return 0;
}

int CScene::LateUpdate( float fDeltaTime )
{
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for( iter = m_LayerList.begin(); iter != iterEnd; )
    {
        if( !(*iter)->GetEnable() )
        {
            ++iter;
            continue;
        }

        (*iter)->LateUpdate( fDeltaTime );

        if( !(*iter)->GetLife() )
        {
            SAFE_DELETE( (*iter) );
            iter = m_LayerList.erase( iter );
            iterEnd = m_LayerList.end();
        }

        else
            ++iter;
    }
    return 0;
}

void CScene::Collision( float fDeltaTime )
{
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for( iter = m_LayerList.begin(); iter != iterEnd; )
    {
        if( !(*iter)->GetEnable() )
        {
            ++iter;
            continue;
        }

        (*iter)->Collision( fDeltaTime );

        if( !(*iter)->GetLife() )
        {
            SAFE_DELETE( (*iter) );
            iter = m_LayerList.erase( iter );
            iterEnd = m_LayerList.end();
        }

        else
            ++iter;
    }
}

void CScene::Render( HDC hDC, float fDeltaTime )
{
    list<CLayer*>::iterator iter;
    list<CLayer*>::iterator iterEnd = m_LayerList.end();

    for( iter = m_LayerList.begin(); iter != iterEnd; )
    {
        if( !(*iter)->GetEnable() )
        {
            ++iter;
            continue;
        }

        (*iter)->Render( hDC, fDeltaTime );

        if( !(*iter)->GetLife() )
        {
            SAFE_DELETE( (*iter) );
            iter = m_LayerList.erase( iter );
            iterEnd = m_LayerList.end();
        }

        else
            ++iter;
    }
}

bool CScene::LayerSort( CLayer* pL1, CLayer* pL2 )
{
    return pL1->GetZOrder() < pL2->GetZOrder();
}
