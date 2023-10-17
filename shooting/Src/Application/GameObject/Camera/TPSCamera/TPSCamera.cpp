#include "TPSCamera.h"
#include "Application/Scene/SceneManager.h"

void TPSCamera::Init()
{
	// 注視店
	m_LocalPos = Math::Matrix::CreateTranslation(0, 2.f, -3.5);

	//画面中央
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void TPSCamera::Update()
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

	//カメラの回転
	UpdateRotateByMouse();
	m_Rotation = GetRotationMatrix();
	m_mWorld = m_LocalPos * m_Rotation * targetMat;

	// カメラと対象の間にオブジェクトが映らないようにする
	Collider();

	CameraBase::Update();
}

void TPSCamera::UpdateRotateByMouse()
{
	//マウスでカメラを回転させる処理
	POINT nowPos;
	GetCursorPos(&nowPos);

	POINT mouseMove;
	mouseMove.x = nowPos.x - m_FixMousePos.x;
	mouseMove.y = nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	//カメラを回転させる処理　　↓マウスの感度
	m_DegAng.x += mouseMove.y * 0.1f;	//マウスを縦に動かしたとき
	m_DegAng.y += mouseMove.x * 0.1f;	//マウスを横に動かしたとき

	//回転制御
	m_DegAng.x = std::clamp(m_DegAng.x, -80.f, 80.f);
}

void TPSCamera::Collider()
{
	// カメラが追いかけている対象の行列取得
	Math::Matrix targetMat;
	std::shared_ptr<const KdGameObject> spTarget = m_wpTarget.lock();
	if (spTarget)
	{
		targetMat = spTarget->GetMatrix();
	}

	KdCollider::RayInfo rayInfo;

	Math::Vector3 targetRange = m_mWorld.Translation() - ((targetMat.Translation()) + targetMat.Up() * 1.f);

	rayInfo.m_pos = targetMat.Translation() + targetMat.Up() * 1.f;
	rayInfo.m_range = targetRange.Length();
	targetRange.Normalize();
	rayInfo.m_dir = targetRange;
	rayInfo.m_type = KdCollider::TypeGround;

	std::list<KdCollider::CollisionResult> rayList;

	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects
		(
			rayInfo,
			&rayList
		);
	}

	float maxOverLap = 0;
	bool hitFlf = false;
	Math::Vector3 hitPos;
	Math::Vector3 hitDir;
	for (auto& ret : rayList)
	{
		// １番近くで当たったものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			hitFlf = true;
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			hitPos = ret.m_hitPos;
		}
	}

	if (hitFlf)
	{
		m_mWorld.Translation((hitPos)+hitDir * 0.1f);
	}
}
