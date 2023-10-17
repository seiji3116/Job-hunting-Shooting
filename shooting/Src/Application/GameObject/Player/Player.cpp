#include "Player.h"
#include "Application/Scene/SceneManager.h"
#include "Application/GameObject/Camera/CameraBase.h"
#include "Application/GameObject/Enemy/Enemy.h"

void Player::Update()
{
	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3(0, 0.7f, 0), 0.5f, { 1, 0, 0 });

	// 攻撃用ノードの読込
	m_attackNodePos[0] = LoadNodePos("J_Bip_L_Hand") + m_pos;
	m_attackNodePos[1] = LoadNodePos("J_Bip_R_Hand") + m_pos;
	m_attackNodePos[2] = LoadNodePos("J_Bip_L_ToeBase_end") + m_pos;
	m_attackNodePos[3] = LoadNodePos("J_Bip_R_ToeBase_end") + m_pos;

	m_state.Update(m_pos, m_moveDir);
	m_pos = m_state.GetPos();
	m_moveDir = m_state.GetDir();

	if (m_aliveFlg)
	{
		if (m_nowMoveState & MoveState::Run)
		{
			// 回転処理
			UpdateRotate();
		}

		// キャラ操作関連
		Action();
	}

	// 当たり判定
	Collider();

	// キャラアニメーション
	Animation();
}

void Player::PostUpdate()
{
	// マトリックスの合成
	m_transMat = Math::Matrix::CreateTranslation(m_pos);
	m_rotateMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	m_mWorld = m_rotateMat * m_transMat;
}

void Player::PreDraw()
{

}

void Player::GenerateDepthMapFromLight_SkinMesh()
{
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
}

void Player::DrawUnlitWithTransparency_SkinMesh()
{
	KdShaderManager::Instance().ChangeRasterizerState(KdRasterizerState::CullNone);	// ここだけカリングを切る
	KdShaderManager::Instance().m_HD2DShader.DrawModel(*m_model, m_mWorld);
	KdShaderManager::Instance().UndoRasterizerState();								// カリングの設定を戻す
}

void Player::DrawDebug()
{
	m_pDebugWire->Draw();
}

void Player::Init()
{
	srand(timeGetTime());

	// モデル(キャラ)
	m_model = std::make_shared<KdModelWork>();
	m_model->SetModelData(KdAssets::Instance().m_modeldatas.GetData("Asset/Models/Player/Player.Test.gltf"));

	m_mWorld = Math::Matrix::Identity;			// ワールドマトリックス
	m_moveVec = Math::Vector3::Zero;			// プレイヤーの現在の移動量
	m_moveDir = Math::Vector3{ -1.f, 0, 0 };	// プレイヤーの現在の角度
	m_angle = 0;								// プレイヤーの今の回転角度(Y軸)

	// 初回ステートセット
	m_nowMoveState = MoveState::Idle;
	m_state.ChengeIdle(m_pos, m_moveDir);
	m_animator = std::make_shared<KdAnimator>();
	m_animator = m_state.GetAnime();
	m_animeSpd = m_state.GetAnimeSpeed();
	m_chengeFlg = true;
	m_aliveFlg = true;


	// 重力関係
	m_keyFlg = false;
	m_gravityPow = 0;

	// 攻撃用ノードの読込
	m_attackNodePos[0] = LoadNodePos("J_Bip_L_Hand") + m_pos;
	m_attackNodePos[1] = LoadNodePos("J_Bip_R_Hand") + m_pos;
	m_attackNodePos[2] = LoadNodePos("J_Bip_L_ToeBase_end") + m_pos;
	m_attackNodePos[3] = LoadNodePos("J_Bip_R_ToeBase_end") + m_pos;

	// ステータスの設定
	m_hitPt = 10000.f;

	// デバッグ
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	// 当たり判定初期化
	m_collisionFlg = true;
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("PlayerBody", m_pos + Math::Vector3(0, 0.7f, 0), 0.5f, KdCollider::TypeDamage);
}

void Player::SetEnemy(std::shared_ptr<Enemy> _enemy)
{
	m_enemy = std::make_shared<Enemy>();
	m_enemy = _enemy;
}

void Player::Hit(float _damage)
{
	if (m_aliveFlg)
	{
		if (m_hitPt <= _damage)
		{
			m_nowMoveState = MoveState::Lose;
			m_state.ChengeLose(m_pos, m_moveDir);
			m_animator = std::make_shared<KdAnimator>();
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			m_chengeFlg = false;
			m_aliveFlg = false;
			m_hitPt = 0;
		}
		else
		{
			m_hitPt -= _damage;
			m_nowMoveState = MoveState::Damage;
			m_state.ChengeDamage(m_pos, m_moveDir);
			m_animator = std::make_shared<KdAnimator>();
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			m_chengeFlg = false;
		}
	}
}

void Player::UpdateRotate()
{
	// 移動中
	m_moveVec.Normalize();

	// キャラの向きを変える
	// 今キャラが向いている方向
	// キャラの回転行列を作成
	Math::Matrix nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	// 現在の方向を変形させる
	Math::Vector3 nowVec = Math::Vector3::TransformNormal(Math::Vector3(0, 0, 1), nowRotMat);

	// 向きたい方向
	Math::Vector3 toVec = -m_moveVec;

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

void Player::Action()
{
	//CheckAndAdjustPlayerStatus();
	if (m_enemy == nullptr)
	{
		if (m_nowMoveState != MoveState::Idle)
		{
			m_state.ChengeIdle(m_pos, m_moveDir);
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			ChengeState(MoveState::Idle);
		}
		return;
	}

	// 進行方向を求めるためにカメラの行列を取得
	std::shared_ptr<CameraBase> spCamera = m_wpCamera.lock();
	if (!spCamera)
	{
		return;
	}

	// カメラの水平回転をしただけの行列取得
	const auto& mCam = spCamera->GetRotaionYMatrix();

	// キャラ操作
	// カメラの方向に動く
	if (m_moveVec != Math::Vector3::Zero)
	{
		m_moveDir = m_moveVec;
		m_moveDir.Normalize();
	}
	m_moveVec = Math::Vector3::Zero;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000)
	{
		m_moveVec += mCam.Right();
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000)
	{
		m_moveVec += mCam.Left();
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000)
	{
		m_moveVec += mCam.Backward();
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000)
	{
		m_moveVec += mCam.Forward();
	}

	m_moveVec.Normalize();

	// 移行フラグがtrueのときだけ移行処理
	if (m_chengeFlg)
	{
		// 移動量がある場合は走り状態へ移行
		if (m_moveVec != Math::Vector3::Zero && m_nowMoveState != MoveState::Run)
		{
			m_state.ChengeRun(m_pos, m_moveVec);
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			ChengeState(MoveState::Run);
		}

		// ジャンプ
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_gravityPow = 0.25f;
			m_state.ChengeJump(m_pos, m_moveDir);
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			ChengeState(MoveState::Jump);
		}

		// 回避
		if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
		{
			m_state.ChengeAvoidance(m_pos, m_moveDir);
			m_animator = m_state.GetAnime();
			m_animeSpd = m_state.GetAnimeSpeed();
			ChengeState(MoveState::Avoidance);
		}

		// 攻撃
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			m_collisionFlg = true;
			if (m_nowMoveState != MoveState::Attack)
			{
				m_state.ChengeAttack(m_pos, m_moveDir);
				m_animator = m_state.GetAnime();
				m_animeSpd = m_state.GetAnimeSpeed();
				ChengeState(MoveState::Attack);
			}
		}
	}

	// 待機と走り状態以外はアニメーションが終わってから移行
	if (m_nowMoveState != MoveState::Idle && m_nowMoveState != MoveState::Run)
	{
		if (m_nowMoveState & MoveState::Damage)
		{
			if (m_animator->IsAnimationEnd())
			{
				m_chengeFlg = true;
			}
			else
			{
				m_chengeFlg = false;
			}
		}

		if (m_animator->IsAnimationEnd())
		{
			m_chengeFlg = true;
		}
		else
		{
			m_chengeFlg = false;
		}
	}
	else
	{
		m_chengeFlg = true;
	}

	m_gravityPow += -0.007f;
	m_pos.y += m_gravityPow;
}

void Player::Collider()
{
	if (RayCollider(m_pos + Math::Vector3(0, 0.5f, 0), m_moveDir, 3.f, KdCollider::TypeGround))
	{
		/*m_pos = m_moveDir * m_maxOverLap;*/
		/*m_pos = m_rayHitPos - m_moveDir * -4.f;*/
	}

	if (SphereCollider(m_pos + Math::Vector3(0, 0.5f, 0), 0.7f, KdCollider::TypeGround))
	{
		m_gravityPow = 0;
		m_pos += m_sphereHitDir;
		if (m_aliveFlg)
		{
			// 移動量がなく待機状態では無かったら待機状態へ移行
			if (m_moveVec == Math::Vector3::Zero && m_nowMoveState != MoveState::Idle)
			{
				// 攻撃モーション中だったらアニメーションが終わってから待機に移行
				if (m_chengeFlg)
				{
					m_state.ChengeIdle(m_pos, m_moveDir);
					m_animator = m_state.GetAnime();
					m_animeSpd = m_state.GetAnimeSpeed();
					ChengeState(MoveState::Idle);
				}
			}
		}
	}

	if (m_nowMoveState & MoveState::Attack && m_collisionFlg)
	{
		m_collisionFlg = false;
		for (int i = 0; i < NODE_NUM; i++)
		{
			if (SphereCollider(m_attackNodePos[i], 0.1f, KdCollider::TypeBump))
			{
				m_enemy->Hit(m_state.GetHitDamage());
			}
		}
	}
}

bool Player::RayCollider(Math::Vector3 _pos, Math::Vector3 _rayDir, float _range, KdCollider::Type _type)
{
	//========================================================
	//レイ判定
	//========================================================
	// レイ判定用に変数を作成
	KdCollider::RayInfo rayInfo;

	// レイの発射座標を設定
	rayInfo.m_pos = _pos;

	// レイの方向を設定
	rayInfo.m_dir = _rayDir;

	// レイの長さを設定
	rayInfo.m_range = _range;

	// 当たり判定をしたいタイプを設定
	rayInfo.m_type = _type;

	// デバッグ用==========================================
	m_pDebugWire->AddDebugLine(rayInfo.m_pos, rayInfo.m_dir, rayInfo.m_range, { 0, 1, 0 });

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
	m_maxOverLap = 0;
	m_rayHitPos = Math::Vector3::Zero;
	bool hit = false;
	for (auto& ret : retRayList)
	{
		// レイを遮断しオーバー↓長さが
		// 1番長いものを探す
		if (m_maxOverLap < ret.m_overlapDistance)
		{
			m_maxOverLap = ret.m_overlapDistance;
			m_rayHitPos = ret.m_hitPos;
			hit = true;
		}
	}

	// 当たっていたら
	if (hit)
	{
		return true;
	}
	return false;
}

bool Player::SphereCollider(Math::Vector3 _pos, float _radius, KdCollider::Type _type)
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
	m_maxOverLap = 0;
	bool sphereHitFlg = false;
	m_sphereHitDir = Math::Vector3::Zero; // 当たった方向
	for (auto& ret : retSphereList)
	{
		// １番近くで当たったものを探す
		if (m_maxOverLap < ret.m_overlapDistance)
		{
			m_maxOverLap = ret.m_overlapDistance;
			sphereHitFlg = true;
			m_sphereHitDir = ret.m_hitDir;
			m_sphereHitDir.Normalize();
		}
	}
	if (sphereHitFlg)
	{
		// 球とモデルが当たっている
		m_sphereHitDir *= m_maxOverLap;
		return true;
	}
	return false;
}

void Player::Animation()
{
	if (!m_model)	return;
	if (!m_animator) return;

	// アニメーションの更新
	m_animator->AdvanceTime(m_model->WorkNodes(), m_animeSpd);
	m_model->CalcNodeMatrices();
}

void Player::ChengeState(MoveState _nextState)
{
	// 前と同じステータスの場合切り替えを行わない
	if (m_nowMoveState == _nextState) return;

	m_nowMoveState = _nextState;
}

Math::Vector3 Player::LoadNodePos(std::string_view _nodeName)
{
	const KdModelWork::Node* pNode = m_model->FindNode(_nodeName);

	if (pNode)
	{
		return pNode->m_worldTransform.Translation();
	}
	return Math::Vector3::Zero;
}
