#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;		//�Ѿ� �̹��� 
	RECT rc;				//�Ѿ� ��Ʈ
	float x, y;				//�Ѿ� ��ǥ(�ǽð�)
	float angle;			//�Ѿ� ����
	float radius;			//�Ѿ� ������
	float speed;			//�Ѿ� ���ǵ�
	float dmg;
	float fireX, fireY;		//�Ѿ� �߻�� ó�� ��ǥ(�߻�� ��ǥ)
	bool isFire;
	int count;				//�Ѿ� ������ī��Ʈ��
};
struct tagTorna
{
	image* Image1;		//�Ѿ� �̹��� 
	image* Image2;
	image* Image3;
	RECT rc;
	RECT rc1;
	RECT rc2;
	float x, y;				//�Ѿ� ��ǥ(�ǽð�)
	float angle;			//�Ѿ� ����
	float radius;			//�Ѿ� ������
	float speed;			//�Ѿ� ���ǵ�
	float fireX, fireY;		//�Ѿ� �߻�� ó�� ��ǥ(�߻�� ��ǥ)
	float dmg;
	int count;				//�Ѿ� ������ī��Ʈ��
};
struct tagHeart
{
	image* Image;
	RECT rc;
	float x, y;
	float angle;
	float radius;
	float speed;
	float fireX, fireY;
	float dmg;
	bool isFire;
	int count;
};
struct tagTriangle
{
	image* Image;
	RECT rc;
	float x, y;
	float angle;
	float radius;
	float speed;
	float fireX, fireY;
	float dmg;
	int count;
};
class triangle :public gameNode
{
	vector<tagTriangle>			_vTri;
	vector<tagTriangle>::iterator _viTri;

	const char* _imageName;
	float _range;
	int _bulletMax;
	int currentY = 0;
public:
	triangle() {};
	~triangle() {};

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);

	void move();

	void removeBullet(int arrNum);

	vector<tagTriangle> getVTri() { return _vTri; }
	vector<tagTriangle>::iterator getViTri() { return _viTri; }


};
class heart :public gameNode
{
	vector<tagHeart>			_vHeart;
	vector<tagHeart>::iterator _viHeart;

	const char* _imageName;
	float _range;
	int _bulletMax;
	int currentY = 0;
public:
	heart() {};
	~heart() {};

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);

	void move();

	void removeBullet(int arrNum);

	vector<tagHeart> getVHeart() { return _vHeart; }
	vector<tagHeart>::iterator getViHeart() { return _viHeart; }
};
class fireball : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;
	int currentY=0;
public:
	fireball() {};
	~fireball() {};

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);

	void move();

	//�Ѿ��� �����޶�� �����ϴ� �Լ�
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

};
class tornado : public gameNode
{
private:
	vector<tagTorna>			_vTorna;
	vector<tagTorna>::iterator _viTorna;

	const char* _imageName;
	float _range;
	int _bulletMax;
	int currentY = 0;
	int index=0;
	int index1=1;
	int index2=-1;
public:
	tornado() {};
	~tornado() {};

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);

	void move();

	//�Ѿ��� �����޶�� �����ϴ� �Լ�
	void removeBullet(int arrNum);

	vector<tagTorna> getVTorna() { return _vTorna; }
	vector<tagTorna>::iterator getViTorna() { return _viTorna; }

};

