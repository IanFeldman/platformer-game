#include "renderer.h"
#include <SDL2/SDL.h>

// constructor
Renderer::Renderer()
    :mWindowSize((SDL_Point){800, 500})
{
}

bool Renderer::Create() {
    // init video
    int initialized = SDL_Init(SDL_INIT_VIDEO);
    if (initialized != 0) {
        return false;
    }
    // create window
    mWindow = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowSize.x, mWindowSize.y, 0);
    if (mWindow == NULL) {
        return false;
    }

    mSDLRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (mSDLRenderer == NULL) {
        return false;
    }

    return true;
}

void Renderer::Destroy() {
    //Destroy window
    SDL_DestroyWindow(mWindow);
    // Destroy renderer
    SDL_DestroyRenderer(mSDLRenderer);
}

void Renderer::ClearScreen() {
    SDL_SetRenderDrawColor(mSDLRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mSDLRenderer);
}

void Renderer::Present() {
    SDL_RenderPresent(mSDLRenderer);
}

void Renderer::DrawTexture(SDL_Texture* texture, int width, int height, int xPos, int yPos) {
    // check if out of screen
    
    SDL_Rect r;
    r.w = width;
    r.h = height;
    r.x = xPos;
    r.y = yPos;

    SDL_RenderCopy(mSDLRenderer, texture, nullptr, &r);
}

