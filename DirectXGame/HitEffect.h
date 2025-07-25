#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
class HitEffect {
public:
	
	void Update();
	void Draw() ;
	static void SetModel(Model* model) { model_ = model; }
	static void SetCamera(Camera* camera) { camera_ = camera; }
	static HitEffect* Create(const Vector3& position) ;
private:
void Initialize(const Vector3& position) ;
	static Model* model_ ;
	static Camera* camera_;
	// 円形エフェクト
	WorldTransform circleWorldTransform_;
	static const inline uint32_t kellipseEffectNum = 2;
	std::array<WorldTransform,kellipseEffectNum>ellipseWorldTransforms_;
};
