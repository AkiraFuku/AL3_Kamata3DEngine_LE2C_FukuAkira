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
	
	
	// 入力処理
	inputMove();

	// 衝突判定
	CollisionMapInfo collisionMapInfo;
	collisionMapInfo.move = velocity_;
	MapCollisionCheck(collisionMapInfo);

	//着地フラグ
	bool landing =false;
	//
	if (velocity_.y<0) {
		if (worldTransform_.translation_.y<=1.0f) {
			landing=true;
		}
	}
	if (onGround_) {
		if (velocity_.y>0.0f) {
			onGround_=false;
		}
	} else {
		if (landing) {
			///めり込み排除
			worldTransform_.translation_.y=1.0f;
			//摩擦
			velocity_.x *=(1.0f-kAttenution);
			//下方向速度リセット
			velocity_.y=0.0f;
			onGround_=true;


		}
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
	model_->Draw(worldTransform_, *camera_); }

void Player::MapCollisionCheck(CollisionMapInfo& collisionMapInfo) {
	CheckMapCollisionUp(collisionMapInfo);
	CheckMapCollisionDown(collisionMapInfo);
	CheckMapCollisionRight(collisionMapInfo);
	CheckMapCollisionLeft(collisionMapInfo);

}

void Player::CheckMapCollisionUp(CollisionMapInfo& info) {
	if (info.move.y<=0) {
		return;
	}
	std::array<Vector3,kNumCorner> PositionNew;
	for (uint32_t i = 0; i < PositionNew.size(); i++) {
		PositionNew[i] = CornerPosition(worldTransform_.translation_+info.move, static_cast<Corner>(i));
	}

}

void Player::CheckMapCollisionDown(CollisionMapInfo& info) {info;}

void Player::CheckMapCollisionRight(CollisionMapInfo& info) {info;}

void Player::CheckMapCollisionLeft(CollisionMapInfo& info) {info;}

void Player::inputMove() {
	if (onGround_) {
	
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
		if (std::abs(velocity_.x)<=0.0001f) {
			velocity_.x = 0.0f;
		}
		if (Input::GetInstance()->PushKey(DIK_UP)) {
			velocity_=Add(velocity_,Vector3(0,kJumpAcceleration/60.0f,0));
		}
	} else {
		//落下速度
		velocity_=Add(velocity_, Vector3(0,-kGravityAcceleration/60.0f,0));
		//落下速度制限
		velocity_.y=std::max(velocity_.y,-kLimitFallSpeed);
	}
}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {
	Vector3 OffsetTable[kNumCorner]={
	
		Vector3{+kWidth / 2.0f, -kHeight / 2.0f,0.0f}, // kRightBottom
		Vector3{-kWidth / 2.0f, -kHeight / 2.0f,0.0f}, // kLeftBottom
		Vector3{+kWidth / 2.0f, +kHeight / 2.0f,0.0f}, // kRightTop
		Vector3{-kWidth / 2.0f, +kHeight / 2.0f,0.0f} // kLeftTop
	};
	return center + OffsetTable[static_cast<uint32_t>(corner)];
	

}
