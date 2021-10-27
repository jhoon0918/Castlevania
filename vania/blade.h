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

	RECT _rc;				//��Ʈ
	RECT _censor;			//������Ʈ

	blademove _state;

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

