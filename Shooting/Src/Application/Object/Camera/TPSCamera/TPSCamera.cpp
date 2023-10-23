#include "TPSCamera.h"

void TPSCamera::Init()
{
	// �����_
	m_LocalPos = Math::Matrix::CreateTranslation(0, 2.5f, -10.0f);

	//��ʒ���
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;

	//SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	CameraBase::Init();
}

void TPSCamera::Update()
{
	// �^�[�Q�b�g�̍s��(�L���ȏꍇ���p����)
	Math::Matrix targetMat = Math::Matrix::Identity;
	if (!m_wpTarget.expired())
	{
		const std::shared_ptr<const KdGameObject> spTarget = m_wpTarget.lock();
		if (spTarget)
		{
			//targetMat = Math::Matrix::CreateTranslation(spTarget->GetPos());
			targetMat = spTarget->GetMatrix();
		}
	}

	//�J�����̉�]
	UpdateRotateByMouse();
	m_Rotation = GetRotationMatrix();

	// �J�����̍ŐV�f�[�^
	m_ghostMat[0] = m_LocalPos * m_Rotation * targetMat;

	// �Ōォ��1�O�̃f�[�^���R�s�[
	for (int i = GHOST_MAX - 1; i > 0; i--)
	{
		m_ghostMat[i] = m_ghostMat[i - 1];
	}

	m_mWorld = m_ghostMat[9];

	CameraBase::Update();
}

void TPSCamera::UpdateRotateByMouse()
{
	//�}�E�X�ŃJ��������]�����鏈��
	//POINT nowPos;
	//GetCursorPos(&nowPos);

	//POINT mouseMove;
	//mouseMove.x = nowPos.x - m_FixMousePos.x;
	//mouseMove.y = nowPos.y - m_FixMousePos.y;

	//SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	////�����ŃJ��������]�����鏈��
	//m_DegAng.x += mouseMove.y * 0.15f;
	//m_DegAng.y += mouseMove.x * 0.15f;
}
