#include "stdafx.h"
#include "bone.h"

HRESULT bone::init()
{
	return S_OK;
}

HRESULT bone::init(POINT position)
{
	_currentFrameX = _currentFrameY = 0;

	_boneA = IMAGEMANAGER->findImage("boneShot");
	_boneI = IMAGEMANAGER->findImage("boneIdle");

	_bone = _boneI;
	direction = true;
	_state = LEFT_IDLEBO;
	_count =_fireCount= 0;
	_rc = RectMakeCenter(position.x, position.y,
		_bone->getFrameWidth(), _bone->getFrameHeight());
	_censor = RectMakeCenter(position.x, position.y, 800, 300);

	_currentFrameX = 0;
	reverseFrame = _bone->getMaxFrameX();
	maxHP = currentHP=28;
	whatTo = false;
	x = position.x;
	y = position.y;
	return S_OK;
}

void bone::release()
{
	
}

void bone::update()
{
	if (whatTo&&direction) { _state = LEFT_ATTACKBO; ; }
	if (whatTo && !direction) { _state = RIGHT_ATTACKBO; }
	if (!whatTo&&direction) { _state = LEFT_IDLEBO;}
	if (!whatTo && !direction) { _state = RIGHT_IDLEBO; }
	if (direction) { _currentFrameY = 0; }
	if (!direction) { _currentFrameY = 1; }
	_count++;
	if (_count % 50 == 0)
	{
		if (_state == LEFT_IDLEBO)
		{
			_bone->setFrameX(_currentFrameX);
			_bone->setFrameY(_currentFrameY);
			_currentFrameX++;
			_count = 0;
			if (_currentFrameX > _bone->getMaxFrameX()) _currentFrameX = 0;

		}
		if (_state == RIGHT_IDLEBO)
		{

			_bone->setFrameX(reverseFrame);
			_bone->setFrameY(_currentFrameY);
			reverseFrame--;
			_count = 0;
			if (reverseFrame < 0) reverseFrame = _bone->getMaxFrameX();
		}
		if (_state == LEFT_ATTACKBO)
		{

			_boneA->setFrameX(_currentFrameX);
			_boneA->setFrameY(_currentFrameY);
			_currentFrameX++;
			_count = 0;
			if (_currentFrameX > _boneA->getMaxFrameX()) _currentFrameX = 0;
		}
		if (_state == RIGHT_ATTACKBO)
		{

			_boneA->setFrameX(reverseFrame);
			_boneA->setFrameY(_currentFrameY);
			reverseFrame--;
			_count = 0;
			if (reverseFrame < 0) reverseFrame = _boneA->getMaxFrameX();
			
		}
	}
	
	_rc = RectMakeCenter(x, y,
		_bone->getFrameWidth(), _bone->getFrameHeight());
	_censor = RectMakeCenter(x, y, 800, 400);
}

void bone::render()
{
	draw();
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _censor);
		Rectangle(getMemDC(), _rc);
	}
}

void bone::draw()
{
	if (_state == RIGHT_ATTACKBO || _state == LEFT_ATTACKBO)
	{
		_boneA->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	if(_state==RIGHT_IDLEBO||_state==LEFT_IDLEBO)
	{
		_bone->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
}


bool bone::bulletCountFire()
{
	if (whatTo)
	{
		_fireCount++;

		if (_fireCount >= 50)
		{

			_fireCount = 0;

			return true;
		}
		return false;
	}
}

void bone::hitDamage(float damage)
{
	currentHP -= damage;
}


