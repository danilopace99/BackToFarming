#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void)
	// to initialise more sprites here use a comma-separated list
{
	// TODO: add initialisation here
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	Uint32 t = GetTime();

	// TODO: add the game update code here

	
	bg.Update(t);
	bgscroller.Update(t);


	if (level == 1) 
	{ 
		level1code();
	}
	if (level == 2)
	{
		level2code();
	}
	if (level == 3)
	{

	}

	PlayerControl();

	if (level == 0)
	{
		CarControl();
	}

	m_sprites.delete_if(deleted);
}

void CMyGame::PlayerControl()
{
	//player's movement
	if (IsKeyDown(SDLK_LEFT) || IsKeyDown(SDLK_a))
	{
		player.SetMotion(-400, 0);
	}
	else if (IsKeyDown(SDLK_RIGHT) || IsKeyDown(SDLK_d))
	{ 
		player.SetMotion(400, 0); 
	}
	else if (IsKeyDown(SDLK_UP) || IsKeyDown(SDLK_w))
	{
		player.SetMotion(0, 400);
	}
	else if (IsKeyDown(SDLK_DOWN) || IsKeyDown(SDLK_s))
	{
		player.SetMotion(0, -400);
	}
	else
	{
		player.SetMotion(0, 0);
	}

	if (level == 0 || level == 1)
	{
		//player collisions with car, doctor, console
		CSpriteRect a(800, 600, 30, 30, CColor::Black(), CColor::White(), GetTime());
		CSpriteRect b(800, GetHeight() / 4, 30, 30, CColor::Black(), CColor::White(), GetTime());
		CSpriteRect c(GetWidth() / 4, 600, 30, 30, CColor::Black(), CColor::White(), GetTime());
		CVector pos = player.GetPos();
		player.Update(GetTime());
		if (player.GetY() < -120 || player.GetY() > 900 || player.GetX() < 0 || player.GetX() > 1080)
		{
			player.SetPosition(pos);
		}
		if (level == 0)
		{
			if (player.HitTest(&a) || player.HitTest(&b) || player.HitTest(&c))
				player.SetPosition(pos);
		}
	}

	if (level == 2)
	{
		player.Update(GetTime());
	}
}

void CMyGame::CarControl()
{
	if (player.HitTest(&car) && IsKeyDown(SDLK_t))
	{
		carMenu.SetPosition(800, GetHeight() / 2);
		carrots.SetPosition(650, 320);
		potatoes.SetPosition(800, 320);
		tomatoes.SetPosition(950, 320);

	}
	if (!player.HitTest(&car))
	{
		carMenu.SetPosition(7000, 7000);
		carrots.SetPosition(7000, 7000);
		potatoes.SetPosition(7000, 7000);
		tomatoes.SetPosition(7000, 7000);
	}
}

void CMyGame::ConsoleControl()
{
	if (player.HitTest(&console) && IsKeyDown(SDLK_t))
	{
		//water plants
	}
}
void CMyGame::DoctorControl()
{
	if (player.HitTest(&doctor) && IsKeyDown(SDLK_t))
	{
		//speak with doctor
	}
}

void CMyGame::OnDraw(CGraphics* g)
{
	// TODO: add drawing code here
	
	if (level == 0 || level == 1)
	{
		//scrolling to the sides code
		if (player.GetX() > 10 && player.GetX() < (GetWidth() - 10))
		{
			g->SetScrollPos((GetWidth() / 2) - player.GetX(), (GetHeight() / 2) - player.GetY());
		}
		else if (player.GetX() < 10)
		{
			g->SetScrollPos((GetWidth() / 2) - 10, (GetHeight() / 2) - player.GetY());
		}
		else if (player.GetX() > (GetWidth() - 10))
		{
			g->SetScrollPos((GetWidth() / 2) - (GetWidth() - 10), (GetHeight() / 2) - player.GetY());
		}
	}

	if (level == 2)
	{
		g->SetScrollPos((GetWidth() / 2) - player.GetX(), (GetHeight() / 2) - player.GetY());
	}

	if (level == 0)
	{
		bg.Draw(g);

		car.Draw(g);

		doctor.Draw(g);
		console.Draw(g);

		carMenu.Draw(g);
		carrots.Draw(g);
		potatoes.Draw(g);
		tomatoes.Draw(g);
	}

	if (level == 1)
	{
		bgscroller.Draw(g);
		for (CSprite* enemy : m_sprites) enemy->Draw(g);
	}
	if (level == 2)
	{
		for (CSprite* back : backlist)
		{
			back->Draw(g);
		}
		for (CSprite* potato : lv2potatolist)
		{
			potato->Draw(g);
		}
	}
	if (level == 3)
	{

	}

	player.Draw(g);

	if (level == 2)
	{
		CVector center = mousetoscreen(GetWidth() * 0.1, GetHeight() * 0.9);
		*g << xy(center.GetX(), center.GetY()) << color(CColor::Blue()) << font(30) << "Collected potates: " << potatoscore;
	}
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
	//player setup
	player.LoadImage("pg.png");
	player.SetImage("pg.png");
	player.SetPosition(GetWidth() / 2, GetHeight() / 2);

	//background setup
	bg.LoadImage("bg.png");
	bg.SetImage("bg.png");
	bg.SetPosition(GetWidth() / 2, GetHeight() / 2);

	//setup
	car.LoadImage("car.png");
	car.SetImage("car.png");
	car.SetPosition(800, 600);

	doctor.LoadImage("doc.png");
	doctor.SetImage("doc.png");
	doctor.SetPosition(800, GetHeight() / 4);
	
	console.LoadImage("console.png");
	console.SetImage("console.png");
	console.SetPosition(GetWidth() / 4, 600);

	

	//travel menu
	carMenu.LoadImage("carMenu.png");
	carMenu.SetImage("carMenu.png");

	carrots.LoadImage("carrots.png");
	carrots.SetImage("carrots.png");

	potatoes.LoadImage("potatoes.png");
	potatoes.SetImage("potatoes.png");

	tomatoes.LoadImage("tomatoes.png");
	tomatoes.SetImage("tomatoes.png");

	bgscroller.LoadImage("bg1.png");
	bgscroller.SetImage("bg1.png");


	potatoscore = 0;
}

// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen
void CMyGame::OnDisplayMenu()
{
	StartGame();	// exits the menu mode and starts the game mode
}

// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame()
{
	level = 0;

	// Clean up first
	for (CSprite* pSprite : m_sprites)
		delete pSprite;
	m_sprites.clear();


	player.SetPosition(GetWidth()/2, GetHeight()/2);

	// background is of size 1080x10000
	bgscroller.SetPosition(540, 4830);
	bgscroller.SetMotion(0, 0);
}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{
}

// called at the beginning of level
void CMyGame::SetupLevel1()
{
}

void CMyGame::SetupLevel2()
{
	createbacks();
	potatoscore = 0;
	player.SetPos(GetWidth() / 2, GetHeight() / 2);
}

void CMyGame::SetupLevel3()
{

}

// called when the game is over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	if (carrots.HitTest(mousetoscreen(x, y)))
	{
		player.SetPosition(GetWidth() / 2, GetHeight() / 2);
		level = 1;
		SetupLevel1();
	}
	if (potatoes.HitTest(mousetoscreen(x, y)))
	{
		level = 2;
		SetupLevel2();
	}
	if (tomatoes.HitTest(mousetoscreen(x, y)))
	{
		level = 3;
		SetupLevel3();
	}
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}

////////////////////////////////////////////
//game functions

CVector CMyGame::mousetoscreen(float x, float y)
{
	//find the mouse pos based on the screen movement
	CVector mousepos = CVector(x, y);
	CVector cornerscreen = CVector(player.GetX() - (GetWidth() / 2), player.GetY() - (GetHeight() / 2));
	mousepos = cornerscreen + mousepos;
	return mousepos;
}

void CMyGame::level1code()
{
	if (bgscroller.GetY() < -4000)
	{
		for (CSprite* enemy : m_sprites)
		{
			enemy->Delete();
		}
		bgscroller.SetPosition(540, 4830);
		player.SetPosition(GetWidth() / 2, GetHeight() / 2);
		level = 0;
	}

	bgscroller.SetMotion(0, -100);

	// enemy spawn from the right side   
	if (rand() % 80 == 0) {
		CSprite* newSprite = new CSprite(float(rand() % 1080), 768, "obstacle.png", CColor::White(), GetTime());
		newSprite->SetDirection(0, -100.f);
		newSprite->SetSpeed(75);
		m_sprites.push_back(newSprite);
	}

	for (CSprite* enemy : m_sprites)
	{
		// collision with player
		if (enemy->HitTest(&player)) {
			enemy->Delete();
		}
	}

	for (CSprite* enemy : m_sprites)
	{
		if (enemy->GetY() < 0 || enemy->GetX() < 0)
		{
			enemy->Delete();
		}
	}
}

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