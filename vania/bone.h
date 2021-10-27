#pragma once
#include "gameNode.h"
#include "bullets.h"
enum bonemove
{
	LEFT_IDLEBO,
	RIGHT_IDLEBO,
	LEFT_ATTACKBO,
	RIGHT_ATTACKBO,
};

class bone :public gameNode
{
private:
	image* _bone;
	image* _boneA;
	image* _boneI;
	RECT _rc;				//��Ʈ
	RECT _censor;			//������Ʈ

	bonemove _state;

	int _currentFrameX;//�����ӹ�ȣ�� ����� ����
	int reverseFrame;
	int _currentFrameY;

	int _count;				//�����ӷ����� ��
	int _fireCount;			//�߻� ī��Ʈ ��

	float maxHP, currentHP;
	float x, y;
	

	bool whatTo;
	bool direction;

public:
	bone() {};
	~bone() {};

	void setD(bool D) { direction = D; }
	void setWT(bool WT) { whatTo = WT; }

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();
	void draw();
	
	bool bulletCountFire();
	
	void hitDamage(float damage);
	
	float getHP() { return currentHP; }
	float getX() { return x; }
	float getY() { return y; }
	inline RECT getRect() { return _rc; }
	inline RECT getCensor() { return _censor; }
	bool getBD() { return direction; }
};