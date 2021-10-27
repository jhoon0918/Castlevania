#pragma once
#include "JState.h"

class playerJ;

class StandingState:public JState
{
public:
	int frameCount=0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);

};

class AttackState :public JState
{
public:
	int count = 0;
	int count1 = 0;
	int index = 0;
	int reverse;
	int frameCount=0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);

};

class HittedState :public JState
{
public:
	int frameCount = 0;
	int count = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);
};
class BackHitted :public JState
{
public:
	int frameCount = 0;
	int count = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);
};
class BackstepState : public JState
{
public:
	int frameCount = 0;
	int count = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);
};
class RunState : public JState
{
	int frameCount;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);
};

class CharlotteState :public JState
{
public:
	int frameCount = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);

};
class DyingState :public JState
{
public:
	int frameCount = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);

};