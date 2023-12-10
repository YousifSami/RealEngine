#pragma once

struct SDL_SysWMinfo;

class REWindowMenu
{
public:
	REWindowMenu(SDL_Window* Window);
	~REWindowMenu();

	//create add the Win32 menu to the sdl window
	void initialiseMenu();

	//restart the game
	void RestartGame();

	//exit the whole application
	void ExitApp();

	//shows a simple dialog box with title and message
	void ActivatePopup(REString Title, REString Message);


private:
	//store the owner window that this will be attached to
	SDL_Window* m_Window;

	//stores the info for a windows menu to convert to sdl
	SDL_SysWMinfo* m_WindowInfo;
};

