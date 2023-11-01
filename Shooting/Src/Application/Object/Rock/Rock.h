#pragma once

class Player;

class Rock : public KdGameObject
{
public:

	Rock() { Init(); };
	~Rock() {};

	void GenerateDepthMapFromLight()override;
	void DrawLit()override;
	void DrawBright()override;
	void Init()override;

	void Update()override;

	void SetPlayer(std::shared_ptr<Player> _player)
	{
		m_wpPlayer = _player;
	}
	void ChengeThrow(Math::Vector3 _targetVec)
	{
		m_targetVec = _targetVec;
		m_gravityFlg = false;
		m_throwFlg = true;
	}
private:
	void Throw();
	void Gravity();
	void Rotate(Math::Vector3 _targetDir);

private:

	std::shared_ptr<KdModelWork> m_model;

	std::weak_ptr<Player> m_wpPlayer;

	Math::Vector3 m_scale;
	Math::Matrix m_transMat;
	Math::Matrix m_rotateMat;
	Math::Matrix m_scaleMat;
	float m_angle;

	// �v���C���[�Ɉ����񂹂���Ƃ�
	Math::Vector3 m_playerVec;		// �v���C���[�ւ̃x�N�g��
	Math::Vector3 m_targetVec;		// �^�[�Q�b�g�̕���
	Math::Vector3 m_targetPos;		// �^�[�Q�b�g�̍��W
	Math::Vector3 m_localPos;		// �^�[�Q�b�g����ǂ̂��炢����Ă��邩
	bool m_gravityFlg;				// �������񂹂��Ă��邩
	float m_gravityPow;				// �����񂹂���speed

	// �v���C���[���瓊�����鎞
	bool m_throwFlg;
};