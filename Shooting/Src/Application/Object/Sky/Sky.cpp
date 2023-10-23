#include "Sky.h"
#include "../Player/Player.h"

void Sky::Update()
{
	std::shared_ptr<Player> spPlayer = m_wpPlayer.lock();
	if (!spPlayer)
	{
		return;
	}

	Math::Vector3 playerPos = spPlayer->GetPos();

	m_transMat = Math::Matrix::CreateTranslation(playerPos);

	m_mWorld = m_transMat;
}

void Sky::DrawUnLit()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Sky::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Sky::Init()
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Sky/Sky.gltf"));

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Sky", m_model, KdCollider::TypeEvent);

	m_pos = { 0, -2, 0 };
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_transMat;
}