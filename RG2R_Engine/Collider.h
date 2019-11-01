#pragma once
#include "Component.h"
#include "ColliderType.h"
class Collider :
	public Component
{
private:
	ColliderType collidertype;
public:
	Collider();
	~Collider();

	ColliderType GetColliderType();
};

