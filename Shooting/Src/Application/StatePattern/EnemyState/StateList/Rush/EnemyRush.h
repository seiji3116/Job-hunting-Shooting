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
	bool m_rashFlg;
	bool m_standFlg;

	float m_rashCnt;
};