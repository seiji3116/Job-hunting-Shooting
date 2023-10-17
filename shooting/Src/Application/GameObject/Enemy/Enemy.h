#pragma once
#include "../../StatePattern/EnemyState/EnemyStatePattern.h"

class Player;

class Enemy :public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy() {}

	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight_SkinMesh()override;
	void DrawLit_SkinMesh()override;
	void Init()override;

	void DrawDebug()override;

	void SetPlayer(std::shared_ptr<Player> _player);

	void Hit(float _damage);

private:
	enum MoveState
	{
		Idle = 1 << 0,
		Walk = 1 << 1,
		Jump = 1 << 2,
		Rush = 1 << 3
	};

	void Action();
	void Animation();
	void UpdateRotate();	// ��]����
	void Collider();	// �R���C�_�[����
	bool RayCollider(Math::Vector3 _pos, Math::Vector3 _rayDir, float _range, KdCollider::Type _type);		// ���C�p�R���C�_�[
	bool SphereCollider(Math::Vector3 _pos, float _radius, KdCollider::Type _type);	// �~�p�R���C�_�[

	EnemyStatePattern m_state;

	std::shared_ptr<KdModelWork> m_model = nullptr;

	// �A�j���[�V�����p
	std::shared_ptr<KdAnimator> m_animator = nullptr;
	float m_animeSpd;
	bool m_animeChenge;

	Math::Vector3 m_pos;		// ���W
	Math::Vector3 m_moveDir;	// �ړ������x�N�g��
	Math::Vector3 m_moveVec;	// �ړ��x�N�g��
	Math::Matrix m_transMat;
	Math::Matrix m_rotateMat;

	float m_angle;				// ���̊p�x
	bool m_rotateFlg;

	float m_idleCnt;

	// �����蔻��p
	float m_sphereMaxOverLap;
	Math::Vector3 m_sphereHitDir;
	bool m_collisionFlg;			// 1�A�j���[�V�����ɂ��P��̓����蔻��ɂȂ�悤�ɂ���

	// �d��
	float m_gravity;

	// �G�̃X�e�[�^�X
	float m_hitPt;
	bool m_aliveFlg;

	// ���݂̃X�e�[�g
	MoveState m_nowMoveState;
	MoveState m_nextMoveState;

	std::shared_ptr<Player> m_player;
};