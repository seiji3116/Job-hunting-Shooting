#pragma once
class TPSCamera;

class Tank : public KdGameObject
{
public:

	Tank() { Init(); };
	~Tank() {};

	void Update();
	void PostUpdate()override;

	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void Init()override;

	void SetCamera(const std::shared_ptr<TPSCamera> camera)
	{
		m_camera = camera;
	}
private:

	std::shared_ptr<KdModelWork> m_model;
	std::weak_ptr<TPSCamera> m_camera;
	float m_roll = 0;
	float m_pitch = 0;

};