#pragma once
#include "Scene.h"
#include "Object.h"
#include "Player.h"
#include "Camera.h"
#include "RandomGenerator.h"
class MainScene :
	public Scene
{
private:
	Object* score_txt;
	Player* player;
	Camera* maincamera;
	RandomGenerator* rander;

	float score = 0;

	float player_skill_cool = 0;
	const float player_skill_cool_const = 10;

public:
	bool game_started = false;

	MainScene();
	~MainScene();

	void OnUpdate();
};

