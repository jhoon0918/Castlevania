#pragma once
#include "JState.h"
class playerJ;
class JumpingState :public JState
{	
	public:
		int frameCount = 0;
		int index = 0;
		virtual JState* inputHandle(playerJ* player);
		virtual void update(playerJ* player);
		virtual void enter(playerJ* player);
		virtual void exit(playerJ* player);
};

class JumpingAttackState :public JState
{
public:
	int frameCount=0;
	int index = 0;
	int reverse;
	int count = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);

};
class JumpingSubAttackState :public JState
{
public:
	int frameCount=0;
	int index = 0;
	int count = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);

};


class JumpingHitState :public JState
{
public:
	int frameCount;
	int count = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);

};
class BackAttackState :public JState
{
public:
	int frameCount;
	int count = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);

};
