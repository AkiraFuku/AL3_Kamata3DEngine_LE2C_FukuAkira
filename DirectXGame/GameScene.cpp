#include "GameScene.h"
#include "ImGui.h"
using namespace KamataEngine;

//GameScene::GameScene() {}
//
GameScene::~GameScene() { 
	delete sprite_;
	delete model_;
	delete debugCamera_;
}
//  ゲームシーンの初期化
void GameScene::Initialize() {
	textureHandle_ = TextureManager::Load("img_thumb_08_01.png");
	// スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	model_ = Model::Create();
	// モデルのワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// カメラの初期化
	camera_.Initialize();
	//
	soundDataHandle_ = Audio::GetInstance()->LoadWave("mokugyo.wav");
	//Audio::GetInstance()->PlayWave(soundDataHandle_);

	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_,true);

	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	debugCamera_ = new DebugCamera(1280,720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());
}
// ゲームシーンの更新
void GameScene::Update() {

	
		//ImGui::Begin("Debug1");
		ImGui::Text("Kamata Tarou %d.%d.%d",2050,12,31);
		//ImGui::End();
	//#endif // DEBUG


Vector2 position = sprite_->GetPosition();
	position.x += 2.0f;
	position.y += 1.0f;
	sprite_->SetPosition(position);
//	
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		Audio::GetInstance()->StopWave(voiceHandle_);
	}
	debugCamera_->Update();
}
// ゲームシーンの描画
void GameScene::Draw() {
	// DirectXcomonインスタンスを取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance(); 

	//// スプライトの描画前処理
	Sprite::PreDraw(dxCommon->GetCommandList());

	////
	sprite_->Draw();

	//// スプライトの描画後処理
	Sprite::PostDraw();

	// モデルの描画
	Model::PreDraw(dxCommon->GetCommandList());

	//
	model_->Draw(worldTransform_, debugCamera_->GetCamera(), textureHandle_);

	Model::PostDraw();
	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});
}
