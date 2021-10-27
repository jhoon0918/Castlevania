#include "stdafx.h"
#include "object.h"

HRESULT Djump::init()
{
	return S_OK;
}

HRESULT Djump::init(POINT position)
{
	_djump = IMAGEMANAGER->findImage("djump item");
	_rc = RectMakeCenter(position.x, position.y, _djump->getWidth(), _djump->getHeight());
	x = position.x;
	y = position.y;
	return S_OK;
}

void Djump::release()
{
}

void Djump::update()
{
}

void Djump::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	_djump->render(getMemDC(), _rc.left, _rc.top);
}

HRESULT Combination::init()
{
	return S_OK;
}

HRESULT Combination::init(POINT position)
{
	_Combi = IMAGEMANAGER->findImage("combi item");
	_rc = RectMakeCenter(position.x, position.y, _Combi->getWidth(), _Combi->getHeight());
	x = position.x;
	y = position.y;
	return S_OK;
}

void Combination::release()
{
}

void Combination::update()
{
}

void Combination::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	_Combi->render(getMemDC(), _rc.left, _rc.top);
}

HRESULT regenHeart::init()
{
	return S_OK;
}

HRESULT regenHeart::init(POINT position)
{
	_reHeart = IMAGEMANAGER->findImage("heart item");
	_rc = RectMakeCenter(position.x, position.y, _reHeart->getWidth(), _reHeart->getHeight());
	x = position.x;
	y = position.y;
	_probeX = (_rc.left + _rc.right) / 2;
	_probeY = (_rc.top + _rc.bottom) / 2;
	areaH = _rc.bottom - _rc.top;
	force = gravity = 0;
	count = DATAMANAGER->getN();
	return S_OK;
}

void regenHeart::release()
{
	
}

void regenHeart::update()
{
	_probeX = (_rc.left + _rc.right) / 2;
	_probeY = (_rc.top + _rc.bottom) / 2;
	
	gravity += 0.001f;
	force -= gravity;
	y -= force;
	
	_rc = RectMakeCenter(x, y, _reHeart->getWidth(), _reHeart->getHeight());
	pixelCollision();
}

void regenHeart::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	_reHeart->render(getMemDC(), _rc.left, _rc.top);
}

void regenHeart::pixelCollision()
{
	count = DATAMANAGER->getN();
	if (count == 1)map = "시작맵백";
	if (count == 2)map = "홀백";
	if (count == 3)map = "힐백";
	if (count == 4)map = "버티칼백";
	if (count == 5)map = "세이브백";
	if (count == 6)map = "보스방백";
	if (count == 9)map = "null";

	for (int i = _probeY - areaH; i < _probeY + areaH; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(map)->getMemDC(), x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 100 && g == 100 && b == 100))
		{
			y = i - areaH + 1;
			gravity = 0;
			force = 0;
			break;
		}
	}
}
