#pragma once
#include "gameNode.h"
class startScene:public gameNode
{

private:
	int fadeOut;
	bool change;
public:
	startScene();
	~startScene();
	HRESULT init();
	void release();
	void update();
	void render();

};

