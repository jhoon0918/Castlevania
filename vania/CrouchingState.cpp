#include "stdafx.h"
#include "CrouchingState.h"
#include "StandingState.h"
#include "player.h"

JState * CrouchingState::inputHandle(playerJ * player)
{
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		return new StandingState();
	}
	if (KEYMANAGER->isOnceKeyDown('Z')||KEYMANAGER->isStayKeyDown('Z'))
	{
		return new CrouchAttack();
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		return new Slide();
	}
	if (player->getHITTED())
	{
		return new CrouchHit();
	}
	if (!player->getLP())
	{
		return new DyingState();
	}

	return nullptr;
}

void CrouchingState::update(playerJ * player)
{
	frameCount++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
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
	player->setRC(player->getX(), player->getY()+50, 70, 90);
}

void CrouchingState::enter(playerJ * player)
{
	player->setImg("導擠");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
	return;
}

void CrouchingState::exit(playerJ * player)
{
}

JState * CrouchAttack::inputHandle(playerJ * player)
{
	if (count >= 45)
	{
		
		index = 0;
		reverse = player->getI()->getMaxFrameX();
		player->setWA(false);
		return new CrouchingState;
	}
	if (!player->getLP())
	{
		return new DyingState();
	}
	return nullptr;
}

void CrouchAttack::update(playerJ * player)
{
	count++;
	frameCount++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
		if (frameCount >= 4)
		{
			
			player->getI()->setFrameY(0);
			player->getI()->setFrameX(index);
			frameCount = 0;
			
			if (index > player->getI()->getMaxFrameX())
			{
				index = 0;
			}
			index++;
		}
		player->setRC(player->getX(), player->getY() + 40, 70, 70);
	}
	else if (!player->getD())
	{
		if (frameCount >= 4)
		{
			player->getI()->setFrameY(1);
			player->getI()->setFrameX(reverse);
			
			if (reverse< 0)
			{
				reverse=player->getI()->getMaxFrameX();
			}
			reverse--;
			frameCount = 0;
		}
		player->setRC(player->getX(), player->getY()+40 , 70, 70);
	}
	
}

void CrouchAttack::enter(playerJ * player)
{
	player->setImg("導擠奢問");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
	reverse = player->getI()->getMaxFrameX();
	return;
}

void CrouchAttack::exit(playerJ * player)
{
}

JState * CrouchHit::inputHandle(playerJ * player)
{
	if (count >= 60)
	{
		count = 0;
		player->setHITTED(false);
		return new CrouchingState;
	}
	if (!player->getLP())
	{
		return new DyingState();
	}
	return nullptr;
}

void CrouchHit::update(playerJ * player)
{
	frameCount++;
	count++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
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
	player->setRC(player->getX(), player->getY() + 20, 70, 120);
}

void CrouchHit::enter(playerJ * player)
{
	player->setImg("導擠Я問");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
}

void CrouchHit::exit(playerJ * player)
{
}

JState * Slide::inputHandle(playerJ * player)
{
	if (count >= 30)
	{
		return new CrouchingState;
	}
	if (!player->getLP())
	{
		return new DyingState();
	}
	return nullptr;
}

void Slide::update(playerJ * player)
{
	count++;
	frameCount++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
		player->setX(player->getX() - (player->getS()*1.5));
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
		player->setX(player->getX() + (player->getS()*1.5));
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
	player->setRC(player->getX(), player->getY()+40, 100, 80);
}

void Slide::enter(playerJ * player)
{
	player->setImg("蝸塭檜萄");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
	return;
}

void Slide::exit(playerJ * player)
{
}

