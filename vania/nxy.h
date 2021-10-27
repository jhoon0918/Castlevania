#pragma once
#include "gameNode.h"
enum nyxmove
{
	LEFT_IDLEN,
	RIGHT_IDLEN,
	LEFT_DIEN,
	RIGHT_DIEN,
	LEFT_HITN,
	RIGHT_HITN,
	LEFT_ATTACKN,
	RIGHT_ATTACKN,
	LEFT_MOVEN,
	RIGHT_MOVEN
};

class nyx :public gameNode
{
private:
	image* _nyx;
	image* _nyxA;
	image* _nyxM;
	image* _nyxI;
	image* _nyxH;
	image* _nyxD;

	RECT _rc;				//렉트
	RECT _censor;			//감지렉트
	RECT _aCensor;			//공격감지

	nyxmove _state;

	int _currentFrameX;		//프레임번호로 사용할 변수
	int reverseFrame;
	int _currentFrameY;

	int _count;				//프레임렌더링 용
	int _fireCount;			//발사 카운트 용
	int _rndFireCount;		//랜덤 발사 카운트 용
	int speed;
	
	float bodyDMG, injectDMG;
	float maxHP,currentHP;
	float areaH;
	float areaW;
	float _probeY;
	float _probeX;
	float x, y;

	int alpha;
	int count;
	const char* map;

	bool whatTo;
	bool attack;
	bool direction;
	

public:
	nyx() {};
	~nyx() {};

	void setD(bool D) { direction = D; }
	void setWT(bool WT) { whatTo = WT; }
	void setAT(bool AT) { attack = AT; }
	void setAP(int _alpha) { alpha = _alpha; }

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
	bool getND() { return direction; }
	float getX(){return x;}
	float getY(){return y;}
	float getbodYDMG() { return bodyDMG; }
	float getinjecTDMG() { return injectDMG; }
	int getAP() { return alpha; }
};

