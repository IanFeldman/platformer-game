#pragma once
#include "actor.h"

class Obstacle : public Actor
{
public:
    Obstacle(class Game* game);

private:
    class SpriteComponent* mSpriteComponent;
    class CollisionComponent* mCC;
};

