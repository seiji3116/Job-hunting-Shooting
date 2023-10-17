#include "GameScene.h"
#include "Application/Scene/SceneManager.h"

#include "Application/GameObject/Camera/TPSCamera/TPSCamera.h"
#include "Application/GameObject/Ground/Ground.h"
#include "Application/GameObject/Player/Player.h"
#include "Application/GameObject/Sky/Sky.h"
#include "Application/GameObject/Enemy/Enemy.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('P') & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
	}
}

void GameScene::Init()
{
	//===================================================================
	// �O���E���h������
	//===================================================================
	std::shared_ptr<Ground> ground;
	ground = std::make_shared<Ground>();
	m_objList.push_back(ground);

	//===================================================================
	// �X�J�C�X�t�B�A������
	//===================================================================
	std::shared_ptr<Sky> sky;
	sky = std::make_shared<Sky>();
	m_objList.push_back(sky);

	//===================================================================
	// �v���C���[������
	//===================================================================
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	m_objList.push_back(player);

	//===================================================================
	// �G�l�~�[������
	//===================================================================
	std::shared_ptr<Enemy> enemy;
	enemy = std::make_shared<Enemy>();
	enemy->SetPlayer(player);
	player->SetEnemy(enemy);
	m_objList.push_back(enemy);

	//===================================================================
	// �J����������
	//===================================================================
	std::shared_ptr<TPSCamera> camera = std::make_shared<TPSCamera>();
	camera->Init();
	camera->SetTarget(player);
	player->SetCamera(camera);
	m_objList.push_back(camera);
}
