#pragma once

class REGameObject;
class  REInput;

class REComponent{
public:
	REComponent(REGameObject* Owner) : m_Owner(Owner) {}
	~REComponent() = default;

	// run whgen the component first spawns into the game
	virtual void BeginPlay() {}

	//detect game input
	virtual void ProcessInput(REInput* GameInput) {}

	// run component  logic
	virtual void Update(float DeltaTime) {}

	//destroy the component 
	void Destroy();

	//returns the game object owner of the component
	REGameObject* GetOwner() const { return m_Owner; }

protected:
	//run on component destroy
	virtual void OnDestroy() {}

private:
	// the gameobject owner of the component
	REGameObject* m_Owner;

};
	