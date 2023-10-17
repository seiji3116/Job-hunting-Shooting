#include "Enemy.h"
#include "Application/Scene/SceneManager.h"
#include "Application/GameObject/Player/Player.h"

void Enemy::Update()
{
	if (m_player == nullptr)
	{
		if (m_nowMoveState != MoveState::Idle)
		{
			m_moveDir.Normalize();
			m_nowMoveState = MoveState::Idle;
			m_state.ChengeIdle(m_pos, m_moveDir);
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			m_idleCnt = 120.f;
			m_collisionFlg = true;
		}
		// 当たり判定
		Collider();
		Animation();
		return;
	}


	// 当たり判定
	Collider();
	Animation();
	// 重力処理
	m_gravity += -0.007f;
	m_pos.y += m_gravity;

	// デバッグ用
	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3(0, 3, 0), 4.f, { 1, 0, 0 });

	// 当たり判定
	Collider();

	m_state.Update(m_pos, m_moveDir);
	m_pos = m_state.GetPos();

	// プレイヤーへのベクトル算出
	m_moveDir = m_player->GetPos() - m_pos;
	m_moveDir = Math::Vector3(m_moveDir.x, 0, m_moveDir.z);

	if (m_aliveFlg)
	{
		// 一定距離離れていたら歩きモーションへ移行
		if (m_state.GetStateChengeFlg())
		{
			if (m_moveDir.Length() >= 10)
			{
				if (m_nowMoveState != Walk)
				{
					m_nowMoveState = MoveState::Walk;
					m_moveDir.Normalize();
					m_state.ChengeWalk(m_pos, m_moveDir);
					m_animator = m_state.GetAnime();
					m_animeSpd = m_state.GetAnimeSpeed();
				}
			}
			else if (m_nowMoveState != MoveState::Idle)
			{
				m_moveDir.Normalize();
				m_nowMoveState = MoveState::Idle;
				m_state.ChengeIdle(m_pos, m_moveDir);
				m_animator = m_state.GetAnime();
				m_animeSpd = m_state.GetAnimeSpeed();
				m_idleCnt = 120.f;
				m_collisionFlg = true;
			}
		}

		m_idleCnt--;
		if (m_idleCnt <= 0 && m_nowMoveState & MoveState::Idle)
		{
			m_idleCnt = 0;
			m_moveDir.Normalize();
			switch (m_nextMoveState)
			{
			case MoveState::Jump:
				m_nextMoveState = MoveState::Rush;
				m_nowMoveState = MoveState::Jump;
				m_state.ChengeJump(m_pos, m_moveDir);
				m_animator = m_state.GetAnime();
				m_animeSpd = m_state.GetAnimeSpeed();
				break;
			case MoveState::Rush:
				m_nextMoveState = MoveState::Jump;
				m_nowMoveState = MoveState::Rush;
				m_state.ChengeRush(m_pos, m_moveDir);
				m_animator = m_state.GetAnime();
				m_animeSpd = m_state.GetAnimeSpeed();
				break;
			default:
				break;
			}
		}

		if (m_nowMoveState & MoveState::Jump)
		{
			if (m_state.GetActionFlg())
			{
				if (m_animator->AnimationTime() <= 0)
				{
					m_gravity = 0.3f;
				}
			}
		}

		// 回転処理
		UpdateRotate();

		if (m_nowMoveState & MoveState::Idle || m_nowMoveState & MoveState::Walk)
		{
			m_rotateFlg = true;
		}
	}
	else
	{

	}

	Animation();

	// 重力処理
	m_gravity += -0.007f;
	m_pos.y += m_gravity;
}

void Enemy::PostUpdate()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	m_mWorld = m_rotateMat * m_transMat;
}

void Enemy::GenerateDepthMapFromLight_SkinMesh()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Enemy::DrawLit_SkinMesh()
{
	if (m_aliveFlg)
	{
		KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
	}
}

void Enemy::Init()
{
	// モデル読込
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Enemy/Enemy.gltf"));

	// マトリックスの初期化
	m_mWorld = Math::Matrix::Identity;
	m_transMat = Math::Matrix::Identity;
	m_rotateMat = Math::Matrix::Identity;
	m_angle = 0;
	m_pos = Math::Vector3(0, 3, 3);
	m_rotateFlg = true;

	m_moveDir = Math::Vector3(0, 0, -1);
	m_moveDir.Normalize();

	// 初期ステート設定
	m_animator = std::make_shared<KdAnimator>();
	m_nowMoveState = MoveState::Idle;
	m_nextMoveState = MoveState::Rush;
	m_state.ChengeIdle(m_pos, m_moveDir);
	m_animator = m_state.GetAnime();
	m_animeSpd = m_state.GetAnimeSpeed();
	m_idleCnt = 120.f;
	m_aliveFlg = true;

	// 重力の設定
	m_gravity = 0;

	// 敵のステータスの設定
	m_hitPt = 1000.f;

	// デバッグ
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	// 当たり判定初期化
	m_collisionFlg = true;
	m_sphereMaxOverLap = 0;;
	m_sphereHitDir = Math::Vector3::Zero;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyBody", m_pos + Math::Vector3(0, 3, 0), 4.f, KdCollider::TypeBump);
}

void Enemy::DrawDebug()
{
	m_pDebugWire->Draw();
}

void Enemy::SetPlayer(std::shared_ptr<Player> _player)
{
	m_player = std::make_shared<Player>();
	m_player = _player;
}

void Enemy::Hit(float _damage)
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		_damage = 10000;
	}
	if (m_aliveFlg)
	{
		m_hitPt -= _damage;
	}

	if (m_hitPt <= _damage)
	{
		m_hitPt = 0;
		m_aliveFlg = false;
	}
}

void Enemy::Action()
{
}

void Enemy::Animation()
{
	if (!m_model)	return;
	if (!m_animator) return;

	// アニメーションの更新
	m_animator->AdvanceTime(m_model->WorkNodes(), m_animeSpd);
	m_model->CalcNodeMatrices();
}

void Enemy::UpdateRotate()
{
	// 移動中
	m_moveDir.Normalize();

	// キャラの向きを変える
	// 今キャラが向いている方向
	// キャラの回転行列を作成
	Math::Matrix nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	// 現在の方向を変形させる
	Math::Vector3 nowVec = Math::Vector3::TransformNormal(Math::Vector3(0, 0, 1), nowRotMat);

	// 向きたい方向
	Math::Vector3 toVec = -m_moveDir;

	float dot = nowVec.Dot(toVec);
	// 丸目誤差（小数点以下を省略した際に生じる誤差）
	if (dot > 1)
	{
		dot = 1;
	}
	if (dot < -1)
	{
		dot = -1;
	}

	float ang = DirectX::XMConvertToDegrees(acos(dot));

	if (ang <= 5)
	{
		m_rotateFlg = false;
	}

	if (m_rotateFlg)
	{
		// 少しでも角度が変わったら
		if (ang >= 0.1f)
		{
			if (ang > 10.f)
			{
				ang = 10.f;
			}

			// 外積（どっちに回転するのか調べる）
			// ベクトルAとベクトルBに垂直なベクトル
			Math::Vector3 cross = nowVec.Cross(toVec);
			if (cross.y >= 0)
			{
				m_angle += ang;
			}
			else
			{
				m_angle -= ang;
			}
		}
	}
}

void Enemy::Collider()
{
	//RayCollider();
	if (SphereCollider(m_pos + Math::Vector3(0, 3, 0), 3.5f, KdCollider::TypeGround))
	{
		m_pos += m_sphereHitDir * m_sphereMaxOverLap;
		m_gravity = 0;
	}

	// プレイヤーとの当たり判定
	if (m_state.GetCollisionFlg() && m_aliveFlg)
	{
		if (m_collisionFlg)
		{
			if (m_nowMoveState & MoveState::Jump)
			{
				if (SphereCollider(m_pos + Math::Vector3(0, 3, 0), 6.f, KdCollider::TypeDamage))
				{
					m_collisionFlg = false;
					m_player->Hit(m_state.GetHitDamege());
				}
			}
			if (m_nowMoveState & MoveState::Rush)
			{
				if (SphereCollider(m_pos + Math::Vector3(0, 3, 0), 3.5f, KdCollider::TypeDamage))
				{
					m_collisionFlg = false;
					m_player->Hit(m_state.GetHitDamege());
				}
			}
		}
	}

}

bool Enemy::RayCollider(Math::Vector3 _pos, Math::Vector3 _rayDir, float _range, KdCollider::Type _type)
{
	//========================================================
	//レイ判定
	//========================================================
	// レイ判定用に変数を作成

	KdCollider::RayInfo rayInfo;

	// レイの発射座標を設定
	rayInfo.m_pos = m_pos + Math::Vector3(0, 3, 0);

	rayInfo.m_dir = m_mWorld.Down();

	// レイの長さを設定
	rayInfo.m_range = 3.f;

	// 当たり判定をしたいタイプを設定
	rayInfo.m_type = KdCollider::TypeGround;

	// デバッグ用==========================================
	m_pDebugWire->AddDebugLine(rayInfo.m_pos, rayInfo.m_dir, rayInfo.m_range);

	// レイに当たったオブジェクト情報
	std::list<KdCollider::CollisionResult> retRayList;

	// レイと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects
		(
			rayInfo,
			&retRayList
		);
	}

	// レイに当たったリストから1番近いオブジェクトを検出
	float maxOverLap = 0;
	Math::Vector3 groundPos;
	bool hit = false;
	for (auto& ret : retRayList)
	{
		// レイを遮断しオーバー↓長さが
		// 1番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			groundPos = ret.m_hitPos;
			hit = true;
		}
	}

	// 当たっていたら
	if (hit)
	{
		m_pos += m_mWorld.Down() * maxOverLap;
		m_gravity = 0;
		return true;
	}
	else
	{
		return false;
	}
}

bool Enemy::SphereCollider(Math::Vector3 _pos, float _radius, KdCollider::Type _type)
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
	m_pDebugWire->AddDebugSphere(sphereInfo.m_sphere.Center, sphereInfo.m_sphere.Radius);

	// 弾の当たったオブジェクト情報を格納するリスト
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

	// 急に当たったリスト情報から1番近いオブジェクトを検出
	m_sphereMaxOverLap = 0;
	bool  m_sphereHitFlg = false;
	m_sphereHitDir = Math::Vector3::Zero; // 当たった方向
	for (auto& ret : retSphereList)
	{
		// １番近くで当たったものを探す
		if (m_sphereMaxOverLap < ret.m_overlapDistance)
		{
			m_sphereMaxOverLap = ret.m_overlapDistance;
			m_sphereHitFlg = true;
			m_sphereHitDir = ret.m_hitDir;
			m_sphereHitDir.Normalize();
		}
	}
	if (m_sphereHitFlg)
	{
		// 球とモデルが当たっている
		return true;
	}
	else
	{
		return false;
	}
}
