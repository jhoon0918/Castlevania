#include "stdafx.h"
#include "gameOver.h"

gameOver::gameOver()
{
}

gameOver::~gameOver()
{
}

HRESULT gameOver::init()
{
	IMAGEMANAGER->addImage("gameover", "img/gameover.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gameoverment", "img/gameoverMent.bmp", 1280, 720, true, RGB(255, 0, 255));
	return S_OK;
}

void gameOver::release()
{
}

void gameOver::update()
{
}

void gameOver::render()
{
}
