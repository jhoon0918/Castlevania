#pragma once

class playerJ;

class JState
{
public:
	virtual JState* inputHandle(playerJ* player) = 0;
	virtual void update(playerJ* player)=0;
	virtual void enter(playerJ* player) = 0;
	virtual void exit(playerJ* player) = 0;
};

