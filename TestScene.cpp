#include "TestScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/Input.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent, "TestScene"),m_hModel(-1)
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
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

void TestScene::Update()
{
    

    //スペースキー押したら 
    // SceneManager::ChangeScene(SCENE_ID_PLAY); を呼び出してね
   // スペースキー押したらシーン遷移
    if (Input::IsKeyDown(DIK_SPACE))
    {
        // 親（SceneManager）を取得してシーン変更
        SceneManager* pManager = dynamic_cast<SceneManager*>(GetParent());
        if (pManager)
        {
            pManager->ChangeScene(SCENE_ID_PLAY);
        }
    }
  
	
    
    
}

void TestScene::Draw()
{
   
    if (m_hModel >= 0)
    {
        Model::Draw(m_hModel);
    }
}

void TestScene::Release()
{
    Model::Release();
}