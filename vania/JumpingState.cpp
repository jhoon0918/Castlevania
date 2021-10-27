#include "stdafx.h"
#include "JumpingState.h"
#include "StandingState.h"
#include "CrouchingState.h"
#include "UpState.h"
#include "player.h"

JState * JumpingState::inputHandle(playerJ * player)
{
	if (player->getF()==0)
	{
		return new StandingState();
	}
	if (KEYMANAGER->isOnceKeyDown('Z') ||KEYMANAGER->isStayKeyDown('Z'))
	{
		return new JumpingAttackState;
	}
	if ((KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isOnceKeyDown('A')) && player->getPCMP() >= 6)
	{
		
		return new JumpingSubAttackState;
	}
	if ((KEYMANAGER->isOnceKeyDown('X') || KEYMANAGER->isStayKeyDown('X'))&&player->getDJ()>0&&player->getF()<-1)
	{
		player->setG(0);

		return new JumpingState();
	}
	if (player->getHITTED())
	{
		return new JumpingHitState();
	}
	if (player->getBACKHITTED())
	{
		return new BackAttackState();
	}
	if (!player->getLP())
	{
		return new DyingState();
	}
	return nullptr;
}

void JumpingState::update(playerJ * player)
{
	frameCount++;
	if(KEYMANAGER->isOnceKeyUp('X')||player->getG()>0.535f)player->setDJ(player->getDJ()-1);
	

	if (player->getD())
	{
		if (player->getF() < 3.0f)
		{
			player->setF(player->getF() + 0.6f);
		}
		player->setY(player->getY() - player->getF());
		if (frameCount >= 15)
		{
			
			player->getI()->setFrameY(0);
			player->getI()->setFrameX(index);
			index++;
			frameCount = 0;
			if (index >= 3)
			{
				index=0;
			}
			index++;
		}
	}
	else if (!player->getD())
	{
		if (player->getF() < 3.0f)
		{
			player->setF(player->getF() + 0.6f);
		}
		if (frameCount >= 15)
		{
			player->getI()->setFrameY(1);
			player->getI()->setFrameX(player->getI()->getFrameX() - 1);

			if (player->getI()->getFrameX() <= player->getI()->getMaxFrameX()-4)
			{
				player->getI()->setFrameX(player->getI()->getMaxFrameX());
			}
			frameCount = 0;
		}
	}
	player->setG(player->getG()+0.008f);
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());
	player->setRC(player->getX(), player->getY(), 70, 140);
}

void JumpingState::enter(playerJ * player)
{
	player->setImg("점프");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
	return;
}

void JumpingState::exit(playerJ * player)
{
}

JState * JumpingAttackState::inputHandle(playerJ * player)
{
	if (count >= 40&&(index=player->getI()->getMaxFrameX())||(reverse<0))
	{
		index = 0;
		reverse = player->getI()->getMaxFrameX();
		player->setWA(false);
		
		return new StandingState;
	}
	if (!player->getLP())
	{
		return new DyingState();
	}
	return nullptr;
}

void JumpingAttackState::update(playerJ * player)
{
	count++;
	frameCount++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
		if (frameCount >= 2.5)
		{

			player->getI()->setFrameY(0);
			player->getI()->setFrameX(index);
			frameCount = 0;
			
			if (index >= player->getI()->getMaxFrameX())
			{
				index = 0;
			}
			index++;
		
		}
	}
	else if (!player->getD())
	{
		if (frameCount >= 2.5)
		{
			player->getI()->setFrameY(1);
			player->getI()->setFrameX(reverse);
			
			if (reverse <= 0)
			{
				reverse =player->getI()->getMaxFrameX();
			}
			reverse--;
			frameCount = 0;
		}
	}
	player->setRC(player->getX(), player->getY(), 70, 140);
}

void JumpingAttackState::enter(playerJ * player)
{
	player->setImg("공중공격");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
	reverse = player->getI()->getMaxFrameX();
	index = 0;
	return;
}

void JumpingAttackState::exit(playerJ * player)
{
	index = 0;
	reverse = player->getI()->getMaxFrameX();

}

JState * JumpingSubAttackState::inputHandle(playerJ * player)
{
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		player->setDC(1);
		return new StandingState();
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		return new JumpingState();
	}
	if (player->getF() < -5)
	{
		return new StandingState();
	}
	if (!player->getLP())
	{
		return new DyingState();
	}
	return nullptr;
}

void JumpingSubAttackState::update(playerJ * player)
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

void JumpingSubAttackState::enter(playerJ * player)
{
	player->setImg("공중서브");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
	return;
}

void JumpingSubAttackState::exit(playerJ * player)
{
}

JState * JumpingHitState::inputHandle(playerJ * player)
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

void JumpingHitState::update(playerJ * player)
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

void JumpingHitState::enter(playerJ * player)
{
	player->setImg("공중피격");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
}

void JumpingHitState::exit(playerJ * player)
{
}

JState * BackAttackState::inputHandle(playerJ * player)
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

void BackAttackState::update(playerJ * player)
{
	frameCount++;
	count++;
	if (player->getF() > -5)player->setF(player->getF() - player->getG());
	player->setY(player->getY() - player->getF());


	if (player->getD())
	{
		player->setX(player->getX() + 3);
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

void BackAttackState::enter(playerJ * player)
{
	player->setImg("백어택");
	if (!player->getD())player->getI()->setFrameY(1);
	if (player->getD())player->getI()->setFrameY(0);
}

void BackAttackState::exit(playerJ * player)
{
}
