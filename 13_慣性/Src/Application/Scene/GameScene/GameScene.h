#pragma once
#include "../BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
public:

	GameScene() { Init(); }
	~GameScene() {}

private:
	//�I�[�o�[���C�h�����ꍇ�e�̏����͍s���Ȃ��Ȃ�
	void Event()override;
	void Init()override;

};