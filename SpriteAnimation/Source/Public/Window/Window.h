#pragma once

// forward declaration
struct SDL_Window;
struct SDL_Renderer;

class Window {
public:
	Window();
	~Window();

	// create a window
	// @param 1 - the title of the window
	// @param 2 - width of the window
	// @param 3 - height of the window
	bool CreateWindow(REString Title, int Width, int Height);

	// deallocate memory that the window holds
	void Destroy();

private:
	// store the SDL window
	SDL_Window* m_Window;
	// store the SDL renderer
	SDL_Renderer* m_Renderer;
	// store the width and height
	int m_Width, m_Height;
	// store the tittle of the window
	REString m_Title;
};
