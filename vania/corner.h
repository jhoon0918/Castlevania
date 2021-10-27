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

	
	RECT _rc;				//��Ʈ
	RECT _censor;			//������Ʈ
	RECT _aCensor;			//���ݰ���

	cornermove _state;

	int _currentFrameX;		//�����ӹ�ȣ�� ����� ����
	int _currentFrameY;

	
	int _count;				//�����ӷ����� ��
	int _fireCount;			//�߻� ī��Ʈ ��
	int _rndFireCount;		//���� �߻� ī��Ʈ ��
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

