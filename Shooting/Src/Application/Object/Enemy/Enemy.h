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

private:
	std::unique_ptr<EnemyStateManager> m_stateMan;

	std::weak_ptr<Player> m_wpPlayer;

	std::shared_ptr<KdModelWork> m_model;

	Math::Vector3 m_pos;
	Math::Vector3 m_moveDir;
	Math::Vector3 m_scale;
	Math::Matrix m_transMat;				// ˆÚ“®s—ñ
	Math::Matrix m_rotateMat;				// ‰ñ“]s—ñ
	Math::Matrix m_scaleMat;				// Šgks—ñ

	float m_roll = 0;						// z²—p‰ñ“]—Ê
	float m_pitch = 0;						// x²—p‰ñ“]—Ê
};