#include "Player.h"

void Player::Initialize(Model* model,uint32_t textureHandle,Camera* camera,const Vector3& position) { 
	assert(model);
	/// 引数をメンバ変数に格納
	/// モデル
	model_ = model;
	// テクスチャハンドル
	textureHandle_ = textureHandle;
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	// カメラ
	camera_=camera;
}

void Player::Update() {
	// afine変換
	/*Matrix4x4 affin_mat = MakeAfineMatrix(
		worldTransform_.scale_,
		worldTransform_.rotation_,
		worldTransform_.translation_
	);
	worldTransform_.matWorld_ =affin_mat;*/
	WorldTransformUpdate(&worldTransform_);

	//worldTransform_.TransferMatrix();
	

}

void Player::Draw() { 
	model_->Draw(worldTransform_, *camera_);
}
