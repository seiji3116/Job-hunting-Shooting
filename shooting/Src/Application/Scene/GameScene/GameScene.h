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

	// ノードの最大数
	static const int NODE_NUM = 12;
};