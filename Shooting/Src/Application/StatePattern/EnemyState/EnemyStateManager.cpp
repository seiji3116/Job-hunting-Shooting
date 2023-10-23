#include "EnemyStateManager.h"
#include "StateList/Normal/EnemyNormal.h"
#include "StateList/Rush/EnemyRush.h"
#include "StateList/Laser/EnemyLaser.h"

void EnemyStateManager::Init()
{
	m_nowState->Init();
}

void EnemyStateManager::Update()
{
	m_nowState->Update();
}

void EnemyStateManager::Action()
{
	m_nowState->Action();
}

std::shared_ptr<KdModelWork> EnemyStateManager::GetModel()
{
	return m_nowState->GetModel();
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
