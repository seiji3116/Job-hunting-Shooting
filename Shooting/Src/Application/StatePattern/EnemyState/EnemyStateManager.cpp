#include "EnemyStateManager.h"
#include "StateList/Normal/EnemyNormal.h"
#include "StateList/Rush/EnemyRush.h"
#include "StateList/Laser/EnemyLaser.h"

void EnemyStateManager::Update()
{
	m_nowState->Update();
}

void EnemyStateManager::PostUpdate()
{
	m_nowState->PostUpdate();
}

void EnemyStateManager::Action()
{
	m_nowState->Action();
}

std::shared_ptr<KdModelWork> EnemyStateManager::GetModel() const
{
	return m_nowState->GetModel();
}

Math::Vector3 EnemyStateManager::GetPos() const
{
	return m_nowState->GetPos();
}

Math::Vector3 EnemyStateManager::GetMoveDir() const
{
	return m_nowState->GetMoveDir();
}

void EnemyStateManager::SetTargetPos(const Math::Vector3& _pos)
{
	m_nowState->SetTargetPos(_pos);
}

void EnemyStateManager::ChengeRush()
{
	std::shared_ptr<EnemyRush> state = std::make_shared<EnemyRush>();
	ChengeState(state);
}

void EnemyStateManager::ChengeLaser()
{
	std::shared_ptr<EnemyLaser> state = std::make_shared<EnemyLaser>();
	ChengeState(state);
}

void EnemyStateManager::ChengeNormal()
{
	std::shared_ptr<EnemyNormal> state = std::make_shared<EnemyNormal>();
	ChengeState(state);
}

void EnemyStateManager::ChengeState(std::shared_ptr<EnemyBaseState> state)
{
	if (m_nowState == state)return;		// ���̃X�e�[�g�ƑO�̃X�e�[�g�������ꍇ�؂�ւ����s��Ȃ�

	m_nowState.reset();					// �O�܂ł̃X�e�[�g���폜����
	m_nowState = state;					// �w�肵���X�e�[�g�ɐ؂�ւ���
	m_nowState->Init();					// �؂�ւ��Ɠ����ɏ���������
}
