#include "Bullet.h"
#include "Engine//Fbx.h"
#include "Engine/Model.h"
#include <assert.h>
#include "Engine/SphereCollider.h"


Bullet::Bullet(GameObject* parent, const XMFLOAT3& pos, const XMFLOAT3& dir)
    : GameObject(parent, "Bullet"),
    direction_(dir),
    speed_(0.5f),   // 初期速度（必要に応じて変更）
    lifeTime_(0.0f),
    hModel(-1)
{
    transform_.position_ = pos;
}

Bullet::Bullet(GameObject* parent)
    : GameObject(parent, "Bullet"),
    direction_(XMFLOAT3{ 0.0f, 0.0f, 1.0f }),
    speed_(0.5f),
    lifeTime_(0.0f),
    hModel(-1)
{
    //位置は後からSetPositionで設定する想定
}

void Bullet::Initialize()
{
    //モデル読み込み
    hModel = Model::Load("Bullet.fbx");
    assert(hModel >= 0);
    transform_.scale_ = { 1.0f,1.0f,1.0f };

    //弾の衝突判定を追加
    SphereCollider* col = new SphereCollider(0.5f);
    AddCollider(col);
}


void Bullet::Update()
{
    // 位置更新
    transform_.position_.x += direction_.x * speed_;
    transform_.position_.y += direction_.y * speed_;
    transform_.position_.z += direction_.z * speed_;

    // ライフタイムカウント
    lifeTime_ += 1.0f;

    //300フレームで消す
    if (lifeTime_ > 300.0f) {
        KillMe();
        return;
    }

    // ワールド外で消す
    const float bound = 200.0f;
    if (fabs(transform_.position_.x) > bound ||
        fabs(transform_.position_.y) > bound ||
        fabs(transform_.position_.z) > bound) {
        KillMe();
    }
}

void Bullet::Draw()
{
    if (hModel >= 0) {
        Model::SetTransform(hModel, transform_);
        Model::Draw(hModel);
    }
}

void Bullet::Release()
{
    //必要ならここでモデル解放など
}
