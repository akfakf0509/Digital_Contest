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
		->SetAnchor(16, 16)
		->SetPos(1, 1);
	AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Image3.png");
	AttachComponent<CircleCollider>()
		->SetRad(0.25f);
	AttachComponent<Rigidbody>();
}

Player::~Player()
{
}

void Player::OnUpdate() {
	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER) {
		clicked_point = RG2R_InputM->GetMouseWorldPos();
	}
	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT) {
		Vec2F vec_distance = clicked_point - RG2R_InputM->GetMouseWorldPos();
		float distance = sqrt(pow(vec_distance.x, 2) + pow(vec_distance.y, 2));
		if (distance > 100)
			distance = 100;

		GetComponent<Rigidbody>()->AddForce(vec_distance.Normalize() * distance * 10);
	}
}

void Player::OnCollisionEnter(CollisionInfo* _collisioninfo) {
	Vec2F p = GetComponent<Rigidbody>()->GetForce();
	Vec2F n = _collisioninfo->collisionline;

	GetComponent<Rigidbody>()->SetForce(p + 2 * n * (-p * n));

	_collisioninfo->object->SetIsEnable(false);
}