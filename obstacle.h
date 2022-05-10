#pragma once
#include "actor.h"

class Obstacle : public Actor
{
public:
    Obstacle(class Game* game, int width, int height);

private:
    class SpriteComponent* mSpriteComponent;
    class CollisionComponent* mCC;
};

