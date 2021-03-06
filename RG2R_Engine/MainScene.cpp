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
#include "GameOverScene.h"
#include "TextRenderer.h"

MainScene::MainScene()
{
	rander = new RandomGenerator();

	player = new Player;
	AttachObject(player);


	score_txt = CreateObject();

	score_txt->AttachComponent<TextRenderer>()
		->SetText("Score : " + std::to_string(score))
		->SetTextColor(Color(1, 1, 1))
		->SetZ_index(1);
	score_txt->GetComponent<Transform>()
		->SetPos(-5,2.8f)
		->SetIsRelative(false);

	maincamera = GetMainCamera();

	for (int i = 0; i < 20; i++) {
		auto enemy = new Enemy;
		enemy->GetComponent<Transform>()->SetPos(rander->GetInt(player->GetComponent<Transform>()->GetPos().x - 10, player->GetComponent<Transform>()->GetPos().x + 10), rander->GetInt(player->GetComponent<Transform>()->GetPos().y - 10, player->GetComponent<Transform>()->GetPos().y + 10));
		AttachObject(enemy);
	}

	player->onCollisionEnterListener = [=](CollisionInfo* _collisioninfo) {
		if(!this->game_started){
			game_started = true;
			player->SetLimitPlayerShoot(true);
		}
		Vec2F p = player->GetComponent<Rigidbody>()->GetForce();
		Vec2F n = _collisioninfo->collisionline;

		player->GetComponent<Rigidbody>()->SetForce(p + 2 * n * (-p * n));
		_collisioninfo->object->GetComponent<Transform>()->SetPos(rander->GetInt(player->GetComponent<Transform>()->GetPos().x - 10, player->GetComponent<Transform>()->GetPos().x + 10), rander->GetInt(player->GetComponent<Transform>()->GetPos().y - 10, player->GetComponent<Transform>()->GetPos().y + 10));
		player->SetPlayerShootLimit(2);
		score++;
	};
}


MainScene::~MainScene()
{
}

void MainScene::OnUpdate() {
	if(game_started){
		score += RG2R_TimeM->GetDeltaTime();

		score_txt->GetComponent<TextRenderer>()
			->SetText("Score : " + std::to_string(score));
	}
	for (auto iter : this->FindObjectsByTag("Enemy")) {
		auto iter_transform = iter->GetComponent<Transform>();

		if (15 <= sqrt(pow(iter_transform->GetPos().x - player->GetComponent<Transform>()->GetPos().x, 2) + pow(iter_transform->GetPos().y - player->GetComponent<Transform>()->GetPos().y, 2))) {
			iter->GetComponent<Transform>()->SetPos(rander->GetInt(player->GetComponent<Transform>()->GetPos().x - 10, player->GetComponent<Transform>()->GetPos().x + 10), rander->GetInt(player->GetComponent<Transform>()->GetPos().y - 10, player->GetComponent<Transform>()->GetPos().y + 10));
		}
	}

	if (player_skill_cool > 0)
		player_skill_cool -= RG2R_TimeM->GetDeltaTime();
	if (player_skill_cool <= 0 && RG2R_InputM->GetKeyState(KeyCode::KEY_SPACE) == KeyState::KEYSTATE_ENTER) {
		player_skill_cool = player_skill_cool_const;
		Object* short_enemy = nullptr;
		for (auto iter : this->FindObjectsByTag("Enemy")) {
			auto iter_transform = iter->GetComponent<Transform>();

			if (!short_enemy)
				short_enemy = iter;
			if (sqrt(pow(short_enemy->GetComponent<Transform>()->GetPos().x - player->GetComponent<Transform>()->GetPos().x, 2) + pow(short_enemy->GetComponent<Transform>()->GetPos().y - player->GetComponent<Transform>()->GetPos().y, 2)) > sqrt(pow(iter_transform->GetPos().x - player->GetComponent<Transform>()->GetPos().x, 2) + pow(iter_transform->GetPos().y - player->GetComponent<Transform>()->GetPos().y, 2))) {
				short_enemy = iter;
			}
		}
		player->GetComponent<Rigidbody>()->SetForce((short_enemy->GetComponent<Transform>()->GetPos() - player->GetComponent<Transform>()->GetPos()) * 10);
	}

	Vec2F player2camera = player->GetComponent<Transform>()->GetPos() - maincamera->GetPos();

	maincamera->SetPos(maincamera->GetPos() + player2camera * 0.2f);
	
	if (game_started && abs(player->GetComponent<Rigidbody>()->GetForce().x) + abs(player->GetComponent<Rigidbody>()->GetForce().y) <= 0.1f) {
		RG2R_SceneM->ChangeScene(new GameOverScene(score));
	}

	this->FixedUpdate();
}