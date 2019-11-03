#pragma once
#include "Component.h"
class Collider :
	public Component
{
public:
	Collider();
	~Collider();

	virtual std::type_index GetID() { return typeid(Collider); }
};

