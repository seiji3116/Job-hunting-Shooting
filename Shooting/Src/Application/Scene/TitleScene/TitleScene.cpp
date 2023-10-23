#include "TitleScene.h"
#include "../SceneManager.h"

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}
}

void TitleScene::Init()
{
	
}
