#include "stdafx.h"
#include "spell.h"

HRESULT whip::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void whip::release()
{
}

void whip::update()
{
	if (DATAMANAGER->getD())
	{
		
		_whip.rc = RectMake(_whip.x - 200, _whip.y + 30, 200, 30);

		cout << "그만";
	}
	else
	{
		
		_whip.rc = RectMake(_whip.x + 70, _whip.y + 30, 200, 30);
		cout << "그만!";
	}
	
}

void whip::render()
{
	for (_viWhip = _vWhip.begin(); _viWhip != _vWhip.end();++_viWhip)
	{
		if(KEYMANAGER->isToggleKey(VK_TAB))
		Rectangle(getMemDC(), _whip.rc);
	}	
}

void whip::fire(float x, float y)
{
	if (_bulletMax < _vWhip.size()) return;

	
	ZeroMemory(&_whip, sizeof(tagWhip));
	_whip.x = _whip.fireX = x;
	_whip.y = _whip.fireY = y;
	if (DATAMANAGER->getD())
	{
		_whip.rc = RectMake(_whip.x-200, _whip.y+30,200,30);
	}
	else
	{
		_whip.rc = RectMake(_whip.x+70, _whip.y + 30, 200, 30);
	}
	_vWhip.push_back(_whip);
}

void whip::move()
{
	
	
}

void whip::removeMissile()
{
	cout << "흐헤헤헤헤 채찍";
	_vWhip.clear();
}

HRESULT dagger::init(const char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void dagger::release()
{
}

void dagger::update()
{
	move();
	if (DATAMANAGER->getD()) { currentY = 0; }
	if (!DATAMANAGER->getD()) { currentY = 1; }
}

void dagger::render()
{
	for (_viDagger = _vDagger.begin(); _viDagger != _vDagger.end(); ++_viDagger)
	{
		_viDagger->Image->frameRender(getMemDC(),
			_viDagger->rc.left,
			_viDagger->rc.top,
			_viDagger->Image->getFrameX(), currentY);
	}
}

void dagger::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vDagger.size()) return;

	tagDagger dag;
	ZeroMemory(&dag, sizeof(tagDagger));
	dag.Image = IMAGEMANAGER->findImage(_imageName);
	dag.speed = speed;
	dag.x = dag.fireX = x;
	dag.y = dag.fireY = y;
	dag.angle = angle;
	dag.rc = RectMakeCenter(dag.x, dag.y,
		dag.Image->getFrameWidth(),
		dag.Image->getFrameHeight()/2 );

	_vDagger.push_back(dag);
}

void dagger::move()
{
	for (_viDagger = _vDagger.begin(); _viDagger != _vDagger.end();)
	{

		_viDagger->x += cosf(_viDagger->angle) * _viDagger->speed;


		_viDagger->rc = RectMakeCenter(_viDagger->x, _viDagger->y,
		_viDagger->Image->getFrameWidth(),
		_viDagger->Image->getFrameHeight() / 2);

		if (_range < getDistance(_viDagger->x, _viDagger->y, _viDagger->fireX, _viDagger->fireY))
		{
			_viDagger = _vDagger.erase(_viDagger);
		}
		else ++_viDagger;
	}
}

void dagger::removeMissile(int arrNum)
{
	_vDagger.erase(_vDagger.begin() + arrNum);
}

HRESULT lightning::init(const char * imageName,  int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void lightning::release()
{
}

void lightning::update()
{
}

void lightning::render()
{
	for (_viLightning = _vLightning.begin(); _viLightning != _vLightning.end(); ++_viLightning)
	{
		_viLightning->Image->frameRender(getMemDC(),_viLightning->rc.left,_viLightning->rc.top,_viLightning->Image->getFrameX(), currentY);
		_viLightning->count++;

		if (_viLightning->count % 3 == 0)
		{
			_viLightning->Image->setFrameX(_viLightning->Image->getFrameX() + 1);
			//최대 프레임보다 커지면
			if (_viLightning->Image->getFrameX() >= _viLightning->Image->getMaxFrameX())
			{
				_viLightning->Image->setFrameX(0);
			}
			_viLightning->count = 0;
		}
		if (KEYMANAGER->isToggleKey(VK_TAB))
			Rectangle(getMemDC(), _viLightning->rc);
	}
	
	
}

void lightning::fire(float x, float y)
{
	if (_bulletMax < _vLightning.size()) return;

	tagLightning light;
	ZeroMemory(&light, sizeof(tagLightning));
	light.Image = IMAGEMANAGER->findImage(_imageName);
	light.x = light.fireX = x;
	light.y = light.fireY = y;
	

	light.rc = RectMake(light.x, light.y,1024,1024);

	_vLightning.push_back(light);
}

void lightning::removeMissile()
{
	_vLightning.clear();
}
