#include "stdafx.h"
#include "GameOverScene.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Engine.h"
#include "Player.h"
#include "Mainmenuscene.h"
#include "TextRenderer.h"

GameOverScene::GameOverScene(float _score)
{
	background = CreateObject();

	background->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Gameover.png");
	background->GetComponent<Transform>()
		->SetAnchor(640, 360)
		->SetScale(0.5f, 0.5f);

	button = CreateObject();

	button->GetComponent<Transform>()
		->SetAnchor(16, 16)
		->SetPos(3.9f, -1.7f);
	button->AttachComponent<BoxCollider>()
		->SetWidthSize(0.25f)
		->SetHeightSize(0.25f);
	button->AttachComponent<Rigidbody>();

	player = new Player();

	AttachObject(player);

	score_txt = CreateObject();

	score_txt->AttachComponent<TextRenderer>()
		->SetText("Score : " + std::to_string(_score))
		->SetTextColor(Color(1, 1, 1))
		->SetZ_index(1);
	score_txt->GetComponent<Transform>()
		->SetPos(-5, 2.8f)
		->SetIsRelative(false);

	player->onUpdateListener = [=]() {
		auto player_transform = player->GetComponent<Transform>();
		if (player_transform->GetPos().x > 5 || player_transform->GetPos().x < -5 || player_transform->GetPos().y > 3 || player_transform->GetPos().y < -3) {
			player_transform->SetPos(0, 0);
		}
	};

	player->onCollisionEnterListener = [=](CollisionInfo* _collision) {
		RG2R_SceneM->ChangeScene(new Mainmenuscene);
	};
}


GameOverScene::~GameOverScene()
{
}

void GameOverScene::OnUpdate() {
	FixedUpdate();
}