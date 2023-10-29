#include "EnemyRush.h"

void EnemyRush::Init()
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Enemy/Enemy.gltf"));

	m_moveSpd = 0.5f;
	m_standCnt = 100;
	m_rashCnt = 200;
	m_rashFlg = false;
	m_standFlg = true;
}

void EnemyRush::Update()
{
	Action(); 

	m_moveDir.Normalize();
	m_pos += m_moveDir * m_moveSpd;
}

void EnemyRush::PostUpdate()
{
}

void EnemyRush::Shot()
{
}

void EnemyRush::Action()
{
	Math::Vector3 targetDir = m_targetPos - m_pos;

	if (targetDir.Length() < 10)
	{
		if (!m_rashFlg)
		{
			m_standFlg = true;
		}
	}

	if (m_standFlg)
	{
		m_moveSpd = 0;
		m_standCnt--;
		if (m_standCnt < 0)
		{
			m_standCnt = 100;
			m_rashFlg = true;
			m_standFlg = false;
			m_moveSpd = 1;
		}
	}

	if (m_rashFlg)
	{
		m_rashCnt--;
		if (m_rashCnt < 0)
		{
			m_moveSpd = 0;
			m_rashCnt = 200;
			m_rashFlg = false;
		}
	}

	targetDir.Normalize();

	m_moveDir = targetDir;
}
