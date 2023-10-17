#include "TitleUI.h"

void TitleUI::Update()
{

	Math::Matrix scaleMat = Math::Matrix::CreateScale(1.5);
	m_titleMat = scaleMat * Math::Matrix::CreateTranslation({ -200, 100, 0 });


	m_enterMat = Math::Matrix::CreateTranslation({ -200, -100, 0 });
	SinCurve(&m_enterAlpha, 3);
}

void TitleUI::DrawSprite()
{
	Math::Rectangle rc;
	Math::Color color;
	color = { 1, 1, 1, m_screenAlpha };

	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_titleMat);
	rc = { 0, 0, 330, 61 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(
		&m_titleTex, 0, 0, 330, 61, &rc, &color
	);

	color = { 1, 1, 1, m_enterAlpha };
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_enterMat);
	rc = { 0, 0, 391, 55 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(
		&m_enterTex, 0, 0, 391, 55, &rc, &color
	);

	KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);
}

void TitleUI::Init()
{
	m_titleTex.Load("Asset/Textures/Title/Title.png");
	m_enterTex.Load("Asset/Textures/Title/Enter.png");

	Math::Matrix scaleMat = Math::Matrix::CreateScale(0.1);
	m_titleMat = scaleMat * Math::Matrix::CreateTranslation({ 0, 100, 0 });


	m_enterMat = Math::Matrix::CreateTranslation({ 0, -100, 0 });

	m_screenAlpha = 1;
	m_enterAlpha = 1;

	m_sinAngle = 0;
}

void TitleUI::SinCurve(float* _alpha, float _angleSpeed)
{
	m_sinAngle += _angleSpeed;

	if (m_sinAngle >= 200)
	{
		m_sinAngle -= 200;
	}

	*_alpha = (sin(DirectX::XMConvertToRadians(m_sinAngle)) + 1) / 2;
}
