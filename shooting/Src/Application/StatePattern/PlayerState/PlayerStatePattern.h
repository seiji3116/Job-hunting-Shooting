#pragma once

class PlayerState;

class PlayerStatePattern
{
public:
	// �X�e�[�g�̏����l�ݒ�
	PlayerStatePattern() {}

public:
	// ��v�ȏ���
	void Update(Math::Vector3 _pos = Math::Vector3::Zero, Math::Vector3 _dir = Math::Vector3::Zero);
	Math::Vector3 GetPos() const;
	Math::Vector3 GetDir() const;
	std::shared_ptr<KdAnimator> GetAnime() const;
	float GetAnimeSpeed() const;
	float GetHitDamage() const;
	
	// �X�e�[�g�̐؂�ւ�
	void ChengeAttack(Math::Vector3 _pos, Math::Vector3 _moveDir);		// �U��
	void ChengeAvoidance(Math::Vector3 _pos, Math::Vector3 _moveDir);	// ���
	void ChengeDamage(Math::Vector3 _pos, Math::Vector3 _moveDir);		// �_���[�W
	void ChengeJump(Math::Vector3 _pos, Math::Vector3 _moveDir);		// �W�����v
	void ChengeLose(Math::Vector3 _pos, Math::Vector3 _moveDir);		// �s�k
	void ChengeIdle(Math::Vector3 _pos, Math::Vector3 _moveDir);		// �ҋ@
	void ChengeRun(Math::Vector3 _pos, Math::Vector3 _moveDir);			// ����

private:
	// �����Ő؂�ւ����s��
	// ���݂̃X�e�[�g���폜���A���̃X�e�[�g�Ɉڍs����
	void ChengeState(std::shared_ptr<PlayerState> state, Math::Vector3 _pos, Math::Vector3 _moveDir);

private:
	// ���݂̃X�e�[�g
	std::shared_ptr<PlayerState> m_state;
};