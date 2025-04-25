#include "GameScene.h"

using namespace KamataEngine;

//GameScene::GameScene() {}
//
GameScene::~GameScene() { 
	delete player_;
	delete model_;
	///
	delete blockM_;
	//
	for (WorldTransform*WorldTransformBlock:WorldTransformBlocks_) {
		delete WorldTransformBlock;
	}
	WorldTransformBlocks_.clear();
}
//  ゲームシーンの初期化
void GameScene::Initialize() {
	teXtureHandle_ = TextureManager::Load("img_thumb_08_01.png");
	// モデルの生成
	model_=Model::Create();
	
	
	camera_.Initialize();
	//自キャラ生成
	player_ = new Player();
	player_->Initialize(model_,teXtureHandle_,&camera_);
	//	//ブロックモデル生成
	blockM_ = Model::Create();
	///ブロック要素数
	const uint32_t kNumBlockHorizontal = 20;
	//ブロック1個横幅
	const float kBlockWidth = 2.0f;
	//要素数の変更
	WorldTransformBlocks_.resize(kNumBlockHorizontal);
	//キューブの生成
	for (uint32_t i = 0; i < kNumBlockHorizontal; i++) {
		WorldTransformBlocks_[i] = new WorldTransform();
		WorldTransformBlocks_[i]->Initialize();
		WorldTransformBlocks_[i]->translation_.x =  kBlockWidth*i;
		WorldTransformBlocks_[i]->translation_.y = 0.0f;
	}



}
// ゲームシーンの更新
void GameScene::Update() {
player_->Update();
	///// ブロックの更新
	for (WorldTransform*WorldTransformBlock:WorldTransformBlocks_  ) {
		//アフィン変換
		


	}
}
// ゲームシーンの描画
void GameScene::Draw() { 

	DirectXCommon* dxCommon =DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList() );
	// カメラの描画
	player_->Draw();

	Model::PostDraw();
}
