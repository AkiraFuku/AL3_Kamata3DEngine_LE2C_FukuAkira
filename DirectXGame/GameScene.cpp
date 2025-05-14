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
	for (std::vector<WorldTransform*>&worldTransformBlockLine:WorldTransformBlocks_) {
		for (WorldTransform*WorldTransformBlock:worldTransformBlockLine) {
			delete WorldTransformBlock;
		}
	}
	
	WorldTransformBlocks_.clear();
	// デバッグカメラの解放
	delete debugCamera_;
	// スカイドームの解放
	delete skydome_;
	// スカイドームのモデルの解放
	delete modelSkydome_;
	// マップチップフィールドの解放
	delete mapchipField_;
}
// ゲームシーンのブロック生成
void GameScene::GenerateBlock() {
	///ブロック要素数
	uint32_t numBlockVertical = mapchipField_->GetNumBlockVertical();
	uint32_t numBlockHorizontal = mapchipField_->GetNumBlockHorizontal();
	WorldTransformBlocks_.resize(numBlockVertical);
	for (uint32_t i = 0; i < numBlockVertical; i++) {
		WorldTransformBlocks_[i].resize(numBlockHorizontal);
	}
	//キューブの生成
	for (uint32_t i = 0; i < numBlockVertical; i++) {
		for (uint32_t j = 0; j < numBlockHorizontal; j++) {
			if ((i+j)%2==1) {continue;}
			
					WorldTransformBlocks_[i][j] = new WorldTransform()	;
					WorldTransformBlocks_[i][j]->Initialize();
					WorldTransformBlocks_[i][j]->translation_.x =  kBlockWidth*j;
					WorldTransformBlocks_[i][j]->translation_.y = kBlockHeight*i;
		
					
		
			
		}
	}
}


//  ゲームシーンの初期化
void GameScene::Initialize() {
	teXtureHandle_ = TextureManager::Load("img_thumb_08_01.png");
	// モデルの生成
	model_= Model::CreateFromOBJ("player",true);
	
	
	
	camera_.Initialize();
	//自キャラ生成
	player_ = new Player();
	player_->Initialize(model_,teXtureHandle_,&camera_);
	//	//ブロックモデル生成
	blockM_ = Model::CreateFromOBJ("block",true);
	///ブロック要素数
	 const uint32_t kNumBlockVertical = 10;
	const uint32_t kNumBlockHorizontal = 20;
	//ブロック1個横幅
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;

	//要素数の変更
	WorldTransformBlocks_.resize(kNumBlockVertical);
	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		WorldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}
	// マップチップフィールドの生成
	mapchipField_ = new MapchipField();
	mapchipField_->LoadMapChipCsv("Resources/blocks.csv");

	//キューブの生成
	for (uint32_t i = 0; i < kNumBlockVertical; i++) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			if ((i+j)%2==1) {continue;}
			
					WorldTransformBlocks_[i][j] = new WorldTransform()	;
					WorldTransformBlocks_[i][j]->Initialize();
					WorldTransformBlocks_[i][j]->translation_.x =  kBlockWidth*j;
					WorldTransformBlocks_[i][j]->translation_.y = kBlockHeight*i;
		
					
		
			
		}
	}

	///
	GenerateBlock();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(WinApp::kWindowWidth,WinApp::kWindowHeight);
	// スカイドームのモデル生成
	modelSkydome_ = Model::CreateFromOBJ("skydome",true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_,&camera_);
	


}
// ゲームシーンの更新
void GameScene::Update() {
	player_->Update();
	///// ブロックの更新
	for (std::vector<WorldTransform*>&worldTransformBlockLine:WorldTransformBlocks_) {
		for (WorldTransform*WorldTransformBlock:worldTransformBlockLine  ) {
			if (!WorldTransformBlock) {continue;}
			//アフィン変換
			WorldTransformBlock->matWorld_ = MakeAfineMatrix(
			WorldTransformBlock->scale_,
			WorldTransformBlock->rotation_,
			WorldTransformBlock->translation_
			);
			// ワールド行列の転送
			WorldTransformBlock->TransferMatrix();



		}
	}
	// スカイドームの更新
	skydome_->Update();
}
// ゲームシーンの描画
void GameScene::Draw() { 
	///
	DirectXCommon* dxCommon =DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList() );
	// カメラの描画
	player_->Draw();
	// ブロックの描画
	for (std::vector<WorldTransform*>&worldTransformBlockLine:WorldTransformBlocks_) {

		for (WorldTransform* WorldTransformBlock :worldTransformBlockLine ) {
			if (!WorldTransformBlock) {continue;}
			blockM_->Draw(*WorldTransformBlock,camera_);
		}
	}
	// スカイドームの描画
	skydome_->Draw();
	///
	Model::PostDraw();

	#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_TAB)) {
		if (!isDebugCameraActive_) {
			isDebugCameraActive_ = true;
		} else {
			isDebugCameraActive_ = false;
		}
	}
	#endif // _DEBUG
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		//
		camera_.TransferMatrix();
	} else {
		camera_.TransferMatrix();
	}
	

	
}

