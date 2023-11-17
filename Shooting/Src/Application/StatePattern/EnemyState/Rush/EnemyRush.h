#pragma once
#include "../../BaseState.h"

class EnemyRush :public BaseState
{
public:
	void Init(KdGameObject& _owner)override;
	void Update(KdGameObject& _owner)override;
	void Shot(KdGameObject& _owner)override;
	void Action(KdGameObject& _owner)override;

private:
	void Rush();
	void Stand();
	void Rotate(Math::Vector3 _targetDir) override;

private:
	bool m_rashFlg;
};