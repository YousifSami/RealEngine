#pragma once
#include "REComponent.h"
#include "Collisions/RECollision.h"


class RECollision;

class RECollisionComponent :
    public REComponent
{
public:
    RECollisionComponent(REGameObject* Owner);

    virtual void BeginPlay() override;

    virtual void Update(float DeltaTime) override;


    //returns the collision attached to this component
    RECollision* GetCollision() const { return m_Collision; }

private:
    // set the position of the bounds to the position of the gameobject
    void FollowOwner();

public:
    //the offset of the collision bounds
    //usefull if you need to offset the collision from the relative position of the object
    REBoxBounds BoundsOffset;

private:
    //Collisio attached to this component
    RECollision* m_Collision;

    //store the collisions we are currently overlapped with
    TArray<RECollision*> m_OverlappedCollisions;

};

