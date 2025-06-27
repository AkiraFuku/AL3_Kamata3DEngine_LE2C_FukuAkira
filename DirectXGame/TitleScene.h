#pragma once  
#include "KamataEngine.h"
using namespace KamataEngine;
class TitleScene {  
public:  
	void Initialize();  
	void Update();  
	void Draw(); 
	bool IsFinished() const { return finished_; }

private:
	bool finished_ = false;
	Model titleModel_;
	Model playerModel_;

};
