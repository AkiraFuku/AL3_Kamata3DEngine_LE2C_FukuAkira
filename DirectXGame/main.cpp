#include <Windows.h>
#include "KamataEngine.h"
#include "TitleScene.h"
#include "GameScene.h"
using namespace KamataEngine;
GameScene* gameScene=nullptr;
TitleScene* titleScene = nullptr;
enum class Scene {

	kUnknown = 0, // 不明なシーン
	kTitle,       // タイトルシーン
	kGame,        // ゲームシーン

};
Scene scene = Scene::kUnknown; 

void ChangeScene();


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	// エンジンの初期化
	KamataEngine::Initialize();
	//DirectX
	DirectXCommon* dxCommon =DirectXCommon::GetInstance();

	//gameScene = new GameScene();
	// ゲームシーンの初期化
	//gameScene->Initialize();
	scene = Scene::kTitle; // シーンをタイトルに設定
	// タイトルシーンのインスタンスを生成
	titleScene = new TitleScene;
	// タイトルシーンの初期化
	titleScene->Initialize();
	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
		}
		// ゲームシーンの更新
	//	gameScene->Update();
	// 
		titleScene->Update();	
		//描画開始
		dxCommon->PreDraw();
		
		///
		/// 描画処理
		///
		//gameScene->Draw();
		titleScene->Draw();
		/// 
		/// 描画処理 
		///
		
		//描画終了
		dxCommon->PostDraw();

	}
	// ゲームシーンの終了
	//delete gameScene;
	delete titleScene;
	// エンジンの終了処理
	KamataEngine::Finalize();
	return 0;
}
void ChangeScene() {
	switch (scene) {
	
	case Scene::kTitle:
		if (titleScene->IsFinished()) {
			//シーン変更
			scene = Scene::kGame;
			// タイトルシーンの終了処理
			delete titleScene;
			titleScene = nullptr;
			// ゲームシーンのインスタンスを生成
			gameScene = new GameScene;
			// ゲームシーンの初期化
			gameScene->Initialize();
		}
		break;
	case Scene::kGame:
		break;
	default:
		break;
	}
}
