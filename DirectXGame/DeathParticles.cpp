#include "DeathParticles.h"

void DeathParticles::Initialze(Model* model, uint32_t textureHandle, Camera* camera, const Vector3& position) {
model_=model;
camera_=camera;
for (WorldTransform& worldTransform:worldTransforms_) {
	worldTransform.Initialize();
	worldTransform.translation_=position;
}

}
void DeathParticles::Update(){}
void DeathParticles::Draw(){}
