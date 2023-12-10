#pragma once
#include "CoreMinimal.h"
#include "Collisions/REBounds.h"

class REGameObject;

enum REObjectTypes : REUint8 {
	OT_ALL = 0,
	OT_PLAYER,
	OT_ENEMY,
	OT_COLLECTABLE
};

class RECollision {
public:
	RECollision(REGameObject* Owner) : m_Owner(Owner), Debug(false), Type(OT_ALL) {}

	// return the gameobject owner of this collision
	REGameObject* GetOwner() const { return m_Owner; }

public:
	//should this be debugged(in the case of window drawn to the screen)
	bool Debug;

	// the type o object this collision is for
	REObjectTypes Type;

	//the position and the size of the collision
	//can also be used to determine overlap
	REBoxBounds Bounds;

private:
		// the owner game object for the collision
	REGameObject* m_Owner;



	
};