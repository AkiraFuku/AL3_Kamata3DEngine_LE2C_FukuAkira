#pragma once
#include <KamataEngine.h>
#include "Player.h"
class CameraController {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	private:
		// カメラ
		KamataEngine::Camera camera_;
		Player* target_=nullptr;
		
};
