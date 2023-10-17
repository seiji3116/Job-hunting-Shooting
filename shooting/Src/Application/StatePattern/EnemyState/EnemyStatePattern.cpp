#include "EnemyStatePattern.h"

#include "StateList/JumpState/EnemyJumpState.h"
#include "StateList/RushState/EnemyRushState.h"
#include "StateList/WalkState/EnemyWalkState.h"
#include "StateList/IdleState/EnemyIdleState.h"

void EnemyStatePattern::Update(Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_state->Update(_pos, _dir);
}

Math::Vector3 EnemyStatePattern::GetPos() const
{
	return m_state->GetPos();
}

Math::Vector3 EnemyStatePattern::GetDir() const
{
	return m_state->GetDir();
}

std::shared_ptr<KdAnimator> EnemyStatePattern::GetAnime() const
{
	return m_state->GetAnime();
}

float EnemyStatePattern::GetAnimeSpeed() const
{
	return m_state->GetAnimeSpeed();
}

bool EnemyStatePattern::GetCollisionFlg() const
{
	return m_state->GetCollisionFlg();
}

bool EnemyStatePattern::GetStateChengeFlg() const
{
	return m_state->GetStateChengeFlg();
}

bool EnemyStatePattern::GetActionFlg() const
{
	return m_state->GetActionFlg();
}

float EnemyStatePattern::GetHitDamege() const
{
	return m_state->GetHitDamege();
}

void EnemyStatePattern::SetDir(Math::Vector3 _dir)
{
	m_state->SetDir(_dir);
}

void EnemyStatePattern::ChengeRush(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<EnemyState> state = std::make_shared<EnemyRushState>();
	ChengeState(state, _pos, _moveDir);
}

void EnemyStatePattern::ChengeWalk(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<EnemyState> state = std::make_shared<EnemyWalkState>();
	ChengeState(state, _pos, _moveDir);
}

void EnemyStatePattern::ChengeJump(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<EnemyState> state = std::make_shared<EnemyJumpState>();
	ChengeState(state, _pos, _moveDir);
}

void EnemyStatePattern::ChengeIdle(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<EnemyState> state = std::make_shared<EnemyIdleState>();
	ChengeState(state, _pos, _moveDir);
}

void EnemyStatePattern::ChengeState(std::shared_ptr<EnemyState> state, Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	if (m_state == state)return;									// ���̃X�e�[�g�ƑO�̃X�e�[�g�������ꍇ�؂�ւ����s��Ȃ�

	m_state.reset();												// �O�܂ł̃X�e�[�g���폜����
	m_state = state;												// �w�肵���X�e�[�g�ɐ؂�ւ���
	m_state->Init("Asset/Models/Enemy/Enemy.gltf", _pos, _moveDir);	// �؂�ւ��Ɠ����ɏ���������
}
