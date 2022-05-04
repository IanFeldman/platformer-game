#pragma once
#include "math.h"
#include <vector>

enum class ActorState
{
	Active,
	Paused,
	Destroy
};

class Actor
{
public:
	Actor(class Game* game);
    // overridable destructor
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);

	// Getters/setters
	const Vector2& GetPosition() const { return mPosition; } // reference to vector2
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	ActorState GetState() const { return mState; }
	void SetState(ActorState state) { mState = state; }

	const Vector2 GetForward() const { return Vector2(cos(mRotation), -sin(mRotation)); }

	class Game* GetGame() { return mGame; }

	// Adds component to Actor (this is automatically called in the component constructor)
	void AddComponent(class Component* c);

	// Returns component of type T, or null if doesn't exist
	template <typename T>
	T* GetComponent() const
	{
		for (auto c : mComponents)
		{
			T* t = dynamic_cast<T*>(c);
			if (t != nullptr)
			{
				return t;
			}
		}

		return nullptr;
	}

protected:
	// Any actor-specific update code (overridable)
	virtual void OnUpdate(float deltaTime);

	class Game* mGame;
	// Actor's state
	ActorState mState;

	// Transform
	Vector2 mPosition;
	float mScale;
	float mRotation;

	// Components
	std::vector<class Component*> mComponents;
};
