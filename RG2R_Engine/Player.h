#pragma once
#include "Object.h"
class Player :
	public Object
{
private:
	Object* arrow;

	Vec2F clicked_point = { 0,0 };

	bool limit_shoot_count = false;

	int player_shoot_limit = 2;
	const int player_shoot_limit_const = 2;
public:
	Player();
	~Player();

	Player* SetPlayerShootLimit(int);
	Player* SetLimitPlayerShoot(bool);

	int GetPlayerShootLimit();
	bool GetLimitPlayerShoot();

	void OnUpdate();
};

