#include "Player.h"
#include "Engine/Fbx.h"
#include "Engine/Model.h"
#include "ChildOden.h"
#include "Engine/Input.h"
#include "Bullet.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hModel(-1)
{

}

Player::~Player()
{
}

void Player::Initialize()
{

	hModel = Model::Load("oden.fbx");
	
	if (hModel < 0) return;
	
	/*pFbx_->Load("Oden.fbx");*/
	transform_.scale_.x = 0.4f;
	transform_.scale_.y = 0.4f;
	transform_.scale_.z = 0.4f;

	//子オブジェクトにChildOdenを追加する
	pRChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	pLChildOden_ = (ChildOden*)Instantiate<ChildOden>(this);
	pRChildOden_->SetPosition(2.0f, 1.0f, 0.0f);
	pLChildOden_->SetPosition(-2.0f, 1.0f, 0.0f);

	SphereCollider* col = new SphereCollider(0.5f);
	AddCollider(col);


}

void Player::Update()
{
	static float x = 0.0;
	float tx = sin(x) * 5.0f;
	x += 0.02f;
	//transform_.position_.x = tx;
	transform_.rotate_.y += 1.0f;
	if (Input::IsKey(DIK_D))
	{
		transform_.position_.x += 0.2f;
	}
	else if (Input::IsKey(DIK_A))
	{
		transform_.position_.x -= 0.2f;
	}
	else if (Input::IsKey(DIK_SPACE))
	{
		FireBullet();
	}

};

void Player::Draw()
{
	
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Player::Release()
{
	/*if (pFbx_)
	{
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;

	}*/
}

void Player::FireBullet()
{
	//Bulletをプレイヤーの親の親に生成する
	Bullet* b = dynamic_cast<Bullet*>(Instantiate<Bullet>(GetParent()->GetParent()));

	//弾の発射位置をプレイヤーの前に合わせる
	b->SetPosition(
		transform_.position_.x,
		transform_.position_.y,
		transform_.position_.z + 2.0f);  //ちょっと前
}
