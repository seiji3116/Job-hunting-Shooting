#pragma once

class BaseState
{
public:
	// ��{�֐�
	virtual void Init(KdGameObject& _owner) = 0;
	virtual void Update(KdGameObject& _owner) = 0;
	virtual void Shot(KdGameObject& _owner) = 0;		// �e�̔���
	virtual void Action(KdGameObject& _owner) = 0;		// �����̑�{

public:
	// �Q�b�^�[
	Math::Vector3 GetMoveDir() const { return m_moveDir; }				// �ړ��x�N�g���擾
	float GetActionCnt() const { return m_actionCnt; }					// ���݂�Action���s���Ԃ̎擾
	bool GetActionEndFlg() const { return m_actionEndFlg; }				// ���݂�Actiong���I����Ă��邩�ǂ���

public:
	// �Z�b�^�[
	void SetMoveDir(const Math::Vector3& _moveDir) { m_moveDir = _moveDir; }
	void SetMatrix(const Math::Matrix& _matrix) { m_mWorld = _matrix; }
	void SetPos(const Math::Vector3& _pos) { m_mWorld.Translation(_pos); }

protected:
	virtual void Rotate(Math::Vector3 _targetDir) = 0;	// ��]����

protected:
	std::shared_ptr<KdModelWork> m_model = nullptr;	// ���f���f�[�^

	Math::Matrix m_mWorld;							// ���[���h�s��

	Math::Vector3 m_moveDir = Math::Vector3::Zero;	// �ړ��x�N�g��
	float m_moveSpd = 0;							// �ړ�speed

	float m_standCnt = 0;							// �e����������Ƃ��̑ҋ@����
	float m_actionCnt = 1;							// �e���������s���Ă���Ƃ��̎���
	bool m_actionEndFlg = false;					// �������I����Ă��ăX�e�[�g��ς��Ă�������������t���O
};