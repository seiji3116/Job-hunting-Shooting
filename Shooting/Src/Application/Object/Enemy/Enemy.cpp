#include "Enemy.h"
#include "../Player/Player.h"

void Enemy::Update()
{
	std::shared_ptr<Player> spPlayer = m_wpPlayer.lock();
	if (spPlayer)
	{
		m_stateMan->SetTargetPos(spPlayer->GetPos());
	}
	m_stateMan->Update();
	m_pos = m_stateMan->GetPos();
}

void Enemy::PostUpdate()
{
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Enemy::Init()
{
	m_model = std::make_shared<KdModelWork>();

	// �����X�e�[�g�Z�b�g
	m_stateMan = std::make_shared<EnemyStateManager>();
	m_stateMan->ChengeRush();
	m_model = m_stateMan->GetModel();

	// �f�o�b�O���C���[�Z�b�g
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//�����蔻�菉����
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyModel", m_mWorld.Translation(), 6.5f, KdCollider::TypeDamage);
}