#pragma once

#include "../Game.h"

class CObject
{
protected:
	CObject();
	virtual ~CObject();

protected:
	POSITION	m_tPos;
	_SIZE		m_tSize;
};

