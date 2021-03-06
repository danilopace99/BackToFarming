#include "stdafx.h"
#include "MyGame.h"
#include "lv2.h"
#include "Dirt.h"

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

	menu.Update(t);
	bg.Update(t);
	bgscroller.Update(t);
	for (CSprite* enemy : m_sprites)
		enemy->Update(t);

	dirtcode(&patch1);
	dirtcode(&patch2);
	dirtcode(&patch3);
	dirtcode(&patch4);
	dirtcode(&patch5);
	dirtcode(&patch6);
	dirtcode(&patch7);
	dirtcode(&patch8);
	dirtcode(&patch9);


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
		if (level != 1)
		{
			player.SetMotion(0, 400);
		}
	}
	else if (IsKeyDown(SDLK_DOWN) || IsKeyDown(SDLK_s))
	{
		if (level != 1)
		{
			player.SetMotion(0, -400);
		}
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
		carMenu.SetPosition(800, 800);
		carrots.SetPosition(750, 780);
		potatoes.SetPosition(900, 780);

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

		patch1.Draw(g);
		patch2.Draw(g);
		patch3.Draw(g);
		patch4.Draw(g);
		patch5.Draw(g);
		patch6.Draw(g);
		patch7.Draw(g);
		patch8.Draw(g);
		patch9.Draw(g);

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

	if (level == 0)
	{
		CVector center2 = mousetoscreen(850, 50);
		CSpriteRect d(center2.GetX(), center2.GetY(), 400, 200, CColor::White(), CColor::Black(), GetTime());
		d.Draw(g);
		*g << xy(center2.GetX() - 180, center2.GetY() + 70) << color(CColor::Blue()) << font(15) << "Collected carrots: " << carrotscore;
		*g << xy(center2.GetX() - 180, center2.GetY() + 50) << color(CColor::Blue()) << font(15) << "Collected potatoes: " << potatoammount;

		int farm = checkhitallfarms();
		if (farm > 0)
		{
			CVector center = CVector(player.GetX(), player.GetY() + 64);
			if (noToFarm(farm)->hasPlant())
			{
				if (noToFarm(farm)->getPlantGrowthPercent() > 1)
				{
					*g << xy(center.GetX(), center.GetY()) << color(CColor::Blue()) << font(30) << "Press E to harvest";
				}
				else
				{
					*g << xy(center.GetX(), center.GetY()) << color(CColor::Blue()) << font(30) << "This plant is not yet ready for harvest";
				}
			}

			if (!noToFarm(farm)->hasPlant())
			{
				if (carrotscore <= 0 && potatoammount <= 0)
				{
					*g << xy(center.GetX(), center.GetY()) << color(CColor::Blue()) << font(30) << "You dont have any seeds";
				}
				else if (carrotscore > 0 && potatoammount <= 0)
				{
					*g << xy(center.GetX(), center.GetY()) << color(CColor::Blue()) << font(30) << "Press E to plant carrots";
				}
				else if (carrotscore <= 0 && potatoammount > 0)
				{
					*g << xy(center.GetX(), center.GetY()) << color(CColor::Blue()) << font(30) << "Press F to plant potatoes";
				}
				else if (carrotscore > 0 && potatoammount > 0)
				{
					*g << xy(center.GetX(), center.GetY()+20) << color(CColor::Blue()) << font(30) << "Press E to plant carrots";
					*g << xy(center.GetX(), center.GetY()) << color(CColor::Blue()) << font(30) << "Press F to plant potatoes";
				}
			}
		}
	}

	if (level == 2)
	{
		CVector center = mousetoscreen(GetWidth() * 0.1, GetHeight() * 0.9);
		*g << xy(center.GetX(), center.GetY()) << color(CColor::Blue()) << font(30) << "Collected potates: " << potatoscore;
	}

	if (IsMenuMode())
	{
		menu.Draw(g);
	}
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
	menu.LoadImage("menu.png");
	menu.SetImage("menu.png");
	menu.SetPosition(GetWidth() / 2, GetHeight() / 2);

	//player setup
	player.LoadImage("pg.png");
	player.SetImage("pg.png");
	player.SetPosition(GetWidth() / 2, GetHeight() / 2);
	player.AddImage("spritesheet_17.png", "flying", 3, 1, 0, 0, 2, 0, CColor::Black());
	player.SetAnimation("flying");

	//background setup
	bg.LoadImage("bg.jpg");
	bg.SetImage("bg.jpg");
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

	carrotscore = 0;
	potatoscore = 0;
	potatoammount = 0;

	int space = 128;
	int x1 = 340;
	int x2 = x1 + space;
	int x3 = x1 + (space * 2);
	int y1 = 500;
	int y2 = y1 - space;
	int y3 = y1 - (space * 2);

	patch1.SetPos(x1, y1);
	patch1.setUpDirt();
	patch2.SetPos(x2, y1);
	patch2.setUpDirt();
	patch3.SetPos(x3, y1);
	patch3.setUpDirt();

	patch4.SetPos(x1, y2);
	patch4.setUpDirt();
	patch5.SetPos(x2, y2);
	patch5.setUpDirt();
	patch6.SetPos(x3, y2);
	patch6.setUpDirt();

	patch7.SetPos(x1, y3);
	patch7.setUpDirt();
	patch8.SetPos(x2, y3);
	patch8.setUpDirt();
	patch9.SetPos(x3, y3);
	patch9.setUpDirt();
}

// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen
void CMyGame::OnDisplayMenu()
{
	BGM.Play("back to farming.wav");
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
	BGM.Play("Liyue.wav");
	SFX.Play("Portal.wav");
}

void CMyGame::SetupLevel2()
{
	createbacks();
	potatoscore = 0;
	player.SetPos(GetWidth() / 2, GetHeight() / 2);
	BGM.Play("Liyue.wav");
	SFX.Play("Portal.wav");
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

	if (IsMenuMode())
	{
		if (sym == SDLK_F5)
		{
			StartGame();	// exits the menu mode and starts the game mode
		}
	}

	if (level == 0)
	{
		if (player.HitTest(&console) && sym == SDLK_t)
		{
			SFX.Play("wadr.wav");
			patch1.waterPlant();
			patch2.waterPlant();
			patch3.waterPlant();
			patch4.waterPlant();
			patch5.waterPlant();
			patch6.waterPlant();
			patch7.waterPlant();
			patch8.waterPlant();
			patch9.waterPlant();
		}

		int farm = checkhitallfarms();
		if (farm > 0)
		{
			if (sym == SDLK_e)
			{
				dirtinteract(noToFarm(farm), 1);
			}
			if (sym == SDLK_f)
			{
				dirtinteract(noToFarm(farm), 2);
			}
		}
	}
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
		player.SetPosition(533, GetHeight() / 2);
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
		carrotscore++;
		level = 0;
		SFX.Play("Portal.wav");
	}

	bgscroller.SetMotion(0, -200);

	// enemy spawn from the right side   
	if (rand() % 70 == 0) {
		CSprite* newSprite = new CSprite(float((100) + rand() % 900), 900, "obstacle.bmp", CColor::White(), GetTime());
		newSprite->SetDirection(0, -100.f);
		newSprite->SetSpeed(200);
		m_sprites.push_back(newSprite);
	}

	for (CSprite* enemy : m_sprites)
	{
		// collision with player
		if (enemy->HitTest(&player))
		{
			bgscroller.SetPosition(540, 4830);
			player.SetPosition(GetWidth() / 2, GetHeight() / 2);
			level = 0;
			enemy->Delete();
		}
	}

	for (CSprite* enemy : m_sprites)
	{
		if (enemy->GetY() < -200 || enemy->GetX() < 0)
		{
			enemy->Delete();
		}
	}
}

void CMyGame::dirtcode(CDirt* patch)
{
	patch->Update(GetTime());
	patch->eachframe();
}

int CMyGame::checkhitallfarms()
{
	int hit = 0;
	if (player.HitTest(&patch1))
	{
		hit = 1;
	}
	if (player.HitTest(&patch2))
	{
		hit = 2;
	}
	if (player.HitTest(&patch3))
	{
		hit = 3;
	}
	if (player.HitTest(&patch4))
	{
		hit = 4;
	}
	if (player.HitTest(&patch5))
	{
		hit = 5;
	}
	if (player.HitTest(&patch6))
	{
		hit = 6;
	}
	if (player.HitTest(&patch7))
	{
		hit = 7;
	}
	if (player.HitTest(&patch8))
	{
		hit = 8;
	}
	if (player.HitTest(&patch9))
	{
		hit = 9;
	}
	return hit;
}

void CMyGame::dirtinteract(CDirt* patch, int type)
{
	if (type == 1)
	{
		if (patch->hasPlant())
		{
			if (patch->getPlantGrowthPercent() > 1)
			{
				if (patch->harvestPlant() == 1)
				{
					carrotscore += 3;
					SFX.Play("planting.wav");
				}
				else if (patch->harvestPlant() == 2)
				{
					potatoammount += 3;
					SFX.Play("planting.wav");
				}
			}
		}
	}

	if (!patch->hasPlant())
	{
		if (type == 1)
		{
			if (carrotscore > 0)
			{
				carrotscore--;
				patch->plantPlant("carrots");
			}
		}
		if (type == 2)
		{
			if (potatoammount > 0)
			{
				potatoammount--;
				patch->plantPlant("potatoes");
			}
		}
	}
}

CDirt* CMyGame::noToFarm(int no)
{
	if (no == 1)
	{
		return &patch1;
	}
	else if (no == 2)
	{
		return &patch2;
	}
	else if (no == 3)
	{
		return &patch3;
	}
	else if (no == 4)
	{
		return &patch4;
	}
	else if (no == 5)
	{
		return &patch5;
	}
	else if (no == 6)
	{
		return &patch6;
	}
	else if (no == 7)
	{
		return &patch7;
	}
	else if (no == 8)
	{
		return &patch8;
	}
	else if (no == 9)
	{
		return &patch9;
	}
}