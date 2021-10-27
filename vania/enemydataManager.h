#pragma once
#include "singletonBase.h"

class enemyManager;

class enemydataManager:public singletonBase<enemydataManager>
{
private:
	enemyManager* _em;
public:
	
	enemyManager* getEnemyManagerMemoryAddressLink() { return _em; }
	void setEnemyManagerMemoryAddressLink(enemyManager* em) { _em = em; }

	enemydataManager();
	~enemydataManager();

	HRESULT init();
	void release();
};

