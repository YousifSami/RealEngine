#include "CoreMinimal.h"
#include "GameObjects/Characters/REEnemy2.h"
#include "GameObjects/Components/RESpriteComponent.h"
#include "GameObjects/Components/RECollisionComponent.h"
#include "GameObjects/Components/REMovementComponent.h"


REEnemy2::REEnemy2(REString DefaultName, Window* AssignedWindow) : RECharacter(DefaultName, AssignedWindow)
{

	m_CharacterSize = REVector2(64.0f);
	m_EngineEffect = AddComponent<RESpriteComponent>();

	REAnimParams AnimParams;
	AnimParams.EndFrame = 9;
	AnimParams.FrameCount = 10;

	m_EngineEffect->AddAnimation(
		"EngineContent/Images/SpriteSheets/Enemies/EngineEffects/Kla'ed - Support ship - Engine10f.png",
		AnimParams
	);

	//add base enemy ship sprite to the main sprite component
	GetSpriteComponent()->AddSingleSprite(
		"EngineContent/Images/SpriteSheets/Enemies/Base/Kla'ed - Support ship - Base.png"
	);

	//enemy moves down te screen
	m_MovementDir = REVector2(0.0f, 1.0f);

	m_EnemyAcceleration = 10.0f;
	GetMovementComponent()->m_MaxVelocity = 1.0f;
	GetMovementComponent()->m_Drag = -5.0f;

	SetRotation(180.0f);
	
	
}

void REEnemy2::Update(float DeltaTime)
{
	RECharacter::Update(DeltaTime);

	GetMovementComponent()->AddForce(m_MovementDir, m_EnemyAcceleration);

	if (GetTransform()->Position.y > 720.0f) {
		SetPosition({ GetTransform()->Position.x,- GetScaledCharacterSize().y });
	}
}

void REEnemy2::BeginPlay()
{
	RECharacter::BeginPlay();
	GetCollisionComponent()->GetCollision()->Bounds.w = -GetScaledCharacterSize().x * 0.05f;
	GetCollisionComponent()->GetCollision()->Bounds.h = -GetScaledCharacterSize().y * 0.05f;
	GetCollisionComponent()->BoundsOffset.x = 64.0f;
	GetCollisionComponent()->BoundsOffset.y = 64.0f;

}
