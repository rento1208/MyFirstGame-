#include "RootJob.h"
#include "../PlayScene.h"
#include "SceneManager.h"

RootJob::RootJob(GameObject* parent)
	:GameObject(parent, "RootJob")
{
	
}

RootJob::~RootJob()
{
}

void RootJob::Initialize()
{
	////PlaySceneを生成して、子オブジェクトに追加する
	////PLaySceneのインスタンスを生成
	//PlayScene* pPlayScene = new PlayScene(this);
	////PlaySceneのintializeを呼ぶ
	//pPlayScene->Initialize();
	//childList_.push_back(pPlayScene);
	Instantiate<SceneManager>(this);
	

}

void RootJob::Update()
{
}

void RootJob::Draw()
{
}

void RootJob::Release()
{
}
