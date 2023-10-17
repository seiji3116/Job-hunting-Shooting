#include "AttackState.h"

void AttackState::Init(std::string_view _modelName, Math::Vector3 _pos = Math::Vector3::Zero, Math::Vector3 _dir = Math::Vector3::Zero)
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData(_modelName));
	m_attackOrder = AttackOrder::FirstAttack;
	m_nextAttackOrder = AttackOrder::FirstAttack;
	m_attackCnt = 60.f;
	m_attackFlg = false;
	m_keyFlg = false;
	m_animeSpd = 3.f;
	m_animator = std::make_shared<KdAnimator>();
	m_animator->SetAnimation(m_model->GetData()->GetAnimation("Attack1"), false);

	m_pos = _pos;
	m_moveDir = _dir;
}

void AttackState::Update(Math::Vector3 _pos, Math::Vector3 _dir)
{
	// 一定時間経過で攻撃モーションリセット
	m_attackCnt--;
	if (m_attackCnt <= 0)
	{
		m_attackCnt = 0;
		m_nextAttackOrder = AttackOrder::FirstAttack;
	}

	// 攻撃モーションの切り替え
	// 今攻撃モーション中の場合アニメーションが終わるまで切り替えを行わない
	if (!m_animator->IsAnimationEnd())
	{
		m_attackFlg = false;
	}

	// 攻撃モーションの切り替え
	Action();
	m_attackOrder = m_nextAttackOrder;

	m_pos = _pos;
	m_moveDir = _dir;
}

float AttackState::GetHitDamage() const
{
	float damage = 0;

	switch (m_attackOrder)
	{
	case AttackOrder::FirstAttack:
		damage = 20.f;
		break;
	case AttackOrder::SecondAttack:
		damage = 20.f;
		break;
	case AttackOrder::ThirdAttack:
		damage = 15.f;
		break;
	case AttackOrder::FourthAttack:
		damage = 40.f;
		break;
	default:
		break;
	}

	return damage;
}

void AttackState::Action()
{
	// 攻撃中は移行しない
	if (m_attackFlg) return;

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_keyFlg)
		{
			m_keyFlg = true;  
			m_attackCnt = 60.f;
			switch (m_nextAttackOrder)
			{
			case AttackOrder::FirstAttack:
				m_animator->SetAnimation(m_model->GetData()->GetAnimation("Attack1"), false);
				m_attackOrder = AttackOrder::FirstAttack;
				m_nextAttackOrder = AttackOrder::SecondAttack;
				break;
			case AttackOrder::SecondAttack:
				m_animator->SetAnimation(m_model->GetData()->GetAnimation("Attack2"), false);
				m_attackOrder = AttackOrder::SecondAttack;
				m_nextAttackOrder = AttackOrder::ThirdAttack;
				break;
			case AttackOrder::ThirdAttack:
				m_animator->SetAnimation(m_model->GetData()->GetAnimation("Attack3"), false);
				m_attackOrder = AttackOrder::ThirdAttack;
				m_nextAttackOrder = AttackOrder::FourthAttack;
				break;
			case AttackOrder::FourthAttack:
				m_animator->SetAnimation(m_model->GetData()->GetAnimation("Attack4"), false);
				m_attackOrder = AttackOrder::FourthAttack;
				m_nextAttackOrder = AttackOrder::FirstAttack;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		m_keyFlg = false;
	}
}
