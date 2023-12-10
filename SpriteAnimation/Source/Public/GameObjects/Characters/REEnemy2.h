#pragma once
#include "GameObjects/Characters/RECharacter.h"
class REEnemy2 :
    public RECharacter
{
public:
    REEnemy2(REString DefaultName, Window* AssignedWindow);

    void Update(float DeltaTime) override;

    void BeginPlay() override;

private:
    //sprite component for engine effect animation
    TSharedPtr<RESpriteComponent> m_EngineEffect;

    //direction the enemy will be moving in
    REVector2 m_MovementDir;

    float m_EnemyAcceleration;

};


