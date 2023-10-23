#pragma once

class Enemy : public KdGameObject
{
public:

	Enemy() { Init(); };
	~Enemy() {};

	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void Init()override;
	void Update()override;
	void PostUpdate()override;

private:
	std::shared_ptr<KdModelWork> m_model;

	Math::Vector3 m_pos;
	Math::Vector3 m_scale;
	Math::Matrix m_transMat;
	Math::Matrix m_rotateMat;
	Math::Matrix m_scaleMat;
};