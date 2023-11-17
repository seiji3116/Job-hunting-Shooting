#include "StateManager.h"
#include "EnemyState/Normal/EnemyNormal.h"
#include "EnemyState/Rush/EnemyRush.h"
#include "EnemyState/Laser/EnemyLaser.h"
#include "EnemyState/Tracking/EnemyTracking.h"

void StateManager::Update(KdGameObject& _owner)
{
	m_nowState->Update(_owner);
}

Math::Vector3 StateManager::GetMoveDir() const
{
	return m_nowState->GetMoveDir();
}

float StateManager::GetActionCnt() const
{
	return m_nowState->GetActionCnt();
}

bool StateManager::GetActionEndFlg() const
{
	return m_nowState->GetActionEndFlg();
}

void StateManager::SetMoveDir(const Math::Vector3& _moveDir)
{
	m_nowState->SetMoveDir(_moveDir);
}

void StateManager::SetMatrix(const Math::Matrix& _matrix)
{
	m_nowState->SetMatrix(_matrix);
}

void StateManager::SetPos(const Math::Vector3& _pos)
{
	m_nowState->SetPos(_pos);
}

void StateManager::ChengeRush(KdGameObject& _owner)
{
	std::shared_ptr<EnemyRush> state = std::make_shared<EnemyRush>();
	ChengeState(state, _owner);
}

void StateManager::ChengeLaser(KdGameObject& _owner)
{
	std::shared_ptr<EnemyLaser> state = std::make_shared<EnemyLaser>();
	ChengeState(state, _owner);
}

void StateManager::ChengeNormal(KdGameObject& _owner)
{
	std::shared_ptr<EnemyNormal> state = std::make_shared<EnemyNormal>();
	ChengeState(state, _owner);
}

void StateManager::ChengeTracking(KdGameObject& _owner)
{
	std::shared_ptr<EnemyTracking> state = std::make_shared<EnemyTracking>();
	ChengeState(state, _owner);
}

void StateManager::ChengeState(std::shared_ptr<BaseState> state, KdGameObject& _owner)
{
	if (m_nowState == state)return;		// ���̃X�e�[�g�ƑO�̃X�e�[�g�������ꍇ�؂�ւ����s��Ȃ�

	m_nowState.reset();					// �O�܂ł̃X�e�[�g���폜����
	m_nowState = state;					// �w�肵���X�e�[�g�ɐ؂�ւ���
	m_nowState->Init(_owner);			// �؂�ւ��Ɠ����ɏ��������A�I�[�i�[�̃Z�b�g
}
