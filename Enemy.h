#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

class Enemy :
    public GameObject
{
    Fbx* pFbx;
public:
    //コンストラクタ
    Enemy(GameObject* parent);
    //デストラクタ
    ~Enemy();
    //初期化
    void Initialize() override;
    //更新
    void Update() override;
    //描画
    void Draw() override;
    //開放
    void Release() override;

private:
    float moveTime_;          // 時間経過
    float moveAmplitude_;     // 移動幅
    float moveSpeed_;         // 移動速度
};