#include "stdafx.h"
#include "bat.h"

HRESULT bat::init()
{
	return S_OK;
}

HRESULT bat::init(POINT position)
{
	_currentFrameX = _currentFrameY = 0;

	_batIdle = IMAGEMANAGER->findImage("batIdle");
	_batMove = IMAGEMANAGER->findImage("bat");
	_bat = _batIdle;
	
	direction = false;
	_state = RIGHT_HANG;

	_rc = RectMakeCenter(position.x, position.y,
		_bat->getFrameWidth(), _bat->getFrameHeight());
	_censor = RectMakeCenter(position.x, position.y, WINSIZEX, 500);
	bodyDMG = 2.0f;
	maxHP =currentHP= 15;
	speed = 3;
	whatTo = false;
	x = position.x;
	y = position.y;


	
	return S_OK;
}

void bat::release()
{
}

void bat::update()
{
	if (whatTo&&direction) { _state = LEFT_MOVE; x -= speed; }
	if (whatTo && !direction) { _state = RIGHT_MOVE; x += speed; }
	if (!whatTo&&direction) { _state = LEFT_HANG; }
	if (!whatTo && !direction) { _state = RIGHT_HANG; }
	if (direction) { _currentFrameY = 1; }
	if (!direction) { _currentFrameY = 0; }
	_count++;
	if (_count % 5 == 0)
	{
		if (_state == LEFT_HANG)
		{
			_rc = RectMake(x, y,
				_bat->getFrameWidth(), _bat->getFrameHeight());
			_bat->setFrameY(_currentFrameY);
			_bat->setFrameX(_currentFrameX);
			
			_count = 0;

			if (_currentFrameX <=0) _currentFrameX = _batIdle->getMaxFrameX();
			_currentFrameX--;
		}
		if (_state == RIGHT_HANG)
		{
			_rc = RectMake(x, y,
				_bat->getFrameWidth(), _bat->getFrameHeight());
			_bat->setFrameY(_currentFrameY);
			_bat->setFrameX(_currentFrameX);
			
			_count = 0;

			if (_currentFrameX >= _batIdle->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameX++;
		}
		if (_state == LEFT_MOVE)
		{
			_rc = RectMake(x, y,
				_batMove->getFrameWidth(), _batMove->getFrameHeight());
			_batMove->setFrameX(_currentFrameX);
			_batMove->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX < 0) _currentFrameX = _batMove->getMaxFrameX();
			_currentFrameX--;
		}
		if (_state == RIGHT_MOVE)
		{
			_rc = RectMake(x, y,
				_batMove->getFrameWidth(), _batMove->getFrameHeight());
			_batMove->setFrameX(_currentFrameX);
			_batMove->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX > _batMove->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameX++;
		}
	}
	
	_censor = RectMakeCenter(x, y, WINSIZEX, 300);

}

void bat::render()
{
	draw();
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _censor);
		Rectangle(getMemDC(), _rc);
	}
}

void bat::draw()
{
	
	if (_state == RIGHT_MOVE || _state == LEFT_MOVE) 
	{ 
		_batMove->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY); 
	}
	if(_state==RIGHT_HANG||_state==LEFT_HANG)
	{
	_bat->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
}


void bat::hitDamage(float damage)
{
	currentHP -= damage;
}
