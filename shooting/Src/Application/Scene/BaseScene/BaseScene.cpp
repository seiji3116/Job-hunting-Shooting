#include "BaseScene.h"

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
			obj->GenerateDepthMapFromLight();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndGenerateDepthMapFromLight();

	// スキンメッシュかつ光を遮るオブジェクト(不透明な物体や2Dキャラ)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_HD2DShader.BeginGenerateDepthMapFromLight_SkinMesh();
	{
		for (auto& obj : m_objList)
		{
			obj->GenerateDepthMapFromLight_SkinMesh();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndGenerateDepthMapFromLight_SkinMesh();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影のあるオブジェクト(不透明な物体や2Dキャラ)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_HD2DShader.BeginLit();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawLit();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndLit();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// スキンメッシュかつ陰影のあるオブジェクト(不透明な物体や2Dキャラ)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_HD2DShader.BeginLit_SkinMesh();
	{
		for (auto& obj : m_objList) 
		{
			obj->DrawLit_SkinMesh();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndLit_SkinMesh();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影のないオブジェクト(透明な部分を含む物体やエフェクト)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_HD2DShader.BeginUnLit();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawUnLit();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndUnLit();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影があるがUnLitの後に表示したいオブジェクト(透明な部分を含む物体やエフェクト)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_HD2DShader.BeginDrawUnlitWithTransparency();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawUnlitWithTransparency();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndDrawUnlitWithTransparency();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 陰影があるがUnLitの後に表示したいオブジェクト(透明な部分を含む物体やエフェクト)はBeginとEndの間にまとめてDrawする(スキンメッシュ対応)
	KdShaderManager::Instance().m_HD2DShader.BeginDrawUnlitWithTransparency_SkinMesh();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawUnlitWithTransparency_SkinMesh();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndDrawUnlitWithTransparency_SkinMesh();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// 光源オブジェクト(自ら光るオブジェクトやエフェクト)はBeginとEndの間にまとめてDrawする
	KdShaderManager::Instance().m_postProcessShader.BeginBright();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawBright();
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

void BaseScene::PreUpdate()
{
	auto it = m_objList.begin();

	while (it != m_objList.end())
	{
		// 不要になったオブジェクトを削除する
		if ((*it)->IsExpired())
		{
			// 消す
			it = m_objList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void BaseScene::Update()
{
	for (auto& obj : m_objList)
	{
		obj->Update();
	}

	Event();
}

void BaseScene::PostUpdate()
{
	for (auto& obj : m_objList)
	{
		obj->PostUpdate();
	}
}

void BaseScene::Init()
{
}

void BaseScene::DrawDebug()
{
	//KdShaderManager::Instance().m_HD2DShader.BeginUnLit();
	//{
	//	for (auto& obj : m_objList)
	//	{
	//		obj->DrawDebug();
	//	}
	//}
	//KdShaderManager::Instance().m_HD2DShader.EndUnLit();
}

void BaseScene::Event()
{

}
