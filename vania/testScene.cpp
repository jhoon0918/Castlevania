#include "stdafx.h"
#include "testScene.h"
#include "player.h"
#include "enemyManager.h"


testScene::testScene()
{
}


testScene::~testScene()
{
}

HRESULT testScene::init()
{
	IMAGEMANAGER->addImage("È¦¹é", "img/hallbbg.bmp", 2360, 3024, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("È¦", "img/hallb.bmp", 2360, 3024, true, RGB(255, 0, 255));
	CAMERAMANAGER->setBackScreenSize(2360,3024);
	play = PLAYERMANAGER->getPlayerJMemoryAddressLink();
	play->setX(PLAYERMANAGER->getPX());
	play->setY(PLAYERMANAGER->getPY());
	play->setPHP(PLAYERMANAGER->getPHP());
	play->setPCHP(PLAYERMANAGER->getPCHP());
	play->setPRC(PLAYERMANAGER->getPRC());
	play->init();
	_em = ENEMYDATAMANAGER->getEnemyManagerMemoryAddressLink();
	_em->init();
	_em->setMinion(_Eblade,2000, 2000);
	_em->setMinion(_Eblade, 1650, 1350);
	_em->setMinion(_Ebone, 2000, 2800);
	_em->setMinion(_Ebone,2000, 2850);
	_em->setMinion(_Ebone, 1600, 1920);
	_em->setMinion(_Ebone, 1600, 1870);
	_em->setMinion(_Ebone, 1600, 1820);
	_em->setMinion(_Ecorner, 1350, 2350);
	_em->setMinion(_Ecorner, 1350, 1000);
	_em->setMinion(_Enyx, 400, 1650);
	_em->setMinion(_Enyx, 1100, 1650);
	_em->setMinion(_Enyx, 400, 700);
	_om = OBJECTDATAMANAGER->getObjectManagerMemoryAddressLink();
	_om->init();
	
	
	
	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("Å×½ºÆ®¾À2");
	}
	play->update();
	_em->update();
	_om->update();
}

void testScene::render()
{
	
	IMAGEMANAGER->findImage("È¦")->render(getMemDC());
	if(KEYMANAGER->isToggleKey(VK_TAB))
		IMAGEMANAGER->findImage("È¦¹é")->render(getMemDC());
	_em->render();
	_om->render();
}
