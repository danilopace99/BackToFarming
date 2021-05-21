#pragma once
#include "stdafx.h"
#include "MyGame.h"

void CMyGame::backcode()
{
	//move the backgrounds
	for (CSprite* back1 : backlist)
	{
		CVector displacement = back1->GetPos() - player.GetPos();
		//left right movement
		//moving right
		if (displacement.GetX() <= -2048)
		{
			int left;
			if (back1->GetHealth() == 1)
			{
				left = 3;
			}
			else if (back1->GetHealth() == 2)
			{
				left = 1;
			}
			else if (back1->GetHealth() == 3)
			{
				left = 2;
			}
			for (CSprite* back2 : backlist)
			{
				if (back2->GetStatus() == back1->GetStatus() && back2->GetHealth() == left)
				{
					back1->SetX(back2->GetX() + 1024);
				}
			}
		}
		//moving left
		else if (displacement.GetX() >= 2048)
		{
			int right;
			if (back1->GetHealth() == 1)
			{
				right = 2;
			}
			else if (back1->GetHealth() == 2)
			{
				right = 3;
			}
			else if (back1->GetHealth() == 3)
			{
				right = 1;
			}
			for (CSprite* back2 : backlist)
			{
				if (back2->GetStatus() == back1->GetStatus() && back2->GetHealth() == right)
				{
					back1->SetX(back2->GetX() - 1024);
				}
			}
		}

		//up down movement
		//moving up
		if (displacement.GetY() <= -1536)
		{
			int below;
			if (back1->GetStatus() == 1)
			{
				below = 3;
			}
			else if (back1->GetStatus() == 2)
			{
				below = 1;
			}
			else if (back1->GetStatus() == 3)
			{
				below = 2;
			}
			for (CSprite* back2 : backlist)
			{
				if (back2->GetHealth() == back1->GetHealth() && back2->GetStatus() == below)
				{
					back1->SetY(back2->GetY() + 768);
				}
			}
		}
		//moving down
		if (displacement.GetY() >= 1536)
		{
			int above;
			if (back1->GetStatus() == 1)
			{
				above = 2;
			}
			else if (back1->GetStatus() == 2)
			{
				above = 3;
			}
			else if (back1->GetStatus() == 3)
			{
				above = 1;
			}
			for (CSprite* back2 : backlist)
			{
				if (back2->GetHealth() == back1->GetHealth() && back2->GetStatus() == above)
				{
					back1->SetY(back2->GetY() - 768);
				}
			}
		}
	}
}

void CMyGame::createbacks()
{
	//set up backgrounds
	//row 1
	CSprite* back1_1 = new CSprite((GetWidth() / 2) - 1024, (GetHeight() / 2) - 768, "explorebg.bmp", GetTime());
	back1_1->SetHealth(1);
	back1_1->SetStatus(1);
	backlist.push_back(back1_1);
	CSprite* back2_1 = new CSprite(GetWidth() / 2, (GetHeight() / 2) - 768, "explorebg.bmp", GetTime());
	back2_1->SetHealth(2);
	back2_1->SetStatus(1);
	backlist.push_back(back2_1);
	CSprite* back3_1 = new CSprite((GetWidth() / 2) + 1024, (GetHeight() / 2) - 768, "explorebg.bmp", GetTime());
	back3_1->SetHealth(3);
	back3_1->SetStatus(1);
	backlist.push_back(back3_1);
	//row 2
	CSprite* back1_2 = new CSprite((GetWidth() / 2) - 1024, GetHeight() / 2, "explorebg.bmp", GetTime());
	back1_2->SetHealth(1);
	back1_2->SetStatus(2);
	backlist.push_back(back1_2);
	CSprite* back2_2 = new CSprite(GetWidth() / 2, GetHeight() / 2, "explorebg.bmp", GetTime());
	back2_2->SetHealth(2);
	back2_2->SetStatus(2);
	backlist.push_back(back2_2);
	CSprite* back3_2 = new CSprite((GetWidth() / 2) + 1024, GetHeight() / 2, "explorebg.bmp", GetTime());
	back3_2->SetHealth(3);
	back3_2->SetStatus(2);
	backlist.push_back(back3_2);
	//row 3
	CSprite* back1_3 = new CSprite((GetWidth() / 2) - 1024, (GetHeight() / 2) + 768, "explorebg.bmp", GetTime());
	back1_3->SetHealth(1);
	back1_3->SetStatus(3);
	backlist.push_back(back1_3);
	CSprite* back2_3 = new CSprite(GetWidth() / 2, (GetHeight() / 2) + 768, "explorebg.bmp", GetTime());
	back2_3->SetHealth(2);
	back2_3->SetStatus(3);
	backlist.push_back(back2_3);
	CSprite* back3_3 = new CSprite((GetWidth() / 2) + 1024, (GetHeight() / 2) + 768, "explorebg.bmp", GetTime());
	back3_3->SetHealth(3);
	back3_3->SetStatus(3);
	backlist.push_back(back3_3);
}

void CMyGame::level2code()
{
	for (CSprite* back : backlist)
	{
		back->Update(GetTime());
	}
	for (CSprite* potato : lv2potatolist)
	{
		potato->Update(GetTime());
	}
	backcode();

	lv2potatospawn();

	for (CSprite* potato : lv2potatolist)
	{
		if (player.HitTest(potato))
		{
			potatoscore++;
			potato->Delete();
		}
		if (Distance(potato->GetPos(), player.GetPos()) > 1280)
		{
			potato->Delete();
		}
	}

	if (potatoscore >= 5)
	{
		lv2end();
	}

	lv2potatolist.delete_if(deleted);
}

void CMyGame::lv2end()
{
	backlist.delete_all();
	lv2potatolist.delete_all();
	level = 0;
	potatoscore = 0;
	player.SetPos(GetWidth() / 2, GetHeight() / 2);
}

void CMyGame::lv2potatospawn()
{
	if (lv2potatolist.size() < 2)
	{
		//moving left and right
		if (player.GetYVelocity() == 0)
		{
			//doing nothing
			if (player.GetXVelocity() == 0)
			{
				//no spawn
			}
			//moving right
			else if (player.GetXVelocity() > 0)
			{
				CVector spawnpos = mousetoscreen(GetWidth() + (rand() % 100 + 32), rand() % GetHeight());
				subpotatospawning(spawnpos);
			}
			//moving left
			else if (player.GetXVelocity() < 0)
			{
				CVector spawnpos = mousetoscreen(-(rand() % 100 + 32), rand() % GetHeight());
				subpotatospawning(spawnpos);
			}
		}
		//moving up and down
		else if (player.GetXVelocity() == 0)
		{
			//doing nothing
			if (player.GetYVelocity() == 0)
			{
				//no spawn
			}
			// moving up
			else if (player.GetYVelocity() > 0)
			{
				CVector spawnpos = mousetoscreen(rand() % GetWidth(), GetHeight() + (rand() % 100 + 32));
				subpotatospawning(spawnpos);
			}
			//moving down
			else if (player.GetYVelocity() < 0)
			{
				CVector spawnpos = mousetoscreen(rand() % GetWidth(), -(rand() % 100 + 32));
				subpotatospawning(spawnpos);
			}
		}
	}
}

void CMyGame::subpotatospawning(CVector spawnpoint)
{
	if (lv2potatolist.size() > 0)
	{
		for (CSprite* potatoo : lv2potatolist)
		{
			//check for colision
			if (Distance(potatoo->GetPos(), spawnpoint) > 150)
			{
				//if no collision spawn potato
				CSprite* potato = new CSprite(spawnpoint.GetX(), spawnpoint.GetY(), "potatoimg.bmp", CColor::Black(), GetTime());
				lv2potatolist.push_back(potato);
			}
		}
	}
	else
	{
		//spawn potato
		CSprite* potato = new CSprite(spawnpoint.GetX(), spawnpoint.GetY(), "potatoimg.bmp", CColor::Black(), GetTime());
		lv2potatolist.push_back(potato);
	}
}