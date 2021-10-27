#pragma once
#include "singletonBase.h"
#include "image.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	//카메라가 비추는 화면 크기(WINSIZEX, WINSIZEY)와 좌표(left, right, top, bottom)
	RECT _screen, _zoom;
	int _backWidth, _backHeight;	//backDC 크기
	int _frontWidth, _frontHeight;	//frontDC 크기
	float _count;
	float x, y;

public:
	cameraManager();
	~cameraManager();

	HRESULT init(int width, int height);
	void release();

	//카메라 위치 갱신
	void updateScreen(float standardX, float standardY,
		float ratioX = 0.5f, float ratioY = 0.5f, float zoom = 1.0f);
	//카메라 진동
	void vibrateScreen(float standardX, float standardY,
		float magnitude = 5.0f, float interval = 0);
	//카메라 출력
	void render(HDC frontDC, int destX, int destY, HDC backDC,
		float zoom = 1.0f);

	void setBackScreenSize(float width, float height) { _backWidth = width, _backHeight = height; }
	//void setFrontScreenSize(float width, float height) { _frontWidth = width, _frontHeight = height; }
	float getBackScreenWidth() { return _backWidth; }
	float getBackScreenHeight() { return _backHeight; }
	float getX() { return x; }
	float getY() { return y; }
};

