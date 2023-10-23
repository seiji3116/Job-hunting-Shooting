#include "Saturn.h"
#include "../Player/Player.h"

void Saturn::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Saturn::DrawLit()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Saturn::DrawBright()
{
	//KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Saturn::Update()
{
	std::shared_ptr<Player> spPlayer = m_wpPlayer.lock();
	if (!spPlayer)
	{
		return;
	}

	Math::Vector3 playerPos = spPlayer->GetPos();

	m_transMat = Math::Matrix::CreateTranslation(playerPos);
	Math::Matrix localMat = Math::Matrix::CreateTranslation(Math::Vector3(-100, -100, 0));

	m_mWorld = m_transMat * localMat;
}

void Saturn::Init()
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Saturn/Saturn.gltf"));

	m_pos = { 50, 0, 0 };
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_transMat;

	//“–‚½‚è”»’è‰Šú‰»
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("SaturnModel", m_model, KdCollider::TypeGround);
}
