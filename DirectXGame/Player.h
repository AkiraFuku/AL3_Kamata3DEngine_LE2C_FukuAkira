#pragma once
#define NOMINMAX
#include "KamataEngine.h"
#include "MassFunction.h"
#include <numbers>
#include <algorithm>

using namespace KamataEngine;
/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:

	enum class LRDirection { kRight, kLeft,  };

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model,uint32_t textureHandle,Camera* camera,const Vector3& position );
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
	Model* model_ = nullptr;        ///< モデル
	uint32_t textureHandle_ = 0u;    ///< テクスチャハンドル
	Camera* camera_=nullptr;      ///< カメラ
	Vector3 velocity_ = {}; ///< 速度
	static inline const float kAcceleration = 0.1f; ///< 移動速度
	static inline const float kAttenution = 0.1f;   ///< 減速
	static inline const float kLimitRunSpeed = 1.0f; ///< 最大速度
	LRDirection lrDirection_ = LRDirection::kRight; ///< キャラクターの向き
	// 旋回開始時角度
	float turnFirstRotationY_ = 0.0f;
	//旋回タイマー
	float turnTimer_ = 0.0f;
	// 旋回時間<秒>
	static inline const float kTimeTurn =0.3f;
	bool onGround_=true;
	static inline const float kGravityAcceleration=0.1f;
	static inline const float  kLimitFallSpeed = 1.0f;
	static inline const float kJumpAcceleration=0.1f;


};
