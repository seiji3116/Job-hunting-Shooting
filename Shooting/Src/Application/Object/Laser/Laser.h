#pragma once

class CameraBase;

class Laser :public KdGameObject
{
public:
	Laser() { Init(); }
	~Laser(){}

	// ��{�֐�
	void DrawBright()override;
	void DrawLit()override;
	void Init()override;
	void Update()override;
	void PostUpdate()override;

public:
	void SetDir(const Math::Vector3& _dir) { m_dir = _dir; }
	void SetRange(const Math::Vector2& _range) { m_range = _range; }
	void SetRange(const float _xRange, const float _yRange) { m_range = Math::Vector2(_xRange, _yRange); }
	void SetStartPos(const Math::Vector3& _pos)
	{
		// ���ˈʒu�̃Z�b�g
		m_startPos = _pos;
		// ���ˈʒu�A�����x�N�g���A�������璆�S���W�̃Z�b�g
		if (m_range != Math::Vector2::Zero && m_dir != Math::Vector3::Zero)
		{
			float xHalfRange = m_range.y / 2;
			m_dir.Normalize();
			m_centerPos = (m_dir * xHalfRange) + m_startPos;
		}
	}

	void SetCamera(const std::shared_ptr<CameraBase> camera)
	{
		m_camera = camera;
	}

private:
	void Rotate(Math::Vector3 _dir);
	void UpdateCenterPos();
	void Billboard(Math::Matrix& _rotateMat);

private:
	std::shared_ptr<KdSquarePolygon> m_poly;
	Math::Vector3 m_centerPos;
	Math::Vector3 m_startPos;
	Math::Vector3 m_dir;
	Math::Vector2 m_range;

	std::weak_ptr<CameraBase> m_camera;		// �J�������
};