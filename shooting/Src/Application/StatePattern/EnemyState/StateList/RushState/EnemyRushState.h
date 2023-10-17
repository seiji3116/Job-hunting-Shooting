#pragma once
#include "../../EnemyState.h"

class EnemyRushState :public EnemyState
{
public:
	void Init(std::string_view _modelName, Math::Vector3 _pos = Math::Vector3::Zero, Math::Vector3 _dir = Math::Vector3::Zero) override;
	void Update(Math::Vector3 _pos = Math::Vector3::Zero, Math::Vector3 _dir = Math::Vector3::Zero) override;
	Math::Vector3 GetPos() const override { return m_pos; };
	Math::Vector3 GetDir() const override { return m_moveDir; };
	std::shared_ptr<KdAnimator> GetAnime() const override { return m_animator; };
	bool GetCollisionFlg() const override;
	float GetAnimeSpeed() const override { return m_animeSpd; };
	bool GetStateChengeFlg() const override;
	bool GetActionFlg() const override;
	float GetHitDamege() const override { return 20.0f; };
	void SetDir(Math::Vector3 _dir) override;

private:
};