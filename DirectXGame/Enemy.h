#pragma once
#include "KamataEngine.h"
#include "MassFunction.h"
#include <numbers>
#include <algorithm>
using namespace KamataEngine;

class Enemy {
public:
	void Initialize(Model* model,Camera* camera,Vector3& position);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	Vector3 GetWorldPosition();
	AABB GetAABB();

private:
	WorldTransform worldTransform_; ///< ワールドトランスフォーム
	Model* model_ = nullptr;    
	Camera* camera_=nullptr;
	static inline const float kWalkSpeed=0.02f ;
	Vector3 velocity_={};
	static inline const float kWalkMotionAngleStart=0.0f;
	static inline const float kWalkMotionAngleEnd=30.0f;
	static inline const float kWalkMotionTime=1.0f;
	float walkTimer_=0.0f;
	static inline const float kWidth = 0.8f; ///< キャラクターの幅
	static inline const float kHeight = 0.8f; ///< キャラクターの高さ
	static inline const float kBlank = 0.04f; ///< キャラクターの余白
};
 