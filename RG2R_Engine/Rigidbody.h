#pragma once
#include "Component.h"
class Rigidbody :
	public Component
{
public:
	Rigidbody();
	~Rigidbody();

	void Update();
	void Render();
	void Render(ViewRenderData&);

	std::type_index GetID(void) { return typeid(Rigidbody); }
	static std::type_index GetFamilyID(void) { return typeid(Rigidbody); }
};

