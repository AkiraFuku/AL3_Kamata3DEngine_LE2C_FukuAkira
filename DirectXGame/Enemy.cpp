
#include <cassert>
#include <numbers>
#include "Enemy.h"
#include "Math.h"

void Enemy::Initialize(Model* model, Camera* camera,Vector3& position) {
	// NULLチェック
	assert(model);

	// 02_09 7枚目
	model_  = model;
	// 02_09 7枚目
	camera_ = camera;
	// 02_09 7枚目
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	// 02_09 7枚目 角度調整
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 3.0f / 2.0f;
}
void Enemy::Update() {

	WorldTransformUpdate(&worldTransform_);
};
void Enemy::Draw(){

model_->Draw(worldTransform_,*camera_);
};