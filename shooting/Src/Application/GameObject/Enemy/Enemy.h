#pragma once
#include "../../StatePattern/EnemyState/EnemyStatePattern.h"

class Player;

class Enemy :public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy() {}

	void Update()override;
	void PostUpdate()override;
	void GenerateDepthMapFromLight_SkinMesh()override;
	void DrawLit_SkinMesh()override;
	void Init()override;

	void DrawDebug()override;

	void SetPlayer(std::shared_ptr<Player> _player);

	void Hit(float _damage);

private:
	enum MoveState
	{
		Idle = 1 << 0,
		Walk = 1 << 1,
		Jump = 1 << 2,
		Rush = 1 << 3
	};

	void Action();
	void Animation();
	void UpdateRotate();	// 回転処理
	void Collider();	// コライダー統括
	bool RayCollider(Math::Vector3 _pos, Math::Vector3 _rayDir, float _range, KdCollider::Type _type);		// レイ用コライダー
	bool SphereCollider(Math::Vector3 _pos, float _radius, KdCollider::Type _type);	// 円用コライダー

	EnemyStatePattern m_state;

	std::shared_ptr<KdModelWork> m_model = nullptr;

	// アニメーション用
	std::shared_ptr<KdAnimator> m_animator = nullptr;
	float m_animeSpd;
	bool m_animeChenge;

	Math::Vector3 m_pos;		// 座標
	Math::Vector3 m_moveDir;	// 移動方向ベクトル
	Math::Vector3 m_moveVec;	// 移動ベクトル
	Math::Matrix m_transMat;
	Math::Matrix m_rotateMat;

	float m_angle;				// 今の角度
	bool m_rotateFlg;

	float m_idleCnt;

	// 当たり判定用
	float m_sphereMaxOverLap;
	Math::Vector3 m_sphereHitDir;
	bool m_collisionFlg;			// 1アニメーションにつき１回の当たり判定になるようにする

	// 重力
	float m_gravity;

	// 敵のステータス
	float m_hitPt;
	bool m_aliveFlg;

	// 現在のステート
	MoveState m_nowMoveState;
	MoveState m_nextMoveState;

	std::shared_ptr<Player> m_player;
};