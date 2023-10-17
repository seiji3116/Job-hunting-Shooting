#include "RunState.h"

void RunState::Init(std::string_view _modelName, Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData(_modelName));
	m_animeSpd = 2.5f;
	m_animator = std::make_shared<KdAnimator>();
	m_animator->SetAnimation(m_model->GetData()->GetAnimation("Run"));

	m_pos = _pos;
	m_moveDir = _dir;
}

void RunState::Update(Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_moveDir = _dir;

	Math::Vector3 moveVec = Math::Vector3::Zero;
	moveVec = m_moveDir * 0.2f;
	m_pos += moveVec;
}
