#include "stdafx.h"
#include "objectManager.h"
#include "player.h"

HRESULT objectManager::init()
{
	_vcombi.clear();
	_vdjump.clear();
	_vrheart.clear();
	return S_OK;
}

void objectManager::release()
{
}

void objectManager::update()
{
	for (_virheart = _vrheart.begin(); _virheart != _vrheart.end(); ++_virheart)
	{
		(*_virheart)->update();
	}
}

void objectManager::render()
{
	for (_vicombi = _vcombi.begin(); _vicombi != _vcombi.end(); ++_vicombi)
	{
		(*_vicombi)->render();
	}
	for (_vidjump = _vdjump.begin(); _vidjump != _vdjump.end(); ++_vidjump)
	{
		(*_vidjump)->render();
	}
	for (_virheart = _vrheart.begin(); _virheart != _vrheart.end(); ++_virheart)
	{
		(*_virheart)->render();
	}
}

void objectManager::setItem(int IT, int i, int j)
{
	switch (IT)
	{
	case 0:
		_djump = new Djump;
		_djump->init(PointMake(i,j));
		_vdjump.push_back(_djump);
		break;
	case 1:
		_Combi = new Combination;
		_Combi->init(PointMake(i, j));
		_vcombi.push_back(_Combi);
		break;
	case 2:
		_regenH = new regenHeart;
		_regenH->init(PointMake(i, j));
		_vrheart.push_back(_regenH);
		break;
	}
}

void objectManager::removeIdjump(int arrNum)
{
	_vdjump.clear();
}

void objectManager::removeIcombi(int arrNum)
{
	_vcombi.clear();
}

void objectManager::removeIregenH(int arrNum)
{
	_vrheart.erase(_vrheart.begin() + arrNum);
}
