#include "Texture.h"
#include "../Core/PathManager.h"

CTexture::CTexture()
	:
	m_hMemDC( nullptr )
{
}

CTexture::~CTexture()
{
	SelectObject( m_hMemDC, m_hOldBitmap );
	DeleteObject( m_hBitmap );
	DeleteDC( m_hMemDC );
}

bool CTexture::LoadTexture( HINSTANCE hInst, HDC hDC, 
	const string& strKey, const wchar_t* pFileName, const string& strPathKey )
{
	// Make memory DC
	m_hMemDC = CreateCompatibleDC( hDC );

	// Make a whole path
	const wchar_t* pPath = GET_SINGLE( CPathManager )->FindPath( strPathKey );

	wstring strPath;
	if( pPath )
		strPath = pPath;

	strPath += pFileName;

	m_hBitmap = (HBITMAP)LoadImage( hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	// Set DC with Bitmap tool
	m_hOldBitmap = (HBITMAP)SelectObject( m_hMemDC, m_hBitmap );

	GetObject( m_hBitmap, sizeof( m_tInfo ), &m_tInfo );

	return true;
}
