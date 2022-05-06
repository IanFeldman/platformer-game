#pragma once
#include "actor.h"
#include "math.h"

class Player : public Actor
{

public:
	Player(class Game* game);
	void OnUpdate(float deltaTime) override;
    Vector2 GetInput();

private:
    //class SpriteComponent* mSpriteComponent;
    class AnimatedSprite* mASprite;
    float mMoveSpeed;
};

