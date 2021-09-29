#include "InGameScene.h"
#include "../Object/Player.h"
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

    // 본인 기능 수행.

    return true;
}
