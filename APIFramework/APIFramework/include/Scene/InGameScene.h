#pragma once

#include "Scene.h"

class CInGameScene : public CScene
{
private:

	friend class CSceneManager;

private: // SceneManger�� ���ؼ��� �����ϵ��� ��.
	CInGameScene();
	virtual ~CInGameScene() override;

public:
	virtual bool Init() override;
};

