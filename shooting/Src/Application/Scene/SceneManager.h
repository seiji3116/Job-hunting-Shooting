#pragma once

class BaseScene;

class SceneManager
{
public:
	// シーン情報
	enum class SceneType
	{
		Title,
		Game,
		Result,
	};

	void PreDraw();
	void Draw();
	void DrawSprite();

	void PreUpdate();
	void Update();
	void PostUpdate();

	void DrawDebug();

	// マネージャの初期化関数
	void Init()
	{
		ChengeScene(SceneType::Title);
	}

	// この関数ではシーンは切り替わらない
	// あくまで予約
	void SetNextScene(SceneType _nextScene)
	{
		m_nextSceneType = _nextScene;
	}

	const std::list<std::shared_ptr<KdGameObject>>& GetObjList();
	void AddObject(const std::shared_ptr<KdGameObject>& _obj);

private:
	void ChengeScene(SceneType _sceneType);

	// 現在のシーンを管理しているポインタ
	std::shared_ptr<BaseScene> m_currentScene = nullptr;
	// 現在のシーンを管理しているデータ（変数）
	SceneType m_currentSceneType = SceneType::Title;

	// 次のシーンを管理しているデータ（変数）
	SceneType m_nextSceneType = m_currentSceneType;

	// シングルトンパターン
	// 生成するインスタンスの「数を１つに制限する
private:
	SceneManager() { Init(); }
	~SceneManager() {}

public:
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
};