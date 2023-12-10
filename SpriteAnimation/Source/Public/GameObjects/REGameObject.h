#pragma once

#include "GameObjects/Components/RETransformComponent.h"

class Window;
class REInput;
class REComponent;
class RETransformComponent;
struct REVector2;
class RECollision;

class REGameObject {
public:
	REGameObject(REString DefaultName, Window* AssignedWindow);
	~REGameObject() = default;

	//runs when the object get spawned in the game
	virtual void BeginPlay();

	//listen for player input
	virtual void ProcessInput(REInput* GameInput);

	//update logic for game object
	virtual void Update(float DeltaTime);

	//activate when a collision overlaps with this game objects collision
	//this will only run if there is a collision component on the game object
	virtual void OnBeginOverlap(RECollision* Col) {}

	//activate when a collision stops overlapping with the game objects collision
	//this will only run if there is a collision component on the game object
	virtual  void OnEndOverlap(RECollision* Col) {}

	//destroys the objects and its components
	void Destroy();

	//sets the  position of the game object
	void SetPosition(REVector2 Position);

	//sets the scale of the entire game object
	void SetScale(REVector2 Scale);

	//set the rotation of the entire game object
	void SetRotation(float Rotation);


	TSharedPtr<RETransformComponent> GetTransform() const { return m_Transform; }

	//get the window the game object is assigned
	Window* GetWindow() const { return m_Window; }

	// if destroyed wait for garbage collection
	bool IsPendingDestroy() const { return m_ShouldDestroy; }

protected:
	//runs when obeject is destroyed and before the component are destroyed
	virtual void OnDestroy() {}

	//class T - Accept any class
	//typename std::enable_if - only allow types undera condition
	//std::is_base_of<REComponent, T>::value - the template (T) has to be derived from the base class REComponent
	//::type* = nullptr - what to return if its not derived from REComponent
	template <class T, typename std::enable_if<std::is_base_of<REComponent, T>::value>::type* = nullptr>
	inline TSharedPtr<T> AddComponent() {
		TSharedPtr<T> NewComponent = TMakeShared<T>(this);

		if (NewComponent == nullptr) {
			RELog("Failed to create component on :" + m_Name);
			return nullptr;
		}

		m_Components.push_back(NewComponent);

		return NewComponent;

	}

private:
	// unique identifier for the object
	REString m_Name;

	//window that is this game object can render to
	Window* m_Window;

	//all of the components assigned to the game object
	TSharedArray<REComponent> m_Components;	

	//holds the transform information for the game object
	TSharedPtr<RETransformComponent> m_Transform;

	//flag a game object should be destroyed
	bool m_ShouldDestroy;
};