#include "EnemyLaser.h"
#include "../../../Object/Laser/Laser.h"
#include "../../../Object/Enemy/Enemy.h"
#include "../../../Scene/SceneManager.h"

void EnemyLaser::Init(KdGameObject& _owner)
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Enemy/LaserEnemy.gltf"));

	_owner.SetModel(m_model);

	m_laserFlg = false;
}

void EnemyLaser::Update(KdGameObject& _owner)
{
	if (!m_laserFlg)
	{
		m_laserFlg = true;
		m_laser = std::make_shared<Laser>();
		m_laser->SetDir(_owner.GetTargetDir());
		m_laser->SetStartPos(m_mWorld.Translation() + (m_mWorld.Backward() * 5));
		m_laser->SetRange(Math::Vector2(3, 20));
		m_laser->SetCamera(_owner.GetCamera().lock());
		SceneManager::Instance().AddObject(m_laser);
	}
	m_laser->SetDir(_owner.GetTargetDir());
	m_laser->SetStartPos(m_mWorld.Translation() + (m_mWorld.Backward() * 5));
	Rotate(_owner.GetTargetDir());

	_owner.SetMatrix(m_mWorld);
}

void EnemyLaser::Shot(KdGameObject& _owner)
{
}

void EnemyLaser::Action(KdGameObject& _owner)
{
}

void EnemyLaser::Rotate(Math::Vector3 _targetDir)
{
	Math::Vector3 nowDir = m_mWorld.Backward();
	nowDir.Normalize();
	_targetDir.Normalize();

	float dot = nowDir.Dot(_targetDir);
	dot = std::clamp(dot, -1.f, 1.f);

	float betweeanAng = acos(dot);
	betweeanAng = DirectX::XMConvertToDegrees(betweeanAng);

	float rotateAng = std::clamp(betweeanAng, -4.f, 4.f);

	Math::Vector3 rotAxis;
	nowDir.Cross(_targetDir, rotAxis);
	if (rotAxis.LengthSquared() == 0)return;

	Math::Matrix rotation;
	rotation = Math::Matrix::CreateFromAxisAngle(rotAxis, DirectX::XMConvertToRadians(rotateAng));

	Math::Vector3 pos = m_mWorld.Translation();
	m_mWorld.Translation(Math::Vector3(0, 0, 0));

	m_mWorld *= rotation;
	m_mWorld.Translation(pos);
}
