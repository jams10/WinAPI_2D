#pragma once

#include "Scene.h"

class CInGameScene : public CScene
{
private:

	friend class CSceneManager;

private: // SceneManger를 통해서만 생성하도록 함.
	CInGameScene();
	virtual ~CInGameScene() override;

public:
	virtual bool Init() override;
};

