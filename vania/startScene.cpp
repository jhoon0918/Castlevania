#include "stdafx.h"
#include "startScene.h"

startScene::startScene()
{
}

startScene::~startScene()
{
}

HRESULT startScene::init()
{

	IMAGEMANAGER->addImage("null", "img/nullback.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("title", "img/title.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("gamestart", "img/gamestart.bmp", 678, 24, 2, 1, true, RGB(255, 0, 255)); CAMERAMANAGER->setBackScreenSize(1280, 720);
	CAMERAMANAGER->setBackScreenSize(1280, 720);

	DATAMANAGER->setN(9);
	fadeOut = 255;
	change = false;
	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))change = true;

	if (change)
	{
		fadeOut--;
		if (fadeOut < 105)
		{
			DATAMANAGER->setN(1);
			PLAYERMANAGER->setPX(1200);
			PLAYERMANAGER->setPY(WINSIZEY / 2);	
		}
		if (fadeOut <= 100)SCENEMANAGER->changeScene("Å×½ºÆ®¾À2");
		
	}
}

void startScene::render()
{
	IMAGEMANAGER->findImage("title")->alphaRender(getMemDC(), fadeOut);
	IMAGEMANAGER->findImage("gamestart")->frameRender(getMemDC(), WINSIZEX-339, WINSIZEY);
}
