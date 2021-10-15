#include "InGameScene.h"
#include "../Object/Player.h"
#include "../Object/Minion.h"
#include "../Object/Bullet.h"
#include "../Object/Stage.h"
#include "Layer.h"

CInGameScene::CInGameScene()
{
}

CInGameScene::~CInGameScene()
{
}

bool CInGameScene::Init()
{
    // 부모 Scene 클래스의 초기화 함수를 호출해줌.
    if( !CScene::Init() )
    {
        return false;
    }

    CLayer* pLayer = FindLayer( "Default" );

    CPlayer* pPlayer = CObject::CreateObj<CPlayer>( "Player", pLayer );

    SAFE_RELEASE( pPlayer );

    CMinion* pMinion = CObject::CreateObj<CMinion>( "Minion", pLayer );

    SAFE_RELEASE( pMinion );

    // 총알 프로토타입을 만들어 준다.
    CBullet* pBullet = CScene::CreatePrototype<CBullet>( "Bullet" );

    pBullet->SetSize( 50.f, 50.f );

    SAFE_RELEASE( pBullet );

    // Stage
    CLayer* pStageLayer = FindLayer( "Stage" );
    CStage* pStage = CObject::CreateObj<CStage>( "Stage", pStageLayer );

    SAFE_RELEASE( pPlayer );

    return true;
}
