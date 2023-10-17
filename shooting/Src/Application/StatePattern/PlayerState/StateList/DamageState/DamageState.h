#pragma once
#include "../../PlayerState.h"

class DamageState :public PlayerState
{
public:
	void Init(std::string_view _modelName, Math::Vector3 _pos = Math::Vector3::Zero, Math::Vector3 _dir = Math::Vector3::Zero) override;
	void Update(Math::Vector3 _pos = Math::Vector3::Zero, Math::Vector3 _dir = Math::Vector3::Zero) override;
	Math::Vector3 GetPos() const override { return m_pos; };
	Math::Vector3 GetDir() const override { return m_moveDir; };
	std::shared_ptr<KdAnimator> GetAnime() const override { return m_animator; };
	float GetAnimeSpeed() const override { return m_animeSpd; };
	float GetHitDamage() const override { return 0.0f; };

private:
};