#pragma once

class RETexture {
public:
	RETexture();
	~RETexture();

	// import an image file and convert it to a texture
	bool ImportTexture(SDL_Renderer* Renderer, REString PathToFile);

	// render texture to the SDL renderer
	void Renderer(SDL_Renderer* Renderer);

	// deallocate memory
	void ClearTexture();

public: 
	// holds screen position and scale of the texture
	SDL_FRect m_ScreenRect;

private:
	// the clip value for the texture
	SDL_Rect* m_ClipRect;

	// hold the sdl version of the texture
	SDL_Texture* m_Texture;

	// store original file path
	REString m_Path;
};
