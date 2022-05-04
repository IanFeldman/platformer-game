#pragma once
#include "spritecomponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Renderer {

public:
    Renderer();
    ~Renderer();

    bool Create();
    void ClearScreen();
    void Present();

    void DrawSprite(SpriteComponent* sprite);
    void DrawTexture(SDL_Texture* texture, int width, int height, int xPos, int yPos);

    // getters/setters
    SDL_Renderer* GetSDLRenderer() { return mSDLRenderer; }
    SDL_Point GetWindowSize() { return mWindowSize; }

protected:
    SDL_Point mWindowSize;
    SDL_Window* mWindow;
    SDL_Renderer* mSDLRenderer;
};

