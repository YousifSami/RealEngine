#pragma 

class REAnimation;
class Window;

class REAnimStateMachine {
public:
	REAnimStateMachine();
	~REAnimStateMachine();
	
	// creates and adds animation to state machine
	bool AddAnimation(Window* AssignedWindow, REString PathToFile, REAnimParams AnimParams);

	void Start(REUint StartingIndex = 0);

	//plays anim index animation
	void Update(float DeltaTime);

	//sets position on screen
	void SetPosition(float X, float Y);

	//sets height and width for animations
	void SetScale(float W, float H);

	//set the new rotation of all animations in the state machine
	void SetRotation(float NewRot);

	// changes animation to another
	void SetIndex(REUint Index);

private:
	// update the transforms of the animation to match the state machine
	void UpdateAnimTransforms();

private:


	//stores all animation
	TSharedArray<REAnimation>m_Animations;

	//helps get animation needed
	REUint m_AnimIndex;

	//screen position and scalar value of state machine
	float m_PosX, m_PosY;

	float m_ScaleW, m_ScaleH;

	//rotation value for the anim state machine
	float m_Rotation;
};
