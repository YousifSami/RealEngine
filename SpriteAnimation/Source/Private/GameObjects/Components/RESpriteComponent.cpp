#include "CoreMinimal.h"
#include "GameObjects/Components/RESpriteComponent.h"

#include "Graphics/REAnimStateMachine.h"
#include "GameObjects/REGameObject.h"

RESpriteComponent::RESpriteComponent(REGameObject* Owner)
	: REComponent(Owner)
{
	m_ASM = new REAnimStateMachine();
}

bool RESpriteComponent::AddAnimation(REString PathToFile, REAnimParams AnimParams)
{
	return m_ASM->AddAnimation(GetOwner()->GetWindow(), PathToFile, AnimParams);
}

bool RESpriteComponent::AddSingleSprite(REString PathToFile, RESpriteParams SpriteParams)
{

	REAnimParams AnimParams;
		AnimParams.StartFrame = SpriteParams.Frame;
		AnimParams.EndFrame = SpriteParams.Frame;
		AnimParams.FrameCount = SpriteParams.FrameCount;
		AnimParams.FrameWidth = SpriteParams.FrameWidth;
		AnimParams.FrameHeight = SpriteParams.FrameHeight;
		AnimParams.Row = SpriteParams.Row;
		AnimParams.RowCount = SpriteParams.RowCount;
		AnimParams.FrameRate = 0.0f;

	return m_ASM->AddAnimation(GetOwner()->GetWindow(), PathToFile, AnimParams);
}

void RESpriteComponent::SetSpriteIndex(REUint Index)
{
	m_ASM->SetIndex(Index);
}

void RESpriteComponent::BeginPlay()
{
	FollowGameObject();

	m_ASM->Start();
}

void RESpriteComponent::Update(float DeltaTime)
{
	FollowGameObject();

	m_ASM->Update(DeltaTime);
}

void RESpriteComponent::OnDestroy()
{
	if (m_ASM != nullptr) {
		delete m_ASM;
	}
}

void RESpriteComponent::FollowGameObject()
{
	//set the position of the anim state machine to the owner object
	m_ASM->SetPosition(
		GetOwner()->GetTransform()->Position.x,
		GetOwner()->GetTransform()->Position.y
	);
	//set the scale of the anim state machine to the owner object
	m_ASM->SetScale(
		GetOwner()->GetTransform()->Scale.x, 
		GetOwner()->GetTransform()->Scale.y
	);
	//set the rotation of the anim state machine to the owner object
	m_ASM->SetRotation(GetOwner()->GetTransform()->Rotation);
}
