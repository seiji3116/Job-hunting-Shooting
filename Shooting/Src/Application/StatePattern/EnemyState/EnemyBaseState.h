#pragma once

class EnemyBaseState
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Shot() = 0;	// 弾の発射
	virtual void Action() = 0;	// 挙動の大本

	// モデルの取得
	std::shared_ptr<KdModelWork> GetModel()
	{
		// モデルがあればモデルを返す、無ければnullを返す
		if (m_model) { return m_model; }
		else { return nullptr;}
	}

protected:
	std::shared_ptr<KdModelWork> m_model = nullptr;	// モデルデータ

	Math::Vector3 m_pos = Math::Vector3::Zero;		// 座標
	Math::Vector3 m_moveDir = Math::Vector3::Zero;	// 移動ベクトル

	float m_standCnt;								// 各挙動をするときの待機時間
	float m_angle;									// 回転制御用
};