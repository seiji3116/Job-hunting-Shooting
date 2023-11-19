#include "Base.h"

void Base::Init()
{
	Math::Matrix transMat = Math::Matrix::CreateTranslation(Math::Vector3(0, -50, -100));
	m_mWorld = transMat;

	// ���f���̓Ǎ�
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Base/Base.gltf"));

	//�����蔻�菉����
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("BaseModel", m_model, KdCollider::TypeEvent);
}

void Base::DrawLit()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Base::Update()
{
}
