#pragma once
#include "../BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() {}

private:
	//オーバーライドした場合親の処理は行われなくなる
	void Event()override;
	void Init()override;

};