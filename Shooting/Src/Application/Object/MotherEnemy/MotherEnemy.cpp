#include "MotherEnemy.h"

void MotherEnemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void MotherEnemy::DrawLit()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void MotherEnemy::Update()
{
}

void MotherEnemy::PostUpdate()
{
}

Math::Vector3 MotherEnemy::GetNodePos(int _num)
{
	std::string nodeNum;
	nodeNum = std::to_string(_num);
	const KdModelWork::Node* pNode = m_model->FindNode("LaserPos" + nodeNum);

	if (pNode)
	{
		return pNode->m_worldTransform.Translation() + m_mWorld.Translation();
	}
	return Math::Vector3::Zero;
}

void MotherEnemy::Init()
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Enemy/MotherEnemy.gltf"));

	m_pos = Math::Vector3::Zero;
	m_transMat = Math::Matrix::CreateTranslation(Math::Vector3(0, 0, 150));
	m_rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180));
	m_scaleMat = Math::Matrix::Identity;

	m_mWorld = m_scaleMat * m_rotateMat * m_transMat;
}