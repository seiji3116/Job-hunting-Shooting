#include "Enemy.h"
#include "../Player/Player.h"

void Enemy::Update()
{
	std::shared_ptr<Player> spPlayer = m_wpPlayer.lock();

	if (spPlayer)
	{
		m_targetDir = spPlayer->GetPos() - m_mWorld.Translation();
		m_targetPos = spPlayer->GetPos();
		m_stateMan->SetPos(m_mWorld.Translation());
		m_stateMan->Update(*this);

		//if (m_stateMan->GetActionEndFlg())
		//{
		//	if (targetDir.Length() > 2)
		//	{
		//		m_stateMan->ChengeTracking();
		//		m_model = m_stateMan->GetModel();
		//	}
		//	else
		//	{
		//		m_stateMan->ChengeRush();
		//		m_model = m_stateMan->GetModel();
		//		m_stateMan->SetMoveDir(targetDir);
		//		m_stateMan->SetTargetDir(targetDir);
		//		m_stateMan->SetMatrix(m_mWorld);
		//	}
		//}
		//m_stateMan->SetTargetDir(targetDir);
	}

	//m_stateMan->SetMatrix(m_mWorld);
	//m_stateMan->Update();
	//m_mWorld = m_stateMan->GetMatrix();


}

void Enemy::PostUpdate()
{
	//Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	//m_mWorld = m_rotateMat * transMat;
}

void Enemy::SetState(const std::string& _stateName)
{
	// ステートセット関数
	m_stateMan = std::make_unique<StateManager>();
	if (_stateName == "Normal")
	{
		m_stateMan->ChengeNormal(*this);
		m_nowState = State::Normal;
	}
	else if(_stateName == "Laser")
	{
		m_stateMan->ChengeLaser(*this);
		m_nowState = State::Laser;
	}
	else if (_stateName == "Rush")
	{
		m_stateMan->ChengeRush(*this);
		m_nowState = State::Rush;
	}
	else
	{
		return;
	}
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
	m_moveDir = Math::Vector3(0, 0, 1);

	m_model = std::make_shared<KdModelWork>();

	// デバッグワイヤーセット
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//当たり判定初期化
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyModel", m_mWorld.Translation(), 6.5f, KdCollider::TypeDamage);
}