#pragma once
#include "../../PlayerState.h"

class AttackState :public PlayerState
{
public:
	void Init(std::string_view _modelName, Math::Vector3 _pos, Math::Vector3 _dir) override;
	void Update(Math::Vector3 _pos = Math::Vector3::Zero, Math::Vector3 _dir = Math::Vector3::Zero) override;
	Math::Vector3 GetPos() const override { return m_pos; };
	Math::Vector3 GetDir() const override { return m_moveDir; };
	std::shared_ptr<KdAnimator> GetAnime() const override { return m_animator; };
	float GetAnimeSpeed() const override { return m_animeSpd; };
	float GetHitDamage() const override;

private:
	enum AttackOrder
	{
		FirstAttack,
		SecondAttack,
		ThirdAttack,
		FourthAttack,
	};

	void Action();

	float m_attackCnt;				// ��莞�Ԍo�߂ōU�����[�V�������ŏ��ɖ߂�
	bool m_attackKeyFlg;			// �U���p�̃L�[�t���O 
	bool m_attackFlg;				// ���U�����悤�Ƃ��Ă���̂��ϑ�
	AttackOrder m_attackOrder;		// ���Ԗڂ̍U��������p
	AttackOrder m_nextAttackOrder;	// ���̍U���͉���
	bool m_keyFlg;
};