#include "actor.h"
#include "game.h"
#include "renderer.h"
#include "spritecomponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// constructor
Renderer::Renderer(Game* game)
    :mGame(game)
    ,mWindowSize((SDL_Point){800, 500})
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
    // cam worldspace
    float camX = mGame->GetCamera().x;
    float camY = mGame->GetCamera().y;
    // owner world pos -> cam pos
    float ownerPosX = sprite->GetOwner()->GetPosition().x - camX + mWindowSize.x / 2; // relative to cam position
    float ownerPosY = sprite->GetOwner()->GetPosition().y - camY + mWindowSize.y / 2; // relative to cam position
    float texW = sprite->GetTexWidth();
    float texH = sprite->GetTexHeight();
    float scale = sprite->GetOwner()->GetScale();

    // check if sprite is out of screen
    if (ownerPosX + (texW / 2.0f) * scale < 0 || ownerPosX - (texW / 2.0f) * scale > mWindowSize.x) {
        return;
    }

    // called by game in process update
    SDL_Rect r;
    r.w = static_cast<int>(texW * scale);
    r.h = static_cast<int>(texH * scale);
    r.x = static_cast<int>(ownerPosX - r.w / 2);
    r.y = static_cast<int>(ownerPosY - r.h / 2);

    SDL_RenderCopy(mSDLRenderer, sprite->GetTexture(), nullptr, &r);
}

// CC DEBUG
void Renderer::DrawRectangle(SDL_Rect rect) {
    // cam worldspace
    float camX = mGame->GetCamera().x;
    float camY = mGame->GetCamera().y;
    // convert to cam space
    rect.x += -camX + mWindowSize.x / 2;
    rect.y += -camY + mWindowSize.y / 2;
    SDL_SetRenderDrawColor(mSDLRenderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(mSDLRenderer, &rect);
}

