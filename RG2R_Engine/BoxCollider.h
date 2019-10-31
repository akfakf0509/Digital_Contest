#pragma once
#include "Component.h"
class BoxCollider :
	public Component
{
private:
	Vec2F anchor = { 0,0 };
	float hor_size = 0, ver_size = 0;
public:
	BoxCollider();
	BoxCollider(float, float);
	~BoxCollider();

	Vec2F GetBoxColliderAnchor();
	float GetHorSize();
	float GetVerSize();

	BoxCollider* SetBoxColliderAnchor(Vec2F);
	BoxCollider* SetBoxColliderAnchor(float, float);
	BoxCollider* SetHorSize(float);
	BoxCollider* SetVerSize(float);
};

