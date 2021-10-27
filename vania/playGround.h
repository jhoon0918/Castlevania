#pragma once
#include "gameNode.h"
#include "testScene.h"
#include "testScene2.h"
#include "third.h"
#include "save.h"
#include "heal.h"
#include "bossroom.h"
#include "player.h"
#include "enemyManager.h"
#include "objectManager.h"
#include "startScene.h"
#include "clear.h"
#include "gameOver.h"

#pragma warning(disable:4996)

#define BATMAX 10
class playGround : public gameNode
{
private:
	playerJ* _play;
	enemyManager* _em;
	objectManager* _om;
	int x, y;
	int i;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
};

