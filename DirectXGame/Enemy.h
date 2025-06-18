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

private:
	WorldTransform worldTransform_; ///< ワールドトランスフォーム
	Model* model_ = nullptr;    
	Camera* camera_=nullptr;
	
};
 