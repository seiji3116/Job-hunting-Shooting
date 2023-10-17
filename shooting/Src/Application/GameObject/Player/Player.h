#pragma once
#include "../../StatePattern/PlayerState/PlayerStatePattern.h"

class Enemy;
class CameraBase;

class Player:public KdGameObject
{
public:
	Player() { Init(); }
	~Player() {}

	void Update()override;
	void PostUpdate()override;
	void PreDraw()override;
	void GenerateDepthMapFromLight_SkinMesh()override;
	void DrawUnlitWithTransparency_SkinMesh()override;
	void DrawDebug()override;
	void Init()override;

	void SetEnemy(std::shared_ptr<Enemy> _enemy);

	void SetCamera(const std::shared_ptr<CameraBase> camera)
	{
		m_wpCamera = camera;
	}

	void Hit(float _damage);

private:
	enum MoveState
	{
		Idle = 1 << 0,
		Walk = 1 << 1,
		Run = 1 << 2,
		Jump = 1 << 3,
		Attack = 1 << 4,
		Avoidance = 1 << 5,
		Damage = 1 << 6,
		Lose = 1 << 7
	};

	void UpdateRotate();
	void Action();

	// �����蔻��p�֐�
	void Collider();		// �R���C�_�[����
	bool RayCollider(Math::Vector3 _pos, Math::Vector3 _rayDir, float _range, KdCollider::Type _type);		// ���C�p�R���C�_�[
	bool SphereCollider(Math::Vector3 _pos, float _radius, KdCollider::Type _type);							// ���p�R���C�_�[

	// �A�j���[�V�����p�֐�
	void Animation();
	void ChengeState(MoveState _nextState);	// �A�j���[�V�����؂�ւ�

	// �U���p�֐�
	Math::Vector3 LoadNodePos(std::string_view _nodeName);

	//======================================================================================
	//�ϐ�
	//======================================================================================
	// �X�e�[�g�Ǘ�
	PlayerStatePattern m_state;

	std::weak_ptr<CameraBase> m_wpCamera;

	std::shared_ptr<KdAnimator> m_animator = nullptr;

	std::shared_ptr<KdModelWork> m_model = nullptr;
	Math::Vector3 m_moveVec;
	Math::Vector3 m_moveDir;
	Math::Matrix m_rotateMat;
	Math::Matrix m_transMat;
	Math::Vector3 m_pos;
	float m_angle;						// �L�����N�^�[�̍��̉�]�p�x(Y��)

	// �d��
	float m_gravityPow;

	// �A�j���[�V�����p
	MoveState m_nowMoveState;	// ���݂̃v���C���[�̏�
	float m_animeSpd;

	// �����蔻��
	Math::Vector3 m_sphereHitDir;
	Math::Vector3 m_rayHitPos;
	float m_maxOverLap;
	bool m_collisionFlg;
	static const int NODE_NUM = 4;
	Math::Vector3 m_attackNodePos[NODE_NUM];
	std::shared_ptr<Enemy> m_enemy;

	// �t���O
	bool m_keyFlg;
	bool m_chengeFlg;

	// �v���C���[�̃X�e�[�^�X
	float m_hitPt;					// �̗�
	float m_attackPow;				// �U����
	float m_defensePower;			// �h���
	bool m_aliveFlg;				// �����t���O
};