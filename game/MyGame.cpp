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

	}
	if (level == 3)
	{

	}

	PlayerControl();

	CarControl();

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

	//player collisions with car, doctor, console
	CSpriteRect a(800, 600, 40, 40, CColor::Black(), CColor::White(), GetTime());
	CSpriteRect b(800, GetHeight() / 4, 40, 40, CColor::Black(), CColor::White(), GetTime());
	CSpriteRect c(GetWidth() / 4, 600, 40, 40, CColor::Black(), CColor::White(), GetTime());
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
	
	//scrolling to the sides code
	if (player.GetX() > 10 && player.GetX() < (GetWidth()-10))
	{
		g->SetScrollPos((GetWidth()/2)-player.GetX(), (GetHeight()/2)-player.GetY());
	}
	else if (player.GetX() < 10)
	{
		g->SetScrollPos((GetWidth() / 2) - 10, (GetHeight() / 2) - player.GetY());
	}
	else if (player.GetX() > (GetWidth() - 10))
	{
		g->SetScrollPos((GetWidth() / 2) - (GetWidth() - 10), (GetHeight() / 2) - player.GetY());
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

	}
	if (level == 3)
	{

	}

	player.Draw(g);
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
	for (CSprite* enemy : m_sprites)
	{
		if (bgscroller.GetY() < -4000)
		{
			enemy->Delete();
			bgscroller.SetPosition(540, 4830);
			player.SetPosition(GetWidth() / 2, GetHeight() / 2);
			level = 0;
		}
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