#pragma once
#include "Scene.h"
#include "Object.h"
class MainScene :
	public Scene
{
public:
	Object *obj1, *obj2;
	MainScene();
	~MainScene();
	void OnUpdate();
};

