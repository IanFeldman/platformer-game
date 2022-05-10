#pragma once
#include "component.h"

class CollisionComponent : public Component
{
public:
    CollisionComponent(class Actor* owner, int width, int height);

    void Update(float deltaTime) override;
    void Collide(class CollisionComponent* otherCC);

    void Debug();

protected:
    int mColliderWidth;
    int mColliderHeight;

};

