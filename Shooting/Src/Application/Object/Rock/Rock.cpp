#include "Rock.h"
#include "../Player/Player.h"
#include "../../Scene/SceneManager.h"

void Rock::Update()
{
	//m_transMat = Math::Matrix::CreateTranslation(m_pos);
	//m_rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	//m_mWorld = m_rotateMat * m_mWorld;
	Gravity();
}

void Rock::Gravity()
{
	std::shared_ptr<Player> spPlayer = m_wpPlayer.lock();

	m_playerVec = spPlayer->GetPos() - m_mWorld.Translation();

	if (spPlayer->GetGravityFlg() && !m_gravityFlg && !m_throwFlg)
	{
		if (m_playerVec.Length() < 5)
		{
			spPlayer->PushBackGravityList(this);
			m_gravityFlg = true;
		}
	}

	if (m_gravityFlg)
	{
		m_playerVec.Normalize();

		Math::Vector3 pos = GetPos();

		pos += m_playerVec * m_gravityPow;

		m_mWorld.Translation(pos);
	}

	if (m_throwFlg)
	{
		m_targetVec.Normalize();

		Math::Vector3 pos = GetPos();

		pos += m_targetVec * m_gravityPow;

		m_mWorld.Translation(pos);

		if (m_playerVec.Length() > 30)
		{
			m_isExpired = true;
		}
	}
}

void Rock::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Rock::DrawLit()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Rock::DrawBright()
{
}

void Rock::Init()
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Rock/Rock.gltf"));

	m_angle = 0;

	m_gravityPow = 0.5f;
	m_gravityFlg = false;

	m_throwFlg = false;

	m_localPos = Math::Vector3(2, 0, 0);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//ìñÇΩÇËîªíËèâä˙âª
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("RockModel", m_mWorld.Translation(), 2, KdCollider::TypeEvent);
}
