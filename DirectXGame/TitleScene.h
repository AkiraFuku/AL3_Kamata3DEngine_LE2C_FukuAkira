#pragma once
#include "KamataEngine.h"
#include "Fade.h"
using namespace KamataEngine;
class TitleScene {
public:
	~TitleScene();
	void Initialize();
	void Update();
	void Draw();

	bool IsFinished()  { return finished_; }

private:
	static inline const float kTimeTitleMove = 2.0f;

	// ビュープロジェクション
	Camera camera_;
	WorldTransform worldTransformTitle_;
	WorldTransform worldTransformPlayer_;
	float counter_ = 0.0f;
	bool finished_ = false;
	Model* titleModel_;
	Model* playerModel_;
	Fade* fade_=nullptr;
};
