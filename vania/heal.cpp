#include "stdafx.h"
#include "heal.h"

heal::heal()
{
}

heal::~heal()
{
}

HRESULT heal::init()
{
	IMAGEMANAGER->addImage("Èú¹é", "img/healbg.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Èú", "img/heal.bmp", 1280, 720, true, RGB(255, 0, 255));
	CAMERAMANAGER->setBackScreenSize(1280, 720);
	_pj = PLAYERMANAGER->getPlayerJMemoryAddressLink();
	_pj->init();
	_em = ENEMYDATAMANAGER->getEnemyManagerMemoryAddressLink();
	_em->init();
	_pj->setPCHP(PLAYERMANAGER->getPCHP());
	pond = RectMake(340, 575, 600, 70);
	return S_OK;
	
}

void heal::release()
{
}

void heal::update()
{
	RECT temp;
	_pj->setPCHP(PLAYERMANAGER->getPCHP());
	_em->update();
	_pj->update();
	if(IntersectRect(&temp,&pond,&(PLAYERMANAGER->getPRC())))
	{ 
		_pj->setPCHP(_pj->getPHP());
	}
	pond = RectMake(340, 575, 600, 70);
}

void heal::render()
{
	IMAGEMANAGER->findImage("Èú")->render(getMemDC());
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		IMAGEMANAGER->findImage("Èú¹é")->render(getMemDC());
		Rectangle(getMemDC(), pond);
	}
	_em->render();
	
}
