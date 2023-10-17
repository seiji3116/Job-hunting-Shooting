#include "TitleCamera.h"
#include "Application/Scene/SceneManager.h"

void TitleCamera::Init()
{
	// �����X
	m_LocalPos = Math::Matrix::CreateTranslation(-0.7, 1, -1.5);

	//��ʒ���
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void TitleCamera::Update()
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

	m_mWorld = m_LocalPos * targetMat;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
	CameraBase::Update();
}
