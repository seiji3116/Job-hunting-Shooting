#pragma once

class Player;

class Rock : public KdGameObject
{
public:

	Rock() { Init(); };
	~Rock() {};

	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void DrawBright()override;
	void Init()override;

	void Update()override;

	void SetPlayer(std::shared_ptr<Player> _player)
	{
		m_wpPlayer = _player;
	}
	void ChengeThrow(Math::Vector3 _targetVec)
	{
		m_targetVec = _targetVec;
		m_gravityFlg = false;
		m_throwFlg = true;
	}
private:
	void Throw();
	void Gravity();
	void Rotate(Math::Vector3 _targetDir);

private:

	std::shared_ptr<KdModelWork> m_model;

	std::weak_ptr<Player> m_wpPlayer;

	Math::Vector3 m_scale;
	Math::Matrix m_transMat;
	Math::Matrix m_rotateMat;
	Math::Matrix m_scaleMat;
	float m_angle;

	// プレイヤーに引き寄せられるとき
	Math::Vector3 m_playerVec;		// プレイヤーへのベクトル
	Math::Vector3 m_targetVec;		// ターゲットの方向
	Math::Vector3 m_targetPos;		// ターゲットの座標
	Math::Vector3 m_localPos;		// ターゲットからどのくらい離れているか
	bool m_gravityFlg;				// 今引き寄せられているか
	float m_gravityPow;				// 引き寄せられるspeed

	// プレイヤーから投げられる時
	bool m_throwFlg;
};