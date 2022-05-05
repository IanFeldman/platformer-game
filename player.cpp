#include "game.h"
#include "player.h"
#include "math.h"

Player::Player(Game* game)
	:Actor(game)
    ,mMoveSpeed(500.0f)
{
    mSpriteComponent = new SpriteComponent(this, 100);
    mSpriteComponent->SetTexture(mGame->GetTexture("boid.png"));
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
