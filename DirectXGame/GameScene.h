#pragma once
#include "KamataEngine.h"
#include "Player.h"

// ゲームシーン
class GameScene {
private:
	//3Dモデル
	KamataEngine::Model* model_ = nullptr;
	// texture
	uint32_t teXtureHandle_ = 0;
	//
	
	// カメラ
	KamataEngine::Camera* camera_;
	// 自キャラ
	Player* player_=nullptr;


public:
	
	//// デストラクタ
	~GameScene();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();

};
