#pragma once

#include "../Game.h"

class CScene
{
protected:

	friend class CSceneManager;

protected:
	CScene();
	virtual ~CScene() = 0; // 순수 가상함수. 추상클래스.

public:
	virtual bool Init();
};

