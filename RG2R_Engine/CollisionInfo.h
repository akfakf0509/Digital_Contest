#pragma once
#include "Object.h"
typedef struct CollisionInfo {
	Object *object = nullptr;
	Vec2F collisionline = { 0,0 };
}CollisionInfo;