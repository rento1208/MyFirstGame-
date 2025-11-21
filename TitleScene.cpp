#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/Input.h"


TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent, "TitleScene"),m_hModel(-1)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
    // モデルの読み込み
    m_hModel = Model::Load("Oden.fbx");

    // トランスフォーム設定（位置など）
    Transform transform;
    transform.position_ = { 0.0f, -1.0f, 0.0f };
    transform.rotate_ = { 0.0f, 0.0f, 0.0f };
    transform.scale_ = { 1.0f, 1.0f, 1.0f };

    Model::SetTransform(m_hModel, transform);
}

void TitleScene::Update()
{
    

    //スペースキー押したら 
    // SceneManager::ChangeScene(SCENE_ID_PLAY); を呼び出してね
   // スペースキー押したらシーン遷移
    if (Input::IsKeyDown(DIK_T))
    {
        // 親（SceneManager）を取得してシーン変更
        SceneManager* pManager = dynamic_cast<SceneManager*>(GetParent());
        if (pManager)
        {
            pManager->ChangeScene(SCENE_ID_PLAY);
        }
    }
  
	
    
    
}

void TitleScene::Draw()
{
   
   
    if (m_hModel >= 0)
    {
        Model::Draw(m_hModel);
    }
}

void TitleScene::Release()
{
    Model::Release();
}