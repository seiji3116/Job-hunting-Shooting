#pragma once

class GavityValidObjectPos
{
public:
	GavityValidObjectPos(){}
	~GavityValidObjectPos(){}

	Math::Vector3 GetPos();
	void SetPos(Math::Vector3 _pos);

private:
	Math::Vector3 m_pos;
};