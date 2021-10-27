#include "stdafx.h"
#include "astarte.h"

HRESULT astarte::init()
{
	return S_OK;
}

HRESULT astarte::init(POINT position)
{
	_currentFrameX = _currentFrameY = 0;
	_astML = IMAGEMANAGER->findImage("bossMelee");
	_astM = IMAGEMANAGER->findImage("bossMove");
	_astI = IMAGEMANAGER->findImage("bossIdle");
	_astS = IMAGEMANAGER->findImage("bossStaff");
	_astH = IMAGEMANAGER->findImage("bossHit");
	_astT =IMAGEMANAGER->findImage("bossTorna");
	_astJ =IMAGEMANAGER->findImage("bossJump");
	_astK =IMAGEMANAGER->findImage("bossKiss");

	_ast = _astI;
	direction = false;
	_state = RIGHT_IDLEAS;

	_rc = RectMakeCenter(position.x, position.y,
		_ast->getFrameWidth(), _ast->getFrameHeight());
	_censor = RectMakeCenter(position.x, position.y, 1500, 800);

	maxHP = currentHP=300;
	speed = 3;
	heartDMG = 5.0f;
	bodyDMG = 6.0f;
	tornaDMG = 8.0f;
	triDMG = 9.0f;
	whatTo = false;
	progress = false;
	staff = false;
	pattern = false;
	pattern1 = false;
	pattern2 = false;
	pattern3 = false;
	x = position.x;
	y = position.y;
	force = gravity  = 0;
	count = pcount=0;
	rp = RND->getInt(4);

	_probeX = x;
	_probeY = y;

	areaH = _rc.bottom - _rc.top;
	areaW = _rc.right - _rc.left;

	return S_OK;
}

void astarte::release()
{
}

void astarte::update()
{
	if (rp == 0) { pattern = true; cout << "0"; cout << "0중"; }
	if (rp == 1) { pattern1 = true; cout << "1";	cout << "1중"; }
	if (rp == 2) { pattern2 = true; cout << "2"; cout << "2중"; }
	if (rp == 3) { pattern3 = true; cout << "3";	 cout << "3중"; }
	if (!whatTo&&direction && !attack) { _state = LEFT_IDLEAS; }
	if (!whatTo && !direction && !attack) { _state = RIGHT_IDLEAS; }
	if (whatTo&&direction && !attack) { _state = LEFT_MOVEAS; x -= speed; }
	if (whatTo && !direction && !attack) { _state = RIGHT_MOVEAS; x += speed; }
	if (!whatTo&&direction&&attack&&pattern&&progress) { _state = LEFT_MELEEAS;  x -= speed * 1.2; }
	if (!whatTo && !direction&&attack&&pattern&&progress) { _state = RIGHT_MELEEAS; x += speed * 1.2; }
	if (!whatTo&&direction&&attack&&pattern1&&progress) { _state = LEFT_HEART; }
	if (!whatTo && !direction&&attack&&pattern1&&progress) { _state = RIGHT_HEART;  }
	if (!whatTo&&direction&&attack&&pattern2&&progress) { _state = LEFT_TORNA; }
	if (!whatTo && !direction&&attack&&pattern2&&progress) { _state = RIGHT_TORNA; 	}
	if (!whatTo&&direction&&attack&&pattern3 && !staff&&progress) { _state = LEFT_STAFFAS; staff = true;  }
	if (!whatTo && !direction&&attack&&pattern3 && !staff&&progress) { _state = RIGHT_STAFFAS; staff = true; 	}
	if (!whatTo&&direction&&attack&&pattern3&&staff&&progress) { _state = LEFT_FLEE; x += speed ; force = 5; staff = false;  }
	if (!whatTo && !direction&&attack&&pattern3&&staff&&progress) { _state = RIGHT_FLEE; x -= speed ; force = 5; staff = false;  }
	if (maxHP == 0 && direction) { _state = LEFT_HITAS; }
	if (maxHP == 0 && !direction) { _state = RIGHT_HITAS; }
	if (direction) { _currentFrameY = 0; }
	if (!direction) { _currentFrameY = 1; }
	
	_count++;
	if (_count % 10 == 0)
	{
		pcount++; cout << "우";
		if (_state == LEFT_IDLEAS)
		{
			_ast->setFrameX(_currentFrameX);
			_ast->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX <= 0) _currentFrameX = _ast->getMaxFrameX();
			_currentFrameX--;
		}
		if (_state == RIGHT_IDLEAS)
		{

			_ast->setFrameX(_currentFrameX);
			_ast->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX >= _ast->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameX++;
		}
		if (_state == LEFT_MOVEAS)
		{

			_astM->setFrameX(_currentFrameX);
			_astM->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX <= 0) _currentFrameX = _astM->getMaxFrameX();
			_currentFrameX--;
		}
		if (_state == RIGHT_MOVEAS)
		{

			_astM->setFrameX(_currentFrameX);
			_astM->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX >= _astM->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameX++;
		}
		if (_state == LEFT_HITAS)
		{

			_astH->setFrameX(_currentFrameX);
			_astH->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX <= 0) _currentFrameX = _astH->getMaxFrameX();
			_currentFrameX--;
		}
		if (_state == RIGHT_HITAS)
		{

			_astH->setFrameX(_currentFrameX);
			_astH->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX >= _astH->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameX++;
		}
		if (_state == LEFT_TORNA)
		{

			_astT->setFrameX(_currentFrameX);
			_astT->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX >= _astT->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			_currentFrameX++;
		}
		if (_state == RIGHT_TORNA)
		{

			_astT->setFrameX(_currentFrameX);
			_astT->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX <= 0)
			{
				_currentFrameX = _astT->getMaxFrameX();
			}
			_currentFrameX--;
			
		}
		if (_state == LEFT_MELEEAS)
		{

			_astML->setFrameX(_currentFrameX);
			_astML->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX >= _astML->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			_currentFrameX++;
		}
		if (_state == RIGHT_MELEEAS)
		{

			_astML->setFrameX(_currentFrameX);
			_astML->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX <= 0)
			{
				_currentFrameX = _astML->getMaxFrameX();
			}
			_currentFrameX--;
		}
		if (_state == LEFT_HEART)
		{

			_astK->setFrameX(_currentFrameX);
			_astK->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX >= _astK->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			_currentFrameX++;
		}
		if (_state == RIGHT_HEART)
		{

			_astK->setFrameX(_currentFrameX);
			_astK->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX <= 0)
			{
				_currentFrameX = _astK->getMaxFrameX();
			}
			_currentFrameX--;
		}
		if (_state == LEFT_STAFFAS)
		{

			_astS->setFrameX(_currentFrameX);
			_astS->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX <= 0)
			{
				_currentFrameX = _astS->getMaxFrameX();
			}
			_currentFrameX--;
		}
		if (_state == RIGHT_STAFFAS)
		{

			_astS->setFrameX(_currentFrameX);
			_astS->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX >= _astS->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			_currentFrameX++;
		}
		if (_state == LEFT_FLEE)
		{

			_astJ->setFrameX(_currentFrameX);
			_astJ->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX <= 0)
			{
				_currentFrameX = _astJ->getMaxFrameX();
			}
			_currentFrameX--;
		}
		if (_state == RIGHT_FLEE)
		{

			_astJ->setFrameX(_currentFrameX);
			_astJ->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX >= _astJ->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
			_currentFrameX++;
		}
	}
	
	if (pcount == 10) 
	{ pcount = 0; 
	progress = false; 
	rp = RND->getInt(4); 
	pattern = false; 
	pattern1 = false;
	pattern2 = false; 
	pattern3 = false;
	}
	_probeX = x;
	_probeY = y;
	gravity += 0.1f;
	if (force > -5)force -= gravity;
	y -= force;
	pixelCollision();
	if(!pattern)_rc = RectMakeCenter(x, y,_ast->getFrameWidth(), _ast->getFrameHeight());
	if (pattern2)_rc = RectMakeCenter(x, y-10, _ast->getFrameWidth()*2.5, _ast->getFrameHeight());
	if(pattern)_rc= RectMakeCenter(x, y, _ast->getFrameWidth()*2.5, _ast->getFrameHeight());
	_censor = RectMakeCenter(x, y, 1500, 800);
	_aCensor = RectMakeCenter(x, y, 1200, _ast->getFrameHeight() + 300);
}

void astarte::render()
{
	draw();
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _censor);
		Rectangle(getMemDC(), _aCensor);
		Rectangle(getMemDC(), _rc);
	}
}

void astarte::move()
{

}

void astarte::draw()
{
	if (_state == RIGHT_STAFFAS || _state == LEFT_STAFFAS)
	{
		_astS->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	else if (_state == RIGHT_MELEEAS || _state == LEFT_MELEEAS)
	{
		_astML->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	else if (_state == RIGHT_HITAS || _state == LEFT_HITAS)
	{
		_astH->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	else if (_state == RIGHT_FLEE || _state == LEFT_FLEE)
	{
		_astJ->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	else if (_state == RIGHT_TORNA || _state == LEFT_TORNA)
	{
		_astT->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	else if (_state == RIGHT_IDLEAS || _state == LEFT_IDLEAS)
	{
		_ast->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	else if (_state == RIGHT_MOVEAS || _state == LEFT_MOVEAS)
	{
		_astM->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	else if (_state == RIGHT_HEART || _state == LEFT_HEART)
	{
		_astK->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
}

void astarte::pixelCollision()
{
	count = DATAMANAGER->getN();
	if (count == 1)map = "시작맵백";
	if (count == 2)map = "홀백";
	if (count == 3)map = "힐백";
	if (count == 4)map = "버티칼백";
	if (count == 5)map = "세이브백";
	if (count == 6)map = "보스방백";

	for (int i = _probeX - areaW / 2; i < _probeX; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(map)->getMemDC(), i, y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 50 && g == 100 && b == 100))
		{
			x = i + areaW / 2;
			direction = false;
			break;
		}
	}
	for (int i = _probeX - areaW / 2; i < _probeX; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(map)->getMemDC(), i, y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 100 && g == 100 && b == 50))
		{
			x = i - areaW / 2;
			direction = true;
			break;
		}
	}
	for (int i = _probeY - areaH/2; i < _probeY + areaH/2; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(map)->getMemDC(), x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 100 && g == 100 && b == 100))
		{
			y = i - areaH / 2;
			gravity = 0;
			force = 0;
			break;
		}

	}
	
}



bool astarte::tornaCountFire()
{
	if (pattern2)
	{
		_fireCount++;

		if (_fireCount >= 80)
		{

			_fireCount = 0;

			return true;
		}
		return false;
	}
}

bool astarte::heartCountFire()
{
	if (pattern1)
	{
		_fireCount1++;

		if (_fireCount1 >=60)
		{
			_fireCount1 = 0;
			return true;
		}

		return false;
	}
}

bool astarte::triCountFire()
{
	if (pattern3)
	{
		_fireCount2++;

		if (_fireCount2 >= 50)
		{
			_fireCount2 = 0;
			return true;
		}

		return false;
	}
}

void astarte::hitDamage(float damage)
{
	currentHP -= damage;
}
