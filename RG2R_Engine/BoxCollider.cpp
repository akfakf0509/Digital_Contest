#include "stdafx.h"
#include "BoxCollider.h"
#include "Transform.h"

BoxCollider::BoxCollider()
{
	anchor = GetOwner()->GetComponent<Transform>()->GetAnchor();
}

BoxCollider::BoxCollider(float _ver_size, float _hor_size) {
	anchor = GetOwner()->GetComponent<Transform>()->GetAnchor();
	ver_size = _ver_size;
	hor_size = _hor_size;
}


BoxCollider::~BoxCollider()
{
}

Vec2F BoxCollider::GetBoxColliderAnchor() {
	return anchor;
}

float BoxCollider::GetHorSize() {
	return hor_size;
}

float BoxCollider::GetVerSize() {
	return ver_size;
}

void BoxCollider::SetBoxColliderAnchor(Vec2F _anchor) {
	anchor = _anchor;
}

void BoxCollider::SetBoxColliderAnchor(float _x, float _y) {
	anchor = Vec2F(_x, _y);
}

void BoxCollider::SetHorSize(float _hor_size) {
	hor_size = _hor_size;
}

void BoxCollider::SetVerSize(float _ver_size) {
	ver_size = _ver_size;
}