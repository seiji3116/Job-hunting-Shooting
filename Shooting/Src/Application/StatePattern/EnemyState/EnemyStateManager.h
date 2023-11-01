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
	Math::Matrix GetMatrix() const;
	float GetActionCnt() const;
	bool GetActionEndFlg() const;
	void SetTargetDir(const Math::Vector3& _dir);
	void SetMoveDir(const Math::Vector3& _moveDir);
	void SetMatrix(const Math::Matrix& _matrix);

public:
	// ステートの切り替え
	void ChengeRush();		// 突進
	void ChengeLaser();		// レーザーの発射
	void ChengeNormal();	// 通常弾を発射できる状態
	void ChengeTracking();	// プレイヤーへの追尾状態

private:
	// ここで切り替えを行う
	// 現在のステートを削除し、次のステートに移行する
	void ChengeState(std::shared_ptr<EnemyBaseState> state);

private:
	// 現在のステート
	std::shared_ptr<EnemyBaseState> m_nowState;
};