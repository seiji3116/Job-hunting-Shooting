#pragma once

class EnemyBaseState;

class EnemyStateManager
{
public:
	// ステートの初期値設定
	EnemyStateManager(){}

public:
	// 主な処理
	void Init();
	void Update();
	void Action();
	std::shared_ptr<KdModelWork> GetModel();

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