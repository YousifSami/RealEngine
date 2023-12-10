#pragma once

class Window;
class REInput;
class RECollisionEngine;

//debug
class REAnimStateMachine;
class REGameObject;



class Game {
public:
	//get or create the game instance if there isn't one already
	static Game* GetGameInstance();

	// destroy the game instance
	static void DestroyGameInstance();

	// run the game/app loop
	void Run();

	// closes the app loop and ends the game
	void EndGame() { m_IsRunning = false; }

	//gets delta time as float
	float GetDeltaTimeF() const { return static_cast<float>(m_DeltaTime); }

	//add a game object to the game
	template<class G, typename std::enable_if<std::is_base_of<REGameObject, G>::value>::type* = nullptr>
	inline G* AddGameObject(REString ObjectName = "GameObject") {
		G* NewGameObject = new G(ObjectName, m_Window);

		if (NewGameObject == nullptr) {
			RELog("GameObject failed to create: " + ObjectName);
			return nullptr;
		}

		m_GameObjectStack.push_back(NewGameObject);

		return NewGameObject;
	}

	//remove the game object from the game objects stack
	//make sure to remove all references of the gameobject in other areas
	void RemoveGameObject(REGameObject* GameObject);

	//gets the cureent collision engine
	RECollisionEngine* GetCollision() const { return m_CollisionEngine; }

	//get the main window
	Window* GetWindow() const { return m_Window; }

	//restarts game
	void RestartGame();
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

	//time between each frame
	double m_DeltaTime;

	//stores game inputs
	REInput* m_GameInput;

	// hold all the game objects in the game
	TArray<REGameObject*> m_GameObjectStack;

	//DEBUG VAR
	REGameObject* m_Player;

	//storing a collision engine in the game
	RECollisionEngine* m_CollisionEngine;
};
