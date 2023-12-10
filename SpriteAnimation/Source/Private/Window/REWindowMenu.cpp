#include "CoreMinimal.h"
#include "Window/REWindowMenu.h"

#include "SDL2/SDL_syswm.h"
#include <Windows.h>
#include "../../resource.h"
#include "Game.h"

REWindowMenu::REWindowMenu(SDL_Window* Window)
{
	m_Window = Window;
	m_WindowInfo = new SDL_SysWMinfo();

	//update the window info with the current SDL version
	SDL_VERSION(&m_WindowInfo->version);

	//after we have the sdl version SDL will allow us fill in the rest of the window info
	SDL_GetWindowWMInfo(m_Window, m_WindowInfo);
}

REWindowMenu::~REWindowMenu()
{
	m_Window = nullptr;

	delete m_WindowInfo;
	m_WindowInfo = nullptr;
}

void REWindowMenu::initialiseMenu()
{
	// gets/converst the sdl window info into the system window
	HWND SysWindow = m_WindowInfo->info.win.window;

	//we need to get the recource menu that we created in visual studio
	//GetModuleHandle(0) get the current instance of the window that we're actively in
	HINSTANCE WindowInstance = GetModuleHandle(0);
	//MAKEINTRECOURCE will convert the menu into a LPCWSTR which is  the index for the menu
	LPCWSTR MenuIndex = MAKEINTRESOURCE(IDR_MENU1);
	//load the menu and save it to a variable
	HMENU SysMenu = LoadMenu(WindowInstance, MenuIndex);

	//adds the menu to the window
	if (!SetMenu(SysWindow,SysMenu)) {
		RELog("Menu Could not be added to window");
	}

	//add an event listener to sdl to listen out for win32 menu buttons
	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
}

void REWindowMenu::RestartGame()
{
	RELog("Restart Game");
}

void REWindowMenu::ExitApp()
{
	Game::GetGameInstance()->EndGame();
}

void REWindowMenu::ActivatePopup(REString Title, REString Message)
{
	//simple popup
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, Title.c_str(), Message.c_str(), m_Window);
}
