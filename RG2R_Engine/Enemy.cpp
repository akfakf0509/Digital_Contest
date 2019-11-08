#include "stdafx.h"
#include "Enemy.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "Rigidbody.h"

Enemy::Enemy()
{
	GetComponent<Transform>()
		->SetAnchor(16, 16);
	AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Image2.png");
	AttachComponent<BoxCollider>()
		->SetWidthSize(0.25f)
		->SetHeightSize(0.25f);
	AttachComponent<Rigidbody>();
}


Enemy::~Enemy()
{
}
