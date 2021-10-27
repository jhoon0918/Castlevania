#include "stdafx.h"
#include "clear.h"

clear::clear()
{
}

clear::~clear()
{
}

HRESULT clear::init()
{
	IMAGEMANAGER->addImage("clear", "img/½æ³Ú.bmp", 1280, 720, true, RGB(255, 0, 255));
	return S_OK;
}

void clear::release()
{
}

void clear::update()
{
}

void clear::render()
{
}
