#include "Player.h"
#include "MapchipField.h"

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


	// 衝突判定結果をワールドトランスフォームに反映
	ResultCollisionMapInfo(collisionMapInfo);
	// 天井に当たった場合の処理
	hitCeiling(collisionMapInfo);
	HitWall(collisionMapInfo);
	//着地
	UpdatOnGround(collisionMapInfo);
	////着地フラグ
	//bool landing =false;
	////
	//if (velocity_.y<0) {
	//	if (worldTransform_.translation_.y<=1.0f) {
	//		landing=true;
	//	}
	//}
	//if (onGround_) {
	//	if (velocity_.y>0.0f) {
	//		onGround_=false;
	//	}
	//} else {
	//	if (landing) {
	//		///めり込み排除
	//		worldTransform_.translation_.y=1.0f;
	//		//摩擦
	//		velocity_.x *=(1.0f-kAttenution);
	//		//下方向速度リセット
	//		velocity_.y=0.0f;
	//		onGround_=true;


	//	}
	//}

	
	
	//worldTransform_.translation_ =Add(worldTransform_.translation_,velocity_);










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
	if (info.move.y<=0.0f) {
		return;
	}
	std::array<Vector3,kNumCorner> PositionNew;
	for (uint32_t i = 0; i < PositionNew.size(); ++i) {
		PositionNew[i] = CornerPosition(worldTransform_.translation_+info.move, static_cast<Corner>(i));
	}
	MapChipType mapChipType;
	//真上の当たり判定
	bool hit=false;
	// 左上の当たり判定
	 MapChipField::IndexSet indexSet;
	 indexSet=mapChipField_->GetMapChipIndexSetByPosition(PositionNew[kLeftTop]);
	 mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex,indexSet.yIndex);
	 if (mapChipType==MapChipType::kBlock) {
		 hit = true;
	 }
	 // 右上の当たり判定
	 indexSet=mapChipField_->GetMapChipIndexSetByPosition(PositionNew[kRightTop]);
	  mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex,indexSet.yIndex);
	 if (mapChipType==MapChipType::kBlock) {
		 hit = true;
	 }
	 // 当たっていたら
	 if (hit) {
		 // めり込み排除する方向へ移動
		 indexSet =mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_+Vector3(0.0f,+kHeight/2.0f,0.0f));
		 MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		 // 上方向の移動量を計算
		 info.move.y= std::max(0.0f,rect.bottom-worldTransform_.translation_.y-(kHeight/2.0f+kBlank));
		 info.isCeiling = true;
	 }


}

void Player::CheckMapCollisionDown(CollisionMapInfo& info) {
	if (info.move.y>=0.0f) {
		return;
	}	
	
	std::array<Vector3, kNumCorner> PositionNew;
	for (uint32_t i = 0; i < PositionNew.size(); ++i) {
		PositionNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}

	MapChipType mapChipType;
	// 下方向の当たり判定
	bool hit = false;
	// 左下の当たり判定
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(PositionNew[kLeftBottom]);

	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	// 右下の当たり判定
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(PositionNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType == MapChipType::kBlock) {
		hit = true;
	}
	// 当たっていたら
	if (hit) {
		// めり込み排除する方向へ移動
		indexSet= mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_+info.move+Vector3(0.0f,-kHeight/2.0f,0.0f));
		// めり込み先のマップチップの矩形を取得
		MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
		// 下方向の移動量を計算
		info.move.y = std::min(0.0f, rect.top - worldTransform_.translation_.y + (kHeight / 2.0f + kBlank));
		info.isFloor = true;

	}

	
	

}

void Player::CheckMapCollisionRight(CollisionMapInfo& info) {
	
	info;
	if (info.move.x<=0.0f) {
		return;
	}
	std::array<Vector3,kNumCorner> positionsNew;
	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i]=CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}
	MapChipType mapChipType;
	//右側の当たり判定
	bool hit=false;
	//右上の判定
	MapChipField::IndexSet indexSet;
	indexSet=mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType== MapChipType::kBlock) {
		hit= true;
	}
	//右下の判定
	indexSet=mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType== MapChipType::kBlock) {
		hit= true;
	}
	//ブロックにヒット
	if (hit) {
		// 現在座標が壁の外か判定
		//MapChipField::IndexSet indexSetNow;
		//indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(+kWidth / 2.0f, 0, 0));
		//if (indexSetNow.xIndex != indexSet.xIndex){
			// めり込み排除する方向へ移動
			indexSet= mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_+info.move+Vector3(+kWidth/2.0f,0.0f,0.0f));
			// めり込み先のマップチップの矩形を取得
			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
			// 下方向の移動量を計算
			info.move.x= std::max(0.0f, rect.left - worldTransform_.translation_.x -(kWidth / 2.0f + kBlank));
			info.isWall = true;
		//}
	}


}

void Player::CheckMapCollisionLeft(CollisionMapInfo& info) {
	info;
		if (info.move.x>=0.0f) {
		return;
	}
	std::array<Vector3,kNumCorner> positionsNew;
	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i]=CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}
	MapChipType mapChipType;
	//左側の当たり判定
	bool hit=false;
	//左上の判定
	MapChipField::IndexSet indexSet;
	indexSet=mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType== MapChipType::kBlock) {
		hit= true;
	}
	//左下の判定
	indexSet=mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	if (mapChipType== MapChipType::kBlock) {
		hit= true;
	}
	//ブロックにヒット
	if (hit) {
		// 現在座標が壁の外か判定
		//	MapChipField::IndexSet indexSetNow;
		//indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(-kWidth / 2.0f, 0, 0));

		//if (indexSetNow.xIndex != indexSet.xIndex){
			// めり込み排除する方向へ移動
			indexSet= mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_+info.move+Vector3(-kWidth/2.0f,0.0f,0.0f));
			// めり込み先のマップチップの矩形を取得
			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
			// 下方向の移動量を計算
			info.move.x= std::min(0.0f, rect.right - worldTransform_.translation_.x +(kWidth / 2.0f + kBlank));
			info.isWall = true;
		//}
	}

}

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

void Player::ResultCollisionMapInfo(const CollisionMapInfo& info) { 
	worldTransform_.translation_ += info.move;

}

void Player::hitCeiling(const CollisionMapInfo& info) {
	if (info.isCeiling) {
		DebugText::GetInstance()->ConsolePrintf("hitCeiling\n");
		// めり込み排除
		velocity_.y = 0.0f;
	}
}

void Player::UpdatOnGround(const CollisionMapInfo& info) {
		
	
	if (onGround_) {
		info;
		if (velocity_.y>0.0f) {
			onGround_=false;
		} else {
			//落下判定
				std::array<Vector3, kNumCorner> positionsNew;

			for (uint32_t i = 0; i < positionsNew.size(); ++i) {
				positionsNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
			}
			MapChipType mapChipType;
			//真下の当たり判定
			bool hit= false;
			//左下
			MapChipField::IndexSet indexSet;
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom] + Vector3(0, -kGroundSearchHeight, 0));
			mapChipType=mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex,indexSet.yIndex);
			if (mapChipType==MapChipType::kBlock) {
				hit =true;
			}
			//右下
			indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom] + Vector3(0, -kGroundSearchHeight, 0));
			mapChipType=mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex,indexSet.yIndex);
			if (mapChipType==MapChipType::kBlock) {
				hit =true;
			}
			//落下開始
			if (!hit) {
				DebugText::GetInstance()->ConsolePrintf("jump");
				onGround_=false;
			}

		}

		

	} else {
		
		// // 着地している場合
		if (info.isFloor) {
			//
			onGround_ = true;
			// ｘ方向の速度を減衰
			velocity_.x *= (1.0f -kAttenuationLanding );
			// y方向の速度をリセット
			velocity_.y = 0.0f;
		}
		
	}
}

void Player::HitWall(const CollisionMapInfo& info) {
	
	if (info.isWall) {
		velocity_.x*=(1.0f-kAttenuationWall);
	}

}



