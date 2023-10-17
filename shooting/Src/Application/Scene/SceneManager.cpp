#include "SceneManager.h"
#include "Application/Scene/BaseScene/BaseScene.h"
#include "Application/Scene/GameScene/GameScene.h"
#include "Application/Scene/TitleScene/TitleScene.h"
#include "Application/Scene/ResultScene/ResultScene.h"

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

void SceneManager::PreUpdate()
{
	// シーン切り替え
	if (m_currentSceneType != m_nextSceneType)
	{
		ChengeScene(m_nextSceneType);
	}

	// 現在のシーンの処理
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

void SceneManager::DrawDebug()
{
	m_currentScene->DrawDebug();
}

const std::list<std::shared_ptr<KdGameObject>>& SceneManager::GetObjList()
{
	return m_currentScene->GetObjList();
}

void SceneManager::AddObject(const std::shared_ptr<KdGameObject>& _obj)
{
	m_currentScene->AddObject(_obj);
}

void SceneManager::ChengeScene(SceneType _sceneType)
{
	// 現在のシーンを削除
	m_currentScene.reset();
	m_currentSceneType = m_nextSceneType;

	KdAudioManager::Instance().StopAllSound();

	// 次のシーンを作成し、現在のシーンにする
	switch (_sceneType)
	{
	case SceneManager::SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;

	case SceneManager::SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;

	case SceneManager::SceneType::Result:
		m_currentScene = std::make_shared<ResultScene>();
		break;

	default:
		break;
	}

	m_currentSceneType = _sceneType;
}
