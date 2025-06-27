#include "TitleScene.h"
void TitleScene::Initialize(){};
void TitleScene::Update() {
	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		finished_ = true;
	}
};
void TitleScene::Draw(){
DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());


	Model::PostDraw();
};