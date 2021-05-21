#pragma once
#include "Dirt.h"

class CMyGame : public CGame
{
	// Define sprites and other instance variables here
	CSprite bg;
	CSprite lv1sky;
	CSprite bgscroller;
	CSprite player;
	CSprite doctor;
	CSprite console;

	CSprite car;
	CSprite carMenu;

	CSprite carrots;
	CSprite potatoes;
	CSprite tomatoes;

	CSpriteList m_sprites;	// All other sprites

	//sounds
	CSoundPlayer BGM;
	CSoundPlayer SFX;

	//dirt stuff
	CDirt patch1;
	CDirt patch2;
	CDirt patch3;
	CDirt patch4;
	CDirt patch5;
	CDirt patch6;
	CDirt patch7;
	CDirt patch8;
	CDirt patch9;
	
	void dirtcode(CDirt* patch);
	void dirtinteract(CDirt* patch);
	int checkhitallfarms();
	CDirt* noToFarm(int no);

	//functions
	CVector mousetoscreen(float x, float y);
	
	void level1code();


	//lv1 stuff
	int carrotscore;

	int potatoammount;
	//lv2 stuff
	int potatoscore;

	CSpriteList backlist; //lv2 backgrounds
	CSpriteList lv2potatolist;

	void level2code();
	void backcode();
	void createbacks();
	void lv2end();
	void lv2potatospawn();
	void subpotatospawning(CVector spawnpoint);

public:
	CMyGame(void);
	~CMyGame(void);

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// ---- variables ----
	int level;

	// ---- member functions ----
	void PlayerControl();
	void DoctorControl();
	void CarControl();
	void ConsoleControl();

	void SetupLevel1();
	void SetupLevel2();
	void SetupLevel3();

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnStartLevel(Sint16 nLevel);
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
