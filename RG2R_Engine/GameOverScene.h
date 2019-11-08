#pragma once
#include "Scene.h"
#include "Object.h"
class GameOverScene :
	public Scene
{
private:
	Object* score_txt;
	Object* background;
	Object* button;
	Object* player;
public:
	GameOverScene(float);
	~GameOverScene();

	void OnUpdate();
};

