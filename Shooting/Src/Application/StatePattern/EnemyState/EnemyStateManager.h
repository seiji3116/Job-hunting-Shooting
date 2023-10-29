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
	void SetTargetPos(const Math::Vector3& _pos);

public:
	// �X�e�[�g�̐؂�ւ�
	void ChengeRush();		// �ːi
	void ChengeLaser();		// ���[�U�[�̔���
	void ChengeNormal();	// �ʏ���

private:
	// �����Ő؂�ւ����s��
	// ���݂̃X�e�[�g���폜���A���̃X�e�[�g�Ɉڍs����
	void ChengeState(std::shared_ptr<EnemyBaseState> state);

private:
	// ���݂̃X�e�[�g
	std::shared_ptr<EnemyBaseState> m_nowState;
};