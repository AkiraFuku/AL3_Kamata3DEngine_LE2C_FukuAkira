#include "GameScene.h"

using namespace KamataEngine;

//GameScene::GameScene() {}
//
GameScene::~GameScene() { 
	delete player_;
	delete model_;
}
//  ゲームシーンの初期化
void GameScene::Initialize() {
	teXtureHandle_ = TextureManager::Load("");
	model_=Model::Create();
	
	
	camera_.Initialize();
	//自キャラ生成
	player_ = new Player();
	player_->Initialize(model_,teXtureHandle_,camera_);
}
// ゲームシーンの更新
void GameScene::Update() {
player_->Update();
}
// ゲームシーンの描画
void GameScene::Draw() { 
	player_->Draw();
}
