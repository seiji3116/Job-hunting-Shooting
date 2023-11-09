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
	Math::Matrix m_transMat;				// �ړ��s��
	Math::Matrix m_rotateMat;				// ��]�s��
	Math::Matrix m_scaleMat;				// �g�k�s��
};