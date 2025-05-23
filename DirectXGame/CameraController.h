#pragma once
#include <KamataEngine.h>
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
};
