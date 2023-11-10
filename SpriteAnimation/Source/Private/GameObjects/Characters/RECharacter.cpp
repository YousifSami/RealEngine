#include "CoreMinimal.h"
#include "GameObjects/Characters/RECharacter.h"

#include "GameObjects/Components/RESpriteComponent.h"
#include "GameObjects/Components/REMovementComponent.h"

RECharacter::RECharacter(REString DefaultName, Window* AssignedWindow) 
	: REGameObject(DefaultName, AssignedWindow)
{
	m_SpriteComponent = AddComponent<RESpriteComponent>();

	m_MovementComponent = AddComponent<REMovementComponent>();
}
