#pragma once

class GameScene;
class Player;

class Ground :public KdGameObject
{
public:
	Ground() { Init(); }
	~Ground() {}

	void Update()override;
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

	std::shared_ptr<KdModelWork>const GetModel()
	{
		return m_model;
	}

private:
	void Animation();

	std::shared_ptr<KdModelWork> m_model;
	std::shared_ptr<KdAnimator> m_animator = nullptr;

	Math::Vector3 m_pos;
	Math::Vector3 m_scale;
	Math::Matrix m_transMat;
	Math::Matrix m_rotateMat;
	Math::Matrix m_scaleMat;
};