#include "ResultScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

ResultScene::ResultScene(GameObject* parent)
	:GameObject(parent, "ResultScene"), hModel_(-1)
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	hModel_ = Model::Load("oden.fbx");

    if (hModel_ < 0) return;

	/*pFbx_->Load("Oden.fbx");*/
	transform_.scale_.x = 0.3f;
	transform_.scale_.y = 0.3f;
	transform_.scale_.z = 0.3f;
}

void ResultScene::Update()
{
	if (Input::IsKeyDown(DIK_T))
	{
		// 親（SceneManager）を取得してシーン変更
		SceneManager* pManager = dynamic_cast<SceneManager*>(GetParent());
		if (pManager)
		{
			pManager->ChangeScene(SCENE_ID_TITLE);
		}
	}
}

void ResultScene::Draw()
{
	if (hModel_ >= 0)
	{
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
	}
}

void ResultScene::Release()
{
	Model::Release();
}
