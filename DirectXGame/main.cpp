#include <Windows.h>
#include "KamataEngine.h"
#include "GameScene.h"
using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	// エンジンの初期化
	KamataEngine::Initialize();
	//DirectX
	DirectXCommon* dxCommon =DirectXCommon::GetInstance();
	GameScene* gameScene = new GameScene();
	// ゲームシーンの初期化
	gameScene->Initialize();
	// メインループ
	while (true) {
		// エンジンの更新
		if (
			KamataEngine::Update()) {
		}
		// ゲームシーンの更新
		gameScene->Update();
		//描画開始
		dxCommon->PreDraw();
		
		///
		/// 描画処理
		///
		gameScene->Draw();
		/// 
		/// 描画処理 
		///
		
		//描画終了
		dxCommon->PostDraw();

	}
	// ゲームシーンの終了
	delete gameScene;
	gameScene = nullptr;
	// エンジンの終了処理
	KamataEngine::Finalize();
	return 0;
}
