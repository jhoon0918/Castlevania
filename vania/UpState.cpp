#include "stdafx.h"
#include "UpState.h"
#include "StandingState.h"
#include "JumpingState.h"
#include "player.h"

JState * UpState::inputHandle(playerJ * player)
{
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		return new StandingState();
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		return new SubattackState();
	}
	if (KEYMANAGER->isOnceKeyDown('C')&&player->getPCMP()>70&&PLAYERMANAGER->getFUSION())
	{
		return new CombiState();
	}
	if (player->getHITTED())
	{
		return new HittedState();
	}
	if (player->getBACKHITTED())
	{
		return new BackHitted();
	}
	if (!player->getLP())
	{
		return new DyingState();
	}
	return nullptr;
}

void UpState::update(playerJ * player)
{
	frameCount++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
		if (frameCount >= 10)
		{
			player->getI()->setFrameY(0);
			player->getI()->setFrameX(player->getI()->getFrameX() + 1);

			if (player->getI()->getFrameX() >= player->getI()->getMaxFrameX())
			{
				player->getI()->setFrameX(0);
			}
			frameCount = 0;
		}
	}
	else if (!player->getD())
	{
		if (frameCount >= 10)
		{
			player->getI()->setFrameY(1);
			player->getI()->setFrameX(player->getI()->getFrameX() - 1);

			if (player->getI()->getFrameX() <= 0)
			{
				player->getI()->setFrameX(player->getI()->getMaxFrameX());
			}
			frameCount = 0;
		}
	}
	player->setRC(player->getX(), player->getY(), 70, 140);
}

void UpState::enter(playerJ * player)
{
	player->setImg("업");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
	return;
}

void UpState::exit(playerJ * player)
{
}

JState * SubattackState::inputHandle(playerJ * player)
{
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		player->setDC(1);
		return new StandingState();
	}
	if (KEYMANAGER->isOnceKeyDown('Z') || KEYMANAGER->isStayKeyDown('Z'))
	{
		return new AttackState();
	}
	if (KEYMANAGER->isOnceKeyDown('X') || KEYMANAGER->isStayKeyDown('x'))
	{
		return new JumpingState();
	}
	if (!player->getLP())
	{
		return new DyingState();
	}
	return nullptr;
}

void SubattackState::update(playerJ * player)
{
	frameCount++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
		if (frameCount >= 5)
		{

			player->getI()->setFrameY(0);
			player->getI()->setFrameX(index);
			frameCount = 0;
			index++;
			if (index > player->getI()->getMaxFrameX())
			{
				index = 0;
			}
		}
	}
	else if (!player->getD())
	{
		if (frameCount >= 5)
		{
			player->getI()->setFrameY(1);
			player->getI()->setFrameX(player->getI()->getFrameX() - 1);

			if (player->getI()->getFrameX() < 0)
			{
				player->getI()->setFrameX(player->getI()->getMaxFrameX());
			}
			frameCount = 0;
		}
	}
	player->setRC(player->getX(), player->getY(), 70, 140);
}

void SubattackState::enter(playerJ * player)
{
	player->setImg("서브공격");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
	return;
}

void SubattackState::exit(playerJ * player)
{
}

JState * CombiState::inputHandle(playerJ * player)
{
	if (KEYMANAGER->isOnceKeyUp('C')&&player->getPCMP()>=70)
	{
		player->setPCMP(player->getPCMP() - 70);
		player->setCP(true);
		return new CombionState();
	}
	
	
	return nullptr;
}

void CombiState::update(playerJ * player)
{
	frameCount++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
		if (frameCount >= 2)
		{

			player->getI()->setFrameY(0);
			player->getI()->setFrameX(index);
			frameCount = 0;
			index++;
			if (index > player->getI()->getMaxFrameX())
			{
				index = 0;
			}
		}
	}
	else if (!player->getD())
	{
		if (frameCount >= 2)
		{
			player->getI()->setFrameY(1);
			player->getI()->setFrameX(player->getI()->getFrameX() - 1);

			if (player->getI()->getFrameX() < 0)
			{
				player->getI()->setFrameX(player->getI()->getMaxFrameX());
			}
			frameCount = 0;
		}
	}
	player->setRC(player->getX(), player->getY(), 70, 140);
}

void CombiState::enter(playerJ * player)
{
	player->setImg("콤비준비");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
	return;
}

void CombiState::exit(playerJ * player)
{
}

JState * CombionState::inputHandle(playerJ * player)
{
	if (!player->getCP())
	{
		return new StandingState;
	}
	return nullptr;
}

void CombionState::update(playerJ * player)
{
	frameCount++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
		if (frameCount >= 2)
		{

			player->getI()->setFrameY(0);
			player->getI()->setFrameX(index);
			frameCount = 0;
			index++;
			if (index > player->getI()->getMaxFrameX())
			{
				index = 0;
			}
		}
	}
	else if (!player->getD())
	{
		if (frameCount >= 2)
		{
			player->getI()->setFrameY(1);
			player->getI()->setFrameX(player->getI()->getFrameX() - 1);

			if (player->getI()->getFrameX() < 0)
			{
				player->getI()->setFrameX(player->getI()->getMaxFrameX());
			}
			frameCount = 0;
		}
	}
	player->setRC(player->getX(), player->getY(), 70, 140);
}

void CombionState::enter(playerJ * player)
{
	player->setImg("콤비온");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
	return;
}

void CombionState::exit(playerJ * player)
{
}
