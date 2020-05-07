#pragma once

#include <ScreenComponent.hpp>
#include <SDL_ttf.h>
#include <string>

class Texture : public ScreenComponent {
	public:
		Texture();
		Texture( Vector2D<int> size );
        Texture( Vector2D<int> size, Vector2D<int> position );
        Texture( Vector2D<float> size );
		~Texture();

		bool load( SDL_Renderer* renderer, std::string path );
		bool loadText( SDL_Renderer* renderer, std::string textureText, TTF_Font* font, SDL_Color textColor );

		void free();
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		void setBlendMode( SDL_BlendMode blending );
		void setAlpha( Uint8 alpha );
		
		virtual void render( SDL_Renderer* renderer ) override;

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* _texture;
		Vector2D<int> _textureSize;
};