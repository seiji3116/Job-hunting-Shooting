#pragma once
#include "Application/Scene/BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:
	TitleScene() { Init(); }
	~TitleScene() {}

private:
	void Event()override;
	void Init()override;
};