#include "CoreMinimal.h"
#include "REInput.h"

#include "Game.h"
#include "Window/REWindowMenu.h"
#include "Window/Window.h"
#include "SDL2/SDL_syswm.h"
#include "../../resource.h"

REInput::REInput()
{
	m_KeyboardState = nullptr;
}

REInput::~REInput()
{
	m_KeyboardState = nullptr;
}

void REInput::ProcessInput()
{
	// stoere the inputs pressed in the frame
	SDL_Event Event;

	// find the inputs pressed in the frame and update the event variable
	// an event listener
	while (SDL_PollEvent(&Event)) {
		//this will listen to different event types
		switch (Event.type) {
		case SDL_MOUSEBUTTONDOWN : // detects mouse button press
			OnMouseButtonChanged(Event.button, true);
			break;
		case SDL_MOUSEBUTTONUP: // detects mouse button release
			OnMouseButtonChanged(Event.button, false);
			break;
		case SDL_KEYDOWN: //detect if key is pressed down or released
		case SDL_KEYUP:
			m_KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_QUIT: // when the close button is clicked
			Game::GetGameInstance()->EndGame();
			break;

		case SDL_SYSWMEVENT:
			HandleWMEvents(Event);
			break;
		}
	}
}

bool REInput::IsKeyDown(SDL_Scancode key)
{
	if (m_KeyboardState == nullptr) {
		return false;
	}

	return m_KeyboardState[key];
}

bool REInput::IsMouseButtonDown(EMouseButtons Button)
{
	return m_MouseStates[Button];
}

void REInput::OnMouseButtonChanged(SDL_MouseButtonEvent Event, bool IsPressed)
{
	switch (Event.button) {
	case SDL_BUTTON_LEFT :
		m_MouseStates[MB_LEFT] = IsPressed;
		break;
	case SDL_BUTTON_RIGHT : 
		m_MouseStates[MB_RIGHT] = IsPressed;
		break;
	case SDL_BUTTON_MIDDLE :
		m_MouseStates[MB_MIDDLE] = IsPressed;
		break;
	}
}

void REInput::HandleWMEvents(SDL_Event Event)
{
	REString Title;
	REString Message;

	switch (Event.syswm.msg->msg.win.wParam)
	{
	case ID_FILE_RESTART :
		Game::GetGameInstance()->GetWindow()->GetWindowMenu()->RestartGame();
		break;
	case ID_FILE_EXIT:
		Game::GetGameInstance()->GetWindow()->GetWindowMenu()->ExitApp();
		break;
	case ID_GAMECONTROLS:
		 Title = REString("Controls");
		 Message = REString("A to move left \n D to move right \n Left mouse button to shoot");
		Game::GetGameInstance()->GetWindow()->GetWindowMenu()->ActivatePopup(Title, Message);
		break;
	case ID_HELP_ABOUTREALENGINE:
		Title = REString("About the Engine");
		Message = REString(" REngine is an SDL2-based C++ 2D game engine created by Yousif in 2023");
		Game::GetGameInstance()->GetWindow()->GetWindowMenu()->ActivatePopup(Title, Message);
		break;
	default:
		break;
	}

}
