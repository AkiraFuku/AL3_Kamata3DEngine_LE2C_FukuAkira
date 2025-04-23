#pragma once
#include "KamataEngine.h"
using namespace KamataEngine;
/// <summary>
/// 自キャラ
/// </summary>
class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model,uint32_t textureHandle,Camera* camera);
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
};
