#pragma once

class EnemyState;

class EnemyStatePattern
{
public:
	// �X�e�[�g�̏����l�ݒ�
	EnemyStatePattern() {}

public:
	// ��v�ȏ���
	void Update(Math::Vector3 _pos = Math::Vector3::Zero, Math::Vector3 _dir = Math::Vector3::Zero);
	Math::Vector3 GetPos() const;
	Math::Vector3 GetDir() const;
	std::shared_ptr<KdAnimator> GetAnime() const;
	float GetAnimeSpeed() const;
	bool GetCollisionFlg() const;
	bool GetStateChengeFlg() const;
	bool GetActionFlg() const;
	float GetHitDamege() const;
	void SetDir(Math::Vector3 _dir);

	// �X�e�[�g�̐؂�ւ�
	void ChengeRush(Math::Vector3 _pos, Math::Vector3 _moveDir);	// �ːi
	void ChengeWalk(Math::Vector3 _pos, Math::Vector3 _moveDir);	// ����
	void ChengeJump(Math::Vector3 _pos, Math::Vector3 _moveDir);	// �W�����v
	void ChengeIdle(Math::Vector3 _pos, Math::Vector3 _moveDir);	// �ҋ@

private:
	// �����Ő؂�ւ����s��
	// ���݂̃X�e�[�g���폜���A���̃X�e�[�g�Ɉڍs����
	void ChengeState(std::shared_ptr<EnemyState> state, Math::Vector3 _pos, Math::Vector3 _moveDir);

private:
	// ���݂̃X�e�[�g
	std::shared_ptr<EnemyState> m_state;
};