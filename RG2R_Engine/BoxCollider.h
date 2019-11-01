#pragma once
#include "Collider.h"
class BoxCollider :
	public Collider
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

	void SetBoxColliderAnchor(Vec2F);
	void SetBoxColliderAnchor(float, float);
	void SetHorSize(float);
	void SetVerSize(float);
};

