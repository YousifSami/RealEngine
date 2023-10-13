#include "CoreMinimal.h"
#include "Game.h"
#include "Window/Window.h"

//debug includes
#include "Graphics/RETexture.h"
#include "Graphics/REAnimations.h"


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
	m_DeltaTime = 0.0;
	//debug
	m_Anim = nullptr;
	m_Anim2 = nullptr;
	m_Anim3 = nullptr;
	m_Anim4 = nullptr;
	m_Anim5 = nullptr;

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
		Sprite1->SetPosition(20.0f, 100.0f);

	}

	TSharedPtr<RETexture> Sprite2 = m_Window->CreateTexture("EngineContent/Images/Letters/ERed.png");

	if (Sprite2 != nullptr) {
		Sprite2->SetPosition(120.0f, 100.0f);
	}

	TSharedPtr<RETexture> Sprite3 = m_Window->CreateTexture("EngineContent/Images/Letters/LBlue.png");

	if (Sprite3 != nullptr) {
		Sprite3->SetPosition(200.0f, 100.0f);
	}

	TSharedPtr<RETexture> Sprite4 = m_Window->CreateTexture("EngineContent/Images/Letters/LRed.png");

	if (Sprite4 != nullptr) {
		Sprite4->SetPosition(280.0f, 100.0f);
	}

	TSharedPtr<RETexture> Sprite5 = m_Window->CreateTexture("EngineContent/Images/Letters/OBlue.png");

	if (Sprite5 != nullptr) {
		Sprite5->SetPosition(365.0f, 100.0f);
	}

	TSharedPtr<RETexture> Sprite6 = m_Window->CreateTexture("EngineContent/Images/Letters/WBlue.png");

	if (Sprite6 != nullptr) {
		Sprite6->SetPosition(600.0f, 100.0f);
	}

	TSharedPtr<RETexture> Sprite7 = m_Window->CreateTexture("EngineContent/Images/Letters/ORed.png");

	if (Sprite7 != nullptr) {
		Sprite7->SetPosition(720.0f, 100.0f);
	}

	TSharedPtr<RETexture> Sprite8 = m_Window->CreateTexture("EngineContent/Images/Letters/RBlue.png");

	if (Sprite8 != nullptr) {
		Sprite8->SetPosition(830.0f, 100.0f);
	}

	TSharedPtr<RETexture> Sprite9 = m_Window->CreateTexture("EngineContent/Images/Letters/LRed.png");

	if (Sprite9 != nullptr) {
		Sprite9->SetPosition(930.0f, 100.0f);
	}

	TSharedPtr<RETexture> Sprite0 = m_Window->CreateTexture("EngineContent/Images/Letters/DBlue.png");

	if (Sprite0 != nullptr) {
		Sprite0->SetPosition(1030.0f, 100.0f);
	}

	m_Anim = new REAnimation();
	m_Anim2 = new REAnimation();
	m_Anim3 = new REAnimation();
	m_Anim4 = new REAnimation();
	m_Anim5 = new REAnimation();

	REAnimParams AnimParams;
	AnimParams.FrameCount = 50;
	AnimParams.EndFrame = 49;
	AnimParams.FrameRate = 12.0f;

	m_Anim->ImportAnimation(m_Window, "EngineContent/Images/SpriteSheets/Planet/Planet1-50f.png", AnimParams);
	m_Anim->SetScale(20.0f, 20.0f);
	m_Anim->SetPosition(600.0f, 500.0f);

	AnimParams.FrameCount = 30;
	AnimParams.EndFrame = 29;

	m_Anim2->ImportAnimation(m_Window, "EngineContent/Images/SpriteSheets/Planet/sun-30f.png", AnimParams);
	m_Anim2->SetPosition(1100.0f, 450.0f);

	AnimParams.FrameCount = 30;
	AnimParams.EndFrame = 29;

	m_Anim3->ImportAnimation(m_Window, "EngineContent/Images/SpriteSheets/Planet/moon30f.png", AnimParams);
	m_Anim3->SetPosition(470.0f, 400.0f);

	AnimParams.FrameCount = 30;
	AnimParams.EndFrame = 29;

	m_Anim4->ImportAnimation(m_Window, "EngineContent/Images/SpriteSheets/Planet/gasgiant30f.png", AnimParams);
	m_Anim4->SetPosition(10.0f, 400.0f);

	AnimParams.FrameCount = 30; 
	AnimParams.EndFrame = 29; 

	m_Anim5->ImportAnimation(m_Window, "EngineContent/Images/SpriteSheets/Planet/galaxy30f.png", AnimParams);
	m_Anim5->SetPosition(500.0f, 140.0f);
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

	m_Anim->Update(GetDeltaTimeF());
	m_Anim2->Update(GetDeltaTimeF());
	m_Anim3->Update(GetDeltaTimeF());
	m_Anim4->Update(GetDeltaTimeF());
	m_Anim5->Update(GetDeltaTimeF());


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
