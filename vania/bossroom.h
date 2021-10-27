#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class bossroom : public gameNode
{
private:
	playerJ* play;
	enemyManager* _em;
public:
	bossroom();
	~bossroom();

	HRESULT init();
	void release();
	void update();
	void render();
};


