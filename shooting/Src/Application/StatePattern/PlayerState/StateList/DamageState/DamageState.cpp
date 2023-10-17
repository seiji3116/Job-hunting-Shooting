#include "DamageState.h"

void DamageState::Init(std::string_view _modelName, Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData(_modelName));

	m_animeSpd = 1.f;
	m_animator = std::make_shared<KdAnimator>();
	m_animator->SetAnimation(m_model->GetData()->GetAnimation("Damage"), false);

	m_pos = _pos;
	m_moveDir = _dir;
}

void DamageState::Update(Math::Vector3 _pos, Math::Vector3 _dir)
{
}
