#pragma once
#include "../../EnemyBaseState.h"

class EnemyLaser :public EnemyBaseState
{
public:
	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void Shot()override;
	void Action()override;

private:
};