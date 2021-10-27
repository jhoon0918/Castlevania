#pragma once
#include "gameNode.h"
class Djump :gameNode
{
private:
	image* _djump;
	
	RECT _rc;
	
	float x, y;

public:
	Djump() {};
	~Djump() {};
	
	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();
	
	RECT getRect() { return _rc; }
	
};
class Combination :gameNode
{
private:
	image* _Combi;

	RECT _rc;

	float x, y;

public:
	Combination() {};
	~Combination() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	RECT getRect() { return _rc; }
};
class regenHeart :gameNode
{
private:
	image* _reHeart;

	RECT _rc;

	float x, y;
	float _probeX, _probeY;
	float gravity, force;
	float areaH;
	
	const char* map;
	
	int count;
	

public:
	regenHeart() {};
	~regenHeart() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();
	
	void pixelCollision();

	RECT getRect() { return _rc; }
};