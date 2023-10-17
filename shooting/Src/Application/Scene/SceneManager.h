#pragma once

class BaseScene;

class SceneManager
{
public:
	// �V�[�����
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

	// �}�l�[�W���̏������֐�
	void Init()
	{
		ChengeScene(SceneType::Title);
	}

	// ���̊֐��ł̓V�[���͐؂�ւ��Ȃ�
	// �����܂ŗ\��
	void SetNextScene(SceneType _nextScene)
	{
		m_nextSceneType = _nextScene;
	}

	const std::list<std::shared_ptr<KdGameObject>>& GetObjList();
	void AddObject(const std::shared_ptr<KdGameObject>& _obj);

private:
	void ChengeScene(SceneType _sceneType);

	// ���݂̃V�[�����Ǘ����Ă���|�C���^
	std::shared_ptr<BaseScene> m_currentScene = nullptr;
	// ���݂̃V�[�����Ǘ����Ă���f�[�^�i�ϐ��j
	SceneType m_currentSceneType = SceneType::Title;

	// ���̃V�[�����Ǘ����Ă���f�[�^�i�ϐ��j
	SceneType m_nextSceneType = m_currentSceneType;

	// �V���O���g���p�^�[��
	// ��������C���X�^���X�́u�����P�ɐ�������
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