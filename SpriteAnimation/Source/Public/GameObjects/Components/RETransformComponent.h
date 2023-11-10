#pragma once
#include "GameObjects/Components/REComponent.h"
#include "Math/REVector2.h"

class RETransformComponent : public REComponent {
public:
	RETransformComponent(REGameObject* Owner)
		: Position(REVector2(0.0f)), Scale(REVector2(1.0f)), Rotation(0.0f), REComponent(Owner) {}

	REVector2 Position;
	REVector2 Scale;
	float Rotation;
};

