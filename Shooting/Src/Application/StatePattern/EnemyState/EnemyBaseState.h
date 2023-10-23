#pragma once

class EnemyBaseState
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Shot() = 0;	// �e�̔���
	virtual void Action() = 0;	// �����̑�{

	// ���f���̎擾
	std::shared_ptr<KdModelWork> GetModel()
	{
		// ���f��������΃��f����Ԃ��A�������null��Ԃ�
		if (m_model) { return m_model; }
		else { return nullptr;}
	}

protected:
	std::shared_ptr<KdModelWork> m_model = nullptr;	// ���f���f�[�^

	Math::Vector3 m_pos = Math::Vector3::Zero;		// ���W
	Math::Vector3 m_moveDir = Math::Vector3::Zero;	// �ړ��x�N�g��

	float m_standCnt;								// �e����������Ƃ��̑ҋ@����
	float m_angle;									// ��]����p
};