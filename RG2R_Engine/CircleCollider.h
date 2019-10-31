#pragma once
#include "Component.h"
class CircleCollider :
	public Component
{
private:
	Vec2F anchor = { 0,0 };
	float rad = 0;
public:
	CircleCollider();
	CircleCollider(float);
	~CircleCollider();

	Vec2F GetCircleColliderAnchor();
	float GetRad();

	CircleCollider* SetCircleColliderAnchor(Vec2F);
	CircleCollider* SetCircleColliderAnchor(float, float);
	CircleCollider* SetRad(float);
};