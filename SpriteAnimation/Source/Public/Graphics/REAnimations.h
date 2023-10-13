#pragma once

class Window;
class RETexture;

class REAnimation {
public:
	REAnimation();
	~REAnimation();

	//this will import a sprite sheet amd use anim params to set up for play
	bool ImportAnimation(Window* AssignedWindow, REString PathToFile, REAnimParams AnimParams);

	//updates the timer logic to switch animation frames
	void Update(float DeltaTime);

	//set the screen position of the animation
	void SetPosition(int X, int Y);
	
	//set the scale of the animation  
	void SetScale(int W, int H);

private:
	void ClipAnimation();

private:
	//animation paramaters for play rate
	REAnimParams m_AnimParams;

	//Spritesheet texture
	TSharedPtr<RETexture> m_SpriteSheet;

	//time since last frame
	float FrameTimer;

	//current frame playing in the animation
	REUint CurrentFrame;
};