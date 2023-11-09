#include "GameScene.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Camera/TPSCamera/TPSCamera.h"
#include "../../Object/Sky/Sky.h"
#include "../../Object/Rock/Rock.h"
#include "../../Object/Enemy/Enemy.h"
#include "../../Object/MotherEnemy/MotherEnemy.h"
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
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	AddObject(player);

	std::shared_ptr<MotherEnemy> mEnemy;
	mEnemy = std::make_shared<MotherEnemy>();
	AddObject(mEnemy);

	std::shared_ptr<Enemy> enemy;
	enemy = std::make_shared<Enemy>();
	enemy->SetPlayer(player);
	enemy->SetState("Normal");
	AddObject(enemy);

	for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<Enemy> enemy;
		enemy = std::make_shared<Enemy>();
		enemy->SetState("Laser");
		enemy->SetPlayer(player);
		enemy->SetPos(mEnemy->GetNodePos(i));
		AddObject(enemy);
	}

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::shared_ptr<Rock> rock;
			rock = std::make_shared<Rock>();
			rock->SetPos(Math::Vector3(i * 3, 0, j * 3));
			rock->SetPlayer(player);
			AddObject(rock);
		}
	}

	std::shared_ptr<Sky> sky;
	sky = std::make_shared<Sky>();
	sky->SetPlayer(player);
	AddObject(sky);

	std::shared_ptr<TPSCamera> camera = std::make_shared<TPSCamera>();
	player->SetCamera(camera);
	camera->SetTarget(player);
	AddObject(camera);
}