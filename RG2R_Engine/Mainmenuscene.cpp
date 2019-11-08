#include "stdafx.h"
#include "Mainmenuscene.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Player.h"
#include "Engine.h"
#include "MainScene.h"

Mainmenuscene::Mainmenuscene()
{
	background = CreateObject();

	background->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Mainmenu.png");
	background->GetComponent<Transform>()
		->SetAnchor(640, 360)
		->SetScale(0.5f, 0.5f);

	button = CreateObject();

	button->GetComponent<Transform>()
		->SetAnchor(16, 16)
		->SetPos(0.7f, 1.3f);
	button->AttachComponent<BoxCollider>()
		->SetWidthSize(0.25f)
		->SetHeightSize(0.25f);
	button->AttachComponent<Rigidbody>();

	player = new Player();

	AttachObject(player);

	player->onUpdateListener = [=]() {
		auto player_transform = player->GetComponent<Transform>();
		if (player_transform->GetPos().x > 2 || player_transform->GetPos().x < -2 || player_transform->GetPos().y > 2 || player_transform->GetPos().y < -2) {
			player_transform->SetPos(0, 0);
		}
	};

	player->onCollisionEnterListener = [=](CollisionInfo* _collision) {
		RG2R_SceneM->ChangeScene(new MainScene);
	};
}


Mainmenuscene::~Mainmenuscene()
{
}

void Mainmenuscene::OnUpdate() {
	FixedUpdate();
}