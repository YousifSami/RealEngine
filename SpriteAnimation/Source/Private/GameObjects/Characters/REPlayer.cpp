#include "CoreMinimal.h"
#include "GameObjects/Characters/REPlayer.h"

#include"GameObjects/Components/REMovementComponent.h"
#include "GameObjects/Components/RESpriteComponent.h"
#include "REInput.h"

REPlayer::REPlayer(REString DefaultName, Window* AssignedWindow)
	: RECharacter(DefaultName, AssignedWindow)
{
	m_EngineSprite = AddComponent<RESpriteComponent>();
	m_EngineEffect = AddComponent<RESpriteComponent>();

	m_PlayerAcceleration = 100.0f;
	GetMovementComponent()->m_MaxVelocity = 2;
	GetMovementComponent()->m_Drag = -2.0f;


	//add base ship sprite
	m_EngineSprite->AddSingleSprite("EngineContent/Images/SpriteSheets/Ships/Engines/MainShipEnginesSupercharged.png");

	//add engine effects
	GetSpriteComponent()->AddSingleSprite("EngineContent/Images/SpriteSheets/Ships/Base/MainShipFullHealth.png");


	//set up animated engine effects sprite
	REAnimParams AnimParams;
	AnimParams.FrameCount = 4;
	AnimParams.EndFrame = 3;

	//idle effect
	m_EngineEffect->AddAnimation("EngineContent/Images/SpriteSheets/Ships/EngineEffects/Supercharged EngineIdle.png"
		, AnimParams);

	//powered effect
	m_EngineEffect->AddAnimation("EngineContent/Images/SpriteSheets/Ships/EngineEffects/Supercharged EnginePowering.png"
		, AnimParams);


	SetScale(5.0f);
}

void REPlayer::Update(float DeltaTime)
{
	RECharacter::Update(DeltaTime);

	GetMovementComponent()->AddForce(m_MovementDir, m_PlayerAcceleration);

	if (GetTransform()->Position.y > 720.0f) {
		SetPosition({ GetTransform()->Position.x, -200.0f });
	}

}

void REPlayer::ProcessInput(REInput* GameInput)
{
	RECharacter::ProcessInput(GameInput);

	//reset the input directio to update the correct direction
	//this will also make sure we haven no input direction when no pressing anything
	m_MovementDir = REVector2::Zero();

	//move up when pressing W
	if (GameInput->IsKeyDown(SDL_SCANCODE_W)) {
		m_MovementDir += REVector2(0.0f, -1.0f);
	}
	//move down when pressing S
	if (GameInput->IsKeyDown(SDL_SCANCODE_S)) {
		m_MovementDir += REVector2(0.0f, 1.0f);
	}
	//move left when pressing A
	if (GameInput->IsKeyDown(SDL_SCANCODE_A)) {
		m_MovementDir += REVector2(-1.0f, 0.0f);
	}
	//move right when pressing D
	if (GameInput->IsKeyDown(SDL_SCANCODE_D)) {
		m_MovementDir += REVector2(1.0f, 0.0f);
	}

	//if the movement input is greater than zero 
	if (m_MovementDir.Length() > 0.0f) {
		m_EngineEffect->SetSpriteIndex(1);// set engines to powered
	}
	else {
		m_EngineEffect->SetSpriteIndex(0); // set engines to idle
	}

}
