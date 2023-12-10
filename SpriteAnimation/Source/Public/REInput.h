#pragma once

enum EMouseButtons : REUint8 {
	MB_LEFT = 0,
	MB_RIGHT,
	MB_MIDDLE
};

class REInput {
public:
	REInput();
	~REInput();

	//proccess input of each frame
	void ProcessInput();

	//detects key presses and for release it detects if false
	bool IsKeyDown(SDL_Scancode key);
	
	//detects when mouse buttons is down, for release it detects if false
	bool IsMouseButtonDown(EMouseButtons Button);

private:
	//listen for mouse buttons changing
	void OnMouseButtonChanged(SDL_MouseButtonEvent Event, bool IsPressed);

	//listen and handle any win32 menu events
	void HandleWMEvents(SDL_Event Event);

private:

	//stores state of each button on keyboard
	const REUint8* m_KeyboardState;

	//stores state of 3 main mouse buttons 
	bool m_MouseStates[3] = { false };
};