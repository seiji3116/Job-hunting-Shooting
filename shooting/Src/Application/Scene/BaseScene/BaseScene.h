#pragma once

class KdGameObject;

class BaseScene
{
public:
	BaseScene() { Init(); }
	~BaseScene() {}

	void PreDraw();
	void Draw();
	void DrawSprite();

	void PreUpdate();
	void Update();
	void PostUpdate();

	void DrawDebug();


	const std::list<std::shared_ptr<KdGameObject>>& GetObjList()
	{
		return m_objList;
	}
	void AddObject(const std::shared_ptr<KdGameObject>& _obj)
	{
		m_objList.push_back(_obj);
	}

protected:
	virtual void Init();
	virtual void Event();

	// 全オブジェクトを管理
	std::list<std::shared_ptr<KdGameObject>> m_objList;
};