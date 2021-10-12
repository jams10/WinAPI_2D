#include "ResourcesManager.h"
#include "Texture.h"

DEFINITION_SINGLE( CResourcesManager )


CResourcesManager::CResourcesManager()
{
}

CResourcesManager::~CResourcesManager()
{
	Safe_Release_Map( m_mapTexture );
}

CTexture* CResourcesManager::LoadTexture( const string& strKey, const wchar_t* pFileName, const string& strPathKey )
{
	return nullptr;
}