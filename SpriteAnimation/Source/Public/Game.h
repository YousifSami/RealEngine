#pragma once

class Window;

class Game {
public:
	//get or create the game instance if there isn't one already
	static Game* GetGameInstance();

	// destroy the game instance
	static void DestroyGameInstance();

	// run the game/app loop
	void Run();

	// closes the app loop and ends the game
	inline void EndGame() { m_IsRunning = false; }

private:
	//runs when the class is instantiated
	// new game()
	Game();
	// runs when the class is deleted from memory
	// delete game()
	~Game();

	// initialise all libraries and dependencies
	bool Initialise();

	// runs once when game start
	// runs after init
	void Start();


	//process any user input - first function in loop
	void ProcessInput();

	// update logic of the game based on input and checks - Second in the loop
	void Update();

	// render graphics to the screen - third in the loop
	void Render();

	// clean up the game when it's ended
	// deallocating memory
	void CleanupGame();

private:
	// game loop flag
	bool m_IsRunning;

	// store the window
	Window* m_Window;
};
