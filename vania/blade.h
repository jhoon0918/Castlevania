#pragma once
#include "gameNode.h"

enum blademove
{
	LEFT_IDLEB,
	RIGHT_IDLEB,
	LEFT_MOVEB,
	RIGHT_MOVEB
};

class blade :public gameNode
{
private:
	image* _blade;
	image* _bladeI;
	image* _bladeM;

	RECT _rc;				//렉트
	RECT _censor;			//감지렉트

	blademove _state;

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
	bool upDown;
	bool direction;

public:
	blade() {};
	~blade () {};

	void setD(bool D) { direction = D; }
	void setWT(bool WT) { whatTo = WT; }
	void setUD(bool UD) { upDown = UD; }

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void draw();
	void hitDamage(float damage);
	
	
	float getHP() { return currentHP; }
	inline RECT getRect() { return _rc; }
	inline RECT getCensor() { return _censor; }
	float getbodYDMG() { return bodyDMG; }
};

