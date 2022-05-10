#include "actor.h"
#include "collisioncomponent.h"
#include "game.h"
// CC Debug
#include <SDL2/SDL.h>

CollisionComponent::CollisionComponent(Actor* owner, int width, int height)
    :Component(owner)
    ,mColliderWidth(width)
    ,mColliderHeight(height)
{
}

void CollisionComponent::Update(float deltaTime) {
    // iterate over every actor
    for (Actor* actor : mOwner->GetGame()->GetActors()) {
        // skip itself
        if (actor == mOwner) {
            continue;
        }
        // check if it has a collision component
        CollisionComponent* otherCC = actor->GetComponent<CollisionComponent>();
        if (otherCC != nullptr) {
            Collide(otherCC);
        }
    }
}

void CollisionComponent::Collide(CollisionComponent* otherCC) {}

void CollisionComponent::Debug() {
    // debug draw our own collider
    SDL_Rect r;
    r.w = mColliderWidth * mOwner->GetScale();
    r.h = mColliderHeight * mOwner->GetScale();
    r.x = mOwner->GetPosition().x - r.w / 2;
    r.y = mOwner->GetPosition().y - r.h / 2;
    mOwner->GetGame()->GetRenderer()->DrawRectangle(r);
}

