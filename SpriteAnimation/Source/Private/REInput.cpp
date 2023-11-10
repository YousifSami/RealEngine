#include "CoreMinimal.h"
#include "REInput.h"

#include "Game.h"

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
