#pragma once
#include "Collider.h"
class CircleCollider :
	public Collider
{
private:
	float rad = 0;
public:
	CircleCollider();
	CircleCollider(float);
	~CircleCollider();

	void Update();
	void Render();
	void Render(ViewRenderData&);

	std::type_index GetID() { return typeid(CircleCollider); }
	static std::type_index GetFamilyID(void) { return typeid(CircleCollider); }

	float GetRad();

	CircleCollider* SetRad(float);
};