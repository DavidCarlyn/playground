#pragma once

#include <ScreenComponent.hpp>

class Food : public ScreenComponent {
    public:
        Food();
        Food( Vector2D<int> size, Vector2D<int> position );

        Vector2D<int> getGamePosition() { return _gamePosition; }
        void setGamePosition( Vector2D<int> position ) { _gamePosition = position; }

        virtual void render( SDL_Renderer* renderer ) override;
    private:
        Vector2D<int> _gamePosition;
};