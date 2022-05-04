#include "actor.h"
#include "renderer.h"
#include "spritecomponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// constructor
Renderer::Renderer()
    :mWindowSize((SDL_Point){800, 500})
{
}

Renderer::~Renderer() {
    //Destroy window
    SDL_DestroyWindow(mWindow);
    // Destroy renderer
    SDL_DestroyRenderer(mSDLRenderer);
}

bool Renderer::Create() {
    // init video
    int initialized = SDL_Init(SDL_INIT_VIDEO);
    if (initialized != 0) {
        return false;
    }
    // init sdl_img
    int imgInitialized = IMG_Init(IMG_INIT_PNG);
    if ((imgInitialized & IMG_INIT_PNG) != IMG_INIT_PNG) {
        return false;
    }
    // create window
    mWindow = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowSize.x, mWindowSize.y, 0);
    if (mWindow == NULL) {
        return false;
    }
    // create renderer
    mSDLRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (mSDLRenderer == NULL) {
        return false;
    }

    return true;
}

void Renderer::ClearScreen() {
    SDL_SetRenderDrawColor(mSDLRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mSDLRenderer);
}

void Renderer::Present() {
    SDL_RenderPresent(mSDLRenderer);
}

void Renderer::DrawSprite(SpriteComponent* sprite) {
    // todo:
    // check if sprite is out of screen

    // called by game in process update
    SDL_Rect r;
    r.w = static_cast<int>(sprite->GetTexWidth() * sprite->GetOwner()->GetScale());
    r.h = static_cast<int>(sprite->GetTexHeight() * sprite->GetOwner()->GetScale());
    r.x = static_cast<int>(sprite->GetOwner()->GetPosition().x - r.w / 2);
    r.y = static_cast<int>(sprite->GetOwner()->GetPosition().y - r.h / 2);

    SDL_RenderCopy(mSDLRenderer, sprite->GetTexture(), nullptr, &r);
}

// old
/*
void Renderer::DrawTexture(SDL_Texture* texture, int width, int height, int xPos, int yPos) {
    // check if out of screen
    SDL_Rect r;
    r.w = width;
    r.h = height;
    r.x = xPos;
    r.y = yPos;

    SDL_RenderCopy(mSDLRenderer, texture, nullptr, &r);
}
*/

