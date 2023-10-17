#pragma once

class CameraBase : public KdGameObject
{
public:
	CameraBase() {}
	virtual ~CameraBase()	override {}

	void Init()				override;
	void Update()			override;
	void PreDraw()			override;

	void SetTarget(const std::shared_ptr<KdGameObject>& target);

	//��ΕύX���Ȃ��A���鎞�����ȏ�����
	const std::shared_ptr<const KdCamera>& GetCamera() const
	{
		return m_spCamera;
	}

	//���g�M�邩������Ȃ����̏�����
	std::shared_ptr<KdCamera> WorkCamera() const
	{
		return m_spCamera;
	}

	const Math::Matrix GetRotationMatrix() const
	{
		//3�̉�]���ꏏ�����ɂȂ��Ă���
		return Math::Matrix::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(m_DegAng.y), DirectX::XMConvertToRadians(m_DegAng.x), DirectX::XMConvertToRadians(m_DegAng.z));//Y��],X��],Z��]
	}

	const Math::Matrix GetRotaionYMatrix() const
	{
		return Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_DegAng.y));
	}

	const Math::Vector3& GetDegAngle()const { return m_DegAng; }
protected:
	std::shared_ptr<KdCamera>			m_spCamera = nullptr;
	std::weak_ptr<KdGameObject>			m_wpTarget;

	Math::Matrix						m_LocalPos;
	Math::Matrix						m_Rotation;
	Math::Matrix						m_RotationY;

	//�J������]�p�p�x
	Math::Vector3						m_DegAng;
};