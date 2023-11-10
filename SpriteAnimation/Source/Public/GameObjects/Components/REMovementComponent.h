#pragma once
#include "GameObjects/Components/REComponent.h"
#include "Math/REVector2.h"

class RETransformComponent;

class REMovementComponent : public REComponent {
public:
	REMovementComponent(REGameObject* Owner);

	void Update(float DeltaTime) override;

	//add force to the movement to accelerate the object
	void AddForce(REVector2 Direction, float Force);

	//returns current velocity component
	REVector2 GetVelocity() const { return m_Velocity; }

protected:
	TSharedPtr<RETransformComponent> GetTransform();

public:

	//constant value against velocity
	float m_Drag;

	// max possible velocity
	float m_MaxVelocity;

	//weight of the object
	float m_Mass;

private:
	//the speed that the gameobject will be moving at
	//increase this value over time
	REVector2 m_Velocity;

	//the power/speed that the velocity will increase by
	REVector2 m_Accelaration;

};