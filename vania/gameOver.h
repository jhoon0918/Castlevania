#pragma once
#include "gameNode.h"
class gameOver:public gameNode
{
private:
public:
	gameOver();
	~gameOver();
	HRESULT init();
	void release();
	void update();
	void render();

};

