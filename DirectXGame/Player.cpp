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
	
	
	// キー入力
	if(Input::GetInstance()->PushKey(DIK_RIGHT)||
		Input::GetInstance()->PushKey(DIK_LEFT)){
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			// 右キーが押されている
			if (velocity_.x<0.0f) {
				velocity_.x *= (1.0f - kAttenution);
			}
			acceleration.x += kAcceleration;
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 左キーが押されている
			if (velocity_.x > 0.0f) {
				velocity_.x *= (1.0f - kAttenution);
			}
			acceleration.x -= kAcceleration;
		}
		velocity_ = Add(velocity_, acceleration);
		// 最大速度
		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
	} else {
		// 減速
		velocity_ .x*=(1.0f-kAcceleration);
	}

	worldTransform_.translation_ =Add(worldTransform_.translation_,velocity_);

	
	WorldTransformUpdate(&worldTransform_);
	

}

void Player::Draw() { 
	model_->Draw(worldTransform_, *camera_);
}
