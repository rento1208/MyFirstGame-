#include "Enemy.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"


Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), pFbx(nullptr), moveTime_(0.0f), 
	 moveAmplitude_(10.0f), moveSpeed_(0.05f)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("oden.fbx");
	transform_.position_ = { 0.0f, 0.0f, 70.0f };

	// 移動パラメータ初期化
	moveTime_ = 0.0f;
	moveAmplitude_ = 30.0f;   // 左右±20動く
	moveSpeed_ = 0.02f;        // 動くスピード

	SphereCollider* col = new SphereCollider(2.0f);
	AddCollider(col);
}

void Enemy::Update()
{// 時間経過
	moveTime_ += moveSpeed_;
	// サインカーブで左右に移動
	transform_.position_.x = sinf(moveTime_) * moveAmplitude_;
}

void Enemy::Draw()
{
	pFbx->Draw(transform_);
}

void Enemy::Release()
{
}

void Enemy::onCollision(GameObject* pTarget)
{
	
}
