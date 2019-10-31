#include "stdafx.h"
#include "CircleCollider.h"
#include "Transform.h"

CircleCollider::CircleCollider()
{
	anchor = GetOwner()->GetComponent<Transform>()->GetAnchor();
}

CircleCollider::CircleCollider(float _rad) {
	anchor = GetOwner()->GetComponent<Transform>()->GetAnchor();
	rad = _rad;
}

CircleCollider::~CircleCollider()
{
}

Vec2F CircleCollider::GetCircleColliderAnchor() {
	return anchor;
}

float CircleCollider::GetRad() {
	return rad;
}

CircleCollider* CircleCollider::SetCircleColliderAnchor(Vec2F _anchor) {
	anchor = _anchor;

	return this;
}

CircleCollider* CircleCollider::SetCircleColliderAnchor(float _x, float _y) {
	anchor = Vec2F(_x, _y);

	return this;
}

CircleCollider* CircleCollider::SetRad(float _rad) {
	rad = _rad;
}