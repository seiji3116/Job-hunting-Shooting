#pragma once

class BaseScene : public std::enable_shared_from_this<BaseScene>
{
public:

	BaseScene() { Init(); }
	~BaseScene() {}

	void PreUpdate();
	void Update();
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	//virtual void Release();

	const std::list<std::shared_ptr<KdGameObject>> GetObjList()
	{
		return m_objList;
	}
	void AddObject(const std::shared_ptr<KdGameObject> _obj) { m_objList.push_back(_obj); }

protected:
	virtual void Event();
	virtual void Init();

	//�S�I�u�W�F�N�g�̃A�h���X���Ǘ�
	std::list<std::shared_ptr<KdGameObject>> m_objList;
};