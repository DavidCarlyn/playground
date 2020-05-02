/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#define SDL_MAIN_HANDLED

#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Engine.hpp>
#include <Texture.hpp>
#include <Snake.hpp>
#include <Food.hpp>
#include <stdlib.h>
#include <time.h> 

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


	int screenWidth = 960;
    int screenHeight = 720;
	int yBlocks = 30;
	int xBlocks = 50;

	int topBarHeight = 50;

	int blockSize = getBlockSize(screenWidth, screenHeight-topBarHeight, xBlocks, yBlocks);
	int xMargin = (screenWidth - blockSize * xBlocks) / 2;
	int yMargin = topBarHeight + (screenHeight - blockSize * yBlocks) / 2;

	Engine* gameEngine = new Engine();
	SDL_Window* window = gameEngine->createWindow(screenWidth, screenHeight, "Snake");
	SDL_Surface* surface = gameEngine->createSurface(window);
	SDL_Renderer* renderer = gameEngine->createRenderer(window);

	TTF_Font* font = TTF_OpenFont( "LemonMilk.otf", 56 );
	if ( font == NULL ) {
		std::cout << TTF_GetError() << std::endl;
	}

	Texture* texture = new Texture();
	SDL_Color textColor = { 0, 255, 0 };
	int score = 0;
	texture->loadText( renderer, "Snake: " + std::to_string(score), font, textColor );

	Snake* snake = new Snake(1, 1, blockSize, blockSize);
	Food* food = new Food(getRandomPosition(xBlocks), getRandomPosition(yBlocks), blockSize, blockSize);

	bool quit = false;
	SDL_Event e;

	int scrollingOffset = 0;
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
					case SDL_WINDOWEVENT_MAXIMIZED:
					case SDL_WINDOWEVENT_MINIMIZED:
					case SDL_WINDOWEVENT_RESIZED:
						screenWidth = e.window.data1;
						screenHeight = e.window.data2;
						blockSize = getBlockSize( screenWidth, screenHeight, xBlocks, yBlocks );
						xMargin = (screenWidth - blockSize * xBlocks) / 2;
						yMargin = (screenHeight - blockSize * yBlocks) / 2;
						snake->setSize( blockSize, blockSize );
						food->setSize( blockSize, blockSize );
						snake->render( renderer, xMargin, yMargin );
						food->render( renderer, xMargin, yMargin );
            			break;
					default:
						break;
				}
			}

			snake->handleInput( e );
		}

		//Clear screen
		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderClear( renderer );

		// Draw border
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_Rect border;
		border.x = xMargin - borderThickness;
		border.y = yMargin - borderThickness;
		border.w = xBlocks * blockSize + borderThickness * 2;
		border.h = yBlocks * blockSize + borderThickness * 2;
		SDL_RenderFillRect( renderer, &border );
		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
		border.x += borderThickness;
		border.y += borderThickness;
		border.w -= borderThickness * 2;
		border.h -= borderThickness * 2;
		SDL_RenderFillRect( renderer, &border );



		//TODO: control speed
		Uint32 curTicks = SDL_GetTicks();
		ticks += curTicks - lastTicks;
		lastTicks = curTicks;

		if ( ticks >= ticksPerFrame ) {
			int movements = ticks / ticksPerFrame;
			for ( int i = 0; i < movements; ++i ) {
				snake->move();
				ticks -= ticksPerFrame;

				if ( snake->getX() < 0 || snake->getX() > xBlocks-1 ) {
					quit = true;
				} else if ( snake->getY() < 0 || snake->getY() > yBlocks-1 ) {
					quit = true;
				} else if ( snake->didCollideWithBody( snake->getX(), snake->getY() ) ) {
					quit = true;
				}

				if ( snake->getX() == food->getX() && snake->getY() == food->getY() ) {
					snake->grow();
					++score;
					texture->loadText( renderer, "Snake: " + std::to_string(score), font, textColor );
					int newX = 0;
					int newY = 0;
					do {
						newX = getRandomPosition( xBlocks );
						newY = getRandomPosition( yBlocks );
					} while ( snake->didCollide( newX, newY ) );
					
					food->setPos( newX, newY );
				}
			}
		}

		if ( quit ) {
			break;
		}

		texture->render( renderer, 0 + xMargin, 10 );

		snake->render( renderer, xMargin, yMargin );
		food->render( renderer, xMargin, yMargin );

		//Update screen
		SDL_RenderPresent( renderer );
	}

	//TODO: temp
	TTF_Font* game_over_font = TTF_OpenFont( "LemonMilk.otf", 224 );
	if ( font == NULL ) {
		std::cout << TTF_GetError() << std::endl;
	}
	Texture* game_over_texture = new Texture();
	game_over_texture->loadText( renderer, "Game Over", font, textColor );
	quit = false;
	while ( !quit ) {
		while ( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if ( e.type == SDL_QUIT ) {
				quit = true;
			}
		}
		//Clear screen
		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderClear( renderer );

		// Draw border
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_Rect border;
		border.x = xMargin - borderThickness;
		border.y = yMargin - borderThickness;
		border.w = xBlocks * blockSize + borderThickness * 2;
		border.h = yBlocks * blockSize + borderThickness * 2;
		SDL_RenderFillRect( renderer, &border );
		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
		border.x += borderThickness;
		border.y += borderThickness;
		border.w -= borderThickness * 2;
		border.h -= borderThickness * 2;
		SDL_RenderFillRect( renderer, &border );

		texture->render( renderer, 0 + xMargin, 10 );

		game_over_texture->render( renderer, (screenWidth / 2) - 200, (screenHeight / 2) - 50 );

		//Update screen
		SDL_RenderPresent( renderer );
	}

	TTF_CloseFont( font );
    font = NULL;

	gameEngine->close();
	delete snake;
	delete gameEngine;

	return 0;
}