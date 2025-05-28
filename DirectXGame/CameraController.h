#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

class Player;
class CameraController {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Camera *camera );

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void SetTarget(Player* target) { target_ = target; }

	void Reset();

	private:
		// カメラ
		Camera* camera_=nullptr;
		Player* target_=nullptr;

		Vector3 targetOffset_ = {0.0f, 0.0f, -15.0f};
		
};
