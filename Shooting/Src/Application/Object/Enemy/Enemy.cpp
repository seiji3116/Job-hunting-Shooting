#include "Enemy.h"

void Enemy::Update()
{
}

void Enemy::PostUpdate()
{
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Enemy::Init()
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Enemy/Enemy.gltf"));

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//“–‚½‚è”»’è‰Šú‰»
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyModel", m_mWorld.Translation(), 6.5f, KdCollider::TypeDamage);
}