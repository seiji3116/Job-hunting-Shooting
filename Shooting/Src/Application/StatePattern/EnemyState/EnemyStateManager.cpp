#include "EnemyStateManager.h"
#include "StateList/Normal/EnemyNormal.h"
#include "StateList/Rush/EnemyRush.h"
#include "StateList/Laser/EnemyLaser.h"
#include "StateList/Tracking/EnemyTracking.h"

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

Math::Matrix EnemyStateManager::GetMatrix() const
{
	return m_nowState->GetMatrix();
}

float EnemyStateManager::GetActionCnt() const
{
	return m_nowState->GetActionCnt();
}

bool EnemyStateManager::GetActionEndFlg() const
{
	return m_nowState->GetActionEndFlg();
}

void EnemyStateManager::SetTargetDir(const Math::Vector3& _dir)
{
	m_nowState->SetTargetDir(_dir);
}

void EnemyStateManager::SetTargetPos(const Math::Vector3& _pos)
{
	m_nowState->SetTargetPos(_pos);
}

void EnemyStateManager::SetMoveDir(const Math::Vector3& _moveDir)
{
	m_nowState->SetMoveDir(_moveDir);
}

void EnemyStateManager::SetMatrix(const Math::Matrix& _matrix)
{
	m_nowState->SetMatrix(_matrix);
}

void EnemyStateManager::SetPos(const Math::Vector3& _pos)
{
	m_nowState->SetPos(_pos);
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

void EnemyStateManager::ChengeTracking()
{
	std::shared_ptr<EnemyTracking> state = std::make_shared<EnemyTracking>();
	ChengeState(state);
}

void EnemyStateManager::ChengeState(std::shared_ptr<EnemyBaseState> state)
{
	if (m_nowState == state)return;		// 次のステートと前のステートが同じ場合切り替えを行わない

	m_nowState.reset();					// 前までのステートを削除する
	m_nowState = state;					// 指定したステートに切り替える
	m_nowState->Init();					// 切り替えと同時に初期化する
}
