/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#define SDL_MAIN_HANDLED

#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Engine.hpp>
#include <Window.hpp>
#include <Food.hpp>
#include <Texture.hpp>

const std::string sprites = "bin/snake_sprite_sheet.png";

int main( int argc, char* args[] ) {
	Window* window = new Window( "Testing", Vector2D<int>( 1080, 720 ) );
	window->getPanel()->setBackgroundColor( { 100, 100, 100 } );

	Texture* snakeSprites = new Texture();
	snakeSprites->load( window->getRenderer(), sprites );

	Food* food = new Food( Vector2D<int>( 48, 48 ), Vector2D<int>( 5, 5 ) );
	SDL_Rect clip;
	clip.x = 16;
	clip.y = 0;
	clip.w = 16;
	clip.h = 16;
	food->setTexture( snakeSprites, &clip );
	window->addComponent( food );

	window->display();

	return 0;
}