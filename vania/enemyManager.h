#pragma once
#include "gameNode.h"
#include "bat.h"
#include "blade.h"
#include "bone.h"
#include "nxy.h"
#include "corner.h"
#include "bullets.h"
#include "astarte.h"
#include <vector>


//상호참조를 위한 클라스 전방선언
enum enemyType
{
	_Ebat,
	_Eblade,
	_Ebone,
	_Enyx,
	_Ecorner,
	_Eastarte
};
class playerJ;

class enemyManager : public gameNode
{
private:
	
	

	typedef vector<bat*>				vEnemyb;
	typedef vector<bat*>::iterator		viEnemyb;

	typedef vector<nyx*>				vEnemyn;
	typedef vector<nyx*>::iterator		viEnemyn;

	typedef vector<bone*>				vEnemybo;
	typedef vector<bone*>::iterator		viEnemybo;

	typedef vector<blade*>				vEnemybl;
	typedef vector<blade*>::iterator	viEnemybl;

	typedef vector<corner*>				vEnemyc;
	typedef vector<corner*>::iterator	viEnemyc;

	typedef vector<astarte*>			vEnemyas;
	typedef vector<astarte*>::iterator	vIEnemyas;
private:

	vEnemyb _vbat;
	viEnemyb _vibat;

	vEnemybo _vbone;
	viEnemybo _vibone;

	vEnemybl _vblade;
	viEnemybl _viblade;
	vEnemyn _vnyx;
	viEnemyn _vinyx;
	vEnemyc _vcorner;
	viEnemyc _vicorner;
	vEnemyas _vastarte;
	vIEnemyas _viastarte;

	enemyManager* _em;
	triangle* _tri;
	heart* _heart;
	tornado* _torna;
	fireball* _fire;
	playerJ* _player;
	bat* eBat;
	blade* eblade;
	nyx* enyx;
	bone* ebone;
	corner* ecorner;
	astarte* eastarte;

	RECT prc;
	//얘는 빈 포인터에 불과하다 아직은
	int r;
	float x2;
	float y2;

public:
	enemyManager() {};
	~enemyManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setMinion(int ET,int i, int j);
	   
	void batCensorCollision();

	void bladeCencorCollision();
	
	void boneCensorCollision();
	void boneBulletFire();
	void boneFireCollsion();
	
	void nyxCensorCollision();
	void nyxAttackCensorCollision();
	
	void cornerCensorCollision();
	void cornerAttackCensorCollision();
	
	void bossCensorCollision();
	void bossAttackCensorCollision();
	void bossAttackTornado();
	void bossHeartAttack();
	void bossTriangle();
	void tornadoCollision();
	void heartCollision();
	void TriangleCollision();

	void removeBat(int arrNum);
	void removeBlade(int arrNum);
	void removeBone(int arrNum);
	void removeNyx(int arrNum);
	void removeCorner(int arrNum);
	void removeBoss(int arrNum);

	//단지 설정자인데 함수이름이 그럴싸함 주의
	void setPlayerMemoryAddressLink(playerJ* player) { _player = player; }
	

	vector<bat*> getVBat() { return _vbat; }
	vector<bat*>::iterator getVIBat() { return _vibat; }

	vector<nyx*> getVNyx() { return _vnyx; }
	vector<nyx*>::iterator getVINyx() { return _vinyx; }

	vector<bone*> getVBone() { return _vbone; }
	vector<bone*>::iterator getVIBone() { return _vibone; }

	vector<blade*> getVBlade() { return _vblade; }
	vector<blade*>::iterator getVIBlade() { return _viblade; }

	vector<corner*>getVCorner() { return _vcorner; }
	vector<corner*>::iterator getVICorner() { return _vicorner; }
	
	vector<astarte*>getVAstarte() { return _vastarte; }
	vector<astarte*>::iterator getVIAstarte() { return _viastarte; }

};

