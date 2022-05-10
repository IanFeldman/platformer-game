#include "animatedsprite.h"
#include "collisioncomponent.h"
#include "game.h"
#include "player.h"
#include "math.h"

Player::Player(Game* game)
	:Actor(game)
    ,mMoveSpeed(300.0f)
    ,mAirMoveSpeed(100.0f)
    ,mJumpSpeed(800.0f)
    ,mFallAccel(1500.0f)
    ,mGrounded(false)
{
    // create collision component
    mCC = new CollisionComponent(this, 16, 30);

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
    // squat
	std::vector<SDL_Texture*> squatAnim{
		mGame->GetTexture("assets/player/squat/squat1.png")};
    mASprite->AddAnimation("squat", squatAnim);
    // jump
	std::vector<SDL_Texture*> jumpAnim{
		mGame->GetTexture("assets/player/jump/jump1.png")};
    mASprite->AddAnimation("jump", jumpAnim);
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
    if (!mGrounded) {
        mVelocity.y += mFallAccel * deltaTime;
    }
    
    mPosition += mVelocity * deltaTime;
    // offset for collisions
    Vector2 offset = mCC->GetMinOffset();
    mPosition += offset; 

    // if the collision pushed player up, then he is standing on an obstacle
    if (offset.y < 0) {
        mGrounded = true;
        mVelocity.y = 0;
    }
    // make player fall of ledges
    else if (offset.y == 0.0f) {
        mGrounded = false;
    }
}

void Player::GetInput() {
    Vector2 vel = Vector2(0.0f, 0.0f);

    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    bool left = keyboardState[SDL_SCANCODE_A];
    bool right = keyboardState[SDL_SCANCODE_D];
    bool space = keyboardState[SDL_SCANCODE_SPACE];

    switch(mMoveState) {
        case MoveState::Idle:
            // squat
            if (space) {
                mVelocity = Vector2(0.0f, 0.0f);
                mASprite->SetAnimation("squat"); 
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
                mVelocity.y = -mJumpSpeed; 
                mASprite->SetAnimation("jump");
                mMoveState = MoveState::Jump;
                mGrounded = false;
            }
            break;
        case MoveState::Jump:
            if (mGrounded) {
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
                mASprite->SetAnimation("squat");
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
                mASprite->SetAnimation("squat");
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
}

