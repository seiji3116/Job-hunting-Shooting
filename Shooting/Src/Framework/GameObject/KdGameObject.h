#pragma once

class KdDebugWireFrame;
class CameraBase;

// ゲーム上に存在するすべてのオブジェクトの基底となるクラス
class KdGameObject : public std::enable_shared_from_this<KdGameObject>
{
public:

	// どのような描画を行うのかを設定するTypeID：Bitフラグで複数指定可能
	enum
	{
		eDrawTypeLit = 1 << 0,
		eDrawTypeUnLit = 1 << 1,
		eDrawTypeBright = 1 << 2,
		eDrawTypeUI = 1 << 3,
		eDrawTypeDepthOfShadow = 1 << 4,
	};

	KdGameObject() {}
	virtual ~KdGameObject() { Release(); }

	// 生成される全てに共通するパラメータに対する初期化のみ
	virtual void Init() {}

	virtual void PreUpdate() {}
	virtual void Update() {}
	virtual void PostUpdate() {}

	// それぞれの状況で描画する関数
	virtual void PreDraw();
	virtual void GenerateDepthMapFromLight() {}
	virtual void DrawLit() {}
	virtual void DrawUnLit() {}
	virtual void DrawBright() {}
	virtual void DrawSprite() {}
	virtual void DrawDebug();

	virtual void SetAsset(const std::string&) {}

	virtual void SetPos(const Math::Vector3& pos) { m_mWorld.Translation(pos); }
	virtual Math::Vector3 GetPos() const { return m_mWorld.Translation(); }

	// 拡大率を変更する関数
	void SetScale(float scalar);
	virtual void SetScale(const Math::Vector3& scale);
	virtual Math::Vector3 GetScale() const;

	const Math::Matrix& GetMatrix() const { return m_mWorld; }
	void SetMatrix(const Math::Matrix& _mWorld) { m_mWorld = _mWorld; }

	// add: 
	const std::weak_ptr<CameraBase>& GetCamera() const { return m_camera; }

	// add: モデルをセットする関数
	void SetModel(const std::shared_ptr<KdModelWork>& _model) 
	{
		m_model = std::make_shared<KdModelWork>();
		m_model = _model;
	}

	// add:
	virtual Math::Vector3 GetTargetDir() const { return m_targetDir; }
	virtual Math::Vector3 GetTargetPos() const { return m_targetPos; };

	void SetCamera(const std::shared_ptr<CameraBase> _camera)
	{
		m_camera = _camera;
	}

	virtual bool IsExpired() const { return m_isExpired; }

	virtual bool IsVisible() const { return false; }

	// 視錐台範囲内に入っているかどうか
	virtual bool CheckInScreen(const DirectX::BoundingFrustum&) const { return false; }

	// カメラからの距離を計算
	virtual void CalcDistSqrFromCamera(const Math::Vector3& camPos);

	float GetDistSqrFromCamera() const { return m_distSqrFromCamera; }

	UINT GetDrawType() const { return m_drawType; }

	bool Intersects(const KdCollider::SphereInfo& targetShape, std::list<KdCollider::CollisionResult>* pResults);
	bool Intersects(const KdCollider::RayInfo& targetShape, std::list<KdCollider::CollisionResult>* pResults);

protected:

	void Release() {}

	// 描画タイプ・何の描画を行うのかを決める / 最適な描画リスト作成用
	UINT m_drawType = 0;

	// カメラからの距離
	float m_distSqrFromCamera = 0;

	// 存在消滅フラグ
	bool m_isExpired = false;

	// 3D空間に存在する機能
	Math::Matrix	m_mWorld;

	// add: 
	Math::Vector3	m_targetDir;
	Math::Vector3	m_targetPos;

	std::weak_ptr<CameraBase> m_camera;		// カメラ情報

	// モデル用
	std::shared_ptr<KdModelWork> m_model;

	// 当たり判定クラス
	std::unique_ptr<KdCollider> m_pCollider = nullptr;

	//デバッグ用
	std::unique_ptr<KdDebugWireFrame> m_pDebugWire = nullptr;
};