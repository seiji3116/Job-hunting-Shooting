#pragma once

class Sky :public KdGameObject
{
public:
	Sky() { Init(); }
	~Sky() {}

	void Update()override;
	void DrawUnLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

private:
	std::shared_ptr<KdModelWork> m_model;

	Math::Vector3 m_pos;
	Math::Vector3 m_scale;
	Math::Matrix m_transMat;
	Math::Matrix m_rotateMat;
	Math::Matrix m_scaleMat;
};