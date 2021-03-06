#include "stdafx.h"
#include "Scene.h"
#include "Settings.h"
#include "Engine.h"
#include "ViewRenderData.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "CollisionInfo.h"

Scene::Scene()
{
	mainCamera = new Camera;
}

Scene::~Scene()
{
	ApplyListener(onDestroyListener);
	OnDestroy();

	for (auto iter : objects)
	{
		delete iter;
	}
	for (auto iter : cameras)
	{
		delete iter;
	}

	delete mainCamera;
}

void Scene::Update()
{
	for (auto iter : objects)
	{
		if (iter->GetIsEnable())
		{
			if (iter->isFirstUpdate)
			{
				ApplyListener(iter->onStartListener);
				iter->OnStart();

				ApplyListener(iter->onFirstUpdateBeforeListener);
				iter->OnFirstUpdateBefore();
			}
			ApplyListener(iter->onUpdateBeforeListener);
			iter->OnUpdateBefore();

			iter->Update();

			if (iter->isFirstUpdate)
			{
				ApplyListener(iter->onFirstUpdateListener);
				iter->OnFirstUpdate();

				iter->isFirstUpdate = false;
			}
			ApplyListener(iter->onUpdateListener);
			iter->OnUpdate();
		}
	}

	for (auto iter : cameras)
	{
		iter->Update();
	}
}

void Scene::FixedUpdate() {
	std::vector<Object*>fixed_objects;

	for (auto iter : objects) {
		if (iter->GetComponent<Rigidbody>())
			fixed_objects.push_back(iter);
	}
	for (auto iter1 : fixed_objects) {
		auto iter1circlecollider = iter1->GetComponent<CircleCollider>();
		auto iter1boxcollider = iter1->GetComponent<BoxCollider>();
		if (iter1->GetIsEnable() && (iter1circlecollider || iter1boxcollider)) {
			for (auto iter2 : fixed_objects) {
				auto iter2circlecollider = iter2->GetComponent<CircleCollider>();
				auto iter2boxcollider = iter2->GetComponent<BoxCollider>();
				if (iter2->GetIsEnable() && iter1 != iter2 && (iter2circlecollider || iter2boxcollider)) {
					Transform *obj1_transform = iter1->GetComponent<Transform>();
					Transform *obj2_transform = iter2->GetComponent<Transform>();
					if (iter1boxcollider && iter2boxcollider) {
						bool is_crash = 1;

						Vec2F a1(cos(obj1_transform->GetRot()), sin(obj1_transform->GetRot()));
						Vec2F a2(-sin(obj1_transform->GetRot()), cos(obj1_transform->GetRot()));
						Vec2F a3(cos(obj2_transform->GetRot()), sin(obj2_transform->GetRot()));
						Vec2F a4(-sin(obj2_transform->GetRot()), cos(obj2_transform->GetRot()));

						Vec2F l = obj1_transform->GetPos() - obj2_transform->GetPos();

						float r1, r2, r3, r4;

						r1 = iter1boxcollider->GetWidthSize() * fabs(a1.Dot(a1));
						r2 = iter1boxcollider->GetHeightSize() * fabs(a2.Dot(a1));
						r3 = iter2boxcollider->GetWidthSize() * fabs(a3.Dot(a1));
						r4 = iter2boxcollider->GetHeightSize() * fabs(a4.Dot(a1));
						if (r1 + r2 + r3 + r4 <= fabs(l.Dot(a1)))
							is_crash = 0;

						r1 = iter1boxcollider->GetWidthSize() * fabs(a1.Dot(a2));
						r2 = iter1boxcollider->GetHeightSize() * fabs(a2.Dot(a2));
						r3 = iter2boxcollider->GetWidthSize() * fabs(a3.Dot(a2));
						r4 = iter2boxcollider->GetHeightSize() * fabs(a4.Dot(a2));
						if (r1 + r2 + r3 + r4 <= fabs(l.Dot(a2)))
							is_crash = 0;

						r1 = iter1boxcollider->GetWidthSize() * fabs(a1.Dot(a3));
						r2 = iter1boxcollider->GetHeightSize() * fabs(a2.Dot(a3));
						r3 = iter2boxcollider->GetWidthSize() * fabs(a3.Dot(a3));
						r4 = iter2boxcollider->GetHeightSize() * fabs(a4.Dot(a3));
						if (r1 + r2 + r3 + r4 <= fabs(l.Dot(a3)))
							is_crash = 0;

						r1 = iter1boxcollider->GetWidthSize() * fabs(a1.Dot(a4));
						r2 = iter1boxcollider->GetHeightSize() * fabs(a2.Dot(a4));
						r3 = iter2boxcollider->GetWidthSize() * fabs(a3.Dot(a4));
						r4 = iter2boxcollider->GetHeightSize() * fabs(a4.Dot(a4));
						if (r1 + r2 + r3 + r4 <= fabs(l.Dot(a4)))
							is_crash = 0;

						if (is_crash) {
							if (iter1->isFirstCollision) {
								iter1->OnCollisionEnter(new CollisionInfo{ iter2 });
								iter1->isFirstCollision = false;
							}
							else {
								iter1->OnCollisionStay(new CollisionInfo{ iter2 });
							}

							if (iter2->isFirstCollision) {
								iter2->OnCollisionEnter(new CollisionInfo{ iter1 });
								iter2->isFirstCollision = false;
							}
							else {
								iter2->OnCollisionStay(new CollisionInfo{ iter1 });
							}
						}
						else {
							if (!iter1->isFirstCollision) {
								iter1->OnCollisionExit(new CollisionInfo{ iter2 });
								iter1->isFirstCollision = true;
							}
							if (!iter2->isFirstCollision) {
								iter2->OnCollisionExit(new CollisionInfo{ iter1 });
								iter2->isFirstCollision = true;
							}
						}
					}
					else if (iter1circlecollider && iter2boxcollider) {
						bool is_crash = true;

						Vec2F a1(cos(obj2_transform->GetRot()), sin(obj2_transform->GetRot()));
						Vec2F a2(-sin(obj2_transform->GetRot()), cos(obj2_transform->GetRot()));

						Vec2F l = obj1_transform->GetPos() - obj2_transform->GetPos();

						if (obj2_transform->GetPos().x - iter2boxcollider->GetWidthSize() <= obj1_transform->GetPos().x && obj1_transform->GetPos().x <= obj2_transform->GetPos().x + iter2boxcollider->GetWidthSize() ||
							obj2_transform->GetPos().y - iter2boxcollider->GetHeightSize() <= obj1_transform->GetPos().y && obj1_transform->GetPos().y <= obj2_transform->GetPos().y + iter2boxcollider->GetHeightSize()) {

							if (iter2boxcollider->GetWidthSize() + iter1circlecollider->GetRad() <= fabs(l.Dot(a1))) {
								is_crash = false;
							}

							if (iter2boxcollider->GetHeightSize() + iter1circlecollider->GetRad() <= fabs(l.Dot(a2))) {
								is_crash = false;
							}
						}
						else {
							if (obj1_transform->GetPos().x >= obj2_transform->GetPos().x) {
								if (obj1_transform->GetPos().y >= obj2_transform->GetPos().y) {
									Vec2F point(obj2_transform->GetPos().x + iter2boxcollider->GetWidthSize(), obj2_transform->GetPos().y + iter2boxcollider->GetHeightSize());

									if (iter1circlecollider->GetRad() < sqrt(pow(point.x - obj1_transform->GetPos().x, 2) + pow(point.y - obj1_transform->GetPos().y, 2))) {
										is_crash = false;
									}
								}
								else {
									Vec2F point(obj2_transform->GetPos().x + iter2boxcollider->GetWidthSize(), obj2_transform->GetPos().y - iter2boxcollider->GetHeightSize());

									if (iter1circlecollider->GetRad() < sqrt(pow(point.x - obj1_transform->GetPos().x, 2) + pow(point.y - obj1_transform->GetPos().y, 2))) {
										is_crash = false;
									}
								}
							}
							else {
								if (obj1_transform->GetPos().y >= obj2_transform->GetPos().y) {
									Vec2F point(obj2_transform->GetPos().x - iter2boxcollider->GetWidthSize(), obj2_transform->GetPos().y + iter2boxcollider->GetHeightSize());

									if (iter1circlecollider->GetRad() < sqrt(pow(point.x - obj1_transform->GetPos().x, 2) + pow(point.y - obj1_transform->GetPos().y, 2))) {
										is_crash = false;
									}
								}
								else {
									Vec2F point(obj2_transform->GetPos().x - iter2boxcollider->GetWidthSize(), obj2_transform->GetPos().y - iter2boxcollider->GetHeightSize());

									if (iter1circlecollider->GetRad() < sqrt(pow(point.x - obj1_transform->GetPos().x, 2) + pow(point.y - obj1_transform->GetPos().y, 2))) {
										is_crash = false;
									}
								}
							}
						}

						if (is_crash) {
							Vec2F crashline = obj1_transform->GetPos() - obj2_transform->GetPos();

							if (abs(crashline.x) > abs(crashline.y)) {
								crashline = a1;
							}
							else {
								crashline = a2;
							}

							if (iter1->isFirstCollision) {
								iter1->OnCollisionEnter(new CollisionInfo{ iter2 , crashline });
								iter1->isFirstCollision = false;
							}
							else {
								iter1->OnCollisionStay(new CollisionInfo{ iter2 , crashline });
							}

							if (iter2->isFirstCollision) {
								iter2->OnCollisionEnter(new CollisionInfo{ iter1 , crashline });
								iter2->isFirstCollision = false;
							}
							else {
								iter2->OnCollisionStay(new CollisionInfo{ iter1 , crashline });
							}
						}
						else {
							Vec2F crashline = obj1_transform->GetPos() - obj2_transform->GetPos();

							if (abs(crashline.x) > abs(crashline.y)) {
								crashline = a1;
							}
							else {
								crashline = a2;
							}
							
							if (!iter1->isFirstCollision) {
								iter1->OnCollisionExit(new CollisionInfo{ iter2 , crashline });
								iter1->isFirstCollision = true;
							}
							if (!iter2->isFirstCollision) {
								iter2->OnCollisionExit(new CollisionInfo{ iter1 , crashline });
								iter2->isFirstCollision = true;
							}
						}
					}
					else if (iter1circlecollider && iter2circlecollider) {
						Vec2F distance = obj1_transform->GetPos() - obj2_transform->GetPos();

						if (iter1circlecollider->GetRad() + iter2circlecollider->GetRad() >= sqrt(pow(distance.x, 2) + pow(distance.y, 2))) {
							Vec2F crashline = distance.Normalize();

							if (iter1->isFirstCollision) {
								iter1->OnCollisionEnter(new CollisionInfo{ iter2 , -crashline});
								iter1->isFirstCollision = false;
							}
							else {
								iter1->OnCollisionStay(new CollisionInfo{ iter2 , -crashline});
							}

							if (iter2->isFirstCollision) {
								iter2->OnCollisionEnter(new CollisionInfo{ iter1 , crashline});
								iter2->isFirstCollision = false;
							}
							else {
								iter2->OnCollisionStay(new CollisionInfo{ iter1 , crashline});
							}
						}
						else {
							Vec2F crashline(0, 0);

							if (!iter1->isFirstCollision) {
								iter1->OnCollisionExit(new CollisionInfo{ iter2 , -crashline});
								iter1->isFirstCollision = true;
							}
							if (!iter2->isFirstCollision) {
								iter2->OnCollisionExit(new CollisionInfo{ iter1 , crashline});
								iter2->isFirstCollision = true;
							}
						}
					}
				}
			}
		}
	}
}

void Scene::Render()
{
	float translationRatio = sqrtf(
		(float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)
		/ (INCH_PER_DISTANCE * INCH_PER_DISTANCE * DIAGONAL_LENGTH * DIAGONAL_LENGTH)
	);

	defaultMatrix =
		D2D1::Matrix3x2F::Scale(translationRatio, translationRatio) *
		D2D1::Matrix3x2F(mainCamera->GetIsFlipX() ? -1 : 1, 0, 0, mainCamera->GetIsFlipY() ? -1 : 1, 0, 0) *
		D2D1::Matrix3x2F::Translation(RG2R_WindowM->GetSize().width / 2.f, RG2R_WindowM->GetSize().height / 2.f);

	matrix =
		D2D1::Matrix3x2F::Translation(-GetMainCamera()->GetPos().x * INCH_PER_DISTANCE, GetMainCamera()->GetPos().y * INCH_PER_DISTANCE)*
		D2D1::Matrix3x2F::Scale(translationRatio, translationRatio) *
		D2D1::Matrix3x2F::Rotation(-GetMainCamera()->GetRot()) *
		D2D1::Matrix3x2F(mainCamera->GetIsFlipX() ? -1 : 1, 0, 0, mainCamera->GetIsFlipY() ? -1 : 1, 0, 0) *
		D2D1::Matrix3x2F::Scale(GetMainCamera()->GetZoom().x, GetMainCamera()->GetZoom().y) *
		D2D1::Matrix3x2F::Translation(RG2R_WindowM->GetSize().width / 2.f, RG2R_WindowM->GetSize().height / 2.f);

	for (auto iter : objects)
	{
		if (iter->GetIsEnable())
		{
			if (iter->isFirstRender)
			{
				ApplyListener(iter->onFirstRenderBeforeListener);
				iter->OnFirstRenderBefore();
			}
			ApplyListener(iter->onRenderBeforeListener);
			iter->OnRenderBefore();

			iter->Render();

			if (iter->isFirstRender)
			{
				ApplyListener(iter->onFirstRenderListener);
				iter->OnFirstRender();

				iter->isFirstRender = false;
			}
			ApplyListener(iter->onRenderListener);
			iter->OnRender();
		}
	}
}

void Scene::Render(ViewRenderData& viewRenderData)
{
	defaultMatrix_v =
		D2D1::Matrix3x2F(viewRenderData.GetCamera()->GetIsFlipX() ? -1 : 1, 0, 0, viewRenderData.GetCamera()->GetIsFlipY() ? -1 : 1, 0, 0) *
		D2D1::Matrix3x2F::Translation(viewRenderData.GetSize().width / 2.f, viewRenderData.GetSize().height / 2.f);

	matrix_v =
		D2D1::Matrix3x2F::Translation(-viewRenderData.GetCamera()->GetPos().x * INCH_PER_DISTANCE, viewRenderData.GetCamera()->GetPos().y * INCH_PER_DISTANCE)*
		D2D1::Matrix3x2F::Rotation(-viewRenderData.GetCamera()->GetRot()) *
		D2D1::Matrix3x2F(viewRenderData.GetCamera()->GetIsFlipX() ? -1 : 1, 0, 0, viewRenderData.GetCamera()->GetIsFlipY() ? -1 : 1, 0, 0) *
		D2D1::Matrix3x2F::Scale(viewRenderData.GetCamera()->GetZoom().x, viewRenderData.GetCamera()->GetZoom().y) *
		D2D1::Matrix3x2F::Translation(viewRenderData.GetSize().width / 2.f, viewRenderData.GetSize().height / 2.f);

	for (auto iter : objects)
	{
		if (iter->GetIsEnable())
		{
			iter->Render(viewRenderData);
		}
	}
}

Object* Scene::CreateObject()
{
	auto object = new Object();
	AttachObject(object);

	return object;
}

Object* Scene::AttachObject(Object* object)
{
	if (object->scene != this)
	{
		object->scene = this;
		objects.push_back(object);
	}

	return object;
}

Object* Scene::FindObject(Object* object)
{
	for (auto iter : objects)
	{
		if (iter == object)
			return iter;

		auto result = iter->FindChild(object);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

Object* Scene::FindObjectByTag(std::string tag)
{
	for (auto iter : objects)
	{
		if (iter->GetTag() == tag)
			return iter;

		auto result = iter->FindChildByTag(tag);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

Object* Scene::FindObjectByName(std::string name)
{
	for (auto iter : objects)
	{
		if (iter->GetName() == name)
			return iter;

		auto result = iter->FindChildByName(name);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

Object* Scene::FindObjectCondition(std::function<bool(Object*)> condition)
{
	for (auto iter : objects)
	{
		if (condition(iter))
			return iter;

		auto result = iter->FindChildCondition(condition);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

std::vector<Object*> Scene::FindObjectsByTag(std::string tag)
{
	std::vector<Object*> foundObjects;

	for (auto iter : objects)
	{
		if (iter->GetTag() == tag)
			foundObjects.push_back(iter);

		auto result = iter->FindChildsByTag(tag);
		for (auto iter2 : result)
			foundObjects.push_back(iter2);
	}

	return foundObjects;
}

std::vector<Object*> Scene::FindObjectsByName(std::string name)
{
	std::vector<Object*> foundObjects;

	for (auto iter : objects)
	{
		if (iter->GetName() == name)
			foundObjects.push_back(iter);

		auto result = iter->FindChildsByName(name);
		for (auto iter2 : result)
			foundObjects.push_back(iter2);
	}

	return foundObjects;
}

std::vector<Object*> Scene::FindObjectsCondition(std::function<bool(Object*)> condition)
{
	std::vector<Object*> foundObjects;

	for (auto iter : objects)
	{
		if (condition(iter))
			foundObjects.push_back(iter);

		auto result = iter->FindChildsCondition(condition);
		for (auto iter2 : result)
			foundObjects.push_back(iter2);
	}

	return foundObjects;
}

Camera* Scene::CreateCamera()
{
	auto camera = new Camera();
	AttachCamera(camera);

	return camera;
}

Camera* Scene::AttachCamera(Camera* camera)
{
	if (camera->scene != this)
	{
		camera->scene = this;
		cameras.push_back(camera);
	}

	return camera;
}

Camera* Scene::FindCamera(Camera* cam)
{
	for (auto iter : cameras)
	{
		if (iter == cam)
			return iter;
	}

	return nullptr;
}

Camera* Scene::FindCameraByName(std::string name)
{
	for (auto iter : cameras)
	{
		if (iter->GetName() == name)
			return iter;
	}

	return nullptr;
}

Camera* Scene::FindCameraCondition(std::function<bool(Camera*)> condition)
{
	for (auto iter : cameras)
	{
		if (condition(iter))
			return iter;
	}

	return nullptr;
}

std::vector<Camera*> Scene::FindCamerasCondition(std::function<bool(Camera*)> condition)
{
	std::vector<Camera*> foundCameras;

	for (auto iter : cameras)
	{
		if (condition(iter))
			foundCameras.push_back(iter);
	}

	return foundCameras;
}

void Scene::SetGameSpeed(float _speed) {
	for (auto iter : objects) {
		auto iterrigidbody = iter->GetComponent<Rigidbody>();

		if (iterrigidbody)
			iterrigidbody->SetCalculationSpeed(_speed);
	}
}

float Scene::GetGameSpeed() {
	float speed = 0;

	for (auto iter : objects) {
		auto iterrigidbody = iter->GetComponent<Rigidbody>();

		if (iterrigidbody)
			if (speed < iterrigidbody->GetCalculationSpeed())
				speed = iterrigidbody->GetCalculationSpeed();
	}

	return speed;
}