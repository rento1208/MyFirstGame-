#pragma once

#include "Engine//GameObject.h"
#include <DirectXMath.h>
using namespace DirectX;

class Bullet : public GameObject
{
public:
    //親付き・位置と方向を渡すコンストラクタ
    Bullet(GameObject* parent, const XMFLOAT3& pos, const XMFLOAT3& dir);

    //引数なし／親のみのコンストラクタ
    Bullet(GameObject* parent);

    virtual ~Bullet() {}

    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void Release() override;

    //便利メソッド
    void SetDirection(const XMFLOAT3& dir) { direction_ = dir; }
    void SetSpeed(float s) { speed_ = s; }

private:
    XMFLOAT3 direction_;
    float speed_;
    float lifeTime_; //フレーム数や経過時間を入れる
    int hModel;
};
