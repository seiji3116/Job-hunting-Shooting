#include "Player.h"
#include "../Camera/TPSCamera/TPSCamera.h"
#include "../Bullet/Bullet.h"
#include "../Rock/Rock.h"
#include "../../Scene/SceneManager.h"

void Player::Update()
{
	Action();
	GravityThrow();
	UpdateCollision();
}

void Player::PostUpdate()
{
	Math::Matrix rotMatZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_roll));
	Math::Matrix rotMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_pitch));

	Math::Matrix rotMat = rotMatX * rotMatZ;

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_moveVec);

	m_mWorld = rotMat * transMat * m_mWorld;
	m_moveDir = m_mWorld.Backward();
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Player::DrawBright()
{
	//KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Player::Init()
{
	// ���W�ړ��n������
	m_moveVec = Math::Vector3(0, 0, 0.1f);							// �ړ���
	m_moveDir = Math::Vector3::Zero;

	// �}�g���b�N�X�̏�����
	Math::Matrix transMat = Math::Matrix::CreateTranslation({ 0,5,0 });
	m_mWorld = transMat;

	// �t���O�֌W������
	m_keyFlg = false;
	m_gravityKeyFlg = false;
	m_gravityFlg = false;
	m_throwKeyFlg = false;

	// ���f���̓Ǎ�
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Player/Player2.gltf"));

	//�����蔻�菉����
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("PlayerModel", m_model, KdCollider::TypeDamage);

	//m_pCollider->RegisterCollisionShape("GravityArea", m_mWorld.Translation(), 10, KdCollider::TypeEvent);
}

void Player::Action()
{
	// ���[�J�����Ǘ�
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_roll += 0.1f;
		if (m_roll > 2)
		{
			m_roll = 2;
		}
	}
	if (m_roll > 0)
	{
		m_roll -= 0.05f;
		if (m_roll < 0)
		{
			m_roll = 0;
		}
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_roll -= 0.1f;
		if (m_roll < -2)
		{
			m_roll = -2;
		}
	}
	if (m_roll < 0)
	{
		m_roll += 0.05f;
		if (m_roll > 0)
		{
			m_roll = 0;
		}
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_pitch -= 0.1f;
		if (m_pitch < -2)
		{
			m_pitch = -2;
		}
	}
	if (m_pitch < 0)
	{
		m_pitch += 0.05f;
		if (m_pitch > 0)
		{
			m_pitch = 0;
		}
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_pitch += 0.1f;
		if (m_pitch > 2)
		{
			m_pitch = 2;
		}
	}
	if (m_pitch > 0)
	{
		m_pitch -= 0.05f;
		if (m_pitch < 0)
		{
			m_pitch = 0;
		}
	}

	// Missile����
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_keyFlg)
		{
			m_keyFlg = true;
			std::shared_ptr<Bullet> bullet;
			bullet = std::make_shared<Bullet>();
			bullet->SetPos(m_mWorld.Translation());
			bullet->SetMoveDir(m_moveDir);
			SceneManager::Instance().AddObject(bullet);
		}
	}
	else if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
	{
		if (!m_keyFlg)
		{
			m_keyFlg = true;
			m_mWorld.Translation(m_mWorld.Translation() + m_moveDir * 20.f);
		}
	}
	else
	{
		m_keyFlg = false;
	}
}

void Player::UpdateCollision()
{
	RockSphereCollision(m_mWorld.Translation(), 5, KdCollider::TypeEvent);
}

bool Player::RockSphereCollision(Math::Vector3 _pos, float _radius, KdCollider::Type _type)
{
	//========================================================
	//������
	//========================================================
	// ������p�̕ϐ�
	KdCollider::SphereInfo sphereInfo;

	// ���̒��S�ʒu��ݒ�
	sphereInfo.m_sphere.Center = _pos;

	// ���̔��a��ݒ�
	sphereInfo.m_sphere.Radius = _radius;

	// �����蔻����������^�C�v��ݒ�
	sphereInfo.m_type = _type;

	// �f�o�b�O�p
	//m_pDebugWire->AddDebugSphere(sphereInfo.m_sphere.Center, sphereInfo.m_sphere.Radius);

	// ���������I�u�W�F�N�g�����i�[���郊�X�g
	std::list<KdCollider::CollisionResult> retSphereList;

	// ���Ɠ����蔻�������
	// �}�b�v�Ƃ̓����蔻��
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects
		(
			sphereInfo,
			&retSphereList
		);
	}

	// �����������X�g��񂩂�1�ԋ߂��I�u�W�F�N�g�����o
	float maxOverLap = 0;
	bool sphereHitFlg = false;
	Math::Vector3 sphereHitDir = Math::Vector3::Zero; // ������������
	for (auto& ret : retSphereList)
	{
		// �P�ԋ߂��œ����������̂�T��
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			sphereHitFlg = true;
			sphereHitDir = ret.m_hitDir;
			sphereHitDir.Normalize();
		}
	}
	if (sphereHitFlg)
	{
		// ���ƃ��f�����������Ă���
		return true;
	}
	// �e�Ɠ������Ă��Ȃ�������false�ŋA��
	return false;
}

void Player::GravityThrow()
{
	// ��Ȃǂ̈�����
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_gravityKeyFlg && !m_gravityFlg && m_gravityList.size() == 0)
		{
			m_gravityKeyFlg = true;
			m_gravityFlg = true;
		}
	}
	else
	{
		m_gravityKeyFlg = false;
	}

	if (m_gravityList.size() >= 3)
	{
		m_gravityFlg = false;
	}

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (!m_gravityKeyFlg && !m_throwKeyFlg)
		{
			m_throwKeyFlg = true;

			if (m_gravityList.size() <= 0)
			{
				return;
			}
			auto& it = m_gravityList.begin();
			(*m_gravityList.begin())->ChengeThrow(m_mWorld.Backward());
			m_gravityList.erase(it);
		}
	}
	else
	{
		m_throwKeyFlg = false;
	}
}
