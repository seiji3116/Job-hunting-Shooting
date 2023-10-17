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
	// �����Ղ�I�u�W�F�N�g(�s�����ȕ��̂�2D�L����)��Begin��End�̊Ԃɂ܂Ƃ߂�Draw����
	KdShaderManager::Instance().m_HD2DShader.BeginGenerateDepthMapFromLight();
	{
		for (auto& obj : m_objList)
		{
			obj->GenerateDepthMapFromLight();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndGenerateDepthMapFromLight();

	// �X�L�����b�V���������Ղ�I�u�W�F�N�g(�s�����ȕ��̂�2D�L����)��Begin��End�̊Ԃɂ܂Ƃ߂�Draw����
	KdShaderManager::Instance().m_HD2DShader.BeginGenerateDepthMapFromLight_SkinMesh();
	{
		for (auto& obj : m_objList)
		{
			obj->GenerateDepthMapFromLight_SkinMesh();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndGenerateDepthMapFromLight_SkinMesh();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// �A�e�̂���I�u�W�F�N�g(�s�����ȕ��̂�2D�L����)��Begin��End�̊Ԃɂ܂Ƃ߂�Draw����
	KdShaderManager::Instance().m_HD2DShader.BeginLit();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawLit();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndLit();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// �X�L�����b�V�����A�e�̂���I�u�W�F�N�g(�s�����ȕ��̂�2D�L����)��Begin��End�̊Ԃɂ܂Ƃ߂�Draw����
	KdShaderManager::Instance().m_HD2DShader.BeginLit_SkinMesh();
	{
		for (auto& obj : m_objList) 
		{
			obj->DrawLit_SkinMesh();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndLit_SkinMesh();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// �A�e�̂Ȃ��I�u�W�F�N�g(�����ȕ������܂ޕ��̂�G�t�F�N�g)��Begin��End�̊Ԃɂ܂Ƃ߂�Draw����
	KdShaderManager::Instance().m_HD2DShader.BeginUnLit();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawUnLit();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndUnLit();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// �A�e�����邪UnLit�̌�ɕ\���������I�u�W�F�N�g(�����ȕ������܂ޕ��̂�G�t�F�N�g)��Begin��End�̊Ԃɂ܂Ƃ߂�Draw����
	KdShaderManager::Instance().m_HD2DShader.BeginDrawUnlitWithTransparency();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawUnlitWithTransparency();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndDrawUnlitWithTransparency();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// �A�e�����邪UnLit�̌�ɕ\���������I�u�W�F�N�g(�����ȕ������܂ޕ��̂�G�t�F�N�g)��Begin��End�̊Ԃɂ܂Ƃ߂�Draw����(�X�L�����b�V���Ή�)
	KdShaderManager::Instance().m_HD2DShader.BeginDrawUnlitWithTransparency_SkinMesh();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawUnlitWithTransparency_SkinMesh();
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndDrawUnlitWithTransparency_SkinMesh();

	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// �����I�u�W�F�N�g(�������I�u�W�F�N�g��G�t�F�N�g)��Begin��End�̊Ԃɂ܂Ƃ߂�Draw����
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
	// 2D�̕`��͂��̊Ԃōs��
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
		// �s�v�ɂȂ����I�u�W�F�N�g���폜����
		if ((*it)->IsExpired())
		{
			// ����
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
