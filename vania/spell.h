#pragma once
#include "gameNode.h"
#include <vector>

struct tagWhip
{ 
	RECT rc;				//�Ѿ� ��Ʈ
	float x, y;				//�Ѿ� ��ǥ(�ǽð�)
	float angle;			//�Ѿ� ����
	float radius;			//�Ѿ� ������
	float fireX, fireY;		//�Ѿ� �߻�� ó�� ��ǥ(�߻�� ��ǥ)
	bool isFire;			//�߻�ƴ�?
	int count;				//�Ѿ� ������ī��Ʈ��
};
struct tagDagger
{
	image* Image;
	RECT rc;
	float x, y;
	float angle;
	float fireX, fireY;
	float speed;
	int count;
};
struct tagLightning
{
	image* Image;
	image* Image1;
	RECT rc;
	float x, y;
	float fireX, fireY;
	int count;
};
	
class lightning :public gameNode
{
private:
	vector<tagLightning>				_vLightning;
	vector<tagLightning>::iterator		_viLightning;

	const char* _imageName;
	float _range;
	int _bulletMax;
	int currentY = 0;
	float damage = 10.0f;


public:
	lightning() {};
	~lightning() {};
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);
	void removeMissile();

	vector<tagLightning> getVLightning() { return _vLightning; }
	vector<tagLightning>::iterator getVILightning() { return _viLightning; }

	float getDMG() { return damage; }
};

class dagger :public gameNode
{
private:
	vector<tagDagger>				_vDagger;
	vector<tagDagger>::iterator		_viDagger;

	const char* _imageName;
	float _range;
	int _bulletMax;
	int currentY = 0;
	float damage = 5.0f;


public:
	dagger() {};
	~dagger() {};
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);
	void move();
	void removeMissile(int arrNum);
	
	vector<tagDagger> getVDagger() { return _vDagger; }
	vector<tagDagger>::iterator getVIDagger() { return _viDagger; }

	float getDMG() { return damage; }
};

class whip:public gameNode
{
private:
	vector<tagWhip>					_vWhip;
	vector<tagWhip>::iterator		_viWhip;

	float _range;
	int _bulletMax;
	float damage = 20.0f;
	tagWhip _whip;

public:
	whip() {};
	~whip() {};
	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();
	
	void fire(float x, float y);
	void move();
	void removeMissile();
	vector<tagWhip> getVWhip() { return _vWhip; }
	vector<tagWhip>::iterator getVIWhip() { return _viWhip; }
	float getDMG() { return damage; }
};

//class hyunMoo : public gameNode
//{
//private:
//	vector<tagBullet>			_vBullet;
//	vector<tagBullet>::iterator _viBullet;
//
//	float _range;
//	int _bulletMax;
//
//public:
//	hyunMoo() {};
//	~hyunMoo() {};
//
//	HRESULT init(int bulletMax, float range);
//	void release();
//	void update();
//	void render();
//
//	void fire(float x, float y);
//
//	void move();
//
//	//�Ѿ� �����޶�� �����Լ�
//	void removeMissile(int arrNum);
//
//	vector<tagBullet> getVHyunMoo() { return _vBullet; }
//	vector<tagBullet>::iterator getVIHyunMoo() { return _viBullet; }
//};