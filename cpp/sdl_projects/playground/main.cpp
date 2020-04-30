/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#define SDL_MAIN_HANDLED
#include <SDL_image.h>
#include <stdio.h>
#include <Engine.hpp>
#include <Texture.hpp>
#include <Dot.hpp>

int main( int argc, char* args[] ) {
	const int screenWidth = 640;
    const int screenHeight = 480;

	Engine* gameEngine = new Engine();
	SDL_Window* window = gameEngine->createWindow(screenWidth, screenHeight);
	SDL_Surface* surface = gameEngine->createSurface(window);
	SDL_Surface* pngSurface = gameEngine->createImageSurface(surface, "loaded.png");
	SDL_Renderer* renderer = gameEngine->createRenderer(window);

	Texture* dotTexture = new Texture();
	dotTexture->load(renderer, "dot.bmp");

	Texture* bgTexture = new Texture();
	bgTexture->load(renderer, "bg.png");

	Dot* dot = new Dot(dotTexture);

	bool quit = false;
	SDL_Event e;

	int scrollingOffset = 0;

	while ( !quit ) {
		//Handle events on queue
		while ( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if ( e.type == SDL_QUIT ) {
				quit = true;
			}

			//Handle input for the dot
			dot->handleEvent( e );
		}

		dot->move(screenWidth, screenHeight);

		//Scroll background
		--scrollingOffset;
		if ( scrollingOffset < -bgTexture->getWidth() ) {
			scrollingOffset = 0;
		}

		//Clear screen
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( renderer );

		//Render background
		bgTexture->render( renderer, scrollingOffset, 0 );
		bgTexture->render( renderer, scrollingOffset + bgTexture->getWidth(), 0 );

		//Render objects
		dot->render( renderer );

		//Update screen
		SDL_RenderPresent( renderer );
	}

	bgTexture->free();
	dotTexture->free();
	gameEngine->close();
	delete dot;
	delete gameEngine;

	return 0;
}