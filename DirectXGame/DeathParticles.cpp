#include "DeathParticles.h"
#include "MassFunction.h"
void DeathParticles::Initialze(Model* model, Camera* camera, const Vector3& position) {
model_=model;
camera_=camera;
for (WorldTransform& worldTransform:worldTransforms_) {
	worldTransform.Initialize();
	worldTransform.translation_=position;
}

}
void DeathParticles::Update(){
for (WorldTransform& worldTransform:worldTransforms_) {
 WorldTransformUpdate(&worldTransform);
}
}
void DeathParticles::Draw(){
	for (WorldTransform& worldTransform:worldTransforms_) {
	model_->Draw(worldTransform,*camera_);
	}

}
