#include "stdafx.h"
#include "corner.h"

HRESULT corner::init()
{
	return S_OK;
}

HRESULT corner::init(POINT position)
{
	_currentFrameX = _currentFrameY = 0;

	_cornerI = IMAGEMANAGER->findImage("cornerMove");
	_cornerM = IMAGEMANAGER->findImage("cornerMove");
	_cornerA = IMAGEMANAGER->findImage("cornerAttack");
	_corner = _cornerM;
	direction = false;
	block = false;
	_state = RIGHT_IDLEC;
	x = position.x;
	y = position.y;

	
	maxHP =currentHP= 31;
	_rc = RectMakeCenter(position.x, position.y,
		_corner->getFrameWidth(), _corner->getFrameHeight());
	_censor = RectMakeCenter(position.x, position.y, 800, 800);
	_aCensor = RectMakeCenter(x, y, _corner->getFrameWidth() , _corner->getFrameHeight() -50);
	bodyDMG = 6.0f;
	speed = 2;
	whatTo = false;
	_probeX = x;
	_probeY = y;
	areaH = _rc.bottom - _rc.top;
	areaW = _rc.right - _rc.left;


	return S_OK;
}

void corner::release()
{
}

void corner::update()
{
	if (!whatTo&&direction && !attack) { _state = LEFT_IDLEC; }
	if (!whatTo && !direction&&!attack) { _state = RIGHT_IDLEC; }
	if (whatTo&&direction&&attack) { _state = LEFT_ATTACKC; }
	if (whatTo && !direction&&attack) { _state = RIGHT_ATTACKC; }
	if (whatTo&&direction && !attack&&!block) { _state = LEFT_MOVEC; x -= speed; }
	if (whatTo && !direction && !attack&&!block) { _state = RIGHT_MOVEC; x += speed; }

	
	if (direction) { _currentFrameY = 0; }
	if (!direction) { _currentFrameY = 1; }
	_count++;
	if (_count % 15 == 0)
	{
		if (_state == LEFT_IDLEC)
		{
			_corner->setFrameX(0);
			_corner->setFrameY(_currentFrameY);
			_count = 0;
		}
		if (_state == RIGHT_IDLEC)
		{
			_corner->setFrameX(_corner->getMaxFrameX());
			_corner->setFrameY(_currentFrameY);
			_count = 0;
		}
		if (_state == LEFT_MOVEC)
		{
			pierceCountFire = false;
			_corner->setFrameX(_currentFrameX);
			_corner->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX <= 0) _currentFrameX = _corner->getMaxFrameX();
			_currentFrameX--;
		}
		if (_state == RIGHT_MOVEC)
		{
			pierceCountFire = false;
			_corner->setFrameX(_currentFrameX);
			_corner->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX >=_corner->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameX++;
		}
		if (_state == RIGHT_ATTACKC)
		{
			pierceCountFire = false;
			_cornerA->setFrameX(_currentFrameX);
			_cornerA->setFrameY(_currentFrameY);
			
			_count = 0;

			if (_currentFrameX <= 0)
			{
				_currentFrameX = _cornerA->getMaxFrameX();
			}
			_currentFrameX--;
		}
		if (_state == LEFT_ATTACKC)
		{
			pierceCountFire = false;
			_cornerA->setFrameX(_currentFrameX);
			_cornerA->setFrameY(_currentFrameY);
			_count = 0;
			{
				if (_currentFrameX > _cornerA->getMaxFrameX()) _currentFrameX = 0;
			}
			_currentFrameX++;
		}
	}
	DATAMANAGER->setCOX(x);
	DATAMANAGER->setCOY(y);

	_probeX = x;
	_probeY = y;
	pixelCollision();
	if (_state == RIGHT_ATTACKC || _state == LEFT_ATTACKC)
	{
		_rc = RectMakeCenter(x, y, _corner->getFrameWidth()+100, _corner->getFrameHeight()+50);
	}
	else
	{
		_rc = RectMakeCenter(x, y, _corner->getFrameWidth(), _corner->getFrameHeight());
	}
	_censor = RectMakeCenter(x, y, 800, 800);
	_aCensor = RectMakeCenter(x, y, _corner->getFrameWidth()+50, _corner->getFrameHeight()+50);
}

void corner::render()
{
	draw();
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _censor);
		Rectangle(getMemDC(), _aCensor);
		Rectangle(getMemDC(), _rc);
	}
}

void corner::move()
{
}

void corner::draw()
{
	
	if (_state == RIGHT_ATTACKC || _state == LEFT_ATTACKC)
	{
		_cornerA->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	if(_state == RIGHT_MOVEC||_state==LEFT_MOVEC||_state==RIGHT_IDLEC||_state==LEFT_IDLEC)
	{
		_cornerM->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
}

void corner::pixelCollision()
{
	count = DATAMANAGER->getN();
	if (count == 1)map = "시작맵백";
	if (count == 2)map = "홀백";
	if (count == 3)map = "힐백";
	if (count == 4)map = "버티칼백";
	if (count == 5)map = "세이브백";
	if (count == 6)map = "보스방백";

	for (int i = _probeX - areaW/2; i < _probeX; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(map)->getMemDC(), i, y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 75 && g == 100 && b == 100))
		{
			x = i + areaW/2;
			speed = 0;
			block = true;
			break;
		}
	}
	for (int i = _probeX; i < _probeX + areaW / 2; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(map)->getMemDC(), i, y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 100 && g == 100 && b == 75))
		{
			x = i - areaW/2;
			speed = 0;
			block = true;
			break;
		}
	}
	for (int i = _probeY - areaH; i < _probeY + areaH; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(map)->getMemDC(), x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 100 && g == 100 && b == 100))
		{
			y = i - areaH/2;
			speed = 2;
			block = false;
			break;
		}

	}
	
	
}



void corner::hitDamage(float damage)
{
	currentHP -= damage;
}
