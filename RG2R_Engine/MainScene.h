#pragma once
#include "Scene.h"
#include "Object.h"
#include "Camera.h"
class MainScene :
	public Scene
{
private:
	Object* player;
	Camera* maincamera;

	float respawn_cool = 0;
	const float respawn_cool_const = 1;
public:
	MainScene();
	~MainScene();
	void OnUpdate();
};

