#pragma once

class BaseScene;
class Rock;

class Player : public KdGameObject
{
public:

	Player() { Init(); };
	~Player() {};

	void Update()override;
	void PostUpdate()override;

	void GenerateDepthMapFromLight()override;
	void DrawBright()override;
	void DrawLit()override;
	void Init()override;

	void SetOener(std::shared_ptr<BaseScene> _owner)
	{
		m_owner = _owner;
		m_owner.lock();
	}

	bool GetGravityFlg()
	{
		return m_gravityFlg;
	}

	bool PushBackGravityList(Rock* _rock)
	{
		if (m_gravityList.size() < 3)
		{
			m_gravityList.push_back(_rock);
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	void Action();
	void UpdateCollision();
	bool RockSphereCollision(Math::Vector3 _pos, float _radius, KdCollider::Type _type);
	void GravityThrow();

private:
	struct RockStatus
	{
		Math::Vector3 Pos;
		Math::Vector3 Vec;
	};

	std::shared_ptr<KdModelWork> m_model;	// モデル情報
	float m_roll = 0;						// z軸用回転量
	float m_pitch = 0;						// x軸用回転量

	std::weak_ptr<BaseScene> m_owner;

	// 座標移動系
	Math::Vector3 m_moveVec;				// 移動量
	Math::Vector3 m_moveDir;				// 進みたい角度

	// 岩等の引き寄せ処理用
	bool m_gravityFlg;
	std::list<Rock*> m_gravityList;

	// フラグ関係
	bool m_keyFlg;
	bool m_gravityKeyFlg;
	bool m_throwKeyFlg;
};