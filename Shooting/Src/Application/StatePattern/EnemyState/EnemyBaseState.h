#pragma once

class EnemyBaseState
{
public:
	// ��{�֐�
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void PostUpdate() = 0;
	virtual void Shot() = 0;	// �e�̔���
	virtual void Action() = 0;	// �����̑�{

public:
	// �Q�b�^�[

	// ���f���̎擾
	std::shared_ptr<KdModelWork> GetModel() const
	{
		// ���f��������΃��f����Ԃ��A�������null��Ԃ�
		if (m_model) { return m_model; }
		else { return nullptr;}
	}

	Math::Vector3 GetPos() const { return m_pos; }	// ���W�̎擾

	Math::Vector3 GetMoveDir() const { return m_moveDir; }	// �ړ��x�N�g���擾

public:
	// �Z�b�^�[
	void SetTargetPos(const Math::Vector3& _pos) { m_targetPos = _pos; }

protected:
	std::shared_ptr<KdModelWork> m_model = nullptr;	// ���f���f�[�^

	Math::Vector3 m_pos = Math::Vector3::Zero;		// ���W
	Math::Vector3 m_moveDir = Math::Vector3::Zero;	// �ړ��x�N�g��
	float m_moveSpd = 0;							// �ړ�speed
	Math::Vector3 m_targetPos = Math::Vector3::Zero;// �^�[�Q�b�g�̍��W

	float m_standCnt = 0;							// �e����������Ƃ��̑ҋ@����
	float m_angle = 0;								// ��]����p
};