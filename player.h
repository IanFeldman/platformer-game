#pragma once
#include "actor.h"

class Player : public Actor
{

public:
	Player(class Game* game);
	void OnUpdate(float deltaTime) override;

private:
    class SpriteComponent* mSpriteComponent;
	class CollisionComponent* mCollisionComponent;
};

