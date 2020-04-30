#include <Engine.hpp>

#include <SDL_image.h>
#include <stdio.h>

Engine::Engine() {
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		//TODO: Assert here
	}

    //Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init( imgFlags ) & imgFlags) ) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		//TODO: Assert here
	}
}

SDL_Window* Engine::createWindow() {
    //Create window
	SDL_Window* gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _screenWidth, _screenHeight, SDL_WINDOW_SHOWN );
	if ( gWindow == NULL ) {
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		//TODO: Assert here
	}

    return gWindow;
}

SDL_Surface* Engine::createSurface(SDL_Window* window) {
    return SDL_GetWindowSurface( window );
}

SDL_Surface* Engine::createImageSurface(SDL_Surface* surface, std::string path) {
    //The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if ( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        //TODO: ASSERT HERE
	} 
	//Convert surface to screen format
	optimizedSurface = SDL_ConvertSurface( loadedSurface, surface->format, 0 );
	if ( optimizedSurface == NULL ) {
		printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        //TODO: Log here
	}

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );

	return optimizedSurface;
}

void Engine::freeSurface(SDL_Surface* surface) {
    SDL_FreeSurface( surface );
	surface = NULL;
}

void Engine::destroyWindow(SDL_Window* window) {
	SDL_DestroyWindow( window );
	window = NULL;
}

void Engine::close() {
    IMG_Quit();
	SDL_Quit();
}