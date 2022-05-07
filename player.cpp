#include "animatedsprite.h"
#include "game.h"
#include "player.h"
#include "math.h"

Player::Player(Game* game)
	:Actor(game)
    ,mMoveSpeed(300.0f)
    ,mAirMoveSpeed(100.0f)
    ,mJumpSpeed(200.0f)
    ,mFallAccel(500.0f)
{
    //mSpriteComponent = new SpriteComponent(this, 100);
    //mSpriteComponent->SetTexture(mGame->GetTexture("boid.png"));
    mASprite = new AnimatedSprite(this, 100);
    mASprite->SetFPS(10.0f);
    // idle
	std::vector<SDL_Texture*> idleAnim{
		mGame->GetTexture("assets/player/idle/idle1.png"),
		mGame->GetTexture("assets/player/idle/idle1.png"),
		mGame->GetTexture("assets/player/idle/idle2.png"),
		mGame->GetTexture("assets/player/idle/idle2.png"),
		mGame->GetTexture("assets/player/idle/idle3.png"),
		mGame->GetTexture("assets/player/idle/idle3.png"),
		mGame->GetTexture("assets/player/idle/idle4.png"),
		mGame->GetTexture("assets/player/idle/idle4.png")};
    mASprite->AddAnimation("idle", idleAnim);
    // run right
	std::vector<SDL_Texture*> runRAnim{
		mGame->GetTexture("assets/player/run-r/run-r1.png"),
		mGame->GetTexture("assets/player/run-r/run-r2.png"),
		mGame->GetTexture("assets/player/run-r/run-r3.png"),
		mGame->GetTexture("assets/player/run-r/run-r4.png"),
		mGame->GetTexture("assets/player/run-r/run-r5.png"),
		mGame->GetTexture("assets/player/run-r/run-r6.png")};
    mASprite->AddAnimation("run-right", runRAnim);
    // run left 
	std::vector<SDL_Texture*> runLAnim{
		mGame->GetTexture("assets/player/run-l/run-l1.png"),
		mGame->GetTexture("assets/player/run-l/run-l2.png"),
		mGame->GetTexture("assets/player/run-l/run-l3.png"),
		mGame->GetTexture("assets/player/run-l/run-l4.png"),
		mGame->GetTexture("assets/player/run-l/run-l5.png"),
		mGame->GetTexture("assets/player/run-l/run-l6.png")};
    mASprite->AddAnimation("run-left", runLAnim);
    // set anim
    mASprite->SetAnimation("idle");
	mASprite->SetIsPaused(false);
    // set move state
    mMoveState = MoveState::Idle;
}

void Player::OnUpdate(float deltaTime)
{
    // updates velocity
    GetInput(); 
    // add accel
    if (mPosition.y < 200.0f) {
        mVelocity.y += mFallAccel * deltaTime;
    }
    // set position if below 0
    if (mPosition.y > 200.0f) {
        mPosition.y = 200.0f;
    }
    
    mPosition += mVelocity * deltaTime;
}

void Player::GetInput() {
    Vector2 vel = Vector2(0.0f, 0.0f);

    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    bool left = keyboardState[SDL_SCANCODE_A];
    bool right = keyboardState[SDL_SCANCODE_D];
    bool space = keyboardState[SDL_SCANCODE_SPACE];

    // strat 2: go through each state
    switch(mMoveState) {
        case MoveState::Idle:
            // squat
            if (space) {
                mVelocity = Vector2(0.0f, 0.0f);
                mASprite->SetAnimation("idle"); // change to squat
                mMoveState = MoveState::Squat;
            }
            // run right
            else if (right && !left) {
                mVelocity.x = mMoveSpeed; 
                mASprite->SetAnimation("run-right");
                mMoveState = MoveState::RunRight;
            }
            // run left
            else if (!right && left) {
                mVelocity.x = -mMoveSpeed;
                mASprite->SetAnimation("run-left");
                mMoveState = MoveState::RunLeft;
            }
            break;
        case MoveState::Squat:
            // jump
            if (!space) {
                mVelocity.y = -mJumpSpeed; // change to jump speed
                mASprite->SetAnimation("idle"); // change to jump
                mMoveState = MoveState::Jump;
            }
            break;
        case MoveState::Jump:
            if (mPosition.y > 199.0f) {
                mPosition.y = 200.0f;
                mMoveState = MoveState::Idle;
                mASprite->SetAnimation("idle");
            }
            // change direction a little bit in air
            //  right
            else if (right && !left) {
                mVelocity.x = mAirMoveSpeed; 
            }
            // left
            else if (!right && left) {
                mVelocity.x = -mAirMoveSpeed;
            }
            break;
        case MoveState::RunRight:
            // squat
            if (space) {
                mVelocity = Vector2(0.0f, 0.0f);
                mASprite->SetAnimation("idle"); // change to squat
                mMoveState = MoveState::Squat;
            }
            // run left
            else if (!right && left) {
                mVelocity.x = -mMoveSpeed;
                mASprite->SetAnimation("run-left");
                mMoveState = MoveState::RunLeft;
            }
            // idle
            else if ((!right && !left) || (left && right)) {
                mVelocity = Vector2(0.0f, 0.0f);
                mASprite->SetAnimation("idle");
                mMoveState = MoveState::Idle;
            }
            break;
        case MoveState::RunLeft:
            // squat
            if (space) {
                mVelocity = Vector2(0.0f, 0.0f);
                mASprite->SetAnimation("idle"); // change to squat
                mMoveState = MoveState::Squat;
            }
            // run right
            else if (right && !left) {
                mVelocity.x = mMoveSpeed;
                mASprite->SetAnimation("run-right");
                mMoveState = MoveState::RunRight;
            }
            // idle
            else if ((!right && !left) || (left && right)) {
                mVelocity = Vector2(0.0f, 0.0f);
                mASprite->SetAnimation("idle");
                mMoveState = MoveState::Idle;
            }
            break;
        default:
            break;
    }

    // strat 1: go through each input
    /*
    if (space) {
        if (mMoveState != MoveState::Squat && mMoveState != MoveState::Jump) {
            // set velocity
            mVelocity = Vector2(0.0f, 0.0f);
            // set animation
            mASprite->SetAnimation("idle"); // change to squat
            // set state
            mMoveState = MoveState::Squat;
        }
    }
    else if (!space) {
        if (mMoveState == MoveState::Squat) {
            // set vel
            mVelocity.y = 100.0f;
            // set anim
            mASprite->SetAnimation("idle"); // jump anim
            mMoveState = MoveState::Jump;
        }
    }
    else if (left && !right) {
        if (mMoveState != MoveState::RunLeft) {
            // set velocity
            mVelocity.x = -mMoveSpeed;
            // set animation
            mASprite->SetAnimation("run-left");
            // set state
            mMoveState = MoveState::RunLeft;
        }
    }
    else if (!left && right) {
        if (mMoveState != MoveState::RunRight) {
            // set velocity
            mVelocity.x = mMoveSpeed;
            // set animation
            mASprite->SetAnimation("run-right");
            // set state
            mMoveState = MoveState::RunRight;
        }
    }
    else {
        if (mMoveState != MoveState::Idle) {
            // set velocity
            mVelocity = Vector2(0.0f, 0.0f);
            // set animation
            mASprite->SetAnimation("idle");
            // set state
            mMoveState = MoveState::Idle;
        }
    }
    */
}

