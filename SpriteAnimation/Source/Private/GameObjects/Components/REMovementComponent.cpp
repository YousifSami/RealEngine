#include "CoreMinimal.h"
#include "GameObjects/Components/REMovementComponent.h"

#include "GameObjects/REGameObject.h"

#define GRAVITY 9.81f

REMovementComponent::REMovementComponent(REGameObject* Owner)
	: REComponent(Owner)
{
	m_Mass = 1.0f;
	m_Drag = 0.0f;
	m_MaxVelocity = 100.0f;
}

void REMovementComponent::Update(float DeltaTime)
{
	// make sure we have a transform component or theres no point on moving anything
	if (GetTransform() == nullptr) {
		return;
	}

	// setting  dragforce to gravity
	float DragForce = GRAVITY + m_Drag;
	// increasing the drag based on mass
	DragForce *= m_Mass;

	// stop adding drag when we it stops moving 
	if (m_Velocity.Length() > 0.01f) {
		//setting the drag to be negative the current velocity * the strenght
		AddForce(-m_Velocity, DragForce);
	}
	else {
		m_Velocity = 0.0f;
	}

	//increase velocity by acceleration
	m_Velocity += m_Accelaration * DeltaTime;

	// make sure that we cant go over maximum velocity
	if (m_Velocity.Length() > m_MaxVelocity) {
		m_Velocity = m_Velocity.Normal() * m_MaxVelocity;
	}

	GetTransform()->Position += m_Velocity;

	//negate acceleration to make sure we dont accelerate for ever
	m_Accelaration = REVector2::Zero();
}

void REMovementComponent::AddForce(REVector2 Direction, float Force)
{
	// geth the directio of the force and make sure its normalised
	//multiply it  by for to get the strength
	REVector2 Acceleration = Direction.Normal() * Force;

	//dive acceleration by mass to make heavier objects slower at accelerating
	//std::max will use the larger of the two numbers
	Acceleration /= std::max(m_Mass, 0.01f);

	// update the member acceleration
	m_Accelaration += Acceleration;

}

TSharedPtr<RETransformComponent> REMovementComponent::GetTransform()
{
	return GetOwner()->GetTransform();
}
