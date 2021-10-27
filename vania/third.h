#pragma once
#include "gameNode.h"

class third : public gameNode
{
private:
	playerJ* play;
	enemyManager* _em;
	objectManager* _om;
public:
	third();
	~third();

	HRESULT init();
	void release();
	void update();
	void render();
};

