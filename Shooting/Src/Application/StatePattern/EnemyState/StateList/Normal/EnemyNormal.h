#pragma once
#include "../../EnemyBaseState.h"

class EnemyNormal :public EnemyBaseState
{
public:
	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void Shot()override;
	void Action()override;

private:
	void Rotate(Math::Vector3 _targetDir) override;
	void UpdatePos();

private:

	// çÏã∆ópçsóÒ
	static const int GHOST_MAX = 60;
	Math::Vector3 m_ghostTargetPos[GHOST_MAX];
};