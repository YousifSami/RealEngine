#include "CoreMinimal.h"
#include "GameObjects/Characters/REEnemy.h"
#include "GameObjects/Components/RESpriteComponent.h"
#include "GameObjects/Components/REMovementComponent.h"


REEnemy::REEnemy(REString DefaultName, Window* AssignedWindow) : RECharacter(DefaultName, AssignedWindow)
{
	m_EngineEffect = AddComponent<RESpriteComponent>();

	REAnimParams AnimParams;
	AnimParams.EndFrame= 11 ;
	AnimParams.FrameCount = 12;

	m_EngineEffect->AddAnimation(
		"EngineContent/Images/SpriteSheets/Enemies/EngineEffects/BattlecruiserEngineEffect-12f.png",
		AnimParams
		);

	//add base enemy ship sprite to the main sprite component
	GetSpriteComponent()->AddSingleSprite(
		"EngineContent/Images/SpriteSheets/Enemies/Base/MainEnemyBattlecruiser.png"
	);

	//enemy moves down te screen
	m_MovementDir = REVector2(0.0f, 1.0f);

	m_EnemyAcceleration = 10.0f;
	GetMovementComponent()->m_MaxVelocity = 3.0f;
	GetMovementComponent()->m_Drag = -5.0f;

	SetRotation(180.0f);
	SetScale(3.0f);
}

void REEnemy::Update(float DeltaTime)
{
	RECharacter::Update(DeltaTime);

	GetMovementComponent()->AddForce(m_MovementDir, m_EnemyAcceleration);

	if (GetTransform()->Position.y > 720.0f) {
		SetPosition({ GetTransform()->Position.x, -200.0f });
	}
}
