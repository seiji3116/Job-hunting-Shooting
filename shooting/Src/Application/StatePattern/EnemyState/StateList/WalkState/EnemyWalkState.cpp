#include "EnemyWalkState.h"

void EnemyWalkState::Init(std::string_view _modelName, Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData(_modelName));

	m_animator = std::make_shared<KdAnimator>();
	m_animator->SetAnimation(m_model->GetData()->GetAnimation("Walk"));

	m_animeSpd = 2.5f;

	m_pos = _pos;
	m_moveDir = _dir;
}

void EnemyWalkState::Update(Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_pos = _pos;
	m_moveDir = _dir;

	m_pos += m_moveDir * 0.05f;
}

void EnemyWalkState::SetDir(Math::Vector3 _dir)
{
	m_moveDir = _dir;
}
