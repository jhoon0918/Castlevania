#include "stdafx.h"
#include "nxy.h"

HRESULT nyx::init()
{
	return S_OK;
}

HRESULT nyx::init(POINT position)
{
	_currentFrameX = _currentFrameY = 0;

	_nyxA = IMAGEMANAGER->findImage("nyx attack");
	_nyxM = IMAGEMANAGER->findImage("nyx rush");
	_nyxI = IMAGEMANAGER->findImage("nyx stand");
	_nyxD =IMAGEMANAGER->findImage("nyx die");
	_nyxH =IMAGEMANAGER->findImage("nyx hitted");
	_nyx = _nyxI;
	direction = false;
	_state = RIGHT_IDLEN;

	_rc = RectMakeCenter(position.x, position.y,
		_nyx->getFrameWidth(), _nyx->getFrameHeight());
	_censor = RectMakeCenter(position.x, position.y, WINSIZEX, 800);

	maxHP =currentHP= 34;
	bodyDMG = 4.0f;
	injectDMG = 7.0f;
	speed = 3;
	whatTo = false;
	
	count = 1;
	alpha = 255;
	x = position.x;
	y = position.y;
	_currentFrameX = 0;
	reverseFrame = _nyx->getMaxFrameX();
	_probeX = x;
	_probeY = y;

	areaH = _rc.bottom - _rc.top;
	areaW = _rc.right - _rc.left;

	return S_OK;
}

void nyx::release()
{

}

void nyx::update()
{
	
	if (!whatTo&&direction&&!attack) { _state = LEFT_IDLEN; }
	if (!whatTo && !direction&&!attack) { _state = RIGHT_IDLEN; }
	if (whatTo&&direction && !attack) { _state = LEFT_MOVEN; x -= speed; }
	if (whatTo && !direction && !attack) { _state = RIGHT_MOVEN; x += speed; }
	if (whatTo&&direction&&attack) { _state = LEFT_ATTACKN; x -= speed * 1.5; }
	if (whatTo && !direction&&attack) { _state = RIGHT_ATTACKN; x += speed * 1.5; }
	if (direction) { _currentFrameY = 0; }
	if (!direction) { _currentFrameY = 1; }
	_count++;
	if (_count % 10 == 0)
	{
		if (_state == LEFT_IDLEN)
		{
			_nyx->setFrameX(reverseFrame);
			_nyx->setFrameY(_currentFrameY);
			_count = 0;
			if (reverseFrame <= 0) reverseFrame = _nyx->getMaxFrameX();
			reverseFrame--;
		}
		if (_state == RIGHT_IDLEN)
		{

			_nyx->setFrameX(_currentFrameX);
			_nyx->setFrameY(_currentFrameY);
			_count = 0;
			if (_currentFrameX >= _nyx->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameX++;
		}
		if (_state == LEFT_MOVEN)
		{

			_nyxM->setFrameX(reverseFrame);
			_nyxM->setFrameY(_currentFrameY);
			_count = 0;
			if (reverseFrame <= 0) reverseFrame = _nyxM->getMaxFrameX();
			reverseFrame--;
		}
		if (_state == RIGHT_MOVEN)
		{

			_nyxM->setFrameX(_currentFrameX);
			_nyxM->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX >= _nyxM->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameX++;
		}
		if (_state == LEFT_HITN)
		{

			_nyxH->setFrameX(reverseFrame);
			_nyxH->setFrameY(_currentFrameY);
			
			_count = 0;
			if (reverseFrame <= 0) reverseFrame = _nyxH->getMaxFrameX();
			reverseFrame--;
		}
		if (_state == RIGHT_HITN)
		{

			_nyxH->setFrameX(_currentFrameX);
			_nyxH->setFrameY(_currentFrameY);
			
			_count = 0;
			if (_currentFrameX >= _nyxH->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameX++;
		}
		
		if (_state == LEFT_ATTACKN)
		{

			_nyxA->setFrameX(reverseFrame);
			_nyxA->setFrameY(_currentFrameY);
			
			_count = 0;
			if (reverseFrame <= 0) reverseFrame = _nyxA->getMaxFrameX();
			reverseFrame--;
		}
		if (_state == RIGHT_ATTACKN)
		{

			_nyxA->setFrameX(_currentFrameX);
			_nyxA->setFrameY(_currentFrameY);
		
			_count = 0;
			if (_currentFrameX >= _nyxA->getMaxFrameX()) _currentFrameX = 0;
			_currentFrameX++;
		}

	}
	DATAMANAGER->setNX(x);
	DATAMANAGER->setNY(y);
	if (currentHP <= 0)
	{
		whatTo = false;
		attack = false;
		alpha -= 5;
	}
	_probeX = x;
	_probeY = y;
	pixelCollision();
	if (attack)
	{
		_rc = RectMakeCenter(x, y, _nyx->getFrameWidth()*1.5, _nyx->getFrameHeight());	
	}
	else if(whatTo)
	{
		_rc = RectMakeCenter(x, y - 20, _nyx->getFrameWidth(), _nyx->getFrameHeight());
	}
	else
	{
		_rc = RectMakeCenter(x, y, _nyx->getFrameWidth(), _nyx->getFrameHeight());
	}
	_censor = RectMakeCenter(x, y, 800, 800);
	_aCensor = RectMakeCenter(x, y, _nyx->getFrameWidth() + 50, _nyx->getFrameHeight() + 50);
}

void nyx::render()
{
	draw();
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _censor);
		Rectangle(getMemDC(), _aCensor);
		Rectangle(getMemDC(), _rc);
	}
}

void nyx::move()
{
}

void nyx::draw()
{
	if (_state == RIGHT_MOVEN || _state == LEFT_MOVEN)
	{
		_nyxM->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	 if (_state == RIGHT_ATTACKN || _state == LEFT_ATTACKN)
	{
		_nyxA->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	 if (_state == RIGHT_HITN || _state == LEFT_HITN)
	{
		_nyxH->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
	
	 if(_state==RIGHT_IDLEN||_state==LEFT_IDLEN)
	{
		_nyx->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	}
}

void nyx::pixelCollision()
{
	count = DATAMANAGER->getN();
	if (count == 1)map = "½ÃÀÛ¸Ê¹é";
	if (count == 2)map = "È¦¹é";
	if (count == 3)map = "Èú¹é";
	if (count == 4)map = "¹öÆ¼Ä®¹é";
	if (count == 5)map = "¼¼ÀÌºê¹é";
	if (count == 6)map = "º¸½º¹æ¹é";

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

		if ((r == 75 && g == 100 && b == 100))
		{
			x = i + areaW / 2;
			direction = false;
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
			x = i - areaW / 2;
			direction = true;
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
			y = i - areaH / 2;
			break;
		}

	}
	

}



void nyx::hitDamage(float damage)
{
	currentHP -= damage;
}


