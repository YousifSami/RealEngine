#include "CoreMinimal.h"
#include "Graphics/RETexture.h"
#include "SDL2/SDL_image.h"

RETexture::RETexture()
{
	// initialise variables here
	m_ScreenRect = { 0, 0, 0, 0 };
	m_ClipRect = nullptr;
	m_Texture = nullptr;
	m_Width = m_Height = 0;
	m_ScalarW = m_ScalarH = 1.0f;
	m_Visibility = true;
	m_Rotation = 0.0;
}

RETexture::~RETexture()
{
	ClearTexture();
}

bool RETexture::ImportTexture(SDL_Renderer* Renderer, REString PathToFile)
{
	// clears the textures if the there already is one
	if (m_Texture != nullptr) {
		ClearTexture();
	}

	// import texture - SDL surface - which is a string of pixels
	SDL_Surface* ImageSurface = IMG_Load(PathToFile.c_str());

	if (ImageSurface == nullptr) {
		RELog("image failed to import: " +PathToFile + " - " + SDL_GetError());
		return false;
	}

	// turn surface into texture to render on the screen
	m_Texture = SDL_CreateTextureFromSurface(Renderer, ImageSurface);

	// set the width and height of an image
	m_ScreenRect.w = m_Width = ImageSurface->w;
	m_ScreenRect.h = m_Height = ImageSurface->h;
	//stores the path
	m_Path = PathToFile;

	// remove the surface from memory
	SDL_FreeSurface(ImageSurface);

	if (m_Texture == nullptr) {
		RELog("image failed to convert to texture: " + PathToFile + " - " + SDL_GetError());
	}

	// log success
	RELog("Texture loaded Succesfully: " + m_Path);

	return true;
}

void RETexture::Render(SDL_Renderer* Renderer)
{
	if (!m_Visibility) {
		return;
	}

	SDL_FRect ScaledScreenRect = m_ScreenRect;
	ScaledScreenRect.w *= m_ScalarW;
	ScaledScreenRect.h *= m_ScalarH;

	//render texture to the screen
	SDL_RenderCopyExF(
		Renderer,
		m_Texture,
		m_ClipRect,
		&m_ScreenRect,
		m_Rotation,
		nullptr,
		SDL_FLIP_NONE
	);
}

void RETexture::ClearTexture()
{
	// removes texture from memory
	if (m_Texture != nullptr) {
		SDL_DestroyTexture(m_Texture);
	}

	// removes the clip rect from memory
	if (m_ClipRect != nullptr) {
		delete m_ClipRect;
	}
}

void RETexture::SetPosition(float X, float Y)
{
	m_ScreenRect.x = X;
	m_ScreenRect.y = Y;
}

void RETexture::SetDimensions(float W, float H)
{
	m_ScreenRect.w = W;
	m_ScreenRect.h = H;
}

void RETexture::SetScale(float W, float H)
{
	m_ScalarW = W;
	m_ScalarH = H;

}

void RETexture::SetClip(int X, int Y, int W, int H)
{
	if (m_ClipRect == nullptr) {
		m_ClipRect = new SDL_Rect();
	}

	m_ClipRect->x = X;
	m_ClipRect->y = Y;
	m_ClipRect->w = W;
	m_ClipRect->h = H;

}
