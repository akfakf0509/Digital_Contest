#pragma once
#include "Component.h"
class Collider :
	public Component
{
public:
	Collider();
	~Collider();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Render(ViewRenderData&) = 0;

	virtual std::type_index GetID() { return typeid(Collider); }
	static std::type_index GetFamilyID(void) { return typeid(Collider); }
};

