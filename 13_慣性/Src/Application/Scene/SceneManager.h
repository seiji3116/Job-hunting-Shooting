#pragma once
class BaseScene;

class SceneManager
{
public:
	//�V�[�����
	enum class SceneType
	{
		Title,
		Game,
	};

	void PreUpdate();
	void Update();
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	//�}�l�[�W���̏������֐�
	void Init() { ChangeScene(SceneType::Title); }

	//void Release();

	//���̊֐��ł̓V�[���͕ς��Ȃ�
	//�����܂ŗ\��
	void SetNextScene(SceneType _nextScene) { m_nextSceneType = _nextScene; }

	const std::list<std::shared_ptr<KdGameObject>> GetObjList();

	void AddObject(const std::shared_ptr<KdGameObject>& _obj);
private:

	void ChangeScene(SceneType _sceneType);

	//���݂̃V�[�����Ǘ����Ă���|�C���^
	std::shared_ptr<BaseScene> m_currentScene = nullptr;
	//BaseScene *m_currentScene = nullptr;

	//���݂̃V�[�����Ǘ����Ă���f�[�^�i�ϐ��j
	SceneType m_currentSceneType = SceneType::Title;
	//���̃V�[�����Ǘ����Ă���f�[�^�i�ϐ��j
	SceneType m_nextSceneType = m_currentSceneType;

	//�V���O���g���p�^�[��
	//��������C���X�^���X�̐����P�ɐ�������
	//�֗��߂���
	//���p���Ȃ��I
private:
	SceneManager() { Init(); }
	~SceneManager(){}

public:
	static SceneManager& Instance()
	{
		static SceneManager instance;
		return instance;
	}
};