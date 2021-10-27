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

	RECT _rc;				//��Ʈ
	RECT _censor;			//������Ʈ

	batmove _state;

	int _currentFrameX;		//�����ӹ�ȣ�� ����� ����
	int _currentFrameY;

	int _count;				//�����ӷ����� ��
	int _fireCount;			//�߻� ī��Ʈ ��
	int _rndFireCount;		//���� �߻� ī��Ʈ ��
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

