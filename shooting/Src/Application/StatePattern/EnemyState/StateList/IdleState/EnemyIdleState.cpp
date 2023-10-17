#include "EnemyIdleState.h"

void EnemyIdleState::Init(std::string_view _modelName, Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData(_modelName));

	m_animator = std::make_shared<KdAnimator>();
	m_animator->SetAnimation(m_model->GetData()->GetAnimation("Idle"));

	m_animeSpd = 1.f;

	m_standCnt = 90.f;
	m_patternChengeFlg = false;

	m_pos = _pos;
	m_moveDir = _dir;

	m_collisionFlg = false;
}

void EnemyIdleState::Update(Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_pos = _pos;
	m_moveDir = _dir;
}

void EnemyIdleState::SetDir(Math::Vector3 _dir)
{
	m_moveDir = _dir;
}
