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

	//sets position of screen
	void SetPosition(float X, float Y);

	//sets scale of clipped texture
	void SetDimensions(float W, float H);

	//sets scale of  whole image
	void SetScale(float W, float H);


	void SetClip(int X, int Y, int W, int H);

private:
	// holds screen position and scale of the texture
	SDL_FRect m_ScreenRect;

	// the clip value for the texture
	SDL_Rect* m_ClipRect;

	// hold the sdl version of the texture
	SDL_Texture* m_Texture;

	// store original file path
	REString m_Path;

	// original image witch and height
	REUint m_Width, m_Height;

	//scaler values to scale size of image
	float m_ScalarW, m_ScalarH;
};
