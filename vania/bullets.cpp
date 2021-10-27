#include "stdafx.h"
#include "bullets.h"


HRESULT fireball::init(const char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void fireball::release()
{
}

void fireball::update()
{
	move();
	if (DATAMANAGER->getBD()) { currentY = 0; }
	if (!DATAMANAGER->getBD()) { currentY = 1; }
}

void fireball::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (DATAMANAGER->getBD())
		{
			_viBullet->bulletImage->frameRender(getMemDC(),
				_viBullet->rc.left,
				_viBullet->rc.top,
				_viBullet->bulletImage->getFrameX(),currentY);

			_viBullet->count++;

			if (_viBullet->count % 10 == 0)
			{
				_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);

				//최대 프레임보다 커지면
				if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
				{
					_viBullet->bulletImage->setFrameX(0);
				}

				_viBullet->count = 0;
			}
		}
		if(!DATAMANAGER->getBD())
		{
			_viBullet->bulletImage->frameRender(getMemDC(),
				_viBullet->rc.left,
				_viBullet->rc.top,
				_viBullet->bulletImage->getFrameX(), currentY);

			_viBullet->count++;

			if (_viBullet->count % 5 == 0)
			{
				_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() - 1);

				//최대 프레임보다 커지면
				if (_viBullet->bulletImage->getFrameX() <= 0)
				{
					_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getMaxFrameX());
				}

				_viBullet->count = 0;
			}
		}
		if(KEYMANAGER->isToggleKey(VK_TAB))
		Rectangle(getMemDC(), _viBullet->rc);
	}
	
}

void fireball::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.radius = bullet.bulletImage->getWidth() / 2;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.dmg = 15.0f;
	bullet.angle = angle;

	bullet.rc = RectMake(bullet.x, bullet.y,
		100,
		50);

	_vBullet.push_back(bullet);
}

void fireball::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		

		_viBullet->rc = RectMake(_viBullet->x, _viBullet->y,
			100,
			50);

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void fireball::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}



HRESULT tornado::init(const char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void tornado::release()
{
}

void tornado::update()
{
	move();
	if (DATAMANAGER->getBOD()) { currentY = 0; }
	if (!DATAMANAGER->getBOD()) { currentY = 1; }
}

void tornado::render()
{
	for (_viTorna = _vTorna.begin(); _viTorna != _vTorna.end(); ++_viTorna)
	{
		if (DATAMANAGER->getBOD())
		{
			cout << "왼쪽";
			_viTorna->Image1->frameRender(getMemDC(),
				_viTorna->rc.left,
				_viTorna->rc.top,
				_viTorna->Image1->getFrameX(), currentY);
			_viTorna->Image2->frameRender(getMemDC(),
				_viTorna->rc1.left,
				_viTorna->rc1.top,
				_viTorna->Image2->getFrameX(), currentY);
			_viTorna->Image3->frameRender(getMemDC(),
				_viTorna->rc2.left,
				_viTorna->rc2.top,
				_viTorna->Image3->getFrameX(), currentY);
			_viTorna->count++;

			if (_viTorna->count % 10 == 0)
			{
				_viTorna->Image1->setFrameX(index);
				_viTorna->Image2->setFrameX(index1);
				_viTorna->Image3->setFrameX(index2);
				
				index++;
				index1++;
				index2++;
				//최대 프레임보다 커지면
				if (_viTorna->Image1->getFrameX() >= _viTorna->Image1->getMaxFrameX())
				{
					index = 0;
					index1 = index + 1;
					index2 = index - 1;
				}

				_viTorna->count = 0;
			}
		}
		if (!DATAMANAGER->getBOD())
		{
			cout << "오른쪽";
			_viTorna->Image1->frameRender(getMemDC(),
				_viTorna->rc.left,
				_viTorna->rc.top,
				_viTorna->Image1->getFrameX(), currentY);
			_viTorna->Image2->frameRender(getMemDC(),
				_viTorna->rc1.left,
				_viTorna->rc1.top,
				_viTorna->Image2->getFrameX(), currentY);
			_viTorna->Image3->frameRender(getMemDC(),
				_viTorna->rc2.left,
				_viTorna->rc2.top,
				_viTorna->Image3->getFrameX(), currentY);
			_viTorna->count++;

			if (_viTorna->count % 10 == 0)
			{
				_viTorna->Image1->setFrameX(index);
				_viTorna->Image2->setFrameX(index1);
				_viTorna->Image3->setFrameX(index2);
				
				index--;
				index1--;
				index2--;
				//최대 프레임보다 커지면
				if (_viTorna->Image1->getFrameX() <= 0)
				{
					index=_viTorna->Image1->getMaxFrameX();
					index1=index+1;
					index2 = index - 1;
				}
				_viTorna->count = 0;
			}
		}
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(getMemDC(), _viTorna->rc);
			Rectangle(getMemDC(), _viTorna->rc1);
			Rectangle(getMemDC(), _viTorna->rc2);
		}
	}
}

void tornado::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vTorna.size()) return;

	tagTorna _torna;
	ZeroMemory(&_torna, sizeof(tagTorna));
	_torna.Image1 = IMAGEMANAGER->findImage(_imageName);
	_torna.Image2 = IMAGEMANAGER->findImage(_imageName);
	_torna.Image3 = IMAGEMANAGER->findImage(_imageName);
	_torna.speed = speed;
	_torna.dmg = 12.0f;
	_torna.x = _torna.fireX = x;
	_torna.y = _torna.fireY = y;
	_torna.angle = angle;

	_torna.rc = RectMake(_torna.x+190, _torna.y,50,75);
	_torna.rc1 = RectMake(_torna.x+150, _torna.y, 50, 75);
	_torna.rc2= RectMake(_torna.x+110, _torna.y, 50, 75);

	_vTorna.push_back(_torna);
}

void tornado::move()
{
	for (_viTorna = _vTorna.begin(); _viTorna != _vTorna.end();)
	{
		_viTorna->x += cosf(_viTorna->angle) * _viTorna->speed;

		_viTorna->rc = RectMake(_viTorna->x + 190, _viTorna->y, 50, 75);
		_viTorna->rc1 = RectMake(_viTorna->x + 150, _viTorna->y+20, 60, 90);
		_viTorna->rc2 = RectMake(_viTorna->x+110, _viTorna->y-20, 50, 85);

		if (_range < getDistance(_viTorna->x, _viTorna->y, _viTorna->fireX, _viTorna->fireY))
		{
			_viTorna = _vTorna.erase(_viTorna);
		}
		else ++_viTorna;
	}
}

void tornado::removeBullet(int arrNum)
{
	_vTorna.erase(_vTorna.begin() + arrNum);
}

HRESULT heart::init(const char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void heart::release()
{
}

void heart::update()
{
	move();
	if (DATAMANAGER->getBOD()) { currentY = 1; }
	if (!DATAMANAGER->getBOD()) { currentY = 0; }
}

void heart::render()
{
	for (_viHeart = _vHeart.begin(); _viHeart != _vHeart.end(); ++_viHeart)
	{
		if (DATAMANAGER->getBOD())
		{
			_viHeart->Image->setFrameX(0);
			cout << "왼쪽";
			_viHeart->Image->frameRender(getMemDC(),
				_viHeart->rc.left,
				_viHeart->rc.top,
				_viHeart->Image->getFrameX(), currentY);		
		}
		if (!DATAMANAGER->getBOD())
		{
			cout << "오른쪽";
			_viHeart->Image->setFrameX(0);
			_viHeart->Image->frameRender(getMemDC(),
			_viHeart->rc.left,
			_viHeart->rc.top,
			_viHeart->Image->getFrameX(), currentY);
		}
		if (KEYMANAGER->isToggleKey(VK_TAB))
			Rectangle(getMemDC(), _viHeart->rc);
	}

}

void heart::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vHeart.size()) return;

	tagHeart heart;
	ZeroMemory(&heart, sizeof(tagHeart));
	heart.Image = IMAGEMANAGER->findImage(_imageName);
	heart.speed = speed;
	heart.radius = heart.Image->getWidth() / 2;
	heart.x = heart.fireX = x;
	heart.y = heart.fireY = y;
	heart.dmg = 10.0f;
	heart.angle = angle;
	heart.rc = RectMakeCenter(heart.x, heart.y,
		heart.Image->getWidth(),
		heart.Image->getHeight()/2);

	_vHeart.push_back(heart);
}

void heart::move()
{
	for (_viHeart = _vHeart.begin(); _viHeart != _vHeart.end();)
	{
		
		_viHeart->x += cosf(_viHeart->angle) * _viHeart->speed;
		_viHeart->y += -sinf(_viHeart->angle) * _viHeart->speed;
		

		_viHeart->rc = RectMakeCenter(_viHeart->x, _viHeart->y,
			_viHeart->Image->getWidth(),
			_viHeart->Image->getHeight()/2);

		if (_range < getDistance(_viHeart->x, _viHeart->y, _viHeart->fireX, _viHeart->fireY))
		{
			_viHeart = _vHeart.erase(_viHeart);
		}
		else ++_viHeart;
	}
}

void heart::removeBullet(int arrNum)
{
	_vHeart.erase(_vHeart.begin() + arrNum);
}

HRESULT triangle::init(const char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void triangle::release()
{
}

void triangle::update()
{
	move();
}

void triangle::render()
{
	for (_viTri = _vTri.begin(); _viTri != _vTri.end(); ++_viTri)
	{
		_viTri->Image->frameRender(getMemDC(),
		_viTri->rc.left-20,
		_viTri->rc.top,
		_viTri->Image->getFrameX(), currentY);
		_viTri->count++;
		if (_viTri->count % 10 == 0)
		{
			_viTri->Image->setFrameX(_viTri->Image->getFrameX() + 1);

			//최대 프레임보다 커지면
			if (_viTri->Image->getFrameX() >= _viTri->Image->getMaxFrameX())
			{
				_viTri->Image->setFrameX(0);
			}

			_viTri->count = 0;
		}

		if (KEYMANAGER->isToggleKey(VK_TAB))
			Rectangle(getMemDC(), _viTri->rc);
	}
}

void triangle::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vTri.size()) return;

	tagTriangle _tri;
	ZeroMemory(&_tri, sizeof(tagTriangle));
	_tri.Image = IMAGEMANAGER->findImage(_imageName);
	_tri.speed = speed;
	_tri.radius = _tri.Image->getWidth() / 2;
	_tri.x = _tri.fireX = x;
	_tri.y = _tri.fireY = y;
	_tri.angle = angle;
	_tri.dmg = 50.0f;
	_tri.rc = RectMakeCenter(_tri.x, _tri.y,
		_tri.Image->getWidth()/5,
		_tri.Image->getHeight());

	_vTri.push_back(_tri);
}

void triangle::move()
{
	for (_viTri = _vTri.begin(); _viTri != _vTri.end();)
	{

		_viTri->x += cosf(_viTri->angle) * _viTri->speed;
		_viTri->y += -sinf(_viTri->angle) * _viTri->speed;


		_viTri->rc = RectMakeCenter(_viTri->x, _viTri->y,
		_viTri->Image->getWidth()/5,
		_viTri->Image->getHeight());

		if (_range < getDistance(_viTri->x, _viTri->y, _viTri->fireX, _viTri->fireY))
		{
			_viTri = _vTri.erase(_viTri);
		}
		else ++_viTri;
	}
}

void triangle::removeBullet(int arrNum)
{
	_vTri.erase(_vTri.begin() + arrNum);
}
