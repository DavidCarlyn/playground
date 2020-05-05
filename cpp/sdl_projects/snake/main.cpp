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
#include <Scene.hpp>
#include <stdlib.h>
#include <ctime>

const std::string FONTPATH = "LemonMilk.otf";

class GameScene : public Scene {
	public:
		GameScene() : Scene() {}
		GameScene( SDL_Window* w, SDL_Surface* s, SDL_Renderer* r ) : Scene( w, s, r ) {}

		virtual int start() override;

		int getScore() { return _score; }
	private:
		int getRandomPosition( int max ) { return rand() % max; }
		int getBlockSize() {
			int xBlockSize = ( _screenWidth - _borderPadding.getFirst() ) / _xBlocks;
			int yBlockSize = ( _screenHeight - _borderPadding.getSecond() ) / _yBlocks;
			return xBlockSize < yBlockSize ? xBlockSize : yBlockSize;
		}

		int _screenWidth;
		int _screenHeight;
		int _xBlocks;
		int _yBlocks;
		int _score;
		Vector2D<int> _borderPadding;
};

int GameScene::start() {
	srand(time(NULL));

	_screenHeight = _surface->h;
	_screenWidth = _surface->w;

	const int ticksPerFrame = 100;
	const int borderThickness = 6;
    _borderPadding = Vector2D<int>( borderThickness/2, borderThickness/2 );

	_yBlocks = 30;
	_xBlocks = 50;

	int blockSize = getBlockSize();

	Panel* windowPanel = new Panel( Vector2D<int>( _screenWidth, _screenHeight ) );
    windowPanel->setBackgroundColor( { 0, 0, 0, 255 } );

    Panel* scorePanel = new Panel( Vector2D<float>( 1.0f, 0.2f ) );
    scorePanel->setBackgroundColor( { 0, 0, 0, 255 } );

    Panel* gamePanel = new Panel( Vector2D<float>( 1.0f, 0.8f ) );
    gamePanel->setBackgroundColor( { 255, 255, 255, 255 } );

    windowPanel->addComponent( scorePanel );
    windowPanel->addComponent( gamePanel );

    TTF_Font* font = TTF_OpenFont( FONTPATH.c_str(), 56 );
	if ( font == NULL ) {
		std::cout << TTF_GetError() << std::endl;
	}

    Texture* text = new Texture( Vector2D<float>( 0.2f, 0.5f ) );
    _score = 0;
    text->loadText( _renderer, "Snake: " + std::to_string( _score ), font, { 0, 255, 0, 255 });

    scorePanel->addComponent( text );

    Snake* snake = new Snake( Vector2D<int>( blockSize, blockSize ), Vector2D<int>( 1, 1 ) );
    snake->setPosition( _borderPadding );
	Food* food = new Food( Vector2D<int>( blockSize, blockSize ), Vector2D<int>( getRandomPosition( _xBlocks ), getRandomPosition( _yBlocks ) ) );
    food->setPosition( _borderPadding );

    Panel* gameBoard = new Panel( Vector2D<int>( blockSize * _xBlocks, blockSize * _yBlocks) );
    gameBoard->setBackgroundColor( { 0, 0, 0, 255 } );
    gameBoard->setPosition( _borderPadding );
    
    gamePanel->addComponent( gameBoard );
    gamePanel->addComponent( snake );
    gamePanel->addComponent( food );

	bool quit = false;
	SDL_Event e;

	int moveToEndScreen = 0;

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
						_screenWidth = e.window.data1;
						_screenHeight = e.window.data2;
                        blockSize = getBlockSize();
                        snake->setPosition( _borderPadding );
                        food->setPosition( _borderPadding );
                        gameBoard->setPosition( _borderPadding );
                        windowPanel->setSize( Vector2D<int>( _screenWidth, _screenHeight ) );
                        gameBoard->setSize( Vector2D<int>( blockSize * _xBlocks, blockSize * _yBlocks) );
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
				if ( snakeX < 0 || snakeX > _xBlocks-1 ) {
					quit = true;
					moveToEndScreen = 1;
				} else if ( snakeY < 0 || snakeY > _yBlocks-1 ) {
					quit = true;
					moveToEndScreen = 1;
				} else if ( snake->didCollideWithBody( Vector2D<int>( snakeX, snakeY ) ) ) {
					quit = true;
					moveToEndScreen = 1;
				}

				if ( snake->getGamePosition().equals( food->getGamePosition() ) ) {
					snake->grow();
					++_score;
					text->loadText( _renderer, "Snake: " + std::to_string( _score ), font, { 0, 255, 0, 255 } );
					int newX = 0;
					int newY = 0;
					do {
						newX = getRandomPosition( _xBlocks );
						newY = getRandomPosition( _yBlocks );
					} while ( snake->didCollide( Vector2D<int>( newX, newY ) ) );
					
					food->setGamePosition( Vector2D<int>( newX, newY ) );
				}
			}
		}

		if ( quit ) {
			return moveToEndScreen;
		}

		//Clear screen
		SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderClear( _renderer );

        windowPanel->render( _renderer );


		//Update screen
		SDL_RenderPresent( _renderer );
	}


	delete windowPanel;
	TTF_CloseFont( font );
	font = NULL;

	return moveToEndScreen;
}

class StartingScene : public Scene {
	public:
		StartingScene() : Scene() {}
		StartingScene( SDL_Window* w, SDL_Surface* s, SDL_Renderer* r ) : Scene( w, s, r ) {}

		virtual int start() override;
};

class EndingScene : public Scene {
	public:
		EndingScene( int score ) : Scene() { _score = score; }
		EndingScene( int score, SDL_Window* w, SDL_Surface* s, SDL_Renderer* r ) : Scene( w, s, r ) { _score = score; }

		virtual int start() override;

	private:
		int _score;
};

int StartingScene::start() {
	int screenHeight = _surface->h;
	int screenWidth = _surface->w;

	Panel* windowPanel = new Panel( Vector2D<int>( screenWidth, screenHeight ) );
    windowPanel->setBackgroundColor( { 0, 0, 0, 255 } );

	TTF_Font* font = TTF_OpenFont( FONTPATH.c_str(), 56 );
	if ( font == NULL ) {
		std::cout << TTF_GetError() << std::endl;
	}

	Texture* title = new Texture( Vector2D<float>( 1.0f, 0.5f ) );
	title->loadText( _renderer, "Snake", font, { 0, 255, 0, 255 } );

	Texture* instructions = new Texture( Vector2D<float>( 1.0f, 0.5f ) );
	instructions->loadText( _renderer, "Click Left Mouse to Play...", font, { 0, 255, 0, 255 } );

	windowPanel->addComponent( title );
	windowPanel->addComponent( instructions );

	bool quit = false;
	SDL_Event e;
	int playGame = 0;

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
						windowPanel->setSize( Vector2D<int>( screenWidth, screenHeight ) );

                }
            } else if ( e.type == SDL_MOUSEBUTTONUP ) {
				quit = true;
				playGame = 1;
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderClear( _renderer );

        windowPanel->render( _renderer );

		//Update screen
		SDL_RenderPresent( _renderer );
	}

	delete windowPanel;
	TTF_CloseFont( font );
	font = NULL;

	return playGame;
}

int EndingScene::start() {
	int screenHeight = _surface->h;
	int screenWidth = _surface->w;

	Panel* windowPanel = new Panel( Vector2D<int>( screenWidth, screenHeight ) );
    windowPanel->setBackgroundColor( { 0, 0, 0, 255 } );

	TTF_Font* font = TTF_OpenFont( FONTPATH.c_str(), 56 );
	if ( font == NULL ) {
		std::cout << TTF_GetError() << std::endl;
	}

	Texture* gameOverText = new Texture( Vector2D<float>( 1.0f, 0.333f ) );
	gameOverText->loadText( _renderer, "Game Over", font, { 0, 255, 0, 255 } );
	
	Panel* scorePanel = new Panel( Vector2D<float>( 1.0f, 0.333f ) );
	scorePanel->setBackgroundColor( { 0, 0, 0, 255 } );

	Panel* options = new Panel( Vector2D<float>( 1.0f, 0.333f ) );
	options->setBackgroundColor( { 0, 0, 0, 255 } );

	windowPanel->addComponent( gameOverText );
	windowPanel->addComponent( scorePanel );
	windowPanel->addComponent( options );

	Texture* scoreLabel = new Texture( Vector2D<float>( 0.48f, 1.0f ) );
	scoreLabel->loadText( _renderer, "Score: " , font, { 0, 255, 0, 255 } );

	float size = 0.00f;
	int tmp = _score;
	do {
		tmp /= 10;
		size += 0.10f;
	} while ( tmp > 0 );

	Texture* scoreText = new Texture( Vector2D<float>( size, 1.0f ) );
	scoreText->loadText( _renderer, std::to_string( _score ) , font, { 255, 0, 0, 255 } );

	scorePanel->addComponent( scoreLabel );
	scorePanel->addComponent( scoreText );

	Texture* playAgain = new Texture( Vector2D<float>( 0.48f, 1.0f ) );
	playAgain->loadText( _renderer, "Play Again", font, { 0, 255, 0, 255 } );

	Texture* quitButton = new Texture( Vector2D<float>( 0.48f, 1.0f ) );
	quitButton->loadText( _renderer, "Quit", font, { 0, 255, 0, 255 } );

	options->addComponent( playAgain );
	options->addComponent( quitButton );

	bool quit = false;
	SDL_Event e;
	int playAgainReturn = 0;

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
						windowPanel->setSize( Vector2D<int>( screenWidth, screenHeight ) );

                }
            } else if ( e.type == SDL_MOUSEBUTTONUP ) {
				if ( e.button.y >= options->getPosition().getSecond() ) {
					quit = true;
					if ( e.button.x <= options->getPosition().getFirst() + options->getSize().getFirst() / 2 ) {
						playAgainReturn = 1;
					}
				}
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderClear( _renderer );

        windowPanel->render( _renderer );

		//Update screen
		SDL_RenderPresent( _renderer );
	}

	delete windowPanel;
	TTF_CloseFont( font );
	font = NULL;

	return playAgainReturn;
}

int main( int argc, char* args[] ) {
	int screenWidth = 956;
    int screenHeight = 720;

    Engine* gameEngine = new Engine();
	SDL_Window* window = gameEngine->createWindow(screenWidth, screenHeight, "Snake");
	SDL_Surface* surface = gameEngine->createSurface(window);
	SDL_Renderer* renderer = gameEngine->createRenderer(window);

	while ( true ) {
		StartingScene* startScene = new StartingScene( window, surface, renderer );
		if ( startScene->start() == 0 ) { break; }
		delete startScene;

    	GameScene* gameScene = new GameScene( window, surface, renderer );
		if ( gameScene->start() == 0 ) { break; }

		EndingScene* endScene = new EndingScene( gameScene->getScore(), window, surface, renderer );
		if ( endScene->start() == 0 ) { break; }
		delete gameScene;
		delete endScene;
	}

    gameEngine->destroyWindow(window);
    gameEngine->freeSurface(surface);
    gameEngine->destroyRenderer(renderer);
	gameEngine->close();
	delete gameEngine;

	return 0;
}