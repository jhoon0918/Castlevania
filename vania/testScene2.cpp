#include "stdafx.h"
#include "testScene2.h"
#include "player.h"
#include "enemyManager.h"
#include "objectManager.h"

testScene2::testScene2()
{
}


testScene2::~testScene2()
{
}

HRESULT testScene2::init()
{
	IMAGEMANAGER->addImage("½ÃÀÛ¸Ê¹é", "img/StartingPointbbg.bmp", 1280,720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("½ÃÀÛ¸Ê", "img/StartingPointb.bmp", 1280, 720, true, RGB(255, 0, 255));
	CAMERAMANAGER->setBackScreenSize(1280, 720);
	

	DATAMANAGER->getPX();
	DATAMANAGER->getPY();
	DATAMANAGER->getPRC();

	_pj = PLAYERMANAGER->getPlayerJMemoryAddressLink();
	_pj->init();
	_em = ENEMYDATAMANAGER->getEnemyManagerMemoryAddressLink();
	_em->init();
	_om = OBJECTDATAMANAGER->getObjectManagerMemoryAddressLink();
	_om->init();
	//_em->setMinion(_Ebat,120, 295);
	_em->setMinion(_Eblade,300, 200);
	_om->setItem(0, 700, 630);
	_om->setItem(1, 750, 630);
	_om->setItem(2, 800, 630);
	_pj->setPCHP(PLAYERMANAGER->getPCHP());
	
		return S_OK;
}

void testScene2::release()
{
}

void testScene2::update()
{
	_pj->setPCHP(PLAYERMANAGER->getPCHP());
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("Å×½ºÆ®¾À1");
	}
	_em->update();
	_om->update();
	_pj->update();
}

void testScene2::render()
{

	IMAGEMANAGER->findImage("½ÃÀÛ¸Ê")->render(getMemDC());
	if (KEYMANAGER->isToggleKey(VK_TAB))
	IMAGEMANAGER->findImage("½ÃÀÛ¸Ê¹é")->render(getMemDC());
	_em->render();
	_om->render();
}
