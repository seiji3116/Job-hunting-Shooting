#include "Enemy.h"
#include "../Player/Player.h"

void Enemy::Update()
{
	std::shared_ptr<Player> spPlayer = m_wpPlayer.lock();
	if (spPlayer)
	{
		Math::Vector3 targetDir = spPlayer->GetPos() - m_mWorld.Translation();

		if (m_stateMan->GetActionEndFlg())
		{
			if (targetDir.Length() > 2)
			{
				m_stateMan->ChengeTracking();
				m_model = m_stateMan->GetModel();
			}
			else
			{
				m_stateMan->ChengeRush();
				m_model = m_stateMan->GetModel();
				m_stateMan->SetMoveDir(targetDir);
				m_stateMan->SetTargetDir(targetDir);
				m_stateMan->SetMatrix(m_mWorld);
			}
		}
		m_stateMan->SetTargetDir(targetDir);
	}

	m_stateMan->SetMatrix(m_mWorld);
	m_stateMan->Update();
	m_mWorld = m_stateMan->GetMatrix();
}

void Enemy::PostUpdate()
{
	//Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	//m_mWorld = m_rotateMat * transMat;
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

	// 初期ステートセット
	m_stateMan = std::make_unique<EnemyStateManager>();
	m_stateMan->ChengeTracking();
	m_nowState = State::Tracking;
	m_model = m_stateMan->GetModel();

	m_moveDir = Math::Vector3(0, 0, 1);

	// デバッグワイヤーセット
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//当たり判定初期化
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyModel", m_mWorld.Translation(), 6.5f, KdCollider::TypeDamage);
}