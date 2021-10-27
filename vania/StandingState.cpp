#include "stdafx.h"
#include "StandingState.h"
#include "JumpingState.h"
#include "CrouchingState.h"
#include "UpState.h"
#include "player.h"

JState * StandingState::inputHandle(playerJ * player)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		player->setD(false);
		return new RunState();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		player->setD(true);
		return new RunState();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown(VK_UP))
	{
		return new UpState();
	}
	if (KEYMANAGER->isOnceKeyDown('Z') || KEYMANAGER->isStayKeyDown('Z'))
	{
		return new AttackState();
	}
	if (KEYMANAGER->isOnceKeyDown('X') || KEYMANAGER->isStayKeyDown('X'))
	{
		return new JumpingState();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) || KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		return new CrouchingState();
	}
	if (KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isStayKeyDown('A') && player->getPCMP() >= 6)
	{
		return new SubattackState();
	}
	if (KEYMANAGER->isOnceKeyDown('Q') || KEYMANAGER->isStayKeyDown('Q'))
	{
		return new BackstepState();
	}
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		player->setCT(false);
		return new CharlotteState();
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


void StandingState::update(playerJ * player)
{

	frameCount++;
	if(player->getF()>-5)player->setF(player->getF() - player->getG());
	player->setY(player->getY()-player->getF());
	
	
	if (player->getD())
	{
		if (frameCount >=5)
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
		if (frameCount >= 5)
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

void StandingState::enter(playerJ * player)
{
	player->setImg("기본");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
	return;
}

void StandingState::exit(playerJ * player)
{
}

JState * AttackState::inputHandle(playerJ * player)
{
	if (KEYMANAGER->isOnceKeyDown('X') || KEYMANAGER->isStayKeyDown('X'))
	{
		return new JumpingState();
	}
	if (KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isStayKeyDown('A') && player->getPCMP() >= 6)
	{
		
		return new SubattackState();
	}
	if (count >= 1 || count1 >= 1)
	{
		player->setWA(false);
		index = 0;
		reverse = player->getI()->getMaxFrameX();
		return new StandingState();
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

void AttackState::update(playerJ * player)
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
			
			if (index >= player->getI()->getMaxFrameX())
			{
				index=0;
				count++;
			}
			index++;
			frameCount = 0;
		}
	}
	else if (!player->getD())
	{
		if (frameCount >= 2)
		{
			player->getI()->setFrameY(1);
			player->getI()->setFrameX(reverse);
			
			if (reverse <= 0)
			{
				reverse=player->getI()->getMaxFrameX();
				count1++;
			}
			reverse--;
			frameCount = 0;
		}
	}
	player->setRC(player->getX(), player->getY(), 70, 140);
}

void AttackState::enter(playerJ * player)
{
	player->setImg("공격");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
	reverse = player->getI()->getMaxFrameX();
	return;
}

void AttackState::exit(playerJ * player)
{
}

JState * RunState::inputHandle(playerJ * player)
{
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		return new StandingState();
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		return new StandingState();
	}
	if (KEYMANAGER->isOnceKeyDown('Z')||KEYMANAGER->isStayKeyDown('Z'))
	{
		return new AttackState();
	}
	if (KEYMANAGER->isOnceKeyDown('X') || KEYMANAGER->isStayKeyDown('X'))
	{
		return new JumpingState();
	}
	if (KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isStayKeyDown('A')&&player->getPCMP()>=6)
	{
		
		return new SubattackState();
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

void RunState::update(playerJ * player)
{
	frameCount++;
	if (player->getF() > -5)
		player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (!player->getD())
	{
		if (frameCount >= 3)
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
	else if (player->getD())
	{
		if (frameCount >= 3)
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
	player->setRC(player->getX(), player->getY(), 70, 140);
}

void RunState::enter(playerJ * player)
{
	player->setImg("런");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
}

void RunState::exit(playerJ * player)
{
}

JState * HittedState::inputHandle(playerJ * player)
{
	if (count >= 60)
	{
		count = 0;
		player->setHITTED(false);
		return new StandingState;
	}
	if (!player->getLP())
	{
		return new DyingState();
	}
	return nullptr;
}

void HittedState::update(playerJ * player)
{

	frameCount++;
	count++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
		player->setX(player->getX() + 2);
		if (frameCount > 5)
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
		player->setX(player->getX() - 2);
		if (frameCount >= 5)
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

void HittedState::enter(playerJ * player)
{
	player->setImg("피격");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
}

void HittedState::exit(playerJ * player)
{
}

JState * BackHitted::inputHandle(playerJ * player)
{
	if (count >= 60)
	{
		count = 0;
		player->setBACKHITTED(false);
		return new StandingState;
	}
	if (!player->getLP())
	{
		return new DyingState();
	}
	return nullptr;
}

void BackHitted::update(playerJ * player)
{
	frameCount++;
	count++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
		player->setX(player->getX() - 3);
		if (frameCount > 5)
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
		player->setX(player->getX() + 3);
		if (frameCount >= 5)
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

void BackHitted::enter(playerJ * player)
{
	player->setImg("백어택");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
}

void BackHitted::exit(playerJ * player)
{
}

JState * BackstepState::inputHandle(playerJ * player)
{
	if (count >= 40)
	{
		return new StandingState;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		return new RunState;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		return new RunState;
	}
	if (!player->getLP())
	{
		return new DyingState();
	}
	return nullptr;
}

void BackstepState::update(playerJ * player)
{
	frameCount++;
	count++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
		player->setX(player->getX() + (player->getS()) * 1.4);
		if (frameCount >= 5)
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
		player->setX(player->getX() - player->getS() * 1.4);
		if (frameCount >= 5)
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

void BackstepState::enter(playerJ * player)
{
	player->setImg("백스텝");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
}

void BackstepState::exit(playerJ * player)
{
}

JState * CharlotteState::inputHandle(playerJ * player)
{
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		player->setCT(true);
		return new StandingState();
	}
	return nullptr;
}

void CharlotteState::update(playerJ * player)
{
	frameCount++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
		if (frameCount >= 5)
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
		if (frameCount >= 5)
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

void CharlotteState::enter(playerJ * player)
{
	player->setImg("샬롯기본");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
}

void CharlotteState::exit(playerJ * player)
{
}

JState * DyingState::inputHandle(playerJ * player)
{
	return nullptr;
}

void DyingState::update(playerJ * player)
{
	frameCount++;

	player->setY(player->getY() + 50);


	if (player->getD())
	{
		player->setX(player->getX() - 3);
		if (frameCount > 5)
		{
			player->getI()->setFrameY(0);
			player->getI()->setFrameX(player->getI()->getFrameX() + 1);

			if (player->getI()->getFrameX() >= player->getI()->getMaxFrameX())
			{
				player->getI()->setFrameX(player->getI()->getMaxFrameX());
			}
			frameCount = 0;
		}
	}
	else if (!player->getD())
	{
		player->setX(player->getX() + 3);
		if (frameCount >= 5)
		{
			player->getI()->setFrameY(1);
			player->getI()->setFrameX(player->getI()->getFrameX() - 1);

			if (player->getI()->getFrameX() <= 0)
			{
				player->getI()->setFrameX(0);
			}
			frameCount = 0;
		}
	}
	player->setRC(player->getX(), player->getY(), 70, 140);
}

void DyingState::enter(playerJ * player)
{
	player->setImg("백어택");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
}

void DyingState::exit(playerJ * player)
{
}
