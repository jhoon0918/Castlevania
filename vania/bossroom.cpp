#include "stdafx.h"
#include "bossroom.h"

bossroom::bossroom()
{
}

bossroom::~bossroom()
{
}

HRESULT bossroom::init()
{
	IMAGEMANAGER->addImage("보스방백", "img/bossRbg.bmp", 2304, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스방", "img/bossRb.bmp", 2304, 720, true, RGB(255, 0, 255));
	CAMERAMANAGER->setBackScreenSize(2304, 720);
	play = PLAYERMANAGER->getPlayerJMemoryAddressLink();
	play->init();
	_em = ENEMYDATAMANAGER->getEnemyManagerMemoryAddressLink();
	_em->init();
	_em->setMinion(_Eastarte, 1150, 560);
	return S_OK;
}

void bossroom::release()
{
}

void bossroom::update()
{
	
	_em->update();
	play->update();
}

void bossroom::render()
{
	IMAGEMANAGER->findImage("보스방")->render(getMemDC());
	if (KEYMANAGER->isToggleKey(VK_TAB))
		IMAGEMANAGER->findImage("보스방백")->render(getMemDC());

	_em->render();

}
