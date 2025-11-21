#pragma once
#include "Engine/GameObject.h"

//前方宣言
class Fbx;
class ChildOden;

class Player :
    public GameObject
{
  
public:
    Player(GameObject* parent);
    ~Player();
    //純粋仮想関数のオーバーライド
    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;

private:
   /* Fbx* pFbx_;*/
    int hModel;
    ChildOden* pRChildOden_;
    ChildOden* pLChildOden_;

    void FireBullet();

};

