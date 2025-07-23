#include "HitEffect.h"
void HitEffect::Initialize(const Vector3& position){}
void HitEffect::Update(){}
void HitEffect::Draw(){}
HitEffect* HitEffect::Create(const Vector3& position){ 
	HitEffect* instance = new HitEffect();
	
	assert(instance);
	instance->Initialize(position);
	return instance;
}