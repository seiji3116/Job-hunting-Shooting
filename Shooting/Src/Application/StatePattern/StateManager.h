#pragma once

class BaseState;

class StateManager
{
public:
	// �X�e�[�g�̏����l�ݒ�
	StateManager(){}

public:
	// Base�̊֐��Ăяo���p
	void Update(KdGameObject& _owner);

	Math::Vector3 GetMoveDir() const;
	float GetActionCnt() const;
	bool GetActionEndFlg() const;

	void SetMoveDir(const Math::Vector3& _moveDir);
	void SetMatrix(const Math::Matrix& _matrix);
	void SetPos(const Math::Vector3& _pos);

public:
	// �X�e�[�g�̐؂�ւ�
	void ChengeRush(KdGameObject& _owner);		// �ːi
	void ChengeLaser(KdGameObject& _owner);		// ���[�U�[�̔���
	void ChengeNormal(KdGameObject& _owner);	// �ʏ�e�𔭎˂ł�����
	void ChengeTracking(KdGameObject& _owner);	// �v���C���[�ւ̒ǔ����

private:
	// �����Ő؂�ւ����s��
	// ���݂̃X�e�[�g���폜���A���̃X�e�[�g�Ɉڍs����
	void ChengeState(std::shared_ptr<BaseState> state, KdGameObject& _owner);

private:
	// ���݂̃X�e�[�g
	std::shared_ptr<BaseState> m_nowState;
};