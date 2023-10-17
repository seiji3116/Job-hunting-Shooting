#include "EnemyJumpState.h"

void EnemyJumpState::Init(std::string_view _modelName, Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData(_modelName));

	m_animator = std::make_shared<KdAnimator>();
	m_animator->SetAnimation(m_model->GetData()->GetAnimation("JumpStandby"), false);

	m_animeSpd = 2.5f;

	m_standCnt = 90.f;
	m_patternChengeFlg = false;

	m_pos = _pos;
	m_moveDir = _dir;
}

void EnemyJumpState::Update(Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_pos = _pos;
	m_standCnt--;
	if (m_standCnt <= 0 && m_animator->IsAnimationEnd())
	{
		m_patternChengeFlg = true;
		m_standCnt = 90.f;
	}

	if (m_patternChengeFlg)
	{
		m_patternChengeFlg = false;
		switch (m_nextMovePatterm)
		{
		case EnemyState::Standby:
			m_animator->SetAnimation(m_model->GetData()->GetAnimation("JumpStandby"), false);
			m_nowMovePattern = EnemyState::Standby;
			m_nextMovePatterm = EnemyState::Action;
			break;
		case EnemyState::Action:
			m_animator->SetAnimation(m_model->GetData()->GetAnimation("JumpAction"), false);
			m_nowMovePattern = EnemyState::Action;
			m_nextMovePatterm = EnemyState::Landing;
			break;
		case EnemyState::Landing:
			m_animator->SetAnimation(m_model->GetData()->GetAnimation("JumpLanding"), false);
			m_nowMovePattern = EnemyState::Landing;
			m_nextMovePatterm = EnemyState::Standby;
			break;
		default:
			break;
		}
	}
}

bool EnemyJumpState::GetCollisionFlg() const
{
	if (m_nowMovePattern & EnemyState::Action)
	{
		return false;
	}

	return true;
}

bool EnemyJumpState::GetStateChengeFlg() const
{
	if (m_nowMovePattern & EnemyState::Landing && m_animator->IsAnimationEnd())
	{
		return true;
	}

	return false;
}

bool EnemyJumpState::GetActionFlg() const
{
	if (m_nowMovePattern & EnemyState::Action)
	{
		return true;
	}

	return false;
}

void EnemyJumpState::SetDir(Math::Vector3 _dir)
{
	m_moveDir = _dir;
}
