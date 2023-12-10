#include "CoreMinimal.h"
#include "GameObjects/Characters/RECharacter.h"

#include "GameObjects/Components/RESpriteComponent.h"
#include "GameObjects/Components/REMovementComponent.h"
#include "GameObjects/Components/RECollisionComponent.h"

RECharacter::RECharacter(REString DefaultName, Window* AssignedWindow) 
	: REGameObject(DefaultName, AssignedWindow)
{
	m_CharacterSize = REVector2(1.0f);
	m_SpriteComponent = AddComponent<RESpriteComponent>();
	m_MovementComponent = AddComponent<REMovementComponent>();
	m_CollisionComponent = AddComponent<RECollisionComponent>();
	
	m_CollisionComponent->GetCollision()->Debug = true;
	
}

void RECharacter::BeginPlay()
{
	REGameObject::BeginPlay();
	m_CollisionComponent->GetCollision()->Bounds.w = GetScaledCharacterSize().x;
	m_CollisionComponent->GetCollision()->Bounds.h = GetScaledCharacterSize().y;
}

REVector2 RECharacter::GetScaledCharacterSize() const
{
	return GetTransform()->Scale * m_CharacterSize;
}
