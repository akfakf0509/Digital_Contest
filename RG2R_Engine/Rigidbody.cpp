#include "stdafx.h"
#include "Rigidbody.h"
#include "Engine.h"
#include "Transform.h"


Rigidbody::Rigidbody()
{
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update() {
	acceleration = acceleration - acceleration / 10;
	velocity = acceleration * RG2R_TimeM->GetDeltaTime();
	this->GetOwner()->GetComponent<Transform>()
		->SetPos(this->GetOwner()->GetComponent<Transform>()->GetPos() + velocity);
}

void Rigidbody::Render() {

}

void Rigidbody::Render(ViewRenderData&) {

}

Rigidbody* Rigidbody::SetForce(Vec2F _acceleration) {
	acceleration = _acceleration;

	return this;
}

Vec2F Rigidbody::GetForce() {
	return acceleration;
}