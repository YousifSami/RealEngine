#pragma once
#include "GameObjects/Characters/RECharacter.h"
class REPlayer :
    public RECharacter
{
public:
    REPlayer(REString DefaultName, Window* AssignedWindow);

    void BeginPlay() override;

    void Update(float DeltaTime) override;

    void ProcessInput(REInput* GameInput) override;

    void OnBeginOverlap(RECollision* Col) override;

    void OnEndOverlap(RECollision* Col) override;

private:
    //this will limit the players movement on the x-axis and thus stop the player from moving off screen
    void LimitPlayerX();

private:
    //the direction moved based on player input
    REVector2 m_MovementDir;

    //accelaration of player
    float m_PlayerAcceleration;
    
    //Stores engine sprite component
    TSharedPtr<RESpriteComponent> m_EngineSprite;

    //stores animated engine effects 
    TSharedPtr<RESpriteComponent> m_EngineEffect;
};

