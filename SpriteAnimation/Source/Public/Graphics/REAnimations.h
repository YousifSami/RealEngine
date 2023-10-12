#pragma once

class Window;
class RETexture;

class REAnimation {
public:
	REAnimation();
	~REAnimation();

	//this will import a sprite sheet amd use anim params to set up for play
	bool ImportAnimation(Window* AssignedWindow, REString PathToFile, REAnimParams AnimParams);

	void Update(float DeltaTime);

private:
	//animation paramaters for play rate
	REAnimParams m_AnimParams;

	//Spritesheet texture
	TSharedPtr<RETexture> m_SpriteSheet;


};