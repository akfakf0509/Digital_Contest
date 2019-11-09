#include "stdafx.h"
#include "Player.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Rigidbody.h"
#include "Engine.h"

Player::Player()
{
	GetComponent<Transform>()
		->SetAnchor(16, 16);
	AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Image3.png");
	AttachComponent<CircleCollider>()
		->SetRad(0.25f);
	AttachComponent<Rigidbody>();
}

Player::~Player()
{
}

Player* Player::SetPlayerShootLimit(int _shoot_limit) {
	player_shoot_limit = _shoot_limit;

	return this;
}

Player* Player::SetLimitPlayerShoot(bool _limit) {
	limit_shoot_count = _limit;

	return this;
}

int Player::GetPlayerShootLimit() {
	return player_shoot_limit;
}

bool Player::GetLimitPlayerShoot() {
	return limit_shoot_count;
}

void Player::OnUpdate() {
	if (player_shoot_limit > 0 && RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER) {
		clicked_point = RG2R_InputM->GetMouseWorldPos();
	}
	if (player_shoot_limit > 0 && RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_STAY) {
		Vec2F vec_distance = clicked_point - RG2R_InputM->GetMouseWorldPos() - Vec2F(0,1);
		vec_distance = vec_distance.Normalize();

		float angle = ToDegree(acos(vec_distance.x));

		printf("%f\n",angle);
	}
	if (player_shoot_limit > 0 && RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT) {
		Vec2F vec_distance = clicked_point - RG2R_InputM->GetMouseWorldPos();
		float distance = sqrt(pow(vec_distance.x, 2) + pow(vec_distance.y, 2));
		if (distance > 5)
			distance = 5;
		if (vec_distance != Vec2F(0, 0)) {
			GetComponent<Rigidbody>()->AddForce(vec_distance.Normalize() * distance * 10);
			player_shoot_limit--;
		}
	}

	if(!limit_shoot_count)
		player_shoot_limit = 2;
}