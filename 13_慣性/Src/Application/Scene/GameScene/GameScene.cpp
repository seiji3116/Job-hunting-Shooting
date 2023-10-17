#include "GameScene.h"
#include "../../Object/Ground/Ground.h"
#include "../../Object/Tank/Tank.h"
#include "../../Object/Camera/TPSCamera/TPSCamera.h"
#include "../SceneManager.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('P'))
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
}

void GameScene::Init()
{
	std::shared_ptr<TPSCamera> camera = std::make_shared<TPSCamera>();
	m_objList.push_back(camera);

	std::shared_ptr<Ground>ground;
	ground = std::make_shared<Ground>();
	m_objList.push_back(ground);

	std::shared_ptr<Tank>tank;
	tank = std::make_shared<Tank>();
	tank->SetCamera(camera);
	camera->SetTarget(tank);
	m_objList.push_back(tank);

	

}