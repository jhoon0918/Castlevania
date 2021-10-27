#pragma once
#include "singletonBase.h"

class objectManager;

class objectdataManager:public singletonBase<objectdataManager>
{
private:
	objectManager* _om;
public:
	objectManager* getObjectManagerMemoryAddressLink() { return _om; }
	void setObjectManagerMemoryAddressLink(objectManager* om) { _om = om; }

	objectdataManager();
	~objectdataManager();

	HRESULT init();
	void release();
};

