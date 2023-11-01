#pragma once

class EnemyBaseState;

class EnemyStateManager
{
public:
	// �X�e�[�g�̏����l�ݒ�
	EnemyStateManager(){}

public:
	// Base�̊֐��Ăяo���p
	void Update();
	void PostUpdate();
	void Action();
	std::shared_ptr<KdModelWork> GetModel() const;
	Math::Vector3 GetPos() const;
	Math::Vector3 GetMoveDir() const;
	Math::Matrix GetMatrix() const;
	float GetActionCnt() const;
	bool GetActionEndFlg() const;
	void SetTargetDir(const Math::Vector3& _dir);
	void SetMoveDir(const Math::Vector3& _moveDir);
	void SetMatrix(const Math::Matrix& _matrix);

public:
	// �X�e�[�g�̐؂�ւ�
	void ChengeRush();		// �ːi
	void ChengeLaser();		// ���[�U�[�̔���
	void ChengeNormal();	// �ʏ�e�𔭎˂ł�����
	void ChengeTracking();	// �v���C���[�ւ̒ǔ����

private:
	// �����Ő؂�ւ����s��
	// ���݂̃X�e�[�g���폜���A���̃X�e�[�g�Ɉڍs����
	void ChengeState(std::shared_ptr<EnemyBaseState> state);

private:
	// ���݂̃X�e�[�g
	std::shared_ptr<EnemyBaseState> m_nowState;
};