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
	if (m_state == state)return;											// 次のステートと前のステートが同じ場合切り替えを行わない

	m_state.reset();														// 前までのステートを削除する
	m_state = state;														// 指定したステートに切り替える
	m_state->Init("Asset/Models/Player/Player.Test.gltf", _pos, _moveDir);	// 切り替えと同時に初期化する
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

// 攻撃ステートに切り替える
void PlayerStatePattern::ChengeAttack(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<AttackState>();
	ChengeState(state, _pos, _moveDir);
}

// 回避ステートに切り替える
void PlayerStatePattern::ChengeAvoidance(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<AvoidanceState>();
	ChengeState(state, _pos, _moveDir);
}

// ダメージステートに切り替える
void PlayerStatePattern::ChengeDamage(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<DamageState>();
	ChengeState(state, _pos, _moveDir);
}

// 待機ステートに切り替える
void PlayerStatePattern::ChengeIdle(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<IdleState>();
	ChengeState(state, _pos, _moveDir);
}

// ジャンプステートに切り替える
void PlayerStatePattern::ChengeJump(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<JumpState>();
	ChengeState(state, _pos, _moveDir);
}

// 敗北ステートに切り替える
void PlayerStatePattern::ChengeLose(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<LoseState>();
	ChengeState(state, _pos, _moveDir);
}

// 走りステートに切り替える
void PlayerStatePattern::ChengeRun(Math::Vector3 _pos, Math::Vector3 _moveDir)
{
	std::shared_ptr<PlayerState> state = std::make_shared<RunState>();
	ChengeState(state, _pos, _moveDir);
}
