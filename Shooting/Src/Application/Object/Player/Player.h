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

	std::shared_ptr<KdModelWork> m_model;	// ���f�����
	float m_roll = 0;						// z���p��]��
	float m_pitch = 0;						// x���p��]��

	std::weak_ptr<BaseScene> m_owner;

	// ���W�ړ��n
	Math::Vector3 m_moveVec;				// �ړ���
	Math::Vector3 m_moveDir;				// �i�݂����p�x

	// �ⓙ�̈����񂹏����p
	bool m_gravityFlg;
	std::list<Rock*> m_gravityList;

	// �t���O�֌W
	bool m_keyFlg;
	bool m_gravityKeyFlg;
	bool m_throwKeyFlg;
};