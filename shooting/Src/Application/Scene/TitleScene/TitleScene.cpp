#include "TitleScene.h"
#include "Application/Scene/SceneManager.h"

#include "Application/GameObject/Camera/TitleCamera/TitleCamera.h"
#include "Application/GameObject/Ground/Ground.h"
#include "Application/GameObject/Player/Player.h"
#include "Application/GameObject/Sky/Sky.h"
#include "Application/GameObject/UI/TitleUI/TitleUI.h"


void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}
}

void TitleScene::Init()
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
	// �G�l�~�[������
	//===================================================================
	std::shared_ptr<Player> player;
	player = std::make_shared<Player>();
	m_objList.push_back(player);

	//===================================================================
	// �J����������
	//===================================================================
	std::shared_ptr<TitleCamera> camera = std::make_shared<TitleCamera>();
	camera->Init();
	camera->SetTarget(player);
	m_objList.push_back(camera);

	//===================================================================
	// UI������
	//===================================================================
	std::shared_ptr<TitleUI> titleUI = std::make_shared<TitleUI>();
	titleUI->Init();
	m_objList.push_back(titleUI);
}
