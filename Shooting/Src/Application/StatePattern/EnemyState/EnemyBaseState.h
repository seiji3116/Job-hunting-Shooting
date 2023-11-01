#pragma once

class EnemyBaseState
{
public:
	// ��{�֐�
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void PostUpdate() = 0;
	virtual void Shot() = 0;							// �e�̔���
	virtual void Action() = 0;							// �����̑�{

public:
	// �Q�b�^�[

	// ���f���̎擾
	std::shared_ptr<KdModelWork> GetModel() const
	{
		// ���f��������΃��f����Ԃ��A�������null��Ԃ�
		if (m_model) { return m_model; }
		else { return nullptr;}
	}

	Math::Vector3 GetPos() const { return m_mWorld.Translation(); }		// ���W�̎擾
	Math::Vector3 GetMoveDir() const { return m_moveDir; }				// �ړ��x�N�g���擾
	Math::Matrix GetMatrix() const { return m_mWorld; }					// �s��̎擾
	float GetActionCnt() const { return m_actionCnt; }					// ���݂�Action���s���Ԃ̎擾
	bool GetActionEndFlg() const { return m_actionEndFlg; }				// ���݂�Actiong���I����Ă��邩�ǂ���

public:
	// �Z�b�^�[
	void SetTargetDir(const Math::Vector3& _dir) { m_targetDir = _dir; }
	void SetMoveDir(const Math::Vector3& _moveDir) { m_moveDir = _moveDir; }
	void SetMatrix(const Math::Matrix& _matrix) { m_mWorld = _matrix; }

protected:
	virtual void Rotate(Math::Vector3 _targetDir) = 0;	// ��]����

protected:
	std::shared_ptr<KdModelWork> m_model = nullptr;	// ���f���f�[�^

	Math::Matrix m_mWorld;							// ���[���h�s��

	//Math::Vector3 m_pos = Math::Vector3::Zero;		// ���W
	Math::Vector3 m_moveDir = Math::Vector3::Zero;	// �ړ��x�N�g��
	float m_moveSpd = 0;							// �ړ�speed
	Math::Vector3 m_targetDir = Math::Vector3::Zero;// �^�[�Q�b�g�̍��W

	float m_standCnt = 0;							// �e����������Ƃ��̑ҋ@����
	float m_actionCnt = 1;							// �e���������s���Ă���Ƃ��̎���
	bool m_actionEndFlg = false;					// �������I����Ă��ăX�e�[�g��ς��Ă�������������t���O
};