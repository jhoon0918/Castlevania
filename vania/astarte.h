#pragma once
#include "gameNode.h"

enum astmove
{
	LEFT_IDLEAS,
	RIGHT_IDLEAS,
	LEFT_STAFFAS,
	RIGHT_STAFFAS,
	LEFT_HITAS,
	RIGHT_HITAS,
	LEFT_MELEEAS,
	RIGHT_MELEEAS,
	LEFT_MOVEAS,
	RIGHT_MOVEAS,
	LEFT_HEART,
	RIGHT_HEART,
	LEFT_TORNA,
	RIGHT_TORNA,
	LEFT_FLEE,
	RIGHT_FLEE
};

class astarte:public gameNode
{
	image* _ast;
	image* _astS;
	image* _astM;
	image* _astI;
	image* _astH;
	image* _astT;
	image* _astJ;
	image* _astK;
	image* _astML;


	RECT _rc;				//렉트
	RECT _censor;			//감지렉트
	RECT _aCensor;			//공격감지

	astmove _state;

	int _currentFrameX;		//프레임번호로 사용할 변수
	int _currentFrameY;

	int _count;				//프레임렌더링 용
	int _fireCount;			//발사 카운트 용
	int _fireCount1;
	int _fireCount2;
	int _rndFireCount;		//랜덤 발사 카운트 용
	int speed;

	float heartDMG, tornaDMG, triDMG, bodyDMG;
	float gravity;
	float force;
	float areaH;
	float areaW;
	float _probeY;
	float _probeX;
	float x, y;
	float maxHP, currentHP;

	int count;
	int pcount;
	int rp;
	const char* map;

	bool whatTo;
	bool attack;
	bool direction;
	bool pattern;		//밀리공격
	bool pattern1;		//하트공격
	bool pattern2;		//토네이도
	bool pattern3;		//스태프 , 점프
	bool staff;
	bool progress;




public:
	astarte() {};
	~astarte() {};

	void setD(bool D) { direction = D; }
	void setWT(bool WT) { whatTo = WT; }
	void setAT(bool AT) { attack = AT; }
	void setP(bool P) { pattern=P; }
	void setP1(bool P) { pattern1 = P; }
	void setP2(bool P) { pattern2 = P; }
	void setP3(bool P) { pattern3 = P; }
	void setPR(bool PR) { progress = PR; }

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void move();
	void draw();
	void pixelCollision();
	

	bool tornaCountFire();
	bool heartCountFire();
	bool triCountFire();

	void hitDamage(float damage);
	
	float getHP() { return currentHP; }
	inline RECT getRect() { return _rc; }
	inline RECT getCensor() { return _censor; }
	inline RECT getACensor() { return _aCensor; }
	inline bool getPR() { return progress; }
	bool getAD() { return direction; }
	float getX() { return x; }
	float getY() { return y; }
	float gethearTDMG(){return heartDMG;}
	float gettornADMG(){return tornaDMG;}
	float gettrIDMG(){return triDMG;}
	float getbodYDMG(){return bodyDMG;}
};

