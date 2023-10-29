#pragma once

class EnemyBaseState;

class EnemyStateManager
{
public:
	// ステートの初期値設定
	EnemyStateManager(){}

public:
	// Baseの関数呼び出し用
	void Update();
	void PostUpdate();
	void Action();
	std::shared_ptr<KdModelWork> GetModel() const;
	Math::Vector3 GetPos() const;
	Math::Vector3 GetMoveDir() const;
	void SetTargetPos(const Math::Vector3& _pos);

public:
	// ステートの切り替え
	void ChengeRush();		// 突進
	void ChengeLaser();		// レーザーの発射
	void ChengeNormal();	// 通常状態

private:
	// ここで切り替えを行う
	// 現在のステートを削除し、次のステートに移行する
	void ChengeState(std::shared_ptr<EnemyBaseState> state);

private:
	// 現在のステート
	std::shared_ptr<EnemyBaseState> m_nowState;
};