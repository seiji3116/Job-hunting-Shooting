#pragma once
#include "../../StatePattern/EnemyState/EnemyStateManager.h"

class Player;

class Enemy : public KdGameObject
{
public:

	Enemy() { Init(); };
	~Enemy() {};

	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void Init()override;
	void Update()override;
	void PostUpdate()override;

	void SetPlayer(std::shared_ptr<Player> _player)
	{
		m_wpPlayer = _player;
	}

private:
	enum State
	{
		Tracking,
		Normal,
		Rush,
		Laser
	};

private:
	std::unique_ptr<EnemyStateManager> m_stateMan;

	std::weak_ptr<Player> m_wpPlayer;

	std::shared_ptr<KdModelWork> m_model;

	Math::Vector3 m_pos;
	Math::Vector3 m_moveDir;
	Math::Vector3 m_scale;
	Math::Matrix m_transMat;				// 移動行列
	Math::Matrix m_rotateMat;				// 回転行列
	Math::Matrix m_scaleMat;				// 拡縮行列

	float m_roll = 0;						// z軸用回転量
	float m_pitch = 0;						// x軸用回転量

	State m_nowState;						// 現在のステート
};