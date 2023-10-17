#include "TPSCamera.h"
#include "Application/Scene/SceneManager.h"

void TPSCamera::Init()
{
	// �����X
	m_LocalPos = Math::Matrix::CreateTranslation(0, 2.f, -3.5);

	//��ʒ���
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void TPSCamera::Update()
{
	// �^�[�Q�b�g�̍s��(�L���ȏꍇ���p����)
	Math::Matrix targetMat = Math::Matrix::Identity;

	// �^�[�Q�b�g�����Ȃ�������v�Z��z�ɕς���
	if (m_wpTarget.expired()) { return; }

	// �J�������ǂ������Ă���Ώۂ̍s��擾
	std::shared_ptr<const KdGameObject> spTarget = m_wpTarget.lock();
	if (spTarget)
	{
		targetMat = Math::Matrix::CreateTranslation(spTarget->GetPos());
	}

	//�J�����̉�]
	UpdateRotateByMouse();
	m_Rotation = GetRotationMatrix();
	m_mWorld = m_LocalPos * m_Rotation * targetMat;

	// �J�����ƑΏۂ̊ԂɃI�u�W�F�N�g���f��Ȃ��悤�ɂ���
	Collider();

	CameraBase::Update();
}

void TPSCamera::UpdateRotateByMouse()
{
	//�}�E�X�ŃJ��������]�����鏈��
	POINT nowPos;
	GetCursorPos(&nowPos);

	POINT mouseMove;
	mouseMove.x = nowPos.x - m_FixMousePos.x;
	mouseMove.y = nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	//�J��������]�����鏈���@�@���}�E�X�̊��x
	m_DegAng.x += mouseMove.y * 0.1f;	//�}�E�X���c�ɓ��������Ƃ�
	m_DegAng.y += mouseMove.x * 0.1f;	//�}�E�X�����ɓ��������Ƃ�

	//��]����
	m_DegAng.x = std::clamp(m_DegAng.x, -80.f, 80.f);
}

void TPSCamera::Collider()
{
	// �J�������ǂ������Ă���Ώۂ̍s��擾
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
		// �P�ԋ߂��œ����������̂�T��
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
