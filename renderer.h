#pragma once
#include <SDL2/SDL.h>

class Renderer {

public:
    Renderer();
    bool Create();
    void Destroy();
    void ClearScreen();
    void Present();

    void DrawTexture(SDL_Texture* texture, int width, int height, int xPos, int yPos);

    // getters/setters
    SDL_Renderer* GetSDLRenderer() { return mSDLRenderer; }
    SDL_Point GetWindowSize() { return mWindowSize; }

protected:
    SDL_Point mWindowSize;
    SDL_Window* mWindow;
    SDL_Renderer* mSDLRenderer;
};

