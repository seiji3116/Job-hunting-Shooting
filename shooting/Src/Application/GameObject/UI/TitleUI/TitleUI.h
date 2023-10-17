#pragma once

class TitleUI :public KdGameObject
{
public:
	TitleUI() {};
	~TitleUI() {};

	void Update() override;
	void DrawSprite() override;
	void Init() override;

private:
	void SinCurve(float* _alpha, float _angleSpeed);

	KdTexture m_titleTex;
	KdTexture m_enterTex;

	Math::Matrix m_titleMat;
	Math::Matrix m_enterMat;

	float m_screenAlpha;
	float m_enterAlpha;

	float m_sinAngle;
};