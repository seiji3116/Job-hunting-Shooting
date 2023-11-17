#pragma once

class BaseState;

class StateManager
{
public:
	// ステートの初期値設定
	StateManager(){}

public:
	// Baseの関数呼び出し用
	void Update(KdGameObject& _owner);

	Math::Vector3 GetMoveDir() const;
	float GetActionCnt() const;
	bool GetActionEndFlg() const;

	void SetMoveDir(const Math::Vector3& _moveDir);
	void SetMatrix(const Math::Matrix& _matrix);
	void SetPos(const Math::Vector3& _pos);

public:
	// ステートの切り替え
	void ChengeRush(KdGameObject& _owner);		// 突進
	void ChengeLaser(KdGameObject& _owner);		// レーザーの発射
	void ChengeNormal(KdGameObject& _owner);	// 通常弾を発射できる状態
	void ChengeTracking(KdGameObject& _owner);	// プレイヤーへの追尾状態

private:
	// ここで切り替えを行う
	// 現在のステートを削除し、次のステートに移行する
	void ChengeState(std::shared_ptr<BaseState> state, KdGameObject& _owner);

private:
	// 現在のステート
	std::shared_ptr<BaseState> m_nowState;
};