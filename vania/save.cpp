#include "stdafx.h"
#include "save.h"

save::save()
{
}

save::~save()
{
}

HRESULT save::init()
{
	IMAGEMANAGER->addImage("세이브백", "img/savebg.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("세이브", "img/saveb.bmp", 1280, 720, true, RGB(255, 0, 255));
	CAMERAMANAGER->setBackScreenSize(1280, 720);
	play = PLAYERMANAGER->getPlayerJMemoryAddressLink();
	play->setPCHP(PLAYERMANAGER->getPCHP());
	play->init();
	_em = ENEMYDATAMANAGER->getEnemyManagerMemoryAddressLink();
	_em->init();
	return S_OK;
}

void save::release()
{
}

void save::update()
{
	play->setPCHP(PLAYERMANAGER->getPCHP());
	play->update();
	_em->update();
}

void save::render()
{
	IMAGEMANAGER->findImage("세이브")->render(getMemDC());
	if (KEYMANAGER->isToggleKey(VK_TAB))
		IMAGEMANAGER->findImage("세이브백")->render(getMemDC());
	_em->render();
}
