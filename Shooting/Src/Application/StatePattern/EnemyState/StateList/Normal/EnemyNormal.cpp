#include "EnemyNormal.h"
#include "../../../../Object/Bullet/Bullet.h"
#include "../../../../Scene/SceneManager.h"

void EnemyNormal::Init()
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Enemy/NormalEnemy.gltf"));

	m_moveSpd = 0.5f;
}

void EnemyNormal::Update()
{
	UpdatePos();
}

void EnemyNormal::PostUpdate()
{
	
}

void EnemyNormal::Shot()
{
	std::shared_ptr<Bullet> bullet;
	bullet = std::make_shared<Bullet>();
	bullet->SetPos(m_mWorld.Translation());
	bullet->SetMoveDir(m_targetDir);
	SceneManager::Instance().AddObject(bullet);
}

void EnemyNormal::Action()
{
	Shot();
	UpdatePos();
}

void EnemyNormal::Rotate(Math::Vector3 _targetDir)
{
}

void EnemyNormal::UpdatePos()
{
	// カメラの最新データ
	m_ghostTargetPos[0] = m_targetPos;

	// 最後から1つ前のデータをコピー
	for (int i = GHOST_MAX - 1; i > 0; i--)
	{
		m_ghostTargetPos[i] = m_ghostTargetPos[i - 1];
	}

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_ghostTargetPos[30]);
	m_mWorld = transMat;
}
