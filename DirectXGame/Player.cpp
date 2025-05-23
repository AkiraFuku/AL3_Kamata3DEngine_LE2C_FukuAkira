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
				// 旋回時の角度
				turnFirstRotationY_ = worldTransform_.rotation_.y;
				// 旋回タイマー初期化
				turnTimer_ = kTimeTurn;

			}
			acceleration.x += kAcceleration;
			if (lrDirection_ != LRDirection::kRight) {
				lrDirection_ = LRDirection::kRight;
			}
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 左キーが押されている
			if (velocity_.x > 0.0f) {
				velocity_.x *= (1.0f - kAttenution);
			}
			acceleration.x -= kAcceleration;
			if (lrDirection_ != LRDirection::kLeft) {
				lrDirection_ = LRDirection::kLeft;
				// 旋回時の角度
				turnFirstRotationY_ = worldTransform_.rotation_.y;
				// 旋回タイマー初期化
				turnTimer_ = kTimeTurn;
			}
		}
		velocity_ = Add(velocity_, acceleration);
		// 最大速度
		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
	} else {
		// 減速
		velocity_ .x*=(1.0f-kAcceleration);
	}
	
	worldTransform_.translation_ =Add(worldTransform_.translation_,velocity_);
	// 旋回
	if (turnTimer_>0.0f) {
		// 旋回時間を減少
		turnTimer_ =std::max(turnTimer_-(1.0f/60.0f),0.0f);
		// 旋回角度



		float destinationRotationYTable[]={
	    std::numbers::pi_v<float>/2.0f,
	    std::numbers::pi_v<float>*3.0f/2.0f
		} ;

	float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

	worldTransform_.rotation_.y = EaseInOut( destinationRotationY, turnFirstRotationY_,turnTimer_ / kTimeTurn);
	} 
	

	

	
	WorldTransformUpdate(&worldTransform_);

}

void Player::Draw() { 
	model_->Draw(worldTransform_, *camera_);
}
