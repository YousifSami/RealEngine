#include "CoreMinimal.h"
#include "Collisions/RECollisionEngine.h"
#include "Collisions/RECollision.h"

RECollisionEngine::~RECollisionEngine()
{
	//loop through all collsion and delete them
	for (auto Col : m_CollisionStack) {
		delete Col;
	}

	//resize the array to 0
	m_CollisionStack.clear();
}

RECollision* RECollisionEngine::AddCollision(REGameObject* Owner)
{
	//create the collision object
	RECollision* NewCol = new RECollision(Owner);

	// test if it was created
	if (NewCol != nullptr) {
		//if it was create then add it to the stack
		m_CollisionStack.push_back(NewCol);
	}

	//return the collision in case the thing that created wants to use it store it
	return NewCol;
}

void RECollisionEngine::RemoveCollision(RECollision* Col)
{
	//look through the whole collision stack and see if the collision exists
	// this returns the end() iteraTOR value if it didnt find the  element(Col)
	auto it = std::find(m_CollisionStack.begin(), m_CollisionStack.end(), Col);

	//if we didnt find the element end the function
	if (it == m_CollisionStack.end()) {
		return;
	}

	//remove the collision from memory
	delete *it;

	//remove the element from the array and resize the array
	m_CollisionStack.erase(it);
}
