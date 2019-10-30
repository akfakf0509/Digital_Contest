#include "stdafx.h"
#include "MainScene.h"
#include "Engine.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "Transform.h"


MainScene::MainScene()
{
	obj1 = CreateObject();
	obj1->GetComponent<Transform>()
		->SetAnchor(16, 16);
	obj1->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Image1.png");

	obj2 = CreateObject();
	obj2->GetComponent<Transform>()
		->SetAnchor(16, 16);
	obj2->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Image2.png");

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
	bool is_crash = 1;

	Transform *obj1_transform = obj1->GetComponent<Transform>();
	Transform *obj2_transform = obj2->GetComponent<Transform>();


	Vec2F a1(cos(obj1_transform->GetRot()), sin(obj1_transform->GetRot()));
	Vec2F a2(-sin(obj1_transform->GetRot()), cos(obj1_transform->GetRot()));
	Vec2F a3(cos(obj2_transform->GetRot()), sin(obj2_transform->GetRot()));
	Vec2F a4(-sin(obj2_transform->GetRot()), cos(obj2_transform->GetRot()));

	Vec2F l = obj1_transform->GetPos() - obj2_transform->GetPos();

	float r1, r2, r3, r4;

	r1 = 0.25f*fabs(a1.Dot(a1));
	r2 = 0.25f*fabs(a2.Dot(a1));
	r3 = 0.25f*fabs(a3.Dot(a1));
	r4 = 0.25f*fabs(a4.Dot(a1));
	if (r1 + r2 + r3 + r4 <= fabs(l.Dot(a1)))
		is_crash = 0;

	r1 = 0.25f*fabs(a1.Dot(a2));
	r2 = 0.25f*fabs(a2.Dot(a2));
	r3 = 0.25f*fabs(a3.Dot(a2));
	r4 = 0.25f*fabs(a4.Dot(a2));
	if (r1 + r2 + r3 + r4 <= fabs(l.Dot(a2)))
		is_crash = 0;

	r1 = 0.25f*fabs(a1.Dot(a3));
	r2 = 0.25f*fabs(a2.Dot(a3));
	r3 = 0.25f*fabs(a3.Dot(a3));
	r4 = 0.25f*fabs(a4.Dot(a3));
	if (r1 + r2 + r3 + r4 <= fabs(l.Dot(a3)))
		is_crash = 0;

	r1 = 0.25f*fabs(a1.Dot(a4));
	r2 = 0.25f*fabs(a2.Dot(a4));
	r3 = 0.25f*fabs(a3.Dot(a4));
	r4 = 0.25f*fabs(a4.Dot(a4));
	if (r1 + r2 + r3 + r4 <= fabs(l.Dot(a4)))
		is_crash = 0;

	printf("%d %d\n", (int)obj1_transform->GetRot(), (int)obj2_transform->GetRot());
	if (is_crash)
		printf("Crash!");
}