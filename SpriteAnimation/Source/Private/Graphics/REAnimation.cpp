#include "CoreMinimal.h"
#include "Graphics/REAnimations.h"
#include "Window/Window.h"
#include "Graphics/RETexture.h"

REAnimation::REAnimation()
{
    m_SpriteSheet = nullptr;
    FrameTimer = 0.0f;
    CurrentFrame = 0;
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
    if (m_AnimParams.FrameHeight == 0) {
        m_AnimParams.FrameHeight = m_SpriteSheet->GetHeight() / std::max(m_AnimParams.RowCount, 1U);
    }
    
    if (m_AnimParams.FrameWidth == 0) {
        m_AnimParams.FrameWidth = m_SpriteSheet->GetWidth() / std::max(m_AnimParams.FrameCount, 1U);
    }

    //make sure the texture uses the new width and height
    m_SpriteSheet->SetDimensions(m_AnimParams.FrameWidth, m_AnimParams.FrameHeight);

    //makes sure start from the start of frame
    CurrentFrame = m_AnimParams.StartFrame;

    //set the clip for the texture to make sure we are on the right frame
    ClipAnimation();

    return true;
}

void REAnimation::Update(float DeltaTime)
{
    if (m_SpriteSheet == nullptr) {
        return;
    }

    //increases timer by delta time
    FrameTimer += DeltaTime;

    //find how long between each frame based on frame rate
    float FPS = 1.0f / m_AnimParams.FrameRate;


    //if  timer exceeds the time between each frame then inccrement the current frame 
    //and reset the time
    if (FrameTimer > 1.0f / m_AnimParams.FrameRate) {
        FrameTimer = 0.0f;
        CurrentFrame++;
    }


    //if we exceed the end frame then reset to start frame
    if (CurrentFrame > m_AnimParams.EndFrame) {
        CurrentFrame = m_AnimParams.StartFrame;
    }

    //set the clip for the texture to make sure we are on the right frame
    ClipAnimation(); 
}

void REAnimation::SetPosition(int X, int Y)
{
    m_SpriteSheet->SetPosition(X, Y);
}

void REAnimation::SetScale(int W, int H)
{
    m_SpriteSheet->SetScale(W, H);
}

void REAnimation::ClipAnimation()
{
    m_SpriteSheet->SetClip(
        m_AnimParams.FrameWidth * CurrentFrame,
        m_AnimParams.FrameHeight * m_AnimParams.Row,
        m_AnimParams.FrameWidth,
        m_AnimParams.FrameHeight

    );
}
