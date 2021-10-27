#pragma once
#include "gameNode.h"
class objectManager;


class testScene : public gameNode
{
private:
	playerJ* play;
	enemyManager* _em;
	objectManager* _om;

	int x, y;
	int num;

public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

