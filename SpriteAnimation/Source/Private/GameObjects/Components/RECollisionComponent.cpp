#include "CoreMinimal.h"
#include "GameObjects/Components/RECollisionComponent.h"
#include "Game.h"
#include "Collisions/RECollisionEngine.h"
#include "GameObjects/REGameObject.h"

RECollisionComponent::RECollisionComponent(REGameObject* Owner) : REComponent(Owner)
{
	m_Collision = Game::GetGameInstance()->GetCollision()->AddCollision(Owner);
}

void RECollisionComponent::BeginPlay()
{
	FollowOwner();

}

void RECollisionComponent::Update(float DeltaTime)
{
	FollowOwner();

	//loop through all the  collision in the game
	for (auto Col : Game::GetGameInstance()->GetCollision()->GetCollisions()) {
		//if the collision is our collision then skip
		if (Col == m_Collision) {
			continue;
		}
		//check if we have already overlapped with the collision
		auto it = std::find(m_OverlappedCollisions.begin(), m_OverlappedCollisions.end(), Col);

		// if the collision is in the overlapped collision array
		if (it != m_OverlappedCollisions.end()) {
			//and we are no longer overlapping 
			if (m_Collision->Bounds.IsOverlapping(Col->Bounds)) {
				m_OverlappedCollisions.erase(it);
				//run the game object end overlap
				GetOwner()->OnEndOverlap(Col);
			}

		}
		//if the collision was not in the overlap collision array
		else {
			// and we are overlapping the bounds
			if (m_Collision->Bounds.IsOverlapping(Col->Bounds)) {
				m_OverlappedCollisions.push_back(Col);
				//run  the gameobjects begin overlap
				GetOwner()->OnBeginOverlap(Col);
			}
		}
	}

}

void RECollisionComponent::FollowOwner()
{
	//sets the position of the bounding box to the position of the gameobject owner and offset the value
	m_Collision->Bounds.x = GetOwner()->GetTransform()->Position.x + BoundsOffset.x;
	m_Collision->Bounds.y = GetOwner()->GetTransform()->Position.y + BoundsOffset.y;
}
