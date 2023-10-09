#include "CoreMinimal.h"
#include "Window/Window.h"
#include "SDL2/SDL.h"

Window::Window()
{
	m_Window = nullptr;
	m_Renderer = nullptr;
	m_Width = m_Height = 0;
	m_Title = "";
}

Window::~Window()
{
	m_Window = nullptr;
	m_Renderer = nullptr;
}

bool Window::CreateWindow(REString Title, int Width, int Height)
{
	//use SDL to create a window
	m_Window = SDL_CreateWindow(
		Title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		Width, Height,
		SDL_WINDOW_SHOWN
	);

	// if the window failed to create
	if (m_Window == nullptr) {
		std::cout << "SDL window Creation failed: " << SDL_GetError() << std::endl;
		return false;
	}

	// if the window was succesful store the variables
	m_Title = Title;
	m_Width = Width;
	m_Height = Height;

	// create a renderer using SDL
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC);

	// if the renderer faild to create
	if (m_Renderer == nullptr) {
		std::cout << "SDL renderer creation failed: " << SDL_GetError() << std::endl;
		Destroy();
		return false;
	}

	return true;
}

void Window::Destroy()
{
	// clean up the renderer
	if (m_Renderer != nullptr) {
		SDL_DestroyRenderer(m_Renderer);
	}

	// clean up the window
	if (m_Window != nullptr) {
		SDL_DestroyWindow(m_Window);
	}
}
