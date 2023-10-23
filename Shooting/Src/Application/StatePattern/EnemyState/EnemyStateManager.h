#pragma once

class EnemyBaseState;

class EnemyStateManager
{
public:
	// �X�e�[�g�̏����l�ݒ�
	EnemyStateManager(){}

public:
	// ��ȏ���
	void Init();
	void Update();
	void Action();
	std::shared_ptr<KdModelWork> GetModel();

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