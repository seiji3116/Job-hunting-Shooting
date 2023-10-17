#include "EnemyRushState.h"

void EnemyRushState::Init(std::string_view _modelName, Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData(_modelName));
	
	m_animator = std::make_shared<KdAnimator>();
	m_animator->SetAnimation(m_model->GetData()->GetAnimation("RushStandby"), false);

	m_animeSpd = 2.5f;

	m_standCnt = 90.f;
	m_patternChengeFlg = false;

	m_collisionFlg = false;

	m_pos = _pos;
	m_moveDir = _dir;
}

void EnemyRushState::Update(Math::Vector3 _pos, Math::Vector3 _dir)
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
		m_collisionFlg = false;
		m_patternChengeFlg = false;
		switch (m_nextMovePatterm)
		{
		case EnemyState::Standby:
			m_animator->SetAnimation(m_model->GetData()->GetAnimation("RushStandby"), false);
			m_nowMovePattern = EnemyState::Standby;
			m_nextMovePatterm = EnemyState::Action;
			break;
		case EnemyState::Action:
			m_animator->SetAnimation(m_model->GetData()->GetAnimation("RushAction"), false);
			m_nowMovePattern = EnemyState::Action;
			m_nextMovePatterm = EnemyState::Landing;
			m_collisionFlg = true;
			break;
		case EnemyState::Landing:
			m_animator->SetAnimation(m_model->GetData()->GetAnimation("RushLanding"), false);
			m_nowMovePattern = EnemyState::Landing;
			m_nextMovePatterm = EnemyState::Standby;
			break;
		default:
			break;
		}
	}

	if (m_nowMovePattern & EnemyState::Action)
	{
		m_moveDir.Normalize();
		m_pos += m_moveDir * 0.7f;
	}
}

bool EnemyRushState::GetCollisionFlg() const
{
	return m_collisionFlg;
}

bool EnemyRushState::GetStateChengeFlg() const
{
	if (m_nowMovePattern & EnemyState::Landing && m_animator->IsAnimationEnd())
	{
		return true;
	}

	return false;
}

bool EnemyRushState::GetActionFlg() const
{
	if (m_nowMovePattern & EnemyState::Action)
	{
		return true;
	}

	return false;
}

void EnemyRushState::SetDir(Math::Vector3 _dir)
{
	if (m_nowMovePattern & EnemyState::Standby)
	{
		m_moveDir = _dir;
	}
}
