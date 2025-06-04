#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include <vector>
#include "MassFunction.h"
#include "Skydome.h"
#include "MapchipField.h"
#include "CameraController.h"

using namespace KamataEngine ;


class GameScene {
private:
	//3Dモデル
	Model* model_ = nullptr;
	
	Model* blockM_ = nullptr;


	// texture
	uint32_t teXtureHandle_ = 0;
	//
	
	// カメラ
	KamataEngine::Camera camera_;
	// 自キャラ
	Player* player_=nullptr;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	bool isDebugCameraActive_ = false;
	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	// スカイドーム
	Skydome* skydome_ = nullptr;
	// スカイドームのモデル
	Model* modelSkydome_ = nullptr;
	// mapchipField
	 MapChipField* mapchipField_ ;
	// カメラクラス
	 CameraController* cameraControlle_;
	


public:
	
	//// デストラクタ
	~GameScene();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();
	//
	void GenerateBlock();

};
