#include "TitleCamera.h"
#include "Application/Scene/SceneManager.h"

void TitleCamera::Init()
{
	// 注視店
	m_LocalPos = Math::Matrix::CreateTranslation(-0.7, 1, -1.5);

	//画面中央
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void TitleCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix targetMat = Math::Matrix::Identity;

	// ターゲットがいなかったら計算瀬zに変える
	if (m_wpTarget.expired()) { return; }

	// カメラが追いかけている対象の行列取得
	std::shared_ptr<const KdGameObject> spTarget = m_wpTarget.lock();
	if (spTarget)
	{
		targetMat = Math::Matrix::CreateTranslation(spTarget->GetPos());
	}

	m_mWorld = m_LocalPos * targetMat;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
	CameraBase::Update();
}
