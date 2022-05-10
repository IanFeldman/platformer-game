#include "collisioncomponent.h"
#include "game.h"
#include "obstacle.h"
#include "spritecomponent.h"

Obstacle::Obstacle(Game* game, int width, int height)
    :Actor(game)
{
    mCC = new CollisionComponent(this, width, height);
    //mSpriteComponent = new SpriteComponent(this, 100);
    //mSpriteComponent->SetTexture(mGame->GetTexture("assets/blank.png"));
}

