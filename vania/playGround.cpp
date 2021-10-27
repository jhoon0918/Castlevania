#include "stdafx.h"
#include "playGround.h"
#include "player.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//ÃÊ±âÈ­´Â ¿©±â´Ù ÇÏ¼¼¿ä Á¦¹ß
HRESULT playGround::init()
{
	gameNode::init(true);
	IMAGEMANAGER->addFrameImage("blade", "img/blade.bmp", 240, 96, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bladeidle", "img/bladeIdle.bmp", 48, 96, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bat", "img/bat.bmp", 624, 294, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("batIdle", "img/bat idle.bmp", 90, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boneIdle", "img/bone idle.bmp", 116, 116, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boneShot", "img/bone shot.bmp", 174, 112, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cornerMove", "img/corner move.bmp", 240, 212, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cornerAttack", "img/corner attack1.bmp", 558, 340, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("nyx attack", "img/nyx attack.bmp", 277, 202, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("nyx die", "img/nyx die.bmp", 289, 162, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("nyx stand", "img/nyx stand.bmp", 712, 204, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("nyx rush", "img/nyx rush.bmp", 270, 228, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("nyx hitted", "img/nyx hitted.bmp", 218, 198, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossIdle","img/boss idle.bmp",280,300,5,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("bossJump","img/boss jump.bmp",1331,300,11,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("bossKiss","img/boss kiss.bmp",658,300,7,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("bossMelee","img/boss melee.bmp",600,302,5,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("bossTorna","img/boss tornado.bmp",2938,320,13,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("bossMove","img/bossmove.bmp",924,300,11,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("fireball", "img/fireball.bmp", 415, 90, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("tornado","img/torando effect.bmp",180,154,4,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("triangle","img/triangle.bmp",315,54,3,1,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("heart","img/heart.bmp",64,128,1,2,true,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("dagger", "img/dagger.bmp", 72, 60, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lightning","img/lightning.bmp",18432,1024,18,1,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("combi item","img/combi item.bmp",32,32,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("djump item","img/djump item.bmp",30,30,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("heart item","img/Iheart.bmp",14,14,true,RGB(255,0,255));
	
	

	//SCENEMANAGER->addScene("Å¸ÀÌÆ²",new startScene);
	//SCENEMANAGER->addScene("°ÔÀÓ¿À¹ö",new gameOver);
	//SCENEMANAGER->addScene("Å¬¸®¾î",new clear);
	SCENEMANAGER->addScene("Å×½ºÆ®¾À1", new testScene);
	SCENEMANAGER->addScene("Å×½ºÆ®¾À2", new testScene2);
	SCENEMANAGER->addScene("¾À3", new third);
	SCENEMANAGER->addScene("¾À4", new heal);
	SCENEMANAGER->addScene("¾À5", new save);
	SCENEMANAGER->addScene("¾À6", new bossroom);
	
	PLAYERMANAGER->setPX(WINSIZEX - 80);
	PLAYERMANAGER->setPY(WINSIZEY / 2);
	PLAYERMANAGER->setPCHP(250);
	PLAYERMANAGER->setPCMP(100);
	PLAYERMANAGER->setDJUMP(1);
	_play = new playerJ;
	_play->init();
	PLAYERMANAGER->setPCHP(_play->getPCHP());
	_em = new enemyManager;
	_em->init();
	_om = new objectManager;
	_om->init();
	_play->setEmMemoryAddressLink(_em);
	_play->setOmMemoryAddressLink(_om);
	_em->setPlayerMemoryAddressLink(_play);
	_om->setPlayerMemoryAddressLinkI(_play);

	i = 1;
	DATAMANAGER->setN(i);
	PLAYERMANAGER->setPlayerJMemoryAddressLink(_play);
	ENEMYDATAMANAGER->setEnemyManagerMemoryAddressLink(_em);
	OBJECTDATAMANAGER->setObjectManagerMemoryAddressLink(_om);
	
	SCENEMANAGER->changeScene("Å×½ºÆ®¾À2");

	return S_OK;
}

//¸Þ¸ð¸® ÇØÁ¦´Â ¿©±â´Ù ÇÏ¼¼¿ä Á¦¹ß
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();
	
	
	DATAMANAGER->setN(i);
	DATAMANAGER->setPX(_play->getX());
	DATAMANAGER->setPY(_play->getY());
	DATAMANAGER->setPRC(_play->getRC());
	SCENEMANAGER->update();
	_play->update();
	
		if (_play->getX() <0) 
		{
			i++;
			if (i == 1 && _play->getD())
			{

				PLAYERMANAGER->setPX(1200);
				PLAYERMANAGER->setPY(WINSIZEY/2);
				SCENEMANAGER->changeScene("Å×½ºÆ®¾À2");
				
			}
			else if (i == 1 && !_play->getD())
			{

				PLAYERMANAGER->setPX(50);
				PLAYERMANAGER->setPY(WINSIZEY/2);
				SCENEMANAGER->changeScene("Å×½ºÆ®¾À2");
				
			}
			if (i == 2 && _play->getD())
			{

				PLAYERMANAGER->setPX(2200);
				PLAYERMANAGER->setPY(2700);
				SCENEMANAGER->changeScene("Å×½ºÆ®¾À1");
			}
			if (i == 3 && !_play->getD())
			{

				PLAYERMANAGER->setPX(50);
				PLAYERMANAGER->setPY(WINSIZEY/2);
				SCENEMANAGER->changeScene("¾À4");
				
			}
			if (i == 4 && _play->getD()&&_play->getF()==0)
			{

				PLAYERMANAGER->setPX(3400);
				PLAYERMANAGER->setPY(WINSIZEY/2);
				SCENEMANAGER->changeScene("¾À3");
				
			}
			if (i == 4 && _play->getF() > 0)
			{

				PLAYERMANAGER->setPX(2900);
				PLAYERMANAGER->setPY(650);
				SCENEMANAGER->changeScene("¾À3");
				
			}
			if (i == 4 && !_play->getD() && _play->getF() == 0)
			{

				PLAYERMANAGER->setPX(50);
				PLAYERMANAGER->setPY(WINSIZEY/2);
				SCENEMANAGER->changeScene("¾À3");
				
			}
			if (i == 5 && !_play->getD())
			{

				PLAYERMANAGER->setPX(50);
				PLAYERMANAGER->setPY(WINSIZEY/2);
				SCENEMANAGER->changeScene("¾À5");
				
			}
			else if (i == 5 && _play->getD())
			{

				PLAYERMANAGER->setPX(1200);
				PLAYERMANAGER->setPY(WINSIZEY/2);
				SCENEMANAGER->changeScene("¾À5");
				
			}
			if (i == 6 && _play->getD())
			{

				PLAYERMANAGER->setPX(2200);
				PLAYERMANAGER->setPY(400);
				SCENEMANAGER->changeScene("¾À6");
				
			}
		}
		if (_play->getX() > CAMERAMANAGER->getBackScreenWidth()-50)
		{
			i--;
			if (i == 1 && _play->getD())
			{
				PLAYERMANAGER->setPX(1200);
				PLAYERMANAGER->setPY(WINSIZEY / 2);
				SCENEMANAGER->changeScene("Å×½ºÆ®¾À2");
				
			}
			else if (i == 1 && !_play->getD())
			{
				PLAYERMANAGER->setPX(50);
				PLAYERMANAGER->setPY(WINSIZEY / 2);
				SCENEMANAGER->changeScene("Å×½ºÆ®¾À2");
				
			}
			if (i == 2 && _play->getD())
			{
				PLAYERMANAGER->setPX(2200);
				PLAYERMANAGER->setPY(2700);
				SCENEMANAGER->changeScene("Å×½ºÆ®¾À1");
				
			}
			if (i == 3 && !_play->getD())
			{
				PLAYERMANAGER->setPX(50);
				PLAYERMANAGER->setPY(WINSIZEY / 2);
				SCENEMANAGER->changeScene("¾À4");
				
			}
			if (i == 4 && _play->getD() && _play->getF() == 0)
			{
				PLAYERMANAGER->setPX(3400);
				PLAYERMANAGER->setPY(WINSIZEY / 2);
				SCENEMANAGER->changeScene("¾À3");
				
			}
			 if (i == 4 && _play->getF() > 0)
			{
				 PLAYERMANAGER->setPX(2900);
				 PLAYERMANAGER->setPY(650);
				 SCENEMANAGER->changeScene("¾À3");

				
			}
			if (i == 4 && !_play->getD() && _play->getF() == 0)
			{
				PLAYERMANAGER->setPX(50);
				PLAYERMANAGER->setPY(WINSIZEY / 2);
				SCENEMANAGER->changeScene("¾À3");
				
			}
			if (i == 5 && !_play->getD())
			{
				PLAYERMANAGER->setPX(50);
				PLAYERMANAGER->setPY(WINSIZEY / 2);
				SCENEMANAGER->changeScene("¾À5");

				
			}
			else if (i == 5 && _play->getD())
			{
				PLAYERMANAGER->setPX(1200);
				PLAYERMANAGER->setPY(WINSIZEY / 2);
				SCENEMANAGER->changeScene("¾À5");
				
			}
			if (i == 6 && _play->getD())
			{

				PLAYERMANAGER->setPX(2200);
				PLAYERMANAGER->setPY(400);
				SCENEMANAGER->changeScene("¾À6");
				
			}
		}
		if (_play->getY() <= -20)
		{
			i += 2; 
			PLAYERMANAGER->setPY(650);
			if (i == 4 && _play->getF() > 0)
			{
				PLAYERMANAGER->setPX(2900);
				SCENEMANAGER->changeScene("¾À3");
				
			}
		}
		if (_play->getY() > CAMERAMANAGER->getBackScreenHeight())
		{
			i -= 2;
			if (i == 2 && _play->getF() < 0)
			{
				PLAYERMANAGER->setPX(670);
				PLAYERMANAGER->setPY(30);
				SCENEMANAGER->changeScene("Å×½ºÆ®¾À1");	
			}
		}
		
		PLAYERMANAGER->setPMP(_play->getPMP());
		PLAYERMANAGER->setPCMP(_play->getPCMP());
		PLAYERMANAGER->setPHP(_play->getPHP());
		PLAYERMANAGER->setPCHP(_play->getPCHP());
		PLAYERMANAGER->setPRC(_play->getRC());
		PLAYERMANAGER->setPlayerJMemoryAddressLink(_play);
		ENEMYDATAMANAGER->setEnemyManagerMemoryAddressLink(_em);
		OBJECTDATAMANAGER->setObjectManagerMemoryAddressLink(_om);
		
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// À§¿¡ °ÇµéÁö¸¶¶ó
	//================Á¦¹ß ÀÌ »çÀÌ¿¡ Á» ±×¸³½Ã´Ù==========================

	char str[128];
	//sprintf_s(str, "Áß·Â: %f, Á¡ÇÁ: %f i:%d X:%f Y:%f", _play->getG(), _play->getF(), i,DATAMANAGER->getPX(),DATAMANAGER->getPY() , str, strlen(str));
	SCENEMANAGER->render();
	
	//TIMEMANAGER->render(getMemDC(), _play->getX() - 150, _play->getY() - 150);
	_play->render();
	
	//TextOut(getMemDC(), _play->getX() - 200, _play->getY() - 200,str,strlen(str));
	//==================================================
	//¿©±âµµ °ÇµéÁö¸¶¶ó
	//this->getBackBuffer()->render(getHDC(), 0, 0);
	CAMERAMANAGER->render(getHDC(), 0, 0, getMemDC());

}
