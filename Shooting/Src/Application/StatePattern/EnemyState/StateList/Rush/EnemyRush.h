#pragma once
#include "../../EnemyBaseState.h"

class EnemyRush :public EnemyBaseState
{
public:
	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void Shot()override;
	void Action()override;

private:
	void Rush();
	void Stand();
	void Rotate(Math::Vector3 _targetDir) override;

private:
	bool m_rashFlg;
};