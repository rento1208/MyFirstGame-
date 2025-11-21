#include "Direct3D.h"
#include "SceneManager.h"
#include "../Player.h"
#include "../TitleScene.h"
#include "../PlayScene.h"
#include "../ResultScene.h"
#include "Model.h"

SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent,"SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

void SceneManager::Update()
{
	if (currentSceneID_ != nextSceneID_)
	{
		
		auto scene = childList_.front();
		scene->ReleaseSub();
		SAFE_DELETE(scene);
		childList_.clear();
		//Model::Release();

		switch (nextSceneID_)
		{
		case SCENE_ID_PLAY:
			Instantiate<PlayScene>(this);
			break;
		case SCENE_ID_TITLE:
			Instantiate<TitleScene>(this);
			break;
		case SCENE_ID_RESULT:
			Instantiate<ResultScene>(this);
			break;
		}
		
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID _nextScene)
{
	nextSceneID_ = _nextScene;
}
