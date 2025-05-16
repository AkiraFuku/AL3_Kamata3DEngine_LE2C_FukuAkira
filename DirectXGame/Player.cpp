#include "Player.h"

void Player::Initialize(Model* model,uint32_t textureHandle,Camera* camera,const Vector3 position) { 
	assert(model);
	/// 引数をメンバ変数に格納
	/// モデル
	model_ = model;
	// テクスチャハンドル
	textureHandle_ = textureHandle;
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
//	worldTransform_.translation_ = position;
//	worldTransform_.rotation_.y = std::numbers::pi_v<float>/2.0f;
	// カメラ
	camera_=camera;

}

void Player::Update() {
	// afine変換

	// 移動
	/*if (Input::GetInstance()->PushKey(DIK_RIGHT)||
		Input::GetInstance()->PushKey(DIK_LEFT)) {
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			acceleration.x += kAcceleration;
		} else if(Input::GetInstance()->PushKey(DIK_LEFT)) {
			acceleration.x -= kAcceleration;
		}
		velocity_ = Add(velocity_, acceleration);
		
	}*/


	worldTransform_.translation_ =Add(worldTransform_.translation_,velocity_);
	
	//WorldTransformUpdate(&worldTransform_);

	
	

}

void Player::Draw() { 
	model_->Draw(worldTransform_, *camera_);
}
