#pragma once
#include "../../EnemyBaseState.h"

class EnemyTracking :public EnemyBaseState
{
public:
	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void Shot()override;
	void Action()override;

private:
	void Rotate(Math::Vector3 _targetDir) override;
};