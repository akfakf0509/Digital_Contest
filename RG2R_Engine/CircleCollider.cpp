#include "stdafx.h"
#include "CircleCollider.h"
#include "Transform.h"

CircleCollider::CircleCollider()
{
	rad = 0;
}

CircleCollider::CircleCollider(float _rad) {
	rad = _rad;
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update() {

}

void CircleCollider::Render() {

}

void CircleCollider::Render(ViewRenderData&) {

}

float CircleCollider::GetRad() {
	return rad;
}

CircleCollider* CircleCollider::SetRad(float _rad) {
	rad = _rad;

	return this;
}