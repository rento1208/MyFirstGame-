#include "GameObject.h"
#include "SphereCollider.h"
#include <Windows.h>


GameObject::GameObject()
          :pParent_(nullptr), objectName_("GameObject"), isDead_(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
           : pParent_(parent), objectName_(name), isDead_(false)
{
    if (pParent_ != nullptr)
    {
      transform_.pParent_ = &(pParent_->transform_);
    }
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
    Draw();

	for (auto child : childList_)
	{
		child->DrawSub();
    }
}

void GameObject::UpdateSub()
{
	transform_.Calculation();

	this->Update();

	RoundRobin(GetRootJob());
	for (auto child : childList_)
	{
		child->UpdateSub();
	}

	for (auto it = childList_.begin(); it != childList_.end(); )
	{
		if ((*it)->isDead_)
		{
			(*it)->ReleaseSub();
			delete (*it);
			it = childList_.erase(it); // ← eraseの戻り値を必ず使う
		}
		else
		{
			++it;
		}
	}
}

void GameObject::ReleaseSub()
{

	this->Release();

	for (auto child : childList_)

	{

		child->ReleaseSub();

		delete child;

	}

	childList_.clear();

}

void GameObject::SetPosition(XMFLOAT3 position)

{

	transform_.position_ = position;

}

void GameObject::SetPosition(float x, float y, float z)

{

	transform_.position_ = { x,y,z };

}

void GameObject::KillMe()

{

	isDead_ = true;

}

GameObject* GameObject::GetRootJob()

{

	if (pParent_ == nullptr)

	{

		return this;

	}

	else

	{

		return pParent_->GetRootJob();

	}

}

GameObject* GameObject::FindChildObject(const std::string& name)

{

	if (this->objectName_ == name)

	{

		return this;

	}

	else

	{

		for (auto child : childList_)

		{

			GameObject* result = child->FindChildObject(name);

			if (result != nullptr)

			{

				return result;

			}

		}

	}

	return nullptr;

}

GameObject* GameObject::FindObject(const std::string& name)

{

	GameObject* rootJob = GetRootJob();

	GameObject* result = rootJob->FindChildObject(name);

	return result;



}

GameObject* GameObject::GetRootScene()
{
	GameObject* current = this;
	while (current->pParent_ != nullptr)
	{
		current = current->pParent_;
	}
	return current;
}

void GameObject::AddCollider(SphereCollider* pCollider)

{

	pCollider_ = pCollider;

}

void GameObject::Collision(GameObject* pTarget)
{
	if (!pCollider_ || !pTarget->pCollider_) return;

	float thisR = pCollider_->GetRadius();
	float tgtR = pTarget->pCollider_->GetRadius();
	float thre = (thisR + tgtR) * (thisR + tgtR);

	XMFLOAT3 thisP = transform_.position_;
	XMFLOAT3 tgtP = pTarget->transform_.position_;

	float dist =
		(thisP.x - tgtP.x) * (thisP.x - tgtP.x) +
		(thisP.y - tgtP.y) * (thisP.y - tgtP.y) +
		(thisP.z - tgtP.z) * (thisP.z - tgtP.z);

	if (dist <= thre)
	{
		// コールバックを先に呼ぶ
		this->onCollision(pTarget);
		pTarget->onCollision(this);

		// 弾→敵
		if (objectName_ == "Bullet" && pTarget->objectName_ == "Enemy")
		{
			KillMe();
			pTarget->KillMe();
		}

		// 敵→弾
		if (objectName_ == "Enemy" && pTarget->objectName_ == "Bullet")
		{
			KillMe();
			pTarget->KillMe();
		}
	}
}
void GameObject::RoundRobin(GameObject* target)
{
	if (!pCollider_) return;

	// 対象と自分の衝突
	if (target->pCollider_ && target != this)
		Collision(target);

	// ターゲットの子すべてを調べる
	for (auto child : target->childList_)
	{
		RoundRobin(child);
	}
}