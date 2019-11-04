#include "stdafx.h"
#include "BoxCollider.h"
#include "Transform.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(float _width, float _height) {
	width = _width;
	height = _height;
}


BoxCollider::~BoxCollider()
{
}

void BoxCollider::Update() {

}

void BoxCollider::Render() {

}

void BoxCollider::Render(ViewRenderData&) {

}

float BoxCollider::GetWidthSize() {
	return width;
}

float BoxCollider::GetHeightSize() {
	return height;
}

BoxCollider* BoxCollider::SetWidthSize(float _width) {
	width = _width;

	return this;
}

BoxCollider* BoxCollider::SetHeightSize(float _height) {
	height = _height;

	return this;
}