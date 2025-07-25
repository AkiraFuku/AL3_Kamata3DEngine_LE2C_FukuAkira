#include <cassert>
#include <random>
#include <numbers>
#include "HitEffect.h"
#include "MassFunction.h"


Model* HitEffect::model_ = nullptr;
Camera* HitEffect::camera_ = nullptr;


void HitEffect::Initialize(const Vector3& position){
		std::random_device seedGenerator;
		std::mt19937_64 randomEngine;
	randomEngine.seed(seedGenerator());
	std::uniform_real_distribution<float> rotationDistribution(-std::numbers::pi_v<float>, std::numbers::pi_v<float>);

	for (WorldTransform& worldTransform:ellipseWorldTransforms_) {
		worldTransform.scale_={0.1f,1.5f,1.0f};
		worldTransform.rotation_={0.0f,0.0f,rotationDistribution(randomEngine)};
		worldTransform.translation_=position;
		worldTransform.Initialize();
	}
	circleWorldTransform_.translation_=position;
	circleWorldTransform_.Initialize();
	circleWorldTransform_.translation_.z = -1.0f;
}
void HitEffect::Update(){
for (WorldTransform& worldTransform:ellipseWorldTransforms_) {
	WorldTransformUpdate(&worldTransform);
}
WorldTransformUpdate(&circleWorldTransform_);
}
void HitEffect::Draw(){
	assert(model_);
	assert(camera_);
	for (WorldTransform& worldTransform:ellipseWorldTransforms_) {
		model_->Draw(worldTransform,*camera_);
	}
	model_->Draw(circleWorldTransform_,*camera_);
}
HitEffect* HitEffect::Create(const Vector3& position){ 
	HitEffect* instance = new HitEffect();
	
	assert(instance);
	instance->Initialize(position);
	return instance;
}