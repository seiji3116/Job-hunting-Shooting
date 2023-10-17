#include "Enemy.h"
#include "Application/Scene/SceneManager.h"
#include "Application/GameObject/Player/Player.h"

void Enemy::Update()
{
	if (m_player == nullptr)
	{
		if (m_nowMoveState != MoveState::Idle)
		{
			m_moveDir.Normalize();
			m_nowMoveState = MoveState::Idle;
			m_state.ChengeIdle(m_pos, m_moveDir);
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			m_idleCnt = 120.f;
			m_collisionFlg = true;
		}
		// �����蔻��
		Collider();
		Animation();
		return;
	}


	// �����蔻��
	Collider();
	Animation();
	// �d�͏���
	m_gravity += -0.007f;
	m_pos.y += m_gravity;

	// �f�o�b�O�p
	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3(0, 3, 0), 4.f, { 1, 0, 0 });

	// �����蔻��
	Collider();

	m_state.Update(m_pos, m_moveDir);
	m_pos = m_state.GetPos();

	// �v���C���[�ւ̃x�N�g���Z�o
	m_moveDir = m_player->GetPos() - m_pos;
	m_moveDir = Math::Vector3(m_moveDir.x, 0, m_moveDir.z);

	if (m_aliveFlg)
	{
		// ��苗������Ă�����������[�V�����ֈڍs
		if (m_state.GetStateChengeFlg())
		{
			if (m_moveDir.Length() >= 10)
			{
				if (m_nowMoveState != Walk)
				{
					m_nowMoveState = MoveState::Walk;
					m_moveDir.Normalize();
					m_state.ChengeWalk(m_pos, m_moveDir);
					m_animator = m_state.GetAnime();
					m_animeSpd = m_state.GetAnimeSpeed();
				}
			}
			else if (m_nowMoveState != MoveState::Idle)
			{
				m_moveDir.Normalize();
				m_nowMoveState = MoveState::Idle;
				m_state.ChengeIdle(m_pos, m_moveDir);
				m_animator = m_state.GetAnime();
				m_animeSpd = m_state.GetAnimeSpeed();
				m_idleCnt = 120.f;
				m_collisionFlg = true;
			}
		}

		m_idleCnt--;
		if (m_idleCnt <= 0 && m_nowMoveState & MoveState::Idle)
		{
			m_idleCnt = 0;
			m_moveDir.Normalize();
			switch (m_nextMoveState)
			{
			case MoveState::Jump:
				m_nextMoveState = MoveState::Rush;
				m_nowMoveState = MoveState::Jump;
				m_state.ChengeJump(m_pos, m_moveDir);
				m_animator = m_state.GetAnime();
				m_animeSpd = m_state.GetAnimeSpeed();
				break;
			case MoveState::Rush:
				m_nextMoveState = MoveState::Jump;
				m_nowMoveState = MoveState::Rush;
				m_state.ChengeRush(m_pos, m_moveDir);
				m_animator = m_state.GetAnime();
				m_animeSpd = m_state.GetAnimeSpeed();
				break;
			default:
				break;
			}
		}

		if (m_nowMoveState & MoveState::Jump)
		{
			if (m_state.GetActionFlg())
			{
				if (m_animator->AnimationTime() <= 0)
				{
					m_gravity = 0.3f;
				}
			}
		}

		// ��]����
		UpdateRotate();

		if (m_nowMoveState & MoveState::Idle || m_nowMoveState & MoveState::Walk)
		{
			m_rotateFlg = true;
		}
	}
	else
	{

	}

	Animation();

	// �d�͏���
	m_gravity += -0.007f;
	m_pos.y += m_gravity;
}

void Enemy::PostUpdate()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	m_mWorld = m_rotateMat * m_transMat;
}

void Enemy::GenerateDepthMapFromLight_SkinMesh()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Enemy::DrawLit_SkinMesh()
{
	if (m_aliveFlg)
	{
		KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
	}
}

void Enemy::Init()
{
	// ���f���Ǎ�
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Enemy/Enemy.gltf"));

	// �}�g���b�N�X�̏�����
	m_mWorld = Math::Matrix::Identity;
	m_transMat = Math::Matrix::Identity;
	m_rotateMat = Math::Matrix::Identity;
	m_angle = 0;
	m_pos = Math::Vector3(0, 3, 3);
	m_rotateFlg = true;

	m_moveDir = Math::Vector3(0, 0, -1);
	m_moveDir.Normalize();

	// �����X�e�[�g�ݒ�
	m_animator = std::make_shared<KdAnimator>();
	m_nowMoveState = MoveState::Idle;
	m_nextMoveState = MoveState::Rush;
	m_state.ChengeIdle(m_pos, m_moveDir);
	m_animator = m_state.GetAnime();
	m_animeSpd = m_state.GetAnimeSpeed();
	m_idleCnt = 120.f;
	m_aliveFlg = true;

	// �d�͂̐ݒ�
	m_gravity = 0;

	// �G�̃X�e�[�^�X�̐ݒ�
	m_hitPt = 1000.f;

	// �f�o�b�O
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	// �����蔻�菉����
	m_collisionFlg = true;
	m_sphereMaxOverLap = 0;;
	m_sphereHitDir = Math::Vector3::Zero;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyBody", m_pos + Math::Vector3(0, 3, 0), 4.f, KdCollider::TypeBump);
}

void Enemy::DrawDebug()
{
	m_pDebugWire->Draw();
}

void Enemy::SetPlayer(std::shared_ptr<Player> _player)
{
	m_player = std::make_shared<Player>();
	m_player = _player;
}

void Enemy::Hit(float _damage)
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		_damage = 10000;
	}
	if (m_aliveFlg)
	{
		m_hitPt -= _damage;
	}

	if (m_hitPt <= _damage)
	{
		m_hitPt = 0;
		m_aliveFlg = false;
	}
}

void Enemy::Action()
{
}

void Enemy::Animation()
{
	if (!m_model)	return;
	if (!m_animator) return;

	// �A�j���[�V�����̍X�V
	m_animator->AdvanceTime(m_model->WorkNodes(), m_animeSpd);
	m_model->CalcNodeMatrices();
}

void Enemy::UpdateRotate()
{
	// �ړ���
	m_moveDir.Normalize();

	// �L�����̌�����ς���
	// ���L�����������Ă������
	// �L�����̉�]�s����쐬
	Math::Matrix nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	// ���݂̕�����ό`������
	Math::Vector3 nowVec = Math::Vector3::TransformNormal(Math::Vector3(0, 0, 1), nowRotMat);

	// ������������
	Math::Vector3 toVec = -m_moveDir;

	float dot = nowVec.Dot(toVec);
	// �ۖڌ덷�i�����_�ȉ����ȗ������ۂɐ�����덷�j
	if (dot > 1)
	{
		dot = 1;
	}
	if (dot < -1)
	{
		dot = -1;
	}

	float ang = DirectX::XMConvertToDegrees(acos(dot));

	if (ang <= 5)
	{
		m_rotateFlg = false;
	}

	if (m_rotateFlg)
	{
		// �����ł��p�x���ς������
		if (ang >= 0.1f)
		{
			if (ang > 10.f)
			{
				ang = 10.f;
			}

			// �O�ρi�ǂ����ɉ�]����̂����ׂ�j
			// �x�N�g��A�ƃx�N�g��B�ɐ����ȃx�N�g��
			Math::Vector3 cross = nowVec.Cross(toVec);
			if (cross.y >= 0)
			{
				m_angle += ang;
			}
			else
			{
				m_angle -= ang;
			}
		}
	}
}

void Enemy::Collider()
{
	//RayCollider();
	if (SphereCollider(m_pos + Math::Vector3(0, 3, 0), 3.5f, KdCollider::TypeGround))
	{
		m_pos += m_sphereHitDir * m_sphereMaxOverLap;
		m_gravity = 0;
	}

	// �v���C���[�Ƃ̓����蔻��
	if (m_state.GetCollisionFlg() && m_aliveFlg)
	{
		if (m_collisionFlg)
		{
			if (m_nowMoveState & MoveState::Jump)
			{
				if (SphereCollider(m_pos + Math::Vector3(0, 3, 0), 6.f, KdCollider::TypeDamage))
				{
					m_collisionFlg = false;
					m_player->Hit(m_state.GetHitDamege());
				}
			}
			if (m_nowMoveState & MoveState::Rush)
			{
				if (SphereCollider(m_pos + Math::Vector3(0, 3, 0), 3.5f, KdCollider::TypeDamage))
				{
					m_collisionFlg = false;
					m_player->Hit(m_state.GetHitDamege());
				}
			}
		}
	}

}

bool Enemy::RayCollider(Math::Vector3 _pos, Math::Vector3 _rayDir, float _range, KdCollider::Type _type)
{
	//========================================================
	//���C����
	//========================================================
	// ���C����p�ɕϐ����쐬

	KdCollider::RayInfo rayInfo;

	// ���C�̔��ˍ��W��ݒ�
	rayInfo.m_pos = m_pos + Math::Vector3(0, 3, 0);

	rayInfo.m_dir = m_mWorld.Down();

	// ���C�̒�����ݒ�
	rayInfo.m_range = 3.f;

	// �����蔻����������^�C�v��ݒ�
	rayInfo.m_type = KdCollider::TypeGround;

	// �f�o�b�O�p==========================================
	m_pDebugWire->AddDebugLine(rayInfo.m_pos, rayInfo.m_dir, rayInfo.m_range);

	// ���C�ɓ��������I�u�W�F�N�g���
	std::list<KdCollider::CollisionResult> retRayList;

	// ���C�Ɠ����蔻�������
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects
		(
			rayInfo,
			&retRayList
		);
	}

	// ���C�ɓ����������X�g����1�ԋ߂��I�u�W�F�N�g�����o
	float maxOverLap = 0;
	Math::Vector3 groundPos;
	bool hit = false;
	for (auto& ret : retRayList)
	{
		// ���C���Ւf���I�[�o�[��������
		// 1�Ԓ������̂�T��
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			groundPos = ret.m_hitPos;
			hit = true;
		}
	}

	// �������Ă�����
	if (hit)
	{
		m_pos += m_mWorld.Down() * maxOverLap;
		m_gravity = 0;
		return true;
	}
	else
	{
		return false;
	}
}

bool Enemy::SphereCollider(Math::Vector3 _pos, float _radius, KdCollider::Type _type)
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
	m_pDebugWire->AddDebugSphere(sphereInfo.m_sphere.Center, sphereInfo.m_sphere.Radius);

	// �e�̓��������I�u�W�F�N�g�����i�[���郊�X�g
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

	// �}�ɓ����������X�g��񂩂�1�ԋ߂��I�u�W�F�N�g�����o
	m_sphereMaxOverLap = 0;
	bool  m_sphereHitFlg = false;
	m_sphereHitDir = Math::Vector3::Zero; // ������������
	for (auto& ret : retSphereList)
	{
		// �P�ԋ߂��œ����������̂�T��
		if (m_sphereMaxOverLap < ret.m_overlapDistance)
		{
			m_sphereMaxOverLap = ret.m_overlapDistance;
			m_sphereHitFlg = true;
			m_sphereHitDir = ret.m_hitDir;
			m_sphereHitDir.Normalize();
		}
	}
	if (m_sphereHitFlg)
	{
		// ���ƃ��f�����������Ă���
		return true;
	}
	else
	{
		return false;
	}
}
