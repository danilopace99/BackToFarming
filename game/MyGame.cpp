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

	player.Update(t);
	bg.Update(t);
	bgscroller.Update(t);

	if (level == 1) { SetupLevel1(); bgscroller.SetMotion(0, -100); }
	if (level == 2) SetupLevel2();
	if (level == 3) SetupLevel3();

	PlayerControl();

	CarControl();
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

		carMenu.Draw(g);
		carrots.Draw(g);
		potatoes.Draw(g);
		tomatoes.Draw(g);
	}

	if (level == 1)
	{
		SetupLevel1();
		// reset background image (which is of size 1080x10000)
		if (bgscroller.GetY() < 0)
			bgscroller.SetY(GetWidth() / 2);
		bgscroller.Draw(g);

	}
	if (level == 2) SetupLevel2();
	if (level == 3) SetupLevel3();

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

	//car setup
	car.LoadImage("car.png");
	car.SetImage("car.png");
	car.SetPosition(800, GetHeight() / 4);

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
	}
	if (potatoes.HitTest(mousetoscreen(x, y)))
	{
		level = 2;
	}
	if (tomatoes.HitTest(mousetoscreen(x, y)))
	{
		level = 3;
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