#include "stdafx.h"
#include "blade.h"

HRESULT blade::init()
{
	return S_OK;
}

HRESULT blade::init(POINT position)
{
	_currentFrameX = _currentFrameY = 0;

	_bladeM = IMAGEMANAGER->findImage("blade");
	_bladeI = IMAGEMANAGER->findImage("bladeidle");

	_blade = _bladeI;
	direction = false;
	upDown = false;
	_state = RIGHT_IDLEB;
	maxHP = currentHP=21;
	bodyDMG = 3.0f;
	_rc = RectMakeCenter(position.x, position.y,
		_blade->getFrameWidth(), _blade ->getFrameHeight());
	_censor = RectMakeCenter(position.x, position.y, WINSIZEX,800);

	speed = 4;
	whatTo = false;
	x = position.x;
	y = position.y;
	

	return S_OK;
}

void blade::release()
{
}

void blade::update()
{
	if (whatTo&&direction&&upDown) { _state = LEFT_MOVEB; x -= speed; y -= speed; }
	if (whatTo && !direction&&upDown) { _state = RIGHT_MOVEB; x += speed; y -= speed; }
	if (whatTo&&direction && !upDown) { _state = LEFT_MOVEB; x -= speed; y += speed; }
	if (whatTo && !direction && !upDown) { _state = RIGHT_MOVEB; x += speed; y += speed; }
	if (!whatTo&&direction) { _state = LEFT_IDLEB; }
	if (!whatTo && !direction) { _state = RIGHT_IDLEB; }
	if (direction) { _currentFrameY = 1; }
	if (!direction) { _currentFrameY = 0; }
	_count++;
	if (_count % 5 == 0)
	{
		if (_state == LEFT_IDLEB)
		{
			_currentFrameX = 0;
			_blade->setFrameX(_currentFrameX);
			_blade->setFrameY(_currentFrameY);
			_count = 0;
			
		}
		if (_state == RIGHT_IDLEB)
		{
			_currentFrameX = 0;
			_blade->setFrameX(_currentFrameX);
			_blade->setFrameY(_currentFrameY);

		}
		if (_state == LEFT_MOVEB)
		{

			_bladeM->setFrameX(_currentFrameX);
			_bladeM->setFrameY(_currentFrameY);
			_currentFrameX++;
			_count = 0;
			if (_currentFrameX > _bladeM->getMaxFrameX()) _currentFrameX = 0;
		}
		if (_state == RIGHT_MOVEB)
		{
			_bladeM->setFrameX(_currentFrameX);
			_bladeM->setFrameY(_currentFrameY);
			_currentFrameX--;
			_count = 0;
			if (_currentFrameX < 0) _currentFrameX = _bladeM->getMaxFrameX();
			
		}
	}
	_rc = RectMakeCenter(x, y,
		_blade->getFrameWidth(), _blade->getFrameHeight());
	_censor = RectMakeCenter(x, y, 800, 800);
}

void blade::render()
{
	
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _censor);
		Rectangle(getMemDC(), _rc);
	}
	draw();
}


void blade::draw()
{
	if (_state == RIGHT_MOVEB || _state == LEFT_MOVEB)
	{
		_bladeM->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	else
	{
		_blade->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
}

void blade::hitDamage(float damage)
{
	currentHP -= damage;
}
