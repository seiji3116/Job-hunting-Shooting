#pragma once
#include "../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:

	TitleScene() { Init(); }
	~TitleScene() {}

private:
	//�I�[�o�[���C�h�����ꍇ�e�̏����͍s���Ȃ��Ȃ�
	void Event()override;
	void Init()override;


};