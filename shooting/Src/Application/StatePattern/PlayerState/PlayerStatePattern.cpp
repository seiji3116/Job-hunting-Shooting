#include "PlayerStatePattern.h"

#include "StateList/AttackState/AttackState.h"
#include "StateList/AvoidanceState/AvoidanceState.h"
#include "StateList/DamageState/DamageState.h"
#include "StateList/IdleState/IdleState.h"
#include "StateList/JumpState/JumpState.h"
#include "StateList/LoseState/LoseState.h"
#include "StateList/RunState/RunState.h"

void PlayerStatePattern::ChengeState(std::shared_ptr<PlayerState> state, Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	if (m_state == state)return;											// ���̃X�e�[�g�ƑO�̃X�e�[�g�������ꍇ�؂�ւ����s��Ȃ�

	m_state.reset();														// �O�܂ł̃X�e�[�g���폜����
	m_state = state;														// �w�肵���X�e�[�g�ɐ؂�ւ���
	m_state->Init("Asset/Models/Player/Player.Test.gltf", _pos, _moveDir);	// �؂�ւ��Ɠ����ɏ���������
}

void PlayerStatePattern::Update(Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_state->Update(_pos, _dir);
}

Math::Vector3 PlayerStatePattern::GetPos() const
{
	return m_state->GetPos();
}

Math::Vector3 PlayerStatePattern::GetDir() const
{
	return m_state->GetDir();
}

std::shared_ptr<KdAnimator> PlayerStatePattern::GetAnime() const
{
	return m_state->GetAnime();
}

float PlayerStatePattern::GetAnimeSpeed() const
{
	return m_state->GetAnimeSpeed();
}

float PlayerStatePattern::GetHitDamage() const
{
	return m_state->GetHitDamage();
}

// �U���X�e�[�g�ɐ؂�ւ���
void PlayerStatePattern::ChengeAttack(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<AttackState>();
	ChengeState(state, _pos, _moveDir);
}

// ����X�e�[�g�ɐ؂�ւ���
void PlayerStatePattern::ChengeAvoidance(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<AvoidanceState>();
	ChengeState(state, _pos, _moveDir);
}

// �_���[�W�X�e�[�g�ɐ؂�ւ���
void PlayerStatePattern::ChengeDamage(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<DamageState>();
	ChengeState(state, _pos, _moveDir);
}

// �ҋ@�X�e�[�g�ɐ؂�ւ���
void PlayerStatePattern::ChengeIdle(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<IdleState>();
	ChengeState(state, _pos, _moveDir);
}

// �W�����v�X�e�[�g�ɐ؂�ւ���
void PlayerStatePattern::ChengeJump(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<JumpState>();
	ChengeState(state, _pos, _moveDir);
}

// �s�k�X�e�[�g�ɐ؂�ւ���
void PlayerStatePattern::ChengeLose(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<LoseState>();
	ChengeState(state, _pos, _moveDir);
}

// ����X�e�[�g�ɐ؂�ւ���
void PlayerStatePattern::ChengeRun(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<RunState>();
	ChengeState(state, _pos, _moveDir);
}
