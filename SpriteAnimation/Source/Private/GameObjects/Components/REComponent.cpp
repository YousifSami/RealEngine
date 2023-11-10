#include "CoreMinimal.h"
#include "GameObjects/Components/REComponent.h"

void REComponent::Destroy()
{
	OnDestroy();
}
