#pragma once

class RETexture {
public:
	RETexture();
	~RETexture();

	// import an image file and convert it to a texture
	bool ImportTexture(SDL_Renderer* Renderer, REString PathToFile);

	// render texture to the SDL renderer
	void Render(SDL_Renderer* Renderer);

	// deallocate memory
	void ClearTexture();

	//get original image width
	inline REUint GetWidth() const { return m_Width; }

	//get original image height
	inline REUint GetHeight() const { return m_Height; }

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

	// original image witch and height
	REUint m_Width, m_Height;
};
