#include "stdafx.h"
#include "MyGame.h"

CMyGame game;
CGameApp app;

int main(int argc, char* argv[])
{
	//app.DebugMemoryLeaks();
	app.OpenWindow(1080, 768, "Vibe Studios!");
	//app.OpenFullScreen(800, 600, 24);
	//app.OpenConsole();
	app.SetClearColor(CColor::Black());
	app.Run(&game);
	return(0);
}
