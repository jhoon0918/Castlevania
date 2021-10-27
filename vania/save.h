#pragma once
#include "gameNode.h"
#include "player.h"
#include "enemyManager.h"

class save: public gameNode
{
private:
	playerJ* play;
	enemyManager* _em;
public:
	save();
	~save();

	HRESULT init();
	void release();
	void update();
	void render();
};


