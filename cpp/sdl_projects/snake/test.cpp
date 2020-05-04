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
#include <Snake.hpp>
#include <Food.hpp>
#include <stdlib.h>
#include <ctime>

int getRandomPosition(int max) {
	return rand() % max;
}

int getBlockSize(int screenWidth, int screenHeight, int xBlocks, int yBlocks) {
	int xBlockSize = screenWidth / xBlocks;
	int yBlockSize = screenHeight / yBlocks;

	return xBlockSize < yBlockSize ? xBlockSize : yBlockSize;
}


int main( int argc, char* args[] ) {
    srand(time(NULL));
	const int ticksPerFrame = 100;
	const int borderThickness = 6;
    const Vector2D<int> borderPadding = Vector2D<int>( borderThickness/2, borderThickness/2 );

	int screenWidth = 956;
    int screenHeight = 720;
	int yBlocks = 30;
	int xBlocks = 50;

	int blockSize = getBlockSize(screenWidth-borderThickness, screenHeight-borderThickness, xBlocks, yBlocks);

    Engine* gameEngine = new Engine();
	SDL_Window* window = gameEngine->createWindow(screenWidth, screenHeight, "Snake");
	SDL_Surface* surface = gameEngine->createSurface(window);
	SDL_Renderer* renderer = gameEngine->createRenderer(window);

    Panel* windowPanel = new Panel( Vector2D<int>( screenWidth, screenHeight ) );
    windowPanel->setBackgroundColor( { 0, 0, 0, 255 } );

    Panel* scorePanel = new Panel( Vector2D<float>( 1.0f, 0.2f ) );
    scorePanel->setBackgroundColor( { 0, 0, 0, 255 } );

    Panel* gamePanel = new Panel( Vector2D<float>( 1.0f, 0.8f ) );
    gamePanel->setBackgroundColor( { 255, 255, 255, 255 } );

    windowPanel->addComponent( scorePanel );
    windowPanel->addComponent( gamePanel );

    TTF_Font* font = TTF_OpenFont( "LemonMilk.otf", 56 );
	if ( font == NULL ) {
		std::cout << TTF_GetError() << std::endl;
	}

    Texture* text = new Texture( Vector2D<float>( 0.2f, 0.5f ) );
    int score = 0;
    text->loadText( renderer, "Snake: " + std::to_string(score), font, { 0, 255, 0, 255 });

    scorePanel->addComponent( text );

    Snake* snake = new Snake( Vector2D<int>( blockSize, blockSize ), Vector2D<int>( 1, 1 ) );
    snake->setPosition( borderPadding );
	Food* food = new Food( Vector2D<int>( blockSize, blockSize ), Vector2D<int>( getRandomPosition(xBlocks), getRandomPosition(yBlocks) ) );
    food->setPosition( borderPadding );

    Panel* gameBoard = new Panel( Vector2D<int>( blockSize * xBlocks, blockSize * yBlocks) );
    gameBoard->setBackgroundColor( { 0, 0, 0, 255 } );
    gameBoard->setPosition( borderPadding );
    
    gamePanel->addComponent( gameBoard );
    gamePanel->addComponent( snake );
    gamePanel->addComponent( food );

    /*
    panel->addComponent( new Panel( Vector2D<float>( 0.8f, 0.5f ) ) );
    Texture* texture = new Texture( Vector2D<float>( 0.4f, 0.4f ) );
    texture->load( renderer, "bin/demos.jpg" );
    panel->addComponent( texture );
    panel->addComponent( text );
    */

	bool quit = false;
	SDL_Event e;

    int ticks = 0;
	Uint32 lastTicks = SDL_GetTicks();
	while ( !quit ) {
		//Handle events on queue
		while ( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if ( e.type == SDL_QUIT ) {
				quit = true;
			} else if ( e.type == SDL_WINDOWEVENT ) {
				switch ( e.window.event ) {
					case SDL_WINDOWEVENT_SIZE_CHANGED:
					case SDL_WINDOWEVENT_RESIZED:
						screenWidth = e.window.data1;
						screenHeight = e.window.data2;
                        std::cout << screenHeight << std::endl;
                        blockSize = getBlockSize( screenWidth-borderThickness, screenHeight-borderThickness, xBlocks, yBlocks );
                        snake->setPosition( borderPadding );
                        food->setPosition( borderPadding );
                        gameBoard->setPosition( borderPadding );
                        windowPanel->setSize( Vector2D<int>( screenWidth, screenHeight ) );
                        gameBoard->setSize( Vector2D<int>( blockSize * xBlocks, blockSize * yBlocks) );
                        snake->setSize( Vector2D<int>( blockSize, blockSize ) );
                        food->setSize( Vector2D<int>( blockSize, blockSize ) );

                }
            }

            snake->handleInput( e );
		}

        //TODO: control speed
		Uint32 curTicks = SDL_GetTicks();
		ticks += curTicks - lastTicks;
		lastTicks = curTicks;

		if ( ticks >= ticksPerFrame ) {
			int movements = ticks / ticksPerFrame;
			for ( int i = 0; i < movements; ++i ) {
				snake->move();
				ticks -= ticksPerFrame;

                int snakeX = snake->getGamePosition().getFirst();
                int snakeY = snake->getGamePosition().getSecond();
				if ( snakeX < 0 || snakeX > xBlocks-1 ) {
					quit = true;
				} else if ( snakeY < 0 || snakeY > yBlocks-1 ) {
					quit = true;
				} else if ( snake->didCollideWithBody( Vector2D<int>( snakeX, snakeY ) ) ) {
					quit = true;
				}

				if ( snake->getGamePosition().equals( food->getGamePosition() ) ) {
					snake->grow();
					++score;
					text->loadText( renderer, "Snake: " + std::to_string(score), font, { 0, 255, 0, 255 } );
					int newX = 0;
					int newY = 0;
					do {
						newX = getRandomPosition( xBlocks );
						newY = getRandomPosition( yBlocks );
					} while ( snake->didCollide( Vector2D<int>( newX, newY ) ) );
					
					food->setGamePosition( Vector2D<int>( newX, newY ) );
				}
			}
		}

		if ( quit ) {
			break;
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