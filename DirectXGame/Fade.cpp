#include "Fade.h"

void Fade::Initialize(){
	sprite_= Sprite::Create(0,Vector2{});
	sprite_->SetSize(Vector2(WinApp::kWindowWidth, WinApp::kWindowHeight));
	sprite_->SetColor(Vector4(0, 0, 0,1.0f));
};
void Fade::Update_(){

};
void Fade::Draw_() {
	Sprite::PreDraw(DirectXCommon::GetInstance()->GetCommandList());
	sprite_->Draw();
	Sprite::PostDraw();

};
