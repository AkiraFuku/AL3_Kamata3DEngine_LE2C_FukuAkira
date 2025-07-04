#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
class Fade {
	public:
		void Initialize();
		void Update_();
		void Draw_();

	private:
	    Sprite* sprite_ = nullptr;
};
