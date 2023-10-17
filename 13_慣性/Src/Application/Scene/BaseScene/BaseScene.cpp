#include "BaseScene.h"

void BaseScene::PreUpdate()
{
	//�s�v�ɂȂ����I�u�W�F�N�g������
	//std::list
	//std::vector
	//list��vecotr�̈Ⴂ
	//�Y���������邩�Ȃ���
	//�����_���A�N�Z�X�ł��邩�ł��Ȃ���

	//list��vector�ǂ����������I��
	//�̈���폜����ۂɃR�s�[���������邩���Ȃ���
	//vector�͔������Alist�͔������Ȃ�

	//�C�e���[�^...�R���e�i�𑀍삷��|�C���^
	//�|�C���^...�ϐ��̃A�h���X���L������̈�
	//�R���e�i...vector�Ƃ�list�̎�

	//m_objlist �R���e�i
	//�C�e���[�^
	//std::list<std::shared_ptr<KdGameObject>>::iterator it;
	//�C�e���[�^�ɃR���e�i�̐擪����
	//it = m_objList.begin();

	//���X�g�̐���
	//auto���g�p����
	//�͈̓x�[�XFor�@�C�e���[�^������
	auto it = m_objList.begin();

	while (it != m_objList.end())
	{
		//�s�v�ɂȂ����I�u�W�F�N�g������
		if ((*it)->IsExpired())
		{
			//����
			it = m_objList.erase(it);
		}
		else
		{
			++it;//����
		}
	}
}

void BaseScene::Update()
{
	for (auto& obj : m_objList)
	{
		obj->Update();//�|�����[�t�B�Y��
	}
	Event();
}

void BaseScene::PostUpdate()
{
	for (auto& obj : m_objList)
	{
		obj->PostUpdate();//�|�����[�t�B�Y��
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
	// �����Ղ�I�u�W�F�N�g(�s�����ȕ��̂�2D�L����)��Begin��End�̊Ԃɂ܂Ƃ߂�Draw����
	KdShaderManager::Instance().m_HD2DShader.BeginGenerateDepthMapFromLight();
	{
		for (auto& obj : m_objList)
		{
			obj->GenerateDepthMapFromLight();//�|�����[�t�B�Y��
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndGenerateDepthMapFromLight();


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// �A�e�̂���I�u�W�F�N�g(�s�����ȕ��̂�2D�L����)��Begin��End�̊Ԃɂ܂Ƃ߂�Draw����
	KdShaderManager::Instance().m_HD2DShader.BeginLit();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawLit();//�|�����[�t�B�Y��
		}
	}
	KdShaderManager::Instance().m_HD2DShader.EndLit();


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// �A�e�̂Ȃ��I�u�W�F�N�g(�����ȕ������܂ޕ��̂�G�t�F�N�g)��Begin��End�̊Ԃɂ܂Ƃ߂�Draw����
	KdShaderManager::Instance().m_HD2DShader.BeginUnLit();
	{

	}
	KdShaderManager::Instance().m_HD2DShader.EndUnLit();


	// ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== ===== =====
	// �����I�u�W�F�N�g(�������I�u�W�F�N�g��G�t�F�N�g)��Begin��End�̊Ԃɂ܂Ƃ߂�Draw����
	KdShaderManager::Instance().m_postProcessShader.BeginBright();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawBright();//�|�����[�t�B�Y��
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

void BaseScene::DrawDebug()
{
	KdShaderManager::Instance().m_HD2DShader.BeginUnLit();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawDebug();//�|�����[�t�B�Y��
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
