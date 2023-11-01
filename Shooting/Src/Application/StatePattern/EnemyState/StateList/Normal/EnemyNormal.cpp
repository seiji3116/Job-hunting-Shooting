#include "EnemyNormal.h"

void EnemyNormal::Init()
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Enemy/Enemy.gltf"));

	m_moveSpd = 0.5f;
}

void EnemyNormal::Update()
{
	//Math::Vector3 targetDir = m_targetPos - m_pos;

	//if (targetDir.Length() < 10)
	//{
	//	
	//}

	//targetDir.Normalize();

	//m_moveDir = targetDir;

	//m_moveDir.Normalize();
	//m_pos += m_moveDir * m_moveSpd;
}

void EnemyNormal::PostUpdate()
{
	
}

void EnemyNormal::Shot()
{
}

void EnemyNormal::Action()
{
	Shot();
}

void EnemyNormal::Rotate(Math::Vector3 _targetDir)
{
}
