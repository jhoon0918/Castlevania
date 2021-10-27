#pragma once
#include "gameNode.h"
#include "object.h"
#include <vector>

enum itemType
{
	_Idjump,
	_Icombi,
	_Iheart
};

class playerJ;
class objectManager :public gameNode
{
private:
	typedef vector<Djump*>						vIdjump;
	typedef vector<Djump*>::iterator			viIdjump;

	typedef vector<Combination*>				vIcombi;
	typedef vector<Combination*>::iterator		viIcombi;

	typedef vector<regenHeart*>					vIheart;
	typedef vector<regenHeart*>::iterator		viIheart;

private:

	vIdjump			 _vdjump;
	viIdjump		 _vidjump;

	vIcombi			 _vcombi;
	viIcombi		 _vicombi;

	vIheart			 _vrheart;
	viIheart		 _virheart;

	objectManager*	_om;
	Djump*			_djump;
	Combination*	_Combi;
	regenHeart*		_regenH;
	playerJ* _player;

public:
	objectManager() {};
	~objectManager() {};
	
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setItem(int IT, int i, int j);
	
	void removeIdjump(int arrNum);
	void removeIcombi(int arrNum);
	void removeIregenH(int arrNum);

	void setPlayerMemoryAddressLinkI(playerJ* player) { _player = player; }

	vector<Djump*>	getVDjump() { return _vdjump; }
	vector<Djump*>::iterator	getVIDjump() {return _vidjump;	}

	vector<Combination*>			getVCombi() { return _vcombi; }
	vector<Combination*>::iterator	getVICombi() { return _vicombi; }

	vector<regenHeart*>				getVReH(){return _vrheart;}
	vector<regenHeart*>::iterator	getVIReH(){return _virheart;}


};

