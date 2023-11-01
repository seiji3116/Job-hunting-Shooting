#include "Rock.h"
#include "../Player/Player.h"
#include "../../Scene/SceneManager.h"

void Rock::Update()
{
	std::shared_ptr<Player> spPlayer = m_wpPlayer.lock();

	m_playerVec = spPlayer->GetPos() - m_mWorld.Translation();

	if (spPlayer->GetGravityFlg())
	{
		if (m_playerVec.Length() < 5)
		{
			if (spPlayer->PushBackGravityList(this))
			{
				m_gravityFlg = true;
			}
		}
	}

	Gravity();
	Throw();
}

void Rock::Throw()
{
	if (!m_throwFlg) { return; }

	m_targetVec.Normalize();

	Math::Vector3 pos = GetPos();

	pos += m_targetVec * m_gravityPow;

	m_mWorld.Translation(pos);

	if (m_playerVec.Length() > 30)
	{
		m_isExpired = true;
	}
}

void Rock::Gravity()
{
	if (!m_gravityFlg) { return; }

	Math::Vector3 vMove = m_mWorld.Forward();
	vMove.Normalize();

	vMove *= 0.2;
	Math::Matrix trans = Math::Matrix::CreateTranslation(vMove);
	m_mWorld *= trans;

	Rotate(m_playerVec);
}

void Rock::Rotate(Math::Vector3 _targetDir)
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
