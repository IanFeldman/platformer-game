#include "animatedsprite.h"
#include "game.h"
#include "player.h"
#include "math.h"

Player::Player(Game* game)
	:Actor(game)
    ,mMoveSpeed(500.0f)
{
    //mSpriteComponent = new SpriteComponent(this, 100);
    //mSpriteComponent->SetTexture(mGame->GetTexture("boid.png"));
    mASprite = new AnimatedSprite(this, 100);
    mASprite->SetFPS(5.0f);
    // idle
	std::vector<SDL_Texture*> idleAnim{
		mGame->GetTexture("assets/player/idle/idle1.png"),
		mGame->GetTexture("assets/player/idle/idle2.png"),
		mGame->GetTexture("assets/player/idle/idle3.png"),
		mGame->GetTexture("assets/player/idle/idle4.png"),
		mGame->GetTexture("assets/player/idle/idle5.png"),
		mGame->GetTexture("assets/player/idle/idle6.png"),
		mGame->GetTexture("assets/player/idle/idle7.png"),
		mGame->GetTexture("assets/player/idle/idle8.png")};
    mASprite->AddAnimation("idle", idleAnim);
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
        vel.x -= mMoveSpeed;
    }
    else if (!left && right) {
        vel.x += mMoveSpeed;
    }

    return vel;
}
