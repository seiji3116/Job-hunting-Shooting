#pragma once
#include "../../BaseState.h"

class Laser;
class Enemy;

class EnemyLaser :public BaseState
{
public:
	void Init(KdGameObject& _owner)override;
	void Update(KdGameObject& _owner)override;
	void Shot(KdGameObject& _owner)override;
	void Action(KdGameObject& _owner)override;

private:
	void Rotate(Math::Vector3 _targetDir) override;

private:
	std::shared_ptr<Laser> m_laser;
	bool m_laserFlg;
};