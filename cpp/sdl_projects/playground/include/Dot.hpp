#pragma once

#include <SDL.h>
#include <Texture.hpp>

class Dot {
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 10;

		//Initializes the variables
		Dot(Texture* texture);
        ~Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

		//Shows the dot on the screen
		void render(SDL_Renderer* renderer);

    private:
		//The X and Y offsets of the dot
		int _x, _y;
		//The velocity of the dot
		int _xVel, _yVel;

        Texture* _texture;
};