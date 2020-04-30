#include <Texture.hpp>
#include <SDL_image.h>

Texture::Texture() {
	_texture = NULL;
	_width = 0;
	_height = 0;
}

Texture::~Texture() {
	free();
}

bool Texture::load( SDL_Renderer* renderer, std::string path ) {

	free();

	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if ( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        //TODO: Log here
        return false;
	}

	//Color key image
	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

	//Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
	if( newTexture == NULL ) {
		printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        //TODO: Log here
        return false;
	}

	//Get image dimensions
	_width = loadedSurface->w;
	_height = loadedSurface->h;

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );

	//Return success
	_texture = newTexture;
	return _texture != NULL;
}

void Texture::free() {
	//Free texture if it exists
	if( _texture != NULL )
	{
		SDL_DestroyTexture( _texture );
		_texture = NULL;
		_width = 0;
		_height = 0;
	}
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
	SDL_SetTextureColorMod( _texture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending ) {
	SDL_SetTextureBlendMode( _texture, blending );
}
		
void Texture::setAlpha( Uint8 alpha ) {
	SDL_SetTextureAlphaMod( _texture, alpha );
}

void Texture::render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ) {
	SDL_Rect renderQuad = { x, y, _width, _height };

	//Set clip rendering dimensions
	if ( clip != NULL ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx( renderer, _texture, clip, &renderQuad, angle, center, flip );
}

int Texture::getWidth() {
	return _width;
}

int Texture::getHeight() {
	return _height;
}