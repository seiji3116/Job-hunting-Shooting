#pragma once
#include "Application/Scene/BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
public:
	GameScene() { Init(); }
	~GameScene() {}

private:
	void Event()override;
	void Init()override;

	// ƒm[ƒh‚ÌÅ‘å”
	static const int NODE_NUM = 12;
};