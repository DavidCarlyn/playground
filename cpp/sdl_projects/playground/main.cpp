/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#define SDL_MAIN_HANDLED
#include <SDL_image.h>
#include <stdio.h>
#include <Engine.hpp>

int main( int argc, char* args[] ) {
	Engine* gameEngine = new Engine();
	SDL_Window* window = gameEngine->createWindow();
	SDL_Surface* surface = gameEngine->createSurface(window);
	SDL_Surface* pngSurface = gameEngine->createImageSurface(surface, "loaded.png");

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while( !quit ) {
		//Handle events on queue
		while ( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if ( e.type == SDL_QUIT ) {
				quit = true;
			}
		}
		//Apply the PNG image
		SDL_BlitSurface( pngSurface, NULL, surface, NULL );
		//Update the surface
		SDL_UpdateWindowSurface( window );
	}

	gameEngine->close();
	delete gameEngine;

	return 0;
}