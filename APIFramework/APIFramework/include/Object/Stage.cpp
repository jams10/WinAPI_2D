#include "Stage.h"
#include "../Resources/Texture.h"
#include "../Core.h"

CStage::CStage()
{
}

CStage::CStage( const CStage& stage )
	:
	CStaticObject( stage )
{

}

CStage::~CStage()
{
}

bool CStage::Init()
{
	SetPos( 0.f, 0.f );
	SetSize( 1280.f, 720.f );
	SetPivot( 0.0f, 0.0f );

	SetTexture( "Stage1", L"Stage1.bmp" );

	return true;
}

void CStage::Input( float fDeltaTime )
{
	CStaticObject::Input( fDeltaTime );
}

int CStage::Update( float fDeltaTime )
{
	CStaticObject::Update( fDeltaTime );
	return 0;
}

int CStage::LateUpdate( float fDeltaTime )
{
	CStaticObject::LateUpdate( fDeltaTime );
	return 0;
}

void CStage::Collision( float fDeltaTime )
{
	CStaticObject::Collision( fDeltaTime );
}

void CStage::Render( HDC hDC, float fDeltaTime )
{
	//CStaticObject::Render( hDC, fDeltaTime );

	if( m_pTexture )
	{
		BitBlt( 
			hDC, m_tPos.x - m_tSize.x * m_tPivot.x, 
			m_tPos.y - m_tSize.x * m_tPivot.y, 
			GETRESOLUTION.iW, GETRESOLUTION.iH, m_pTexture->GetDC(),
			0, 0, SRCCOPY );
	}
}

CStage* CStage::Clone()
{
	return new CStage(*this);
}
