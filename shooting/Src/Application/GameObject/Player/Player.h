#pragma once
#include "../../StatePattern/PlayerState/PlayerStatePattern.h"

class Enemy;
class CameraBase;

class Player:public KdGameObject
{
public:
	Player() { Init(); }
	~Player() {}

	void Update()override;
	void PostUpdate()override;
	void PreDraw()override;
	void GenerateDepthMapFromLight_SkinMesh()override;
	void DrawUnlitWithTransparency_SkinMesh()override;
	void DrawDebug()override;
	void Init()override;

	void SetEnemy(std::shared_ptr<Enemy> _enemy);

	void SetCamera(const std::shared_ptr<CameraBase> camera)
	{
		m_wpCamera = camera;
	}

	void Hit(float _damage);

private:
	enum MoveState
	{
		Idle = 1 << 0,
		Walk = 1 << 1,
		Run = 1 << 2,
		Jump = 1 << 3,
		Attack = 1 << 4,
		Avoidance = 1 << 5,
		Damage = 1 << 6,
		Lose = 1 << 7
	};

	void UpdateRotate();
	void Action();

	// 当たり判定用関数
	void Collider();		// コライダー統括
	bool RayCollider(Math::Vector3 _pos, Math::Vector3 _rayDir, float _range, KdCollider::Type _type);		// レイ用コライダー
	bool SphereCollider(Math::Vector3 _pos, float _radius, KdCollider::Type _type);							// 球用コライダー

	// アニメーション用関数
	void Animation();
	void ChengeState(MoveState _nextState);	// アニメーション切り替え

	// 攻撃用関数
	Math::Vector3 LoadNodePos(std::string_view _nodeName);

	//======================================================================================
	//変数
	//======================================================================================
	// ステート管理
	PlayerStatePattern m_state;

	std::weak_ptr<CameraBase> m_wpCamera;

	std::shared_ptr<KdAnimator> m_animator = nullptr;

	std::shared_ptr<KdModelWork> m_model = nullptr;
	Math::Vector3 m_moveVec;
	Math::Vector3 m_moveDir;
	Math::Matrix m_rotateMat;
	Math::Matrix m_transMat;
	Math::Vector3 m_pos;
	float m_angle;						// キャラクターの今の回転角度(Y軸)

	// 重力
	float m_gravityPow;

	// アニメーション用
	MoveState m_nowMoveState;	// 現在のプレイヤーの状況
	float m_animeSpd;

	// 当たり判定
	Math::Vector3 m_sphereHitDir;
	Math::Vector3 m_rayHitPos;
	float m_maxOverLap;
	bool m_collisionFlg;
	static const int NODE_NUM = 4;
	Math::Vector3 m_attackNodePos[NODE_NUM];
	std::shared_ptr<Enemy> m_enemy;

	// フラグ
	bool m_keyFlg;
	bool m_chengeFlg;

	// プレイヤーのステータス
	float m_hitPt;					// 体力
	float m_attackPow;				// 攻撃力
	float m_defensePower;			// 防御力
	bool m_aliveFlg;				// 生存フラグ
};