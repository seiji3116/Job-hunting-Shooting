#include "Ground.h"

void Ground::Update()
{
	Animation();
}

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Ground::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Ground::Init()
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Stage/stage.gltf"));

	// アニメーション
	m_animator = std::make_shared<KdAnimator>();
	m_animator->SetAnimation(m_model->GetData()->GetAnimation("roll"));

	m_pos = { 0, -3, 0 };
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_transMat;

	// 当たり判定初期化
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("StageModel", m_model, KdCollider::TypeGround);
}

void Ground::Animation()
{
	if (!m_model)	return;
	if (!m_animator) return;

	// アニメーションの更新
	m_animator->AdvanceTime(m_model->WorkNodes(), 0.5f);
	m_model->CalcNodeMatrices();
}
