#include "InGameScene.h"

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

    // ���� ��� ����.

    return true;
}
