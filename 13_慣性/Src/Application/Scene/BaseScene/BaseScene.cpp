#include "BaseScene.h"

void BaseScene::PreUpdate()
{
	//不要になったオブジェクトを消す
	//std::list
	//std::vector
	//listとvecotrの違い
	//添え字があるかないか
	//ランダムアクセスできるかできないか

	//listとvectorどっちが効率的か
	//領域を削除する際にコピーが発生するかしないか
	//vectorは発生し、listは発生しない

	//イテレータ...コンテナを操作するポインタ
	//ポインタ...変数のアドレスを記憶する領域
	//コンテナ...vectorとかlistの事

	//m_objlist コンテナ
	//イテレータ
	//std::list<std::shared_ptr<KdGameObject>>::iterator it;
	//イテレータにコンテナの先頭を代入
	//it = m_objList.begin();

	//リストの整備
	//autoを使用する
	//範囲ベースFor　イテレータ生成時
	auto it = m_objList.begin();

	while (it != m_objList.end())
	{
		//不要になったオブジェクトを消す
		if ((*it)->IsExpired())
		{
			//消す
			it = m_objList.erase(it);
		}
		else
		{
			++it;//次へ
		}
	}
}

void BaseScene::Update()
{
	for (auto& obj : m_objList)
	{
		obj->Update();//ポリモーフィズム
	}
	Event();
}

void BaseScene::PostUpdate()
{
	for (auto& obj : m_objList)
	{
		obj->PostUpdate();//ポリモーフィズム
	}
}

void BaseScene::PreDraw()
{
	for (auto& obj : m_objList)
	{
		obj->PreDraw();
	}
}

void BaseScene::Draw()
{
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 光を遮るオブジェクト(不透明な物体や2Dキャラ)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_HD2DShader.BeginGenerateDepthMapFromLight();
	{
		for (auto& obj : m_objList)
		{
			obj->GenerateDepthMapFromLight();//ポリモーフィズム
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndGenerateDepthMapFromLight();


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影のあるオブジェクト(不透明な物体や2Dキャラ)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_HD2DShader.BeginLit();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawLit();//ポリモーフィズム
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndLit();


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影のないオブジェクト(透明な部分を含む物体やエフェクト)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_HD2DShader.BeginUnLit();
	{

	}
	KdShaderManager::Instance().m_HD2DShader.EndUnLit();


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 光源オブジェクト(自ら光るオブジェクトやエフェクト)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_postProcessShader.BeginBright();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawBright();//ポリモーフィズム
		}
	}
	KdShaderManager::Instance().m_postProcessShader.EndBright();

}

void BaseScene::DrawSprite()
{
	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 2Dの描画はこの間で行う
	KdShaderManager::Instance().m_spriteShader.Begin();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawSprite();
		}
	}
	KdShaderManager::Instance().m_spriteShader.End();
}

void BaseScene::DrawDebug()
{
	KdShaderManager::Instance().m_HD2DShader.BeginUnLit();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawDebug();//ポリモーフィズム
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndUnLit();
}

void BaseScene::Event()
{
}

void BaseScene::Init()
{
}
