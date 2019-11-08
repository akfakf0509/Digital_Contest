#pragma once
#include "Scene.h"
#include "Object.h"
#include "Camera.h"
#include "RandomGenerator.h"
class MainScene :
	public Scene
{
private:
	Object* player;
	Camera* maincamera;
	RandomGenerator* rander;

	float player_skill_cool = 0;
	const float player_skill_cool_const = 3;
public:
	MainScene();
	~MainScene();
	void OnUpdate();
};

