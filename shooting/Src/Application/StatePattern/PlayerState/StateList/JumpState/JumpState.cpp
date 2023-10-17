#include "JumpState.h"

void JumpState::Init(std::string_view _modelName, Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData(_modelName));
	m_animeSpd = 2.5f;
	m_animator = std::make_shared<KdAnimator>();
	m_animator->SetAnimation(m_model->GetData()->GetAnimation("RunJump"), false);

	m_pos = _pos;
	m_moveDir = _dir;
}

void JumpState::Update(Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_pos = _pos;
	m_moveDir.Normalize();
	m_pos += m_moveDir * 0.1f;
}
