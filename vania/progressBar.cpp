#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(int x, int y, int width, int height)
{
    _x = x;
    _y = y;

    _rcProgress = RectMake(x, y, width, height);

    _progressBarTop = IMAGEMANAGER->addImage("frontBar", "img/HPbar.bmp", width, height, true, RGB(255, 0, 255));
    _progressBarBottom = IMAGEMANAGER->addImage("backBar", "img/backbar.bmp", width, height, true, RGB(255, 0, 255));

    //�������� ����ũ��� ��ø�� ������ �̹��� �߿��� �տ� ������ ������ ����ũ���!
    _width = _progressBarTop->getWidth();

    return S_OK;
}

void progressBar::release()
{
}

void progressBar::update()
{
    _rcProgress = RectMakeCenter(_x, _y, _progressBarTop->getWidth(),
        _progressBarTop->getHeight());

}

void progressBar::render()
{
    IMAGEMANAGER->render("backBar", getMemDC(),
        _rcProgress.left + _progressBarBottom->getWidth() / 2,
        _y + _progressBarBottom->getHeight() / 2, 0, 0,
        _progressBarBottom->getWidth(), _progressBarBottom->getHeight());

    //��� ������ ũ�Ⱑ �����Ǿ���ϱ⶧���� ����ũ��(sourWidth)�� _width ���� ����
    IMAGEMANAGER->render("frontBar", getMemDC(),
        _rcProgress.left + _progressBarBottom->getWidth() / 2,
        _y + _progressBarBottom->getHeight() / 2, 0, 0,
        _width, _progressBarBottom->getHeight());

}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
    //�ۼ��������� ������ָ� ���� ���� �������ϴ�
    _width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}

HRESULT manaBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_rcMana = RectMake(x, y, width, height);

	_manaBarTop = IMAGEMANAGER->addImage("manaBar", "img/manabar.bmp", width, height, true, RGB(255, 0, 255));
	_manaBarBottom = IMAGEMANAGER->addImage("backBar", "img/backbar.bmp", width, height, true, RGB(255, 0, 255));

	//�������� ����ũ��� ��ø�� ������ �̹��� �߿��� �տ� ������ ������ ����ũ���!
	_width = _manaBarTop->getWidth();

	return S_OK;
}

void manaBar::release()
{
}

void manaBar::update()
{
	_rcMana = RectMakeCenter(_x, _y, _manaBarTop->getWidth(),
		_manaBarTop->getHeight());
}

void manaBar::render()
{
	IMAGEMANAGER->render("backBar", getMemDC(),
		_rcMana.left + _manaBarBottom->getWidth() / 2,
		_y + _manaBarBottom->getHeight() / 2, 0, 0,
		_manaBarBottom->getWidth(), _manaBarBottom->getHeight());

	//��� ������ ũ�Ⱑ �����Ǿ���ϱ⶧���� ����ũ��(sourWidth)�� _width ���� ����
	IMAGEMANAGER->render("manaBar", getMemDC(),
		_rcMana.left + _manaBarBottom->getWidth() / 2,
		_y + _manaBarBottom->getHeight() / 2, 0, 0,
		_width, _manaBarBottom->getHeight());
}

void manaBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _manaBarBottom->getWidth();
}
