#pragma once
#include "../../BaseState.h"

class EnemyNormal :public BaseState
{
public:
	void Init(KdGameObject& _owner)override;
	void Update(KdGameObject& _owner)override;
	void Shot(KdGameObject& _owner)override;
	void Action(KdGameObject& _owner)override;

private:
	void Rotate(Math::Vector3 _targetDir) override;
	void UpdatePos(const Math::Vector3& _targetPos);

private:

	// çÏã∆ópçsóÒ
	static const int GHOST_MAX = 60;
	Math::Vector3 m_ghostTargetPos[GHOST_MAX];
};