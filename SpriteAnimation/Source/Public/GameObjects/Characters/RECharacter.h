#pragma once
#include "GameObjects/REGameObject.h"

class RESpriteComponent;
class REMovementComponent;
class RECollisionComponent;

class RECharacter : public REGameObject {
public:
	RECharacter(REString DefaultName, Window* AssignedWindow);

	void BeginPlay() override;

	//get the main sprite component of the character
	TSharedPtr<RESpriteComponent> GetSpriteComponent() const { return m_SpriteComponent; }

	//get the movement component for the character
	TSharedPtr<REMovementComponent> GetMovementComponent() const { return m_MovementComponent; }

	TSharedPtr<RECollisionComponent> GetCollisionComponent() const { return m_CollisionComponent; }

	REVector2 GetcharacterSize() const { return m_CharacterSize; }

	// get the size of the character scaled
	REVector2 GetScaledCharacterSize() const;

protected:
	//size of character without scale
	REVector2 m_CharacterSize;

private:
	//main sprite component for the character
	TSharedPtr<RESpriteComponent>m_SpriteComponent;

	//the movement component for the character
	TSharedPtr<REMovementComponent> m_MovementComponent;

	//the main collision component for the game objects
	TSharedPtr<RECollisionComponent> m_CollisionComponent;
};