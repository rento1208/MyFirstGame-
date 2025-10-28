#include "RootJob.h"
#include "..\\PlayScene.h"
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
	//
	//PlaySceneを生成して、子オブジェクトに追加する
	//0. PlaySceneの変数を宣言
	//1. PlaySceneのインスタンスを生成
	//2. PlaySceneのInitializeを呼ぶ
	//3. childList_に追加する
	//PlayScene* pPlayScene; //0. PlaySceneの変数を宣言
	//pPlayScene = new PlayScene(this); //1. PlaySceneのインスタンスを生成
	//pPlayScene->Initialize(); //2. PlaySceneのInitializeを呼ぶ
	//childList_.push_back(pPlayScene); //3. childList_に追加する
	Instantiate<PlayScene>(this);
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
