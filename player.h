#pragma once
#include "actor.h"
#include "math.h"

enum class MoveState {
    Idle,
    RunRight,
    RunLeft,
    Squat,
    Jump
};

class Player : public Actor
{

public:
	Player(class Game* game);
	void OnUpdate(float deltaTime) override;
    void GetInput();

private:
    //class SpriteComponent* mSpriteComponent;
    class AnimatedSprite* mASprite;
    MoveState mMoveState;
    Vector2 mVelocity;
    float mMoveSpeed, mAirMoveSpeed, mJumpSpeed, mFallAccel;
};

