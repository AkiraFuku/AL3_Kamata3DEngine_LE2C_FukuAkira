#include "TitleScene.h"
#include "MassFunction.h"
#include <numbers>
TitleScene::~TitleScene() {
	delete titleModel_;
	delete playerModel_;
}
void TitleScene::Initialize() {
	titleModel_ = Model::CreateFromOBJ("titleFont", true);
	playerModel_ = Model::CreateFromOBJ("player");
	// カメラ初期化
	camera_.Initialize();
	const float kPlayerTitle = 2.0f;

	worldTransformTitle_.Initialize();

	worldTransformTitle_.scale_ = {kPlayerTitle, kPlayerTitle, kPlayerTitle};

	const float kPlayerScale = 10.0f;

	worldTransformPlayer_.Initialize();

	worldTransformPlayer_.scale_ = {kPlayerScale, kPlayerScale, kPlayerScale};

	worldTransformPlayer_.rotation_.y = 0.95f * std::numbers::pi_v<float>;

	worldTransformPlayer_.translation_.x = -2.0f;

	worldTransformPlayer_.translation_.y = -10.0f;
};
void TitleScene::Update() {
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}
	counter_ += 1.0f / 60.0f;
	counter_ = std::fmod(counter_, kTimeTitleMove);

	float angle = counter_ / kTimeTitleMove * 2.0f * std::numbers::pi_v<float>;

	worldTransformTitle_.translation_.y = std::sin(angle) + 10.0f;

	camera_.TransferMatrix();

	// アフィン変換～DirectXに転送(タイトル座標)
	WorldTransformUpdate(&worldTransformTitle_);

	// アフィン変換～DirectXに転送（プレイヤー座標）
	WorldTransformUpdate(&worldTransformPlayer_);
};
void TitleScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon->GetCommandList();
	Model::PreDraw(commandList);
	playerModel_->Draw(worldTransformPlayer_, camera_);
	titleModel_->Draw(worldTransformTitle_, camera_);
	Model::PostDraw();
};