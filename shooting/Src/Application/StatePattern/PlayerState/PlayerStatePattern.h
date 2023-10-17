#pragma once

class PlayerState;

class PlayerStatePattern
{
public:
	// ステートの初期値設定
	PlayerStatePattern() {}

public:
	// 主要な処理
	void Update(Math::Vector3 _pos = Math::Vector3::Zero, Math::Vector3 _dir = Math::Vector3::Zero);
	Math::Vector3 GetPos() const;
	Math::Vector3 GetDir() const;
	std::shared_ptr<KdAnimator> GetAnime() const;
	float GetAnimeSpeed() const;
	float GetHitDamage() const;
	
	// ステートの切り替え
	void ChengeAttack(Math::Vector3 _pos, Math::Vector3 _moveDir);		// 攻撃
	void ChengeAvoidance(Math::Vector3 _pos, Math::Vector3 _moveDir);	// 回避
	void ChengeDamage(Math::Vector3 _pos, Math::Vector3 _moveDir);		// ダメージ
	void ChengeJump(Math::Vector3 _pos, Math::Vector3 _moveDir);		// ジャンプ
	void ChengeLose(Math::Vector3 _pos, Math::Vector3 _moveDir);		// 敗北
	void ChengeIdle(Math::Vector3 _pos, Math::Vector3 _moveDir);		// 待機
	void ChengeRun(Math::Vector3 _pos, Math::Vector3 _moveDir);			// 走り

private:
	// ここで切り替えを行う
	// 現在のステートを削除し、次のステートに移行する
	void ChengeState(std::shared_ptr<PlayerState> state, Math::Vector3 _pos, Math::Vector3 _moveDir);

private:
	// 現在のステート
	std::shared_ptr<PlayerState> m_state;
};