#include "Enemy.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"


Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), pFbx(nullptr)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	pFbx = new Fbx;
	pFbx->Load("oden.fbx");
	transform_.position_ = { 0.0f, 0.0f, 50.0f };

	SphereCollider* col = new SphereCollider(2.0f);
	AddCollider(col);
}

void Enemy::Update()
{
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
