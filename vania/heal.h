#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class heal : public gameNode
{
private:
	playerJ* _pj;
	enemyManager* _em;
	RECT pond;
public:
	heal();
	~heal();

	HRESULT init();
	void release();
	void update();
	void render();
};

