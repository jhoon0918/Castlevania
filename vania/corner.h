#pragma once
#include "gameNode.h"

enum cornermove
{
	LEFT_IDLEC,
	RIGHT_IDLEC,
	LEFT_MOVEC,
	RIGHT_MOVEC,
	LEFT_ATTACKC,
	RIGHT_ATTACKC
};

class corner:public gameNode
{
	image* _corner;
	image* _cornerI;
	image* _cornerA;
	image* _cornerM;

	
	RECT _rc;				//렉트
	RECT _censor;			//감지렉트
	RECT _aCensor;			//공격감지

	cornermove _state;

	int _currentFrameX;		//프레임번호로 사용할 변수
	int _currentFrameY;

	
	int _count;				//프레임렌더링 용
	int _fireCount;			//발사 카운트 용
	int _rndFireCount;		//랜덤 발사 카운트 용
	int speed;
	
	float bodyDMG;
	float currentHP, maxHP;
	float _probeY;
	float _probeX;
	float areaH;
	float areaW;
	float x, y;

	int count;
	const char* map;

	bool block;
	bool whatTo;
	bool attack;
	bool direction;
	bool pierceCountFire;
public:
	corner() {};
	~corner() {};

	void setD(bool D) { direction = D; }
	void setWT(bool WT) { whatTo = WT; }
	void setAT(bool AT) { attack = AT; }

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();
	
	
	void move();
	void draw();
	void pixelCollision();

	void hitDamage(float damage);

	float getHP() { return currentHP; }

	inline RECT getRect() { return _rc; }
	inline RECT getCensor() { return _censor; }
	inline RECT getACensor() { return _aCensor; }
	bool getCD() { return direction; }
	float getX() { return x; }
	float getY() { return y; }
	bool getPCF() { return pierceCountFire; }
	float getbodYDMG() {return bodyDMG;	}
};

