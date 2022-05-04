#include "game.h"
#include "player.h"
#include "math.h"

Player::Player(Game* game)
	:Actor(game)
{
    mSpriteComponent = new SpriteComponent(this, 100);
	//mPlayerMove = new PlayerMove(this);
}

void Player::OnUpdate(float deltaTime)
{
}
