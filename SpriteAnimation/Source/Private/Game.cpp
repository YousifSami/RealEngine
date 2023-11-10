#include "CoreMinimal.h"
#include "Game.h"
#include "Window/Window.h"
#include "REInput.h" 
#include "Math/REVector2.h"
#include "GameObjects/REGameObject.h"

//debug header
#include "GameObjects/Characters/REPlayer.h"
#include "GameObjects/Characters/REEnemy.h"
#include <GameObjects/Characters/REEnemy2.h>


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
	m_GameInput = nullptr;
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

	if (!m_Window->CreateWindow("Real Engine", 1280, 720, { 50, 50 , 50 , 255})) {
		EndGame();
		return;
	}

	m_GameInput = new REInput();


	//debug add test game object
	AddGameObject<REEnemy2>()->SetPosition({ 700.0f, -150.0f });
	AddGameObject<REEnemy>()->SetPosition({ 500.0f, -150.0f });
	AddGameObject<REPlayer>();
	

	// loop through all the game objects in the game and run their begin play
	for (auto GameObject : m_GameObjectStack) {
		if (GameObject == nullptr) {
			continue;
		}

		GameObject->BeginPlay();
	}
}

void Game::ProcessInput()
{
	if (m_GameInput == nullptr) {
		RELog("No input class detected");
		return;
	}

	//process the inputs and workout what been pressed
	m_GameInput->ProcessInput();

	// loop through all the game objects in the game and run their process inputs
	for (auto GameObject : m_GameObjectStack) {
		if (GameObject == nullptr) {
			continue;
		}

		GameObject->ProcessInput(m_GameInput);
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

	//when escape button is pressed game ends
	if (m_GameInput->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
		EndGame();
	}

	// loop through all the game objects in the game and run their update
	for (auto GameObject : m_GameObjectStack) {
		if (GameObject == nullptr) {
			continue;
		}

		GameObject->Update(GetDeltaTimeF());
	}
}

void Game::Render()
{
	m_Window->Render();
}

void Game::CleanupGame()
{

	// loop through all the game objects in the game and run their destroy
	for (auto GameObject : m_GameObjectStack) {
		if (GameObject == nullptr) {
			continue;
		}

		GameObject->Destroy();
	}

	// deletes input
	delete m_GameInput;

	//destroy and deallocate the window
	if (m_Window != nullptr) {
		m_Window->Destroy();
		delete m_Window;
	}
	// quit sdl
	SDL_Quit();
}