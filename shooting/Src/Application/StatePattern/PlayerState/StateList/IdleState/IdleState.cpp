#include "IdleState.h"

void IdleState::Init(std::string_view _modelName, Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData(_modelName));

	m_animeSpd = 1.f;
	m_animator = std::make_shared<KdAnimator>();
	m_animator->SetAnimation(m_model->GetData()->GetAnimation("Idle1"), false);

	m_pos = _pos;
	m_moveDir = _dir;

	m_idlePattern = IdleState::First;
}

void IdleState::Update(Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_pos = _pos;
	m_moveDir = _dir;

	if (m_animator->IsAnimationEnd())
	{
		switch (m_idlePattern)
		{
		case IdleState::First:
			m_idlePattern = IdleState::Second;
			m_animator->SetAnimation(m_model->GetData()->GetAnimation("Idle1"), false);
			break;
		case IdleState::Second:
			m_idlePattern = IdleState::Third;
			m_animator->SetAnimation(m_model->GetData()->GetAnimation("Idle2"), false);
			break;
		case IdleState::Third:
			m_idlePattern = IdleState::First;
			m_animator->SetAnimation(m_model->GetData()->GetAnimation("Idle3"), false);
			break;
		default:
			break;
		}
	}
}
