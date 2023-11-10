#include "CoreMinimal.h"
#include "Graphics/REAnimStateMachine.h"
#include "Graphics/REAnimations.h"

REAnimStateMachine::REAnimStateMachine()
{
    m_AnimIndex = 0;
    m_PosX = m_PosY = 0.0f;
    m_ScaleW = m_ScaleH = 1.0f;
}

REAnimStateMachine::~REAnimStateMachine()
{
    m_Animations.clear();
}

bool REAnimStateMachine::AddAnimation(Window* AssignedWindow, REString PathToFile, REAnimParams AnimParams)
{
    TSharedPtr<REAnimation> NewAnim = TMakeShared<REAnimation>();

    // validates if the animation was succesfully created
    if (!NewAnim->ImportAnimation(AssignedWindow, PathToFile, AnimParams)) {
        RELog("Animation failed to import into anim state machine");
        return false;
    }

    //hide the anim by default
    NewAnim->SetVisiblility(false);

    //adds animation to animation stack
    m_Animations.push_back(NewAnim);

    return true;
}

void REAnimStateMachine::Start(REUint StartingIndex)
{
    SetIndex(StartingIndex);
}

void REAnimStateMachine::Update(float DeltaTime)
{
    if (m_Animations.size() <= m_AnimIndex) {
        return;
    }

    UpdateAnimTransforms();

    m_Animations[m_AnimIndex]->Update(DeltaTime);
}

void REAnimStateMachine::SetPosition(float X, float Y)
{
    m_PosX = X;
    m_PosY = Y;
}

void REAnimStateMachine::SetScale(float W, float H)
{
    m_ScaleW = W;
    m_ScaleH = H;
}

void REAnimStateMachine::SetRotation(float NewRot)
{
    m_Rotation = NewRot;
}

void REAnimStateMachine::SetIndex(REUint Index)
{
    if (m_Animations.size() <= Index) {
        RELog("There is no animation/sprite that exists at the index");
        return;
    }

    //hide the current animation
    m_Animations[m_AnimIndex]->SetVisiblility(false);
    //change anim index to play different animation
    m_AnimIndex = Index;
    //update the transforms of that animation to make sure its in the correct position
    UpdateAnimTransforms();
    //show the animation on the screen
    m_Animations[m_AnimIndex]->SetVisiblility(true);
}

void REAnimStateMachine::UpdateAnimTransforms()
{
    m_Animations[m_AnimIndex]->SetPosition(m_PosX, m_PosY);
    m_Animations[m_AnimIndex]->SetScale(m_ScaleW, m_ScaleH);
    m_Animations[m_AnimIndex]->SetRotation(m_Rotation);
}
