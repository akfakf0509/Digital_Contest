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
	acceleration = acceleration - acceleration / calculation_speed;
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

Rigidbody* Rigidbody::SetForce(float _x, float _y) {
	acceleration = Vec2F(_x, _y);

	return this;
}

Rigidbody* Rigidbody::AddForce(Vec2F _acceleration) {
	acceleration += _acceleration;

	return this;
}

Rigidbody* Rigidbody::AddForce(float _x, float _y) {
	acceleration += Vec2F(_x, _y);

	return this;
}

Rigidbody* Rigidbody::SetCalculationSpeed(float _calculation_speed) {
	calculation_speed = _calculation_speed;

	return this;
}

Vec2F Rigidbody::GetForce() {
	return acceleration;
}

float Rigidbody::GetCalculationSpeed() {
	return calculation_speed;
}