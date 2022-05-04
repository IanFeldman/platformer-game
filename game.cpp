#include "actor.h"
#include "game.h"
#include "spritecomponent.h"
#include "renderer.h"
#include <SDL2/SDL.h>

Game::Game()
    :mRunning(true)
{
}

bool Game::Initialize() {
    // create renderer
    mRenderer = new Renderer(); // new creates the object and returns reference to it
    if (!mRenderer->Create())
        return false;
    
    // set previous time
    mPrevTime = SDL_GetTicks();
    
    return true;
}

void Game::RunLoop() {
    while (mRunning){
        ProcessUpdate();
        Update();
        GenerateOutput();
    }
}

void Game::ProcessUpdate() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                mRunning = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        mRunning = false;
                        break;
                    case SDLK_d:
                        break;
                    case SDLK_a:
                        break;
                    case SDLK_w:
                        break;
                    case SDLK_s:
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void Game::Update() {
    // Setting fps
    while ((int)SDL_GetTicks() < mPrevTime + 16) {}
    int currentTime = SDL_GetTicks();
    float deltaTime = (float)(currentTime - mPrevTime) / 1000;
    mPrevTime = currentTime;

    // clear screen
    mRenderer->ClearScreen();

    // update actors
    // calls onupdate and updates all components
    std::vector<Actor*> actors = mActors;
    for (Actor* a : actors) {
        a->Update(deltaTime);
    }

    // destroy dead actors
    std::vector<Actor*> tempActors;
    for (Actor* a : mActors) {
        if (a->GetState() == ActorState::Destroy) {
            tempActors.emplace_back(a);
        }
    }

    if (!tempActors.empty()) {
        for (Actor* tempActor : tempActors) {
            delete tempActor; // calls actor destructor
        }
    }
    
    // render present
    mRenderer->Present();
}

void Game::GenerateOutput() {
}

void Game::End() {
    mRenderer->Destroy();
    SDL_Quit();
}

// add/remove actors
void Game::AddActor(Actor* actor) {
    mActors.push_back(actor);
}

void Game::RemoveActor(Actor* actor) {
    // create iterator
    std::vector<Actor*>::iterator it;
    // find actor
    it = std::find(mActors.begin(), mActors.end(), actor);
    // remove it from actor vector
    if (it != mActors.end()) {
        mActors.erase(it);
    }
}

// add/remove sprites
void Game::AddSprite(SpriteComponent* sprite) {
    mSprites.push_back(sprite);
    std::sort(mSprites.begin(), mSprites.end(),
        [](SpriteComponent* a, SpriteComponent* b) {
            return a->GetDrawOrder() < b->GetDrawOrder();
        });
}

void Game::RemoveSprite(SpriteComponent* sprite) {
    std::vector<SpriteComponent*>::iterator it;
    it = std::find(mSprites.begin(), mSprites.end(), sprite);

    if (it != mSprites.end()) {
        mSprites.erase(it);
    }
}
