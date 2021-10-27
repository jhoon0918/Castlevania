#pragma once
#include "JState.h"

class playerJ;

class CrouchingState :public JState
{
public:
	int frameCount;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);

};
class CrouchAttack :public JState
{
public:
	int frameCount;
	int index = 0;
	int reverse;
	int count = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);

};
class CrouchHit :public JState
{
public:
	int frameCount=0;
	int count = 0;
	int index = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);

};
class Slide :public JState
{
public:
	int frameCount;
	int index = 0;
	int count = 0;
	virtual JState* inputHandle(playerJ* player);
	virtual void update(playerJ* player);
	virtual void enter(playerJ* player);
	virtual void exit(playerJ* player);

};
