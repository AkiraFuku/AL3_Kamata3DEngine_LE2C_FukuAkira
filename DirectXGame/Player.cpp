#include "Player.h"

void Player::Initialize(Model* model,uint32_t textureHandle
	//,Camera* camera
) { 
	assert(model);
	/// 引数をメンバ変数に格納
	/// モデル
	model_ = model;
	// テクスチャハンドル
	textureHandle_ = textureHandle;
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//camera_=camera;
}

void Player::Update() {
	worldTransform_.TransferMatrix();

}

void Player::Draw() { 
	//model_->Draw(worldTransform_, *camera_,textureHandle_);
}
