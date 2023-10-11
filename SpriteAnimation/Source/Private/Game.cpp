#include "CoreMinimal.h"
#include "Game.h"
#include "Window/Window.h"


Game* Game::GetGameInstance()
{
	// a static variable in a funtction can only run once
	//thread safe
	static Game* GameInstance = new Game();

	return GameInstance;
}

void Game::DestroyGameInstance()
{
	// deallocate the game from memory
	delete GetGameInstance();
}

void Game::Run()
{
	std::cout << "Run Game." << std::endl;

	m_IsRunning = Initialise();

	// if initialise was succesful
	if (m_IsRunning) {
		// run the start function
		Start();

		// run the game loop
		while (m_IsRunning) {
			ProcessInput();

			Update();

			Render();
		}
	}

	CleanupGame();
}

Game::Game()
{
	std::cout << "Create Game." << std::endl;
	m_IsRunning = true; 
	m_Window = nullptr;
}

Game::~Game()
{
	std::cout << "Destroy Game." << std::endl;
}

bool Game::Initialise()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL failed to initialise: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Game::Start()
{
	m_Window = new Window();

	if (!m_Window->CreateWindow("Real Engine", 1280, 720)) {
		EndGame();
	}
}

void Game::ProcessInput()
{
	// stoere the inputs pressed in the frame
	SDL_Event Event; 

	// find the inputs pressed in the frame and update the event variable
	// an event listener
	while (SDL_PollEvent(&Event)) {
		//this will listen to different event types
		switch (Event.type) {
		case SDL_QUIT : // when the close button is clicked
			EndGame();
			break;
			case SDL_KEYDOWN :// when the escape button is pressed3

				if (Event.key.keysym.sym == SDLK_ESCAPE) {
					EndGame();
				}
				break;
		}
	}
}

void Game::Update()
{
}

void Game::Render()
{
	m_Window->Render();
}

void Game::CleanupGame()
{
	//destroy and deallocate the window
	if (m_Window != nullptr) {
		m_Window->Destroy();
		delete m_Window;
	}
	// quit sdl
	SDL_Quit();
}
