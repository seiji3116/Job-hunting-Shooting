#include "Tank.h"
#include"../Camera/TPSCamera/TPSCamera.h"

void Tank::Update()
{
	//=======================
	//ƒ[ƒJƒ‹Ž²ŠÇ—
	//=======================

	//A‚ÌƒL[‚ð‰Ÿ‚µ‚½‚ç‚Q“xZ‰ñ“]‚³‚¹‚é
	//D‚ÌƒL[‚ð‰Ÿ‚µ‚½‚ç‚Q“xZ‹t‰ñ“]‚³‚¹‚é
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_roll += 0.1f;
		if (m_roll > 2)
		{
			m_roll = 2;
		}
	}
	if (m_roll > 0)
	{
		m_roll -= 0.05f;
		if (m_roll < 0)
		{
			m_roll = 0;
		}
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_roll -= 0.1f;
		if (m_roll < -2)
		{
			m_roll = -2;
		}
	}
	if (m_roll < 0)
	{
		m_roll += 0.05f;
		if (m_roll > 0)
		{
			m_roll = 0;
		}
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_pitch += 0.1f;
		if (m_pitch > 2)
		{
			m_pitch = 2;
		}
	}
	if (m_pitch > 0)
	{
		m_pitch -= 0.05f;
		if (m_pitch < 0)
		{
			m_pitch = 0;
		}
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_pitch -= 0.1f;
		if (m_pitch < -2)
		{
			m_pitch = -2;
		}
	}
	if (m_pitch < 0)
	{
		m_pitch += 0.05f;
		if (m_pitch > 0)
		{
			m_pitch = 0;
		}
	}

	Math::Matrix rotMatZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_roll));
	Math::Matrix rotMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_pitch));

	Math::Matrix rotMat = rotMatX * rotMatZ;

	Math::Matrix transMat = Math::Matrix::CreateTranslation(Math::Vector3{0, 0, 0.1f});

	m_mWorld = rotMat * transMat * m_mWorld;
}

void Tank::PostUpdate()
{

}

void Tank::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Tank::DrawLit()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Tank::Init()
{
	Math::Matrix transMat = Math::Matrix::CreateTranslation({ 0,5,0 });
	m_mWorld = transMat;

	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/AirPlane/AirPlane.gltf"));
}
