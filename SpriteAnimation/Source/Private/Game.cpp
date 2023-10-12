#include "CoreMinimal.h"
#include "Game.h"
#include "Window/Window.h"

//debug includes
#include "Graphics/RETexture.h"


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
		return;
	}

	TSharedPtr<RETexture> Sprite1 = m_Window->CreateTexture("EngineContent/Images/Letters/HBlue.png");
	
	if (Sprite1 != nullptr) {
		Sprite1->m_ScreenRect.x = 20;
		Sprite1->m_ScreenRect.y = 100;
	}

	TSharedPtr<RETexture> Sprite2 = m_Window->CreateTexture("EngineContent/Images/Letters/ERed.png");

	if (Sprite2 != nullptr) {
		Sprite2->m_ScreenRect.x = 120;
		Sprite2->m_ScreenRect.y = 100;
	}

	TSharedPtr<RETexture> Sprite3 = m_Window->CreateTexture("EngineContent/Images/Letters/LBlue.png");

	if (Sprite3 != nullptr) {
		Sprite3->m_ScreenRect.x = 200;
		Sprite3->m_ScreenRect.y = 100;
	}

	TSharedPtr<RETexture> Sprite4 = m_Window->CreateTexture("EngineContent/Images/Letters/LRed.png");

	if (Sprite4 != nullptr) {
		Sprite4->m_ScreenRect.x = 280;
		Sprite4->m_ScreenRect.y = 100;
	}

	TSharedPtr<RETexture> Sprite5 = m_Window->CreateTexture("EngineContent/Images/Letters/OBlue.png");

	if (Sprite5 != nullptr) {
		Sprite5->m_ScreenRect.x = 365;
		Sprite5->m_ScreenRect.y = 100;
	}

	TSharedPtr<RETexture> Sprite6 = m_Window->CreateTexture("EngineContent/Images/Letters/WBlue.png");

	if (Sprite6 != nullptr) {
		Sprite6->m_ScreenRect.x = 600;
		Sprite6->m_ScreenRect.y = 100;
	}

	TSharedPtr<RETexture> Sprite7 = m_Window->CreateTexture("EngineContent/Images/Letters/ORed.png");

	if (Sprite7 != nullptr) {
		Sprite7->m_ScreenRect.x = 720;
		Sprite7->m_ScreenRect.y = 100;
	}

	TSharedPtr<RETexture> Sprite8 = m_Window->CreateTexture("EngineContent/Images/Letters/RBlue.png");

	if (Sprite8 != nullptr) {
		Sprite8->m_ScreenRect.x = 830;
		Sprite8->m_ScreenRect.y = 100;
	}

	TSharedPtr<RETexture> Sprite9 = m_Window->CreateTexture("EngineContent/Images/Letters/LRed.png");

	if (Sprite9 != nullptr) {
		Sprite9->m_ScreenRect.x = 930;
		Sprite9->m_ScreenRect.y = 100;
	}

	TSharedPtr<RETexture> Sprite0 = m_Window->CreateTexture("EngineContent/Images/Letters/DBlue.png");

	if (Sprite0 != nullptr) {
		Sprite0->m_ScreenRect.x = 1030;
		Sprite0->m_ScreenRect.y = 100;
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
	//delta time must be calculated first
	static double LastTickTime = 0.0;
	//gets the amount of time that has passed since the game started from SDL_GetTicks
	double CurrentTickTime = static_cast<double>(SDL_GetTicks64());
	// remove the last tick time from the current tick time to get the delta time
	//simplifies the number to seconds by dividing by 1000
	m_DeltaTime = (CurrentTickTime - LastTickTime) / 1000.0;
	//update the last tick time
	LastTickTime = CurrentTickTime;


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
