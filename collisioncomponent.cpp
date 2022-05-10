#include "actor.h"
#include "collisioncomponent.h"
#include "game.h"
#include "math.h"
// CC Debug
#include <SDL2/SDL.h>
#include <iostream>

CollisionComponent::CollisionComponent(Actor* owner, int width, int height)
    :Component(owner)
    ,mColliderWidth(width)
    ,mColliderHeight(height)
{
}

Vector2 CollisionComponent::GetMinOffset() {
    Vector2 minOffset = Vector2(0.0f, 0.0f);

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
            minOffset += Collide(otherCC);
        }
    }

    return minOffset;
}

Vector2 CollisionComponent::Collide(CollisionComponent* otherCC) {
    // check collision
    int thisWidth = mColliderWidth * mOwner->GetScale();
    int thisHeight = mColliderHeight * mOwner->GetScale();
    int thisMinX = mOwner->GetPosition().x - thisWidth / 2;
    int thisMaxX = thisMinX + thisWidth;
    int thisMinY = mOwner->GetPosition().y - thisHeight / 2;
    int thisMaxY = thisMinY + thisHeight;

    int otherWidth = otherCC->GetWidth() * otherCC->GetOwner()->GetScale();
    int otherHeight = otherCC->GetHeight() * otherCC->GetOwner()->GetScale();
    int otherMinX = otherCC->GetOwner()->GetPosition().x - otherWidth / 2;
    int otherMaxX = otherMinX + otherWidth;
    int otherMinY = otherCC->GetOwner()->GetPosition().y - otherHeight / 2;
    int otherMaxY = otherMinY + otherHeight;

    bool overlapX = (otherMinX >= thisMinX && otherMinX <= thisMaxX) || (otherMaxX >= thisMinX && otherMaxX <= thisMaxX);
    bool overlapY = (otherMinY >= thisMinY && otherMinY <= thisMaxY) || (otherMaxY >= thisMinY && otherMaxY <= thisMaxY);
    bool collision = overlapX && overlapY;

    if (collision) {
        int moveX = 0;
        int moveY = 0;

        // diff in centers
        int deltaX = mOwner->GetPosition().x - otherCC->GetOwner()->GetPosition().x;
        int expectedDistX = thisWidth / 2 + otherWidth / 2;
        moveX = expectedDistX - std::abs(deltaX);

        // same for y
        int deltaY = mOwner->GetPosition().y - otherCC->GetOwner()->GetPosition().y;
        int expectedDistY = thisHeight / 2 + otherHeight / 2;
        moveY = expectedDistY - std::abs(deltaY);

        // x move is smaller. default to x when equal
        if (moveX <= moveY) {
            if (deltaX < 0) {
                return Vector2(-moveX, 0.0f);
            }
            return Vector2(moveX, 0.0f);
        }
        // y move is smaller 
        if (deltaY < 0) {
            return Vector2(0.0f, -moveY);
        }
        return Vector2(0.0f, moveY);
    }

    // no overlap if no collision
    return Vector2(0.0f, 0.0f);
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

