#pragma once
#include "Collider.h"
class CircleCollider :
	public Collider
{
private:
	Vec2F anchor = { 0,0 };
	float rad = 0;
public:
	CircleCollider();
	CircleCollider(float);
	~CircleCollider();

	std::type_index GetID() { return typeid(CircleCollider); }

	Vec2F GetCircleColliderAnchor();
	float GetRad();

	CircleCollider* SetCircleColliderAnchor(Vec2F);
	CircleCollider* SetCircleColliderAnchor(float, float);
	CircleCollider* SetRad(float);
};