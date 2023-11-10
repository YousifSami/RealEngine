#pragma once
#include "GameObjects/REGameObject.h"

class RESpriteComponent;
class REMovementComponent;

class RECharacter : public REGameObject {
public:
	RECharacter(REString DefaultName, Window* AssignedWindow);

	//get the main sprite component of the character
	TSharedPtr<RESpriteComponent> GetSpriteComponent() const { return m_SpriteComponent; }

	//get the movement component for the character
	TSharedPtr<REMovementComponent> GetMovementComponent() const { return m_MovementComponent; }

private:
	//main sprite component for the character
	TSharedPtr<RESpriteComponent>m_SpriteComponent;

	//the movement component for the character
	TSharedPtr<REMovementComponent> m_MovementComponent;
};