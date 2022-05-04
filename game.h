#pragma once
#include "actor.h"
#include "renderer.h"
#include "spritecomponent.h"
#include <SDL2/SDL.h>
#include <vector>

class Game {
    
public:
    Game();
    bool Initialize();
    void RunLoop();
    void ProcessUpdate();
    void Update();
    void GenerateOutput();
    void End();

    // adds actor to actor list here
    void AddActor(class Actor* actor);
    // removes actor from actor list here
    void RemoveActor(class Actor* actor);
    // add sprite
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    // getters/setters
    Renderer* GetRenderer() { return mRenderer; }

protected:
    bool mRunning;
    int mPrevTime;
    class Renderer* mRenderer;
    std::vector<class Actor*> mActors;
    std::vector<class SpriteComponent*> mSprites;
};
