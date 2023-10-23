#include "Bullet.h"

void Bullet::Update()
{
	m_moveSpd += 0.01;
	if (m_moveSpd > 1)
	{
		m_moveSpd = 1;
	}

	m_moveDir.Normalize();
	m_pos += m_moveDir * m_moveSpd;
}

void Bullet::PostUpdate()
{
	UpdateRotate();

	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_rotateMat * m_transMat;
}

void Bullet::UpdateRotate()
{
	// �p�x����
	Math::Vector3 vFront = Math::Vector3::Zero;
	Math::Vector3 vHeadUp = Math::Vector3::Zero;
	Math::Vector3 vRight = Math::Vector3::Zero;

	// �ړ�������������O�����Ƃ��ĕۑ�
	vFront = m_moveDir;

	// �O��������90�xZ��]�����x�N�g���𓪏�����Ƃ��ĕۑ�
	vHeadUp = vFront;
	Math::Matrix mRot90 = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90.0f));
	vHeadUp = vHeadUp.TransformNormal(vHeadUp, mRot90);

	// �O�����Ɠ�������̊O�ς��E�����x�N�g���Ƃ��ĕۑ�
	vRight = vHeadUp.Cross(vFront);

	// ���ꂼ��̃x�N�g���̐��K��
	vFront.Normalize();
	vRight.Normalize();
	vHeadUp.Normalize();

	// Rotate�̊e�����ɑΉ�����x�N�g��������
	m_rotateMat.Backward(vFront);
	m_rotateMat.Up(vHeadUp);
	m_rotateMat.Right(vRight);
}

void Bullet::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Bullet::DrawLit()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Bullet::DrawBright()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Bullet::Init()
{
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Missile/Missile.gltf"));

	// ���W�ړ��n�ϐ��̏�����
	m_pos = Math::Vector3::Zero;
	m_moveDir = Math::Vector3::Zero;
	m_moveSpd = 0;

	// �}�g���b�N�X�̏�����
	m_rotateMat = Math::Matrix::Identity;
	m_transMat = Math::Matrix::Identity;

	//�����蔻�菉����
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("StageModel", m_model, KdCollider::TypeDamage);
}