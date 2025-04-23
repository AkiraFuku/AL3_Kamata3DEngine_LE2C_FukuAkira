#include "Player.h"

void Player::Initialize(Model* model,uint32_t textureHandle) { 
	assert(model);
	/// 引数をメンバ変数に格納
	model_ = model;
	textureHandle_ = textureHandle;
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

}

void Player::Update() {
	worldTransform_.TransferMatrix();

}

void Player::Draw() {}
