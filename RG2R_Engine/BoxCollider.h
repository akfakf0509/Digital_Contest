#pragma once
#include "Collider.h"
class BoxCollider :
	public Collider
{
private:
	float width = 0, height = 0;
public:
	BoxCollider();
	BoxCollider(float, float);
	~BoxCollider();

	void Update();
	void Render();
	void Render(ViewRenderData&);

	std::type_index GetID() { return typeid(BoxCollider); }
	static std::type_index GetFamilyID(void) { return typeid(BoxCollider); }

	float GetWidthSize();
	float GetHeightSize();

	BoxCollider* SetWidthSize(float);
	BoxCollider* SetHeightSize(float);
};

