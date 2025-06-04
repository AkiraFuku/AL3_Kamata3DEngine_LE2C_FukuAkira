#pragma once
#define NOMINMAX
#include "KamataEngine.h"
#include "MassFunction.h"
#include <numbers>
#include <algorithm>

using namespace KamataEngine;
class MapChipField;
/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:

	enum class LRDirection { kRight, kLeft,  };

struct CollisionMapInfo {
		bool isCeiling = false; ///< 天井に衝突しているか
		bool isFloor = false;   ///< 床に衝突しているか
		bool isWall = false;    ///< 壁に衝突しているか
		Vector3 moveParameter = {}; ///< 移動パラメータ
	};
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

	//WorldTransform GetWorldTransform() const { return worldTransform_; }
    /// <summary>
    /// ワールドトランスフォームの参照を取得
    /// </summary>
    /// <returns>ワールドトランスフォームの参照</returns>
    const WorldTransform& GetWorldTransform() const { return worldTransform_; }
	const Vector3& getVelocity() const { return velocity_; }
	
	void SetMapchipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }
	void MapCollisionCheck(CollisionMapInfo& collisionMapInfo);
	void inputMove();

private:
	WorldTransform worldTransform_; ///< ワールドトランスフォーム
	Model* model_ = nullptr;        ///< モデル
	uint32_t textureHandle_ = 0u;    ///< テクスチャハンドル
	Camera* camera_=nullptr;      ///< カメラ
	Vector3 velocity_ = {}; ///< 速度
	static inline const float kAcceleration = 0.01f; ///< 移動速度
	static inline const float kAttenution = 0.05f;   ///< 減速
	static inline const float kLimitRunSpeed = 0.3f; ///< 最大速度
	LRDirection lrDirection_ = LRDirection::kRight; ///< キャラクターの向き
	// 旋回開始時角度
	float turnFirstRotationY_ = 0.0f;
	//旋回タイマー
	float turnTimer_ = 0.0f;
	// 旋回時間<秒>
	static inline const float kTimeTurn =0.3f;
	bool onGround_=true;
	//重力加速度
	static inline const float kGravityAcceleration=0.98f;
	//落下速度制限
	static inline const float  kLimitFallSpeed = 0.5f;
	//跳躍加速度
	static inline const float kJumpAcceleration=20.0f;
	MapChipField* mapChipField_ = nullptr; ///< マップチップフィールドへのポインタ
	static inline const float kWidth = 0.8f; ///< キャラクターの幅
	static inline const float kHeight = 0.8f; ///< キャラクターの高さ
	
};
