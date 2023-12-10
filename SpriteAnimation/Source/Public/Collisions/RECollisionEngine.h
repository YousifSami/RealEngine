#pragma once

class RECollision;
class REGameObject;

class RECollisionEngine {
public:
	RECollisionEngine() = default;
	~RECollisionEngine();

	//get all the collision in the game
	TArray<RECollision*> GetCollisions() const { return m_CollisionStack; }

	//add a collision to the engine
	//must pass in the game object owner
	RECollision* AddCollision(REGameObject* Owner);

	//remove the collision from the engine
	void RemoveCollision(RECollision* Col);

private:
	//store all collision in the engine
	TArray<RECollision*> m_CollisionStack;
};