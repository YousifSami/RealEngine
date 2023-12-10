#include "CoreMinimal.h"
#include "GameObjects/REGameObject.h"
#include "GameObjects/Components/REComponent.h"
#include "Game.h"


REGameObject::REGameObject(REString DefaultName, Window* AssignedWindow) 
	: m_Name(DefaultName), m_Window(AssignedWindow)
{
	m_Transform = AddComponent<RETransformComponent>();
	m_ShouldDestroy = false;
}

void REGameObject::BeginPlay()
{
	for (auto Component : m_Components) {
		//test if the item is nullptr
		if (Component == nullptr) {
			//skip this loop if it is
			continue;
		}
		// run the components begin play
		Component->BeginPlay();
	}
}

void REGameObject::ProcessInput(REInput* GameInput)
{
	for (auto Component : m_Components) {
		//test if the item is nullptr
		if (Component == nullptr) {
			//skip this loop if it is
			continue;
		}
		//run the components process input
		Component->ProcessInput(GameInput);
	}
}

void REGameObject::Update(float DeltaTime)
{
	for (auto Component : m_Components) {
		//test if the item is nullptr
		if (Component == nullptr) {
			//skip this loop if it is
			continue;
		}
		//run the components update
		Component->Update(DeltaTime);
	}
}

void REGameObject::Destroy()
{
	OnDestroy();

	for (auto Component : m_Components) {
		//test if the item is nullptr
		if (Component == nullptr) {
			//skip this loop if it is
			continue;
		}
		//run the components process input
		Component->Destroy();
	}

	//removes all references to memory in the array
	//because the components are shared ptrs they will delete themselves
	m_Components.clear();

	//lets game objects know this game object wants to be removed
	m_ShouldDestroy = true;

	//call the game instance destroy game object to remove from the game
	Game::GetGameInstance()->RemoveGameObject(this);
}

void REGameObject::SetPosition(REVector2 Position)
{
	m_Transform->Position = Position;
}

void REGameObject::SetScale(REVector2 Scale)
{
	m_Transform->Scale = Scale; 
}

void REGameObject::SetRotation(float Rotation)
{
	m_Transform->Rotation = Rotation;
}
