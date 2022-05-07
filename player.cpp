#include "animatedsprite.h"
#include "game.h"
#include "player.h"
#include "math.h"

Player::Player(Game* game)
	:Actor(game)
    ,mMoveSpeed(300.0f)
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
}

void Player::OnUpdate(float deltaTime)
{
   Vector2 vel = GetInput(); 
   mPosition += vel * deltaTime;
}

Vector2 Player::GetInput() {
    Vector2 vel = Vector2(0.0f, 0.0f);

    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    bool left = keyboardState[SDL_SCANCODE_A];
    bool right = keyboardState[SDL_SCANCODE_D];
    if (left && !right) {
        // set velocity
        vel.x -= mMoveSpeed;
        // set animation
        if (mASprite->GetAnimation() != "run-left") {
            mASprite->SetAnimation("run-left", false);
        }
    }
    else if (!left && right) {
        // set vel
        vel.x += mMoveSpeed;
        // set animation
        if (mASprite->GetAnimation() != "run-right") {
            mASprite->SetAnimation("run-right", false);
        }
    }
    else {
        // set animation
        if (mASprite->GetAnimation() != "idle") {
            mASprite->SetAnimation("idle", false);
        }
    }

    return vel;
}
