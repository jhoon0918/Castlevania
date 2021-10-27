#include "stdafx.h"
#include "third.h"
#include "player.h"
#include "enemyManager.h"

third::third()
{
}

third::~third()
{
}

HRESULT third::init()
{
	IMAGEMANAGER->addImage("¹öÆ¼Ä®¹é", "img/verticalhallbg.bmp", 3456, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¹öÆ¼Ä®", "img/verticalhallb.bmp", 3456, 720, true, RGB(255, 0, 255));
	CAMERAMANAGER->setBackScreenSize(3456, 720);
	play = PLAYERMANAGER->getPlayerJMemoryAddressLink();
	play->init();
	_em = ENEMYDATAMANAGER->getEnemyManagerMemoryAddressLink();
	_em->init();
	_om = OBJECTDATAMANAGER->getObjectManagerMemoryAddressLink();
	_om->init();
	_em->setMinion(_Eblade, 1500, 220);
	_em->setMinion(_Ebone, 2500, 620);
	_em->setMinion(_Ebone, 2500, 560);
	_em->setMinion(_Ebone, 750, 570);
	_em->setMinion(_Ebone, 750, 620);	
	_em->setMinion(_Ebone, 450, 550);
	_em->setMinion(_Ebone, 110, 370);
	_em->setMinion(_Ebone, 110, 420);
	_em->setMinion(_Ebone, 110, 470);
	_em->setMinion(_Ebat, 60, 300);
	_em->setMinion(_Enyx, 1350, 600);
	return S_OK;
}

void third::release()
{
}

void third::update()
{
	play->update();
	_em->update();
	_om->update();
}

void third::render()
{
	IMAGEMANAGER->findImage("¹öÆ¼Ä®")->render(getMemDC());
	if (KEYMANAGER->isToggleKey(VK_TAB))
		IMAGEMANAGER->findImage("¹öÆ¼Ä®¹é")->render(getMemDC());
	_em->render();
	_om->render();
}
