#include "InGameScene.h"
#include "../Object/Player.h"
#include "../Object/Minion.h"
#include "../Object/Bullet.h"
#include "../Object/Stage.h"
#include "Layer.h"
#include "../Core/Camera.h"

CInGameScene::CInGameScene()
{
}

CInGameScene::~CInGameScene()
{
}

bool CInGameScene::Init()
{
    // �θ� Scene Ŭ������ �ʱ�ȭ �Լ��� ȣ������.
    if( !CScene::Init() )
    {
        return false;
    }

    CLayer* pLayer = FindLayer( "Default" );

    CPlayer* pPlayer = CObject::CreateObj<CPlayer>( "Player", pLayer );

    GET_SINGLE( CCamera )->SetTarget( pPlayer );
    GET_SINGLE( CCamera )->SetPivot( 0.8f, 0.3f );

    SAFE_RELEASE( pPlayer );

    CMinion* pMinion = CObject::CreateObj<CMinion>( "Minion", pLayer );

    SAFE_RELEASE( pMinion );

    // �Ѿ� ������Ÿ���� ����� �ش�.
    CBullet* pBullet = CScene::CreatePrototype<CBullet>( "Bullet" );

    pBullet->SetSize( 50.f, 50.f );

    SAFE_RELEASE( pBullet );

    // Stage
    CLayer* pStageLayer = FindLayer( "Stage" );
    CStage* pStage = CObject::CreateObj<CStage>( "Stage", pStageLayer );

    SAFE_RELEASE( pPlayer );

    return true;
}
