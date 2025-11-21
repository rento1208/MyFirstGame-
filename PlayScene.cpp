#include "PlayScene.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Enemy.h"


PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{

}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	//Playerのインスタンスを生成して、子オブジェクトに追加する
	/*Player* pPlayer = new Player(this);
	pPlayer->Initialize();
	childList_.push_back(pPlayer);*/
	

	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
}

void PlayScene::Update()
{
	//Enemyが消えたらResultSceneに切り替える処理を追加する
	GameObject* pEnemy = FindChildObject("Enemy");
	if (pEnemy == nullptr) {
		//Enemyがいない→全滅している
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_RESULT);
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{

}
