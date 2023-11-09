#pragma once

class MotherEnemy :public KdGameObject
{
public:
	MotherEnemy() { Init(); }
	~MotherEnemy() {}

	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void Init()override;
	void Update()override;
	void PostUpdate()override;

	Math::Vector3 GetNodePos(int _num);

private:
	std::shared_ptr<KdModelWork> m_model;

	Math::Vector3 m_pos;
	Math::Vector3 m_moveDir;
	Math::Vector3 m_scale;
	Math::Matrix m_transMat;				// ˆÚ“®s—ñ
	Math::Matrix m_rotateMat;				// ‰ñ“]s—ñ
	Math::Matrix m_scaleMat;				// Šgks—ñ
};