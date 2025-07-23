#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include <vector>
//#include "MassFunction.h"
#include "Skydome.h"
#include "MapchipField.h"
#include "CameraController.h"
#include "Enemy.h"
#include "DeathParticles.h"
#include "Fade.h"
#include "HitEffect.h"
using namespace KamataEngine ;


class GameScene {
private:
	//3Dモデル
	Model* model_ = nullptr;
	Model* AttackModel_ = nullptr;
	
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

	 //エネミー
	 std::list<Enemy*> enemies_;
	 Model* enemy_model_=nullptr ;

	 //デスパーティクル
	 DeathParticles* deathParticles_;
	 Model* deathParticlesModel_=nullptr;

	 //フェーズ
	 enum class Phase{

		 kFadeIn, // フェードイン
		 kPlay, // プレイ中
		 kDeath, // 死亡
		 kFadeOut, // フェードアウト
	 };
	 Phase phase_ = Phase::kPlay;

	 bool finished_ = false; // ゲーム終了フラグ	
	 
	 // フェード
	 Fade* fade_ = nullptr;

	 // ヒットエフェクト
	 HitEffect* hitEffect_ = nullptr;
	 Model* hitEffectModel_ = nullptr;
	 

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
	//当たり判定
	void CheckAllCollisions();
	// フェーズの切り替え
	void ChangePhase();

	// ゲーム終了
	bool IsFinished() const { return finished_; }
	
};
