#pragma once

class Bullet : public KdGameObject
{
public:

	Bullet() { Init(); };
	~Bullet() {};

	// �`��֐�
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void DrawBright()override;
	
	// �������֐�
	void Init()override;

	// �X�V�֐�
	void Update()override;
	void PostUpdate()override;

	// �Z�b�^�[
	void SetPos(Math::Vector3 _pos)
	{
		m_pos = _pos;
	}
	void SetMoveDir(Math::Vector3 _dir)
	{
		m_moveDir = _dir;
		m_moveDir.Normalize();
	}

private:
	void UpdateRotate();

private:
	std::shared_ptr<KdModelWork> m_model;

	// �}�g���b�N�X
	Math::Matrix m_transMat;
	Math::Matrix m_rotateMat;

	// ���W�ړ��n
	Math::Vector3 m_pos;
	Math::Vector3 m_moveDir;
	float m_moveSpd;
};