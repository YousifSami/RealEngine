#pragma once

// forward declaration
class RETexture;
class REText;
class REWindowMenu;

class Window {
public:
	Window();
	~Window();

	// create a window
	// @param 1 - the title of the window
	// @param 2 - width of the window
	// @param 3 - height of the window
	bool CreateWindow(REString Title, int Width, int Height, SDL_Color Colour = {35, 35, 35, 255});

	// render graphics to the window
	void Render();

	// deallocate memory that the window holds
	void Destroy();

	// create texture and add texture stack for rendering
	TSharedPtr<RETexture> CreateTexture(REString PathToFile);

	//get width of the window
	int GetWidth() const { return m_Width; }

	//get height of the window
	int GetHeight() const { return m_Height; }

	//gets  the win32 menu attached to this window
	REWindowMenu* GetWindowMenu() const { return m_WindowMenu; }

protected:
	//render custom graphics for the game engine
	virtual void RenderCustomGraphics();

private:
	// store the SDL window
	SDL_Window* m_Window;   
	// store the SDL renderer
	SDL_Renderer* m_Renderer;
	// store the width and height
	int m_Width, m_Height;
	// store the tittle of the window
	REString m_Title;
	// colour of the background
	SDL_Color m_BGColour;
	// window texture stack
	TSharedArray<RETexture> m_TextureStack;
	//window menu for window
	REWindowMenu* m_WindowMenu;
};
