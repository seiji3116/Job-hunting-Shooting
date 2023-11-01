#pragma once

class EnemyBaseState
{
public:
	// 基本関数
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void PostUpdate() = 0;
	virtual void Shot() = 0;							// 弾の発射
	virtual void Action() = 0;							// 挙動の大本

public:
	// ゲッター

	// モデルの取得
	std::shared_ptr<KdModelWork> GetModel() const
	{
		// モデルがあればモデルを返す、無ければnullを返す
		if (m_model) { return m_model; }
		else { return nullptr;}
	}

	Math::Vector3 GetPos() const { return m_mWorld.Translation(); }		// 座標の取得
	Math::Vector3 GetMoveDir() const { return m_moveDir; }				// 移動ベクトル取得
	Math::Matrix GetMatrix() const { return m_mWorld; }					// 行列の取得
	float GetActionCnt() const { return m_actionCnt; }					// 現在のAction実行時間の取得
	bool GetActionEndFlg() const { return m_actionEndFlg; }				// 現在のActiongが終わっているかどうか

public:
	// セッター
	void SetTargetDir(const Math::Vector3& _dir) { m_targetDir = _dir; }
	void SetMoveDir(const Math::Vector3& _moveDir) { m_moveDir = _moveDir; }
	void SetMatrix(const Math::Matrix& _matrix) { m_mWorld = _matrix; }

protected:
	virtual void Rotate(Math::Vector3 _targetDir) = 0;	// 回転処理

protected:
	std::shared_ptr<KdModelWork> m_model = nullptr;	// モデルデータ

	Math::Matrix m_mWorld;							// ワールド行列

	//Math::Vector3 m_pos = Math::Vector3::Zero;		// 座標
	Math::Vector3 m_moveDir = Math::Vector3::Zero;	// 移動ベクトル
	float m_moveSpd = 0;							// 移動speed
	Math::Vector3 m_targetDir = Math::Vector3::Zero;// ターゲットの座標

	float m_standCnt = 0;							// 各挙動をするときの待機時間
	float m_actionCnt = 1;							// 各挙動を実行しているときの時間
	bool m_actionEndFlg = false;					// 挙動が終わっていてステートを変えてもいいかを見るフラグ
};