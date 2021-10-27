#pragma once
#include "gameNode.h"
#include "spell.h"
#include "progressBar.h"
#include "JState.h"
#include "playground.h"
#pragma warning(disable:4996)

//1. �����Ϸ� ���ѷ����� ���������� ����
//2. ����ӵ��� ���̱� ����
//��ȣ������ ���� Ŭ�� ���漱��
class enemyManager;
class objectManager;

class playerJ:public gameNode
{
private:

	////�굵 ������ �󲮵�����
	enemyManager* _em;
	objectManager* _om;
	whip* _whip;
	dagger* _dagger;
	progressBar* _hpBar;
	manaBar* _mpBar;
	lightning* _lt;
	
	float _currentHP, _maxHP;
	float _currentMP, _maxMP;
	
	int manacount;
	int _countA;
	int _alphaValue;
	int	_index;
	int doubleJ;
	int dcount;
	int combiCount;
	int alpha;

	float _count;
	

	RECT _p;
	RECT _p2;
	float _x, _y;
	float _probeY; //probe == Ž��
	float _probeX;


	RECT rc;
	image* img;
	image* jH;
	image* cH;
	image* ui;
	
	
	float x, y;
	float gravity;
	float force;
	float areaH;
	float areaW;
	
	
	int speed;
	int jump;
	int maxJump;


	bool state;
	bool isJump;
	bool whipA;
	bool hitted;
	bool backhitted;
	bool combiProgress;
	bool character;
	bool life;
	


	int scene;

	//true: ����, false: ������
	bool direction;
	int count;
	const char* map;

public:
	
	void setImg(const char * name) { img = IMAGEMANAGER->findImage(name); }
	void setRC(float x, float y, int x1, int y1) { rc = RectMake(x, y, x1, y1);}
	void setPRC(RECT PRC) { rc = PRC; }
	void setF(float force1) { force = force1; }
	void setY(float Y1) { y = Y1; }
	void setX(float X1) { x = X1; }
	void setD(bool D) { direction = D; }
	void setG(float G) { gravity = G; }
	void setSc(int Sc) { scene = Sc; }
	void setC(int C) { count = C; }
	void setDJ(int DJ) { doubleJ = DJ; }
	void setPHP(float PHP){_maxHP=PHP;}
	void setPCHP(float PCHP){_currentHP=PCHP;}
	void setPMP(float PMP){_maxMP=PMP;}
	void setPCMP(float PCMP){_currentMP=PCMP;}
	void setDC(int DC) { dcount = DC; }
	void setWA(bool WA) { whipA = WA; }
	void setHITTED(bool HT) { hitted = HT; }
	void setBACKHITTED(bool BH) { backhitted = BH; }
	void setCP(bool CP) { combiProgress = CP; }
	void setLP(bool LP){life=LP;}
	void setCT(bool CT){character=CT;}

	void InputHandle();
	JState* _state;

	playerJ();
	~playerJ();
	
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void pixelCollision();

	void hitDamage(float damage);

	RECT getRC() { return rc; }
	image* getI() { return img; }
	int getS() { return speed; }
	bool getD() { return direction; }
	float getG() { return gravity; }
	float getF() { return force; }
	float getX() { return x; }
	float getY() { return y; }
	int getSc() { return scene; }
	int getDJ() { return doubleJ; }
	float getPHP(){return _maxHP;}
	float getPCHP(){return _currentHP;}
	float getPMP() { return _maxMP; }
	float getPCMP() { return _currentMP; }
	int getDC() { return dcount; }
	int getCC() { return combiCount; }
	bool getCP() { return combiProgress; }
	bool getHITTED(){return hitted;}
	bool getBACKHITTED(){return backhitted;}
	bool getLP(){return life;}
	bool getCT(){return character;}

	////�浹�Լ�
	void batMaincollision();
	void batSubcollsion();
	void batcollision();

	void bladeMaincollision();
	void bladeSubcollision();
	void bladecollsion();

	
	void boneMaincollision();
	void boneSubcollision();
	void bonecollision();
	
	void cornerMaincollision();
	void cornerSubcollsion();
	void cornercollision();

	void nyxMaincollision();
	void nyxSubcollision();
	void nyxcollision();

	void bossMaincollision();
	void bossSubcollision();
	void bossbodycollsion();
	
	void combicollision();

	void djumpcollision();
	void combiitemcollision();
	void rheartcollision();

	
	////�̸��� ��ɽ� �׷����� ������ �Լ�
	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }
	void setOmMemoryAddressLink(objectManager* om) { _om = om; }

	whip* getWhip() { return _whip; }
	
	
	

};

