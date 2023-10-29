#pragma once

class EnemyBaseState
{
public:
	// 基本関数
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void PostUpdate() = 0;
	virtual void Shot() = 0;	// 弾の発射
	virtual void Action() = 0;	// 挙動の大本

public:
	// ゲッター

	// モデルの取得
	std::shared_ptr<KdModelWork> GetModel() const
	{
		// モデルがあればモデルを返す、無ければnullを返す
		if (m_model) { return m_model; }
		else { return nullptr;}
	}

	Math::Vector3 GetPos() const { return m_pos; }	// 座標の取得

	Math::Vector3 GetMoveDir() const { return m_moveDir; }	// 移動ベクトル取得

public:
	// セッター
	void SetTargetPos(const Math::Vector3& _pos) { m_targetPos = _pos; }

protected:
	std::shared_ptr<KdModelWork> m_model = nullptr;	// モデルデータ

	Math::Vector3 m_pos = Math::Vector3::Zero;		// 座標
	Math::Vector3 m_moveDir = Math::Vector3::Zero;	// 移動ベクトル
	float m_moveSpd = 0;							// 移動speed
	Math::Vector3 m_targetPos = Math::Vector3::Zero;// ターゲットの座標

	float m_standCnt = 0;							// 各挙動をするときの待機時間
	float m_angle = 0;								// 回転制御用
};