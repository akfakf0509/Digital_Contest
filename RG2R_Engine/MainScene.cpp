#include "stdafx.h"
#include "MainScene.h"
#include "Engine.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Rigidbody.h"
#include "Player.h"
#include "Enemy.h"
#include "RandomGenerator.h"

MainScene::MainScene()
{
	player = new Player;

	AttachObject(player);

	maincamera = GetMainCamera();

	for (int i = 0; i < 20; i++) {
		respawn_cool = respawn_cool_const;
		auto rander = new RandomGenerator();
		auto enemy = new Enemy;
		enemy->GetComponent<Transform>()->SetPos(rander->GetInt(player->GetComponent<Transform>()->GetPos().x - 10, player->GetComponent<Transform>()->GetPos().x + 10), rander->GetInt(player->GetComponent<Transform>()->GetPos().y - 10, player->GetComponent<Transform>()->GetPos().y + 10));
		AttachObject(enemy);
	}
}


MainScene::~MainScene()
{
}

void MainScene::OnUpdate() {
	respawn_cool -= RG2R_TimeM->GetDeltaTime();

	if (respawn_cool < 0) {
		respawn_cool = respawn_cool_const;
		auto rander = new RandomGenerator();
		auto enemy = new Enemy;
		enemy->GetComponent<Transform>()->SetPos(rander->GetInt(player->GetComponent<Transform>()->GetPos().x - 10, player->GetComponent<Transform>()->GetPos().x + 10), rander->GetInt(player->GetComponent<Transform>()->GetPos().y - 10, player->GetComponent<Transform>()->GetPos().y + 10));
		AttachObject(enemy);
	}

	Vec2F player2camera = player->GetComponent<Transform>()->GetPos() - maincamera->GetPos();

	maincamera->SetPos(maincamera->GetPos() + player2camera * 0.2);

	this->FixedUpdate();
}