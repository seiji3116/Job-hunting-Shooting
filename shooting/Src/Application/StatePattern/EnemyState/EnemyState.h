#pragma once

class EnemyState
{
public:
	virtual void Init(std::string_view _modelName, Math::Vector3 _pos, Math::Vector3 _dir) = 0;
	virtual void Update(Math::Vector3 _pos = Math::Vector3::Zero, Math::Vector3 _dir = Math::Vector3::Zero) = 0;
	virtual Math::Vector3 GetPos() const = 0;
	virtual Math::Vector3 GetDir() const = 0;
	virtual std::shared_ptr<KdAnimator> GetAnime() const = 0;
	virtual float GetAnimeSpeed() const = 0;
	virtual bool GetCollisionFlg() const = 0;	// �v���C���[�ɍU�����Ă�������Ԃ�
	virtual bool GetStateChengeFlg() const = 0; // ���X�e�[�g��ς��Ă������̂��ϑ�
	virtual bool GetActionFlg() const = 0;		// ���U������
	virtual float GetHitDamege() const = 0;		// ���݂̃X�e�[�g��Damage��
	virtual void SetDir(Math::Vector3 _dir) = 0;

	enum MovePattern
	{
		Standby,
		Action,
		Landing
	};

protected:
	std::shared_ptr<KdAnimator> m_animator = nullptr;	// ���f���f�[�^�Ɋ܂܂��A�j���[�V����
	std::shared_ptr<KdModelWork> m_model = nullptr;		// ���f���f�[�^
	float m_animeSpd = 0;								// �A�j���[�V�����̍Đ����x

	Math::Vector3 m_pos = Math::Vector3::Zero;
	Math::Vector3 m_moveDir = Math::Vector3::Zero;

	float m_standCnt;
	bool m_patternChengeFlg;

	bool m_collisionFlg;

	MovePattern m_nowMovePattern = MovePattern::Standby;
	MovePattern m_nextMovePatterm = m_nowMovePattern;
};