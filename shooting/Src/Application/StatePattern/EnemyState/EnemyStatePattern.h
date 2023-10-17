#pragma once

class EnemyState;

class EnemyStatePattern
{
public:
	// ステートの初期値設定
	EnemyStatePattern() {}

public:
	// 主要な処理
	void Update(Math::Vector3 _pos = Math::Vector3::Zero, Math::Vector3 _dir = Math::Vector3::Zero);
	Math::Vector3 GetPos() const;
	Math::Vector3 GetDir() const;
	std::shared_ptr<KdAnimator> GetAnime() const;
	float GetAnimeSpeed() const;
	bool GetCollisionFlg() const;
	bool GetStateChengeFlg() const;
	bool GetActionFlg() const;
	float GetHitDamege() const;
	void SetDir(Math::Vector3 _dir);

	// ステートの切り替え
	void ChengeRush(Math::Vector3 _pos, Math::Vector3 _moveDir);	// 突進
	void ChengeWalk(Math::Vector3 _pos, Math::Vector3 _moveDir);	// 歩き
	void ChengeJump(Math::Vector3 _pos, Math::Vector3 _moveDir);	// ジャンプ
	void ChengeIdle(Math::Vector3 _pos, Math::Vector3 _moveDir);	// 待機

private:
	// ここで切り替えを行う
	// 現在のステートを削除し、次のステートに移行する
	void ChengeState(std::shared_ptr<EnemyState> state, Math::Vector3 _pos, Math::Vector3 _moveDir);

private:
	// 現在のステート
	std::shared_ptr<EnemyState> m_state;
};