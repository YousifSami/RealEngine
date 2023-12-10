#include "CoreMinimal.h"
#include "GameObjects/Characters/REPlayer.h"

#include"GameObjects/Components/REMovementComponent.h"
#include "GameObjects/Components/RESpriteComponent.h"
#include "GameObjects/Components/RECollisionComponent.h"
#include "REInput.h"
#include "Window/Window.h"

#define PLAYER_SIZE 48.0f

REPlayer::REPlayer(REString DefaultName, Window* AssignedWindow)
	: RECharacter(DefaultName, AssignedWindow)
{
	m_CharacterSize = REVector2(48.0f);
	m_EngineSprite = AddComponent<RESpriteComponent>();
	m_EngineEffect = AddComponent<RESpriteComponent>();

	m_PlayerAcceleration = 10.0f;
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



}

void REPlayer::BeginPlay()
{
	RECharacter::BeginPlay();
	GetCollisionComponent()->GetCollision()->Bounds.w = -GetScaledCharacterSize().x * 0.7f;
	GetCollisionComponent()->GetCollision()->Bounds.h = -GetScaledCharacterSize().y * 0.7f;
	GetCollisionComponent()->BoundsOffset.x = 41.0f;
	GetCollisionComponent()->BoundsOffset.y = 45.0f;
}

void REPlayer::Update(float DeltaTime)
{
	RECharacter::Update(DeltaTime);

	GetMovementComponent()->AddForce(m_MovementDir, m_PlayerAcceleration);

	LimitPlayerX();

}

void REPlayer::ProcessInput(REInput* GameInput)
{
	RECharacter::ProcessInput(GameInput);

	//reset the input directio to update the correct direction
	//this will also make sure we haven no input direction when no pressing anything
	m_MovementDir = REVector2::Zero();

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

void REPlayer::OnBeginOverlap(RECollision* Col)
{
	RECharacter::OnBeginOverlap(Col);

	RELog("Collision overlapped");
}

void REPlayer::OnEndOverlap(RECollision* Col)
{
	RECharacter::OnEndOverlap(Col);

	RELog("Collision end overlapped");
}


void REPlayer::LimitPlayerX()
{
	//getting the width of the window and casting it to a float
	float WindowWidth = static_cast<float>(GetWindow()->GetWidth());
	// makes sure window width considers the players size
	float PlayerSizeWindow = WindowWidth - GetScaledCharacterSize().x;


	if (GetTransform()->Position.x <= 0.0f) {
		SetPosition({ 0.0f, GetTransform()->Position.y });
	}

	if (GetTransform()->Position.x >= PlayerSizeWindow) {
		SetPosition({ PlayerSizeWindow, GetTransform()->Position.y });
	}
}
