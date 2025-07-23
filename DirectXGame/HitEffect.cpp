#include "HitEffect.h"
#include "MassFunction.h"
void HitEffect::Initialize(const Vector3& position){

	circleWorldTransform_.translation_=position;
}
void HitEffect::Update(){

WorldTransformUpdate(&circleWorldTransform_);
}
void HitEffect::Draw(){
	model_->Draw(circleWorldTransform_,*camera_);
}
HitEffect* HitEffect::Create(const Vector3& position){ 
	HitEffect* instance = new HitEffect();
	
	assert(instance);
	instance->Initialize(position);
	return instance;
}