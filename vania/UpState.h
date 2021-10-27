#pragma once
#include "JState.h"

class playerJ;

class UpState :public JState
{
public:
	int frameCount;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);
};

class SubattackState :public JState
{
public:
	int frameCount;
	int index = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);
};

class CombiState :public JState
{
public:
	int frameCount;
	int index = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);
};
class CombionState :public JState
{
public:
	int frameCount;
	int index = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);
};

