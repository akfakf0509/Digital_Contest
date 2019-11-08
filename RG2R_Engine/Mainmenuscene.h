#pragma once
#include "Scene.h"
#include "Object.h"
class Mainmenuscene :
	public Scene
{
private:
	Object* background;
	Object* button;
	Object* player;
public:
	Mainmenuscene();
	~Mainmenuscene();

	void OnUpdate();
};

