#include "stdafx.h"
#include "MainScene.h"
#include "Engine.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "CircleCollider.h"


MainScene::MainScene()
{
	obj1 = CreateObject();
	obj1->GetComponent<Transform>()
		->SetAnchor(16, 16);
	obj1->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Image1.png");
	obj1->AttachComponent<CircleCollider>()
		->SetRad(0.25f);
		//->SetHeightSize(0.25f)
		//->SetWidthSize(0.25f);

	obj2 = CreateObject();
	obj2->GetComponent<Transform>()
		->SetAnchor(16, 16);
	obj2->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Image2.png");
	obj2->AttachComponent<BoxCollider>()
		->SetHeightSize(0.25f)
		->SetWidthSize(0.25f);

	obj1->onUpdateListener = [=]() {
		Vec2F obj1_pos = obj1->GetComponent<Transform>()->GetPos();
		int h = 0, w = 0;
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_UP) == KeyState::KEYSTATE_STAY) 
			h = 1;
		else if (RG2R_InputM->GetKeyState(KeyCode::KEY_DOWN) == KeyState::KEYSTATE_STAY) 
			h = -1;

		if (RG2R_InputM->GetKeyState(KeyCode::KEY_RIGHT) == KeyState::KEYSTATE_STAY) 
			w = 1;
		else if (RG2R_InputM->GetKeyState(KeyCode::KEY_LEFT) == KeyState::KEYSTATE_STAY) 
			w = -1;

		obj1->GetComponent<Transform>()->SetPos(obj1_pos + Vec2F(w, h) * RG2R_TimeM->GetDeltaTime());

		if (RG2R_InputM->GetKeyState(KeyCode::KEY_Z) == KeyState::KEYSTATE_STAY)
			obj1->GetComponent<Transform>()->Rotate(1);
		else if (RG2R_InputM->GetKeyState(KeyCode::KEY_X) == KeyState::KEYSTATE_STAY)
			obj1->GetComponent<Transform>()->Rotate(-1);
	};
}


MainScene::~MainScene()
{
}

void MainScene::OnUpdate() {
	this->FixedUpdate();
}