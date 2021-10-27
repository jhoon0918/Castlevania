#include "stdafx.h"
#include "player.h"
#include "StandingState.h"
#include "playGround.h"
#include "enemyManager.h"
#include "objectManager.h"


void playerJ::InputHandle()
{
	JState* newState = _state->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_state);
		_state = newState;
		_state->enter(this);
	}
}

playerJ::playerJ()
{
}

playerJ::~playerJ()
{
}

HRESULT playerJ::init()
{
	

	
	IMAGEMANAGER->addFrameImage("기본", "img/jonathan idle2.bmp", 1920, 390, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공격", "img/jonathan stand whip2.bmp", 7200, 390, 15, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("서브공격", "img/jonathan subweapon2.bmp", 960, 390, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("백스텝", "img/jonathan backstep2.bmp", 2400, 390, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("업", "img/jonathan up2.bmp", 2400, 390, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("런", "img/jonathan walk2.bmp", 7200, 390, 15, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("피격", "img/normal hitted2.bmp", 1920, 390, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("전환", "img/jonathan shift.bmp", 116, 90, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("점프", "img/jonathan jump2.bmp", 4800, 390, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공중공격", "img/jonathan air attack2.bmp", 5280, 390, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공중서브", "img/jonathan subweapon air2.bmp", 1440, 390, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공중피격", "img/jonathan air hitted2.bmp", 1440, 390, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("백어택", "img/jonathan air back2.bmp", 1920, 390, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("앉음", "img/jonathan crouch2.bmp", 1920, 390, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("앉음공격", "img/jonathan crouch attack2.bmp", 4800, 390, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("앉음피격", "img/jonathan ground hit2.bmp", 1920, 390, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("슬라이드", "img/jonathan slide2.bmp", 2880, 390, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("콤비준비", "img/combi steady2.bmp", 1920, 390, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("콤비온", "img/combi on2.bmp", 960, 390, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("샬롯기본", "img/charlotte idle1.bmp", 552, 258, 8, 2, true, RGB(255, 0, 255));
	

	x = PLAYERMANAGER->getPX();
	y = PLAYERMANAGER->getPY();
	rc = RectMake(x, y, 70, 140);
	speed = 7;
	direction = true;
	_maxHP = 250;
	_maxMP = 100;
	_currentHP = PLAYERMANAGER->getPCHP();
	_currentMP = PLAYERMANAGER->getPCMP();

	_x = (rc.left +rc.right) / 2;
	_y = (rc.top + rc.bottom) / 2;
	_probeX = _x;
	_probeY = _y;
	_state = new StandingState();
	_state->enter(this);
	
	_whip = new whip;
	_whip->init(1, 300);
	_dagger = new dagger;
	_dagger->init("dagger",2, 700);
	_lt = new lightning;
	_lt->init("lightning", 0, 2000);

	_hpBar = new progressBar;
	_hpBar->init(CAMERAMANAGER->getX()+142, CAMERAMANAGER->getY()+30, 256,12);
	_hpBar->setGauge(_currentHP, _maxHP);

	_mpBar = new manaBar;
	_mpBar->init(CAMERAMANAGER->getX() + 142, CAMERAMANAGER->getY() + 50, 256, 12);
	_mpBar->setGauge(_currentMP, _maxMP);

	ui = IMAGEMANAGER->addImage("UI", "img/UI.bmp", 444, 124, true, RGB(255, 0, 255));
	ui->setX(CAMERAMANAGER->getX() + 50);
	ui->setY(CAMERAMANAGER->getY() + 50);


	combiCount = 0;
	combiProgress = false;
	_p = RectMakeCenter(_probeX, _probeY, 5, 5);
	dcount = 1;
	
	doubleJ = PLAYERMANAGER->getDJUMP();
	force = gravity = _count = _index = 0;
	isJump=state = false;
	maxJump = 2;
	jump = maxJump;
	areaH = rc.bottom - rc.top;
	areaW = rc.right - rc.left;
	scene = 2;
	count = DATAMANAGER->getN();
	whipA = false;
	hitted = false;
	backhitted = false;
	manacount = 0;
	character = true;
	life = true;
	return S_OK;
}

void playerJ::release()
{
}

void playerJ::update()
{
	count = DATAMANAGER->getN();
	if (life)
	{

		manacount++;
		if (manacount >= 20 && _currentMP < _maxMP) { _currentMP++; manacount = 0; }
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !hitted && !backhitted && !combiProgress && !KEYMANAGER->isStayKeyDown(VK_DOWN)) { x -= speed; direction = true; }
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !hitted && !backhitted && !combiProgress && !KEYMANAGER->isStayKeyDown(VK_DOWN)) { x += speed; direction = false; }
		if ((KEYMANAGER->isOnceKeyDown('Z') || KEYMANAGER->isStayKeyDown('Z')) && !whipA)
		{
			_whip->fire(rc.left, rc.top); whipA = true;
		}
		if ((KEYMANAGER->isOnceKeyDown('A') || (KEYMANAGER->isStayKeyDown('A'))) && dcount > 0 && _currentMP >= 6
			&& !(KEYMANAGER->isOnceKeyDown(VK_DOWN) || KEYMANAGER->isStayKeyDown(VK_DOWN)))
		{
			if (direction) { _dagger->fire(rc.left, rc.top + 40, PI, 20.0f); dcount--; _currentMP -= 6; }
			else { _dagger->fire(rc.left, rc.top + 40, 0, 20.0f); dcount--; _currentMP -= 6; }
		}
		if (combiProgress)
		{
			_lt->fire(CAMERAMANAGER->getX(), CAMERAMANAGER->getY() - 280);
			combiCount++;
		}
		if (combiCount % 35 == 0)combicollision();
		if (combiCount >= 200)
		{
			combiProgress = false;
			combiCount = 0;
			_lt->removeMissile();
		}
		gravity += 0.01f;
		if (force > -5)force -= gravity;
		y -= force;

		_x = (rc.left + rc.right) / 2;
		_y = (rc.top + rc.bottom) / 2;
		_probeX = _x;
		_probeY = _y;
		_p = RectMakeCenter(_probeX, _probeY, 5, 5);
		DATAMANAGER->setCX(x);
		DATAMANAGER->setCY(y);
		_whip->update();
		_dagger->update();
		if (!whipA)_whip->removeMissile();
		if (_currentHP <= 0)life = false;
		pixelCollision();
		

		batMaincollision();
		batSubcollsion();
		batcollision();

		bladeMaincollision();
		bladeSubcollision();
		bladecollsion();

		boneMaincollision();
		boneSubcollision();
		bonecollision();

		cornerMaincollision();
		cornerSubcollsion();
		cornercollision();

		nyxMaincollision();
		nyxSubcollision();
		nyxcollision();

		bossMaincollision();
		bossSubcollision();
		bossbodycollsion();

		djumpcollision();
		combiitemcollision();
		rheartcollision();
	}
	
	DATAMANAGER->setD(direction);
	CAMERAMANAGER->updateScreen(x, y);
	_hpBar->setX(CAMERAMANAGER->getX()+142);
	_hpBar->setY(CAMERAMANAGER->getY()+30);
	_hpBar->setGauge(_currentHP, _maxHP);
	_hpBar->update();
	_mpBar->setX(CAMERAMANAGER->getX() + 142);
	_mpBar->setY(CAMERAMANAGER->getY() + 50);
	_mpBar->setGauge(_currentMP, _maxMP);
	_mpBar->update();
	ui->setX(CAMERAMANAGER->getX()+50);
	ui->setY(CAMERAMANAGER->getY()+50);
	InputHandle();
	_state->update(this);
}

void playerJ::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) { Rectangle(getMemDC(), rc); }
	img->frameRender(getMemDC(), _x-(img->getFrameWidth()/2), _y-(img->getFrameHeight()/2));
	Rectangle(getMemDC(), _p);

	_whip->render();
	_dagger->render();
	_lt->render();
	ui->render(getMemDC(), (CAMERAMANAGER->getX() + 20), (CAMERAMANAGER->getY() + 20));
	_hpBar->render();
	_mpBar->render();
	
}

void playerJ::pixelCollision()
{
	count = DATAMANAGER->getN();
	if(count==1)map="시작맵백";
	if (count == 2)map = "홀백";
	if (count == 3)map = "힐백";
	if (count == 4)map = "버티칼백";
	if (count == 5)map = "세이브백";
	if (count == 6)map = "보스방백";
	
	
	for (int i = _probeY - areaH / 4; i < _probeY + areaH / 2; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(map)->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 100 && g == 100 && b == 100))
		{
			y = i - areaH +1;
			gravity = 0;
			force = 0;
			doubleJ = PLAYERMANAGER->getDJUMP();
			break;
		}
	}
	for (int i = _probeY - areaH/2; i < _probeY ; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(map)->getMemDC(), _x, i);
	
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 50 && g == 50 && b == 50))
		{
			y = i+1;
			break;
		}
	}
	for (int i = _probeX - areaW/2; i < _probeX; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(map)->getMemDC(), i, _y);
	
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
	
		if ((r == 50 && g == 100 && b == 100))
		{
			x = i+5 ;
			break;
		}
	}
	for (int i = _probeX; i < _probeX+areaW/2; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(map)->getMemDC(), i, _y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 100 && g == 100 && b == 50))
		{
			x = i-areaW;
			break;
		}
	}
	_p = RectMakeCenter(_probeX, _probeY, 5, 5);
}

void playerJ::hitDamage(float damage)
{
	_currentHP -= damage;
}

void playerJ::batMaincollision()
{
	RECT temp;
	for (int i = 0; i < _em->getVBat().size(); i++)
	{
		RECT rc = _em->getVBat()[i]->getRect();
		float midW = (rc.right + rc.left) / 2;
		float midH = (rc.top + rc.bottom) / 2;
		for (int j = 0; j < _whip->getVWhip().size(); j++)
		{
			if (IntersectRect(&temp, &_whip->getVWhip()[j].rc,
				&rc))
			{
				_em->getVBat()[i]->hitDamage(_whip->getDMG());
				if (_em->getVBat()[i]->getHP() <= 0)
				{
					if(RND->getInt(100)>40)_om->setItem(2, midW, midH);
					_em->removeBat(i);
				}
				_whip->removeMissile();
				break;
			}

		}
	}
}

void playerJ::batSubcollsion()
{
	for (int i = 0; i < _em->getVBat().size(); i++)
	{
		
		for (int j = 0; j < _dagger->getVDagger().size(); j++)
		{
			RECT temp;
			RECT rc = _em->getVBat()[i]->getRect();
			float midW = (rc.right + rc.left) / 2;
			float midH = (rc.top + rc.bottom) / 2;
			if (IntersectRect(&temp, &_dagger->getVDagger()[j].rc,
				&rc))
			{
				_em->getVBat()[i]->hitDamage(_dagger->getDMG());
				if (_em->getVBat()[i]->getHP() <= 0)
				{
					if (RND->getInt(100) > 40)_om->setItem(2, midW, midH);
					_em->removeBat(i);
				}
				_dagger->removeMissile(j);
				break;
			}

		}
	}
}

void playerJ::batcollision()
{
	for (int i = 0; i < _em->getVBat().size(); i++)
	{
		RECT temp;
		RECT _rc = _em->getVBat()[i]->getRect();
		float _mid = (_rc.right + _rc.left) / 2;

		if (IntersectRect(&temp, &rc,&_rc) && (!hitted && !backhitted)&&!combiProgress)
		{
			if (!hitted)
			{
				if (_mid < rc.left&&direction)
				{
					hitDamage(_em->getVBat()[i]->getbodYDMG());
					hitted = true;
				}
				else if (_mid > rc.right && !direction)
				{
					hitDamage(_em->getVBat()[i]->getbodYDMG());
					hitted = true;
				}
				break;
			}
			if (!backhitted)
			{
				if (_mid < rc.left && !direction)
				{
					hitDamage(_em->getVBat()[i]->getbodYDMG() * 1.5);
					backhitted = true;
				}
				else if (_mid > rc.right && direction)
				{
					hitDamage(_em->getVBat()[i]->getbodYDMG()*1.5);
					backhitted = true;
				}
				break;
			}
		}
	}
}

void playerJ::bladeMaincollision()
{
	for (int i = 0; i < _em->getVBlade().size(); i++)
	{
		for (int j = 0; j < _whip->getVWhip().size(); j++)
		{
			RECT temp;
			RECT rc = _em->getVBlade ()[i]->getRect();
			float midW = (rc.right + rc.left) / 2;
			float midH = (rc.top + rc.bottom) / 2;
			if (IntersectRect(&temp, &_whip->getVWhip()[j].rc,
				&rc))
			{
				_em->getVBlade()[i]->hitDamage(_whip->getDMG());
				if (_em->getVBlade()[i]->getHP() <= 0)
				{
					if (RND->getInt(100) > 40)_om->setItem(2, midW, midH);
					_em->removeBlade(i);
				}
				_whip->removeMissile();
				break;
			}

		}
	}
}

void playerJ::bladeSubcollision()
{
	for (int i = 0; i < _em->getVBlade().size(); i++)
	{
		for (int j = 0; j < _dagger->getVDagger().size(); j++)
		{
			RECT temp;
			RECT rc = _em->getVBlade()[i]->getRect();
			float midW = (rc.right + rc.left) / 2;
			float midH = (rc.top + rc.bottom) / 2;
			if (IntersectRect(&temp, &_dagger->getVDagger()[j].rc,
				&rc))
			{
				_em->getVBlade()[i]->hitDamage(_dagger->getDMG());
				if (_em->getVBlade()[i]->getHP() <= 0)
				{
					if (RND->getInt(100) > 40)_om->setItem(2, midW, midH);
					_em->removeBlade(i);
				}
				_dagger->removeMissile(j);
				break;
			}

		}
	}
}

void playerJ::bladecollsion()
{
	for (int i = 0; i < _em->getVBlade().size(); i++)
	{
		RECT temp;
		RECT _rc = _em->getVBlade()[i]->getRect();
		float _mid = (_rc.right + _rc.left) / 2;
		float _midp = (rc.right + rc.left) / 2;
		if (IntersectRect(&temp, &rc, &_rc) && (!hitted && !backhitted)&&!combiProgress)
		{
			if (!hitted)
			{
				if (_mid < _midp&&direction)
				{
					hitDamage(_em->getVBlade()[i]->getbodYDMG());
					hitted = true;
				}
				else if (_mid > _midp && !direction)
				{
					hitDamage(_em->getVBlade()[i]->getbodYDMG());
					hitted = true;
				}
				break;
			}
			if (!backhitted)
			{
				if (_mid <= _midp && !direction)
				{
					hitDamage(_em->getVBlade()[i]->getbodYDMG() * 1.5);
					backhitted = true;
				}
				else if (_mid >= _midp && direction)
				{
					hitDamage(_em->getVBlade()[i]->getbodYDMG()*1.5);
					backhitted = true;
				}
				break;
			}
		}
	}
}

void playerJ::boneMaincollision()
{
	for (int i = 0; i < _em->getVBone().size(); i++)
	{
		for (int j = 0; j < _whip->getVWhip().size(); j++)
		{
			
			RECT temp;
			RECT rc = _em->getVBone()[i]->getRect();
			float midW = (rc.right + rc.left) / 2;
			float midH = (rc.top + rc.bottom) / 2;
			if (IntersectRect(&temp, &_whip->getVWhip()[j].rc,
				&rc))
			{
				_em->getVBone()[i]->hitDamage(_whip->getDMG());
				if (_em->getVBone()[i]->getHP() <= 0)
				{
					if (RND->getInt(100) > 40)_om->setItem(2, midW, midH);
					_em->removeBone(i);
				}
				_whip->removeMissile();
				break;
			}

		}
	}
}

void playerJ::boneSubcollision()
{
	for (int i = 0; i < _em->getVBone().size(); i++)
	{
		for (int j = 0; j < _dagger->getVDagger().size(); j++)
		{
			
			RECT temp;
			RECT rc = _em->getVBone()[i]->getRect();
			float midW = (rc.right + rc.left) / 2;
			float midH = (rc.top + rc.bottom) / 2;
			if (IntersectRect(&temp, &_dagger->getVDagger()[j].rc,
				&rc))
			{
			
				_em->getVBone()[i]->hitDamage(_dagger->getDMG());
				if (_em->getVBone()[i]->getHP() <= 0)
				{
					if (RND->getInt(100) > 40)_om->setItem(2, midW, midH);
					_em->removeBone(i);
				}
				_dagger->removeMissile(j);
				break;
			}
		}
	}
}

void playerJ::bonecollision()
{
	for (int i = 0; i < _em->getVBone().size(); i++)
	{
		RECT temp;
		RECT _rc = _em->getVBone()[i]->getRect();
		float _mid = (_rc.right + _rc.left) / 2;
		float _midt = (rc.top + rc.bottom) / 2;
		if (IntersectRect(&temp, &rc, &_rc)&&!combiProgress)
		{
			
			if (_mid <= rc.left)
			{
				x += 7;
			}
			else if(_mid>=rc.right)
			{
				x -= 7;
			}
		}
	}
}

void playerJ::cornerMaincollision()
{
	for (int i = 0; i < _em->getVCorner().size(); i++)
	{
		for (int j = 0; j < _whip->getVWhip().size(); j++)
		{
			RECT temp;
			RECT rc = _em->getVCorner()[i]->getRect();
			float midW = (rc.right + rc.left) / 2;
			float midH = (rc.top + rc.bottom) / 2;
			if (IntersectRect(&temp, &_whip->getVWhip()[j].rc,
				&rc))
			{
				_em->getVCorner()[i]->hitDamage(_whip->getDMG());
				if (_em->getVCorner()[i]->getHP() <= 0)
				{
					if (RND->getInt(100) > 40)_om->setItem(2, midW, midH);
					_em->removeCorner(i);
				}
				_whip->removeMissile();
				break;
			}

		}
	}
}

void playerJ::cornerSubcollsion()
{
	for (int i = 0; i < _em->getVCorner().size(); i++)
	{
		for (int j = 0; j < _dagger->getVDagger().size(); j++)
		{
			RECT temp;
			RECT rc = _em->getVCorner()[i]->getRect();
			float midW = (rc.right + rc.left) / 2;
			float midH = (rc.top + rc.bottom) / 2;
			if (IntersectRect(&temp, &_dagger->getVDagger()[j].rc,
				&rc))
			{
				_em->getVCorner()[i]->hitDamage(_dagger->getDMG());
				if (_em->getVCorner()[i]->getHP() <= 0)
				{
					if (RND->getInt(100) > 40)_om->setItem(2, midW, midH);
					_em->removeCorner(i);
				}
				_dagger->removeMissile(j);
				break;
			}

		}
	}
}

void playerJ::cornercollision()
{
	for (int i = 0; i < _em->getVCorner().size(); i++)
	{
		RECT temp;
		RECT _rc = _em->getVCorner()[i]->getRect();
		float _mid = (_rc.right + _rc.left) / 2;
		if (IntersectRect(&temp, &rc, &_rc) && (!hitted && !backhitted)&&!combiProgress)
		{
			if (!hitted)
			{
				if (_mid < rc.left&&direction)
				{
					hitDamage(_em->getVCorner()[i]->getbodYDMG());
					hitted = true;
				}
				else if (_mid > rc.right && !direction)
				{
					hitDamage(_em->getVCorner()[i]->getbodYDMG());
					hitted = true;
				}
			}
			if (!backhitted)
			{
				if (_mid < rc.left && !direction)
				{
					hitDamage(_em->getVCorner()[i]->getbodYDMG() * 1.5);
					backhitted = true;
				}
				else if (_mid > rc.right && direction)
				{
					hitDamage(_em->getVCorner()[i]->getbodYDMG()*1.5);
					backhitted = true;
				}
			}
			break;
		}
	}
}

void playerJ::nyxMaincollision()
{
	for (int i = 0; i < _em->getVNyx().size(); i++)
	{
		for (int j = 0; j < _whip->getVWhip().size(); j++)
		{
			RECT temp;
			RECT rc = _em->getVNyx()[i]->getRect();
			float midW = (rc.right + rc.left) / 2;
			float midH = (rc.top + rc.bottom) / 2;
			if (IntersectRect(&temp, &_whip->getVWhip()[j].rc,
				&rc))
			{
				_em->getVNyx()[i]->hitDamage(_whip->getDMG());
				if (_em->getVNyx()[i]->getHP() <= 0)
				{
					if (RND->getInt(100) > 40)_om->setItem(2, midW, midH);
					_em->removeNyx(i);
				}
				_whip->removeMissile();
				
				break;
			}

		}
	}
}

void playerJ::nyxSubcollision()
{
	for (int i = 0; i < _em->getVNyx().size(); i++)
	{
		for (int j = 0; j < _dagger->getVDagger().size(); j++)
		{
			RECT temp;
			RECT rc = _em->getVNyx()[i]->getRect();
			float midW = (rc.right + rc.left) / 2;
			float midH = (rc.top + rc.bottom) / 2;
			if (IntersectRect(&temp, &_dagger->getVDagger()[j].rc,
				&rc))
			{
				_em->getVNyx()[i]->hitDamage(_dagger->getDMG());
				if (_em->getVNyx()[i]->getHP() <= 0)
				{
					if (RND->getInt(100) > 40)_om->setItem(2, midW, midH);
					_em->removeNyx(i);
				}
				_dagger->removeMissile(j);
				break;
			}

		}
	}
}

void playerJ::nyxcollision()
{
	for (int i = 0; i < _em->getVNyx().size(); i++)
	{
		RECT temp;
		RECT _rc = _em->getVNyx()[i]->getRect();
		float _mid = (_rc.right + _rc.left) / 2;
		if (IntersectRect(&temp, &rc, &_rc) && (!hitted && !backhitted)&&!combiProgress)
		{
			if (!hitted)
			{
				if (_mid < rc.left&&direction)
				{
					hitDamage(_em->getVNyx()[i]->getbodYDMG());
					hitted = true;
				}
				else if (_mid > rc.right && !direction)
				{
					hitDamage(_em->getVNyx()[i]->getbodYDMG());
					hitted = true;
				}
			}
			if (!backhitted)
			{
				if (_mid < rc.left && !direction)
				{
					hitDamage(_em->getVNyx()[i]->getbodYDMG() * 1.5);
					backhitted = true;
				}
				else if (_mid > rc.right && direction)
				{
					hitDamage(_em->getVNyx()[i]->getbodYDMG()*1.5);
					backhitted = true;
				}
			}
			break;
		}
	}
}

void playerJ::bossMaincollision()
{
	for (int i = 0; i < _em->getVAstarte().size(); i++)
	{
		
		for (int j = 0; j < _whip->getVWhip().size(); j++)
		{
			RECT temp;
			RECT rc = _em->getVAstarte()[i]->getRect();
			if (IntersectRect(&temp, &_whip->getVWhip()[j].rc,
				&rc))
			{
				_em->getVAstarte()[i]->hitDamage(_whip->getDMG());
				if (_em->getVAstarte()[i]->getHP() <= 0)
				{
					_em->removeBoss(i);
				}
				_whip->removeMissile();
				break;
			}

		}
	}
}

void playerJ::bossSubcollision()
{
	for (int i = 0; i < _em->getVAstarte().size(); i++)
	{
		for (int j = 0; j < _dagger->getVDagger().size(); j++)
		{
			RECT temp;
			RECT rc = _em->getVAstarte()[i]->getRect();
			if (IntersectRect(&temp, &_dagger->getVDagger()[j].rc,
				&rc))
			{
				_em->getVAstarte()[i]->hitDamage(_dagger->getDMG());
				if (_em->getVAstarte()[i]->getHP() <= 0)
				{
					_em->removeBoss(i);
				}
				_dagger->removeMissile(j);
				break;
			}

		}
	}
}

void playerJ::bossbodycollsion()
{
	for (int i = 0; i < _em->getVAstarte().size(); i++)
	{
		RECT temp;
		RECT _rc = _em->getVAstarte()[i]->getRect();
		float _mid = (_rc.right + _rc.left) / 2;
		if (IntersectRect(&temp, &rc, &_rc) && (!hitted && !backhitted)&&!combiProgress)
		{
			if (!hitted)
			{
				if (_mid < rc.left&&direction)
				{
					hitDamage(_em->getVAstarte()[i]->getbodYDMG());
					hitted = true;
				}
				else if (_mid > rc.right && !direction)
				{
					hitDamage(_em->getVAstarte()[i]->getbodYDMG());
					hitted = true;
				}
			}
			if (!backhitted)
			{
				if (_mid < rc.left && !direction)
				{
					hitDamage(_em->getVAstarte()[i]->getbodYDMG() * 1.5);
					backhitted = true;
				}
				else if (_mid > rc.right && !direction)
				{
					hitDamage(_em->getVAstarte()[i]->getbodYDMG()*1.5);
					backhitted = true;
				}
			}
			break;
		}
	}
}

void playerJ::combicollision()
{
	for (int i = 0; i < _em->getVBat().size(); i++)
	{

		for (int j = 0; j < _lt->getVLightning().size(); j++)
		{
			RECT temp;
			RECT rcB = _em->getVBat()[i]->getRect();
			float midW = (rcB.right + rcB.left) / 2;
			float midH = (rcB.top + rcB.bottom) / 2;
			int rand = RND->getInt(100);
			if (IntersectRect(&temp, &_lt->getVLightning()[j].rc,
				&rcB))
			{
				_em->getVBat()[i]->hitDamage(_lt->getDMG());
				if (_em->getVBat()[i]->getHP() <= 0)
				{
					if (rand > 40)_om->setItem(2, midW, midH);
					_em->removeBat(i);
				}
				break;
			}
		}
	}
	for (int i = 0; i < _em->getVBlade().size(); i++)
	{
		for (int j = 0; j < _lt->getVLightning().size(); j++)
		{
			RECT temp1;
			RECT rcBL = _em->getVBlade()[i]->getRect();
			float midW = (rcBL.right + rcBL.left) / 2;
			float midH = (rcBL.top + rcBL.bottom) / 2;
			int rand = RND->getInt(100);
			if (IntersectRect(&temp1, &_lt->getVLightning()[j].rc,
				&rcBL))
			{
				_em->getVBlade()[i]->hitDamage(_lt->getDMG());
				if (_em->getVBlade()[i]->getHP() <= 0)
				{
					if ( rand> 40)_om->setItem(2, midW, midH);
					_em->removeBlade(i);
				}
				break;
			}
		}
	}
	for (int i = 0; i < _em->getVBone().size(); i++)
	{
		for (int j = 0; j < _lt->getVLightning().size(); j++)
		{
			RECT temp2;
			RECT rcBO = _em->getVBone()[i]->getRect();
			float midW = (rcBO.right + rcBO.left) / 2;
			float midH = (rcBO.top + rcBO.bottom) / 2;
			int rand = RND->getInt(100);
			if (IntersectRect(&temp2, &_lt->getVLightning()[j].rc,
				&rcBO))
			{
				_em->getVBone()[i]->hitDamage(_lt->getDMG());
				if (_em->getVBone()[i]->getHP() <= 0)
				{
					if (rand > 40)_om->setItem(2, midW, midH);
					_em->removeBone(i);
				}
				break;
			}
		}
	}
	for (int i = 0; i < _em->getVCorner().size(); i++)
	{
		for (int j = 0; j < _lt->getVLightning().size(); j++)
		{
			RECT temp3;
			RECT rcC = _em->getVCorner()[i]->getRect();
			float midW = (rcC.right + rcC.left) / 2;
			float midH = (rcC.top + rcC.bottom) / 2;
			int rand = RND->getInt(100);
			if (IntersectRect(&temp3, &_lt->getVLightning()[j].rc,
				&rcC))
			{
				_em->getVCorner()[i]->hitDamage(_lt->getDMG());
				if (_em->getVCorner()[i]->getHP() <= 0)
				{
					if (rand> 40)_om->setItem(2, midW, midH);
					_em->removeCorner(i);
				}
				break;
			}
		}
	}
	for (int i = 0; i < _em->getVNyx().size(); i++)
	{
		for (int j = 0; j < _lt->getVLightning().size(); j++)
		{
			RECT temp4;
			RECT rcN = _em->getVNyx()[i]->getRect();
			float midW = (rcN.right + rcN.left) / 2;
			float midH = (rcN.top + rcN.bottom) / 2;
			int rand = RND->getInt(100);
			if (IntersectRect(&temp4, &_lt->getVLightning()[j].rc,
				&rcN))
			{
				_em->getVNyx()[i]->hitDamage(_lt->getDMG());
				if (_em->getVNyx()[i]->getHP() <= 0)
				{
					if (rand > 40)_om->setItem(2, midW, midH);
					_em->removeNyx(i);
				}
				break;
			}
		}
	}
	for (int i = 0; i < _em->getVAstarte().size(); i++)
	{
		for (int j = 0; j < _lt->getVLightning().size(); j++)
		{
			RECT temp5;
			RECT rcA = _em->getVAstarte()[i]->getRect();

			if (IntersectRect(&temp5, &_lt->getVLightning()[j].rc,
				&rcA))
			{
				_em->getVAstarte()[i]->hitDamage(_lt->getDMG());
				if (_em->getVAstarte()[i]->getHP() <= 0)
				{
					_em->removeBoss(i);
				}
				break;
			}
		}
	}
}

void playerJ::djumpcollision()
{
	for (int i = 0; i < _om->getVDjump().size(); i++)
	{
		RECT temp;
		RECT rcJ = _om->getVDjump()[i]->getRect();
		if (IntersectRect(&temp, &rc,&rcJ))
		{
			PLAYERMANAGER->setDJUMP(2);
			_om->removeIdjump(i);
			break;
		}
	}
}

void playerJ::combiitemcollision()
{
	for (int i = 0; i < _om->getVCombi().size(); i++)
	{
		RECT temp;
		RECT rcCB = _om->getVCombi()[i]->getRect();
		if (IntersectRect(&temp, &rc, &rcCB))
		{
			PLAYERMANAGER->setFUSION(true);
			_om->removeIcombi(i);
			break;
		}
	}
}

void playerJ::rheartcollision()
{
	for (int i = 0; i < _om->getVReH().size(); i++)
	{
		RECT temp;
		RECT rcRH = _om->getVReH()[i]->getRect();
		if (IntersectRect(&temp, &rc, &rcRH))
		{
			if (_currentHP < _maxHP - 10)
			_currentHP += 10;
			if (_currentMP < _maxMP - 5)
			_currentMP += 5;
			_om->removeIregenH(i);
			break;
		}
	}
}
