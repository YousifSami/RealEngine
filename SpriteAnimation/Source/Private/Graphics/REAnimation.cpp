#include "CoreMinimal.h"
#include "Graphics/REAnimations.h"
#include "Window/Window.h"

REAnimation::REAnimation()
{
    m_SpriteSheet = nullptr;
}

REAnimation::~REAnimation()
{
    m_SpriteSheet = nullptr;
}

bool REAnimation::ImportAnimation(Window* AssignedWindow, REString PathToFile, REAnimParams AnimParams)
{
    //create texture and sotre in spritesheet for later use
    m_SpriteSheet = AssignedWindow->CreateTexture(PathToFile);

    //validation check that textures work
    if (m_SpriteSheet == nullptr) {
        RELog("Animation failed to create texture.");
        return false;
    }

    //set the anim params if texture worked
    m_AnimParams = AnimParams;

    //auto assigns width and height of animation if not set manually
    if (m - AnimParams.FrameHeight == 0) {

    }

    return true;
}

void REAnimation::Update(float DeltaTime)
{
}
