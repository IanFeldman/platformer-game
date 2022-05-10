#include "actor.h"
#include "collisioncomponent.h"
#include "game.h"
// CC Debug
#include <SDL2/SDL.h>
#include <iostream>

CollisionComponent::CollisionComponent(Actor* owner, int width, int height)
    :Component(owner)
    ,mColliderWidth(width)
    ,mColliderHeight(height)
{
}

// don't do this in update
// change so that collisions are only checked when the player moves,
// then use the minIntersect to adjust player position.
// right now this is running every frame for every actor which is not good.
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
            // check collision
            Collide(otherCC);
        }
    }
}

void CollisionComponent::Collide(CollisionComponent* otherCC) {
    // check collision
    int thisWidth = mColliderWidth * mOwner->GetScale();
    int thisHeight = mColliderHeight * mOwner->GetScale();
    int thisMinX = mOwner->GetPosition().x - thisWidth / 2;
    int thisMaxX = thisMinX + thisWidth;
    int thisMinY = mOwner->GetPosition().y - thisHeight / 2;
    int thisMaxY = thisMinY + thisHeight;

    int otherWidth = mColliderWidth * otherCC->GetOwner()->GetScale();
    int otherHeight = mColliderHeight * otherCC->GetOwner()->GetScale();
    int otherMinX = otherCC->GetOwner()->GetPosition().x - thisWidth / 2;
    int otherMaxX = otherMinX + otherWidth;
    int otherMinY = otherCC->GetOwner()->GetPosition().y - thisHeight / 2;
    int otherMaxY = otherMinY + otherHeight;

    bool overlapX = (otherMinX >= thisMinX && otherMinX <= thisMaxX) || (otherMaxX >= thisMinX && otherMaxX <= thisMaxX);
    bool overlapY = (otherMinY >= thisMinY && otherMinY <= thisMaxY) || (otherMaxY >= thisMinY && otherMaxY <= thisMaxY);
    bool collision = overlapX && overlapY;

    if (collision) {
        std::cout<<"collision"<<std::endl;
    }
}

void CollisionComponent::Debug() {
    // debug draw our own collider
    SDL_Rect r;
    r.w = mColliderWidth * mOwner->GetScale();
    r.h = mColliderHeight * mOwner->GetScale();
    r.x = mOwner->GetPosition().x - r.w / 2;
    r.y = mOwner->GetPosition().y - r.h / 2;
    mOwner->GetGame()->GetRenderer()->DrawRectangle(r);
}

