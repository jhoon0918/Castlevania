#pragma once
#include "gameNode.h"

class playerJ;
class enemyManager;
class objectManager;
class testScene2 : public gameNode
{
private:

	playerJ* _pj;
	enemyManager* _em;
	objectManager* _om;
	RECT _rc;
	int x, y;
public:
	testScene2();
	~testScene2();

	HRESULT init();
	void release();
	void update();
	void render();
};

