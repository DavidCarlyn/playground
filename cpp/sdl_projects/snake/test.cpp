/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#define SDL_MAIN_HANDLED

#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Engine.hpp>
#include <Panel.hpp>
#include <Texture.hpp>
#include <stdlib.h>


int main( int argc, char* args[] ) {
    int screenWidth = 1080;
    int screenHeight = 720;

    Engine* gameEngine = new Engine();
	SDL_Window* window = gameEngine->createWindow(screenWidth, screenHeight, "Snake");
	SDL_Surface* surface = gameEngine->createSurface(window);
	SDL_Renderer* renderer = gameEngine->createRenderer(window);

    Panel* windowPanel = new Panel( Vector2D<int>( screenWidth, screenHeight ) );
    windowPanel->setBackgroundColor( { 0, 0, 0, 255 } );

    Panel* scorePanel = new Panel( Vector2D<float>( 1.0f, 0.2f ) );
    scorePanel->setBackgroundColor( { 0, 0, 0, 255 } );

    Panel* gamePanel = new Panel( Vector2D<float>( 1.0f, 0.8f ) );
    gamePanel->setBackgroundColor( { 255, 0, 0, 255 } );

    windowPanel->addComponent( scorePanel );
    windowPanel->addComponent( gamePanel );

    TTF_Font* font = TTF_OpenFont( "bin/LemonMilk.otf", 56 );
	if ( font == NULL ) {
		std::cout << TTF_GetError() << std::endl;
	}

    Texture* text = new Texture( Vector2D<float>( 0.2f, 0.5f ) );
    text->loadText( renderer, "Snake", font, { 0, 255, 0, 255 });

    scorePanel->addComponent( text );

    /*
    panel->addComponent( new Panel( Vector2D<float>( 0.8f, 0.5f ) ) );
    Texture* texture = new Texture( Vector2D<float>( 0.4f, 0.4f ) );
    texture->load( renderer, "bin/demos.jpg" );
    panel->addComponent( texture );
    panel->addComponent( text );
    */

	bool quit = false;
	SDL_Event e;

	while ( !quit ) {
		//Handle events on queue
		while ( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if ( e.type == SDL_QUIT ) {
				quit = true;
			} 

		}

		//Clear screen
		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderClear( renderer );

        windowPanel->render( renderer );

		//Update screen
		SDL_RenderPresent( renderer );
	}

    gameEngine->destroyWindow(window);
    gameEngine->freeSurface(surface);
    gameEngine->destroyRenderer(renderer);
	gameEngine->close();
	delete gameEngine;

	return 0;
}