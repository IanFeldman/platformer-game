#include "collisioncomponent.h"
#include "game.h"
#include "obstacle.h"
#include "spritecomponent.h"

Obstacle::Obstacle(Game* game)
    :Actor(game)
{
    mCC = new CollisionComponent(this, 32, 32);
    //mSpriteComponent = new SpriteComponent(this, 100);
    //mSpriteComponent->SetTexture(mGame->GetTexture("assets/blank.png"));
}

