#include "CameraController.h"
#include "Player.h"
#include "MassFunction.h"
using namespace KamataEngine;
void CameraController::Initialize(Camera *camera){
	camera_=camera;

};
void CameraController::Update(){
      const WorldTransform& targetWorldTransform = target_->GetWorldTransform();  
       camera_->translation_ =   Add (targetWorldTransform.translation_,targetOffset_);
	  camera_->UpdateMatrix();
}


void CameraController::Reset() {  
    
        const WorldTransform& targetWorldTransform = target_->GetWorldTransform();  
        // 必要に応じて targetWorldTransform を使用して処理を追加 
    
        camera_->translation_ =   Add (targetWorldTransform.translation_,targetOffset_);
}
