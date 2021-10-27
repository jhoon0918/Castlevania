#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	
	_fire = new fireball;
	_fire->init("fireball", 1, 500);
	_torna = new tornado;
	_torna->init("tornado", 0, 500);
	_heart = new heart;
	_heart->init("heart", 4, 700);
	_tri = new triangle;
	_tri->init("triangle", 5, 300);
	_vastarte.clear();
	_vbat.clear();
	_vblade.clear();
	_vbone.clear();
	_vnyx.clear();
	_vcorner.clear();
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	DATAMANAGER->getPX();
	DATAMANAGER->getPY();
	DATAMANAGER->getPRC();
	for (_viastarte = _vastarte.begin(); _viastarte != _vastarte.end(); ++_viastarte)
	{
		
		(*_viastarte)->update();
		(*_viastarte)->getAD();
	}
	for (_vibat = _vbat.begin(); _vibat != _vbat.end(); ++_vibat)
	{
		(*_vibat)->update();
	}
	for (_vibone = _vbone.begin(); _vibone != _vbone.end(); ++_vibone)
	{
		(*_vibone)->update();
		(*_vibone)->getBD();
	}
	for (_viblade = _vblade.begin(); _viblade != _vblade.end(); ++_viblade)
	{
		(*_viblade)->update();
	}
	for (_vinyx = _vnyx.begin(); _vinyx != _vnyx.end(); ++_vinyx)
	{
		(*_vinyx)->update();
		
	}
	for (_vicorner = _vcorner.begin(); _vicorner != _vcorner.end(); ++_vicorner)
	{
		(*_vicorner)->update();
		(*_vicorner)->getCD();
		
	}
	
	_fire->update();
	_torna->update();
	_heart->update();
	_tri->update();
	
	
	x2 = (DATAMANAGER->getPRC().right - DATAMANAGER->getPRC().left);
	y2 = (DATAMANAGER->getPRC().bottom - DATAMANAGER->getPRC().top);
	prc = RectMake(DATAMANAGER->getPX(), DATAMANAGER->getPY(),x2, y2);
	
	batCensorCollision();

	bladeCencorCollision();

	boneCensorCollision();
	boneBulletFire();
	boneFireCollsion();

	nyxCensorCollision();
	nyxAttackCensorCollision();
	
	cornerCensorCollision();
	cornerAttackCensorCollision();

	bossCensorCollision();
	bossAttackCensorCollision();
	bossAttackTornado();
	bossHeartAttack();
	bossTriangle();
	tornadoCollision();
	heartCollision();
	TriangleCollision();
}

void enemyManager::render()
{
	
	for (_vibat = _vbat.begin(); _vibat != _vbat.end(); ++_vibat)
	{
		(*_vibat)->render();
	}
	for (_vibone = _vbone.begin(); _vibone != _vbone.end(); ++_vibone)
	{
		(*_vibone)->render();
		_fire->render();
	}
	for (_viblade = _vblade.begin(); _viblade != _vblade.end(); ++_viblade)
	{
		(*_viblade)->render();
	}
	for (_vinyx = _vnyx.begin(); _vinyx != _vnyx.end(); ++_vinyx)
	{
		(*_vinyx)->render();
	}
	for (_vicorner = _vcorner.begin(); _vicorner != _vcorner.end(); ++_vicorner)
	{
		(*_vicorner)->render();
	}
	for (_viastarte = _vastarte.begin(); _viastarte != _vastarte.end(); ++_viastarte)
	{
		(*_viastarte)->render();
		_torna->render();
		_heart->render();
		_tri->render();
	}
}

void enemyManager::setMinion(int ET,int i, int j)
{	
	switch (ET)
	{
	case 0:
		eBat = new bat;
		eBat->init(PointMake(i,j));
		_vbat.push_back(eBat);
		break;
	case 1:
		eblade = new blade;
		eblade->init(PointMake(i, j));
		_vblade.push_back(eblade);
		break;
	case 2:
		ebone = new bone;
		ebone->init(PointMake(i, j));
		_vbone.push_back(ebone);
		break;
	case 3:
		enyx = new nyx;
		enyx->init(PointMake(i, j));
		_vnyx.push_back(enyx);
		break;
	case 4:
		ecorner = new corner;
		ecorner->init(PointMake(i, j));
		_vcorner.push_back(ecorner);
		break;
	case 5:
		eastarte = new astarte;
		eastarte->init(PointMake(i, j));
		_vastarte.push_back(eastarte);
	}
}


void enemyManager::batCensorCollision()
{
	for (_vibat = _vbat.begin(); _vibat != _vbat.end(); ++_vibat)
	{
		RECT temp;
		float mid = ((*_vibat)->getCensor().right + (*_vibat)->getCensor().left) / 2;

		if (IntersectRect(&temp, &(*_vibat)->getCensor(), &prc))
		{
			
			if (mid < prc.left)
			{
				(*_vibat)->setD(false);
				(*_vibat)->setWT(true);
			}
			else if (mid > prc.right)
			{
				(*_vibat)->setD(true);
				(*_vibat)->setWT(true);
			}
			
		}
		else
		{
			(*_vibat)->setWT(false);
		}
	}
}

void enemyManager::bladeCencorCollision()
{
	for (_viblade = _vblade.begin(); _viblade != _vblade.end(); ++_viblade)
	{
		RECT temp;
		float midX = ((*_viblade)->getCensor().right + (*_viblade)->getCensor().left) / 2;
		float midY = ((*_viblade)->getCensor().bottom + (*_viblade)->getCensor().top) / 2;

		if (IntersectRect(&temp, &(*_viblade)->getCensor(), &prc))
		{
			if (midX < prc.left)
			{
				(*_viblade)->setD(false);
				(*_viblade)->setWT(true);
				if (midY < prc.top)
				{
					(*_viblade)->setUD(false);
				}
				if (midY > prc.bottom)
				{
					(*_viblade)->setUD(true);
				}
			}
			else if (midX > prc.right)
			{
				(*_viblade)->setD(true);
				(*_viblade)->setWT(true);
				if (midY < prc.top)
				{
					(*_viblade)->setUD(false);
				}
				if (midY > prc.bottom)
				{
					(*_viblade)->setUD(true);
				}
			}

		}
		else
		{
			(*_viblade)->setWT(false);
		}
	}
}

void enemyManager::boneCensorCollision()
{
	for (_vibone = _vbone.begin(); _vibone != _vbone.end(); ++_vibone)
	{
		RECT temp;
		float mid = ((*_vibone)->getCensor().right + (*_vibone)->getCensor().left) / 2;

		if (IntersectRect(&temp, &(*_vibone)->getCensor(), &prc))
		{
			if (mid < prc.left)
			{
				(*_vibone)->setD(false);
				(*_vibone)->setWT(true);
				DATAMANAGER->setBD(false);
			}
			else if (mid > prc.right)
			{
				(*_vibone)->setD(true);
				(*_vibone)->setWT(true);
				DATAMANAGER->setBD(true);
			}

		}
		else
		{
			(*_vibone)->setWT(false);
		}
	}
}
void enemyManager::boneBulletFire()
{
	for (_vibone = _vbone.begin(); _vibone != _vbone.end(); ++_vibone)
	{
		if ((*_vibone)->getBD())
		{
			if ((*_vibone)->bulletCountFire())
			{
				float fx = (*_vibone)->getX();
				float fy = (*_vibone)->getY();
				RECT rc = (*_vibone)->getRect();
				_fire->fire(fx - (rc.right - rc.left) / 2, fy-30, PI, 6.0f);
			}
		}
		else
		{
			float fx = (*_vibone)->getX();
			float fy = (*_vibone)->getY();
			if ((*_vibone)->bulletCountFire())
			{
				RECT rc = (*_vibone)->getRect();
				_fire->fire(fx-(rc.right-rc.left)/2 , fy-30, 0, 6.0f);
			}
		}
	}
}
void enemyManager::boneFireCollsion()
{
	for (int i = 0; i < _fire->getVBullet().size(); i++)
	{
		RECT temp;
		RECT rc = RectMake(DATAMANAGER->getPX(), DATAMANAGER->getPY(),
			(_player->getRC().right - _player->getRC().left), (_player->getRC().bottom - _player->getRC().top));
		if (IntersectRect(&temp, &_fire->getVBullet()[i].rc, &rc)&&!_player->getCP())
		{
			_player->hitDamage(_fire->getVBullet()[i].dmg);
			_fire->removeBullet(i);
			_player->setHITTED(true);
			break;
		}
	}
}



void enemyManager::nyxCensorCollision()
{
	for (_vinyx = _vnyx.begin(); _vinyx != _vnyx.end(); ++_vinyx)
	{
		RECT temp;
		float midX = ((*_vinyx)->getCensor().right + (*_vinyx)->getCensor().left) / 2;
		float midY = ((*_vinyx)->getCensor().bottom + (*_vinyx)->getCensor().top) / 2;

		if (IntersectRect(&temp, &(*_vinyx)->getCensor(), &prc))
		{
			if (midX < prc.left)
			{
				(*_vinyx)->setD(false);
				(*_vinyx)->setWT(true);
			}
			else if (midX > prc.right)
			{
				(*_vinyx)->setD(true);
				(*_vinyx)->setWT(true);
			}

		}
		else
		{
			(*_vinyx)->setWT(false);
		}
	}
}
void enemyManager::nyxAttackCensorCollision()
{
	for (_vinyx = _vnyx.begin(); _vinyx != _vnyx.end(); ++_vinyx)
	{
		RECT temp;
		float midX = ((*_vinyx)->getACensor().right + (*_vinyx)->getACensor().left) / 2;
		float midY = ((*_vinyx)->getACensor().bottom + (*_vinyx)->getACensor().top) / 2;

		if (IntersectRect(&temp, &(*_vinyx)->getACensor(), &prc)&&!_player->getCP())
		{
			if (midX < prc.left)
			{
				(*_vinyx)->setD(false);
				(*_vinyx)->setWT(true);
				(*_vinyx)->setAT(true);
			}
			else if (midX > prc.right)
			{
				(*_vinyx)->setD(true);
				(*_vinyx)->setWT(true);
				(*_vinyx)->setAT(true);
			}

		}
		else
		{
			(*_vinyx)->setAT(false);
		}
	}
}

void enemyManager::cornerCensorCollision()
{
	for (_vicorner = _vcorner.begin(); _vicorner != _vcorner.end(); ++_vicorner)
	{
		RECT temp;
		float midX = ((*_vicorner)->getCensor().right + (*_vicorner)->getCensor().left) / 2;
		float midY = ((*_vicorner)->getCensor().bottom + (*_vicorner)->getCensor().top) / 2;

		if (IntersectRect(&temp, &(*_vicorner)->getCensor(), &prc))
		{
			if (midX < prc.left)
			{
				(*_vicorner)->setD(false);
				(*_vicorner)->setWT(true);

			}
			else if (midX > prc.right)
			{
				(*_vicorner)->setD(true);
				(*_vicorner)->setWT(true);

			}

		}
		else
		{
			(*_vicorner)->setWT(false);
		}
	}
}
void enemyManager::cornerAttackCensorCollision()
{
	for (_vicorner = _vcorner.begin(); _vicorner != _vcorner.end(); ++_vicorner)
	{
		RECT temp;
		float midX = ((*_vicorner)->getACensor().right + (*_vicorner)->getACensor().left) / 2;
		float midY = ((*_vicorner)->getACensor().bottom + (*_vicorner)->getACensor().top) / 2;

		if (IntersectRect(&temp, &(*_vicorner)->getACensor(), &prc)&&!_player->getCP())
		{
			if (midX < prc.left)
			{
				(*_vicorner)->setD(false);
				(*_vicorner)->setWT(true);
				(*_vicorner)->setAT(true);
				DATAMANAGER->setCD(false);
			}
			else if (midX > prc.right)
			{
				(*_vicorner)->setD(true);
				(*_vicorner)->setWT(true);
				(*_vicorner)->setAT(true);
				DATAMANAGER->setCD(true);
			}

		}
		else
		{
			(*_vicorner)->setAT(false);
		}
	}
}

void enemyManager::bossCensorCollision()
{
	for (_viastarte = _vastarte.begin(); _viastarte != _vastarte.end(); ++_viastarte)
	{
		if ((*_viastarte)->getPR() == false)
		{
			RECT temp;
			float midX = ((*_viastarte)->getCensor().right + (*_viastarte)->getCensor().left) / 2;
			float midY = ((*_viastarte)->getCensor().bottom + (*_viastarte)->getCensor().top) / 2;

			if (IntersectRect(&temp, &(*_viastarte)->getCensor(), &prc))
			{
				if (midX < prc.left)
				{
					(*_viastarte)->setD(false);
					(*_viastarte)->setWT(true);
					DATAMANAGER->setBOD(false);
				}
				else if (midX > prc.right)
				{
					(*_viastarte)->setD(true);
					(*_viastarte)->setWT(true);
					DATAMANAGER->setBOD(true);
				}

			}
			else
			{
				(*_viastarte)->setWT(false);
			}
		}
	}
}
void enemyManager::bossAttackCensorCollision()
{
	for (_viastarte = _vastarte.begin(); _viastarte != _vastarte.end(); ++_viastarte)
	{
		RECT temp;
		float midX = ((*_viastarte)->getACensor().right + (*_viastarte)->getACensor().left) / 2;
		float midY = ((*_viastarte)->getACensor().bottom + (*_viastarte)->getACensor().top) / 2;

		if (IntersectRect(&temp, &(*_viastarte)->getACensor(), &prc))
		{
			if (midX < prc.left)
			{
				(*_viastarte)->setD(false);
				(*_viastarte)->setWT(false);
				(*_viastarte)->setAT(true);
				(*_viastarte)->setPR(true);
				DATAMANAGER->setBOD(false);
			}
			else if (midX > prc.right)
			{
				(*_viastarte)->setD(true);
				(*_viastarte)->setWT(false);
				(*_viastarte)->setAT(true);
				(*_viastarte)->setPR(true);
				DATAMANAGER->setBOD(true);
			}

		}
		else
		{
			(*_viastarte)->setAT(false);
			(*_viastarte)->setPR(false);
		}
	}
}
void enemyManager::bossAttackTornado()
{
	for (_viastarte = _vastarte.begin(); _viastarte != _vastarte.end(); ++_viastarte)
	{
		if ((*_viastarte)->getAD())
		{
			if ((*_viastarte)->tornaCountFire())
			{
				float fx = (*_viastarte)->getX();
				float fy = (*_viastarte)->getY();
				RECT rc = (*_viastarte)->getRect();
				_torna->fire(fx - (rc.right - rc.left) / 2, fy - 30, PI, 6.0f);
			}
		}
		else
		{
			float fx = (*_viastarte)->getX();
			float fy = (*_viastarte)->getY();
			if ((*_viastarte)->tornaCountFire())
			{
				RECT rc = (*_viastarte)->getRect();
				_torna->fire(fx - (rc.right - rc.left) / 2, fy - 30, 0, 6.0f);
			}
		}
	}
}
void enemyManager::bossHeartAttack()
{
	for (_viastarte = _vastarte.begin(); _viastarte != _vastarte.end(); ++_viastarte)
	{
		if ((*_viastarte)->heartCountFire())
		{
			
				RECT rc = (*_viastarte)->getRect();
				
				if (DATAMANAGER->getBOD())
				{
					_heart->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2, PI, 7.0f);
					_heart->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2, PI*8 / 9, 7.0f);
					_heart->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2, PI*17 / 18, 7.0f);
					_heart->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2, -PI*8 / 9, 7.0f);
					_heart->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2, -PI*17 / 18, 7.0f);
				}
				else
				{					
					_heart->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2, 0, 7.0f);
					_heart->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2, PI / 9, 7.0f);
					_heart->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2, PI / 18, 7.0f);
					_heart->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2, -PI / 9, 7.0f);
					_heart->fire((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2, -PI / 18, 7.0f);
				}
			
		}
	}
}
void enemyManager::bossTriangle()
{
	for (_viastarte = _vastarte.begin(); _viastarte != _vastarte.end(); ++_viastarte)
	{
		if ((*_viastarte)->triCountFire())
		{

			RECT rc = (*_viastarte)->getRect();
			float _px = DATAMANAGER->getPX();
			float _py = DATAMANAGER->getPY()*1.5;
			if (DATAMANAGER->getBOD())
			{
				_tri->fire((rc.left + rc.right) / 2, rc.top, -PI*3/4, 3.0f);
				_tri->fire((rc.left + rc.right) / 2, rc.top, -PI *2/3, 2.0f);
				_tri->fire((rc.left + rc.right) / 2, rc.top, -PI *5 / 9, 1.0f);
				_tri->fire((rc.left + rc.right) / 2, rc.top, -PI * 3 / 4, 1.0f);
				_tri->fire((rc.left + rc.right) / 2, rc.top, -PI * 2 / 3, 3.0f);
				_tri->fire((rc.left + rc.right) / 2, rc.top, -PI * 5 / 9, 2.0f);
			}
			else
			{
				_tri->fire((rc.left + rc.right) / 2, rc.top, -PI/4, 3.0f);
				_tri->fire((rc.left + rc.right) / 2, rc.top, -PI/3, 2.0f);
				_tri->fire((rc.left + rc.right) / 2, rc.top, -PI* 4/ 9, 1.0f);
				_tri->fire((rc.left + rc.right) / 2, rc.top, -PI / 4, 1.0f);
				_tri->fire((rc.left + rc.right) / 2, rc.top, -PI / 3, 3.0f);
				_tri->fire((rc.left + rc.right) / 2, rc.top, -PI * 4 / 9, 2.0f);
			}

		}
	}
}
void enemyManager::tornadoCollision()
{
	for (int i = 0; i <	_torna->getVTorna().size(); i++)
	{
		RECT temp;
		RECT rc = RectMake(DATAMANAGER->getPX(), DATAMANAGER->getPY(),
			(_player->getRC().right-_player->getRC().left), (_player->getRC().bottom-_player->getRC().top));
		if (IntersectRect(&temp, &_torna->getVTorna()[i].rc, &rc)&&!_player->getCP())
		{
			_player->hitDamage(_torna->getVTorna()[i].dmg);
			_torna->removeBullet(i);
			_player->setHITTED(true);
			break;
		}
	}
}
void enemyManager::heartCollision()
{
	for (int i = 0; i < _heart->getVHeart().size(); i++)
	{
		RECT temp;
		RECT rc = RectMake(DATAMANAGER->getPX(), DATAMANAGER->getPY(),
			(_player->getRC().right - _player->getRC().left), (_player->getRC().bottom - _player->getRC().top));
		if (IntersectRect(&temp, &_heart->getVHeart()[i].rc, &rc)&&!_player->getCP()&&_player->getCT())
		{
			_player->hitDamage(_heart->getVHeart()[i].dmg);
			_heart->removeBullet(i);
			break;
		}
	}
}
void enemyManager::TriangleCollision()
{
	for (int i = 0; i < _tri->getVTri().size(); i++)
	{
		RECT temp;
		RECT rc = RectMake(DATAMANAGER->getPX(), DATAMANAGER->getPY(),
			(_player->getRC().right - _player->getRC().left), (_player->getRC().bottom - _player->getRC().top));
		if (IntersectRect(&temp, &_tri->getVTri()[i].rc, &rc)&&!_player->getCP())
		{
			_player->hitDamage(_tri->getVTri()[i].dmg);
			_tri->removeBullet(i);
			_player->setHITTED(true);
			break;
		}
	}
}

void enemyManager::removeBat(int arrNum)
{
	_vbat.erase(_vbat.begin() + arrNum);
}

void enemyManager::removeBlade(int arrNum)
{
	_vblade.erase(_vblade.begin() + arrNum);
}

void enemyManager::removeBone(int arrNum)
{
	_vbone.erase(_vbone.begin() + arrNum);
}

void enemyManager::removeNyx(int arrNum)
{
	_vnyx.erase(_vnyx.begin() + arrNum);
}

void enemyManager::removeCorner(int arrNum)
{
	_vcorner.erase(_vcorner.begin() + arrNum);
}

void enemyManager::removeBoss(int arrNum)
{
	_vastarte.erase(_vastarte.begin() + arrNum);
}
