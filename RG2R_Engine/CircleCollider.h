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

	void Update() = 0;
	void Render() = 0;
	void Render(ViewRenderData&) = 0;

	std::type_index GetID() { return typeid(CircleCollider); }

	float GetRad();

	CircleCollider* SetRad(float);
};