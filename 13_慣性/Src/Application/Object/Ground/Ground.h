#pragma once

class GameScene;

class Ground: public KdGameObject
{
public:

	Ground() { Init(); };
	~Ground() {};

	void GenerateDepthMapFromLight()override;
    void DrawLit()override;
	void DrawBright()override;
	void Init()override;

	Math::Matrix GetMat(){ return m_mWorld; }
private:

	std::shared_ptr<KdModelWork> m_model;
	
};