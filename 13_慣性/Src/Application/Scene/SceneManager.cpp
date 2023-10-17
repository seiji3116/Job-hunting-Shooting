#include "SceneManager.h"
#include "BaseScene/BaseScene.h"
#include"GameScene//GameScene.h"
#include"TitleScene/TitleScene.h"

void SceneManager::PreUpdate()
{
	//�V�[���؂�ւ�
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}


	//���݂̃V�[���̏���
	m_currentScene->PreUpdate();
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::PostUpdate()
{
	m_currentScene->PostUpdate();
}

void SceneManager::PreDraw()
{
	m_currentScene->PreDraw();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::DrawSprite()
{
	m_currentScene->DrawSprite();
}

void SceneManager::DrawDebug()
{
	m_currentScene->DrawDebug();
}

const std::list<std::shared_ptr<KdGameObject>> SceneManager::GetObjList()
{
	//return std::list<std::shared_ptr<KdGameObject>>();
	return m_currentScene->GetObjList();
}

void SceneManager::AddObject(const std::shared_ptr<KdGameObject>& _obj)
{
	m_currentScene->AddObject(_obj);
}

void SceneManager::ChangeScene(SceneType _sceneType)
{

	//KdSafeDelete(m_currentScene);

	//���̃V�[�����쐬���A���݂̃V�[���ɂ���
	switch (_sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::Game:

		m_currentScene = std::make_shared<GameScene>();
		break;
	}
	m_currentSceneType = _sceneType;
}
