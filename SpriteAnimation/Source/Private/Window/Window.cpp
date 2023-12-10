#include "CoreMinimal.h"
#include "Window/Window.h"
#include "Graphics/RETexture.h"
#include "Game.h"
#include "Collisions/RECollisionEngine.h"
#include "Collisions/RECollision.h"
#include "Window/REWindowMenu.h"


Window::Window()
{
	m_Window = nullptr;
	m_Renderer = nullptr;
	m_Width = m_Height = 0;
	m_Title = "";
	m_BGColour = { 35, 35, 35, 255 };
	m_WindowMenu = nullptr;
}

Window::~Window()
{
	m_Window = nullptr;
	m_Renderer = nullptr;

	delete m_WindowMenu;
	m_WindowMenu = nullptr;
}

bool Window::CreateWindow(REString Title, int Width, int Height, SDL_Color Colour)
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
	m_BGColour = Colour;

	// create a renderer using SDL
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC);

	// if the renderer faild to create
	if (m_Renderer == nullptr) {
		std::cout << "SDL renderer creation failed: " << SDL_GetError() << std::endl;
		Destroy();
		return false;
	}

	//create a window menu
	m_WindowMenu = new REWindowMenu(m_Window);
	m_WindowMenu->initialiseMenu();

	return true;
}

void Window::Render()
{
	//set the colour of the background
	SDL_SetRenderDrawColor(m_Renderer,m_BGColour.r, m_BGColour.g, m_BGColour.b, m_BGColour.a);

	// clear the previos frame content
	SDL_RenderClear(m_Renderer);

	// render the custom graphics like textures and animations
	RenderCustomGraphics();


	//present it to the screeen
	SDL_RenderPresent(m_Renderer); 
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

TSharedPtr<RETexture> Window::CreateTexture(REString PathToFile)
{
	// create share ptr instead of an object pointer
	TSharedPtr<RETexture> NewTexture = TMakeShared<RETexture>();

	//if texture fails to import, return nullptr
	if (!NewTexture->ImportTexture(m_Renderer, PathToFile)) {
		return nullptr;
	}

	//if it succeeded adds it to stack
	m_TextureStack.push_back(NewTexture);

	return NewTexture;
}

void Window::RenderCustomGraphics()
{

	//loop over each element in the array and run render function
	// itexture will represent the element of each loop
	for (auto iTexture : m_TextureStack) {
		iTexture->Render(m_Renderer);
	}

	//draw collisions that are set to debug
	for (auto Col : Game::GetGameInstance()->GetCollision()->GetCollisions()) {
		if (!Col->Debug) {
			continue;
		}

		//set the draw rect to the same value as out bounds
		SDL_FRect DrawRect;
		DrawRect.x = Col->Bounds.x;
		DrawRect.y = Col->Bounds.y;
		DrawRect.w = Col->Bounds.w;
		DrawRect.h = Col->Bounds.h;

		//this sets the colour of the box
		SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 255);
		SDL_RenderDrawRectF(m_Renderer, &DrawRect);
	}
}
