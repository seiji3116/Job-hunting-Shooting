#include "EnemyNormal.h"
#include "../../../Object/Bullet/Bullet.h"
#include "../../../Scene/SceneManager.h"

void EnemyNormal::Init(KdGameObject& _owner)
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Enemy/NormalEnemy.gltf"));
	_owner.SetModel(m_model);

	m_moveSpd = 0.5f;
}

void EnemyNormal::Update(KdGameObject& _owner)
{
	UpdatePos(_owner.GetTargetPos());
	_owner.SetMatrix(m_mWorld);
}

void EnemyNormal::Shot(KdGameObject& _owner)
{
	std::shared_ptr<Bullet> bullet;
	bullet = std::make_shared<Bullet>();
	bullet->SetPos(m_mWorld.Translation());
	bullet->SetMoveDir(_owner.GetTargetDir());
	SceneManager::Instance().AddObject(bullet);
}

void EnemyNormal::Action(KdGameObject& _owner)
{
	Shot(_owner);
	UpdatePos(_owner.GetTargetPos());
}

void EnemyNormal::Rotate(Math::Vector3 _targetDir)
{
}

void EnemyNormal::UpdatePos(const Math::Vector3& _targetPos)
{
	// カメラの最新データ
	m_ghostTargetPos[0] = _targetPos;

	// 最後から1つ前のデータをコピー
	for (int i = GHOST_MAX - 1; i > 0; i--)
	{
		m_ghostTargetPos[i] = m_ghostTargetPos[i - 1];
	}

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_ghostTargetPos[30]);
	m_mWorld = transMat;
}
