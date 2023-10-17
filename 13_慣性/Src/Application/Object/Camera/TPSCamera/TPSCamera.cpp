#include "TPSCamera.h"

void TPSCamera::Init()
{
	// 注視点
	m_LocalPos = Math::Matrix::CreateTranslation(0, 10.0f, -20.0f);

	//画面中央
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;

	//SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void TPSCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix targetMat = Math::Matrix::Identity;
	if (!m_wpTarget.expired())
	{
		const std::shared_ptr<const KdGameObject> spTarget = m_wpTarget.lock();
		if (spTarget)
		{
			targetMat = Math::Matrix::CreateTranslation(spTarget->GetPos());
		}
	}

	//カメラの回転
	UpdateRotateByMouse();
	m_Rotation = GetRotationMatrix();
	m_mWorld = m_LocalPos * m_Rotation; //* targetMat;

	CameraBase::Update();
}

void TPSCamera::UpdateRotateByMouse()
{
	//マウスでカメラを回転させる処理
	//POINT nowPos;
	//GetCursorPos(&nowPos);

	//POINT mouseMove;
	//mouseMove.x = nowPos.x - m_FixMousePos.x;
	//mouseMove.y = nowPos.y - m_FixMousePos.y;

	//SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	////差分でカメラを回転させる処理
	//m_DegAng.x += mouseMove.y * 0.15f;
	//m_DegAng.y += mouseMove.x * 0.15f;

	if (GetAsyncKeyState(VK_UP))
	{
		m_DegAng.x += 1;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		m_DegAng.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_DegAng.y += 1;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_DegAng.y -= 1;
	}

	//回転制御
	m_DegAng.x = std::clamp(m_DegAng.x, -FLT_MAX, FLT_MAX);
}
