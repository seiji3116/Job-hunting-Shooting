#include "Player.h"
#include "Application/Scene/SceneManager.h"
#include "Application/GameObject/Camera/CameraBase.h"
#include "Application/GameObject/Enemy/Enemy.h"

void Player::Update()
{
	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3(0, 0.7f, 0), 0.5f, { 1, 0, 0 });

	// �U���p�m�[�h�̓Ǎ�
	m_attackNodePos[0] = LoadNodePos("J_Bip_L_Hand") + m_pos;
	m_attackNodePos[1] = LoadNodePos("J_Bip_R_Hand") + m_pos;
	m_attackNodePos[2] = LoadNodePos("J_Bip_L_ToeBase_end") + m_pos;
	m_attackNodePos[3] = LoadNodePos("J_Bip_R_ToeBase_end") + m_pos;

	m_state.Update(m_pos, m_moveDir);
	m_pos = m_state.GetPos();
	m_moveDir = m_state.GetDir();

	if (m_aliveFlg)
	{
		if (m_nowMoveState & MoveState::Run)
		{
			// ��]����
			UpdateRotate();
		}

		// �L��������֘A
		Action();
	}

	// �����蔻��
	Collider();

	// �L�����A�j���[�V����
	Animation();
}

void Player::PostUpdate()
{
	// �}�g���b�N�X�̍���
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	m_mWorld = m_rotateMat * m_transMat;
}

void Player::PreDraw()
{

}

void Player::GenerateDepthMapFromLight_SkinMesh()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Player::DrawUnlitWithTransparency_SkinMesh()
{
	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullNone);	// ���������J�����O��؂�
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
	KdShaderManager::Instance().UndoRasterizerState();								// �J�����O�̐ݒ��߂�
}

void Player::DrawDebug()
{
	m_pDebugWire->Draw();
}

void Player::Init()
{
	srand(timeGetTime());

	// ���f��(�L����)
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Player/Player.Test.gltf"));

	m_mWorld = Math::Matrix::Identity;			// ���[���h�}�g���b�N�X
	m_moveVec = Math::Vector3::Zero;			// �v���C���[�̌��݂̈ړ���
	m_moveDir = Math::Vector3{ -1.f, 0, 0 };	// �v���C���[�̌��݂̊p�x
	m_angle = 0;								// �v���C���[�̍��̉�]�p�x(Y��)

	// ����X�e�[�g�Z�b�g
	m_nowMoveState = MoveState::Idle;
	m_state.ChengeIdle(m_pos, m_moveDir);
	m_animator = std::make_shared<KdAnimator>();
	m_animator = m_state.GetAnime();
	m_animeSpd = m_state.GetAnimeSpeed();
	m_chengeFlg = true;
	m_aliveFlg = true;


	// �d�͊֌W
	m_keyFlg = false;
	m_gravityPow = 0;

	// �U���p�m�[�h�̓Ǎ�
	m_attackNodePos[0] = LoadNodePos("J_Bip_L_Hand") + m_pos;
	m_attackNodePos[1] = LoadNodePos("J_Bip_R_Hand") + m_pos;
	m_attackNodePos[2] = LoadNodePos("J_Bip_L_ToeBase_end") + m_pos;
	m_attackNodePos[3] = LoadNodePos("J_Bip_R_ToeBase_end") + m_pos;

	// �X�e�[�^�X�̐ݒ�
	m_hitPt = 10000.f;

	// �f�o�b�O
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	// �����蔻�菉����
	m_collisionFlg = true;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("PlayerBody", m_pos + Math::Vector3(0, 0.7f, 0), 0.5f, KdCollider::TypeDamage);
}

void Player::SetEnemy(std::shared_ptr<Enemy> _enemy)
{
	m_enemy = std::make_shared<Enemy>();
	m_enemy = _enemy;
}

void Player::Hit(float _damage)
{
	if (m_aliveFlg)
	{
		if (m_hitPt <= _damage)
		{
			m_nowMoveState = MoveState::Lose;
			m_state.ChengeLose(m_pos, m_moveDir);
			m_animator = std::make_shared<KdAnimator>();
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			m_chengeFlg = false;
			m_aliveFlg = false;
			m_hitPt = 0;
		}
		else
		{
			m_hitPt -= _damage;
			m_nowMoveState = MoveState::Damage;
			m_state.ChengeDamage(m_pos, m_moveDir);
			m_animator = std::make_shared<KdAnimator>();
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			m_chengeFlg = false;
		}
	}
}

void Player::UpdateRotate()
{
	// �ړ���
	m_moveVec.Normalize();

	// �L�����̌�����ς���
	// ���L�����������Ă������
	// �L�����̉�]�s����쐬
	Math::Matrix nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	// ���݂̕�����ό`������
	Math::Vector3 nowVec = Math::Vector3::TransformNormal(Math::Vector3(0, 0, 1), nowRotMat);

	// ������������
	Math::Vector3 toVec = -m_moveVec;

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

void Player::Action()
{
	//CheckAndAdjustPlayerStatus();
	if (m_enemy == nullptr)
	{
		if (m_nowMoveState != MoveState::Idle)
		{
			m_state.ChengeIdle(m_pos, m_moveDir);
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			ChengeState(MoveState::Idle);
		}
		return;
	}

	// �i�s���������߂邽�߂ɃJ�����̍s����擾
	std::shared_ptr<CameraBase> spCamera = m_wpCamera.lock();
	if (!spCamera)
	{
		return;
	}

	// �J�����̐�����]�����������̍s��擾
	const auto& mCam = spCamera->GetRotaionYMatrix();

	// �L��������
	// �J�����̕����ɓ���
	if (m_moveVec != Math::Vector3::Zero)
	{
		m_moveDir = m_moveVec;
		m_moveDir.Normalize();
	}
	m_moveVec = Math::Vector3::Zero;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000)
	{
		m_moveVec += mCam.Right();
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000)
	{
		m_moveVec += mCam.Left();
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000)
	{
		m_moveVec += mCam.Backward();
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000)
	{
		m_moveVec += mCam.Forward();
	}

	m_moveVec.Normalize();

	// �ڍs�t���O��true�̂Ƃ������ڍs����
	if (m_chengeFlg)
	{
		// �ړ��ʂ�����ꍇ�͑����Ԃֈڍs
		if (m_moveVec != Math::Vector3::Zero && m_nowMoveState != MoveState::Run)
		{
			m_state.ChengeRun(m_pos, m_moveVec);
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			ChengeState(MoveState::Run);
		}

		// �W�����v
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_gravityPow = 0.25f;
			m_state.ChengeJump(m_pos, m_moveDir);
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			ChengeState(MoveState::Jump);
		}

		// ���
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
		{
			m_state.ChengeAvoidance(m_pos, m_moveDir);
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			ChengeState(MoveState::Avoidance);
		}

		// �U��
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			m_collisionFlg = true;
			if (m_nowMoveState != MoveState::Attack)
			{
				m_state.ChengeAttack(m_pos, m_moveDir);
				m_animator = m_state.GetAnime();
				m_animeSpd = m_state.GetAnimeSpeed();
				ChengeState(MoveState::Attack);
			}
		}
	}

	// �ҋ@�Ƒ����ԈȊO�̓A�j���[�V�������I����Ă���ڍs
	if (m_nowMoveState != MoveState::Idle && m_nowMoveState != MoveState::Run)
	{
		if (m_nowMoveState & MoveState::Damage)
		{
			if (m_animator->IsAnimationEnd())
			{
				m_chengeFlg = true;
			}
			else
			{
				m_chengeFlg = false;
			}
		}

		if (m_animator->IsAnimationEnd())
		{
			m_chengeFlg = true;
		}
		else
		{
			m_chengeFlg = false;
		}
	}
	else
	{
		m_chengeFlg = true;
	}

	m_gravityPow += -0.007f;
	m_pos.y += m_gravityPow;
}

void Player::Collider()
{
	if (RayCollider(m_pos + Math::Vector3(0, 0.5f, 0), m_moveDir, 3.f, KdCollider::TypeGround))
	{
		/*m_pos = m_moveDir * m_maxOverLap;*/
		/*m_pos = m_rayHitPos - m_moveDir * -4.f;*/
	}

	if (SphereCollider(m_pos + Math::Vector3(0, 0.5f, 0), 0.7f, KdCollider::TypeGround))
	{
		m_gravityPow = 0;
		m_pos += m_sphereHitDir;
		if (m_aliveFlg)
		{
			// �ړ��ʂ��Ȃ��ҋ@��Ԃł͖���������ҋ@��Ԃֈڍs
			if (m_moveVec == Math::Vector3::Zero && m_nowMoveState != MoveState::Idle)
			{
				// �U�����[�V��������������A�j���[�V�������I����Ă���ҋ@�Ɉڍs
				if (m_chengeFlg)
				{
					m_state.ChengeIdle(m_pos, m_moveDir);
					m_animator = m_state.GetAnime();
					m_animeSpd = m_state.GetAnimeSpeed();
					ChengeState(MoveState::Idle);
				}
			}
		}
	}

	if (m_nowMoveState & MoveState::Attack && m_collisionFlg)
	{
		m_collisionFlg = false;
		for (int i = 0; i < NODE_NUM; i++)
		{
			if (SphereCollider(m_attackNodePos[i], 0.1f, KdCollider::TypeBump))
			{
				m_enemy->Hit(m_state.GetHitDamage());
			}
		}
	}
}

bool Player::RayCollider(Math::Vector3 _pos, Math::Vector3 _rayDir, float _range, KdCollider::Type _type)
{
	//========================================================
	//���C����
	//========================================================
	// ���C����p�ɕϐ����쐬
	KdCollider::RayInfo rayInfo;

	// ���C�̔��ˍ��W��ݒ�
	rayInfo.m_pos = _pos;

	// ���C�̕�����ݒ�
	rayInfo.m_dir = _rayDir;

	// ���C�̒�����ݒ�
	rayInfo.m_range = _range;

	// �����蔻����������^�C�v��ݒ�
	rayInfo.m_type = _type;

	// �f�o�b�O�p==========================================
	m_pDebugWire->AddDebugLine(rayInfo.m_pos, rayInfo.m_dir, rayInfo.m_range, { 0, 1, 0 });

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
	m_maxOverLap = 0;
	m_rayHitPos = Math::Vector3::Zero;
	bool hit = false;
	for (auto& ret : retRayList)
	{
		// ���C���Ւf���I�[�o�[��������
		// 1�Ԓ������̂�T��
		if (m_maxOverLap < ret.m_overlapDistance)
		{
			m_maxOverLap = ret.m_overlapDistance;
			m_rayHitPos = ret.m_hitPos;
			hit = true;
		}
	}

	// �������Ă�����
	if (hit)
	{
		return true;
	}
	return false;
}

bool Player::SphereCollider(Math::Vector3 _pos, float _radius, KdCollider::Type _type)
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
	m_maxOverLap = 0;
	bool sphereHitFlg = false;
	m_sphereHitDir = Math::Vector3::Zero; // ������������
	for (auto& ret : retSphereList)
	{
		// �P�ԋ߂��œ����������̂�T��
		if (m_maxOverLap < ret.m_overlapDistance)
		{
			m_maxOverLap = ret.m_overlapDistance;
			sphereHitFlg = true;
			m_sphereHitDir = ret.m_hitDir;
			m_sphereHitDir.Normalize();
		}
	}
	if (sphereHitFlg)
	{
		// ���ƃ��f�����������Ă���
		m_sphereHitDir *= m_maxOverLap;
		return true;
	}
	return false;
}

void Player::Animation()
{
	if (!m_model)	return;
	if (!m_animator) return;

	// �A�j���[�V�����̍X�V
	m_animator->AdvanceTime(m_model->WorkNodes(), m_animeSpd);
	m_model->CalcNodeMatrices();
}

void Player::ChengeState(MoveState _nextState)
{
	// �O�Ɠ����X�e�[�^�X�̏ꍇ�؂�ւ����s��Ȃ�
	if (m_nowMoveState == _nextState) return;

	m_nowMoveState = _nextState;
}

Math::Vector3 Player::LoadNodePos(std::string_view _nodeName)
{
	const KdModelWork::Node* pNode = m_model->FindNode(_nodeName);

	if (pNode)
	{
		return pNode->m_worldTransform.Translation();
	}
	return Math::Vector3::Zero;
}
