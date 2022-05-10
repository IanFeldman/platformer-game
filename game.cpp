#include "actor.h"
#include "game.h"
#include "obstacle.h"
#include "player.h"
#include "renderer.h"
#include "spritecomponent.h"
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
    
    LoadData();
    return true;
}

void Game::LoadData() {
    mPlayer = new Player(this);
    mPlayer->SetPosition(Vector2(400, 250));
    mPlayer->SetScale(5.0f);

    Obstacle* obs = new Obstacle(this);
    obs->SetPosition(Vector2(400, 200));
    obs->SetScale(2.0f);
}

void Game::RunLoop() {
    while (mRunning){
        // poll for exit
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    mRunning = false;
                    break;
                default:
                    break;
            }
        }

        Update();
        GenerateOutput();
    }
}

void Game::Update() {
    // Setting fps
    while ((int)SDL_GetTicks() < mPrevTime + 16) {}
    int currentTime = SDL_GetTicks();
    float deltaTime = (float)(currentTime - mPrevTime) / 1000;
    mPrevTime = currentTime;

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
}

void Game::GenerateOutput() {
    // clear screen
    mRenderer->ClearScreen();

    // loop over sprites and draw them
    for (SpriteComponent* sprite : mSprites) {
        if (sprite->IsVisible()) {
            mRenderer->DrawSprite(sprite);
        }
    }

    // CC DEBUG
    for (Actor* a : mActors) {
        CollisionComponent* cc = a->GetComponent<CollisionComponent>();
        if (cc != nullptr) {
            cc->Debug();
        }
    }

    // render present
    mRenderer->Present();
}

void Game::End() {
    UnloadData();
    SDL_Quit();
}

void Game::UnloadData() {
    // destructor kills window and renderer
    delete mRenderer;

    // delete all actors
    // erase takes out of vector and deletes
    if (!mActors.empty()) {
        mActors.erase(mActors.begin(), mActors.end());
    }

    // destroy textures
    for (auto it = mTextureCache.begin(); it != mTextureCache.end(); it++) {
        SDL_DestroyTexture(it->second);
    }

    mTextureCache.clear();
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

// load texture
SDL_Texture* Game::GetTexture(const char* fileName) {
    std::unordered_map<std::string, SDL_Texture*>::const_iterator got = mTextureCache.find(fileName);
    // get it from map
    if (got != mTextureCache.end())
        return got->second;
    // or load it in
    else {
        SDL_Surface* tempSurface = IMG_Load(fileName);
        SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(mRenderer->GetSDLRenderer(), tempSurface);
        SDL_FreeSurface(tempSurface);
        mTextureCache.emplace(fileName, tempTexture);
        return tempTexture;
    }
}

