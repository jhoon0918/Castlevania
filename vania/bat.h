#pragma once
#include "gameNode.h"

enum batmove
{
	LEFT_HANG,
	RIGHT_HANG,
	LEFT_MOVE,
	RIGHT_MOVE
};

class bat :public gameNode
{
private:
	image* _bat;
	image* _batIdle;
	image* _batMove;

	RECT _rc;				//렉트
	RECT _censor;			//감지렉트

	batmove _state;

	int _currentFrameX;		//프레임번호로 사용할 변수
	int _currentFrameY;

	int _count;				//프레임렌더링 용
	int _fireCount;			//발사 카운트 용
	int _rndFireCount;		//랜덤 발사 카운트 용
	int speed;
	

	float maxHP, currentHP;
	float bodyDMG;
	float x, y;
	
	bool whatTo;
	bool direction;

public:
	bat() {};
	~bat() {};
	
	void setD(bool D) { direction = D; }
	void setWT(bool WT) { whatTo = WT; }

	virtual HRESULT init();
	virtual HRESULT init( POINT position);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw();

	void hitDamage(float damage);
	
	float getHP() { return currentHP; }
	RECT getRect() { return _rc; }
	RECT getCensor() { return _censor; }
	float getbodYDMG() { return bodyDMG; }
};

