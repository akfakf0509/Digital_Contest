#pragma once
#include "Object.h"
class Player :
	public Object
{
private:
	Vec2F clicked_point = { 0,0 };
public:
	Player();
	~Player();

	void OnUpdate();
	void OnCollisionEnter(CollisionInfo*);
};

