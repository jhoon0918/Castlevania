#pragma once
#include "singletonBase.h"

class playerJ;

class playerManager:public singletonBase<playerManager>
{
private:
	float px;
	float py;
	float pHP;
	float pcHP;
	float pMP;
	float pcMP;

	int djump;
	
	bool fusion;

	RECT prc;
	playerJ* _playerJ;
public:
	
	playerJ* getPlayerJMemoryAddressLink() { return _playerJ; }
	void setPlayerJMemoryAddressLink(playerJ* playerJ) { _playerJ = playerJ; }

	void setPX(float PX){px=PX;}
	void setPY(float PY){py=PY;}
	void setPHP(float PHP){pHP=PHP;}
	void setPCHP(float PCHP){pcHP=PCHP;}
	void setPRC(RECT PRC){prc=PRC;}
	void setPMP(float PMP) { pMP = PMP; }
	void setPCMP(float PCMP) { pcMP = PCMP; }
	void setDJUMP(int DJUMP) { djump = DJUMP; }
	void setFUSION(bool FUSION) { fusion = FUSION; }

	playerManager();
	~playerManager();

	HRESULT init();
	void release();

	float getPX(){return px;}
	float getPY(){return py;}
	float getPHP(){return pHP;}
	float getPCHP(){return pcHP;}
	float getPMP(){return pMP;}
	float getPCMP(){return pcMP;}
	int getDJUMP() { return djump; }
	bool getFUSION() { return fusion; }

	RECT getPRC() { return prc; }


};


