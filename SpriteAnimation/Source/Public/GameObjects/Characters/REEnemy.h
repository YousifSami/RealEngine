#pragma once
#include "GameObjects/Characters/RECharacter.h"
class REEnemy :
    public RECharacter
{
public:
    REEnemy(REString DefaultName, Window* AssignedWindow);

    void Update(float DeltaTime) override;

private:
    //sprite component for engine effect animation
    TSharedPtr<RESpriteComponent> m_EngineEffect;

    //direction the enemy will be moving in
    REVector2 m_MovementDir;

    float m_EnemyAcceleration;

};

