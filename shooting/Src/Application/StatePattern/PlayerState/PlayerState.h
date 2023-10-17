#pragma once

class PlayerState
{
public:
	virtual void Init(std::string_view _modelName, Math::Vector3 _pos, Math::Vector3 _dir) = 0;
	virtual void Update(Math::Vector3 _pos = Math::Vector3::Zero, Math::Vector3 _dir = Math::Vector3::Zero) = 0;
	virtual Math::Vector3 GetPos() const = 0;
	virtual Math::Vector3 GetDir() const = 0;
	virtual std::shared_ptr<KdAnimator> GetAnime() const = 0;
	virtual float GetAnimeSpeed() const = 0;
	virtual float GetHitDamage() const = 0;		// 現在のステートのDamage量

protected:
	std::shared_ptr<KdAnimator> m_animator = nullptr;	// モデルデータに含まれるアニメーション
	std::shared_ptr<KdModelWork> m_model = nullptr;		// モデルデータ
	float m_animeSpd = 0;								// アニメーションの再生速度

	Math::Vector3 m_pos = Math::Vector3::Zero;
	Math::Vector3 m_moveDir = Math::Vector3::Zero;
};