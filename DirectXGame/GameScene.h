#pragma once
#include "KamataEngine.h"

// ゲームシーン
class GameScene {
public:
	//// コンストラクタ
	//GameScene();
	//// デストラクタ
	~GameScene();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	
private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// サウンドデータハンドル
	uint32_t soundDataHandle_ = 0;
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;


	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// モデルのワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;
	// カメラ
	KamataEngine::Camera camera_ ;
	//
	KamataEngine::DebugCamera* debugCamera_=nullptr;






};
