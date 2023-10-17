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

	//絶対変更しない、見る時だけな書き方
	const std::shared_ptr<const KdCamera>& GetCamera() const
	{
		return m_spCamera;
	}

	//中身弄るかもしれない時の書き方
	std::shared_ptr<KdCamera> WorkCamera() const
	{
		return m_spCamera;
	}

	const Math::Matrix GetRotationMatrix() const
	{
		//3つの回転が一緒くたになっている
		return Math::Matrix::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(m_DegAng.y), DirectX::XMConvertToRadians(m_DegAng.x), DirectX::XMConvertToRadians(m_DegAng.z));//Y回転,X回転,Z回転
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

	//カメラ回転用角度
	Math::Vector3						m_DegAng;
};