#include "EnemyTracking.h"

void EnemyTracking::Init()
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Enemy/Enemy.gltf"));

	m_moveSpd = 0.5f;
	m_actionEndFlg = true;
}

void EnemyTracking::Update()
{
	Math::Vector3 vMove = m_mWorld.Forward();
	vMove.Normalize();

	vMove *= m_moveSpd;
	Math::Matrix trans = Math::Matrix::CreateTranslation(vMove);
	m_mWorld *= trans;

	Rotate(m_targetDir);
}

void EnemyTracking::PostUpdate()
{

}

void EnemyTracking::Shot()
{
}

void EnemyTracking::Action()
{
}

void EnemyTracking::Rotate(Math::Vector3 _targetDir)
{
	Math::Vector3 nowDir = m_mWorld.Forward();
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

	Math::Vector3 pos = GetPos();
	m_mWorld.Translation(Math::Vector3(0, 0, 0));

	m_mWorld *= rotation;
	m_mWorld.Translation(pos);
}
