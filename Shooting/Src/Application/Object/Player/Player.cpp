#include "Player.h"
#include "../Camera/TPSCamera/TPSCamera.h"
#include "../Bullet/Bullet.h"
#include "../Rock/Rock.h"
#include "../../Scene/SceneManager.h"

void Player::Update()
{
	Action();
	GravityThrow();
	UpdateCollision();
}

void Player::PostUpdate()
{
	Math::Matrix rotMatZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_roll));
	Math::Matrix rotMatX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_pitch));

	Math::Matrix rotMat = rotMatX * rotMatZ;

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_moveVec);

	m_mWorld = rotMat * transMat * m_mWorld;
	m_moveDir = m_mWorld.Backward();
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Player::DrawBright()
{
	//KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Player::Init()
{
	// 座標移動系初期化
	m_moveVec = Math::Vector3(0, 0, 0.1f);							// 移動量
	m_moveDir = Math::Vector3::Zero;

	// マトリックスの初期化
	Math::Matrix transMat = Math::Matrix::CreateTranslation({ 0,5,0 });
	m_mWorld = transMat;

	// フラグ関係初期化
	m_keyFlg = false;
	m_gravityKeyFlg = false;
	m_gravityFlg = false;
	m_throwKeyFlg = false;

	// モデルの読込
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Player/Player2.gltf"));

	//当たり判定初期化
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("PlayerModel", m_model, KdCollider::TypeDamage);

	//m_pCollider->RegisterCollisionShape("GravityArea", m_mWorld.Translation(), 10, KdCollider::TypeEvent);
}

void Player::Action()
{
	// ローカル軸管理
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_roll += 0.1f;
		if (m_roll > 2)
		{
			m_roll = 2;
		}
	}
	if (m_roll > 0)
	{
		m_roll -= 0.05f;
		if (m_roll < 0)
		{
			m_roll = 0;
		}
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_roll -= 0.1f;
		if (m_roll < -2)
		{
			m_roll = -2;
		}
	}
	if (m_roll < 0)
	{
		m_roll += 0.05f;
		if (m_roll > 0)
		{
			m_roll = 0;
		}
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_pitch -= 0.1f;
		if (m_pitch < -2)
		{
			m_pitch = -2;
		}
	}
	if (m_pitch < 0)
	{
		m_pitch += 0.05f;
		if (m_pitch > 0)
		{
			m_pitch = 0;
		}
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_pitch += 0.1f;
		if (m_pitch > 2)
		{
			m_pitch = 2;
		}
	}
	if (m_pitch > 0)
	{
		m_pitch -= 0.05f;
		if (m_pitch < 0)
		{
			m_pitch = 0;
		}
	}

	// Missile発射
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_keyFlg)
		{
			m_keyFlg = true;
			std::shared_ptr<Bullet> bullet;
			bullet = std::make_shared<Bullet>();
			bullet->SetPos(m_mWorld.Translation());
			bullet->SetMoveDir(m_moveDir);
			SceneManager::Instance().AddObject(bullet);
		}
	}
	else if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
	{
		if (!m_keyFlg)
		{
			m_keyFlg = true;
			m_mWorld.Translation(m_mWorld.Translation() + m_moveDir * 20.f);
		}
	}
	else
	{
		m_keyFlg = false;
	}
}

void Player::UpdateCollision()
{
	RockSphereCollision(m_mWorld.Translation(), 5, KdCollider::TypeEvent);
}

bool Player::RockSphereCollision(Math::Vector3 _pos, float _radius, KdCollider::Type _type)
{
	//========================================================
	//球判定
	//========================================================
	// 球判定用の変数
	KdCollider::SphereInfo sphereInfo;

	// 球の中心位置を設定
	sphereInfo.m_sphere.Center = _pos;

	// 球の半径を設定
	sphereInfo.m_sphere.Radius = _radius;

	// 当たり判定をしたいタイプを設定
	sphereInfo.m_type = _type;

	// デバッグ用
	//m_pDebugWire->AddDebugSphere(sphereInfo.m_sphere.Center, sphereInfo.m_sphere.Radius);

	// 当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retSphereList;

	// 球と当たり判定をする
	// マップとの当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects
		(
			sphereInfo,
			&retSphereList
		);
	}

	// 当たったリスト情報から1番近いオブジェクトを検出
	float maxOverLap = 0;
	bool sphereHitFlg = false;
	Math::Vector3 sphereHitDir = Math::Vector3::Zero; // 当たった方向
	for (auto& ret : retSphereList)
	{
		// １番近くで当たったものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			sphereHitFlg = true;
			sphereHitDir = ret.m_hitDir;
			sphereHitDir.Normalize();
		}
	}
	if (sphereHitFlg)
	{
		// 球とモデルが当たっている
		return true;
	}
	// 弾と当たっていなかったらfalseで帰る
	return false;
}

void Player::GravityThrow()
{
	// 岩などの引き寄せ
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_gravityKeyFlg && !m_gravityFlg && m_gravityList.size() == 0)
		{
			m_gravityKeyFlg = true;
			m_gravityFlg = true;
		}
	}
	else
	{
		m_gravityKeyFlg = false;
	}

	if (m_gravityList.size() >= 3)
	{
		m_gravityFlg = false;
	}

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (!m_gravityKeyFlg && !m_throwKeyFlg)
		{
			m_throwKeyFlg = true;

			if (m_gravityList.size() <= 0)
			{
				return;
			}
			auto& it = m_gravityList.begin();
			(*m_gravityList.begin())->ChengeThrow(m_mWorld.Backward());
			m_gravityList.erase(it);
		}
	}
	else
	{
		m_throwKeyFlg = false;
	}
}
