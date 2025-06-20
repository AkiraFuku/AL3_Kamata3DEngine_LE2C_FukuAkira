
#include <cassert>
#include <numbers>
#include "Enemy.h"
#include "Math.h"

void Enemy::Initialize(Model* model, Camera* camera,Vector3& position) {
	// NULLチェック
	assert(model);

	
	model_  = model;
	
	camera_ = camera;
	
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	// 角度調整
	worldTransform_.rotation_.y = std::numbers::pi_v<float> * 3.0f / 2.0f;
	velocity_={-kWalkSpeed,0.0f,0.0f};
	walkTimer_=0.0f;

}
void Enemy::Update() {

	worldTransform_.translation_+=velocity_;
	walkTimer_+=1.0f/60.0f;

	float param= std::sinf(std::numbers::pi_v<float>*2.0f*walkTimer_/kWalkMotionTime);
	float degree =kWalkMotionAngleStart+kWalkMotionAngleEnd*(param+1.0f)/2.0f;
	worldTransform_.rotation_.x=Radian(degree);


	WorldTransformUpdate(&worldTransform_);
};
void Enemy::Draw(){

model_->Draw(worldTransform_,*camera_);
};
Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x =worldTransform_.translation_.x;
	worldPos.y =worldTransform_.translation_.y;
	worldPos.z =worldTransform_.translation_.z;
	
	
	return worldPos;

}

AABB Enemy::GetAABB() { 
	Vector3 worldPos =GetWorldPosition();

AABB aabb;

aabb.min ={worldPos.x-kWidth/2.0f,worldPos.y-kHeight/2.0f,worldPos.z-kWidth/2.0f};
aabb.max ={worldPos.x+kWidth/2.0f,worldPos.y+kHeight/2.0f,worldPos.z+kWidth/2.0f};
return aabb;
}

void Enemy::OnCollision(const Player* player) {
(void)player;

}
