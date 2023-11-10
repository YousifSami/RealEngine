#pragma once
#include "GameObjects/Components/REComponent.h"

class REAnimStateMachine;

class RESpriteComponent : public REComponent {
public:
	RESpriteComponent(REGameObject* Owner);

	//add an animation spritesheet to the component
	bool AddAnimation(REString PathToFile, REAnimParams AnimParams);

	//add a single from a sprite sheet into the component
	bool AddSingleSprite(REString PathToFile, RESpriteParams SpriteParams = RESpriteParams()); 

	//change the sprite to the animation or single sprite on its index
	void SetSpriteIndex(REUint Index);

	void BeginPlay() override;

	void Update(float DeltaTime) override;

protected:
	void OnDestroy() override;

private:
	//matches the position and scale of the game object
	void FollowGameObject();

private:
	//animation state machine for the sprite component
	REAnimStateMachine* m_ASM;
};